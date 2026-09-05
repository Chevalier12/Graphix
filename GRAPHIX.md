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
