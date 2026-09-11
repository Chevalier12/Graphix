# Graphix

**An independent SDL fork maintained for Cerneala.**

Graphix provides the native multimedia and platform foundation used by the
Cerneala project. It is derived from [Simple DirectMedia Layer (SDL)](https://github.com/libsdl-org/SDL),
originally authored by Sam Lantinga and developed by the SDL contributors.
Graphix is a modified, independently maintained fork, not an official SDL
release and not endorsed by the SDL maintainers. We do not claim authorship of
the original SDL software.

## Why this fork exists

Our development workflow includes AI-assisted engineering. SDL's upstream
[contribution policy at our starting release](https://github.com/libsdl-org/SDL/blob/release-3.4.16/AGENTS.md)
does not accept that workflow for upstream contributions. We therefore maintain
our AI-assisted changes independently in Graphix. This is a difference in
contribution policy, not a claim that SDL forbids independent forks or that an
SDL maintainer rejected a patch from us. SDL's upstream policy does not govern
contributions to Graphix.

## Upstream base and compatibility

- Starting release: **SDL 3.4.16**, tag `release-3.4.16`.
- Upstream commit: `fa2c02bb6e21974a89ea9824bc53c9932abe5f9c`.
- Graphix development branch: `graphix`.
- The original `SDL_*` API, ABI and native library names remain unchanged.
  Graphix is the fork's identity, not a new incompatible C API.
- Upstream history and tags are retained. Updates are deliberate and versioned,
  not automatic tracking of SDL's development branch.

Graphix adds a versioned native-only NuGet build recipe, an explicit
six-RID GitHub Actions workflow and the Windows maximum-size correction.
Build and test evidence is scoped to the recorded scenarios, not a claim of
complete cross-platform or GPU certification.
See [GRAPHIX.md](GRAPHIX.md) for the change record and verification status.

## Install the native runtime

The graphix.6 candidate is prepared for maintainer upload; the following
installation commands apply after that upload. This repository's workflow
builds and verifies the archive but does not publish it.

The public package feed is [NuGet.org](https://www.nuget.org/packages/Graphix.Native/3.4.16-graphix.6):

```powershell
dotnet add package Graphix.Native --version 3.4.16-graphix.6
```

This prerelease package contains Windows, Linux and macOS native assets for
x64 and ARM64. It provides no managed API. C# applications can use the separate
[Graphix-CS 3.4.16.1 binding](https://www.nuget.org/packages/Graphix-CS/3.4.16.1).
Do not combine Graphix.Native with another package supplying the same SDL3
native libraries. Normal restore needs no GitHub authentication, Actions
artifact download or local package feed.

## Building

SDL's [installation guide](INSTALL.md) and [CMake guide](docs/README-cmake.md)
remain the build references. The upstream README is preserved in
[README-SDL.md](README-SDL.md) as upstream documentation, not Graphix branding.

For versioned native artifacts, use the
[Graphix.Native build and packaging instructions](packaging/Graphix.Native/README.md).
The manually dispatched `Graphix native packages` workflow builds and tests
Windows, Linux and macOS on x64 and ARM64, then assembles a NuGet artifact only
if all six jobs pass. It does not publish packages or create GitHub releases.
Public NuGet publication is a separate, explicitly authorized step using the
exact verified artifact. CI artifact retention does not limit the public
package feed. Never replace the contents of an already-used package version.

## License and provenance

Graphix retains the original [zlib license notice](LICENSE.txt) unchanged.
Existing SDL copyright and license notices remain intact. Changes made by
Graphix must be identified as modifications and must not be presented as an
official SDL release. Retain any additional notices accompanying third-party
components when redistributing them.
