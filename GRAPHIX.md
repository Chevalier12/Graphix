# Graphix provenance and change record

## Starting point

- Upstream: https://github.com/libsdl-org/SDL
- Release: SDL 3.4.16 (`release-3.4.16`)
- Commit: `fa2c02bb6e21974a89ea9824bc53c9932abe5f9c`
- Original authorship and license: unchanged; see LICENSE.txt and git history.

## 2026-09-06: independent fork identity

Established Graphix branding, preserved the upstream README separately and
introduced explicitly disclosed AI-assisted contribution rules for Graphix.
The SDL implementation, headers, API, ABI and native library names are unchanged.
These documentation changes were prepared with AI assistance.

Verification for this change: original license blob and upstream ancestry
checked; preserved upstream README checked; changed paths and local links
reviewed; git whitespace check performed. No native Graphix build, testautomation
run, release package or human runtime validation is claimed by this entry.

## 2026-09-06: remove contribution and agent policies

At the maintainer's request, removed the agent instruction files, contribution
guides and pull request template. Updated documentation references and removed
Graphix's contribution-policy requirements from the README. The fork rationale
and this historical change record remain; neither makes upstream SDL's policy
a rule for Graphix.

These documentation changes were prepared with AI assistance. SDL licensing,
attribution, upstream history and native sources are unchanged. Verification
covers the changed paths, local documentation links and whitespace, plus
preservation of the license and native source tree. No native build or test run
is claimed for this documentation-only change.

## 2026-09-06: native build and package preparation

Added Graphix-owned build and pack scripts, a native-only `Graphix.Native`
NuGet project, and a manually dispatched six-RID workflow. The pack script
requires complete native payloads with matching versions, source commits and
SHA-256 hashes; it checks the resulting archive, provenance and license bytes.
The workflow uploads build/test evidence and a package artifact without
publishing to NuGet or creating a release. Graphix no longer dispatches the
inherited all-platform SDL build matrix on branch pushes.

The SDL C/C++ implementation and headers remain unchanged. `SDL3-CS` remains
the managed binding, while the proposed native package replaces the separate
SDL3-CS Windows/Linux/macOS runtime packages. SDL companion libraries such as
SDL_shadercross are outside this package's scope.

Local Windows x64 evidence on native source commit
`688e273dc85630a5d6eff02b499b6edf3ab02dc1`:

- MSVC 19.51 / CMake 4.3.1, Release shared library with static CRT and warnings
  treated as errors: build succeeded.
- Existing CTest suite with `SDL_TESTS_QUICK=1`: 25 passed, 0 failed, 66.41 s.
  That suite uses dummy video/audio; it does not cover the native sizing bug.
- The Graphix package build recipe also built and staged the x64 DLL. Its
  SHA-256 is `8b5b00ee2b19fac0bf8f3e42303294d7855dc6b42f6d999de5f918e23b9ef6cd`.
  Re-running that recipe and its own CTest tree passed all 25 tests in 56.34 s.
- An isolated Cerneala test output loaded that DLL and identified Graphix
  through `SDL_GetRevision()`. The corrected native window fixture plus
  dependency provenance test produced 10 passes, 2 sizing failures, 0 skips.
  The two sizing values match the upstream reproduction below.
- An additional input-fixture failure was traced to synthetic key messages
  arriving without native keyboard focus. A real click/key fixture passed
  three repeated runs each with official SDL 3.4.16 and Graphix. No production
  input behavior was changed to conceal the fixture error.
- The prior SDL3-CS 3.4.14.1 downstream Metal fence-query fix is already present
  in SDL 3.4.16's source. This source comparison is not macOS runtime validation.
- Packaging correctly rejected the incomplete local RID set. No six-RID NuGet
  package has yet been produced or consumed by Cerneala.
- PowerShell syntax checks and actionlint 1.7.12 passed for the new recipe and
  workflow. The inherited `build.yml` has a direct commit-message interpolation
  warning, reproduced unchanged at HEAD; its controller is disabled in Graphix.

Cross-platform CI, completed package assembly, downstream NuGet integration,
the native sizing fix, broader Cerneala verification and human validation
remain pending. These Graphix additions were prepared with AI assistance.

## Reproduced upstream defect awaiting a fix

Cerneala's automated Windows x64 window contract tests reproduced the following
on the unmodified official SDL 3.4.16 DLL (file version 3.4.16.0):

| Maximum client dimensions | Expected constrained axis | Observed after native maximize |
| --- | --- | --- |
| Width 700; height unlimited | Width at most 700 | Width 1920 |
| Width unlimited; height 600 | Height at most 600 | Height 991 |

The same eleven native window tests produced nine passes, two failures and zero
skips. Both-finite and both-unbounded maximum-size cases passed. The testhost's
loaded module path and SHA-256 were observed, not inferred from a package label.

- Official asset: `SDL3-3.4.16-win32-x64.zip` from SDL's release-3.4.16.
- Archive SHA-256: `4217944b4e51457af4a59c82d883f8443b3e65964b2acd8943484c492756c4b6`.
- Loaded DLL SHA-256: `1f98969319302a100931f4385e5918a0bd53ab07773040682d22e7edb54858c0`.
- Owning source: `src/video/windows/SDL_windowsevents.c`, WM_GETMINMAXINFO.
  The implementation applies maximum tracking sizes only when both max_w and
  max_h are nonzero, dropping a finite limit when the other axis is unlimited.

This evidence is a focused upstream diagnosis, not full-suite certification of
Graphix or a claim that the defect has already been fixed here.
