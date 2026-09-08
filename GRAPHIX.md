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

## 2026-09-06: Windows ARM64 process crash investigation

The first six-RID package workflow at commit
`7c52ac5efcdb741f87205be8750c3f20a4e48b02` built every native library. CTest
passed 25/25 on Windows x64, both Linux architectures and both macOS
architectures. On Windows ARM64, `testprocess` terminated with `SEGFAULT`
during `process_testStdinToStdout`; its other 24 CTest entries passed.
Re-running the failed job reproduced the crash without source changes.
The recorded seeds are `PYYDU0DMT75FOLTR` and `FV7817M2BX373BWP`.
Package assembly was blocked; no complete package was produced or published.

The `Graphix native process diagnostics` workflow builds the existing process
tests with MSVC AddressSanitizer and debug symbols on native x64 and ARM64
runners, then exercises both recorded seeds against an explicit source commit.
This permits separate RED and GREEN runs without changing test source in CI.
It uploads text logs only, does
not produce a runtime package and does not alter native implementation or test
source. MSVC 2026 is required for ARM64 AddressSanitizer support. This is an
instrumented diagnostic configuration, not the package recipe's compiler
configuration and not a replacement for its six-RID verification gate.

The uninstrumented local x64 comparisons with the first seed, normally and
with `--randmem`, passed. A subsequent local diagnostic changed only SDL's
allocator in a temporary copy of the process-test executable: reallocations
were filled with nonzero bytes and followed by a protected page. The original
test then failed at the same input/output phase. Its stack showed
`process_testStdinToStdout -> strstr`; the invalid read reached the guard page
after a 5120-byte allocation.

The dynamic stdout stream contains raw bytes without a NUL terminator. Its
unbounded marker search was therefore a test-fixture overread. Graphix changes
that search to `SDL_strnstr` bounded by the received byte count; the native
runtime and public API are unchanged. With the same guarded allocator, both
recorded seeds passed three times each, preserving the 1 MiB byte-for-byte
comparison and process-lifetime assertions. The local Release CTest suite
passed 25/25 in 57.15 seconds after this test correction.

Native ARM64 confirmation and the six-RID package gate remain pending. Local
syntax checks cover the four PowerShell steps. Actionlint 1.7.12's outdated
runner-label warning for `windows-11-vs2026-arm` is excluded specifically after
checking the label and installed ASan component against GitHub's official
runner image documentation; its other checks pass. The diagnostic workflow
has not yet run. These additions were prepared with AI assistance.

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

## 2026-09-06: Native Windows maximum-size correction

The process-test correction was confirmed under AddressSanitizer: both recorded
seeds failed on the original source and passed after the correction, on native
x64 and ARM64. Commit 64d5819b479751ba988f21b8a8b7a74a84a4dafd then passed all
six native CTest suites (25 tests each), and CI produced Graphix.Native
3.4.16-graphix.1. Cerneala now restores that verified baseline from an explicitly
approved local feed; no NuGet publication has occurred.

The new Windows regression drives WM_SYSCOMMAND/SC_MAXIMIZE instead of relying
on SDL_MaximizeWindow's separate programmatic clamp. Its deterministic matrix
covers bordered and borderless windows, either finite axis, both finite, both
unlimited and limits equal to the current client size. Six cases across two
styles repeat three times, and queries check that unlimited axes retain the
native tracking limits. Before the fix, 30 of 400 assertions failed.

WM_GETMINMAXINFO now preserves and applies the finite-limit flag separately
for each axis, including when subtracting the current size produces zero.
The first correction fixed bordered windows. The borderless comparison then
showed a constrained 400x300 outer window with a 1920x1020 client: the later
WM_NCCALCSIZE handler replaced its rectangle with the entire monitor work area.
That handler now intersects the proposed window rectangle with the work area
instead of expanding it. No public C API, ABI or unrelated backend changes
are required. The resulting matrix passed all 400 assertions. The local
Release CTest suite passed 25/25 in 55.09 seconds with the final source.

