# Graphix.Native

Native runtime package for Graphix, an independent SDL fork maintained for
Cerneala. SDL was originally authored by Sam Lantinga and developed by the SDL
contributors. Graphix is not an official or endorsed SDL release.

This package preserves SDL3's C API, ABI and native library filenames. The
`Graphix-CS` managed binding remains a separate dependency. Do not combine this
package with another package supplying the same native SDL3 libraries.

The package contains Windows, Linux and macOS runtime assets for x64 and ARM64,
under NuGet's `runtimes/<rid>/native/` layout. It does not provide a managed API,
SDL_shadercross or other SDL companion libraries.

## Installation

The graphix.5 candidate awaits maintainer upload. These installation commands
apply after that upload; the build/package workflow does not publish it.

Install [Graphix.Native 3.4.16-graphix.5 from NuGet.org](https://www.nuget.org/packages/Graphix.Native/3.4.16-graphix.5):

```powershell
dotnet add package Graphix.Native --version 3.4.16-graphix.5
```

This is a prerelease package. Its exact version can be restored directly;
package browsers may require their prerelease filter to show it. C# consumers
can use the separate [Graphix-CS 3.4.16.1](https://www.nuget.org/packages/Graphix-CS/3.4.16.1)
managed binding. Do not reference both Graphix-CS and SDL3-CS in one application.
Normal restore uses NuGet.org and does not require GitHub authentication,
temporary CI artifacts or a local package feed.

## Building the package

From the Graphix repository, build each RID on its matching operating system:

```powershell
./build-scripts/Build-GraphixNative.ps1 -RuntimeIdentifier win-x64 -PackageVersion 3.4.16-graphix.5
```

Repeat for `win-arm64`, `linux-x64`, `linux-arm64`, `osx-x64` and `osx-arm64`,
collecting the outputs under `out/graphix/3.4.16-graphix.5/<rid>/`.
Linux builds require a matching-architecture runner. Windows ARM64 builds
require the ARM64 MSVC tools. CMake and platform development dependencies are
required; building alone does not run or certify the native tests.

Run CTest separately with `SDL_TESTS_QUICK=1`, the RID's `build` directory,
`-C Release --output-on-failure --parallel 1 --no-tests=error` and an output
JUnit path for evidence. The inherited CTest configuration uses dummy video and
audio drivers; passing it does not prove native desktop input, maximization or
GPU behavior.

The manual `Graphix native packages` workflow performs those build/test steps
on six matching-architecture runners and packages only after all six pass.
CTest also runs the deterministic input-lifetime regressions with the real
Windows driver on both Windows architectures. They use named Win32 imports and
source-owned thread naming, not DLL offsets or physical hotplug timing. The
workflow separately runs the native maximum-size regression on both Windows
architectures. Its GitHub Actions artifacts are retained for 30 days for build
verification. Public NuGet publication is a separate, explicitly authorized
step using the exact verified artifact, not a dependency on artifact retention.

The initial recipe uses Ubuntu 24.04 for both Linux architectures and a macOS
12.0 deployment target for both macOS architectures, matching the prior
SDL3-CS native package recipes rather than the build host's macOS default.
Windows uses a static MSVC runtime to avoid a new VC runtime DLL dependency.
These are build settings, not proof of runtime support on every older OS.

After collecting all six builds of the same commit:

```powershell
./build-scripts/Pack-GraphixNative.ps1 -PackageVersion 3.4.16-graphix.5
```

The pack script checks the public installation documentation, complete RID
set, source commit and binary hashes.
It writes to `out/packages/` and refuses to overwrite an existing package of the
same version. A changed native build requires a new package version.

To validate the exact downloaded official CI archive without repacking, first
download its six native payload artifacts to the same layout and check out
their source commit, then run:

```powershell
./build-scripts/Pack-GraphixNative.ps1 -PackageVersion 3.4.16-graphix.5 -VerifyPackagePath ./out/packages/Graphix.Native.3.4.16-graphix.5.nupkg
```

This mode is read-only for the archive. It checks the NuGet repository commit,
version, all native/provenance hashes, and documentation against committed
bytes (not Windows checkout newline conversions).

The original zlib license is retained as `LICENSE.txt`; the original SDL README
is retained as `README-SDL.md`. Per-RID `provenance/` manifests record the source
commit and native hashes. At runtime, `SDL_GetRevision()` includes the Graphix
package version and source commit.
