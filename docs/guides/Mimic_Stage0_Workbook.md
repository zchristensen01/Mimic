# Mimic — Stage 0 Workbook

**Volume III · The Single Joint, session by session**

Companion to the *Mimic Project Guide* (Volume II) and *Before You Build* (Appendix Zero).
Written against the parts on your bench in August 2026: **Arduino UNO**, **12GA-N20 12 V 100 RPM
encoder gearmotor**, **TB6612FNG**, **12 V 5 A supply**, **24 MHz 8-channel logic analyzer**.

---

## How this document differs from the Project Guide

The Project Guide is a map. It tells you where Stage 0 sits in the arc and what you will own at the
end. It deliberately does not tell you what to do on Tuesday.

This is Tuesday.

Thirteen sessions, `S0` through `S12`. Each one is two to four hours. Each one has the same shape:

| Part | What it is |
|---|---|
| **Goal** | One sentence. What is true *of the rig* at the end that was not true at the start. |
| **You will be able to** | One sentence. What is true *of you* at the end — something you can explain or prove that you could not before. The goal is the artifact; this is the education, and they are not the same thing. |
| **Concept** | The idea, with an analogy, before any hardware moves. |
| **The math** | Something you derive on paper. Not something you read. |
| **Look it up yourself** | A number this session needs that a manufacturer publishes. You are told which document and which table, never the answer. |
| **Draw this** | A diagram to sketch by hand and photograph. |
| **Build** | Wiring, pin assignments, what to physically do. |
| **Code** | Skeletons and signatures. You write the bodies. |
| **What will go wrong** | The specific failure, so you recognise it instead of doubting yourself. It ends by naming the one worth photographing. |
| **Prove it** | The test that closes the session. Usually preceded by a prediction you commit to first. |
| **Artifacts** | What goes in the repo, and what goes on the site. |

Two of those rows exist because you are working alone with nobody to tell you that you have
misunderstood. **"You will be able to" gives you something to check yourself against** at the end of an
evening that felt like it worked. **"Look it up yourself" exists because a number you were handed is a
number you cannot defend** — every manufacturer figure quoted in this workbook is one you can go and
verify, and the sessions that need one tell you where to look rather than what you will find. If you
skip those, the arithmetic still comes out; you just will not be able to answer "where did that come
from" in an interview, which is the entire point of the exercise.

*Before You Build*, Part V → "The skill nobody teaches: reading a datasheet" is the twenty minutes that
makes those sections quick rather than frustrating. Read it before S1.

> **WATCH OUT** — Do not read ahead more than one session. The failures in each session are load-bearing;
> knowing the answer before you have felt the problem is how you end up with a working rig you cannot
> debug. This is not a motivational point, it is the mechanism by which Stage 1 becomes possible.

---

## The standing rule: photograph the broken thing before you fix it

Every session below tells you exactly how it will go wrong. **When it does, capture it before you
fix it** — and each session's *What will go wrong* ends by naming the one worth having.

It costs seconds. A phone photo of a screen is enough. A screenshot is better. Neither needs to be
good, neither needs to be framed, and no part of this is a photography exercise.

**It is the only capture in this project that cannot be recreated.** The working rig is reproducible
forever — you can re-shoot a step response in eight months. The wrong trace exists for about four
minutes, and once you understand the bug you can no longer produce it convincingly. You will not
remember what the plot looked like; you will remember what you concluded, which is not the same
thing and is not evidence.

**And it is worth more than the working state, which is the part that sounds wrong.** Anyone can
show a thing that works. A page that shows the wrong trace, then the diagnosis, then the right trace
is a page about engineering. A page with only the right trace is a page about a tutorial being
followed, and the difference is visible from across a room.

So: the oscillation at `Ku` is not an embarrassment you clean up before publishing. It is the
session.

---

## The standing pin map

Fixed for the whole of Stage 0. Every session assumes it. Write it on masking tape and stick it to
the plank.

| Function | UNO pin | Why this pin and not another |
|---|---|---|
| Encoder channel A | **D2** | `INT0`. The UNO has exactly two external interrupt pins. |
| Encoder channel B | **D3** | `INT1`. The other one. Both channels must interrupt for ×4 decoding. |
| TB6612 `PWMA` | **D9** | Timer1. Can be reconfigured to 31 kHz in S11 without breaking `millis()`. |
| TB6612 `AIN1` | **D7** | Any plain digital pin. |
| TB6612 `AIN2` | **D8** | Any plain digital pin. |
| TB6612 `STBY` | **D4** | Must be driven HIGH or nothing happens. Do not tie it to 5 V — you want software control of it. |
| Loop-rate scope pin | **D5** | Toggled at the top of the control loop. This pin is your proof of timing. |
| Limit switch (S11) | **D6** | Input with `INPUT_PULLUP`. |

> **DEFINITION** — **Why D9 and not D5 or D3 for PWM.** The UNO has three hardware timers. Timer0 drives
> `millis()` and `micros()` and also PWM on D5/D6 — touch its prescaler and every timing function in
> your program silently changes. Timer2 drives PWM on D3/D11, and you need D3 for the encoder.
> That leaves Timer1, on D9/D10. This is not arbitrary; it is the only pin pair you can safely
> reconfigure, and S11 depends on it.

---

## What you are working toward

At the end of S12 you can hold a target angle, push the shaft with your finger, and watch it come
back. You can show a plotted step response and name its rise time, overshoot, settling time, and
steady-state error. You can say what your loop rate is and prove it on an instrument. And you have a
Git history that shows the gains changing, the oscillation appearing, and the clamp that fixed it.

That is the whole of Stage 0, and it is already enough to talk about in an interview.

---

# PART I — BEFORE THE MOTOR TURNS

---

## S0 · Bench, toolchain, and the repository

**Goal:** everything installed, everything labelled, an empty repository pushed to GitHub, and a
first commit that proves the whole chain works.

**You will be able to:** explain what each link in the toolchain does — editor, build system, uploader, driver, version control — and say which one is broken when the chain is.

### Concept

Nothing here is the project. This session exists so that when something breaks in S4, the list of
things that could be broken does not include "my editor" or "my driver" or "where did I put the
resistors."

### Build — the unpack

Label as you unpack. Twenty minutes now, or an afternoon in three weeks trying to tell an LM2596
from an MP1584 by sight. Both are blue, both are DC-DC buck converters, and they are not
interchangeable in your rig.

Into the 24-grid organiser, one bin each: LM2596 · MP1584 · XL4015 · UBEC · TB6612FNG · DRV8833 ·
AS5600 · INA219 · level shifters · CP2102 · microSD · limit switches · 100 nF caps · 1000 µF caps ·
120 Ω resistors · resistor kit · headers · screw terminals · barrel jacks.

Into the 10-grid: M3 screws by length. The Kalote kit's own tray is fine if you prefer.

> **WATCH OUT** — **Find a ~2 mm precision screwdriver now, and verify you actually have one.** The
> XL4015, LM2596 and MP1584 each set their output voltage with a multi-turn trim pot needing a 2 mm
> flat or Phillips driver, and nothing else in a general tool roll turns one. **It appears nowhere in
> the *Order Manifest*** — not under *Already owned*, not under *Deliberately deferred*, not in any
> line item — so do not assume it is on the bench because a document said so. If you do not have one,
> it is C$5–8, it is listed in Tier B of *What's Left to Buy*, and it has to arrive before S2. If you
> do, put it in the bin with the buck converters tonight; hunting for it mid-session is how a two-hour
> evening becomes three.
>
> Two more things you do not have, both worth deciding about rather than discovering:
>
> **No smoke stopper** — a current-limiting jig placed in series with a supply the first time you
> power something new, so a wiring mistake browns out instead of burning. You can proceed without
> one, but that makes the current-limit knob on the XL4015 your only first-power-up insurance —
> which is why S2 has you turn it fully down before anything is connected, and treats that step as
> load-bearing rather than optional.
>
> **No power switch.** Nothing in the 31 July order breaks the 12 V rail, and S8 and S10 both have
> you run experiments where being able to kill power in under a second matters. S2 fits one. Read
> that section before you wire anything.

### Build — the software

Install in this order. Everything is free.

**On Windows:**

| Software | Notes |
|---|---|
| **Git for Windows** | Set `user.name`, `user.email`, and `core.autocrlf = input`. |
| **VS Code** | Plus the **PlatformIO IDE** extension and the **WSL** extension. |
| **Python 3.12+** | Tick *Add to PATH*. Then `pip install pyserial matplotlib pandas`. |
| **PulseView** (sigrok) | For the logic analyzer. |
| **Zadig** | **Do not skip this one.** Your FX2-based analyzer enumerates as an unknown device on Windows; Zadig installs the WinUSB driver that lets PulseView see it. Without it the analyzer appears dead and looks like a dud purchase. |
| **STM32CubeIDE** | Stage 1, but install it now — large download, fussy first run. |

**In WSL (Ubuntu 24.04):** `sudo apt update && sudo apt install build-essential git python3-pip python3-venv cmake`

> **DEFINITION** — **The WSL question, settled.** Flash from **Windows**. Plot from **either**. Learn ROS 2
> in **WSL** later. Do not flash from WSL — it needs `usbipd-win` and adds a step every time you
> unplug a board, which you will do fifty times in this stage. Clone the repository twice, once on
> each side, both from GitHub. Native Ubuntu becomes mandatory at Stage 2, not now.

### Build — the repository, which already exists

**The skeleton is already there.** It was scaffolded and pushed before you started: the directory
tree, a licence, `CHANGELOG.md`, `.gitignore`, `.gitattributes`, `.editorconfig`, a
GitHub Action, a README in every folder saying what belongs in it, and the Stage 0 PlatformIO project
with every class declared and every body left as a TODO for the session that writes it.

**Nothing was scaffolded that records a decision, a measurement or a session**, and that is the line
the scaffolding was drawn on. There are no ADR stubs, no session notes and no tuning files, because
every one of those is a claim about work that has not happened yet. `docs/decisions/` does not exist
at all, and no ADR has been written or numbered for you: you create the folder the evening you make
the first decision worth recording, and which decision that turns out to be is yours.

That was done on purpose, and the reason is the first line of this session. An evening spent on
`mkdir` teaches you nothing. An evening spent finding out why PlatformIO cannot see your board
teaches you exactly the thing S4 needs you to already know. So the typing is done and **the
understanding is not** — and the understanding is the part that was never transferable anyway.

Tonight you read the tree, prove it does what it claims, and then make the first commit that is
genuinely yours.

**Walk it, one line each.** Where a folder was specified rather than invented, the source is named —
go and read that line if the one-liner is not enough.

| Path | What goes in it | Specified in |
|---|---|---|
| `firmware/stage0-uno/` | This stage's PlatformIO project. Two environments, `uno` and `native` | *Before You Build*, Part III |
| `firmware/stage1-stm32/` | A README and nothing else yet — CubeIDE generates the project in S1.0 | Stage 1 Workbook, S1.0 |
| `docs/guides/` | This document set, committed alongside the work it describes | *Before You Build*, Part III |
| `docs/sessions/` | One folder per session, `<slug>/README.md`, written after the session. `_TEMPLATE.md` is the one to copy | Every session's *Artifacts*, below |
| `docs/derivations/` | Your handwritten maths, photographed the day you did it | This workbook, "Repository additions" |
| `docs/reference/` | **Material you fetched from elsewhere** — datasheets, manuals, vendor listings. Nothing in it is your own work | This workbook, every *Look it up yourself* |
| `docs/tuning/` | One dated file per session: every gain, every measured number, what it did | *Before You Build*, Part III → "Write down the number" |
| `docs/tuning/raw/` | Captured CSVs, straight off `capture.py` | This workbook, S7 |
| `docs/tuning/plots/` | Generated PNGs. Committed to git proper, not LFS — they are small and regenerable | This workbook, S7 |
| `docs/motor-spec.md` | Your measured motor constants. **This motor has no datasheet, so this file becomes it** | This workbook, S1 |
| `docs/protocol.md` | The CAN message specification. Empty until S1.7 | Stage 1 Workbook, S1.7 |
| `hardware/wiring/` | A dated photograph of every wiring change. Hardware has no `git diff` | *Before You Build*, Part III |
| `hardware/cad/` | STEP exports and native source. Empty until Stage 2 | *Before You Build*, Part III |
| `hardware/bom.md` | What is actually on the bench, as opposed to what was ordered | *Before You Build*, Part III |
| `tools/` | `capture.py` and `plot.py`, both stubs. You write them in S7 | This workbook, S7 |
| `CHANGELOG.md` | One entry per exit-gate tag, written **before** the tag is pushed | *Before You Build*, Part III |
| `.github/workflows/ci.yml` | Builds the firmware on every push. The `pio test` line is commented out until S12 | This workbook, "Repository additions" |
| `.website-capture.md` | The capture tracker. **Gitignored** — a to-do list about the build, not a record of it | *Before You Build*, Part III → "At the end of every session" |

Every folder in that table that can hold your work has a `README.md` in it saying what belongs there
and what does not. **Read the four in `docs/` tonight** — `sessions/`, `derivations/`, `reference/`
and `tuning/`. They are a page between them, and they are the answer to "does this go in
`derivations/` or `reference/`" every time it comes up over the next seven months. The rule they
encode is ownership: **`derivations/` is your handwriting, `reference/` is somebody else's document,
`tuning/` is a number you measured.**

**Three absences, so they read as decisions rather than oversights.**

`docs/decisions/` is in *Before You Build*'s tree and **does not exist yet.** It is created by
`mkdir` on the evening you write the first ADR, and not before, for the same reason nothing was
scaffolded into `docs/derivations/`: an empty folder of decisions is a claim that you have been
making them. The rules for what goes in it — filename, numbering, the four sections — are in
*Before You Build*, Part III → "Decisions get their own files", and the sessions that call for one
say so in their own text.

`ros2_ws/src/` is in *Before You Build*'s tree and is **deliberately not here yet.** It arrives in
Stage 2, because an empty ROS 2 workspace is three generated directories and nothing else, and
`colcon` makes it in one command the moment you have a package to put in it. Waiting costs nothing.

`firmware/stage1-stm32/` holds a README and no project. CubeIDE generates that tree from the `.ioc`
in S1.0, and generated code does not want a hand-made skeleton underneath it.

### Verify it rather than accept it

Four checks. **Each one breaks in a different place**, which is the entire point — you are finding
out which link of the chain is which at the one moment when nothing is at stake.

1. **`pio run -e uno`, from a clean clone.** Not from the folder you have been poking at — clone the
   repository fresh into a second directory and build it there. It should compile `main.cpp` into an
   image for a chip you are not holding. If it does, your toolchain is real; if it does not, you have
   found tonight's actual work, and you have found it before it can be mistaken for a code problem.

2. **`git log --oneline`.** Read every commit message. They are somebody else's — the whole history
   to this point is scaffolding, which is why S0's *Artifacts* below make a point of your first
   commit being yours. Notice the format while you are here; *Before You Build*, Part IV specifies
   it and you are about to start writing them.

3. **Open `.gitignore` and check the top block against *Before You Build*, Part III → "A
   `.gitignore` worth having on day one".** It should be that list, verbatim, under a comment saying
   so. **Verbatim is the claim you are testing** — if a line has drifted, the document and the
   repository disagree and one of them is wrong. Everything below that block is an addition, and the
   comments there say what each rule is for.

4. **Open `firmware/stage0-uno/platformio.ini` and say what every key does, out loud.** There are
   six or seven and you will not have met most of them. That is expected and it is not a gap you
   should fill by guessing: *Before You Build*, Part IV → "The build system, and the files that
   configure it" walks the file key by key, along with `include/` versus `src/`, `#pragma once`,
   cross-compilation, Unity, and what a `native` environment is for. Twenty minutes, once, and this
   file stops being furniture.

> **CHECK YOURSELF** — Why are there **two** environments in that file rather than one, and what can
> the `native` one do that `uno` cannot? Answer before you read Part IV. The answer is the reason
> S12's unit tests are possible at all, and it is a genuinely good thing to be able to explain about
> an embedded project.

### Then make the first commit that is yours

Every commit above you is an agent's. **Yours starts here**, and S0 is not finished until it exists.
Two candidates, and doing both is better than choosing:

- **The three sentences at the top of `README.md`** saying what Mimic is, in your words rather than
  the ones already there. *Before You Build*, Part III: it grows with the project, and it grows far
  better than it gets written from nothing at the end.
- **The first file in `docs/tuning/`.** Tonight that is `power.md` with your adapter's open-circuit
  voltage in it, or a dated file with nothing but a heading and the date. It does not matter that it
  is thin.

That second one is not arbitrary. *Before You Build*'s setup checklist closes with three criteria for
being ready, and **`docs/tuning/` having at least one file in it is the one it says people skip.** An
empty folder is a folder you have not started using, and the habit is the point rather than the file.

> **WHERE THIS POINTS** — `docs/derivations/` is the folder that matters most for what you are trying to
> do with this project, and it is the one most easily left empty. A photographed page of your own
> algebra, committed the day you did it, is evidence. A tidy write-up produced at the end is a claim.
> Hiring managers can tell the difference and so can you. Nothing was scaffolded into it, because
> there is nothing anybody else could have put there.

> **WHERE THIS POINTS** — This structure survives to Stage 4. `docs/decisions/` is the same folder in
> S4 and in M4.5; `docs/tuning/` holds a step response tonight and an EMG fatigue plot in eight
> months. That is why it was worth getting right once rather than growing it by accident — and it is
> why you should resist tidying it later, because a folder that has been reorganised loses the one
> thing it had, which is that its contents are in the order they happened.

### Draw this

**Nothing, and that is the only session in Stage 0 where that is true.** Tonight is unpacking,
installing and reading — there is no geometry, no signal and no decision with a shape to it. The
nearest thing to a drawing is the labelled bench itself, and a photograph of that is better than a
sketch of it would be.

The drawing starts in S1, with the six-wire map. From there every session has one.

### What will go wrong

Every failure in this session is a toolchain failure, which means none of them is your code — worth
knowing, because they all *look* like your code.

- **PlatformIO cannot find the board.** No driver, wrong port, or the board is on a charge-only USB
  cable. Try a different cable before anything else; it is the single most common cause and the least
  suspected.
- **PulseView lists nothing.** You skipped Zadig. The analyzer enumerates as an unknown device on
  Windows and looks like a dud purchase until WinUSB is installed.
- **`git push` asks for a password every time.** You are on HTTPS without a credential helper. Switch
  the remote to SSH and add a key, once, tonight — you will push a hundred times this stage.
- **`import serial` fails but `pip install pyserial` said it succeeded.** Two Pythons. `pip` installed
  into one and `python` is the other. Use `python -m pip install ...` so the two cannot disagree.
- **Line endings churn on every file the moment you clone on both sides.** `core.autocrlf` was not set
  to `input` before the first clone. Fix the setting, then re-clone; fixing it afterwards leaves the
  damage in your history.

**Capture the broken state.** PulseView's device list, empty, before you run Zadig. It is the least
interesting failure in this session and the most useful one to have, because it is the moment the
project's first piece of hardware looked broken and was not. Screenshot it, then run Zadig.

### Prove it

Build and upload the PlatformIO blink example to a bare UNO. Open the serial monitor and see
something. `git push` without a password prompt. Open PulseView and confirm it lists your device.
And the four repository checks above, of which the clean-clone `pio run -e uno` is the one that
actually proves a chain end to end.

> **CHECK YOURSELF** — Four things just happened between you pressing Upload and the LED blinking:
> your source was compiled, it was linked against a core you did not write, the result was converted
> into an image, and something copied that image onto the chip. **Name the program that did each
> step.** You do not need to be right — you need to have an answer, because in three weeks something
> in that chain will fail and the first useful question will be "which of the four?". Interlude E of
> the Project Guide has the answer; write yours down first, then go and check it.

### Artifacts

- **`docs/sessions/bench-and-toolchain/README.md`** — written at the end of the session, not the
  start. Three to five bullets on what actually happened, what the objective did not predict,
  and what you got wrong first. See [the template](../sessions/_TEMPLATE.md).
- **Your first commit**, on top of the scaffolding — the three-sentence README opener in your own
  words, the first file in `docs/tuning/`, or both.
- Photo of the labelled bench → `hardware/wiring/2026-xx-xx-bench.jpg`.
- **Site:** the bench photo and the repo link. Day one of the log.
  **The shot:** one still. The bench lit from the front, close enough that four bin labels are
  readable — the labels are the content, because they are what says this was unpacked
  deliberately. The repository link goes beside it as text, not as a photograph of a browser.

---

## S1 · Motor forensics, and bolting it down

**Goal:** the motor is rigidly mounted to the plank, and you know its six wires, its winding
resistance, its stall current, and — measured, not assumed — its counts per output revolution.

