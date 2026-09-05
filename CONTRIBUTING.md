# Contributing to Graphix

Graphix is an independent, modified SDL fork. Contributions here target Graphix,
not the upstream SDL project. This document replaces upstream contribution
instructions for work submitted to this fork.

## Authorship and AI assistance

AI-assisted contributions are permitted and must disclose that assistance.
Contributors remain responsible for the change, its provenance and the rights
needed to distribute it under the zlib license. Disclosure is not proof of
correctness or a substitute for review. Do not claim human authorship, review
or testing that did not happen.

SDL's upstream contribution policy is separate. Do not send it prohibited
AI-generated code or comments or conceal the use of AI. No upstream submission
is implied by contributing to Graphix.

## Required evidence

1. Describe the observed failure, expected contract, environment and exact
   reproduction. Distinguish a demonstrated cause from a hypothesis.
2. Add a focused regression test and confirm it fails for the intended reason
   before changing the production implementation.
3. Fix the invariant's owner without unrelated cleanup or symptom-hiding
   clamps, retries or alternate execution paths.
4. Rerun the reproduction, affected tests and applicable SDL testautomation and
   platform build gates. Compare failures against the unmodified upstream base.
5. Report exact commands and results, including skipped tests, missing tools,
   unverified platforms and any required human validation.

For documentation-only changes, verify links, provenance, license preservation
and the diff; state that no native code changed rather than claiming a native
build or test run.

Preserve existing copyright/license notices and mark altered source versions.
Follow the existing local code style and avoid whole-file reformatting.
The SDL C API, ABI and native library names remain unchanged unless a breaking
change is explicitly approved by the Graphix maintainer.

## Submitting changes

Open Graphix issues and pull requests in
[Chevalier12/Graphix](https://github.com/Chevalier12/Graphix), against the `graphix`
branch. Describe the scope, AI assistance, provenance and verification performed.
Do not assert that CI ran merely because upstream workflow files are present.
