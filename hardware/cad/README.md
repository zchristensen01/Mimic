# CAD

Source files and neutral exports for every printed and machined part. Empty until Stage 2: nothing in
Stages 0 or 1 is printed.

Commit the native file (`.FCStd`, `.f3d`, or the Onshape link) **and** the STEP export. The native
file is hostage to whatever package made it; in five years the STEP is the one that still opens.
Commit the STL too, so a part can be reprinted without opening CAD.

Not here: slicer projects and G-code (machine-specific and regenerable), downloaded models you did
not make (link them in [`../bom.md`](../bom.md) with their licence), and photographs.

## Naming

```
<part-name>-v<n>.FCStd
<part-name>-v<n>.step
<part-name>-v<n>.stl
```

Version in the filename, not only in git: you will have three revisions of a link on the bench at
once and the physical part cannot be `git log`ged.

## Storage

`.step`, `.stl`, `.f3d`, `.FCStd` and `.3mf` are tracked with Git LFS, see
[`.gitattributes`](../../.gitattributes). Run `git lfs install` once on each machine you clone to.

## Before the first part

Two things to settle: which package, and your machine's measured print tolerances. Do one CAD
tutorial before you need one, because "learn CAD" and "design a link" are two problems.