**You will be able to:** derive counts per output revolution from a PPR figure, a decoding factor and a gear ratio; say why the *lowest* of three winding-resistance readings is the one you want; and distinguish stall, rated and static torque without looking them up.

> **WHERE THIS POINTS** — This session is the Project Guide's milestone **M0.0 (mount it rigidly)** and
> **the first half of M0.1**. See the milestone map at the end of this workbook.

### Concept

Your motor has no datasheet. This is not a problem to be worked around; it is the first genuine
experiment in the project. Every number your control loop uses descends from what you measure in the
next two hours.

An analogy that holds up: you have been handed an instrument you have never played, with no manual.
Before you can play a tune you have to find out how many keys it has and which way is up.

### The math — derive before you measure

**1. Expected counts per output revolution.**

Your motor's encoder is a magnetic Hall type reading a **14-pole ring** on the *motor* shaft, giving
**7 pulses per revolution per channel**. It sits before the gearbox, which is why the resolution at
the output is so high.

```
7 PPR per channel
  × 4        (×4 quadrature decoding — all four edges of both channels)
  = 28 counts per motor-shaft revolution
  × N        (gear ratio — PROVISIONAL, ~300:1 for the 12 V / 100 RPM variant)
  ≈ 8,400 counts per OUTPUT revolution
```

Therefore, if N really is 300:

```
360° / 8,400  = 0.0429° per count
2π  / 8,400   = 7.48 × 10⁻⁴ rad per count
```

Write those three numbers down. Then go and check whether they are true.

> **WATCH OUT** — **`N ≈ 300` is a single-source figure and you should treat it as a hypothesis, not a
> spec.** It comes from one vendor listing for this part number (which gives a 30,000 RPM base motor,
> 1:300 reduction, 1 A stall current, 0.1 kg·cm rated torque and 2 kg·cm stall torque). Other listings
> for a part sold as "12GA-N20" (or "GA12-N20" — both strings are in circulation for this body)
> offer ratios of 10:1, 30:1, 50:1, 100:1, 150:1 and 300:1, and quote
> stall torques from 1.7 to 16 kg·cm and stall currents from 0.67 to 1 A. They cannot all be right
> about your motor. **Every provisional figure in this workbook is marked `[P]` from here on.** Once
> you have measured, replace them — and if your measurement disagrees with 8,400, see
> *Appendix: what changes if the gear ratio is not 300* at the end of this document. It is a short
> list and none of it is difficult; it is only expensive if you find it late.

> **WATCH OUT** — **Two small mistakes multiplying into a large one is the normal shape of a unit bug.**
> Drop the ×4 and use a 100:1 ratio instead of 300:1 and you get `7 × 100 = 700` counts per output
> revolution instead of 8,400 — a factor of twelve, from two errors neither of which looks
> significant on its own. Every angle your controller computed would then be wrong by that constant
> factor, and the symptom would be a loop that overshoots wildly and will not settle. That reads as a
> badly tuned gain, not as arithmetic, which is why you would spend an evening turning knobs before
> you thought to check the constant. Derive this number yourself, from your own encoder and your own
> measured ratio, and never copy it from a document — including this one.

**2. Stall current from winding resistance.**

Measure the resistance across the two thick motor wires. Rotate the shaft slightly between readings
and take three — brush position changes the reading, and the *lowest* is the one you want.

**Why the lowest, specifically.** A brushed motor's brushes sit on a segmented commutator, and where
they happen to be resting decides how many armature windings are in the path between your two probes,
and how good the brush-to-segment contact is. Both of those only ever *add* resistance in series with
the winding you are trying to measure — a partly-lifted brush or a badly-placed one adds contact
resistance, it never subtracts any. So the readings scatter upward from the true value, and the
smallest of them is the closest to it. Three readings is a compromise; if two of them differ by more
than about 20 %, take more.

**Write all three into `docs/motor-spec.md` now, not just the one you keep.** Three readings
scattering by 5 % and three scattering by 40 % are different facts about your meter, your probes and
your motor's brushes, and the lowest value alone throws that away. You cannot go back for the
scatter later — you would have to re-measure, and the brushes will be somewhere else.

```
I_stall = V / R_winding = 12 V / R
```

If R ≈ 12 Ω you should get ≈ 1 A, which matches one published figure for this motor — though other
listings for the same part number quote 0.67 A, which is why you are measuring rather than reading.

> **DEFINITION** — **Rated, stall and static torque are three different numbers and vendors mix them
> freely.** **Stall torque** is what the motor produces at zero speed with full voltage applied; it is
> the largest number on any listing and it is a destructive operating point, not a design figure.
> **Rated torque** (sometimes "continuous" or "nominal") is what it can produce indefinitely without
> overheating — typically a quarter to a third of stall. **Static torque** is what a joint must
> produce simply to hold a position against gravity, which is a demand, not a capability. When a
> listing quotes "2 kg·cm" without saying which it means, assume stall, because that is the flattering
> one. Stage 2's torque budget lives or dies on keeping these three apart.

> **WATCH OUT** — **Your own listing fails that rule of thumb, and that failure is information.** The
> vendor figures quoted two pages up are **0.1 kg·cm rated against 2 kg·cm stall** — a ratio of
> **1:20**, where the definition you have just read puts rated at a quarter to a third of stall,
> which would be 1:3 to 1:4. Something in that listing is wrong: either the rated figure is far too
> low, or the stall figure is far too high, or the two were copied from different motors. You cannot
> tell which from the page, and that is the point — **the anomaly is itself evidence that the listing
> is unreliable**, which is the whole argument for measuring rather than reading. Say so when Stage 2
> S2.4 leans on the 0.0098 N·m rated figure as "the honest number": it is the conservative choice
> *and* it comes from a source that does not agree with itself.

Compare your measured value to your driver: the TB6612FNG is rated **1.2 A continuous, 3.2 A peak**,
with a recommended supply range topping out around **13.5 V** and **15 V as the absolute maximum**.

> **WATCH OUT** — A 1 A stall against a 1.2 A continuous rating is legal and *thermally* uncomfortable.
> A stalled motor is not a safe resting state for this driver. This is one of the reasons S11's
> velocity and current limits exist, and it is why you never leave the rig powered and unattended
> while integral action is enabled.

### Look it up yourself — the driver's real numbers

You are about to compare a measured stall current against a driver rating, and the rating above was
handed to you. Go and get it instead. Twenty minutes, once, and every number in Stage 0 and Stage 2
that touches this part becomes one you can defend.

Find the **TB6612FNG datasheet on Toshiba's own site** — not an aggregator, and check the revision date
on the front page, because two revisions with different formatting are in circulation. **Save the PDF
into `docs/reference/` and commit it**, with its revision and date recorded inside a note beside it;
that folder is the project's home for anything you fetched from somebody else, and it is the first
time you use it. Then answer, writing the **table name and page** beside each answer in
`docs/motor-spec.md`:

1. The **absolute maximum** `V_M`, and separately the top of the **recommended operating** range. Those
   live in two different tables and mean two different things; if you found one number you have found
   only one of them.
2. The output current rating, **and the conditions attached to the peak figure** — there is a maximum
   pulse width and a duty cycle, and Stage 2 S2.4's whole argument about stalls turns on them.
3. The truth table. What do `AIN1 = AIN2 = HIGH` and `STBY = LOW` each do?
4. The minimum logic-side `VCC`, and whether 3.3 V is inside it. You need this in Stage 1, where an
   STM32 drives this same board.

> **CHECK YOURSELF** — Which of the four numbers you just found is the one you design to, and which is
> the one you never touch? If you cannot say which table each came from, go back — that distinction is
> the single most useful thing a datasheet contains and the one people skip.

### Build — bolt it down, before anything else

Do this first, while the motor is still just a lump of brass on a bench and nothing is wired to it.

A motor that skitters, twists or flexes under load makes every step response you plot in S9 and S10
unreadable, and you will spend days tuning gains against a mechanical problem. **The rigid mount is
the first debugging tool in the project and it is also the cheapest.** It is the reason the plank
exists.

**What you have:** the plywood board (9.5 × 20 × 0.5 in), the bracket that shipped with the motor,
the Kalote M3 kit, the M3 brass heat-set inserts, and the T12 insert-nut tip.

**Where to put it.** Place the motor's output shaft roughly **5 inches from one short end** of the
board, centred across the width. That leaves clearance for the driver, the breadboard and the buck
converter behind it, and it is where the shoulder pivot goes in Stage 2 — so the hole pattern you
drill now is the one the arm uses later. Mark the bracket's hole centres with the calipers, not by
eye.

**How to fix it — pick one and write down which.**

| Method | When | Why |
|---|---|---|
| **M3 heat-set inserts** | Preferred | Melt an insert into a drilled hole, bolt into brass. Survives repeated disassembly, which you will do more than twice. Needs the T12 insert tip. |
| **M3 bolt, washer, nut, through-drilled** | Fine | Drill straight through the board, bolt and nut with a washer under each. Slower to change, mechanically excellent. |
| **Wood screws into the face of the plywood** | **No** | Plywood face grain lets go under repeated dynamic loading. It will feel solid on day one and be loose by S10, and it will read to you as a control problem. |

**Then clamp the board to the desk.** A G-clamp at each end. The board on its own is heavy enough to
be stable clamped and *not* heavy enough to be stable free-standing — a 300:1 gearbox reversing
direction at full command will walk an unclamped plank across a desk.

> **CHECK YOURSELF** — Grip the motor body and try to twist it against the board with real force. Nothing
> should move, creak or flex. Then press down on the far end of the board: if the whole assembly
> rocks, add the second clamp. If you can see daylight move under the bracket, the fixing is wrong,
> not "good enough for now."

> **WATCH OUT** — Fingers out of the gearbox and away from the output shaft from here on, including with
> the power off. A geared motor has far more torque than its size suggests and no sense of what it is
> closing on, and the coupler you will fit later turns a bare shaft into a pinch point.

### The multimeter, since every measurement in this stage goes through it

You will use this instrument several hundred times over the next year and nobody has told you how. Four
minutes, once.

**The three modes you actually need.**

- **Continuity** (the beeper). Is this connected to that? Power off, always. It is your fastest tool
  and it is rung 2 of the debugging ladder.
- **DC volts.** Probes in **parallel** — across the thing you are measuring, circuit live. Black lead
  on your star ground, red on the point of interest. This is how you meter a rail.
- **Resistance (Ω).** Power off, and ideally with the component out of circuit — everything else in
  parallel with it is measured too, which is why a resistor in a circuit often reads lower than its
  value.

**Current is the one that is different, and the one that destroys meters.** To measure current the
meter must be **in series** — you break the circuit and let the current flow *through* the instrument —
and on most meters that means physically moving the red lead to a separate **A** jack.

> **WATCH OUT** — **The mistake everyone makes once: leaving the lead in the A jack and then probing a
> voltage.** In the A position the meter is a near short circuit *by design* — that is what lets
> current pass through it. Put that across a 12 V rail and you have connected a dead short, and the
> best case is that the meter's fuse blows. **Habit to build now: the red lead lives in the V/Ω jack,
> and it goes to the A jack only for the duration of one measurement and comes straight back.**

**And the reason S1 computes stall current rather than measuring it.** You could measure it: stall the
motor, put the meter in series, read the amps. It is a legitimate experiment and it is also awkward —
you need the motor held still, the meter in the circuit, and the reading taken quickly enough not to
cook anything. `I = V/R` from a resistance you can measure safely, in seconds, with the power off, gets
you the same number for free. **Prefer the measurement you can take safely and repeatedly over the one
that is more direct.** That is a real engineering habit and it is worth naming.

**Heat, which this project talks about constantly and never measures.** "Thermally uncomfortable",
"thermal event", "cooking" — those all appear in this workbook and you have no instrument for any of
them. You do have a hand:

```
   THE BACK-OF-THE-HAND TEST, and what the numbers mean

   Power off first if you can. Back of a finger, briefly, not a fingertip
   and not for long.

     comfortable to hold indefinitely      < ~50 °C   fine
     hot, you want to let go in a second   ~60 °C     watch it
     you cannot keep contact               > ~70 °C   stop and find out why

   Silicon is usually rated to 125-150 °C at the junction and the package is
   cooler than the junction, so "too hot to touch" is not the same as "about
   to fail". It IS the same as "something is dissipating more than you
   planned", which is the interesting question either way.
```

Do this on the TB6612 and on the buck converter after any run where a motor worked hard. If either one
gets past "want to let go", stop and work out where the power is going before you continue — and note
that a stalled motor is the case where it will.

### Build — identify the six wires

The multimeter does all of this. Motor unpowered, nothing connected.

1. **Two thick wires** read a few ohms to each other — motor + and motor −.
2. **Four thin wires** are the encoder: VCC, GND, A, B. On this family the common colouring is red
   = motor+, white = motor−, black = encoder VCC (5 V), blue = encoder GND, green = A, yellow = B.
   **Verify rather than trust it** — colour conventions on AliExpress motors are suggestions.
3. Power the encoder only (5 V from the UNO, motor wires unconnected). Turn the shaft by hand and
   watch A and B on the multimeter's continuity or DC volts mode. Both should swing between ~0 V and
   ~5 V. This encoder has built-in pull-up shaping resistors, so you should see clean levels without
   adding anything.

### Build — measure counts per output revolution

You cannot do this properly until S3 gives you a working counter. **Do the mechanical half now:**
mark the output shaft with a fine Sharpie, mark a fixed reference on the bracket, and confirm you can
count ten full turns by hand without losing your place. Then come back at the end of S3, run the
counter, turn it ten times, and divide.

> **CHECK YOURSELF** — Ten turns, not one. One turn divides your measurement error by one; ten divides it
> by ten. If your result is 8,400 ± 30 you have a 300:1 gearbox. If it is closer to 7,000 you have
> 250:1. Either is fine — but from here on, *your* number goes in the code and the guide's does not.

### What will go wrong

- **The multimeter reads open circuit across the two thick wires.** Either you have the wrong pair, or
  a brush is resting between commutator segments. Turn the shaft a few degrees and re-measure before
  concluding the motor is dead.
- **You connect 5 V to the wrong pair.** The four thin wires are the encoder; the two thick ones are
  the motor. Putting 5 V across the motor terminals is harmless. Putting 12 V across the *encoder*
  destroys it silently, and the symptom in S3 is a counter that never moves. **Identify the pairs by
  resistance before anything is powered** — a few ohms is the motor, hundreds of kΩ or open is not.
- **The encoder reads a constant voltage and never changes as you turn.** Almost always the ground
  reference: A and B are measured against the *encoder's* GND, not against the UNO's, and if those two
  are not tied together yet you are measuring against nothing.
- **The shaft mark rubs off somewhere around turn seven.** Ten turns is only ten turns if you can still
  see where you started. Use a fine paint pen, or file a shallow flat, or clamp a pointer to the
  shaft — and mark the *bracket* as well, because the reference matters as much as the mark.
- **You skip the mount because the wiring is more interesting.** This is the failure this session
  exists to prevent, it costs a week in S8, and it does not announce itself until then.

**Capture the broken state.** The meter reading open circuit across the two thick wires, before you
turn the shaft a few degrees and watch it come back. Photograph it. That reading is what a brush
resting between commutator segments looks like from the outside, and it is the first time this
project will tell you a part is dead when it is not.

### Draw this

The six-wire map, as a labelled sketch: motor terminals, encoder VCC/GND/A/B, and which colour is
which **on your actual motor**. Photograph it.

**Then, on the same page, write your three measured numbers and the three you predicted** — expected
counts/rev, winding resistance, computed stall current — with the gap between each pair. That page is
the first evidence in the repository that you check things, and it is worth more than a correct
prediction would have been.

### Prove it

Four things, and each one is a number rather than a feeling:

1. **The mount.** Grip the motor body and twist against the board with real force. Nothing moves,
   creaks or flexes, and no daylight appears under the bracket.
2. **The wires.** You can say which of the six is which, and you verified it with the meter rather
   than from the colours.
3. **Winding resistance**, three readings, lowest recorded, and the computed stall current written
   next to it.
4. **The datasheet numbers**, with the table and page each came from, in `docs/motor-spec.md`.

The counts-per-revolution measurement is deliberately *not* on this list — you cannot make it until
S3 gives you a counter. Do the mechanical half now, come back at the end of S3, and finish it there.

> **CHECK YOURSELF** — You now have a computed stall current and a driver rating. Say, in one sentence,
> whether this motor can safely be held stalled, and for how long. If your answer does not mention
> heat, read the driver rating again — the answer is not a comparison of two numbers.

### Artifacts

- **`docs/sessions/motor-forensics/README.md`** — written at the end of the session, not the
  start. Three to five bullets on what actually happened, what the objective did not predict,
  and what you got wrong first. See [the template](../sessions/_TEMPLATE.md).
- `docs/motor-spec.md` — measured resistance, computed stall current, expected and (after S3)
  measured counts/rev, gear ratio conclusion.
- `docs/derivations/2026-xx-xx-encoder-chain.jpg` — the handwritten counts-per-rev derivation.
- `hardware/wiring/2026-xx-xx-mount.jpg` — the mounted motor, plus one line in
  `docs/decisions/` naming the fixing method you chose and why.
- **Site:** the derivation photo. "Here is the arithmetic, here is the measurement, here is the gap."
  **The shot:** one still, and it is a document rather than a photograph. Page flat, square on, no
  shadow of the phone across it. Both columns must be readable at once: what you predicted and
  what you measured. Crop to the paper's edges — a page floating on a desk reads as a snapshot, a
  page filling the frame reads as a scan.

---

## S2 · Power — draw the topology before you wire it

**Goal:** a 12 V motor rail and a 5 V logic rail that share exactly one ground, with bulk capacitance
where it belongs and the buck converter set to the right voltage *before* anything is connected to it.

**You will be able to:** draw a power tree that separates a motor rail from a logic rail at a single ground point, and explain why a brownout reset is the protection working rather than a crash.

### Concept

Most of what feels like a software bug in the next six weeks will be a power problem. A motor
starting draws a large inrush current; that current pulls the shared rail down; the microcontroller
browns out and resets; and the symptom you observe is "my program restarts randomly when the motor
starts."

> **DEFINITION** — **Brownout.** A supply voltage that sags below the minimum a chip needs to operate
> correctly, but does not fall to zero. The ATmega328P has a brownout detector that deliberately holds
> the chip in reset while this is true, because a processor running on marginal voltage does not fail
> cleanly — it computes wrong answers. So the reset you observe is the protection working. The word
> matters because it is what a datasheet calls it (`BODLEVEL`), and because "brownout" and "crash"
> point you at completely different parts of the bench. You will look at your code, because that is
> where you look, and the fault will be four inches to the left.

The analogy: a house where turning on the shower makes the lights dim. Nothing is wrong with the
lights.

### The math

**1. Power budget.**

```
Motor, stalled worst case:   1.0 A × 12 V  = 12 W
UNO + encoder + logic:      ~0.1 A ×  5 V  =  0.5 W
Supply capability:           5.0 A × 12 V  = 60 W
```

Comfortable, by a factor of about five. Note that "comfortable on average" and "comfortable during a
2 ms inrush transient" are different claims, which is what the capacitor is for.

**2. Why 1000 µF, and why 35 V.**

The bulk capacitor's job is to supply the inrush locally so it does not travel back up the wire and
drag the rail down. Roughly:

```
ΔV = I × Δt / C
   = 1.0 A × 0.002 s / 0.001 F
   = 2 V of sag during a 2 ms transient
```

Two volts of sag on a 12 V motor rail is survivable. Two volts of sag on a shared 5 V logic rail is
a reset. That is the whole argument for splitting the rails.

The 35 V rating is not about 12 V. Electrolytics are derated by heat and ripple, and a 16 V part on a
12 V rail with switching ripple is running close to its edge. You bought 35 V parts; use them.

**3. TB6612 headroom.** Your supply is nominally 12 V but a cheap adapter reads 12.6–12.9 V
unloaded. The TB6612FNG's recommended operating range tops out around 13.5 V, with 15 V as the
absolute maximum. You are inside the recommended range, but not by much. Measure your adapter's
actual open-circuit voltage in this session and write it down.

### Draw this — before you wire anything

The **power tree**. One page, by hand:

```
FIGURE III.S2.1 — The power tree, the switch, and the single ground point

   12 V 5 A adapter
        │
   ┌────┴────┐   INLINE SWITCH — breaks the 12 V rail, within reach of
   │  SWITCH │   where you sit. S8 drives the rig to sustained oscillation
   └────┬────┘   and S10 stalls it deliberately; both assume you can cut
        │        power in under a second without groping for a barrel jack.
   barrel jack breakout
        │
        ├──────────────► TB6612  VM  (motor rail)   + 1000 µF across VM/GND
        │
        └──► XL4015 buck ──► 5 V ──► UNO 5V pin, TB6612 VCC, encoder VCC
                                     + 1000 µF bulk, + 100 nF close to the UNO
                                       (you own ten of one and a hundred of
                                        the other; nothing else is needed)

   GROUND: every ground meets at ONE point on the breadboard rail.
           Motor return, logic return, encoder return, UNO GND.

   NOTE — feeding the UNO's 5 V pin means that from S7 onward, when USB is
   also plugged in for telemetry, two supplies are tied together on an
   unprotected rail. See the WATCH OUT below before you do both at once.
```

