# Graphix addition: verify six native builds before creating a NuGet package.
[CmdletBinding()]
param(
    [Parameter(Mandatory)]
    [ValidatePattern('^3\.4\.16-graphix\.[1-9][0-9]*$')]
    [string] $PackageVersion
)

$ErrorActionPreference = 'Stop'
Set-StrictMode -Version Latest
$graphixRoot = Split-Path -Parent $PSScriptRoot
$nativeRoot = Join-Path $graphixRoot "out/graphix/$PackageVersion"
$packageRoot = Join-Path $graphixRoot 'out/packages'
$packagePath = Join-Path $packageRoot "Graphix.Native.$PackageVersion.nupkg"
if (Test-Path -LiteralPath $packagePath) {
    throw "Refusing to overwrite an existing version: $packagePath"
}

$runtimeFiles = [ordered]@{
    'win-x64' = @('SDL3.dll')
    'win-arm64' = @('SDL3.dll')
    'linux-x64' = @('libSDL3.so', 'libSDL3.so.0', 'libSDL3.so.0.4.16')
    'linux-arm64' = @('libSDL3.so', 'libSDL3.so.0', 'libSDL3.so.0.4.16')
    'osx-x64' = @('libSDL3.dylib', 'libSDL3.0.dylib')
    'osx-arm64' = @('libSDL3.dylib', 'libSDL3.0.dylib')
}
$sourceCommit = $null
$expectedEntries = [ordered]@{}
foreach ($rid in $runtimeFiles.Keys) {
    $ridRoot = Join-Path $nativeRoot $rid
    $manifest = Get-Content -LiteralPath (Join-Path $ridRoot 'build.json') -Raw | ConvertFrom-Json
    if ($manifest.packageId -ne 'Graphix.Native' -or $manifest.packageVersion -ne $PackageVersion -or
        $manifest.upstreamVersion -ne '3.4.16' -or $manifest.runtimeIdentifier -ne $rid -or
        $manifest.sourceCommit -notmatch '^[0-9a-f]{40}$') {
        throw "Invalid Graphix provenance for $rid."
    }
    if (-not $sourceCommit) { $sourceCommit = $manifest.sourceCommit }
    if ($manifest.sourceCommit -ne $sourceCommit) { throw 'Native artifacts come from different commits.' }
    if (Compare-Object ($runtimeFiles[$rid] | Sort-Object) ($manifest.nativeFiles.name | Sort-Object)) {
        throw "Unexpected native file set for $rid."
    }
    foreach ($file in $manifest.nativeFiles) {
        $nativePath = Join-Path $ridRoot "native/$($file.name)"
        if ((Get-Item -LiteralPath $nativePath).Length -eq 0 -or
            (Get-FileHash -LiteralPath $nativePath -Algorithm SHA256).Hash -ne $file.sha256) {
            throw "Native artifact hash mismatch: $rid/$($file.name)"
        }
        $expectedEntries["runtimes/$rid/native/$($file.name)"] = $file.sha256
    }
    $expectedEntries["provenance/$rid/build.json"] = (Get-FileHash -LiteralPath (Join-Path $ridRoot 'build.json') -Algorithm SHA256).Hash
}

$checkoutCommit = (git -C $graphixRoot rev-parse HEAD).Trim()
if ($LASTEXITCODE -ne 0 -or $checkoutCommit -ne $sourceCommit) {
    throw 'Package using the same Graphix checkout commit as the native artifacts.'
}

New-Item -ItemType Directory -Path $packageRoot -Force | Out-Null
$projectPath = Join-Path $graphixRoot 'packaging/Graphix.Native/Graphix.Native.csproj'
& dotnet pack $projectPath -c Release "-p:PackageVersion=$PackageVersion" `
    "-p:GraphixNativeRoot=$nativeRoot" "-p:RepositoryCommit=$sourceCommit" -o $packageRoot
if ($LASTEXITCODE -ne 0) { throw 'Graphix NuGet pack failed.' }
if (-not (Test-Path -LiteralPath $packagePath)) { throw 'Expected Graphix package was not created.' }

$expectedEntries['LICENSE.txt'] = (Get-FileHash -LiteralPath (Join-Path $graphixRoot 'LICENSE.txt') -Algorithm SHA256).Hash
$expectedEntries['README-SDL.md'] = (Get-FileHash -LiteralPath (Join-Path $graphixRoot 'README-SDL.md') -Algorithm SHA256).Hash
$expectedEntries['README.md'] = (Get-FileHash -LiteralPath (Join-Path $graphixRoot 'packaging/Graphix.Native/README.md') -Algorithm SHA256).Hash
$package = [IO.Compression.ZipFile]::OpenRead($packagePath)
$hasher = [Security.Cryptography.SHA256]::Create()
try {
    foreach ($entryName in $expectedEntries.Keys) {
        $entry = $package.GetEntry($entryName)
        if ($null -eq $entry) { throw "Missing package entry: $entryName" }
        $stream = $entry.Open()
        try { $hash = [Convert]::ToHexString($hasher.ComputeHash($stream)) }
        finally { $stream.Dispose() }
        if ($hash -ne $expectedEntries[$entryName]) { throw "Package entry hash mismatch: $entryName" }
    }
    $payloadEntries = @($package.Entries.FullName | Where-Object { $_ -match '^(runtimes|provenance)/' } | Sort-Object)
    $expectedPayload = @($expectedEntries.Keys | Where-Object { $_ -match '^(runtimes|provenance)/' } | Sort-Object)
    if (Compare-Object $expectedPayload $payloadEntries) { throw 'Unexpected native or provenance package contents.' }
    if ($package.Entries.FullName -match '^(lib|ref)/') { throw 'The native-only package contains managed assets.' }
}
finally {
    $hasher.Dispose()
    $package.Dispose()
}
Write-Host 'Verified packaged native assets, provenance, license and documentation bytes.'
Get-FileHash -LiteralPath $packagePath -Algorithm SHA256