An exploratory extra assertion asked that even an unlimited axis of a bounded,
bordered window stay within the work-area dimensions. Native message tracing
showed Windows supplying the full-monitor maximize size before SDL changed it.
That assertion would impose an additional window-manager policy beyond the
independent maximum-size contract; it is not part of this regression or fix.
The temporary trace and ineffective ptMaxSize experiments were removed. The
unlimited axis remains owned by Windows; no arbitrary offsets were introduced.

The package workflow now runs this real Windows-driver regression on both
Windows architectures before uploading a payload, in addition to the unchanged
dummy-driver CTest suite. Local actionlint and four PowerShell block syntax
checks pass. Native ARM64 verification of this window fix and a new immutable
package version remain pending.

Cerneala's isolated run with the corrected Windows DLL passes the original two
maximum-size cases. Its broader gates are not green: an ownership/input test
intermittently reports pointer -1 instead of 45, an allocation test failed in
the full suite but passed focused, and a multisampled text/stroke rendering
comparison differs by 47/255 with Graphix 3.4.16 while passing with SDL 3.4.14.
These findings are being investigated separately, not attributed to this
window fix or waived. These Graphix changes were prepared with AI assistance.

## 2026-09-07: public NuGet distribution preparation

Prepared the first public NuGet release as `Graphix.Native 3.4.16-graphix.3`,
with the separate managed binding `Graphix-CS 3.4.16.1`. The entry-point READMEs
now describe direct NuGet.org installation instead of requiring temporary
Actions artifacts. The package workflow remains build/test-only; publication
is a separate, explicitly authorized operation on the exact verified package.

This release preparation changes documentation and packaging checks, not the
native implementation, headers or tests from `0c23f43af6884849165ebf21ba1d14fa2d6cdf51`.
The old package versions are not overwritten. Native builds are
repeated because runtime provenance records the new package version and the
release source commit.

A permanent documentation check rejected the previous README for lacking the
public package URL and pinned installation command, then passed with the new
documentation. It runs before each CI native build and during direct package
assembly. Six matching-RID builds, all six CTest suites and both real Windows
maximum-size regression runs remain mandatory before publication. This entry
records release preparation, not a completed publication or new runtime test
results. These changes were prepared with AI assistance.

## 2026-09-07: D3D12 descriptor heap capacity and binding lifetime

The new native `testgpu_d3d12_descriptors` regression reproduced two violations
on the pre-fix native source at `0c23f43af6884849165ebf21ba1d14fa2d6cdf51`:

- Three fragment samplers, with an actual texture binding changed on every
  draw: 682 draws passed with the expected pixel; draw 683 attempted to copy
  descriptor entries 2046 through 2048 into a 2048-entry sampler heap.
  D3D12 validation reported error 646 (`CopyDescriptorsSimple`, invalid
  destination descriptor handle), and the process exited with code 2173.
  The corresponding compute workload failed at dispatch 683 as well.
- Replacing a full heap left unchanged descriptor tables pointing into the
  previous heap. D3D12 reported error 554 at graphics draw 2048 when a vertex
  sampler stayed bound, and at compute dispatch 2049 when the output binding
  stayed bound. A three-storage-buffer graphics workload also overflowed the
  65536-entry view heap at draw 21846; its compute counterpart retained an
  invalid output table at dispatch 21846.

The fix reserves space for all pending descriptor tables before binding any
table for a draw or dispatch. Heap replacement marks graphics and compute
descriptor tables dirty, including unchanged resources. Compute read-write
tables are now bound at dispatch alongside the other resources, using the
pipeline's declared resource counts. Heap sizes and in-flight resource
lifetimes are unchanged. There is no public C API or header change.

The permanent C test uses public SDL GPU operations, in-memory DXBC shader
compilation with the Windows SDK compiler, native D3D12 validation, and GPU
readback. Its seven scenarios cover sampler/view capacity, retained vertex
bindings, compute output buffers and compute output textures. Each scenario
runs three times with the same device/resources to exercise command-buffer
and heap reuse. Compute dispatches write disjoint output elements, avoiding
unsynchronized overlapping writes. Missing GPU/debug-layer prerequisites
fail the test; they do not count as a pass.