> **DEFINITION** — **Star ground.** Every return path meets at a single physical point rather than daisy-
> chaining through the board. The reason is that wire has resistance: if the motor's return current
> flows through the same length of wire your encoder's ground uses, the motor's current *shifts your
> encoder's idea of what 0 V means*, in time with the PWM. That is not noise you can filter. It is a
> wiring topology error, and it is why "encoder glitches" so often turn out to be a grounding
> problem.

> **DEFINITION** — **Ground loop.** What you get when two points that are both called "ground" are joined
> by more than one path, so current can circulate around the loop those paths enclose. The two ends
> then sit at slightly different potentials, and every signal referenced to one of them is measured
> against the wrong zero. A star topology has exactly one path to each return, which is why it does
> not have this problem. This is the same failure as the daisy-chain above, named for the shape it
> makes on a diagram — and it is the reason the spec traps warn you about it.

### Soldering, since this is the first time you do any

You bought a T12 station, tips, solder, flux, wick, a pump, a third hand and a silicone mat — and
nothing in this document set has told you how to use them. This session asks you to solder an
electrolytic capacitor across a driver's supply pins, which is a real joint on a real part, so here is
the twenty minutes of technique first. **Practise on scrap header pins before you touch the capacitor.**

**The one idea underneath all of it: you are not melting solder onto a joint, you are heating the joint
until the joint melts the solder.** Almost every bad joint comes from getting that backwards.

```
   THE SEQUENCE, and it is always this

   1. TIN THE TIP.     A little solder on the tip before you start. It is not
                       decoration — a bare tip transfers heat badly because it
                       touches the work at one point, and a wetted tip touches
                       through a puddle of molten metal. Tin it, wipe it on the
                       brass wool, tin it again. Do this every few joints.

   2. HEAT BOTH.       Touch the tip so it bridges the PAD and the LEAD at
                       once, for about a second. Not one, then the other.

   3. FEED THE SOLDER  into the joint, on the far side from the tip — so it has
                       to flow through the heat to get there. If it melts on
                       contact with the iron rather than the work, the work is
                       not hot enough and you are about to make a cold joint.

   4. WITHDRAW SOLDER, then the iron. In that order, and do not move the joint
                       while it cools — a second is enough.

   Total: two to three seconds per joint. If you are there for eight, the
   temperature is too low, not too high — and low-and-slow cooks components
   far more effectively than hot-and-quick does.
```

**Temperature.** Start at **330 °C** with your 63/37 leaded solder. Go up for big thermal masses —
ground planes, the motor's own terminals, thick wire — and down for nothing. A T12 cartridge has the
heater in the tip, so it recovers fast and you do not need to run it hot to compensate.

**What a good joint looks like.** Shiny, concave, and it **wets** — flows out to a feathered edge where
it meets the pad, like water on a clean surface rather than a bead of mercury. A ball sitting on top,
dull and rounded, has not wetted: it is a **cold joint**, it may test as continuous today and open in
three weeks under vibration, and it is the failure that hides best.

**Flux is not optional.** Your solder has rosin in the core, and it is spent within a second or two of
melting. Any joint you rework — anything you touch twice — needs fresh flux from the pen, because you
are otherwise soldering through the oxide layer the first pass created.

**Desoldering.** Wick for pads and flat joints: fresh flux, lay the braid on, press with the iron, and
the solder climbs into it. Pump for through-holes with a lot of solder: heat until it flows, then
withdraw the iron and fire the pump in the same motion.

> **WATCH OUT** — **Fumes, and the thing people get backwards.** The smoke is not lead — lead does not
> vaporise anywhere near soldering temperature. It is the **rosin flux**, and it is a respiratory
> irritant and a recognised occupational sensitiser. The lead risk is real but it is on your *hands*:
> wash them before you eat, and do not eat at the bench. Extractor or an open window for the fumes,
> which is why the DIY fan-and-carbon-sheet line is in Tier B.

> **CHECK YOURSELF** — Make five joints on scrap header, then cut one open with the diagonal cutters
> and look at the cross-section. Solder should have flowed *around* the pin and filled the hole, not
> sat on top of it. If you cannot tell a good one from a cold one by eye yet, make five more — this is
> the cheapest possible place to learn it, and the alternative is learning it on the joint that fails
> intermittently in S8.

### Build — in this order, and not another

0. **Fit the switch first.** An inline toggle or rocker in the 12 V lead, upstream of everything,
   rated for at least 5 A DC. A switched mains bar that the adapter plugs into is an acceptable
   substitute and is what you already own; a toggle in the DC lead is better because it is on the
   bench rather than under the desk. **What is not acceptable is planning to yank the barrel jack**,
   which is what S8 and S10 would otherwise require you to do while a geared motor is oscillating.
   It is a C$3 part, it is in Tier B of *What's Left to Buy*, and every "power switch" instruction
   later in this workbook means this switch.
1. **Set the buck converter with nothing connected to its output.** Feed it 12 V, put the meter on
   its output terminals, and turn the trim pot until it reads 5.00 V. This is what the precision
   screwdriver is for. Turn the current-limit pot fully counter-clockwise first, then up — **to
   about 0.5 A**, and here is where that number comes from rather than being handed to you.

   Your logic side draws roughly 100 mA: the UNO is about 50 mA, the encoder a few, the TB6612's
   logic side a few more. Set the limit at roughly **five times** your expected draw and it will not
   trip in normal use, but a dead short pulls the rail down instead of delivering amps into a
   mistake. Too tight and the UNO browns out on every reset inrush and you will chase a phantom;
   too loose and it is not doing anything. **Write the number you set and the draw you measured
   into `docs/tuning/power.md`** — if your measured idle draw is not near 100 mA, use five times
   yours rather than five times mine.

   This pot is standing in for the smoke stopper you do not own, which is the only reason step 1
   is load-bearing rather than housekeeping.
2. Confirm 5.00 V under no load. Then connect the UNO and confirm it still reads 5.00 V.
3. Solder the **1000 µF** across the TB6612's VM and GND, observing polarity. The stripe is the
   negative side. Backwards electrolytics vent, loudly.
4. **Solder a 100 nF ceramic directly across the motor's own terminals** — at the motor, not on the
   breadboard. Short leads. This is the single highest-value five minutes in Stage 0.

> **DEFINITION** — **Decoupling capacitor** (also *bypass capacitor*). A small capacitor placed as close
> as physically possible to a noise source or a noise-sensitive part, to give high-frequency current a
> short local loop instead of a long one through the power wiring. The 100 nF at the motor terminals
> is decoupling a source; the 100 nF you will put next to the UNO decouples a victim. Both are the
> same part doing the same job in opposite directions, and in both cases *close* is the entire
> specification — a decoupling capacitor ten centimetres away has been decoupled from the thing it was
> supposed to decouple.

> **WATCH OUT** — **External 5 V on the UNO's 5 V pin back-feeds the USB port when both are connected.**
> The 5 V pin sits on the same rail as the USB supply with no protection between them, so from S7
> onward — when the cable is plugged in for telemetry while the buck is also feeding the pin — you
> have two sources tied together. Two consequences. First, whichever reads higher sources current
> into the other; a buck set to 5.2 V pushes into your host's USB port, and hosts vary in how much
> they enjoy that. Second, the rail is now only as clean as the worse of the two. Pick one of:
> **(a)** power from the buck and leave USB unplugged except when capturing, **(b)** power from USB
> alone while tuning and accept that motor current comes from the 12 V rail only, or **(c)** feed VIN
> with 7–12 V instead of the 5 V pin and let the onboard regulator arbitrate. Write down which, in
> `docs/decisions/`. The one thing not to do is discover this by finding a warm USB port.

> **WATCH OUT** — The 100 nF at the motor terminals suppresses brush commutation noise at its source.
> On a breadboard, ten centimetres away, it does almost nothing, because the ten centimetres of wire
> between it and the brushes is the antenna. Encoder counts that drift or jump — the failure the
> Project Guide names first — are very frequently this exact capacitor, missing or in the wrong
> place.

### What will go wrong

- **Buck converter outputs 12 V regardless of the pot.** You are turning the wrong pot (there are two
  on the XL4015: voltage and current) or it is a multi-turn pot and you have not turned it enough —
  they can need fifteen full rotations.
- **UNO resets when the motor starts.** Missing bulk cap, or you have not actually split the rails,
  or the grounds are daisy-chained.
- **Everything reads 4.7 V.** You are powering the UNO through its barrel jack or VIN and losing the
  onboard regulator's dropout. Feed the **5 V pin** directly from the buck, or feed VIN with 7–12 V
  and accept the regulator. Pick one and write down which.

> **DEFINITION** — **Dropout, and LDO.** A linear regulator works by burning off the difference between
> its input and its output as heat, so it needs the input to stay some minimum amount above the
> output. That minimum is its **dropout voltage**. An **LDO** is a *low-dropout* regulator, one that
> needs only a few hundred millivolts of headroom rather than a couple of volts. The UNO's onboard
> regulator is not an LDO, which is why feeding it 5 V gives you 4.7 V out and not 5 V — you are
> asking it to work inside its dropout. A buck converter is a switching regulator and does not have
> this constraint, which is the whole reason the XL4015 is in your power tree.

**Capture the broken state.** The meter reading 4.7 V on a rail you set to 5.00 V. Photograph the
display before you work out that you are feeding VIN and paying the regulator's dropout. It is a
two-digit photograph and it is the whole of the LDO definition above, in a form you will actually
remember.

### Prove it

Meter on the 5 V rail, at the UNO's own pin. Note the voltage idle. You will re-measure this in S4
with the motor running and compare — the delta is the number that matters.

> **CHECK YOURSELF** — Write down, now, what you expect that delta to be in S4 — tens of millivolts,
> hundreds, or a volt — and why. Then check the prediction when you get there. Being wrong is the
> useful outcome: a rail that sags far more than you expected is telling you something about your
> wiring that no amount of staring at code will, and you will only notice it fell if you had a number
> in mind before it did.

### Artifacts

- **`docs/sessions/power-tree/README.md`** — written at the end of the session, not the
  start. Three to five bullets on what actually happened, what the objective did not predict,
  and what you got wrong first. See [the template](../sessions/_TEMPLATE.md).
- `hardware/wiring/2026-xx-xx-power-tree.jpg` — the hand-drawn topology.
- `docs/tuning/power.md` — adapter open-circuit voltage, buck output set point, 5 V rail idle.
- **Site:** the power tree drawing. It reads as engineering more than any photo of a breadboard does.
  **The shot:** one still of the whole page, square on. Two things must be legible or the drawing
  does not carry its argument: the **single ground point** where every return meets, and the
  inline switch. Everything else can be rough.

---

# PART II — SIGNAL, MOTION, TIME

---

## S3 · The encoder — interrupts and ×4 decoding

**Goal:** a signed count that tracks the shaft exactly, in both directions, without losing a single
transition when you spin it hard by hand.

**You will be able to:** derive the full sixteen-entry quadrature table from a stated convention, prove your decoder loses no counts, and explain why ×4 decoding gives four times the resolution for free.

### Concept

One channel tells you the shaft moved. Two channels ninety degrees apart tell you which way,
because you can see which one changed first. There is no cleverness in it — you are watching a
two-bit number walk around a four-state loop, and the direction it walks is the direction the shaft
turns.

Forward, the states go `00 → 01 → 11 → 10 → 00`. Backward, the same loop the other way. Every single
transition is a count if you decode all four — which is where the ×4 comes from, and it is free
resolution you get in software.

```
FIGURE III.S3.1 — Two channels, four states, one direction

  Both traces start LOW, so the first state is 00. The only thing you
  are looking for is which channel moves first.

  FORWARD — B leads A                   REVERSE — A leads B

  A      ┌─────┐     ┌─────┐            A   ┌─────┐     ┌─────┐
     ────┘     └─────┘     └──             ─┘     └─────┘     └─────
  B   ┌─────┐     ┌─────┐               B      ┌─────┐     ┌─────┐
     ─┘     └─────┘     └─────             ────┘     └─────┘     └──
      ↑                                     ↑
      B changes first                       A changes first

  states  00 01 11 10 00 …              states  00 10 11 01 00 …

  One cycle is 12 columns and the channels are drawn 3 columns apart —
  a quarter period, which is what "ninety degrees" means. All four AB
  states are therefore equal in width. Check that against your own
  analyzer capture in *Prove it*: unequal state widths mean the offset
  on the wire is not 90°, which is a mechanical or wiring fact about
  your encoder rather than a drawing convention.

  state = (A << 1) | B, so the four states are 0, 1, 3, 2 — not 0,1,2,3.

                          00
                      ↗        ↘
                   10            01     clockwise  = forward = +1
                      ↖        ↙        anticlockwise = reverse = −1
                          11

  The DIAGONALS of that ring — 00↔11 and 01↔10 — are illegal. Two bits
  cannot change in one step. Seeing one means you missed an edge.
```

Read the figure against the definition rather than against your intuition. If forward is
`00 → 01 → 11 → 10`, then from `00` it is **B** that rises first, so **B leads A in the forward
direction**. Plenty of references draw quadrature the other way round, because they define forward
as `00 → 10 → 11 → 01`; both are self-consistent and neither is more correct. What matters is that
the figure, the table you are about to derive, and your code all use the same one. When you probe
the real motor in *Prove it*, you are testing which of the two your particular wiring produces.

### The math — the transition table, derived

Define `state = (A << 1) | B`, giving four values 0, 1, 3, 2 around the loop. Define **forward** as
`00 → 01 → 11 → 10`. Build a 16-entry lookup indexed by `(previous << 2) | current`:

**Get the index arithmetic right first, because this is where people go wrong.** The index is built
from the *binary values* of the two states, not from their position in the loop. The loop visits
`00, 01, 11, 10` — but those are the values 0, 1, **3, 2**. So `prev = 11` means `prev = 3`, and its
four indices are 12–15, not 8–11. Write the table out in index order and the trap disappears:

| index | prev → curr | delta | why |
|---|---|---|---|
| 0 | 00 → 00 | 0 | no change |
| 1 | 00 → 01 | **+1** | forward |
| 2 | 00 → 10 | **−1** | backward |
| 3 | 00 → 11 | 0 ✗ | **illegal** — both bits changed |
| 4 | 01 → 00 | **−1** | backward |
| 5 | 01 → 01 | 0 | no change |
| 6 | 01 → 10 | 0 ✗ | **illegal** — both bits changed |
| 7 | 01 → 11 | **+1** | forward |
| 8 | 10 → 00 | **+1** | forward |
| 9 | 10 → 01 | 0 ✗ | **illegal** — both bits changed |
| 10 | 10 → 10 | 0 | no change |
| 11 | 10 → 11 | **−1** | backward |
| 12 | 11 → 00 | 0 ✗ | **illegal** — both bits changed |
| 13 | 11 → 01 | **−1** | backward |
| 14 | 11 → 10 | **+1** | forward |
| 15 | 11 → 11 | 0 | no change |

```
{ 0, +1, -1, 0,  -1, 0, 0, +1,  +1, 0, 0, -1,  0, -1, +1, 0 }
```

```
FIGURE III.S3.2 — The same sixteen entries as a grid

  Read the index off the axes: index = (prev << 2) | curr. Note the
  column order is 00, 01, 10, 11 — binary value order, NOT loop order.

               curr →    00     01     10     11
     prev ↓            ┌──────┬──────┬──────┬──────┐
        00   (idx  0–3)│   0  │  +1  │  −1  │   ✗  │
                       ├──────┼──────┼──────┼──────┤
        01   (idx  4–7)│  −1  │   0  │   ✗  │  +1  │
                       ├──────┼──────┼──────┼──────┤
        10   (idx 8–11)│  +1  │   ✗  │   0  │  −1  │
                       ├──────┼──────┼──────┼──────┤
        11  (idx 12–15)│   ✗  │  −1  │  +1  │   0  │
                       └──────┴──────┴──────┴──────┘

  Diagonal ✗ cells:   3,  6,  9, 12      illegal, count them
  The +1 cells:       1,  7, 14,  8      the forward loop
  The −1 cells:       4, 13, 11,  2      the same loop, reversed
  The 0 diagonal:     0,  5, 10, 15      no change
```

Check it against the forward loop before you trust it. Forward is `00 → 01 → 11 → 10 → 00`, which in
indices is 1, 7, 14, 8 — and every one of those four entries is `+1`. Backward is the same four
transitions reversed: indices 4, 13, 11, 2, and every one of those is `−1`. If your table does not
pass that check, it is wrong.

Entries marked ✗ are **illegal transitions** — two bits changed at once, which physically cannot
happen in one step. They mean you missed an edge. Note *which* four they are: `00 → 11`, `01 → 10`,
`10 → 01`, `11 → 00` — the diagonals of the loop, each one a jump to the opposite corner. Counting
them is free diagnostics: keep a `missedCount` and watch it while you spin the shaft fast.

> **DEFINITION** — "Forward = `00 → 01 → 11 → 10`" is a **definition, not a fact**. Whether it corresponds
> to clockwise or counter-clockwise depends on which motor wire you called A. You will verify this
> empirically below, and if it is backwards you negate the table — **in one place, with a comment**.
> Never compensate for a sign error downstream; that is how you end up with three sign errors that
> cancel until the day they do not.

**Interrupt load — do this arithmetic, it justifies the code style.**

```
Output at 100 RPM  = 1.667 rev/s
Motor shaft        = 1.667 × 300 = 500 rev/s      [P]
Edges per motor rev = 28
Interrupt rate      = 500 × 28 = 14,000 per second [P]
Average gap between edges = 1 / 14,000 = 71 µs
```

`[P]` — provisional, because it scales directly with the unverified gear ratio. At 250:1 the
interrupt rate is 11,700/s; at 100:1 it is 4,700/s. Redo this line with your measured ratio; the
*conclusion* (read the port register, not `digitalRead`) holds at every plausible ratio, but the
percentage you quote in an interview should be one you actually computed.

An `attachInterrupt` handler costs roughly 3 µs in entry and exit overhead alone on a 16 MHz AVR.
A table lookup and an increment adds maybe 2 µs. Call it 5 µs:

```
14,000 × 5 µs = 70 ms per second = 7 % of your CPU
```

Acceptable. Now put two `digitalRead()` calls in the handler — each costs around 3.6 µs — and you are
at 12 µs, or **17 %**, for no benefit. Read the port register directly instead. This is the concrete
version of the guide's "keep the ISR to a table lookup," and now you know what it costs.

### The logic analyzer, since this is the first capture

You will use this instrument in six sessions across two stages and "probe A and B" is not an
instruction. Three settings and one wiring rule, and then it is genuinely easy.

**Sample rate.** A digital sampler only knows what a signal was doing at each sample instant. Too slow
and you miss transitions entirely, which shows up as a waveform that looks plausible and is wrong — a
signal *appearing* to run at some other frequency because you sampled it at the wrong times. The rule
of thumb is **at least ten samples per period of the fastest edge you care about**; the hard floor is
two, which is Nyquist, and two is nowhere near enough for reading a digital waveform's shape.

Your 24 MHz analyzer against the signals in this project:

```
   31 kHz PWM  (S11)           24 MHz / 31.4 kHz  =  765 samples per period ✓
   20 kHz PWM  (Stage 1)                          = 1200 per period        ✓
   1 kHz loop tick (S1.4)                         = 24,000 per tick        ✓
   500 kbit/s CAN bit (S1.6)   24 MHz / 500 kHz   =   48 samples per BIT   ✓
   encoder edges at 14,000/s   (S3)               = ~1,700 per edge gap    ✓
```

Comfortable everywhere — but **capture time is sample rate × channels × duration**, so 24 MHz on eight
channels for ten seconds is a lot of memory. Drop the rate to what you need. For the loop-rate capture
in S5 you are measuring a 10 ms period; 1 MHz gives you microsecond resolution and a tenth of the data.

**Triggering.** Left alone, the analyzer starts capturing when you press the button, which is fine for
a signal that repeats forever and useless for anything that happens once. Set a trigger — "start
capturing on the rising edge of channel 0" — and you get the event rather than a random window of it.
You will want this the first time you look for the *first* PWM pulse after a step command.

**Ground.** The analyzer has a ground lead and it is not optional. It has no idea what "high" means
without a reference, and a floating ground gives you a capture full of transitions that are not on the
wire. Ground it to your star point, not to a convenient random pin.

