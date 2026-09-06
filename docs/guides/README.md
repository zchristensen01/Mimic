# Start here

The nine documents Mimic is built from, committed alongside the work they describe.

They are **source material, not working files.** Read them, follow them, and leave them exactly as
they arrived — reflowing or lightly editing one makes every future diff against it unreadable, and
the *Order Manifest* in particular is a dated historical record that is never edited at all. If one
of them turns out to be wrong, the correction belongs in an ADR or in the file the error affects,
not in the document.

---

## If you read nothing else on this page

**Four documents matter this month. The other five wait.**

1. **[Before You Build](Mimic_Before_You_Build.md), Part I** — what you are looking at. One sitting.
2. **[The Glossary](Mimic_Glossary.md), "Before anything"** — eighteen terms. Twenty minutes.
3. **[Before You Build](Mimic_Before_You_Build.md), Parts II–V** — set the machine and repository up.
4. **[The Stage 0 Workbook](Mimic_Stage0_Workbook.md)** — one session per evening, starting at S0.

Everything else is opened when a session tells you to open it. **You are never expected to hold this
set in your head.** Each session names what it needs.

---

## What each one is for

| Document | Answers | When you read it |
|---|---|---|
| [Before You Build](Mimic_Before_You_Build.md) — *Appendix Zero* | *What am I looking at, and how do I set it up?* | Once at the start |
| [Glossary](Mimic_Glossary.md) — *Appendix Zero-A* | *What does that word mean?* | One block per session, on demand |
| [Project Guide](Mimic_Project_Guide.md) — *Vol II* | *Why this project, and what is each stage for?* | Once through, then whenever motivation dips |
| [Stage 0 Workbook](Mimic_Stage0_Workbook.md) — *Vol III* | *What do I do tonight?* | Open on the bench, every session |
| [Stage 1 Workbook](Mimic_Stage1_Workbook.md) — *Vol IV* | Same, for Stage 1 | Open on the bench, every session |
| [Stage 2 Workbook](Mimic_Stage2_Workbook.md) — *Vol V* | Same, for Stage 2 | Open on the bench, every session |
| [Stages 3–5 Workbook](Mimic_Stages3-5_Workbook.md) — *Vol VI* | Same, for Stages 3, 4 and 5 | Open on the bench, every session |
| [What's Left to Buy](Mimic_Still_To_Buy.md) | *What do I still need?* | Before each stage's order |
| [Order Manifest](Mimic_Order_Manifest.md) | *What did I already buy?* | Historical record. **Never edit it** |

The division of labour is worth internalising:

> **The Glossary defines. *Before You Build* orients and sets up. The Project Guide explains why.
> The workbooks tell you what to do tonight.**

Anything that tells you what to do on a given evening — session order, the arithmetic with your
actual parts, code skeletons, and the test that closes each session — lives in a workbook. Anything
that explains why lives in *Before You Build* or the *Project Guide*. Anything that is a single term
lives in the Glossary.

---

## The order, concretely

### Evening one — orientation, no parts needed

| Read | Where | Roughly |
|---|---|---|
| Part I | [Before You Build](Mimic_Before_You_Build.md) | 1–2 hours |
| *Before anything* — 18 terms | [Glossary](Mimic_Glossary.md#before-anything--the-words-the-rest-of-the-set-assumes) | 20 min |

Part I is the longest part of that document on purpose. Every other document assumes the architecture
it explains. **You will not retain all of it and you are not meant to** — it is reference you flip
back to for the next year.

### Evening two — the machine and the repository

| Read and do | Where |
|---|---|
| Parts II–V: the machine, the repository, installing, the prerequisite audit | [Before You Build](Mimic_Before_You_Build.md) |
| *Before S0* — 13 terms, as you meet them | [Glossary](Mimic_Glossary.md#before-s0--bench-toolchain-and-the-repository) |

### Evening three — the map

| Read | Where |
|---|---|
| Once through, cover to cover | [The Project Guide](Mimic_Project_Guide.md) |

Where each stage sits in the arc and what you own at the end of it. It deliberately does not tell you
what to do on Tuesday. **Read the Stage 0 chapter and its Interludes properly**; skim Stages 3–5,
which are months away and will make more sense later.

### Every evening after that — the session loop

**This is the whole project, repeated about fifty times.** Every session in every workbook has the
same six steps.

1. Open the workbook at the next session. Read its **Before you start** box.
2. Read the Glossary block it names. Usually one to nine terms; never more than thirteen.
3. Read anything else that box lists — usually one Project Guide interlude, sometimes nothing.
4. Work the session: *Concept → the math → build → code → prove it*.
5. **Photograph the thing that went wrong, before you fix it.**
6. Write the session README, commit, tick the tracker.

**Every session in all four workbooks has a *Before you start* box** — thirteen in Stage 0, ten in
Stage 1, fifteen in Stage 2, and one per milestone in Stages 3–5. You should never have to work out
what to read first; if you do, that is a bug in the workbook, and the fix belongs in your session
README.

> **Do not read ahead more than one session.** The failures in each session are load-bearing; knowing
> the answer before you have felt the problem is how you end up with a working rig you cannot debug.
> This is not a motivational point — it is the mechanism by which Stage 1 becomes possible.

> **Reading a ROS 2 tutorial during Stage 0 is a pleasant way to avoid doing Stage 0.** It feels like
> progress, it is genuinely interesting, and it produces nothing. Installing Jazzy is setup; working
> through its tutorials before Stage 0 is finished is procrastination wearing a lab coat.

---

## What the activities mean

Sessions ask you to do more than read and type. Each of these means something specific, and each one
appears in a session because that session is where it first earns its place.

| When a session says | It means | Why it is there |
|---|---|---|
| **Before you start** | Read the listed blocks first. Ten to twenty minutes | The session uses those ideas without stopping to explain them |
| **The math** | Derive it on paper, in your handwriting | A number you derived is a number you can defend |
| **Draw this** | Sketch by hand, photograph the page | Drawing a topology finds errors that reading it does not |
| **Look it up yourself** | Open the manufacturer's PDF and find the table | A number you were handed is a number you cannot defend |
| **Build** | Wiring, mounting, physical work | — |
| **Code** | Fill in the skeleton. The bodies are yours | The stubs are scaffolding; the thinking is not |
| **Prove it** | Run the test that closes the session | A session is not over because you are tired |
| **Capture the broken state** | Photograph or screenshot the failure *before* fixing it | It exists for about four minutes and cannot be recreated |
| **Artifacts** | What lands in the repo, and what goes to the site | The repository is the deliverable |
| **PORTFOLIO MOMENT** | Stop and produce something publishable | — |

**Instruments, and the session each one first arrives in:**

| Instrument | First needed | For |
|---|---|---|
| **Multimeter** | S1 | Winding resistance, identifying the six wires, continuity |
| **Precision screwdriver** (~2 mm) | S2 | Setting the buck converters' multi-turn trim pots |
| **Soldering iron** | S2 | The first soldering in the project |
| **Scope pin on D5** | S5 | Proving the loop rate on an instrument rather than by feel |
| **Logic analyzer** (PulseView) | S3 | Watching the two encoder channels for real |
| **Python, matplotlib, pandas** | S7 | Capturing a step response and plotting it |

---

## Callout boxes, and what each one obliges

| Box | What it means |
|---|---|
| **GO TO THE WORKBOOK** | The explanation is finished and the work begins |
| **PORTFOLIO MOMENT** | Stop and produce something — a photographed derivation, a plotted result, a written decision. Used in the two explaining documents; **in the workbooks the same instruction appears as the `Site:` line inside each session's *Artifacts*** |
| **WATCH OUT** | A specific, known failure. Read it before the step, not after |
| **CHECK YOURSELF** | Answer it before reading on. Committing to a wrong answer first is the point |
| **LOOK THIS UP** | A number a manufacturer publishes. You are told which document and which table, never the answer |
| **DEFINITION** | A term the rest of the set will use without re-explaining |
| **WHERE THIS POINTS** | Why this matters beyond the session you are in |

---

## Cross-reference conventions inside the set

- **Milestones** are `M<stage>.<n>` — `M0.6`, `M1.6`, `M2.6` are three different pieces of work. The
  Project Guide numbers by milestone; the workbooks number by **session** (`S0`–`S12` in Stage 0,
  `S1.0`–`S1.9` in Stage 1). The Stage 0 Workbook's *Appendix: the milestone map* is the translation
  between the two.
- **Figures** carry their volume: `III.S9.1` is Volume III, session S9, figure 1. Without the prefix
  Stage 0's `S2.1` and Stage 2's session `S2.1` collide.
- **The canonical glossary** for the whole set is [the Glossary](Mimic_Glossary.md), ordered by the
  session that first needs each term. Where a workbook defines a term at the point you first need it,
  that definition is a convenience and the Glossary is the complete list.

---

## A note on the PDF export

Every figure in the set is ASCII/box-drawing art inside a fenced code block, tagged
`FIGURE <id> — <title>` on its first line — deliberately, so the figures render in any Markdown
viewer and stay diffable in Git. If you export to PDF, set the monospace font to one with full
box-drawing and half-block coverage: **DejaVu Sans Mono** is the usual answer. The core PDF
monospace fonts do not carry the characters these figures use and will drop or substitute them.
