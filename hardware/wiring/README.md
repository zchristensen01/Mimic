# Wiring

A dated photograph of every wiring change. Hardware has no `git diff`.

Not primarily for the README. For yourself, three weeks later, when a joint stops working and you
need to know what changed.

Photograph the rig after every wiring change, not just the interesting ones, in good light: the whole
rig in frame, then a close-up of whatever moved. The hand-drawn power tree belongs here once it
exists; the scanned derivation of it goes in [`../../docs/derivations/`](../../docs/derivations/).

Photos for the site go straight to the website repository. This folder is a lab notebook and it is
allowed to be ugly.

## Naming

```
YYYY-MM-DD-<what-changed>.jpg
```

The date is the point. A photo you cannot date cannot answer "what changed between the run that
worked and the run that did not".

## Storage

Images here are tracked with Git LFS, see [`.gitattributes`](../../.gitattributes). Run
`git lfs install` once on each machine you clone to.