> **CHECK YOURSELF** — You want to measure the *duty cycle* of your 490 Hz PWM to within 1 %. What
> sample rate do you need, and why is that a different question from measuring its frequency? Work it
> out before you set the dial — the answer is the difference between resolving the period and resolving
> the edge inside it.

### Build

Motor power **disconnected**. Encoder only. You are turning the shaft by hand this session.

- Encoder A → D2, encoder B → D3, VCC → 5 V, GND → the star ground point.
- Route the encoder wires **away** from where the motor wires will run. Not parallel to them, and
  not in the same bundle. You are establishing the habit now, while nothing is switching.

### Code — skeleton

```cpp
// encoder.h  — S3
#pragma once
#include <Arduino.h>

class Encoder {
public:
  void begin(uint8_t pinA, uint8_t pinB);   // set pins, attach both ISRs, seed state_
  long  count() const;                       // atomic read of count_ (see note below)
  long  missed() const;                      // illegal-transition counter
  void  zero();                              // reset count_ to 0

  void  onEdge();                            // called from BOTH ISRs. Keep it tiny.

private:
  volatile long  count_  = 0;
  volatile long  missed_ = 0;
  volatile uint8_t state_ = 0;               // (A<<1)|B, previous
  uint8_t pinA_ = 0, pinB_ = 0;

  static const int8_t kTable[16];            // the table you derived above
};
```

Three things the skeleton is deliberately not telling you, which you must work out:

1. **Reading the pins fast.** `digitalRead()` is too slow. On the UNO, D2 and D3 are both on PORTD,
   bits 2 and 3, so one read of the input register `PIND` gets you both at once.

   `PIND` is a byte in which **bit *n* is the current level of PORTD pin *n***, so bit 2 is D2 and
   bit 3 is D3 — you want those two bits, moved down to the bottom of a byte, with everything else
   removed. That is one shift and one mask, in that order, and working out which shift and which
   mask is the exercise. Check your answer against the truth rather than against your reasoning:
   print the value while you turn the shaft slowly by hand, and confirm it only ever takes the four
   values you expect and never the other twelve.

   **Where this comes from, if you want it from the source:** the ATmega328P datasheet, section
   *I/O Ports*, has the register description for `PIND` and the port/pin map; the Arduino UNO
   schematic maps header pin D2 to the chip's PD2. Neither is required reading to get this working,
   and both are the difference between knowing it and having been told it.

   Note also what this buys you: no function call, no pin-number lookup table, no timer check. That
   is the 3.6 µs per `digitalRead()` you costed two pages up, and this is where it goes.
2. **Reading `count_` safely from `loop()`.** It is a `long` — four bytes — and the AVR is 8-bit, so
   a read can be interrupted halfway through and return two bytes of the old value and two of the
   new. This is a **torn read**. The fix is to disable interrupts for the duration of the copy.
   Look up `noInterrupts()` / `interrupts()`, and note that `count()` is `const` but must still do
   this.
3. **Attaching two ISRs to one object.** `attachInterrupt` takes a plain function pointer, not a
   member function. The usual pattern is a file-scope pointer to the single instance and two thin
   free functions that call through it. Write it; it is four lines and worth understanding.

> **DEFINITION** — **`volatile`, and why it is not the same problem as a torn read.** `volatile` tells the
> compiler that a variable can change through means it cannot see — an interrupt, in this case — so it
> must not cache the value in a register or optimise the read away. Without it, `while (count_ == 0)
> {}` can compile into an infinite loop, because the compiler proves nothing in that loop modifies
> `count_`. What `volatile` does **not** give you is atomicity: it guarantees the read happens, not
> that it happens all at once. A four-byte `long` on an 8-bit AVR still takes four instructions to
> read, and an interrupt can land between any two of them. That is the torn read, and the fix is
> `noInterrupts()`, not `volatile`. You need both, for two different reasons.

> **DEFINITION** — **Why a member function cannot be a function pointer.** A non-static member function
> needs to know *which object* it is operating on — that hidden `this` argument has to come from
> somewhere, and a plain `void(*)()` has nowhere to put it. So the signature genuinely does not match,
> and no amount of casting makes it safe. The standard workaround is a file-scope pointer to the one
> instance plus a free function that supplies `this` explicitly. The concept is worth naming because
> you will meet it again everywhere C callbacks meet C++ objects, including in the HAL in Stage 1.

> **DEFINITION** — **`const` on a method that disables interrupts, and RAII.** `count()` is `const`
> because it does not change the *logical* state of the encoder — the caller's view of the object is
> unchanged. Disabling and re-enabling interrupts is not a change to that state; it is a change to the
> machine, briefly. The pattern to reach for is **RAII** — *resource acquisition is initialisation* — a
> small object whose constructor saves and clears the interrupt flag and whose destructor restores it.
> The point is that it restores on *every* exit path, including an early `return`, which a hand-written
> `interrupts()` at the bottom of the function does not. Four lines, and it is the same idea as a lock
> guard in any language you already know.

> **LOOK THIS UP** — Watch the **Curio Res** series on reading DC motor encoders on Arduino before you
> write this (search "Curio Res encoder Arduino"). It is the clearest walkthrough of exactly this
> problem, including the ISR discipline. Watch it *after* you have derived the table above, so you
> are checking your reasoning rather than copying.

### Draw this

**The sixteen-entry table, in your own handwriting, before you type the array.** Not copied from the
page above — rebuilt. Write the four loop states down the side as *binary values* (0, 1, 3, 2, in that
order, and notice that it is not 0,1,2,3), the same four across the top, and fill in every one of the
sixteen cells from the rule "one bit changed forward = +1, one bit changed backward = −1, two bits
changed = illegal, no bits changed = 0."

Then check it three ways before you trust it, because this is the table everything downstream stands
on: the four forward transitions must be `+1`, the four reverse ones `−1`, and the four diagonals `✗`.
If any cell disagrees with FIGURE III.S3.2, work out which of you is wrong before you move on — and it
will not always be you.

Underneath, draw the two waveforms for **your** convention with the state written under each interval,
and mark which channel moves first. Photograph the page.

> **CHECK YOURSELF** — Cover the table and answer one question: index 9 is `10 → 01`. Both bits changed,
> so it is illegal — but *why* can both bits not change in one step, physically? If your answer is
> "because the table says so" you have memorised it. If it is about two sensors ninety degrees apart on
> a rotating disc, you have understood it, and you will recognise a real one when `missed()` starts
> climbing.

### Prove it — three tests, in order

1. **Slow, by hand — and note that this is a *measurement*, not yet a test.** Turn the shaft ten
   output revolutions and divide. That number **is** your counts-per-output-revolution, so it cannot
   also be the thing you check it against; ~8,400 `[P]` is a hypothesis you are testing, not a pass
   mark. What you *can* check right now is that the sign is consistent and that ten turns gives ten
   times what one turn gave. Once you have your figure `C`, the acceptance test from here on is
   "ten turns reads 10 × `C` ± 30" — restate it that way in your notes and use it in every later
   session.
2. **Return to zero.** Turn ten revolutions forward, then ten back. You should land within a handful
   of counts of zero. **This one is a real test**, and it is the important one, because it does not
   depend on knowing `C` at all — losing counts shows up as a mismatch whatever the ratio turns out
   to be. If you land 3,000 short, you are losing counts.
3. **On the analyzer.** Probe A and B while turning. Confirm you see two square waves offset by
   ninety degrees, and confirm that when you reverse direction the lead swaps. Save the capture.

Then finish **S1**: ten turns, read the count, divide by ten. Write the number in `docs/motor-spec.md`.

### What will go wrong

- **Count drifts one way when you turn forward and back.** Missing edges. Check `missed()`. Usually
  `digitalRead()` in the ISR, or you are only interrupting on one channel.
- **Count jumps wildly.** Grounding, or the encoder wires are next to something noisy. Not yet the
  motor, so look at your ground first.
- **Count runs backwards.** Negate the table. One place. Comment it.
- **Count is exactly ¼ or ½ of expected.** You are doing ×1 or ×2 decoding — only one channel is
  interrupting, or you are only handling `RISING`. Both channels, `CHANGE`.

**Capture the broken state.** The count drifting one way after ten turns out and ten turns back,
with `missed()` visibly non-zero beside it. Photograph the serial monitor **before you touch the
ISR**. Those two numbers together — a count that should be near zero and is not, and a
missed-transition counter explaining exactly why — are the clearest single frame this stage
produces, and they exist only while the bug does.

### Artifacts

- **`docs/sessions/quadrature/README.md`** — written at the end of the session, not the
  start. Three to five bullets on what actually happened, what the objective did not predict,
  and what you got wrong first. See [the template](../sessions/_TEMPLATE.md).
- PulseView capture of A/B forward and reverse → `docs/tuning/plots/`.
- `docs/derivations/2026-xx-xx-quadrature-table.jpg` — the 16-entry table in your handwriting.
- Measured counts/rev committed to `docs/motor-spec.md`.
- **Site:** the two waveform captures side by side, forward and reverse. It is the most legible
  possible illustration of what quadrature means.
  **The shot:** two stills, and they only work as a pair. Same time base, same zoom, same channel
  order, exported from PulseView rather than photographed off the screen. The A and B labels must
  be readable and the lead swap must be visible without a caption — if a reader has to be told
  which one is forward, the two captures are at different scales and you should re-export them.

---

## S4 · Open loop — making it turn, in both directions

**Goal:** a signed command from −255 to +255 produces proportional speed in the right direction, and a
positive command makes the count go **up**.

**You will be able to:** explain what an H-bridge does with two direction pins and one PWM pin, predict your controller's steady-state error from a measured deadband before you ever close the loop, and defend your chosen loop rate against your PWM frequency.

### Concept

The H-bridge is a power amplifier. Your microcontroller can source about 20 mA at 5 V; your motor
wants 1,000 mA at 12 V. The TB6612 is the thing in between, and the only interesting thing about it
is that it takes *two* inputs: a direction (two digital pins) and a magnitude (one PWM pin).

Analogy: a light switch that can also dim. `AIN1`/`AIN2` decide which way current flows through the
motor; `PWMA` decides for what fraction of each cycle it flows at all.

> **DEFINITION** — **H-bridge.** Four switches arranged around the load in the shape of the letter H, with
> the motor as the crossbar. Close the top-left and bottom-right pair and current runs one way through
> the motor; close the other diagonal and it runs the other way. That is the whole trick, and it is
> the only way to reverse a brushed DC motor from a single-polarity supply. The TB6612FNG **is** an
> H-bridge — two of them, in fact, which is why it has an A and a B channel. It also explains why
> closing both switches on one side gives you `brake` (the motor's terminals are shorted together, so
> its own back-EMF opposes motion) and why opening all four gives you `coast`. Closing both switches
> on the same *leg* is called shoot-through, is a dead short across the supply, and is the thing the
> chip's internal logic exists to make impossible.

### The math

**1. Duty cycle to average voltage.**

```
V_avg = duty/255 × V_supply
duty = 128 → 0.502 × 12 V ≈ 6.0 V
```

For a DC motor at steady state, speed is roughly proportional to applied voltage minus the drop
across the winding resistance, so `V_avg` is a good first-order proxy for commanded speed. It is not
exact and does not need to be — the feedback loop exists precisely so you do not need an accurate
model.

**2. Deadband — the number you are going to measure.**

A gearmotor with a high-ratio reduction has substantial static friction. Below some duty, the motor makes
noise and does not move. Measuring this is the point of the session:

```
duty:   10  20  30  40  50  60  80  100 ...
moves?   n   n   n   y   y   y   y   y
```

Your deadband is somewhere in that transition. **Write the whole sweep into
`docs/tuning/deadband.md` as you take it** — every duty you tried and whether it moved, not just
the threshold you conclude. The table is what lets you plot speed against duty afterwards and read
the deadband off the x-intercept, and it takes ten seconds to record and an evening to re-take. It
is the reason a P-only controller
in S8 will sit stubbornly a degree or two short of target and refuse to close the gap: the
controller *is* commanding a correction, but the correction is smaller than the deadband, so nothing
happens. Knowing the number in advance turns S8's "steady-state error" from a mystery into an
observation.

**3. Choosing your loop rate — derive it now, use it in S5.**

`analogWrite()` on the UNO gives you PWM at **490 Hz** on D9. A control loop should not update the
duty cycle faster than the motor can respond to it, and the practical rule is at least five PWM
periods per control tick:

```
PWM period       = 1 / 490 Hz     = 2.04 ms
Loop period ≥ 5 × 2.04 ms          = 10.2 ms
Loop rate  ≤ ~98 Hz
```

**So Stage 0 runs at 100 Hz — a 10,000 µs period.**

Notice that 100 Hz is very slightly *over* the bound you just derived: a 10 ms tick contains 4.9 PWM
periods, not 5. That is deliberate and you should be able to defend it. The "five periods per tick"
figure is a rule of thumb about letting the motor's current settle between duty updates, not a
threshold with a cliff on the far side of it; 4.9 versus 5.0 is two percent, and 100 Hz has the
practical virtue of making `dt` exactly 0.01 s, which keeps every hand-check of your integral and
derivative terms in round numbers. If you would rather be strictly inside the bound, 90 Hz
(11,111 µs) is fine and nothing else in this workbook changes. **Pick one, write down which and why —
that reasoning is worth more than either answer.**

> **WATCH OUT** — The commonest way a control loop ends up running at a rate its author cannot justify
> is a timing constant copied out of one context into another. `DT_US = 2000` is the right answer for
> a 500 Hz loop on 31 kHz PWM, which is what you will have after S11 — and it is the wrong answer
> here, where `analogWrite` gives you 490 Hz and the loop must be five PWM periods slower than that.
> The two statements are individually true and mutually contradictory, and nothing in the code will
> tell you so. Use **10,000 µs** now, change it deliberately in S11, and write the reason next to the
> constant both times.

In S11 you will reconfigure Timer1 to 31 kHz and *then* 500 Hz becomes available, and you will be
able to hear and measure the difference. On the STM32 in Stage 1, with a 20 kHz timer, 1 kHz is the
right answer.

### Draw this

**The H-bridge, as four switches, twice.** One rectangle with the motor as the crossbar, four switches
labelled by position, and the current path drawn as an arrow through the motor — then the same drawing
again with the *other* diagonal closed and the arrow reversed. That is the entire trick and drawing it
once means you will never again wonder why reversing a brushed motor needs four transistors.

Then add two more states on the same page: **brake** (both switches on one side closed, motor terminals
shorted) and **coast** (all four open). Mark, on the brake drawing, where the back-EMF current flows —
because that is why shorting a spinning motor stops it, and it is the same physics you will meet again
in Stage 5.

Finally, mark the pair that must **never** close together, and write "shoot-through" beside it. Your
TB6612 makes it impossible in silicon; knowing what it prevented is the point.

**Second drawing: your deadband, plotted.** Duty on the x-axis, "did it move" on the y — and once you
have swept it, go back and plot *speed* against duty for the values above the threshold. You get a line
that does not pass through the origin, and the x-intercept is your deadband. That plot is a
characterisation of your plant and it is what makes S8's steady-state error a prediction rather than a
surprise.

### Build

- `PWMA` → D9, `AIN1` → D7, `AIN2` → D8, `STBY` → D4.
- TB6612 `VCC` → 5 V (logic), `VM` → 12 V (motor), `GND` → star ground.
- `AO1`/`AO2` → the two thick motor wires.
- Encoder stays connected from S3.

> **WATCH OUT** — `STBY` low means the driver ignores everything and the motor does not move. It catches
> nearly everyone once, and the symptom — a faint hum, no rotation — looks identical to insufficient
> supply current. Drive it HIGH in `setup()` and check it first when nothing happens.

### Code — skeleton

```cpp
// motor.h  — S4
#pragma once
#include <Arduino.h>

class Motor {
public:
  void begin(uint8_t pwmPin, uint8_t in1, uint8_t in2, uint8_t stby);

  // cmd in [-255, +255]. Sign selects direction, magnitude sets duty.
  // Clamps internally. Positive cmd MUST make Encoder::count() increase.
  void write(int16_t cmd);

  void coast();     // both inputs low  — motor free-wheels
  void brake();     // both inputs high — motor terminals shorted
  void enable(bool on);   // STBY

private:
  uint8_t pwm_ = 0, in1_ = 0, in2_ = 0, stby_ = 0;
};
```

Decide deliberately, and write the decision in `docs/decisions/`: **does zero command mean coast or
brake?** They behave very differently under a control loop. Coasting means the arm drifts down under
gravity when the command is zero; braking means it resists. There is no universal right answer, and
having reasoned about it is exactly the kind of thing an interview probes.

### Prove it

1. Command +100. The motor turns and **the count increases**. If it decreases, swap `AIN1` and
   `AIN2` in software — one place, commented — rather than swapping the wires or negating the
   encoder.
2. Command −100. It turns the other way and the count decreases.
3. Sweep duty from 0 upward in steps of 10 and record where motion starts. That is your deadband
   table.
4. **Re-measure the 5 V rail with the motor running.** Compare to your S2 idle figure. A rail that
   reads 5.00 V idle and 4.4 V under load explains almost every "random" reset you will ever see.

### What will go wrong

- **Hums, does not turn.** `STBY` low, or the current limit on your buck is set too low, or the duty
  is under the deadband.
- **Turns one way only.** `AIN1`/`AIN2` not both wired, or one is stuck.
- **Whines audibly.** That is 490 Hz PWM in the audible band. It is correct, it is annoying, and
  S11 fixes it.
- **UNO resets when it starts.** Back to S2. Bulk capacitance, rail split, star ground.

**Capture the broken state.** Three seconds of video of the motor humming and not turning, with
`STBY` still low. It is a sound rather than a picture, which is precisely why a clip beats a
screenshot here — and it is the failure that catches nearly everyone once and looks identical to
insufficient supply current.

### Artifacts

- **`docs/sessions/open-loop/README.md`** — written at the end of the session, not the
  start. Three to five bullets on what actually happened, what the objective did not predict,
  and what you got wrong first. See [the template](../sessions/_TEMPLATE.md).
- `docs/tuning/deadband.md` — the duty/moves table and the threshold.
- Photo of the assembled rig → `hardware/wiring/`.
- **Site:** short video of the shaft turning both ways. First motion is worth showing.
  **The shot:** one clip, 8 to 12 seconds, landscape, one take. Command +100, let it run, command
  −100. **The shaft and the serial monitor's count must be in frame together** — the shaft alone
  is a motor spinning, and the point is that the sign of the number agrees with the direction of
  the shaft.

---

## S5 · The fixed-rate loop, and proving your rate

**Goal:** a control loop that executes at exactly 100 Hz, and an instrument capture that proves it.

**You will be able to:** explain why `next += period` and `next = now + period` are different equations, why the signed-difference comparison survives a counter rollover, and prove your loop rate on an instrument rather than asserting it.

### Concept

In application programming, "fast enough" is a performance concern. In control, timing is part of
the mathematics: the integral and derivative terms are both *defined* in terms of elapsed time. A
loop running at an inconsistent rate does not compute a slightly worse answer. It computes a
different equation.

Analogy: a metronome. A drummer playing to a metronome that wanders is not slightly off — the whole
piece is wrong, and no amount of practising the individual notes fixes it.

```
FIGURE III.S5.1 — What jitter looks like, and where it comes from

  IDEAL — every period identical
    ┌──┐        ┌──┐        ┌──┐        ┌──┐        ┌──┐
  ──┘  └────────┘  └────────┘  └────────┘  └────────┘  └──── idle
    ├─── 10,000 µs ──┤   exactly, every time

  REAL — with encoder ISRs and one slow telemetry write
              ▌           ▌                 ▌
    ┌──┐      ▌ ┌──┐      ▌ ┌──┐┌───────┐  ▌┌──┐        ┌──┐
  ──┘  └────────┘  └────────┘  └┘telemet└───┘  └────────┘  └──
                                              ▲
    ▌ = encoder ISR (fires whenever the shaft moves — you do not
        control when)                         │
                        this iteration started late. That is JITTER.

  Latency = how long after an event you respond.
  Jitter  = how much the START of your loop moves around.
  For control, jitter hurts more: it corrupts dt, and dt is in the maths.
```

### The math — why `next += period`

Two ways to schedule the next tick:

```
(A)  next = micros() + PERIOD;    // reset from now
(B)  next += PERIOD;              // advance the schedule
```

(A) accumulates drift. If the body of the loop takes 300 µs and you then schedule from *now*, your
actual period is 10,300 µs. Over a minute you have lost 180 ticks, and your `dt` constant is a lie by
3 %. (B) advances an absolute schedule: a tick that runs late is followed by one that runs early, and
the *average* period stays exactly 10,000 µs.

The comparison also matters:

```
if ((int32_t)(micros() - next_us) < 0) return;   // correct
if (micros() < next_us) return;                  // breaks after 71 minutes
```

