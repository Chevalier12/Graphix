# Graphix release contract: both entry-point READMEs describe the public package.
[CmdletBinding()]
param(
    [Parameter(Mandatory)]
    [ValidatePattern('^3\.4\.16-graphix\.[1-9][0-9]*$')]
    [string] $PackageVersion
)

$ErrorActionPreference = 'Stop'
Set-StrictMode -Version Latest
$graphixRoot = Split-Path -Parent $PSScriptRoot
$packageUrl = "https://www.nuget.org/packages/Graphix.Native/$PackageVersion"
$installCommand = "dotnet add package Graphix.Native --version $PackageVersion"
foreach ($relativePath in @('README.md', 'packaging/Graphix.Native/README.md')) {
    $readme = Get-Content -LiteralPath (Join-Path $graphixRoot $relativePath) -Raw
    if (-not $readme.Contains($packageUrl, [StringComparison]::Ordinal) -or
        -not $readme.Contains($installCommand, [StringComparison]::Ordinal)) {
        throw "$relativePath must document public NuGet installation of Graphix.Native $PackageVersion."
    }
    if ($readme -match 'No NuGet publication|not an already published NuGet feed|Publication and the downstream feed remain separate decisions') {
        throw "$relativePath still describes unpublished-only distribution."
    }
}

Write-Output "Public Graphix.Native $PackageVersion documentation contract passed."