Local verification: Windows x64, NVIDIA GeForce RTX 2060, driver
32.0.15.9159, MSVC 19.51, shared SDL with static CRT:

- All seven final scenarios fail on the preserved pre-fix DLL with the
  corresponding descriptor validation errors. The 682-draw control passes.
- Release build with warnings as errors passed. Full CTest with
  `SDL_TESTS_QUICK=1` and the native GPU test enabled: 26/26 passed, 63.03 s.
- The seven-scenario, three-iteration GPU matrix passed in both Release and
  Debug; the focused Debug CTest run took 5.75 s.
- The original 682- and 683-draw boundary runs passed three times each after
  the fix, with expected pixels and no D3D12 validation errors.
- The complete Render automation suite, with `SDL_RENDER_DRIVER=gpu` and
  `SDL_GPU_DRIVER=direct3d12`, passed 19/19 with seed `GRAPHIXD3D12DESCR`.
- The native Windows maximum-size regression still passed all 400 assertions.
- DLL export comparison: the same 1271 exported names. Public headers and
  dynamic API declarations are unchanged. Git whitespace checks passed.

A diagnostic recording comparison also passed on both DLLs: 600 operations
per scenario, 20 iterations, discarding the first two timing samples. Timings
include the debug layer and message inspection and are not production frame
cost or GPU-time benchmarks; no performance improvement is claimed.

Logs, binary/source hashes and preserved baseline artifacts are under the
local ignored directory `out/evidence/d3d12-descriptors/`. These are local
verification artifacts, not a published runtime package. Native ARM64,
other GPUs, other D3D12 platforms and downstream Cerneala conformance have
not been verified for this change. No cross-platform certification or human
manual validation is claimed. These changes were prepared with AI assistance.

### Running the native descriptor regression

The executable is built with the Windows D3D12 test targets. CTest registration
is opt-in with `SDLTEST_D3D12=ON`, because ordinary headless test hosts need not
have a D3D12 device or the Windows Graphics Tools debug layer. The existing
package workflow has not been changed to require GPU-equipped runners.

From a shell with CMake and the Windows C/C++ toolchain available:

```powershell
cmake -S . -B out/build/d3d12-descriptors -DSDL_TESTS=ON -DSDL_SHARED=ON -DSDL_STATIC=OFF -DSDLTEST_D3D12=ON -DSDL_WERROR=ON
cmake --build out/build/d3d12-descriptors --config Release --parallel 8
ctest --test-dir out/build/d3d12-descriptors -C Release -R '^testgpu_d3d12_descriptors$' --output-on-failure --no-tests=error
```

The executable also accepts `--case NAME`, `--draws N` and `--iterations N`.
For a direct run, put the build's `Release` directory on `PATH` so the test
loads that build's SDL3 DLL. The original sampler boundary is:

```powershell
./out/build/d3d12-descriptors/test/Release/testgpu_d3d12_descriptors.exe --case graphics-samplers --draws 683
```

## 2026-09-07: GPU renderer texture storage, cleanup and plane properties

Three additional defects were reproduced through public SDL APIs before any
production changes. The permanent `testgpurender_texture_contracts` regression
was then confirmed RED against the preserved pre-fix DLL:

- P010 streaming textures with odd widths allocated too little chroma storage.
  A 3x16 texture reported pitch 6 and allocated 144 bytes, while upload required
  160. The original protected-memory diagnostic detected a read at the end of
  that allocation during unlock. The permanent test checks the actual requested
  allocation size before writing or uploading, so RED does not require an
  invalid memory access. Five odd-sized cases fail; the even-width control and
  the corresponding NV12, NV21 and RGBA32 cases pass.