`micros()` overflows a `uint32_t` roughly every 71.6 minutes. The signed-difference form handles the
wraparound correctly; the direct comparison does not, and it fails once, in an hour, in a way that
looks like the universe playing a joke on you.

### Draw this

**Predict your own jitter before you measure it.** Draw the timeline of one second of loop ticks as you
expect it to look: the ideal 10 ms grid, and then your prediction of where reality departs from it.
Mark what you think the *sources* are — encoder ISRs firing at 14,000 per second, the serial write you
have not added yet, `millis()` housekeeping — and put a number on how big you think each one is.

Then capture it and lay the capture beside your drawing. **The value is entirely in having committed to
a prediction**: if the measured jitter is far smaller than you guessed, you have learned that ISRs are
cheaper than they feel; if it is far larger, you have found something and you knew to look.

Then one more sketch, which is the whole content of `next += period`: draw ten ticks under the drifting
scheme and ten under the absolute one, with a body that takes 300 µs. After ten ticks the two schedules
are 3 ms apart, and after a minute they are 180 ticks apart. Seeing the two lines diverge on paper is
what makes a two-character difference feel like a two-character difference that matters.

### Code — skeleton

```cpp
// main.cpp  — S5
static const uint32_t DT_US = 10000;          // 100 Hz. Chosen, derived in S4.
static const float    DT_S  = DT_US / 1e6f;

uint32_t nextUs = 0;      // seeded in setup(), NOT here — see below
uint32_t overruns = 0;

void setup() {
  // ... pin modes, encoder.begin(), motor.begin(), Serial.begin() ...
  nextUs = micros();      // ← the schedule starts NOW. Without this line the
                          //   first comparison is against 0, and micros() has
                          //   already passed 0, so the loop free-runs at full
                          //   speed until micros() wraps 71 minutes later.
}

void loop() {
  if ((int32_t)(micros() - nextUs) < 0) return;   // not yet
  nextUs += DT_US;                                 // advance schedule, no drift

  // TODO: if we are already past nextUs again here, the previous tick overran.
  //       Count it. An overrun you do not count is an overrun you will not find.

  digitalWrite(SCOPE_PIN, HIGH);                   // ← rising edge = tick start

  long  pos = encoder.count();                     // SENSE
  int16_t u = 0;                                    // THINK  (S8 onward)
  motor.write(u);                                   // ACT

  digitalWrite(SCOPE_PIN, LOW);                    // ← falling edge = tick end
}
```

The scope pin gives you two numbers at once on the analyzer: the **period** (rising edge to rising
edge, should be 10.000 ms) and the **execution time** (high duration, should be a small fraction of
it). The second is your headroom, and you will watch it grow as you add telemetry in S7.

### Prove it

Analyzer on `SCOPE_PIN`. Capture a few seconds. Measure the period. You are looking for 10.00 ms with
jitter well under 100 µs.

> **CHECK YOURSELF** — Loops that quietly run at half their intended rate are extremely common, and every
> gain you tune against the wrong rate is wrong. Do not proceed to S8 on the assumption that your
> loop rate is what you wrote in the constant. Measure it, save the capture, and write the measured
> figure — not the intended one — at the top of your tuning log.

### What will go wrong

- **Period is 10 ms but the high time is nearly 10 ms too.** Something in the loop is blocking.
  Almost always `Serial.print`, or a `delay()` that survived from an earlier sketch.
- **Period is erratic.** Interrupt load. Spin the motor fast and watch the jitter grow — that is your
  encoder ISR, and now you can *see* the 7 % from S3.
- **Nothing toggles.** The early-return is firing every time because `nextUs` was never seeded.

**Capture the broken state.** The analyzer capture where the period is erratic, or where the high
time nearly fills the period. **That trace is the argument for the session.** A flat 10.000 ms
capture proves you got there; the ragged one proves there was somewhere to get from, and only one of
the two is still available to you afterwards.

### Artifacts

- **`docs/sessions/fixed-rate-loop/README.md`** — written at the end of the session, not the
  start. Three to five bullets on what actually happened, what the objective did not predict,
  and what you got wrong first. See [the template](../sessions/_TEMPLATE.md).
- Analyzer capture of the loop pin → `docs/tuning/plots/2026-xx-xx-loop-rate.png`.
- **Site:** this capture, with the caption naming the measured period. "I can prove my loop rate" is
  a sentence very few hobby projects can say.
  **The shot:** one still: the analyzer's own screenshot with the period measurement annotation
  switched on, so the figure is on the image rather than in the caption. Export it; do not
  photograph the monitor.

---

## S6 · Units — convert once, at the boundary

**Goal:** the controller thinks in radians and never sees a raw count.

**You will be able to:** state how many encoder counts correspond to one degree on *your* motor and show the arithmetic, and say what one count of position quantisation costs you in the derivative term.

### Concept

The most common category of bug in this whole project is not a logic error. It is a unit error — a
number correct in one system being used as though it were in another. Robot code is a chain of
conversions from counts to physics, and every link is a chance to be wrong by a factor of 4, or 2π,
or 57.3.

The discipline is one you already have from application code: parse untrusted input at the edge of
the system and work with validated types internally. Same rule, with physics attached.

### The math — your chain, with your numbers

```
FIGURE III.S6.1 — The conversion chain, both directions

SENSING
  raw count           ──► × RAD_PER_COUNT ──► radians at the output shaft

  RAD_PER_COUNT = 2π / COUNTS_PER_OUTPUT_REV
                = 6.283185 / 8400            (← 8400 is PROVISIONAL [P].
                                              Substitute YOUR measured number.)
                = 7.4800 × 10⁻⁴ rad/count

COMMANDING
  PID output (unitless) ──► clamp to ±1.0 ──► × 255 ──► duty + sign ──► volts
```

Now derive the resolution consequences, because they matter in S10:

```
Position quantum   = 7.48 × 10⁻⁴ rad = 0.0429°
Velocity quantum   = 1 count per tick / 0.01 s
                   = 7.48 × 10⁻² rad/s = 4.29 °/s
```

That second number is why derivative action amplifies noise. Velocity is computed as a difference of
two quantised positions, so it can only ever take values that are multiples of 0.0748 rad/s. With
`Kd = 0.1`, one count of jitter produces a command wobble of 0.0075 out of ±1.0 — three quarters of
one percent, appearing and disappearing every tick. That is audible as a buzz, and it is not a bug.

> **WATCH OUT** — Degrees are for humans and for printing. Radians are for mathematics. Pick radians
> internally and convert only at the display boundary. Mixing them produces a loop that is wrong by
> a factor of 57.3 and behaves exactly as though the gains were wildly miscalibrated.

### Code — skeleton

```cpp
// units.h  — S6
#pragma once

// Measured in S1/S3. Not copied from any document, including this one.
constexpr float COUNTS_PER_OUTPUT_REV = 8400.0f;   // ← replace with YOUR figure
constexpr float RAD_PER_COUNT         = 6.2831853f / COUNTS_PER_OUTPUT_REV;
constexpr float RAD_TO_DEG            = 57.2957795f;

inline float countsToRad(long c)  { return c * RAD_PER_COUNT; }
inline long  radToCounts(float r) { return (long)(r / RAD_PER_COUNT); }
```

> **DEFINITION** — **`constexpr` rather than `#define`, and why the header can hold it.** `#define` is a
> textual substitution performed before the compiler sees your code: it has no type, obeys no scope,
> and produces error messages that point at the expansion rather than the mistake. `constexpr` is a
> real, typed constant that the compiler evaluates at compile time — same zero runtime cost, but
> `RAD_PER_COUNT` is now a `float` that the type system knows about. It also means the *derivation*
> stays in the source: `6.2831853f / COUNTS_PER_OUTPUT_REV` is computed for you, so changing one
> number after S3 updates everything downstream and there is no second constant to forget.
>
> A **translation unit** is one `.cpp` file plus everything it includes, compiled as a single lump. A
> header gets pasted into every unit that includes it, which is why a header containing a definition
> normally causes duplicate-symbol errors at link time — and why `constexpr` and `inline` are safe
> there and a bare global variable is not. This is the rule that decides what goes in `units.h` versus
> `units.cpp`, and it is worth knowing before it bites you in S12.

> **DEFINITION** — **Your PID gains have units.** `Kp` is "command units per radian of error." If you later
> change the decoding mode, the gear ratio, or your angle units, every gain you tuned is now wrong by
> the same factor. Write the units in the comment next to each gain. This costs nothing and saves an
> afternoon.

### Draw this

**The conversion chain, by hand, with your own measured numbers on every arrow** — not the provisional
ones. One page: counts in at the left, radians at the output shaft, and back out the other side through
the clamp and the ×255 to volts at the motor. Write the *units* on every arrow, not just the numbers.

Pin it above the bench. It is the page you will look at every time a value comes out wrong by a factor
you half-recognise, and the whole point of drawing it rather than reading it is that you will remember
where the factors of 4 and 2π live.

> **CHECK YOURSELF** — Without looking: how many counts is one degree on your motor? Show the
> arithmetic. Then answer the harder one — if you swapped to a motor with twice the gear ratio and
> changed nothing else, which of your PID gains would be wrong, and by what factor?

### What will go wrong

- **Everything is out by 57.3.** Degrees where radians belong, or the reverse. It presents as gains
  that are wildly too large or too small rather than as a unit error, which is why it costs an evening.
- **`radToCounts()` rounds toward zero, so small negative targets become 0.** `(long)(-0.4)` is `0`,
  not `-1`. Harmless here and a real asymmetry once you are commanding small moves in both directions;
  decide deliberately whether you want truncation or rounding, and write which.
- **You change `COUNTS_PER_OUTPUT_REV` and forget the gains moved with it.** `Kp` is command per
  *radian*, and radians per count just changed. This is the same trap the appendix at the end of this
  workbook lists as item 4, and it is the one people miss.
- **The constant is right and the answer is still wrong by four.** You are dividing by PPR and then
  also by the decode factor, or by CPR and then also by 4. It is one or the other, never both — the
  Project Guide's FIGURE II.6 marks exactly this.

**Capture the broken state.** The serial monitor printing 22.5 or 360 when you turned the shaft a
quarter turn. Screenshot it next to the number you predicted. A unit error is invisible in code and
obvious in one line of output, and that contrast is the entire point of this session.

### Prove it

Command nothing. Turn the shaft by hand to what looks like 90° and print the computed angle in
degrees. **Predict what it will print before you run it**, given your measured counts/rev. It should
read approximately 90. If it reads 22.5, you are running ×1 decoding. If it reads 360, your
counts-per-rev is a quarter of what it should be.

### Artifacts

- **`docs/sessions/units/README.md`** — written at the end of the session, not the
  start. Three to five bullets on what actually happened, what the objective did not predict,
  and what you got wrong first. See [the template](../sessions/_TEMPLATE.md).
- `docs/derivations/2026-xx-xx-unit-chain.jpg` — the chain, in your handwriting, with your numbers.
- **Site:** this one. It is the clearest possible evidence that you understand what your controller
  is actually computing.
  **The shot:** one still of the whole page. The units on every arrow have to be readable — on
  this page the small writing *is* the content, so fill the frame and use decent light rather than
  relying on a crop.

---

# PART III — CLOSING THE LOOP

---

## S7 · Telemetry that fits — the bandwidth problem

**Goal:** target, position, and command streaming out at the loop rate, captured to CSV, and plotted
— without the act of logging breaking the timing you just proved in S5.

**You will be able to:** budget a serial link in bytes per second against a loop rate, derive a baud rate's error on a 16 MHz AVR from its divisor rather than reading it off a table, and explain why instrumentation is a load that has to be budgeted like any other.

### Concept

You cannot tune what you cannot see. But the naive way of seeing it — printing floats over serial at
the loop rate — is itself slow enough to wreck the loop. This session is where you learn that
instrumentation has a cost and has to be budgeted like anything else.

Analogy: a physicist measuring the temperature of a thimble of water with a thermometer the size of a
brick. The instrument changes the thing it measures.

### The math — the serial budget

Do this arithmetic before you write the logging code. It is the kind of thing that bites at exactly
the wrong moment — mid-tuning, when you are looking for the bug in your gains.

```
A CSV line, integers only:  "123456,4200,4187,145\r\n"  = 22 bytes
   (21 characters plus the line ending — Arduino's println sends
    CR and LF, which is two bytes, and forgetting that is how a
    budget comes out 5 % optimistic)
At 100 Hz:                   22 × 100  = 2,200 bytes/s
At 500 Hz:                   22 × 500  = 11,000 bytes/s

Serial throughput, 8N1 = 10 bits per byte:
  115,200 baud →  11,520 bytes/s
  250,000 baud →  25,000 bytes/s
  500,000 baud →  50,000 bytes/s
```

At **100 Hz you are using 19 % of a 115200 link** — comfortable. At **500 Hz you are at 95 %**, the
64-byte TX buffer fills, and `Serial.write` starts blocking inside your control loop. Your carefully
proven 2 ms period becomes whatever the UART feels like.

Two more facts worth knowing:

- **Baud rate accuracy.** On a 16 MHz ATmega328P, 115200 baud has about **2.1 % error**; 250000 and
  500000 both have **exactly 0 %**. Do not take that on faith — it falls out of one divisor. The
  Arduino core runs the UART in double-speed mode (`U2X = 1`), where the register is

  ```
  UBRR = f_osc / (8 × BAUD) − 1        and UBRR is an INTEGER, so it truncates

  115200 →  16,000,000 / (8 × 115,200) − 1  =  17.361 − 1  =  16.361  →  16
            actual = 16,000,000 / (8 × 17)  =  117,647 baud
            error  = (117,647 − 115,200) / 115,200        =  +2.12 %

  250000 →  16,000,000 / (8 × 250,000) − 1  =   8 − 1     =   7  exact  →  0 %
  500000 →  16,000,000 / (8 × 500,000) − 1  =   4 − 1     =   3  exact  →  0 %
  ```

  The 2.1 % is survivable at 8N1 over a short cable and it is not free — it eats margin you would
  rather spend on cable length and noise. Use **250000**. It is faster, it is exact, and it costs
  nothing. This is a document whose method is *derive, do not read*, so derive this one too.
- **Printing floats is expensive.** `Serial.print(float)` goes through `dtostrf` and costs hundreds
  of microseconds. Send **integers** — counts, milliradians, raw command — and convert on the host,
  where CPU time is free.

> **CHECK YOURSELF** — After adding telemetry, go back and re-capture your loop pin from S5. The high
> time will have grown. If the period is still 10.000 ms, you have budgeted correctly. If it has
> not, you have just learned why this session exists.

### Draw this

**The serial budget, as two bars.** One bar for what your link can carry at each candidate baud rate,
one for what your telemetry demands at each candidate loop rate, drawn to the same scale. Four bars
total and the answer is visible rather than computed — 100 Hz on 115200 fits with room, 500 Hz on
115200 does not.

On the same page, draw **one CSV row as a box divided into its fields**, with the byte count of each
written in and the line ending drawn as its own two-byte box. That drawing is what stops you forgetting
the `\r\n` — it is 9 % of a 22-byte row and it is the reason a budget comes out optimistic.

Then mark where the buffer is. Sixty-four bytes of TX buffer, at 22 bytes a row, is under three rows
of slack. Write that number on the drawing; it is the whole reason blocking happens where it does.

### Code — skeleton, firmware side

```cpp
// telemetry.h  — S7
#pragma once
#include <Arduino.h>

// Emit one CSV row. Integers only — no floats on the wire.
// Called from the control loop, AFTER motor.write(), so logging cost
// is never between sensing and acting.
void logRow(uint32_t tMs, long targetCounts, long posCounts, int16_t cmd);

// Decimation: log every Nth tick. Set to 1 for full rate.
// You will want this the moment you raise the loop rate in S11.
//
// NOTE the `extern`: this DECLARES the variable, it does not create it.
// Exactly one .cpp file must also DEFINE it — `uint8_t logEveryN = 1;` in
// telemetry.cpp — or the linker will tell you the symbol is undefined.
// Put the definition in a header instead and every file that includes it
// gets its own copy and the linker complains about duplicates instead.
// That is the translation-unit rule from S6, and S12 meets it again.
extern uint8_t logEveryN;
```

### Code — skeleton, host side

```python
# tools/capture.py  — S7
"""Read CSV rows from the UNO and write them to a timestamped file."""

import argparse, csv, sys, time
import serial          # pyserial

# TODO:
#  - open the port at 250000 baud
#  - discard the first line (likely partial)
#  - read until KeyboardInterrupt, writing rows to docs/tuning/raw/<date>-<tag>.csv
#  - print a running row count so you can see it is alive
#  - on exit, report: rows captured, elapsed time, and measured rows/sec
#    ^ that last one is a second, independent check on your loop rate
```

```python
# tools/plot.py  — S7
"""Plot a captured run and print its step-response metrics."""

import pandas as pd
import matplotlib.pyplot as plt

# TODO:
#  - load CSV, convert counts -> degrees using COUNTS_PER_OUTPUT_REV
#  - plot target and actual on one axis, command on a twin axis
#  - annotate rise time, overshoot, settling time, steady-state error (see S9)
#  - save to docs/tuning/plots/<date>-run<N>.png at 150 dpi
```

> **LOOK THIS UP** — The Arduino IDE's built-in **Serial Plotter** will draw a live trace with no code on
> the host side at all. It is worth thirty seconds to see your signal moving in real time. It is not
> a substitute for the CSV pipeline — you cannot measure overshoot off a scrolling window, and you
> cannot commit it to the repository — but as a sanity check it is excellent.

### What will go wrong

- **The loop period grows the moment telemetry is enabled.** The TX buffer is full and `Serial.write`
  is blocking inside your control loop. Either the row is too wide, the baud too low, or you are
  printing floats. This is the failure the session exists to produce — capture it before you fix it.
- **The first captured line is garbage.** You opened the port mid-row. Discard the first line; the
  skeleton says so and it is still the commonest reason a plot has one absurd point at t=0.
- **`capture.py` prints nothing and does not error.** Opening the serial port resets the UNO on most
  boards, so the firmware is rebooting as you connect. Wait a second or two after opening before
  expecting data.
- **The CSV loads but every column is a string.** No header row, or a stray partial line in the middle.
  Give the file a header and let pandas name the columns.
- **The plot is empty on a headless or WSL machine.** matplotlib has no display. Save to a file rather
  than calling `show()` — which you want anyway, because a plot you cannot commit is not evidence.
- **Row count is right, timing is wrong.** Rows arriving at the right *average* rate tells you nothing
  about jitter. That is what the scope pin is for, and why *Prove it* below asks for both.

**Capture the broken state.** The loop-pin capture with telemetry enabled and the period blown out —
the one the paragraph above already tells you to take before you fix it. **Take it.** It is the only
evidence that the byte budget was a real constraint rather than an arithmetic exercise, and the
fixed version on its own says nothing at all.

### Prove it

Command a fixed duty in open loop, capture ten seconds, and plot position against time. You should
get a clean ramp. **Before you count them, predict how many rows you expect** — then count: at 100 Hz
over 10 s you want ~1,000. If you have 640, something is blocking, and the ratio tells you roughly
how much.

### Artifacts

- **`docs/sessions/telemetry/README.md`** — written at the end of the session, not the
  start. Three to five bullets on what actually happened, what the objective did not predict,
  and what you got wrong first. See [the template](../sessions/_TEMPLATE.md).
- `tools/capture.py`, `tools/plot.py` committed.
- First CSV in `docs/tuning/raw/`, first plot in `docs/tuning/plots/`.
- Re-captured loop-pin trace showing the period held after telemetry was added.
- **Site:** the open-loop ramp plot. Unglamorous and it proves the whole pipeline works.
  **The shot:** the saved PNG itself, not a screenshot of a window containing it. Both axes
  labelled with units, and the run's date in the filename.

---

## S8 · P only — steady-state error and the stability boundary

**Goal:** a proportional controller. You watch it stop short, and you find the gain at which it
oscillates. Both of those are the point.

**You will be able to:** predict a P-only controller's steady-state error before you run it, tell controller oscillation from gearbox backlash by changing one gain, and say what `Ku` is and why quoting it without the step size is meaningless.

### Concept

Proportional control is the simplest possible feedback: push in proportion to how far off you are.
Far away, push hard. Close, push gently. At the target, push not at all — which is precisely the
problem, because "push not at all" is also what you do when you are stuck one degree short against
friction.

Analogy: a spring. A spring pulls harder the further you stretch it, and it stops pulling when it
reaches its rest length — even if there is a small step in the floor it never quite climbs over.

### The math

```
error  = target − actual                       [radians]
u      = Kp × error                            [unitless, then clamped to ±1]
cmd    = clamp(u, -1, +1) × 255                [driver units]
```

**Kp has units: command per radian.** Work out what value of `Kp` would produce full command at 90°
of error:

