# Session notes

One folder per session: `docs/sessions/<slug>/README.md`. That is the whole convention.

Copy [`_TEMPLATE.md`](_TEMPLATE.md) into a new folder named for the session's slug and fill in the
top half before you start. The bullets wait until you have finished.

```bash
mkdir -p docs/sessions/quadrature
cp docs/sessions/_TEMPLATE.md docs/sessions/quadrature/README.md
```

## The part that matters is written afterwards

Every session opens with a **You will be able to** line, written months before you got there. The gap
between that prediction and what actually happened is the value of this folder, and it is the first
thing to evaporate. Three to five bullets, after the session, in your own words.

## The voice rule

Notes, not an essay. Fragments are fine, bullets are fine, half-sentences are fine.

**No em dashes and no ellipses.** This matches the site's voice rule and applies to anything you
write that might be published. It does not apply to the guide documents in
[`../guides/`](../guides/), which keep theirs.

Write "the D term buzzed until I filtered it" rather than "the derivative term exhibited significant
high-frequency noise which was subsequently mitigated".

## Slugs

Named for the work, not the session number: `quadrature`, not `s3`. These become permanent URL
segments on the site, and the session ID appears in the README's header instead.

Three places use the same string and must agree: this folder name, the `key` in the website's step
list, and the line in the capture tracker.

## What is not in here

Numbers live in [`../tuning/`](../tuning/) and [`../motor-spec.md`](../motor-spec.md), decisions in
`../decisions/`, the maths in [`../derivations/`](../derivations/). Link to them rather than copying.
Media does not live in this repository at all.
