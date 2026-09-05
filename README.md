# Graphix

**An independent SDL fork maintained for Cerneala.**

Graphix provides the native multimedia and platform foundation used by the
Cerneala project. It is derived from [Simple DirectMedia Layer (SDL)](https://github.com/libsdl-org/SDL),
originally authored by Sam Lantinga and developed by the SDL contributors.
Graphix is a modified, independently maintained fork, not an official SDL
release and not endorsed by the SDL maintainers. We do not claim authorship of
the original SDL software.

## Why this fork exists

During Cerneala development, we reproduced a Windows window-sizing defect in
SDL 3.4.14 and 3.4.16: a finite maximum width or height is ignored during native
maximization when the other dimension is unlimited.

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

The Graphix changes so far establish the fork's identity and documentation
only. They do not yet fix the window-sizing defect, publish native
packages, or certify a Graphix build. See [GRAPHIX.md](GRAPHIX.md) for the change
record and verification status.

## Building

SDL's [installation guide](INSTALL.md) and [CMake guide](docs/README-cmake.md)
remain the build references. The upstream README is preserved in
[README-SDL.md](README-SDL.md) as upstream documentation, not Graphix branding.

## License and provenance

Graphix retains the original [zlib license notice](LICENSE.txt) unchanged.
Existing SDL copyright and license notices remain intact. Changes made by
Graphix must be identified as modifications and must not be presented as an
official SDL release. Retain any additional notices accompanying third-party
components when redistributing them.