```
90° = 1.571 rad
u = 1.0 at error = 1.571 rad  →  Kp = 0.637
```

That is a useful starting order of magnitude, and knowing where it came from beats guessing.

**Why steady-state error is guaranteed.** From S4 you know your deadband — say duty 35 of 255, which
is `u = 0.137`. The controller can only overcome friction when:

```
Kp × error > 0.137
error > 0.137 / Kp
```

With `Kp = 0.637`, that is `error > 0.215 rad = 12.3°`. **Below twelve degrees of error, the
controller is commanding a correction too small to move the motor at all.** Raise `Kp` and the
residual shrinks proportionally — which is exactly why the instinct is to keep raising it, and
exactly why that instinct eventually produces oscillation.

Predict your steady-state error from your own deadband and `Kp` **before** you run it. Then run it.
The agreement, or the lack of it, is more instructive than either number alone.

### Draw this

**The P-only loop, as a block diagram, from memory.** Target into a summing junction, measurement back
into it with a minus sign, error out, one gain block, clamp, motor, encoder, and back round. Six boxes.
You will draw the full version in S10 with I and D on it, and drawing the simple one first is what makes
that one legible rather than intimidating.

Mark on it the **one place the deadband lives** — between the command and the motor actually turning —
and write beside it `error > deadband / Kp`. That inequality is this entire session and having it on the
same page as the loop is what makes it obvious rather than algebraic.

**Second drawing, after the experiment: predicted against measured.** Plot `1/Kp` on the x-axis and
steady-state error on the y, for every gain you ran. Theory says that is a straight line through the
origin with slope equal to your deadband. Draw the theoretical line, plot your points on it, and look at
the fit. Where they diverge — and they will at high gain — you are seeing your plant being non-linear,
which is the thing S8's failure list warns you about and this is the picture of it.

### The experiment

`Ki = 0`, `Kd = 0`. For each `Kp`, command a step from 0° to 90°, capture, plot, and record:

| Run | Kp | Predicted SS error | Measured SS error | Overshoot | Note |
|---|---|---|---|---|---|
| 1 | 0.2 | | | | |
| 2 | 0.5 | | | | |
| 3 | 1.0 | | | | |
| 4 | 2.0 | | | | |
| … | | | | | raise until it oscillates |

The gain at which sustained oscillation begins is your **ultimate gain**, `Ku`. **Write `Ku`, `Tu`
and the step size you used into `docs/tuning/` before you change anything** — the three of them
together, on one line, because any one alone is not a measurement and you will not reconstruct the
step size from memory. You have just characterised your plant empirically, which is what tuning
actually is — and those two numbers are the input to every classical tuning rule, should you want one
later.

**How to measure `Tu`, since "note it" is not an instruction.** It is the period of the sustained
oscillation — peak to peak on the *position* trace, in seconds. You already have two instruments that
give it to you and it is worth using both, because they disagree in an informative way:

- **From the CSV.** Capture ten seconds at `Ku`, plot position against time, and read the time between
  two peaks that are several cycles apart — say five cycles — then divide by five. Dividing by five
  divides your reading error by five, for the same reason ten turns beat one in S1.
- **From the analyzer,** if the oscillation is fast enough to see on the scope pin: it is not, at
  a few hertz, and noticing *why* is the point. Your loop pin toggles every tick regardless of what
  the motor is doing; the oscillation is in the plant, not in the schedule. An instrument that cannot
  see a thing is telling you which layer the thing lives in.

Quote `Tu` in seconds alongside `Ku` and the step size you used. `Ku = 3.2, Tu = 0.4 s, on a 0→90°
step` is a characterisation. Any one of those three alone is not.

> **WATCH OUT** — When it oscillates it will be loud and it will look alarming. That is the experiment
> working. Have the S2 inline switch (FIGURE III.S2.1) in reach, keep the plank clamped (S1), and
> keep your fingers away
> from the shaft — a high-ratio gearbox has far more torque than its size suggests and no sense of
> what it is closing on.

### The math — what `Ku` and `Tu` are actually for

You have just measured two numbers at real cost. Here is the classical rule they feed, so that
measuring them is a payoff rather than homework.

**Ziegler–Nichols**, published in 1942, is the oldest and most quoted tuning heuristic. Given the
ultimate gain `Ku` and the oscillation period `Tu`:

```
   Controller    Kp          Ki                  Kd
   ─────────────────────────────────────────────────────────────
   P only        0.50·Ku     —                   —
   PI            0.45·Ku     1.2·Kp / Tu         —
   PID           0.60·Ku     2.0·Kp / Tu         Kp·Tu / 8

   For your own numbers — say Ku = 3.2 and Tu = 0.4 s:
      Kp = 0.60 × 3.2          = 1.92
      Ki = 2.0 × 1.92 / 0.4    = 9.6
      Kd = 1.92 × 0.4 / 8      = 0.096
```

Note the *units* fall out correctly, which is a check in itself: `Ki` is `Kp/time` and `Kd` is
`Kp×time`, exactly as S6 said gains are dimensioned.

**Now the honest part, because this is a heuristic and not a law.** Ziegler–Nichols is tuned for
*disturbance rejection* and it is famously aggressive — it targets roughly a quarter-amplitude decay,
which means it deliberately produces visible overshoot, often 25 % or more. For a joint that is
supposed to arrive at an angle and stay there, that is usually too hot. Treat it as a **starting
point**, not an answer: it puts you in the right order of magnitude in one step instead of ten, and
then you back `Kp` off and see what you get.

**And here is the exercise that is worth more than either method alone.** In S10 you will tune P, D
and I by hand. When you have, come back and compute the Ziegler–Nichols values from your `Ku` and `Tu`,
plot both step responses on one set of axes, and write down which you preferred and why — in
`docs/decisions/`, because a choice between two named methods with a plot as its
evidence is exactly what that folder is for. **A plot with
"hand-tuned vs Ziegler–Nichols, on my rig" on it is a genuinely strong portfolio artifact** — it says
you know the classical method exists, you applied it, and you had a reason for not using its answer.
Almost nobody does that second half.

> **LOOK THIS UP** — After you have your own `Ku` and `Tu`, and not before, read about **relay
> auto-tuning** — the trick of driving the plant with a bang-bang controller to provoke a sustained
> oscillation and extract `Ku` and `Tu` automatically rather than by hand-sweeping the gain. It is what
> commercial controllers do, it is about thirty lines, and knowing it exists is worth the ten minutes.

### Code — skeleton

```cpp
// pid.h  — S8 (extended in S10)
#pragma once

class PIDController {
public:
  void  setGains(float kp, float ki, float kd);
  void  setOutputLimits(float lo, float hi);
  void  reset();                                  // clears integral_ and prevMeas_

  // dt in seconds. Returns a clamped command in [lo, hi].
  float update(float target, float measured, float dt);

private:
  float kp_ = 0, ki_ = 0, kd_ = 0;                // units: cmd/rad, cmd/(rad·s), cmd·s/rad
  float integral_ = 0;
  float prevMeas_ = 0;                             // measurement, not error — see S10
  float lo_ = -1.0f, hi_ = 1.0f;
};
```

For S8, only the `kp_` term is live. Leave the rest declared and unused; you will fill them in S10.

### What will go wrong

This session deliberately drives the rig into sustained oscillation, so the failures here look
alarming by design. These four are the ones that waste an evening.

- **You mistake gearbox backlash chatter for controller oscillation.** A high-ratio gearbox has free
  play, and near the target the motor can rattle back and forth across it at a frequency set by the
  mechanism rather than by your gains. The tell: **backlash chatter barely changes frequency when you
  change `Kp`, and controller oscillation does.** Sweep the gain and watch the period. If the period
  is constant, you are listening to the gears and `Ku` is further up.
- **`Ku` appears to depend on the step size, and you conclude your measurement is bad.** It does
  depend on step size, and your measurement is fine — that is the plant being **non-linear**. Deadband
  and saturation mean a 90° step and a 10° step do not see the same effective gain. Fix the step size
  for the whole sweep, record what you used, and quote `Ku` alongside it. "Ku = 3.2 on a 0→90° step"
  is a real number; "Ku = 3.2" is not.
- **The rig walks across the desk and you raise `Kp` anyway.** Stop and re-clamp. Every step response
  taken on a plank that moves is measuring the desk as well as the motor, and you will tune against
  a mechanical problem for days. This is the failure S1's *bolt it down* section exists to prevent
  and the one people override because they are mid-experiment.
- **It oscillates from the very first gain you try.** Suspect the loop rate before the gains. A loop
  quietly running at half its intended rate doubles the effective `Ki` and `Kd` and halves your
  stability margin — go back to S5's capture and confirm the period is still 10.00 ms now that
  telemetry is running.

**Capture the broken state.** The oscillation at `Ku`. **Film it.** It is loud, it looks alarming,
and that is the point — a plot of a sustained oscillation is legible to a specialist and a video of
a motor shaking a clamped plank is legible to everybody. Get the plot too, with the period marked,
but the clip is the one that travels.

### Prove it

The session closes when you can produce three things from your own rig:

1. **A plot that never arrives** — a low gain, settling visibly short of target, with the measured
   steady-state error annotated on it and your prediction from the deadband written beside it.
2. **A plot that oscillates** — at `Ku`, with the period marked and `Tu` read off it.
3. **The agreement, or the gap.** Predicted steady-state error against measured, for at least three
   gains. If they track, you understand your plant. If they do not, the discrepancy is the interesting
   result and it usually means the deadband you measured in S4 was measured at a different
   duty-versus-direction than the one the controller is using.

> **CHECK YOURSELF** — At the gain where it oscillates, is the frequency set by your gains or by the
> gearbox? You already know how to tell them apart — sweep the gain and watch the period. Do it, and
> write down which you were listening to, because "it oscillated" is not a measurement and `Ku` is
> wrong if you stopped at backlash chatter.

### Artifacts

- **`docs/sessions/proportional-control/README.md`** — written at the end of the session, not the
  start. Three to five bullets on what actually happened, what the objective did not predict,
  and what you got wrong first. See [the template](../sessions/_TEMPLATE.md).
- `docs/tuning/2026-xx-xx-p-only.md` — the table above, filled in, with `Ku` and `Tu`.
- One plot per run in `docs/tuning/plots/`.
- **Site:** two plots side by side — a low gain that never arrives, and a high gain that oscillates.
  The contrast makes the concept legible to a non-specialist in about four seconds.
  **The shot:** two plots side by side, and **the y-axis limits must be identical on both.**
  Different ranges destroy the comparison silently and it is the one mistake that makes this pair
  worthless. Annotate each with its `Kp`, and mark `Tu` on the oscillating one.

---

## S9 · Step-response metrics — the four numbers

**Goal:** you can look at a plot and read off four numbers, and your plotting script computes them
for you.

**You will be able to:** read rise time, overshoot, settling time and steady-state error off any step response, and explain why overshoot is computed against the settled value rather than against the target.

### Concept

Every control system anyone has ever built is described by the same four quantities. Learning to see
them in a trace is the difference between "it kind of works" and being able to say something precise
about your own machine.

### The math — definitions, exactly

Given a step from 0 to a final value `y_f`:

| Metric | Definition |
|---|---|
| **Rise time** `t_r` | Time from 10 % to 90 % of `y_f`. How fast it moves. |
| **Overshoot** `M_p` | `(y_peak − y_f) / y_f × 100 %`. How much it goes past. |
| **Settling time** `t_s` | Time to enter and *stay inside* a ±2 % band around `y_f`. How long until done. |
| **Steady-state error** `e_ss` | `target − y_f`. Where it ended up instead of where you asked. |

```
FIGURE III.S9.1 — The four numbers, on one trace

   angle
     ▲                        overshoot M_p
     │                         ╭───╮
     │· · · · · · · · · · · · ·╱· · ·╲· · · · · · · · ·    target
     │╌ ╌ ╌ ╌ ╌ ╌ ╌ ╌ ╌ ╌ ╌ ╌ ╱ ╌ ╌ ╌ ╲ ╌ ╌ ╌ ╌ ╌ ╌ ╌ ╌    y_f + 2 %
 y_f ┤· · · · · · · · · · · ·╱· · · · ·╲   ╭────────────   e_ss = target − y_f
     │╌ ╌ ╌ ╌ ╌ ╌ ╌ ╌ ╌ ╌ ╌ ╱ ╌ ╌ ╌ ╌ ╌ ╰──╯╌ ╌ ╌ ╌ ╌ ╌    y_f − 2 %
     │                     ╱
     │                    ╱      the ±2 % band is those two dashed lines,
0.9  ┤· · · · · · · · · ·╱       and t_s ends when the trace is inside
y_f  │                  ╱        BOTH of them and stays there.
     │                 ╱
     │                ╱
0.1  ┤· · · · · · · ·╱
y_f  │              ╱
   0 ┼──────────────┬┬───┬──────────────────┬──────────────► time
     │              ││   │                  │
     │              │└t_r┘                  │
     │              │                       │
     │              └───────── t_s ─────────┘

  The LEFT tick is the step. t_r is bracketed from the NEXT one —
  the 10 % crossing — to the 90 % crossing, because rise time is
  10 % → 90 %. t_s alone is measured from the step, and drawing the
  two brackets from a shared left edge is exactly the confusion
  between rise time and time-to-90 % that this figure exists to avoid.

  y_f is where it SETTLES, not where you aimed. Compute M_p against y_f.
  If you compute it against the target you will flatter yourself.
```

Two traps worth naming. First, `y_f` is the value it actually settles at, **not** the target — if
there is steady-state error those differ, and computing overshoot against the target instead of the
final value gives you a wrong and flattering number. Second, settling time requires it to *stay*
inside the band; a trace that dips in, wanders out, and comes back has not settled at the first
crossing.

The classic trade-off, which you will now feel rather than read: **raising `Kp` reduces rise time and
increases overshoot.** They move in opposite directions and you cannot have both. Every controller you
ever tune is you choosing a point on that curve.

### Draw this

By hand, one page: a generic second-order step response with all four metrics annotated on it,
including the ±2 % band drawn as two dashed lines. Do it from the definitions, not from a copied
image. You will refer back to this drawing more than you expect.

### Build

Extend `tools/plot.py` to compute and print all four for any captured run, and to annotate them on
the saved figure. That function is worth writing carefully once — you will call it dozens of times
in S10.

### What will go wrong

- **Your overshoot figure is flattering and you do not notice.** You computed it against the target
  instead of against `y_f`. With steady-state error present those differ, and the error is always in
  the direction that makes your controller look better. This is the trap the figure exists to name and
  it is still the one people write into the script.
- **Settling time comes out absurdly short.** You took the first crossing into the ±2 % band rather
  than the last exit from it. A trace that dips in, wanders out and comes back has not settled at the
  first crossing — search backwards from the end of the trace instead of forwards from the step.
- **Rise time is negative, or `NaN`.** The 10 % and 90 % crossings were found by scanning the whole
  trace for the first sample past each threshold, and the overshoot peak crossed 90 % on the way back
  down too. Bound the search to before the peak.
- **Every metric changes when you change the step size.** Correct, and not a bug — the plant is
  non-linear. Fix the step for the whole comparison and record what you used, exactly as S8 says
  about `Ku`.
- **The script disagrees with your eye and the script is wrong.** Also common. Plot the computed
  markers *onto* the trace rather than printing numbers, and the disagreement becomes obvious in a
  second instead of an hour.

**Capture the broken state.** The plot where your script's computed markers sit visibly in the wrong
place — settling time caught at the first crossing, or the 90 % marker found on the way back down.
Screenshot it beside the corrected one. Two plots of the same run, one with the markers wrong, is a
better demonstration that you understand these four definitions than any quantity of prose about
them.

### Prove it

Re-analyse every run from S8 with the script. The numbers should match what you eyeballed. Where
they do not, work out which of you is wrong.

> **CHECK YOURSELF** — Take the run with the worst overshoot and answer, without re-plotting: if you
> raised `Kp` by 50 %, which of the four numbers would go up and which would go down? Then do it, and
> see whether you were right. Getting this wrong once is worth more than reading the trade-off again.

### Artifacts

- **`docs/sessions/step-response-metrics/README.md`** — written at the end of the session, not the
  start. Three to five bullets on what actually happened, what the objective did not predict,
  and what you got wrong first. See [the template](../sessions/_TEMPLATE.md).
- `docs/derivations/2026-xx-xx-step-metrics.jpg` — your annotated sketch.
- `tools/plot.py` computing all four.
- **Site:** the annotated sketch next to a real annotated plot from your own rig. Textbook and
  reality, same page.
  **The shot:** the hand sketch and the generated plot as two images at similar sizes. On the
  sketch, all four metrics and the ±2 % band must be readable; on the plot, the computed markers
  must be visibly sitting on the trace rather than printed beside it.

---

## S10 · D, then I — derivative on measurement and anti-windup

**Goal:** a full PID that arrives quickly, does not oscillate, and holds zero steady-state error —
with the two failure modes that make naive PID unusable both explicitly handled.

**You will be able to:** explain derivative kick and why differentiating the measurement removes it, name two anti-windup mechanisms and say what each catches that the other misses, and quantify what one count of encoder noise costs you at your chosen `Kd`.

### Concept

Derivative pushes against the *rate of change*, which damps oscillation and lets you raise `Kp`
further than you otherwise could. Integral accumulates the leftover error until it is gone, which is
the only thing that eliminates the steady-state gap.

```
FIGURE III.S10.1 — The loop, with both fixes in place

                     ┌──────────────────────────────────┐
                     │  ANTI-WINDUP                     │
                     │  stop integrating while the      │
                     │  output is already clamped       │
                     │  AND the error would push it     ◄───────────────┐
                     │  further into the clamp          │               │ saturated?
                     └─────────────┬────────────────────┘               │
                                   │ inhibit                            │
                                   ▼                                    │
                        ┌──► [ Ki · ∫e dt ] ─────────────┐              │
                        │                                │              │
   target ──►(Σ)──► e ──┤                                ▼              │
             −▲         └──► [ Kp · e ] ────────────────►(+) ──► clamp ─┴┐
              │                                          ▲    to ±1.0    │
              │                 [ −Kd · d(meas)/dt ] ────┘               ▼
              │                           ▲                         [ × 255  ]
              │                           │ ON MEASUREMENT,              │
              │                           │ not on error                 ▼
              │                           │                         [ TB6612 ]
              │                           │                              │
              │                           │                              ▼
              │                           │                         [  motor  ]
              │                           │                              │
              │                           │                              ▼
              │                           │                         [ encoder ]
              │                           │                              │
              └───────────────────────────┴─── measured angle ◄──────────┘

  Read the summing junction (Σ) carefully: target enters positively and
  the measured angle enters with the MINUS sign marked beside its arrow.
  e = target − measured, here and everywhere else in this project. The
  second junction, further right, really is a plain (+) — P, I and D are
  all added.

  Why D on measurement: a step in the TARGET is a step in the error, and
  d(step)/dt is a spike. That spike is derivative kick. The measurement
  cannot step — the shaft has mass — so differentiating it is well behaved.
  The sign flips because d(error)/dt = −d(measurement)/dt when target is fixed.

  Note the order on the right: the PID sum is clamped to ±1.0 — a unitless
  fraction of full effort — and only THEN scaled to the driver's ±255. That is
  the same chain as FIGURE III.S6.1, and keeping it in that order is what lets
  you change drivers without retuning a single gain.

  Note also what the anti-windup box is wired to. Trace the "saturated?" line
  with a finger: it is tapped at the ┴ on the clamp's OWN OUTPUT — after the
  clamp, not before — runs up the right-hand side, and terminates at the ◄ on
  the anti-windup box. So it reads the CLAMP, not the error, and it inhibits
  the INTEGRATOR, not the output. Gating the output while the accumulator
  keeps growing is not anti-windup; it is windup with the symptom hidden
  until you let go.

  ONE QUESTION BEFORE YOU CODE IT. The tap is after the clamp rather than
  before. Why does that matter — what would you be measuring if you took it
  from the summing junction instead? Answer it in one sentence before you
  read the anti-windup section below; the answer is what the word "saturated"
  actually means.
```

Each has a characteristic failure. Derivative amplifies noise. Integral winds up. Both have standard
fixes and both fixes are two lines.

Analogy for derivative: a car's shock absorber. The spring (P) decides where the wheel should sit;
the damper (D) resists sudden movement so it does not bounce.

### The math — derivative on measurement, not on error

The textbook form differentiates the error:

```
D = Kd × d(error)/dt = Kd × d(target − measured)/dt
```

When `target` is constant this equals `−Kd × d(measured)/dt`, which is fine. But when you **step** the
target, `d(target)/dt` is an impulse — mathematically infinite, practically a single enormous spike in
your command. This is **derivative kick**, and it is why a naive PID slams the motor at every setpoint
change.

