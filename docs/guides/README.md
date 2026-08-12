# The document set

The eight documents Mimic is built from, committed alongside the work they describe.

They are **source material, not working files.** Read them, follow them, and leave them exactly as
they arrived — reflowing or lightly editing one makes every future diff against it unreadable, and
the *Order Manifest* in particular is a dated historical record that is never edited at all. If one
of them turns out to be wrong, the correction belongs in an ADR or in the file the error affects,
not in the document.

---

## What each one is for

| Document | Answers | When you read it |
|---|---|---|
| [Before You Build](Mimic_Before_You_Build.md) — *Appendix Zero* | *What am I looking at?* | Once at the start, then as a dictionary |
| [Project Guide](Mimic_Project_Guide.md) — *Vol II* | *Why this project, and what is each stage for?* | Once through, then whenever motivation dips |
| [Stage 0 Workbook](Mimic_Stage0_Workbook.md) — *Vol III* | *What do I do tonight?* | Open on the bench, every session |
| [Stage 1 Workbook](Mimic_Stage1_Workbook.md) — *Vol IV* | Same, for Stage 1 | Open on the bench, every session |
| [Stage 2 Workbook](Mimic_Stage2_Workbook.md) — *Vol V* | Same, for Stage 2 | Open on the bench, every session |
| [Stages 3–5 Workbook](Mimic_Stages3-5_Workbook.md) — *Vol VI* | Same, for Stages 3, 4 and 5 | Open on the bench, every session |
| [What's Left to Buy](Mimic_Still_To_Buy.md) | *What do I still need?* | Before each stage's order |
| [Order Manifest](Mimic_Order_Manifest.md) | *What did I already buy?* | Historical record. **Never edit it** |

The division of labour is worth internalising: **the guides explain, the workbooks instruct.**
Anything that tells you what to do on a given evening — session order, the arithmetic with your
actual parts, code skeletons, and the test that closes each session — lives in a workbook. Anything
that explains why lives in *Before You Build* or the *Project Guide*.

---

## Reading order

**1. [Before You Build](Mimic_Before_You_Build.md), Part I — in one sitting, before you order
anything.** It is the longest part of that document on purpose. Every other document in the set
assumes the vocabulary and the architecture Part I explains, and reading them without it is the
difference between following instructions and understanding what you are doing. You will not retain
all of it and you are not meant to — the vocabulary, connection map, hardware and software chapters
are reference you flip back to for the next year.

**2. [Before You Build](Mimic_Before_You_Build.md), Parts II–V — the actions.** The repository, the
Windows-side installs, the prerequisite audit, and the twenty minutes on reading a datasheet, which
is the one piece of genuinely new material in the audit list.

**3. [The Project Guide](Mimic_Project_Guide.md) — once through.** Where each stage sits in the arc
and what you own at the end of it. It deliberately does not tell you what to do on Tuesday.

**4. [The Stage 0 Workbook](Mimic_Stage0_Workbook.md) — on the bench, one session at a time.** This
is Tuesday.

**5. [What's Left to Buy](Mimic_Still_To_Buy.md) — before each order**, not before the project.

Then the next workbook, at the next gate. Nothing before its stage.

---

## Two rules the documents set about themselves

> **Do not read ahead more than one session.** The failures in each session are load-bearing; knowing
> the answer before you have felt the problem is how you end up with a working rig you cannot debug.
> This is not a motivational point — it is the mechanism by which Stage 1 becomes possible.

> **Reading a ROS 2 tutorial during Stage 0 is a pleasant way to avoid doing Stage 0.** It feels like
> progress, it is genuinely interesting, and it produces nothing. Installing Jazzy is setup; working
> through its tutorials before Stage 0 is finished is procrastination wearing a lab coat.

---

## Cross-reference conventions inside the set

- **Milestones** are `M<stage>.<n>` — `M0.6`, `M1.6`, `M2.6` are three different pieces of work. The
  Project Guide numbers by milestone; the workbooks number by **session** (`S0`–`S12` in Stage 0,
  `S1.0`–`S1.9` in Stage 1). The Stage 0 Workbook's *Appendix: the milestone map* is the translation
  between the two.
- **Figures** carry their volume: `III.S9.1` is Volume III, session S9, figure 1. Without the prefix
  Stage 0's `S2.1` and Stage 2's session `S2.1` collide.
- **The canonical glossary** for the whole set is *Before You Build* → "The Vocabulary". Where a
  workbook defines a term at the point you first need it, that definition is a convenience and the
  glossary is the complete list.

---

## Callout boxes, and what each one obliges

| Box | What it means |
|---|---|
| **GO TO THE WORKBOOK** | The explanation is finished and the work begins |
| **PORTFOLIO MOMENT** | Stop and produce something — a photographed derivation, a plotted result, a written decision |
| **WATCH OUT** | A specific, known failure. Read it before the step, not after |
| **CHECK YOURSELF** | Answer it before reading on. Committing to a wrong answer first is the point |
| **LOOK THIS UP** | A number a manufacturer publishes. You are told which document and which table, never the answer |
| **DEFINITION** | A term the rest of the set will use without re-explaining |
| **WHERE THIS POINTS** | Why this matters beyond the session you are in |

---

## A note on the PDF export

Every figure in the set is ASCII/box-drawing art inside a fenced code block, tagged
`FIGURE <id> — <title>` on its first line — deliberately, so the figures render in any Markdown
viewer and stay diffable in Git. If you export to PDF, set the monospace font to one with full
box-drawing and half-block coverage: **DejaVu Sans Mono** is the usual answer. The core PDF
monospace fonts do not carry the characters these figures use and will drop or substitute them.