- Failure of the 32092-byte pixel allocation for a 113x71 RGBA32 streaming
  texture caused the backend structure to be freed twice. The native test
  injects exactly one allocation failure and temporarily defers reclamation
  to detect repeated frees deterministically. Creation without injection
  succeeds; creation with injection returns NULL but repeats a free before
  the fix.
- The exposed V-plane property returned the U-plane texture. Both IYUV and
  YV12 fail, with both renderer-owned planes and distinct external planes
  wrapped through texture creation properties.

The fixes are confined to `src/render/gpu/SDL_render_gpu.c`: round chroma width
in pixels before converting it to bytes, leave failure cleanup to the existing
`SDL_DestroyTexture` owner, and publish `textureV` for the V-plane property.
The public pitch, API and resource ownership contracts are unchanged. The
earlier D3D12 descriptor fix is unchanged.

The permanent regression runs 24 streaming format/size combinations, the
allocation-failure case with its control, and four plane-identity cases. It
repeats the matrix three times on the same device and renderer. After checking
storage bounds it initializes the locked pixels, unlocks and submits through
the renderer, then verifies every uploaded plane byte using GPU readback.
Missing devices or other setup failures fail the executable; they are not
counted as successful or skipped tests. No production test hooks were added.

Local verification: Windows x64, NVIDIA RTX 2060, MSVC 19.51, shared SDL with
static CRT and warnings as errors:

- Final permanent test against the preserved pre-fix DLL, on both D3D12 and
  Vulkan: 30 contract assertion failures and 117 passing assertions per run.
- Fixed Release and Debug DLLs, on both D3D12 and Vulkan: 162/162 assertions
  passed per run, including the original 3x16 P010 dimensions.
- Full Release build passed. Final CTest with `SDL_TESTS_QUICK=1` and both
  opt-in GPU tests enabled: 27/27 passed in 67.86 seconds.
- Focused Debug CTest for the renderer and descriptor regressions: 2/2 passed.
- Full native Render automation suite with seed `GRAPHIXGPUTEXTURE`: 19/19
  passed on D3D12 and 19/19 on Vulkan. These runs did not use quick mode.
- The native Windows maximum-size regression still passed 400/400 assertions.
- All 1271 DLL export names match the pre-fix DLL, including `JNI_OnLoad`.
  Public headers and dynamic API declarations are unchanged; whitespace
  checks passed.

The test executable is portable SDL C code. CTest registration is opt-in with
`SDLTEST_GPU_RENDERER=ON`, so ordinary headless package jobs do not acquire a
new GPU requirement. It uses the real platform video driver, rather than the
ordinary suite's dummy driver. From a configured native build:

```powershell
cmake -S . -B out/build/d3d12-descriptors -DSDL_TESTS=ON -DSDLTEST_GPU_RENDERER=ON
cmake --build out/build/d3d12-descriptors --config Release --parallel 8
ctest --test-dir out/build/d3d12-descriptors -C Release -R '^testgpurender_texture_contracts$' --output-on-failure --no-tests=error
```

For direct runs, put the matching build's DLL directory on `PATH`. The executable
accepts `--driver direct3d12` or `--driver vulkan`, `--case streaming`,
`--case allocation-failure`, `--case properties`, and `--iterations 1..100`.

Logs, baseline artifacts and source/binary hashes are retained locally under
`out/evidence/gpu-renderer-fixes/`; the earlier diagnostic findings remain under
`out/evidence/gpu-renderer-audit/`. No runtime package was assembled or published
for these changes. ARM64, non-Windows platforms, other GPUs, Metal and downstream
Cerneala conformance remain unverified. No production performance benchmark or
human manual validation is claimed. These changes were prepared with AI
assistance.

## 2026-09-07: RED gate for process argument escaping (Graphix #2)