The fix is to differentiate the measurement only:

```
D = −Kd × (measured − prevMeasured) / dt
```

Identical behaviour for disturbance rejection, no kick on setpoint changes. There is no reason to use
the other form.

**Noise amplification, quantified.** From S6, one count of position jitter is `7.48 × 10⁻⁴ rad`, so
velocity jitter is `0.0748 rad/s`. With `Kd = 0.1` that is a command wobble of `0.0075` out of `1.0` —
0.75 %, flickering every tick. Audible. If it is intolerable, low-pass the derivative:

```
d_filtered = α × d_new + (1 − α) × d_previous       with α ≈ 0.1 – 0.3
```

Note that `d_previous` is **state**, so it needs a member of its own — the class in S8 does not declare
one, and adding it is part of this session rather than an oversight. It also needs the same
first-call treatment as `prevMeas_`: on the very first tick there is no previous value, and seeding it
to zero puts a spurious step through the filter.

Note also what the filter costs: it adds phase lag, and phase lag is exactly what destabilises a loop.
You are trading noise for stability margin. **This is the decision, and it goes in
`docs/decisions/` tonight rather than at the gate** — your α, the cutoff it
implies at your loop rate, and what the plot looked like either side of it. The plot is the argument;
an α recalled in eight months is a guess.

> **CHECK YOURSELF** — Before you pick α, predict it: at α = 0.1, roughly how many ticks does it take
> for the filtered derivative to reach most of the way to a new steady value, and how many milliseconds
> is that at your loop rate? Compare that against the settling time you measured in S9. If the filter
> is slower than the thing it is filtering, you have chosen badly, and you can see that on paper before
> you hear it on the bench.

### The math — anti-windup

If the motor is held still by your hand while the integral term is active, `error` stays large, the
accumulator grows without bound, and when you let go the stored correction discharges violently.

Two mechanisms, use both:

```
1. Conditional integration — do not accumulate while the output is saturated:
     if (output was clamped AND error has the same sign as the clamp) skip integration

2. Clamp the accumulator so the integral term alone cannot exceed the output range:
     integral_ = constrain(integral_, lo_/ki_, hi_/ki_)
```

**Why mechanism 2 divides by `ki_` at all**, since it is stated as a formula and it is worth being a
result. The integral *term* is `ki_ × integral_`, and what you actually want to bound is that product —
it must not on its own be able to demand more than the output range. Divide both sides by `ki_` and you
get the bound on the accumulator itself, which is what the line says. Write that out once and the
formula stops being something you copied.

**The trap: if `ki_` is zero you divide by zero.** Guard it — and decide *how*, because the two obvious
answers behave differently. Skipping the clamp entirely when `ki_ == 0` is correct, because with no
integral gain the accumulator cannot contribute anything no matter how large it grows. Clamping to the
output limits instead is also safe but silently leaves a large accumulator sitting there, so the moment
you set a non-zero `ki_` mid-experiment it discharges. Pick the first, and write a one-line comment
saying why — you will set `Ki = 0` while tuning D, which is exactly when this fires.

> **WATCH OUT** — Before you enable integral action, read your S1 stall-current figure again. Windup
> against a hand-held shaft means sustained near-stall current through a driver rated 1.2 A
> continuous. Test windup deliberately, briefly, once, with your finger on the S2 inline switch — and
> then implement the fix.

### Draw this

**The three terms, separated, against one error trace.** Take one captured step response and plot four
things on shared time axes: the error itself, then `Kp·e`, then `Ki·∫e`, then `−Kd·d(meas)/dt`, each in
its own lane. Then a fifth lane with the sum and the clamp drawn across it.

This is the single most clarifying drawing in Stage 0 and almost nobody makes it. You can *see* the
proportional term collapse as the error closes, the integral term accumulate and then hold, and the
derivative term spike at the start and go quiet. When one of them misbehaves later, you will recognise
the shape rather than guessing which term did it.

Mark two moments on it: where the sum hits the clamp, and where anti-windup therefore stops the
integrator. Those two marks are the code you are about to write.

### Build — order of operations

1. **D first.** With `Kp` at the value that oscillated in S8, raise `Kd` from 0 until the oscillation
   damps. Then raise `Kp` further than S8 allowed, and observe that you now can.
2. **I last.** Add a small `Ki`. Watch the residual error close. Then deliberately provoke windup —
   hold the shaft, watch the plot — and implement anti-windup. Re-test.

### Code — skeleton (the parts left blank in S8)

```cpp
float PIDController::update(float target, float measured, float dt) {
  float error = target - measured;

  // P
  // TODO

  // D — on measurement, negated. Guard the very first call (prevMeas_ unseeded).
  // TODO

  // I — accumulate, then apply BOTH anti-windup mechanisms above.
  // TODO

  // Sum, clamp to [lo_, hi_], and record whether the clamp fired
  // (conditional integration needs to know).
  // TODO

  prevMeas_ = measured;
  return output;
}
```

### Prove it

- A 0° → 90° step with less than 10 % overshoot, settling inside 500 ms, with zero steady-state error.
- **The disturbance test:** hold the target, push the shaft with your finger, let go. It returns. This
  is the one you film.
- **The windup test:** hold the shaft for five seconds, release. Nothing violent happens.

### What will go wrong

- **A huge spike on the very first tick, before anything has moved.** `prevMeas_` is unseeded, so the
  first derivative is computed against zero and `(measured − 0) / dt` is enormous. The skeleton flags
  this and it is still the commonest bug in this session. Seed `prevMeas_` on the first call and
  return the P term alone for that one tick.
- **A divide-by-zero the moment you set `Ki = 0`.** The accumulator clamp is `lo_/ki_` to `hi_/ki_`.
  This is mentioned once, in passing, above — and it is easy to skim past, which is why it is repeated
  here. Guard `ki_ == 0` explicitly rather than relying on never testing that case.
- **Anti-windup that looks fixed until you let go.** Gating the *output* while the accumulator keeps
  growing is not anti-windup; it is windup with the symptom hidden. The plot looks calm during the
  hold and then lurches on release, exactly as before. FIGURE III.S10.1 draws the inhibit terminating
  at the **integrator** for this reason — check your code against the figure, not against your memory
  of the figure.
- **The windup test cooks something.** You are holding a motor near stall against a driver rated 1.2 A
  continuous. Five seconds, once, hand on the switch. Not thirty seconds while you watch the plot.
- **D makes it worse rather than better.** Almost always derivative noise rather than a wrong sign —
  the velocity signal is quantised at 0.0748 rad/s, so at `Kd = 0.1` it dithers the command by 0.75 %
  every tick. Low-pass it before concluding the term is useless, and write down the α you chose.

> **CHECK YOURSELF** — You should be able to say, for each of P, I and D, what changed when you altered
> it — and point at a plot that shows it. If you can only say "I turned knobs until it looked right,"
> stay here another session. This is the material Stage 1 assumes you own.

**Capture the broken state.** Two, because this session has two distinct failures and they look
nothing alike: the plot with a spike on the very first tick from the unseeded `prevMeas_`, and the
windup plot that sits calm through the hold and then lurches on release. Keep both. The second is
the more valuable, because a controller that looks fine while you are holding the shaft and
misbehaves the instant you let go is exactly the shape of bug that anti-windup exists for.

### Artifacts

- **`docs/sessions/derivative-and-integral/README.md`** — written at the end of the session, not the
  start. Three to five bullets on what actually happened, what the objective did not predict,
  and what you got wrong first. See [the template](../sessions/_TEMPLATE.md).
- `docs/tuning/` — a dated log per session, in the table format from *Before You Build*, Part III →
  "Write down the number", with your corrected counts-per-rev at the top.
- The full sequence of plots, in order.
- An ADR in `docs/decisions/` — your α and your reasoning.
- **Site:** the disturbance-rejection video. It is the single most compelling thirty seconds Stage 0
  produces.
  **The shot:** one clip, 20 to 30 seconds, landscape, phone propped or on a tripod so it does not
  move. **The shaft and the live plot must be in frame at once, and this is the whole
  specification.** A video of the shaft alone proves nothing, because nothing in it shows the
  target being recovered; a video of the plot alone is a video of a graph. Push, hold about two
  seconds, release, let it settle — three times in the single take, so it reads as a property
  rather than a lucky one.

---

# PART IV — MAKING IT AN ENGINEERING ARTIFACT

---

## S11 · The safety envelope, and getting off `analogWrite()`

**Goal:** a joint that refuses illegal commands and cannot hurt itself, running silent PWM at a real
control rate.

**You will be able to:** explain what a joint should do when its host goes silent and why, size a stall-detection window against a driver's pulse rating rather than against what feels responsive, and reconfigure a hardware timer's prescaler while saying exactly what else in the program that does and does not affect.

### Concept

Everything so far has been an experiment. This session turns it into a component you would be willing
to bolt into an assembly — which means it has to behave correctly when it is given something wrong,
not just when it is given something right.

### Part A — the envelope

**1. Soft limits.** Refuse targets outside a range you declare. Not clamp silently — refuse, and
report. Silent clamping hides bugs; refusal surfaces them.

**2. Velocity limiting via a rate-limited setpoint.** Do not feed a step directly to the controller.
Move an internal setpoint toward the commanded target at no more than `V_MAX` per tick:

```
max_step = V_MAX × dt                     [rad per tick]
setpoint += clamp(target − setpoint, −max_step, +max_step)
```

Work out your own `V_MAX`. Your motor's no-load output speed is 100 RPM:

```
100 RPM = 1.667 rev/s = 10.47 rad/s   (absolute ceiling)
Choose V_MAX = 3.0 rad/s               (~29 % of no-load — deliberately conservative)
max_step at 100 Hz = 3.0 × 0.01 = 0.03 rad = 1.72° per tick
```

Note the pleasant side effect: a rate-limited setpoint makes the step response *smoother* as well as
safer, because the controller is no longer being asked for the impossible.

**3. Fail-safe on silence.** If no command has arrived for N milliseconds, hold the current position.
This looks pointless with a USB cable attached and it is the habit Stage 1's CAN work is built on:
holding position is almost always right, and continuing the last velocity command is almost always
catastrophic.

**Write it down here, in `docs/decisions/`, while you are choosing rather than after.**
Hold, coast or brake — three defensible answers with different failure modes, and Stage 1 S1.8 will
ask you to defend the one you picked over a bus instead of a cable. Four sentences per section is
plenty.

**4. Stall detection.** If the command has been saturated for longer than some window and the
position has not changed, cut output and latch a fault requiring an explicit clear. Your driver is
rated 1.2 A continuous and your motor stalls at about 1.0 A; this is what stops a mechanical jam from
becoming a thermal event.

**Derive the window rather than picking one that feels responsive**, because "feels responsive" is not
a thermal argument. Two bounds squeeze it from either side:

```
LOWER BOUND — do not trip on legitimate slow motion.
  At V_MAX and your encoder resolution, how long does a real move take to
  produce one count?  1 count / (V_MAX × COUNTS_PER_RAD)
  At 3.0 rad/s and 8,400 counts/rev that is well under a millisecond, so
  "position has not changed for N ms" is unambiguous for any N above a
  few tens of milliseconds.  Add margin for a joint moving slowly on
  purpose — homing, in Stage 2, runs at a tenth of V_MAX.

UPPER BOUND — the driver's pulse rating, which you looked up in S1.
  The TB6612's peak figure carries a maximum pulse width. Your latch must
  fire well inside it, because that rating is the only thing making an
  over-current transient legal at all.

  Pick a window between those two, write both bounds next to the constant,
  and say which one is binding.
```

On this motor the lower bound is the binding one and the window is generous. **On the Stage 2 motor it
is the other way round** — a JGB37-520 stalls at 2.3 A against the same driver — which is why S2.4 says
to size the latch against the pulse-width limit rather than against feel. Doing the derivation now, when
it is easy, is what makes that sentence mean something later.

> **WHERE THIS POINTS** — Every safety argument in medical device firmware eventually reduces to a
> timing argument: worst-case time from a sensed event to an actuator response. A command timeout and
> a stall latch are the smallest honest versions of that reasoning, and being able to explain why you
> chose *hold* over *coast* over *brake* is a better interview answer than any amount of PID theory.

### Draw this

**The safety envelope as a state machine.** Boxes for the states this joint can be in — idle, running,
rate-limited, soft-limit refused, stalled-and-latched — and an arrow for every transition, labelled with
what causes it. Then mark each arrow **automatic** or **requires an explicit clear**, because that
distinction is the whole difference between a limit and a fault.

Three things the drawing will surface that prose does not:

- **What state does it boot into?** Running, or refusing until told otherwise? You have to choose.
- **Can two faults be active at once**, and what does clearing one do to the other?
- **Is there any path back to running that does not go through a human?** If there is, say why it is
  safe; if there is not, say so, because that is a design property worth claiming.

Keep the page. Stage 1 S1.8 asks you to draw the same machine again with the CAN faults added, and
Stage 2's e-stop joins it after that. Watching it grow across three stages is a better artifact than any
one version of it.

### Part B — real PWM

You have been running 490 Hz because that is what `analogWrite()` gives you. It is audible, it limits
your loop rate, and it is a layer you did not choose. Remove it.

Timer1 drives D9 and D10 in 8-bit phase-correct PWM mode. Its frequency is:

```
f = F_CPU / (2 × N × TOP)        where N = prescaler, TOP = 255

Default:  16 MHz / (2 × 64 × 255)  =    490 Hz
N = 1:    16 MHz / (2 ×  1 × 255)  = 31,373 Hz
```

Setting the prescaler to 1 is one line:

```cpp
// Timer1 prescaler -> 1. Affects D9 and D10 PWM frequency only.
// Timer0 (millis/micros, D5/D6) and Timer2 (D3/D11) are untouched.
TCCR1B = (TCCR1B & 0b11111000) | 0x01;
```

31 kHz is above human hearing, so the whine disappears. More importantly, with 313 PWM periods per
10 ms tick instead of 4.9, the five-periods-per-tick constraint from S4 is gone and you can raise the
loop rate:

```
New loop rate: 500 Hz (DT_US = 2000) — 62 PWM periods per tick. Comfortable.
```

Two consequences to handle, not to discover:

- **Your gains change.** `Ki` and `Kd` are defined in terms of `dt`. Going from 100 Hz to 500 Hz
  changes `dt` by 5×. If your implementation multiplies and divides by `dt` correctly, the gains
  should carry over — **and that is a test.** If they do not carry over, you have a `dt` bug, and you
  have just found it cheaply.
- **Your telemetry no longer fits.** From S7: 22 bytes × 500 Hz = 11,000 B/s, which is 95 % of a
  115200 link. Move to 250000 baud, or set `logEveryN = 5` and log at 100 Hz while controlling at
  500 Hz. Either is legitimate; decide deliberately and write it down.

> **CHECK YOURSELF** — Before you flash the 31 kHz change, predict three things and write them down:
> what happens to the *sound*, what happens to the *step response* at unchanged gains, and what happens
> to your *telemetry*. Two of the three you can reason out from arithmetic already in this workbook.
> The third is the one that catches people, and finding out which was which is the point.

> **DEFINITION** — This is **rung 3** of the ladder in Interlude D of the Project Guide: bypassing the
> Arduino abstraction where timing matters, on hardware you already own. You have now met a
> hardware timer, a prescaler, and a control register — the same three concepts you will meet again
> in CubeMX in Stage 1, where they will be familiar instead of foreign.

### What will go wrong

This session writes the code that is supposed to prevent damage, so its failures are the quiet kind —
things that look like they work.

- **The stall latch trips during normal slow motion.** Your window is shorter than the time a
  legitimately slow move takes to produce a count. Re-check it against the lower bound above, and
  remember Stage 2 homes at a tenth of `V_MAX`.
- **The rate limiter and the controller fight, and you read it as sluggishness.** The controller is
  chasing the *internal setpoint*, not your target, so a large step now looks slow by design. If you
  cannot tell that from an actual problem, plot the setpoint alongside the target and the position —
  three traces, and the distinction becomes obvious.
- **`TCCR1B = (TCCR1B & 0b11111000) | 0x01;` written as a plain assignment instead.** `TCCR1B = 0x01`
  clears WGM12 and every other bit in that register along with the prescaler, and the PWM mode changes
  underneath you. The mask is not decoration — it is the difference between changing one field and
  overwriting a register.
- **The soft limit clamps silently because clamping was easier than refusing.** Then a bug upstream
  that commands 400° looks like a joint that works. Refuse, set a flag, and make the caller deal with
  it — that is the whole difference between an experiment and a component.
- **Everything works and the fault cannot be cleared.** A latch you cannot reset without a power cycle
  is not finished. Test the clear path deliberately, once, in the same session that writes the latch.
- **The gains do not transfer to 500 Hz and you retune them.** Stop. That is a `dt` bug and you have
  just been handed it cheaply — retuning hides it until Stage 1 hands it back.

**Capture the broken state.** The stall latch tripping in the middle of a legitimate slow move.
Capture the plot with the fault flag rising while the position is still visibly changing — that is a
safety mechanism firing on the wrong thing, which is a more interesting artifact than one firing
correctly, and it is the concrete form of the lower bound you derived above.

### Prove it

- Command a target outside the soft limits. It is refused and says so.
- Command a large step. The response is visibly rate-limited, and no longer slams.
- Unplug the serial link mid-motion. It holds position.
- Jam the shaft. It latches a fault rather than cooking.
- The motor is now silent. Analyzer confirms 31.4 kHz on D9 and a 2.000 ms loop period.

### Artifacts

- **`docs/sessions/safety-envelope/README.md`** — written at the end of the session, not the
  start. Three to five bullets on what actually happened, what the objective did not predict,
  and what you got wrong first. See [the template](../sessions/_TEMPLATE.md).
- Analyzer capture showing 31 kHz PWM and the 500 Hz loop.
- An ADR in `docs/decisions/` — hold vs coast vs brake, and why.
- Before/after step-response plots at 100 Hz and 500 Hz.
- **Site:** the two plots, with the note that the gains transferred unchanged. That is a claim about
  your code being dimensionally correct, and it is a strong one.
  **The shot:** two plots, same axes limits, with the gains printed on both so a reader can see
  for themselves that they did not change. That is the claim, and it is only visible if the
  numbers are on the image.

---

## S12 · The refactor, and the exit gate

**Goal:** Stage 0 code that is a `Joint` object rather than a sketch — because in Stage 1 you flash
this exact artifact to more than one board.

**You will be able to:** explain why a class-based joint makes a four-joint arm an array rather than a rewrite, and demonstrate that a refactor changed no behaviour by overlaying step responses rather than by reading the diff.

### Concept

Right now you likely have one `loop()` and a set of file-scope variables. That is fine for one joint
and it is the wrong shape for four. With globals, four joints means four copies of every variable
with numeric suffixes and four copies of every function that touches them. With objects, four joints
is an array.

This is not a style preference. It is the thing that makes Stage 1's "flash it twice" a deployment
detail instead of a rewrite.

### Build

```cpp
// joint.h  — S12
#pragma once
#include "encoder.h"
#include "motor.h"
#include "pid.h"

struct JointState {
  float   positionRad;
  float   velocityRadS;
  float   setpointRad;
  int16_t command;
  uint8_t flags;          // saturated | faulted | timeout | homed
};

class Joint {
public:
  void begin(const JointConfig& cfg);

  void setTarget(float rad);        // rejects out-of-range, returns via state flags
  void tick(float dt);              // sense → limit → think → act. Called at fixed rate.
  JointState state() const;         // ← this is what Stage 1 serialises into a CAN frame

  void clearFault();

private:
  Encoder       enc_;
  Motor         motor_;
  PIDController pid_;
  float targetRad_ = 0, setpointRad_ = 0;
  float minRad_ = 0, maxRad_ = 0, vMaxRadS_ = 0;
  uint32_t lastCommandMs_ = 0;
  uint8_t  flags_ = 0;
};
```

Three things to notice, because they are the reason the refactor is worth an evening:

1. `Joint` is **the artifact you flash to multiple boards** in Stage 1 M1.7. The distributed
   architecture becomes a matter of node IDs, not a rewrite.
2. `state()` is **what your CAN telemetry frame serialises**. Stage 1's protocol design falls out of
   this interface rather than being invented separately.
3. In Stage 2, the `ros2_control` hardware interface becomes a thin adapter over objects that already
   exist, instead of a from-scratch translation layer.

No file-scope mutable state should survive except the single ISR shim pointer, which is unavoidable
because `attachInterrupt` takes a plain function pointer.

### Draw this

**The class diagram, by hand, before you write a line of the refactor.** Four boxes — `Joint`,
`Encoder`, `Motor`, `PIDController` — with an arrow from each owner to what it owns, and the ISR drawn
as an arrow *into* `Encoder::onEdge()` from outside every box, because that arrow is the one thing in
the design that does not obey the ownership tree and it is the thing that breaks first when there are
two joints.

