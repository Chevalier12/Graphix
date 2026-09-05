# Build Graphix's unchanged SDL ABI and stage native assets for NuGet.
# Graphix addition; the SDL source and license remain separately attributed.
# Requires PowerShell 7, CMake, and the target platform's C/C++ toolchain.
[CmdletBinding()]
param(
    [Parameter(Mandatory)]
    [ValidateSet('win-x64', 'win-arm64', 'linux-x64', 'linux-arm64', 'osx-x64', 'osx-arm64')]
    [string] $RuntimeIdentifier,

    [Parameter(Mandatory)]
    [ValidatePattern('^3\.4\.16-graphix\.[1-9][0-9]*$')]
    [string] $PackageVersion
)

$ErrorActionPreference = 'Stop'
Set-StrictMode -Version Latest
$graphixRoot = Split-Path -Parent $PSScriptRoot
$artifactRoot = Join-Path $graphixRoot "out/graphix/$PackageVersion/$RuntimeIdentifier"
$buildRoot = Join-Path $artifactRoot 'build'
$installRoot = Join-Path $artifactRoot 'install'
$nativeRoot = Join-Path $artifactRoot 'native'
$logRoot = Join-Path $artifactRoot 'logs'

Push-Location $graphixRoot
try {
    $sourceCommit = (git rev-parse HEAD).Trim()
    if ($LASTEXITCODE -ne 0) { throw 'Cannot determine the Graphix source commit.' }
    # Package artifacts must be attributable to committed native sources.
    $nativeChanges = git status --porcelain -- src include cmake CMakeLists.txt
    if ($LASTEXITCODE -ne 0 -or $nativeChanges) {
        throw 'Native source changes must be committed before producing package artifacts. Use a separate CMake build for pre-commit regression testing.'
    }

    $targetOs, $targetArchitecture = $RuntimeIdentifier.Split('-')
    $hostArchitecture = [Runtime.InteropServices.RuntimeInformation]::ProcessArchitecture.ToString().ToLowerInvariant()
    if (($targetOs -eq 'win' -and -not $IsWindows) -or
        ($targetOs -eq 'linux' -and -not $IsLinux) -or
        ($targetOs -eq 'osx' -and -not $IsMacOS)) {
        throw "Build $RuntimeIdentifier on its own operating system."
    }
    if ($IsLinux -and $targetArchitecture -ne $hostArchitecture) {
        throw 'Linux builds require a runner matching the target architecture.'
    }

    $cmakeCommand = Get-Command cmake -ErrorAction SilentlyContinue
    $cmake = if ($cmakeCommand) { $cmakeCommand.Source } else { $null }
    $platformArguments = @()
    if ($IsWindows) {
        $vswhere = Join-Path ${env:ProgramFiles(x86)} 'Microsoft Visual Studio/Installer/vswhere.exe'
        $visualStudio = & $vswhere -latest -requires Microsoft.VisualStudio.Component.VC.CMake.Project -format json | ConvertFrom-Json
        if ($LASTEXITCODE -ne 0 -or -not $visualStudio) { throw 'MSVC build tools were not found.' }
        if (-not $cmake) {
            $cmake = Join-Path $visualStudio.installationPath 'Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/cmake.exe'
        }
        $generator = switch (([version]$visualStudio.installationVersion).Major) {
            17 { 'Visual Studio 17 2022' }
            18 { 'Visual Studio 18 2026' }
            default { throw 'Unsupported Visual Studio generator; update the verified build recipe.' }
        }
        $msvcArchitecture = if ($targetArchitecture -eq 'arm64') { 'ARM64' } else { 'x64' }
        $platformArguments = @('-G', $generator, '-A', $msvcArchitecture,
            '-DCMAKE_MSVC_RUNTIME_LIBRARY=MultiThreaded$<$<CONFIG:Debug>:Debug>')
    }
    else {
        $platformArguments = @('-G', 'Ninja', '-DCMAKE_BUILD_TYPE=Release')
        if ($IsMacOS) {
            $appleArchitecture = if ($targetArchitecture -eq 'x64') { 'x86_64' } else { 'arm64' }
            # Preserve the deployment target used by SDL3-CS.MacOS 3.4.14.1.
            $platformArguments += @("-DCMAKE_OSX_ARCHITECTURES=$appleArchitecture",
                '-DCMAKE_OSX_DEPLOYMENT_TARGET=12.0', '-DSDL_FRAMEWORK=OFF')
        }
    }
    if (-not $cmake -or -not (Test-Path -LiteralPath $cmake)) { throw 'CMake was not found.' }
    New-Item -ItemType Directory -Path $logRoot, $nativeRoot -Force | Out-Null

    & $cmake -S $graphixRoot -B $buildRoot @platformArguments `
        -DSDL_SHARED=ON -DSDL_STATIC=OFF -DSDL_TEST_LIBRARY=ON -DSDL_TESTS=ON `
        -DSDL_EXAMPLES=OFF -DSDL_WERROR=ON -DSDL_INSTALL=ON -DSDL_INSTALL_DOCS=OFF `
        -DCMAKE_INSTALL_LIBDIR=lib "-DCMAKE_INSTALL_PREFIX=$installRoot" `
        "-DSDL_VENDOR_INFO=Graphix $PackageVersion commit $sourceCommit" `
        2>&1 | Tee-Object -FilePath (Join-Path $logRoot 'configure.log')
    if ($LASTEXITCODE -ne 0) { throw 'Graphix CMake configuration failed.' }
    & $cmake --build $buildRoot --config Release --parallel 8 `
        2>&1 | Tee-Object -FilePath (Join-Path $logRoot 'build.log')
    if ($LASTEXITCODE -ne 0) { throw 'Graphix native build failed.' }
    & $cmake --install $buildRoot --config Release `
        2>&1 | Tee-Object -FilePath (Join-Path $logRoot 'install.log')
    if ($LASTEXITCODE -ne 0) { throw 'Graphix staging install failed.' }

    $libraryNames = switch ($targetOs) {
        'win' { @('SDL3.dll') }
        'linux' { @('libSDL3.so', 'libSDL3.so.0', 'libSDL3.so.0.4.16') }
        'osx' { @('libSDL3.dylib', 'libSDL3.0.dylib') }
    }
    $libraryDirectory = Join-Path $installRoot $(if ($IsWindows) { 'bin' } else { 'lib' })
    $nativeFiles = foreach ($libraryName in $libraryNames) {
        $sourceFile = Join-Path $libraryDirectory $libraryName
        $destinationFile = Join-Path $nativeRoot $libraryName
        # Materialize aliases as ordinary files for NuGet, not platform symlinks.
        [IO.File]::WriteAllBytes($destinationFile, [IO.File]::ReadAllBytes($sourceFile))
        [ordered]@{
            name = $libraryName
            sha256 = (Get-FileHash -LiteralPath $destinationFile -Algorithm SHA256).Hash.ToLowerInvariant()
        }
    }
    [ordered]@{
        packageId = 'Graphix.Native'
        packageVersion = $PackageVersion
        upstreamVersion = '3.4.16'
        runtimeIdentifier = $RuntimeIdentifier
        sourceCommit = $sourceCommit
        nativeFiles = @($nativeFiles)
    } | ConvertTo-Json -Depth 5 | Set-Content -LiteralPath (Join-Path $artifactRoot 'build.json') -Encoding utf8NoBOM
    Write-Host "Graphix build staged at $artifactRoot. Tests have not been run by this script."
}
finally {
    Pop-Location
}
