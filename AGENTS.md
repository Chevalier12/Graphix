# Graphix contributor instructions

This repository is Graphix, an independent fork of SDL maintained for Cerneala.
The maintainer has chosen an AI-assisted development workflow for this fork.
These instructions govern contributions to Graphix, not to upstream SDL.

- Follow CONTRIBUTING.md. Disclose AI assistance; do not claim generated work
  was exclusively human-authored or independently reviewed when it was not.
- Preserve LICENSE.txt and existing copyright/license notices. Identify Graphix
  modifications and preserve the exact upstream base and change provenance.
- Reproduce a defect before modifying production code. Add a regression test,
  confirm the intended failure, fix the owning invariant and rerun the test.
- Run affected tests and the applicable SDL automation/build gates. Report
  failing, skipped or unavailable gates accurately; compilation is not proof
  of correctness. Do not claim human validation without a human's result.
- Keep changes small and separate unrelated fixes. Preserve the SDL C API, ABI
  and library names unless the maintainer explicitly approves a breaking change.
- Respect upstream SDL's independent contribution policy. Do not submit
  AI-generated code or comments prohibited by that policy, conceal AI use, or
  open upstream issues/PRs without explicit maintainer authorization.

The original upstream AI policy remains available in the unmodified
release-3.4.16 tag and its git history; it is not Graphix's contribution policy.