Then mark, on the same page: which member is `volatile` and why; which call has to disable interrupts
and why; and the single file-scope pointer, with a note saying whether it is documented as
single-instance or indexed. Those three annotations are the entire content of the refactor. If you can
draw them, the code is an afternoon; if you cannot, writing the code first will not teach you them.

> **CHECK YOURSELF** — Cover the drawing and answer: when Stage 1 gives you two `Joint` objects, which
> single line in your design breaks, and what happens — an error, or silently wrong counts? If you
> cannot answer that from the page, the page is not finished. The first bullet below is the answer, so
> commit to yours before you read it.

### What will go wrong

This is a refactor of working code, so every failure here is a regression — which makes the tagged
commit you refactor *from* the most valuable thing in the session.

- **`Joint` holds a static ISR pointer per instance, and the second instance silently steals the
  first.** The file-scope shim pointer is exactly one pointer, and the moment you construct a second
  `Joint` it points at the second one. Stage 0 has one joint so nothing breaks — and Stage 1 M1.7 has
  two, at which point encoder counts from joint 1 land in joint 2. Decide now: either the shim is
  explicitly documented as single-instance, or you index it. Write which, in a comment, at the shim.
- **`state()` returns by value from a struct the ISR is updating, with no torn-read guard.** You fixed
  this for `count_` in S3 and it comes back the moment several fields are read together: the ISR can
  land between two members and you serialise a position from this tick with flags from the next. It
  is the same bug one level up, and Stage 1 S1.5 meets it a third time as a context switch.
- **Behaviour changes and you cannot tell which change did it.** Refactor in small commits and re-run
  the same step response after each one, against the plot from before you started. A refactor that
  changes the step response has changed behaviour, whatever it looked like on the diff.
- **`units.h` constants end up defined in two places.** The `constexpr`/translation-unit rule from S6
  is what stops this. If the linker complains about duplicate symbols, that is this.

**Capture the broken state.** The overlay where the post-refactor step response does **not** sit on
top of the pre-refactor one. If the refactor is clean you will not get this and that is a fine
outcome — but if you do get it, keep it, because it is the plot that justifies the whole practice of
re-running the same step response after every commit rather than reading the diff.

### Build — the tests, which are the reason a refactor is safe

You are a software engineer refactoring working code with no test suite. You would not accept that at
work; do not accept it here. **This is the cheapest credibility win in the entire repository**, it
takes about an hour, and almost no embedded portfolio has one.

PlatformIO runs tests on your *host machine* — a native build, no board attached, `pio test -e native`.
Anything that is pure logic can be tested there in milliseconds, and most of what you wrote in Stage 0
is pure logic wearing a hardware costume.

**The test directories already exist**, with these two files in them and every body left as a TODO —
`test/test_pid/test_pid.cpp` and `test/test_encoder/test_table.cpp`. So does the `[env:native]`
block in `platformio.ini`. What does *not* exist is the Unity runner, and that is deliberate rather
than an omission: see the note after the skeletons below.

```cpp
// test/test_pid/test_pid.cpp   — runs on your laptop, no UNO required
#include <unity.h>
#include "pid.h"

void test_p_only_is_proportional() {
  // TODO: Kp=2, Ki=Kd=0. An error of 0.5 rad must give exactly 1.0.
  //       Then error 0.25 gives 0.5. If it does not, your gain is not linear
  //       and everything you tuned means something else.
}

void test_output_clamps() {
  // TODO: a huge error must return exactly hi_, never more.
}

void test_derivative_is_on_measurement_not_error() {
  // TODO: hold `measured` constant and STEP `target`. A correct
  //       implementation produces NO derivative contribution at all.
  //       This is derivative kick, caught in a unit test, in 50 µs,
  //       instead of on a bench with a motor slamming.
}

void test_integral_does_not_wind_up_while_saturated() {
  // TODO: drive it saturated for 1000 ticks, then remove the error.
  //       The output must not still be pinned. This is the S10 windup
  //       test with no motor, no hand, and no risk to the driver.
}

void test_ki_zero_does_not_divide_by_zero() {
  // TODO: the guard you wrote in S10. One line, and it is the bug
  //       you will otherwise meet at the worst moment.
}
```

And the same treatment for the encoder table, which is pure arithmetic and needs no hardware at all:

```cpp
// test/test_encoder/test_table.cpp
void test_table_has_four_of_each() {
  // TODO: count the entries. Exactly four +1, four -1, four 0-with-no-change,
  //       and four illegal. If your table does not pass this, it is wrong —
  //       and this test would have caught it before you ever wired a motor.
}
void test_forward_loop_gives_plus_one() {
  // TODO: walk 00->01->11->10->00 through the table and assert every step
  //       is +1. Then walk it backwards and assert every step is -1.
}
```

**The runner is missing on purpose, and writing it is part of this session.** Unity needs `setUp`,
`tearDown` and a `main` that calls `RUN_TEST` for each case; the stubs say so in a comment and stop
there. An empty runner that passes is worse than no runner at all, because CI then reports green on
nothing — which is the failure this session exists to avoid rather than an oversight to fix.

**Why this matters more than it looks.** Four of those tests reproduce, in software, experiments that
S8 and S10 had you perform on a physical motor with your hand on a switch. Being able to say *"the
windup behaviour is covered by a host-side unit test that runs in CI on every push"* is a sentence that
lands very differently from *"I tested it on the bench"* — and `.github/workflows/ci.yml` already has
the `pio test -e native` step written and commented out, waiting for this moment. **Uncomment it here**,
once the tests have real assertions in them, and watch it go green on something.

> **CHECK YOURSELF** — Which parts of your Stage 0 code *cannot* be tested this way, and why? The
> answer names the exact boundary between logic and hardware in your design — and if that boundary
> turns out to be blurry, the refactor is not finished.

### Prove it

Run the S10 step response again, unchanged gains, and overlay it on the pre-refactor plot. They should
sit on top of each other. Then run the four S11 failure tests again — soft limit, rate limit, timeout,
stall latch — because those are the behaviours a refactor most easily drops.

> **CHECK YOURSELF** — Interlude D's own gate: your Stage 0 code builds under PlatformIO from `.cpp`
> files; it has at least a `Joint`, an `Encoder` and a `PIDController` with no file-scope mutable
> state; you can point at the one line where the abstraction is bypassed for timing reasons (S11's
> `TCCR1B` write) and explain why; and you can describe what `digitalWrite` does that a register
> write does not.

### Artifacts

- **`docs/sessions/refactor-to-classes/README.md`** — written at the end of the session, not the
  start. Three to five bullets on what actually happened, what the objective did not predict,
  and what you got wrong first. See [the template](../sessions/_TEMPLATE.md).
- **The class diagram** — `Joint`, `Encoder`, `Motor`, `PIDController`, drawn by hand: what owns what,
  and which method the ISR calls. One page. Into `docs/derivations/`.
- The before/after overlay plot showing the step response is unchanged.
- `firmware/stage0-uno/README.md` — pin map, measured motor constants, current gains, how to build.
- The annotated tag `v0.0-stage0-exit`, pushed.
- **Site:** the class diagram and the exit tag. It is the bridge to Stage 1, and it is what makes
  "I flashed the same artifact to two boards" a claim with a picture behind it.
  **The shot:** the class diagram as one still, square on, with the ISR arrow readable — it is the
  arrow that does not obey the ownership tree and it is the reason the drawing exists. The tag
  goes beside it as text: `v0.0-stage0-exit`, and the commit it points at.

---

## The Stage 0 exit gate

Do not start Stage 1 until every one of these is true. They are the Project Guide's gate, made
specific to your hardware.

| # | Criterion | Evidence |
|---|---|---|
| 1 | You can state your loop rate and **prove** it | Saved analyzer capture, measured not intended |
| 2 | It holds a target angle against your hand and returns | Video |
| 3 | You can show a plotted step response and explain its overshoot | Annotated plot |
| 4 | You can say what each of P, I, D changed, with a plot for each | `docs/tuning/` |
| 5 | Your counts-per-output-revolution is **measured**, and the derivation is written | `docs/motor-spec.md` + derivation scan |
| 6 | Anti-windup and derivative-on-measurement are implemented and you can explain both | Code + `docs/decisions/` |
| 7 | Soft limits, velocity limiting, command timeout, and stall latch all work | Four demonstrated failure tests |
| 8 | The code is `Joint`/`Encoder`/`Motor`/`PIDController` under PlatformIO | Repo |
| 9 | Your Git history shows the tuning progression, including the failures | `git log` |
| 10 | Tag `v0.0-stage0-exit` is pushed | GitHub |

---

## What goes on the site, in order

This is the sequence to publish, and it works because it is chronological rather than curated — each
item is dated and each one shows a step forward.

| Session | The artifact | Why it reads well |
|---|---|---|
| S0 | Labelled bench, repo link | Sets the frame: this is a project, not a tutorial |
| S1 | Handwritten counts-per-rev derivation; the mounted motor | Maths in your handwriting, before any code |
| S2 | Hand-drawn power tree | Almost no hobby project shows one |
| S3 | Quadrature A/B captures, forward and reverse | The concept made visible in four seconds |
| S4 | Video of first motion | Momentum |
| S5 | Loop-rate analyzer capture | "I can prove my timing" — rare |
| S6 | Unit-chain derivation | Shows you know what your controller computes |
| S7 | Open-loop ramp plot | The instrumentation works |
| S8 | Two plots: never arrives / oscillates | The trade-off, legible to anyone |
| S9 | Annotated step-response sketch + real plot | Textbook and reality on one page |
| S10 | Disturbance-rejection video | The single best thirty seconds of Stage 0 |
| S11 | 100 Hz vs 500 Hz plots, gains unchanged | A claim about correctness, not effort |
| S12 | The class diagram, and the exit tag | The bridge to Stage 1 |

> **WHERE THIS POINTS** — Commit history is the one part of a portfolio that cannot be retroactively
> faked. A single dump commit reads as a tutorial followed. Forty commits showing a gain raised, an
> oscillation appearing, a clamp added, and a plot attached reads as someone who can debug. Commit
> small, commit often, and commit the failures especially.

---

## Repository additions this workbook assumes

Beyond the layout in *Before You Build*, Part III → "A structure that survives to Stage 4". **All of
these already exist** — this list is here so you know what each one is for and can tell when one of
them is empty because you have not got there yet, rather than because something is missing.

```
docs/sessions/             # one folder per session, plus _TEMPLATE.md to copy
docs/derivations/          # scanned handwritten maths — the highest-value folder here
docs/reference/            # datasheets and vendor material you fetched from elsewhere
docs/tuning/raw/           # captured CSVs
docs/tuning/plots/         # generated PNGs
tools/capture.py           # serial → CSV                    — a stub. You write it in S7
tools/plot.py              # CSV → annotated plot + metrics   — a stub. S7, extended in S9
CHANGELOG.md               # one entry per exit-gate tag, written before the tag
LICENSE                    # MIT
```

Two things that would be worth adding if they were not already there, and are worth understanding
because they are the two claims this repository makes about itself:

- **A per-stage README** in `firmware/stage0-uno/`. Today it is four build commands and a pointer to
  this workbook, deliberately — a scaffolded table of `TODO`s where your pin map and your measured
  constants should be is a shape somebody else chose. **S12 rewrites it** into the real thing: the
  pin map, the measured motor constants, the gains you settled on, and how to build. That is the file
  that makes the repo navigable to someone who is not you, and writing it at the gate rather than at
  the start is what makes every number in it one you actually have.
- **A trivial GitHub Action** that runs `pio run` on push, in `.github/workflows/ci.yml`. It proves
  the firmware compiles from a clean checkout, which is a claim a surprising number of repositories
  cannot make. It is about fifteen lines and the `pio test -e native` line is commented out, because
  a test runner that passes on no tests reports green on nothing. **You uncomment it in S12**, when
  there is something for it to run.

---

## Session index

| # | Session | Hours | Needs parts? |
|---|---|---|---|
| S0 | Bench, toolchain, repository | 3 | No |
| S1 | Motor forensics, and bolting it down | 4 | Motor, multimeter, M3 hardware, plank |
| S2 | Power topology | 3 | Supply, buck, caps, soldering |
| S3 | Encoder, interrupts, ×4 decoding | 4 | + UNO, analyzer |
| S4 | Open loop, both directions | 3 | + TB6612 |
| S5 | Fixed-rate loop, proving the rate | 2 | — |
| S6 | Units and the conversion chain | 2 | — |
| S7 | Telemetry and plotting | 3 | — |
| S8 | P only, steady-state error, `Ku` | 4 | — |
| S9 | Step-response metrics | 2 | — |
| S10 | D then I, kick and windup | 5 | — |
| S11 | Safety envelope, register-level PWM | 4 | + limit switch |
| S12 | Refactor to classes, exit gate | 3 | — |
| | **Total** | **~42 h** | |

At two to three hours a day, that is **two to three weeks** — which matches the Project Guide's
Appendix G estimate for Stage 0 at your pace. The binding constraint is parts shipping, not your
hours.

---

## Appendix: the milestone map

The Project Guide numbers Stage 0 as milestones **M0.0–M0.9** — every milestone in the set is
prefixed with its stage, so that `M0.6` and `M1.6` and `M2.6` are different pieces of work rather
than three things called M6. This workbook numbers it as sessions
**S0–S12**. They are the same work at two levels of detail, and this is the mapping. When the Guide
says "see M0.6," this is how you find it.

| Guide milestone | Workbook session | Note |
|---|---|---|
| **M0.0** · Mount it rigidly | **S1** (Build — bolt it down) | |
| **M0.1** · Decode quadrature without losing counts | **S1** (derive) + **S3** (implement, measure) | |
| **M0.2** · Drive both directions, fix the sign once | **S4** | |
| **M0.3** · Prove the loop rate on an instrument | **S5** | |
| **M0.4** · Build telemetry that fits the serial budget | **S7** | |
| **M0.5** · Close a proportional loop and find `Ku` | **S8** | |
| **M0.6** · Add D, then I, with kick and windup handled | **S10** | |
| **M0.7** · Log a step response and name its four metrics | **S9** | The Guide lists these two in the opposite order; do D and I *after* you can measure a step response |
| **M0.8** · Fit the safety envelope | **S11 Part A** | |
| **M0.9** · Refactor to `Joint`, `Encoder`, `PIDController` | **S12** | Rung 2 of Interlude D's ladder |
| *(no Guide milestone)* | **S0** · Bench, toolchain, repository | Setup, deliberately not a milestone |
| *(no Guide milestone)* | **S2** · Power topology | The Guide covers this only under "what will go wrong" |
| *(no Guide milestone)* | **S6** · Units and the conversion chain | The Guide covers it in Interlude C |
| *(no Guide milestone)* | **S11 Part B** · Register-level PWM | Rung 3 of Interlude D's ladder |

---

## Appendix: what changes if the gear ratio is not 300

You will measure the ratio at the end of S3. If it comes back at 8,400 ± 30 counts per output
revolution, nothing below applies and you can forget this page. If it does not — and there is a real
chance it does not — **this is the complete list of things that move.** Work through it once, in one
sitting, and commit the result. The expensive version of this is discovering item 6 in Stage 2.

Write `N` for your measured ratio and `C = 28 × N` for your measured counts per output revolution.

| # | What changes | Where | How |
|---|---|---|---|
| 1 | `COUNTS_PER_OUTPUT_REV` | `units.h`, S6 | Set to your measured `C`. Everything else in that file is derived and needs no edit. |
| 2 | `RAD_PER_COUNT`, degrees per count | S1, S6 | Recompute: `2π / C`. At 250:1 that is 7,000 counts, 8.98 × 10⁻⁴ rad, 0.0514°. |
| 3 | Interrupt rate and CPU load | S3 | `1.667 × N × 28` edges/s. Recompute the percentage before you quote it anywhere. |
| 4 | **Every PID gain you have tuned** | S8, S10 | `Kp` is command per *radian*, so if `C` changes, the radians your controller sees change, and your gains are wrong by the same factor. **Retune, or scale them by `C_new / C_old` and verify.** This is the item people miss. |
| 5 | Velocity quantisation, and therefore `Kd` noise | S6, S10 | `2π / (C × dt)`. A *lower* ratio means coarser velocity resolution and a noisier derivative term. |
| 6 | No-load output speed and `V_MAX` | S11 | The 100 RPM figure and the ratio are two views of the same fact. If `N` is not 300, measure the no-load output speed too and re-derive the 10.47 rad/s ceiling. |
| 7 | 16-bit counter wrap margin | Stage 1 pin map | `65,536 / C` output revolutions. **Unsigned 16-bit**, because this is a hardware timer's counter register and it wraps at 2¹⁶. It is why Stage 1 uses a 32-bit timer, and the argument only gets stronger as `C` rises. Compare item 12, which is the same question about a *software* variable and therefore has a different exponent — the two are not a typo. |
| 8 | Static torque available at the joint | Stage 2, S2.4 | Torque scales roughly with `N`. A lower ratio means *less* torque and the Stage 2 shortfall gets worse, not better. |
| 9 | Backdrivability | Stage 5 | Lower ratios are more backdrivable, which is *better* for impedance control. This is the one place a surprise is good news. |
| 10 | The S3 acceptance test itself | S3 *Prove it* | S3 already separates the two: turning the shaft **measures** `C`, and the reusable acceptance test is "ten turns reads 10 × `C` ± 30". Write your `C` into that sentence and use it in every later session — the return-to-zero test is the one that works before you know `C` at all. |
| 11 | Telemetry field width and the serial budget | S7 | Counts are the widest column in your CSV. A larger `C` means more digits per row, which eats the byte budget you sized in S7. Re-check that the row still fits at your loop rate before you conclude the port is fine. |
| 12 | Encoder wrap margin on the UNO | S3, S6 | `count_` is a **signed** 32-bit `long`, so the limit is 2³¹ / `C` ≈ 255,000 output revolutions at `C` = 8,400 — signed, because the count goes negative, which costs you one bit. Item 7 uses 2¹⁶ and this uses 2³¹ deliberately: **different objects, different widths, different signedness.** Item 7 is an unsigned hardware register; this is a signed software variable. Not a practical limit at any plausible ratio — but compute it once so you can say you did, and so item 7's contrast means something. |

> **WATCH OUT** — **Expect to run this page twice.** If Stage 2's torque budget sends you to Path A, the
> JGB37-520 is 11 PPR per channel at 270:1, so `C` becomes 11 × 4 × 270 = **11,880** and every row
> above moves again — this time on a motor you chose deliberately rather than one you were surprised
> by. That is not wasted work. Doing the exercise once on the N20 is exactly what turns the second
> pass into a half-hour instead of a week. Build the table with a spare column in it.

> **WHERE THIS POINTS** — Write this up in `docs/motor-spec.md`: the vendor's claim, your measurement, the
> discrepancy, and what you changed as a result. "The listing said 300:1, I measured 250:1, here are
> the twelve numbers that moved and here is the commit where each one changed" is a *better* portfolio
> artifact than the ratio having been right. It is evidence that you check things.

---

## Now go bolt a motor to a plank

Stage 0 does not need the printer, the ESP32s, the AS5600s, the CAN bus, or the electrodes. It needs
one motor, one driver, one encoder, a plank, and the patience to plot a step response and ask why it
looks like that.

Everything in Mimic is downstream of that one thing working.

---

## Figure index

Every figure in this document is plain ASCII/box-drawing art inside a fenced code
block, tagged `FIGURE <id> — <title>` on its first line. That is deliberate: it
renders correctly in GitHub and in any Markdown viewer, and it stays diffable in
Git. For a PDF export, set the monospace font to one with full box-drawing and
half-block coverage — **DejaVu Sans Mono** is the usual answer; the core PDF
monospace fonts do not carry the geometric and box-drawing characters these figures use — in this
volume: `╭ ╮ ╰ ╯ ╱ ╲ ▌ ◄ ► ▲ ▼ ↑ ↓ ← → ↔ ✗ ∫ · ╌ …` — and will drop or substitute them.

**Figure IDs in this volume carry the volume number** — `III.S9.1` is "Volume III,
session S9, figure 1". Without the prefix, Stage 0's `S2.1` and Stage 2's session
`S2.1` are the same string, and Stage 2 has its own `FIGURE S2.2.1`.

| Figure | Title | Where |
|---|---|---|
| **III.S2.1** | The power tree, the switch, and the single ground point | S2 |
| **III.S3.1** | Two channels, four states, one direction | S3 |
| **III.S3.2** | The same sixteen entries as a grid | S3 |
| **III.S5.1** | What jitter looks like, and where it comes from | S5 |
| **III.S6.1** | The conversion chain, both directions | S6 |
| **III.S9.1** | The four numbers, on one trace | S9 |
| **III.S10.1** | The loop, with both fixes in place | S10 |