Added `process_testArgumentsBackslashQuote` in `test/testprocess.c` for the
first case in [Graphix #2](https://github.com/Chevalier12/Graphix/issues/2)
([SDL #16217](https://github.com/libsdl-org/SDL/issues/16217)). It launches the
existing childprocess executable through SDL_CreateProcess, with zero, one
and two literal backslashes before a double quote, followed by a separate
`baz` argument. The first two cases are controls. Exact output length and
bytes verify both argument contents and boundaries; successful launch, read
and child exit are checked separately.

On Windows x64, the two-backslash case loses the quote and merges the two
arguments. Expected and actual child stdout, with literal backslashes:

```text
Expected:
|0=foo\\"bar|
|1=baz|

Actual:
|0=foo\\bar baz|
```

The lines end in CRLF: 24 expected bytes versus 18 actual bytes. Launching
the same unchanged child with .NET ProcessStartInfo.ArgumentList (no shell)
preserves all 24 bytes. This control distinguishes the SDL launch path from
a broken argument-printing fixture. The Windows argument joiner currently
escapes only the final backslash of a run before a quote; the
[Microsoft C runtime rules](https://learn.microsoft.com/en-us/cpp/c-language/parsing-c-command-line-arguments)
interpret the complete run.

Evidence on source commit `7078ad0d1891810b624da8ad18f271a60648c626`, with
only this test added, using MSVC 19.51, Release shared SDL, static CRT and
warnings as errors:

- Existing process CTest passed before adding the regression.
- The focused regression failed identically in three iterations with seed
  `GRAPHIXISSUE0002`: 11 passing assertions and one failing assertion per
  iteration; executable exit code 1.
- Full Release build passed. Full CTest with SDL_TESTS_QUICK=1 and both
  existing opt-in GPU tests enabled: 26/27 passed in 63.25 seconds.
  Only testprocess failed, solely in the new regression; its other 15
  cases passed, with no skips. CTest returned 8.
- Production DLL and childprocess hashes stayed identical before and after
  adding the test. No production source, helper executable source or API
  was modified.

From the existing configured build, with CMake/CTest on PATH:

```powershell
cmake --build out/build/d3d12-descriptors --config Release --target testprocess --parallel 8
ctest --test-dir out/build/d3d12-descriptors -C Release -R '^testprocess$' --output-on-failure --no-tests=error
```

The new case is enabled in the existing process suite: no expected-failure
inversion or CI bypass was added. Direct focused runs use
`--filter process_testArgumentsBackslashQuote --seed GRAPHIXISSUE0002 --iterations 3`;
put the matching DLL directory on PATH and pass the matching childprocess
path as the positional argument.

Logs, JUnit results, the independent control and source/binary provenance
are retained locally under `out/evidence/process-arguments/`.
This is deliberately a RED-only change. It does not reproduce the other
seven reported cases, demonstrate command injection, or verify ARM64,
other operating systems or human interaction. No fix, package, commit or
GitHub issue update was performed. These additions were prepared with AI
assistance.

### Expanded issue investigation (historical, before quote-policy approval)

The maintainer subsequently requested all eight points and approved rejecting
percent, exclamation mark, CR and LF in batch/cmd argument lists, and trailing
spaces/dots in executable paths, while preserving the explicit raw command-line
path. Four further permanent process tests now reproduce the batch filename,
batch argument, executable selection, shell rejection and direct cmd cases.
Fixtures use private directories, copies of the benign childprocess helper,
launch-marker files and harmless echo controls; cleanup assertions pass.

All five focused tests are RED on the unchanged production implementation.
The raw command-line control passes. A first correction fixed the native
argument, executable boundary and rejection tests, but failed quote-containing
shell arguments. An independent native probe established that doubled quotes
are interpreted differently by the CRT and CommandLineToArgvW (used by SDL).
Caret escaping worked through a single batch forwarding step, but forwarding
through a second batch caused the benign echo control to execute instead of
remaining argument data. This is not a safe general replacement.

The candidate production change was discarded and the original implementation
rebuilt. The expanded tests remain, with evidence and the discarded patch under
`out/evidence/process-arguments/full-issue/`. Adding literal double quotes to the
batch/cmd rejection policy requires a further maintainer decision. No completed
fix or full-suite GREEN is claimed, and Graphix issue 2 remains open.

### Correction after strict-policy approval

The maintainer subsequently approved rejecting literal double quotes in the
batch/cmd argument-list path as well. The Windows argument builder now handles
complete backslash runs, protects the executable boundary, quotes batch paths,
and validates the approved shell restrictions before process creation. The
explicit raw command-line path is unchanged. This correction does not represent
a published Graphix release or an upstream SDL fix.

The permanent regression matrix covers native arguments, simple/spaced/mixed-case
batch paths, nested batch forwarding, executable selection, synchronous shell
rejection, direct cmd invocations and the original BatBadBut payload. The same
tests were RED against the retained original DLL before the production change.
All six focused cases subsequently passed three iterations each with seed
`GRAPHIXISSUE0002`.

Windows x64 verification:

- The complete Release CTest suite passed 27/27, including both enabled GPU tests
  (final code/test matrix: 70.53 seconds; process suite: 7.33 seconds).
- The Debug process suite passed 20/20 with `--trackmem --randmem` (10.6 seconds).
  Its old 10-second CTest limit independently timed out despite passing direct
  execution. The expanded process suite now has a 30-second timeout; Debug CTest
  passed in 10.91 seconds afterward. No assertion or test was disabled.
- The original and corrected Release DLLs export the same 1,270 SDL symbol names;
  public declarations were not changed. This does not establish behavioral
  compatibility: the approved strict shell policy is intentionally restrictive.
- The allocation tracker reports no remaining tracked allocations, but this
  build disables free validation and reports unknown frees. The retained original
  DLL also reports unknown frees. These runs are not comprehensive memory-safety
  verification or a zero-allocation claim.
- Additional cmd option/boundary cases passed 230/230 assertions in each of three
  iterations; the matching test executable failed 99 assertions against the
  retained original DLL. Combined switches and missing commands are rejected;
  separate uppercase switches preserve the literal metacharacter control.

Logs, retained RED binaries and reproduction evidence are under
`out/evidence/process-arguments/full-issue/`. ARM64, other operating systems,
ASan and human interaction have not been validated for this correction.
The Windows restrictions and raw command-line responsibility are documented in
`include/SDL3/SDL_process.h`, following this repository's header/wiki rules in
`docs/README-documentation-rules.md`. Header/wiki/header conversion preserved the
policy and public declaration tokens. The local Cygwin Perl misparsed CRLF
headers; a CRLF/LF control reproduced this, and the successful export used an
LF-normalized staging copy, without modifying the script or publishing to SDL's
wiki. All 1,270 exported SDL names and ordinals remain unchanged.
No unrelated documentation infrastructure is required. These verification results
were recorded before publication; commit and issue-closure references belong to
the Graphix issue history. No package release was performed.

## 2026-09-08: graphix.4 release preparation

Prepared `Graphix.Native 3.4.16-graphix.4` from the native implementation at
`f3c691b233bb0d5fc56e1646d8e0d64dc0a1fc07`. Compared with the published
graphix.3 source, this includes the D3D12 descriptor heap and GPU renderer
texture corrections, plus the approved Windows process argument and shell
validation changes documented above. The stricter Windows shell argument
policy is an intentional behavioral compatibility change; the raw command-line
path remains caller-owned. The separate `Graphix-CS 3.4.16.1` binding is unchanged.

Updated the entry-point installation/build commands and the workflow's default
package version. Native sources, headers, tests and package contents are not
changed by this release-preparation step. Existing package versions will not
be overwritten. Runtime provenance will identify the committed release source.

The release documentation gate was confirmed RED against the previous READMEs
for the new version. Six matching-RID builds, their CTest suites, both native
Windows maximum-size runs, package provenance/hash verification and downstream
Cerneala verification remain pending. Publication is authorized but has not
occurred. No NVIDIA alpha-occlusion fix or human validation is claimed.
These release changes were prepared with AI assistance.
