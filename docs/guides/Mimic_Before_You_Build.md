# Mimic — Before You Build

**Appendix Zero**

A beginner's orientation to Mimic — what it is, what every word means, what talks to what, and
everything to set up before Stage 0.

---

## How to Use This Document

This sits in front of Stage 0 and assumes you are starting from zero. Part I is pure explanation —
no tasks, nothing to install. Parts II through V are the actions.

Read Part I first, in one sitting, before you order anything. It is the longest part of this document
on purpose. Every other document in this project assumes the vocabulary and the architecture Part I
explains, and reading them without it is the difference between following instructions and
understanding what you are doing.

You will not retain all of it, and you are not meant to. The vocabulary, connection map, hardware and
software chapters are reference — flip back to them for the next year.

### The document set, and each one's job

| Document | Answers | When you read it |
|---|---|---|
| **This one** — Appendix Zero | *What am I looking at, and how do I set it up?* | Once at the start |
| **[Glossary](Mimic_Glossary.md)** — Appendix Zero-A | *What does that word mean?* | One block per session, on demand |
| **Mimic Project Guide** — Vol II | *Why this project, and what is each stage for?* | Once through, then whenever motivation dips |
| **Stage Workbooks** — Vols III–VI | *What do I do tonight?* | Open on the bench, every session |
| **What's Left to Buy** | *What do I still need?* | Before each stage's order |
| **Order Manifest** | *What did I already buy?* | Historical record. Never edit it. |

**The Glossary defines, this document orients and sets up, the Project Guide explains why, and the
workbooks instruct.** Anything that tells you what to do on a given evening — session order, the
arithmetic with your actual parts, code skeletons, and the test that closes each session — lives in a
workbook, not here. Anything that is a single term lives in the Glossary.

> **START HERE** — If you have not already, read
> **[the Glossary's first block](Mimic_Glossary.md#before-anything--the-words-the-rest-of-the-set-assumes)** —
> eighteen terms, about twenty minutes — before you go further into Part I. Every document in the set
> uses them without stopping to explain, and they are the difference between a sentence that is opaque
> and one that is merely new. [The reading order for the whole set](README.md) is one page.

> **GO TO THE WORKBOOK** — Wherever you see this box, stop reading and open the workbook for that stage.
> It means the explanation is finished and the work begins.

> **PORTFOLIO MOMENT** — And wherever you see this box, stop and produce something — a photographed
> derivation, a plotted result, a written decision. Mimic exists to be shown to someone. An artifact
> made the day you understood something is evidence; a write-up assembled at the end is a claim, and
> the difference is visible from across a room.

### The one idea underneath all of it

**Never debug on two fronts.** Almost every recommendation across these documents exists to collapse a
possible two-front fight into a one-front fight — which is why the stages are gated, why simulation
comes before cutting parts, why native Linux stops being optional at Stage 2, and why the motor gets
bolted to a plank.

> **WHERE THIS POINTS** — The repository is the deliverable. The arm is the reason to have one. A hiring
> manager will read your commit history, your README, your tuning plots and your fault-handling code —
> plausibly without ever seeing the hardware move. Set the repository up as though it is the portfolio
> piece, because it is.

### Time

An hour or two to read Part I. One evening for the repository and the toolchain installs. A second
evening for ROS 2, Gazebo and the CAN tooling, any time in the next two months.

> **WATCH OUT** — The failure mode for a document like this is treating it as a gate. It is not. Stage 0
> needs a motor, a driver, an encoder, a plank, and one piece of software. If you find yourself on
> evening four still configuring Linux, stop, go and close a control loop, and come back to the rest
> later.

---

# PART I — UNDERSTANDING THE PROJECT

---

## Start Here

### What you are building

A robotic arm that sits on your desk. About the size of a desk lamp, made of 3D-printed plastic links
with motors at the joints, with a gripper on the end. It plugs into your computer with a cable.

What makes it a learning project rather than a toy is how it is put together internally. Each joint
has its own small computer — a chip the size of a fingernail — whose only job is to hold that one
joint at whatever angle it has been told to hold. Those small computers are wired together on a
shared pair of wires, and your desktop talks to all of them over that pair. **That is the same way
real prosthetic limbs and real surgical robots are built.**

### What it will do when finished

- Hold a commanded angle against gravity and against you pushing on it, using control code you wrote.
- Move its gripper to a point in space you specify — "put the gripper here" rather than "set joint two
  to 43 degrees."
- Report everything it is doing — every angle, speed, and current — as data you can record, replay and
  graph.
- Find an object with a camera and work out how to grasp it.
- Understand a spoken instruction, processed on your own machine with no cloud service.
- Copy your own arm's posture from motion sensors strapped to you.
- Open and close its gripper from the electrical activity of your forearm muscles.

### What it will not do

It is not a medical device, it will not be strong, and its grip will be modest. Every open
3D-printed arm shares those limits. You are building it to learn the architecture, the control
theory, the firmware discipline and the signal processing that real assistive devices are made of.

### The shape of the year

| Stage | Name | Roughly | What you end up owning | Workbook |
|---|---|---|---|---|
| **0** | The Single Joint | 2–3 weeks | One motor on a plank holding a commanded angle | **Vol III**, 13 sessions |
| **1** | The Smart Joint | 4 weeks | Two joints on a CAN bus running identical firmware | **Vol IV**, 10 sessions |
| **2** | The Arm and ROS 2 | 8 weeks | A physical arm commanded in Cartesian space | **Vol V**, 15 sessions |
| **3** | Eyes and Voice | 3–4 weeks | An arm that sees and listens | **Vol VI** |
| **4** | The Biomech Payload | 4–5 weeks | An arm driven by your own muscles | **Vol VI** |
| **5** | Impedance *(optional)* | open | An arm that is compliant rather than stiff | **Vol VI** |

Roughly **five months of active work**, landing at about **seven months of calendar time** — the gap
is shipping, print time and the fact that some things do not go faster when you throw hours at them.
Project Guide Appendix G breaks this down and is where that arithmetic lives; the two figures agree
because they come from the same table.

### Money, and what you need on day one

The first order was placed on **31 July 2026: C$534 before tax, C$609 after 14 % NS HST**, covering
all of Stage 0 plus the tooling you need in the first month. Roughly **C$912 pre-tax remains**, spread
across the following six months of calendar time, bringing the project to about **C$1,446 pre-tax /
C$1,648 with HST**. See *What's Left to Buy* for the itemised list — including the honest note that
the tooling estimate was wrong by 53 % and is being masked by four later stages coming in slightly
under.

**Nothing is blocking.** Stage 0 needs one motor, one driver, one encoder, a plank, and a computer you
already own.

**Four things it needs are in no parts document at all**, because they were assumed rather than bought.
Check for all four this week rather than at 9 p.m. on the evening you wanted to run a session:

| Check | Needed by | If you do not have it |
|---|---|---|
| **~2 mm precision screwdriver** | S2 — it is the only thing that turns a multi-turn trim pot | C$5–8, Tier B |
| **A plywood board**, roughly 9.5 × 20 × 0.5 in | S1 — the rigid base, and the reason step responses are readable | Offcut, or C$10 |
| **Two G-clamps** | S1 — one at each end, and S1's own check needs the second | C$10 the pair |
| **A drill and a 3 mm bit** | S1 — heat-set inserts and through-bolts both need a drilled hole | Borrow, or C$40 |

None appears in the *Order Manifest* — not as a line item, not under *Already owned*, not under
*Deliberately deferred* — and none is in *What's Left to Buy*'s costed tiers, because all four are
things most people have. **That is exactly why they are worth checking rather than assuming**, and it
is the same discipline the manifest applies to the parts it does list.

---

## The Vocabulary

**Moved.** Every term this set assumes now lives in **[the Glossary](Mimic_Glossary.md)**, split by
the session that first needs it rather than by category. It was the middle third of this document and
it made this chapter unreadable in one sitting, which is the only way anybody was ever going to read
it.

**What to do with it:** read *Before anything · the words the rest of the set assumes* — eighteen
terms, about twenty minutes — before you carry on with Part I. Everything else waits until a session
asks for it, and every session now names its block by title.

| You are | Read |
|---|---|
| Here, now, starting Part I | [Before anything](Mimic_Glossary.md#before-anything--the-words-the-rest-of-the-set-assumes) — 18 terms |
| Opening a Stage 0 session | That session's block. Six to ten terms |
| Stuck on a word, anywhere | Search the Glossary. Every term the set uses is in it |

---

## The Architecture, Plainly

### Two layers, two different jobs

```
FIGURE 0.1 — The two layers, and the seam between them

   ┌──────────────────────────────────────────────┐
   │  HOST  — your desktop, Linux, ROS 2          │
   │  Plans motions · sees · listens · records    │
   │  Soft real-time: late is degraded, tolerable │
   └───────────────────┬──────────────────────────┘
                       │  serial / CAN gateway
   ┌───────────────────┴──────────────────────────┐
   │  JOINTS — one microcontroller each, on CAN   │
   │  Holds an angle. Nothing else.               │
   │  Hard real-time: late is a system failure    │
   └──────────────────────────────────────────────┘
```

### Why split it at all

Because the two halves want incompatible things.

The bottom layer needs **guaranteed timing**. A control loop that runs at 1 kHz must run at 1 kHz
every single time, because the integral and derivative terms are defined in terms of elapsed time. A
microcontroller with nothing else to do can promise that. Linux cannot.

The top layer needs **libraries, filesystems, and processing power** — a motion planner, a camera
pipeline, a speech model. None of that fits on a microcontroller and none of it needs microsecond
timing.

The words for those two promises are **hard real-time** and **soft real-time**, and they are in
[the Glossary](Mimic_Glossary.md#before-anything--the-words-the-rest-of-the-set-assumes).

### Why every joint gets its own microcontroller

You could run all four joints from one board. Many hobby arms do. Four reasons Mimic does not: it is
**how the field actually works** (Dynamixel servos, ODrive controllers and real prostheses are all
independent nodes on a bus); it **forces you to design a protocol** rather than call a function; it
**puts CAN on your résumé**, which is common in job postings and rare in hobby portfolios; and it
**scales without redesign** — write the firmware once, flash it four times with different node IDs.

> **WHERE THIS POINTS** — That is the sketch, and it is all you need to read Part I. **The full version
> is [Project Guide → Chapter 2](Mimic_Project_Guide.md#chapter-2--the-architecture)**, which is the
> same argument with the rates on the diagram, the cost of the decision stated honestly, and a section
> on the seam itself that this document does not attempt. Read it on the evening you read the Project
> Guide — third, after this document — not now.

---

## Follow One Command, End to End

Worth reading slowly once. Everything in the project appears here in order.

### Down: from your voice to a spinning motor

1. **You speak.** "Pick up the blue block." A microphone on your desktop records it.
2. **Speech to text.** A Whisper model running locally on your machine turns the audio into a string.
   No cloud service.
3. **Text to intent.** A local language model converts that string into a *structured command* — an
   action name and parameters — not prose.
4. **Validation.** Your code checks the command is legal: is that action in the allowed set, is the
   target reachable, are the joint limits respected. **The model proposes; your code decides.**
5. **Perception.** The camera finds the block, recovers its pose, and publishes it as a coordinate
   frame the arm understands.
6. **Planning.** MoveIt 2 computes a path from where the arm is to where the gripper needs to be,
   avoiding collisions.
7. **Inverse kinematics.** The path in Cartesian space becomes a sequence of joint angles.
8. **The hardware interface.** A `ros2_control` plugin writes those target angles out — down the USB
   cable to a gateway microcontroller.
9. **The gateway.** It packs each target into an 8-byte CAN frame with the right identifier and puts
   it on the bus.
10. **The joint hears it.** Hardware filtering means it only receives frames addressed to its node ID.
11. **The control loop.** Every millisecond: read the encoder, compute the error, run PID, write a PWM
    duty cycle and a direction.
12. **The driver.** The TB6612FNG converts a logic-level signal — 5 V from the UNO in Stage 0, 3.3 V from the STM32 in Stage 1; it accepts both — into 12 V at an amp.
13. **The motor turns.**

### Back up: how the host knows what happened

The encoder counts. The joint packs position, velocity and current into a state frame. The gateway
forwards it. The hardware interface's `read()` fills in the state. `robot_state_publisher` updates the
transform tree. rviz2 draws it. `ros2 bag` records it. And your plotting script graphs it afterwards.

### The single most important thing on these two pages

**Every single one of those thirteen steps is something you build.** Not one of them is a library you
import and trust. That is what makes this a portfolio rather than an integration exercise — and it is
why Stage 0 is a motor on a plank rather than a kit.

> **PORTFOLIO MOMENT** — Redraw this chain by hand, once, when you have finished Stage 1 — with the
> pieces you have actually built filled in and the rest greyed out. Update it at each gate. It is the
> single best "here is what I built" diagram you will ever have for this project, and watching it fill
> in is also excellent for morale on the bad weeks.

---

## Inside One Joint

One joint, from the outside in:

| Piece | Job | What you own |
|---|---|---|
| **Motor** | Turns electrical power into rotation | 12GA-N20, 12 V, 100 RPM |
| **Gearbox** | Trades speed for torque, **~300:1 — unverified, you measure it in Stage 0 S1/S3** | Built into the motor |
| **Encoder** | Reports how far the shaft turned | Hall sensor, 7 PPR/channel, on the motor shaft |
| **Driver** | Amplifies logic-level commands to motor power | TB6612FNG |
| **Microcontroller** | Runs the control loop | Arduino UNO R3 / ATmega328P (Stage 0) → STM32 (Stage 1) |
| **Current sensor** | Measures torque indirectly | INA219 |
| **Limit switch** | Tells you where zero is | Roller-lever microswitch |

### Walking the loop once

Every tick, at a fixed rate:

```
FIGURE 0.2 — One tick of the control loop, in order

   read encoder  →  convert counts to radians  →  error = target − actual
        ↓
   PID computes a correction  →  clamp it  →  convert to duty + direction
        ↓
   write PWM and direction pins  →  motor responds  →  encoder counts
        ↓
   (repeat, exactly on time)
```

### What Stage 1 changes, and what it does not

The **controller does not change.** The scheduling does. On the UNO you poll `micros()` and return
early when it is not time yet. On the STM32 a hardware timer fires an interrupt at exactly your
control period, and the control loop *is* the handler. It runs at the right time because the hardware
makes it, not because your code remembered to check.

Two other things improve: quadrature decoding moves from a software interrupt handler consuming a few
percent of the UNO's CPU into a hardware peripheral consuming none, and PWM goes from 490 Hz with 256
duty steps — 31 kHz with 256 steps once Stage 0 session S11 reconfigures Timer1 — to 20 kHz with
9,000 steps on the STM32.

---

# PART II — THE MACHINES

---

## What Runs Where

| Machine | Role | From when |
|---|---|---|
| **Ubuntu 24.04 laptop** | All of it: editing, flashing, serial, plotting, ROS 2, Gazebo, socketCAN | Day one |
| **Arduino UNO R3** (ATmega328P) | Stage 0 control loop | Day one |
| **STM32 Nucleo-F446RE** | Stage 1 joint firmware | Week 3–4 |
| **ESP32-S3 ×2** | Stage 1 CAN bus monitor; later, joints 3 and 4 | Stage 1 |

### One host, and why that is the point

**One machine, running native Ubuntu 24.04, does all of it.** PlatformIO flashes the board over USB
and reads the serial back. Python captures and plots. ROS 2 and Gazebo run on real graphics. `candump`
talks to a real kernel interface. Nothing in this project needs a second operating system, and the
single-host arrangement is worth more to you than the convenience of it.

The reason is diagnostic rather than aesthetic. **A virtualisation layer is a second thing that can be
wrong, and from inside the failure you cannot tell which of the two it was.** When a node cannot find
its peer, when a board does not enumerate, when the simulator renders a black window, you want exactly
one place to look. Every one of those has a mundane native-Linux explanation — a udev rule, a group
membership, a graphics driver — and each is a thing you can learn once and then own. Across a boundary
the same three symptoms are unattributable, and you spend the evening debugging the layer rather than
the robot.

> **WATCH OUT** — If you draft code somewhere else because the screen is bigger, **sync through
> GitHub** — commit and push there, pull here — and never through a shared folder or a mounted
> filesystem. Two clones of one repository is a workflow; one directory reached from two operating
> systems is line-ending churn, permission surprises and half-written files. **The Ubuntu machine is
> the machine of record**: it is the one that builds, flashes and measures, and a number is not
> measured until it was measured there.

### Why it has to be native Linux

`socketCAN` is a kernel feature — `candump` and `cansend` have nothing to attach to without the
module. Gazebo needs real GPU access through a real graphics stack. ROS 2 discovery needs a real
network stack with no boundary in the middle. None of the three is a preference; together they are
why the host is a machine rather than an environment running inside one.

**Ubuntu 24.04 specifically**, because ROS 2 Jazzy's apt packages are built for it. The distribution
is not a detail you can absorb later — a rolling-release or security-testing distribution carries a
different package set on a different cadence, and matching the ROS release to the Ubuntu release it
targets removes an entire category of install failure before you ever meet it.

### Why not a Raspberry Pi

It does not fix the Linux question — you would still be installing Ubuntu, just on slower hardware.
Its actual job is untethering the arm from a desk, which Mimic never needs. And it is not cheap once
you add the PSU, storage and case. A used small-form-factor office PC is both cheaper and more capable
for something that never leaves a desk.

---

# PART III — THE REPOSITORY

---

## Creating It

The Project Guide's first standing rule is **git from the first commit**: one repository, branches per
stage, tagged releases at each exit gate. The temptation with hardware is to treat firmware as
disposable scratch work. Resist it — your Stage 0 tuning history is the artifact someone will actually
read.

### One repository, pushed to GitHub

One rather than several, because the point of Mimic is that it is a *system* — firmware, host software
and mechanical design coupled through interfaces you designed. Splitting them hides the thing worth
showing.

### A structure that survives to Stage 4

```
  mimic/
  ├── firmware/
  │   ├── stage0-uno/              # PlatformIO project, the PID rig
  │   └── stage1-stm32/            # CubeIDE project, FreeRTOS + CAN
  ├── ros2_ws/
  │   └── src/                     # Stage 2+. Only src/ is tracked.
  ├── hardware/
  │   ├── cad/                     # STEP and source files
  │   ├── wiring/                  # photographs, every change, dated
  │   └── bom.md
  ├── docs/
  │   ├── decisions/               # ADRs — why, not how. Created with the FIRST one
  │   ├── derivations/             # scanned handwritten maths. YOURS
  │   ├── reference/               # datasheets and vendor material. NOT yours
  │   ├── sessions/                # one folder per session, written afterwards
  │   ├── tuning/                  # gains, plots, measured numbers
  │   │   ├── raw/                 # captured CSVs
  │   │   └── plots/               # generated PNGs
  │   ├── guides/                  # this document set, committed alongside the work it describes
  │   ├── motor-spec.md            # your measured motor constants
  │   └── protocol.md              # your CAN message spec
  ├── tools/                       # capture.py, plot.py, kinematics.py, requirements.txt
  ├── .github/workflows/ci.yml     # builds the firmware on every push
  ├── .gitignore
  ├── .gitattributes               # LFS tracking — set up on day one
  ├── .editorconfig                # what your EDITOR writes. A different layer
  ├── .clang-format                # what the FORMATTER writes. The C++ layer
  ├── .website-capture.md          # the capture tracker. Gitignored, never committed
  ├── LICENSE
  ├── CHANGELOG.md                 # one entry per exit-gate tag
  └── README.md
```

**Four of those folders exist to be told apart, and mixing them is the one filing mistake that costs
you later.** `derivations/` is work in your handwriting. `reference/` is material you fetched from
somebody else. `tuning/` is numbers you measured. `decisions/` is choices you made. Each one has a
`README.md` in it drawing the line, and the test is ownership: if you did not produce it, it is
`reference/`; if you produced it and it is a number, it is `tuning/`; if it is a number you cannot
reproduce because it was a judgement call, it is `decisions/`.

`docs/decisions/` is the only folder in that tree that does not exist yet. It is created the evening
you write the first ADR, because an empty folder of decisions is a claim that you have been making
them. The ADR shape is in "Decisions get their own files", further down this part.

`docs/derivations/` is the highest-value folder in the repository for what you are trying to do. A photographed page of your own algebra, committed the day
you did it, is evidence. A tidy write-up produced at the end is a claim.

### Branches and tags

- `main` — always in a state you would show someone.
- `stage0`, `stage1`, … — the working branch per stage, merged to `main` at the exit gate.
- Short-lived branches off those: `stage0/antiwindup`, `stage1/can-timeout`.
- An annotated tag at every exit gate: `v0.0-stage0-exit`. The gates are the natural release points,
  and a tag is what lets you point at the commit where the joint first held position against a
  disturbance.

> **WHERE THIS POINTS** — Commit history is the one part of a portfolio that cannot be retroactively
> faked into looking like engineering. A single dump commit reads as a tutorial followed. Forty commits
> showing a gain raised, an oscillation appearing, a clamp added and a plot attached reads as someone
> who can debug. Commit small and commit often, including the failures — especially the failures.

### A `.gitignore` worth having on day one

```
# ROS 2 / colcon — generated, large, machine-specific
build/
install/
log/

# PlatformIO
.pio/
.pioenvs/

# STM32CubeIDE
Debug/
Release/
*.launch

# Python
__pycache__/
*.pyc
.venv/
venv/

# Bag files and datasets — use Git LFS or keep out of git
*.db3
*.mcap
rosbag2_*/

# OS noise
.DS_Store
Thumbs.db
desktop.ini
```

> **WATCH OUT** — Two things will try to bloat this repository: `ros2 bag` recordings and CAD binaries.
> Set up **Git LFS on day one**, not after the first 400 MB file lands — rewriting history to remove
> one is a bad evening. And note that writing `.gitattributes` is not enough: you must actually run
> `git lfs install` once on each machine, or the tracking rules do nothing.

### The README is an argument, not documentation

A hiring manager looks for whether the README explains **decisions**, not usage. Structure it around
choices: why CAN and not a serial daisy chain, why an RTOS task instead of one big loop, why the
emergency stop message has the identifier it has, what a joint does when the host goes silent and why
holding position beats continuing the last velocity command.

Start it today with three sentences saying what Mimic is. It grows with the project, and it grows far
better than it gets written from nothing at the end.

**Include, prominently:** *Mimic is a learning platform. It is not a medical device and must not be
used as one.* Keeping that boundary explicit is part of behaving correctly in this field.

---

## The Documentation Discipline

Two of the three standing rules are about record-keeping, and both exist because **hardware has no
`git diff`**. They are trivial to follow from day one and nearly impossible to reconstruct later.

### Photograph every wiring change

Not for the README, though it helps there. For yourself, three weeks later, when a joint stops working
and you need to know what changed. Phone camera, into `hardware/wiring/`, filename with the date.
There is no version control for a breadboard.

### Write down the number

When you tune a gain, log the value and what it did. When you measure a current draw, write it down.
Control work is empirical, and an undocumented experiment is one you will repeat.

A file per session in `docs/tuning/` is enough:

```
## 2026-08-04 — Stage 0, step response, 12GA-N20 on plywood

Setup:   12V, TB6612FNG, 10ms loop (100 Hz), setpoint step 0 -> 90 deg
Encoder: 7 PPR/channel x 4 (quadrature) x ~300:1 gearbox
         Expected: ~8400 counts/output rev
         MEASURED: <your figure> — ten turns of the output shaft, divided by ten
Deadband: duty <your figure> of 255

| Run | Kp   | Ki   | Kd   | Rise  | Overshoot | Steady err | Note
|-----|------|------|------|-------|-----------|------------|----------------------
| 1   | 0.5  | 0    | 0    | 480ms | 0%        | 6 deg      | never arrives, expected
| 2   | 2.0  | 0    | 0    | 180ms | 4%        | 2 deg      |
| 3   | 2.0  | 0.8  | 0    | 175ms | 22%       | 0 deg      | integral windup on step
| 4   | 2.0  | 0.8  | 0.05 | 190ms | 9%        | 0 deg      | D helps, noisy
| 5   | 2.0  | 0.8  | 0.05 | 185ms | 5%        | 0 deg      | + clamp on I. Keeping.

Measured: stall current <yours>, no-load <yours>
Plot:     docs/tuning/plots/2026-08-04-run5.png
Next:     derivative on measurement instead of error
```

> **WATCH OUT** — **The gain values above are an illustration of the format, not starting points.** They
> were not measured on your motor, and neither was the encoder line. Copying either is the specific
> risk this box exists to name.
>
> Consider what it costs to get an encoder constant slightly wrong twice. Write `7 CPR × 100:1 = 700
> counts/rev` and you have made two small errors: you dropped the ×4 quadrature factor, and you used a
> ratio that is not yours — 100 instead of roughly 300. Neither looks serious alone. Compounded they
> are a **factor of twelve**, `700` against `8,400`, and every angle your controller computes is wrong
> by that constant. The symptom is a loop that overshoots and will not settle, which reads as a badly
> tuned gain rather than as arithmetic — so you would spend an evening turning knobs before you
> thought to check the constant.
>
> **Two small mistakes multiplying into a large one is the normal shape of a unit bug.** Derive the
> number from your own encoder and your own measured ratio, and never copy it from a document —
> including this one. Stage 0 Workbook S1 is where you actually do that, and it carries the full
> version of this argument alongside the measurement; this box exists so that the log format above
> cannot be copied without the warning attached.

### Decisions get their own files

When you make a choice that had alternatives — the CAN identifier layout, the state publication rate,
whether joints publish autonomously or the host polls, whether zero command means coast or brake —
write a short file in `docs/decisions/`. Use the standard ADR shape: **Context, Decision, Alternatives
Considered, Consequences.** Four sentences each is plenty.

This is the highest-leverage documentation habit available to you, because these are exactly what an
interview probes. None of them have a single right answer, and **having reasoned about them is the
skill**. A file written the day you decided is evidence; a recollection eight months later is a guess.

> **PORTFOLIO MOMENT** — At each stage exit gate, spend one evening writing up what you learned — not a
> tutorial, a record. What the oscillation looked like at your ultimate gain. What integral windup felt
> like when you held the shaft. Which of your bugs turned out to be electrical rather than software.
> Publish it with the plots, and tag the commit. "Here is what surprised me" reads far better than
> "here is what I built."

---

# PART IV — INSTALLING

---

## The Bench Toolchain

The set that matters this week, because Stages 0 and 1 both live here. Everything below is free, and
most of it is one `apt` line:

```bash
sudo apt update && sudo apt install build-essential git git-lfs cmake \
     python3-venv python3-pip pulseview sigrok-firmware-fx2lafw
```

| Software | Why, and when |
|---|---|
| **Git** | From `apt`. Set `user.name` and `user.email`. There is no line-ending setting to get right on this machine — see "Line endings" below for what the repository does instead, and why that is the better place for the rule to live. |
| **Git LFS** | The package is `git-lfs`; installing it is **not** the same act as running `git lfs install`, which is what actually activates the filters. Do both. Writing `.gitattributes` without the second does nothing. |
| **VS Code** | From Microsoft's apt repository or their `.deb`. Host for PlatformIO and a decent editor for everything else. |
| **PlatformIO** (VS Code extension) *or* Arduino IDE | Stage 0. PlatformIO is the better long-term choice — real dependency management, per-project configuration, host-side unit tests, and it targets ESP32 and STM32 as easily as AVR. Arduino IDE gets you a first blink faster. |
| **udev rules and group membership** | **Do not skip this.** A USB board on Linux is a device node owned by root, and until a rule says otherwise your user cannot open it. Install PlatformIO's `99-platformio-udev.rules` as their documentation currently describes, `sudo udevadm control --reload-rules && sudo udevadm trigger`, then `sudo usermod -aG dialout $USER` and **log out and back in** — group membership is read at login and this is the step people miss. **Without it a perfectly good board looks broken**, or works only under `sudo`, which is a habit worth never forming. |
| **Python 3.12** with `pyserial`, `matplotlib`, `pandas` | Python is already on the system; the three packages are not. **Ubuntu 24.04 refuses a system-wide `pip install`** with `error: externally-managed-environment` — that is PEP 668 protecting the packages `apt` owns, and it is correct rather than an obstacle. Make a virtual environment at the repository root and install `tools/requirements.txt` into it. **Stage 0 requires these three and nothing else on this list provides them**: session S7 captures a step response over serial and plots it. |
| **PulseView / sigrok** | Logic analyzer software — plus **`sigrok-firmware-fx2lafw`**, which is the firmware your FX2-based analyzer has loaded into it at plug-in time. It has no flash of its own; it is a blank chip until something feeds it. **Without that package the device enumerates, PulseView still cannot use it, and it looks like a faulty purchase.** Install both now and confirm the device appears when it arrives. |
| **STM32CubeIDE** | Stage 1. ST ships a Linux installer; let it install the ST-Link udev rules when it offers, for the same reason as the row above. Bundles CubeMX, the compiler and the debugger. Install it early — it is a large download with a fussy first run, and you do not want to meet it on the evening you are excited to start Stage 1. |
| **A serial terminal** | The monitor built into PlatformIO, plus `picocom`, `minicom` or `screen` for when you want one outside the editor. You will live in this during Stage 0. |
| **A CAD package** | **Stage 2, and nothing else on this list replaces it.** Pick one and commit: **FreeCAD** (free, open source, packaged for Ubuntu, exports STEP, and — the reason it matters here — nothing you make is hostage to a licence you might lose), or **Onshape** (free hobby tier, runs in a browser so the operating system is irrelevant, easy; but hobby documents are *public*, which is fine for an open portfolio and not fine for anything else). **Fusion 360 is not an option here** — Autodesk ships no Linux build, and the unofficial wrappers around it are one more layer to debug for no gain. Install your choice now and do one tutorial; do not meet it for the first time on the evening you want to design a link. |
| **A slicer** | Turns your CAD into printer instructions. **OrcaSlicer** or **PrusaSlicer**, both of which ship Linux builds, or whatever comes with your printer. Only needed once the printer arrives, but it is a free download and a concept worth meeting early. |

> **CHECK YOURSELF** — The bench is ready when PlatformIO builds and uploads a blink sketch to a board
> **without `sudo`**, a serial monitor shows output from it, `git push` works without prompting for a
> password, PulseView lists your analyzer, `python -c "import serial, matplotlib, pandas"` runs without
> error inside your virtual environment, and STM32CubeIDE has finished its first launch and update
> cycle. **The `sudo` clause is the load-bearing one.** If you needed it, your udev rules or your group
> membership are wrong, and ten minutes now saves you an hour of misattributed confusion in Stage 1.

> **WHERE THIS POINTS** — Getting the STM32 debugger working — actually stopping at a breakpoint and
> inspecting a variable — is the single biggest quality-of-life difference between Arduino and
> professional embedded work. It is also what most people skip, because print statements feel
> sufficient. Do not skip it. Stage 1's first milestone is a blinking LED whose entire purpose is
> proving the toolchain and the debugger, not the LED.

---

## The build system, and the files that configure it

You have just installed a set of tools, and the repository already contains a dozen files that
configure them. This chapter is what those files are. **None of it is Mimic-specific** — it is the
layer every embedded project sits on, it is assumed rather than taught in almost all of them, and
not knowing it is the difference between a project that builds on your machine and one that builds
anywhere.

Read it once, now, with `firmware/stage0-uno/platformio.ini` open beside you. Twenty minutes. You
will come back to it.

### PlatformIO — what a build system does that an IDE does not

An IDE is an editor with a compiler bolted to it. A **build system** is a program whose only job is
to turn a described project into an artifact: it reads a file that says what you are building and
for what, works out what has to be compiled and in what order, fetches anything missing, and runs
the compiler for you.

The difference that matters is **where the configuration lives**. In the Arduino IDE, your board,
your port and your compiler flags are settings inside the application — invisible, unversioned, and
attached to your installation rather than to your project. Hand somebody your sketch and you have
handed them the source and not the build. In PlatformIO, all of it is in `platformio.ini`, that file
is in the repository, and cloning the project *is* getting the build.

That is the whole argument, and it is why the CI job in this repository can exist at all: a machine
that has never seen your project can clone it, read one file, and produce the same image you get.

> **DEFINITION** — **Environment.** In PlatformIO, an **environment** is one named configuration —
> one target, one framework, one set of flags — declared as an `[env:name]` block. A project can
> have several, and yours has two, which is the single most useful thing in the file. `uno`
> cross-compiles for the ATmega328P and uploads to the board. `native` compiles for *this* machine,
> the one you are sitting at, with no board attached, and runs the result. Most of what you write in
> Stage 0 is arithmetic wearing a hardware costume, and `native` is where you test it in
> milliseconds instead of at a bench.

**What it costs.** A first-run download of a toolchain and a platform package, roughly a few hundred
megabytes, and a build that is slower than Arduino's the first time and faster afterwards. You also
lose the Arduino IDE's one genuine advantage, which is that it works before you understand it.

### `platformio.ini`, key by key

```ini
[platformio]
default_envs = uno                ; which env runs when you do not name one

[env]                             ; settings shared by EVERY environment below
build_flags = -Wall -Wextra       ; extra compiler warnings, on by choice

[env:uno]
platform      = atmelavr@^5.3.0   ; the CHIP FAMILY toolchain. Which compiler, which
                                  ;   uploader, which register definitions. The @ pins
                                  ;   which version of it you get.
board         = uno               ; the specific BOARD. Sets the exact chip, the clock
                                  ;   speed, the flash and RAM sizes, and the upload
                                  ;   protocol. platform is the family; board is the part.
framework     = arduino           ; the API layer you write against. `arduino` gives you
                                  ;   pinMode, digitalWrite, Serial and the core that
                                  ;   defines main() for you. Omit it and you are bare
                                  ;   metal, which is where Stage 1 goes deliberately.
monitor_speed = 250000            ; baud rate `pio device monitor` opens at. It must match
                                  ;   your Serial.begin(). 250000 rather than 115200 is
                                  ;   derived in Stage 0 S7 and it is not arbitrary.

[env:native]
platform       = native@^1.2.1    ; no cross-compiler at all — build for THIS machine
test_framework = unity            ; which unit-test framework `pio test` should expect
build_flags    = -std=c++17 -I include
```

Five of those deserve a sentence more than they look like they need.

**`platform` versus `board`.** `platform` chooses a whole toolchain — the compiler that targets AVR
chips, the tool that talks to their bootloader, the headers that define `TCCR1B`. `board` picks one
part within it and fills in the specifics: 16 MHz, 32 KB of flash, 2 KB of RAM, `avrdude` over
serial at a particular baud. Getting `board` wrong compiles fine and produces an image for the wrong
chip.

**The `@` in `atmelavr@^5.3.0`.** Write `platform = atmelavr` on its own and you have asked for
*whatever version is newest on the day the line is read* — and it is read again every time somebody
builds from a clean checkout, which is exactly what the CI runner does. You resolve it once in
August; a runner resolves it again in March and can get a different compiler. `^5.3.0` means 5.3.0 or
newer but not 6, so fixes still reach you and the breaking change does not. It is the same compromise
the Actions chapter makes with `actions/checkout@v5`, applied to the layer underneath. The failure it
prevents is a quiet one: not a broken build, but a build you did not change, warning about something
it did not warn about last month, in code you have not touched since. That is a long evening, and the
cure is seven characters.

**`framework`.** This is the honest name for what Arduino is: a **hardware abstraction layer plus a
core**. It supplies `main()` — which then calls your `setup()` once and your `loop()` forever — and
it wraps register writes in functions with readable names. Stage 0 S11 bypasses one of those
wrappers on purpose, and Stage 1 removes the framework entirely. Knowing it is a *layer*, and a
removable one, is the point.

**`build_flags`.** Arguments passed straight to the compiler. `-Wall -Wextra` ask it to complain
about far more than it does by default, and you want that: on a chip with no operating system to
catch you, a warning about a comparison between signed and unsigned is frequently a bug you have not
found yet. `-I include` tells the compiler where to look for headers, and `-std=c++17` fixes the
language version so the same code means the same thing on every machine.

**`monitor_speed` is not a setting on the board.** It is what your terminal opens at. Nothing
enforces that it matches `Serial.begin()` in your firmware, and when it does not you get fluent,
confident garbage rather than an error.

> **CHECK YOURSELF** — Why does `[env:native]` have no `board` and no `framework`? Answer before you
> read on. If your answer names the two things a native build has no need of, you have understood
> what those keys are for better than the descriptions above can tell you.

### `include/`, `src/`, `lib/`, `test/` — and why the headers are not beside the source

PlatformIO expects four directories and each one means something specific:

| Directory | What goes in it |
|---|---|
| `src/` | Your `.cpp` files. Compiled and linked into the firmware image |
| `include/` | Your `.h` files — the declarations. On the compiler's include path automatically |
| `lib/` | Private libraries, each in its own subfolder. You will probably never use it |
| `test/` | Unit tests, one subfolder per test group. **Not** compiled into the firmware |

The C convention most people meet first is to put `encoder.h` next to `encoder.cpp`, and this project
does not. The reason is `test/`: a test file in `test/test_encoder/` needs to `#include "encoder.h"`,
and if that header lives in `src/` the test has to reach sideways into the firmware's source tree
with a relative path — `#include "../../src/encoder.h"` — which is fragile, ugly, and breaks the
moment anything moves. With headers in `include/` and `-I include` in the flags, every consumer says
`#include "encoder.h"` and neither knows nor cares where the implementation is.

**That is the general shape of the idea, and it is worth having:** the header is the *interface* and
the `.cpp` is the *implementation*, and things that depend on you should depend on the first without
being able to see the second.

> **DEFINITION** — **`#pragma once`, and the problem it solves.** A header can be included more than
> once in a single compilation — directly by your file and again by another header it includes — and
> the second time, every declaration in it is a duplicate, which is an error. The classic fix is an
> **include guard**: three lines of preprocessor at the top and bottom defining a unique symbol and
> skipping the body if it is already defined. `#pragma once` is one line that means the same thing,
> is understood by every compiler you will meet, and cannot be broken by copying a header and
> forgetting to rename its guard symbol — which is the specific bug include guards produce and it is
> maddening, because the file simply and silently does not exist. It is not in the C++ standard,
> which is the only argument against it and not a practical one.

### Cross-compilation, and what a toolchain actually is

When you run `pio run -e uno`, the compiler that runs is not the compiler that would build a program
for your desktop. It is a different program, `avr-gcc`, which runs on your x86 machine and emits
machine code for an 8-bit AVR — an instruction set your desktop cannot execute at all. That is
**cross-compilation**: the *host* and the *target* are different machines, which is the pairing the
vocabulary chapter introduced.

A **toolchain** is the full chain of programs that gets you from text to a running chip:

```
   your .cpp  ──[ compiler ]──►  .o object files
                                     │
                     the Arduino core, precompiled
                                     │
                              [ linker ]  ──►  .elf  (code + symbols + debug info)
                                                 │
                                          [ objcopy ]  ──►  .hex  (just the bytes)
                                                              │
                                                       [ avrdude ]  ──►  the chip
```

Four programs, and Stage 0 S0's *CHECK YOURSELF* asks you to name them before you are told, for a
reason: in three weeks one of them will fail, and "which of the four?" is the first useful question.
Interlude E of the *Project Guide* covers this pipeline properly.

**What it costs.** You cannot run your firmware to test it, which is why `[env:native]` exists and
why anything you can express as pure arithmetic is worth keeping separable from anything that
touches a pin.

### Unity — what a unit-test framework is in C

**Unity** is a unit-test framework for C, small enough to run on a microcontroller and simple enough
to read in an afternoon. It gives you assertion macros (`TEST_ASSERT_EQUAL`,
`TEST_ASSERT_FLOAT_WITHIN`, and so on), and three things that structure a run:

- **`setUp()`** — runs before *every* test. Put the fresh object under test here, so no test can be
  affected by what a previous one did to it.
- **`tearDown()`** — runs after every test. Usually empty in a project this size.
- **`RUN_TEST(fn)`** — called from `main()` between `UNITY_BEGIN()` and `UNITY_END()`, once per test
  function. It is what actually runs one, catches its failures, and reports them.

There is no discovery and no reflection. **You list your tests by hand**, which feels primitive after
any language with a test runner, and it is a fair price for a framework that fits on a chip with two
kilobytes of RAM.

> **WATCH OUT** — **The runner in `test/test_pid/test_pid.cpp` is deliberately left unwritten**, and
> it is the one thing in that file you should not fill in early. A `main()` that calls
> `UNITY_BEGIN()` and `UNITY_END()` with no `RUN_TEST` between them **passes**. So does one whose
> test bodies are empty, which is what they currently are. Wire it up in Stage 0 S12, when there are
> real assertions for it to run, and not before — because a green CI badge earned by running nothing
> is worse than no badge at all. It is a claim you did not check.

### The `pio` commands you will actually use

| Command | What it does | When |
|---|---|---|
| `pio run -e uno` | Compile only. No board needed | Constantly. It is the fastest way to find out if you broke something |
| `pio run -e uno -t upload` | Compile, then flash the board | Every time you want to see a change on hardware |
| `pio device monitor -b 250000` | Open a serial terminal | Your main window into Stage 0 |
| `pio test -e native` | Build and run the host-side tests | From S12 |
| `pio run -t clean` | Delete the build output | When you suspect a stale build, which is rarer than people think |

Add `-d firmware/stage0-uno` to any of them to run from the repository root instead of from inside
the project.

### Git LFS — and why `.gitattributes` alone does nothing

Git stores every version of every file forever. That is exactly what you want for source and exactly
wrong for a 6 MB phone photograph you will replace four times, because the repository keeps all five
and everyone who clones it downloads all five.

**Git LFS (Large File Storage)** solves it by substitution. A tracked file is replaced *in the
repository* by a small text pointer, and the real bytes go to a separate store that is fetched only
for the version you actually check out. Your working directory looks identical; the history does not
carry the weight.

Two consequences and one trap.

- **The rules live in `.gitattributes`**, which is committed, so everyone who clones gets them.
- **`git lfs install` is per machine, per user — and it is a separate act.** It installs the git
  filters that make the substitution happen. Without it, `.gitattributes` is a file full of rules and
  **nothing enforces them**: your photographs go into git proper, silently, with no error and no
  warning, and you find out when the repository is 400 MB.

> **WATCH OUT** — **`apt install git-lfs` is not `git lfs install`, and it is easy to believe you have
> done the second because you did the first.** One puts the binary on the machine; the other writes the
> filter configuration into your user's git config, and only the second makes the rules in
> `.gitattributes` actually fire. Run it before you commit anything. Undoing this means rewriting
> history, which is a bad evening. `git lfs env` tells you in one line whether it is active.

### Line endings, and why the repository says what it wants out loud

Windows ends a line with two characters, `CR LF`. Linux and macOS use one, `LF`. You are on Linux, so
none of this is currently your problem — which is exactly why it is worth understanding now rather
than the evening somebody else clones this repository and their editor quietly rewrites every file
in it.

`.gitattributes` says `* text=auto eol=lf`, and that line is doing the work: **it is the repository
stating what it wants regardless of anybody's local setting.** The per-machine setting that can also
translate is `core.autocrlf`, and it is worth being able to read:

| Value | What it does | Who wants it |
|---|---|---|
| `input` | Convert `CRLF` to `LF` on commit; do not convert on checkout | A Windows clone of this repository |
| `true` | Convert both ways — `LF` in the repo, `CRLF` in your working tree | The Windows default. Not this project |
| `false` | Never convert | A Linux-only machine, where nothing needs converting |

**The reason the repository does not simply rely on that setting** is that the conversion happens at
*commit time* and is not retroactive. Someone clones with the wrong value, edits a file, and `CRLF`
goes into your history; correct the setting afterwards and every one of those lines shows as changed
the next time anything touches the file, producing diffs where a one-character fix appears as a
200-line rewrite. **The damage is in the history rather than the working tree** — so the repository
declares its own rule in a committed file instead of depending on anyone remembering, which is the
shape of every convention worth having here.

> **DEFINITION** — **`.editorconfig`, and why it is a different layer.** `.gitattributes` governs
> what lands **in the repository**; `.editorconfig` governs what your **editor writes** in the first
> place — indent style and width, final newline, trailing whitespace, maximum line length — and it is
> understood natively or by plugin in VS Code, CubeIDE and essentially everything else. The two are
> complementary rather than redundant: one is a last line of defence at commit time, the other stops
> the problem happening. Note the entry in this repository's file exempting `docs/guides/*.md` from
> trimming and wrapping, because these documents' figures are drawn to the column and a reflow
> destroys them silently.

> **DEFINITION** — **`.clang-format`, and the layer below that again.** `.editorconfig` can say that
> a C++ file indents by two spaces. It cannot say where the brace goes, how a wrapped `if` condition
> lines up under its opening bracket, or how a parameter list breaks when it runs past the margin,
> because it does not parse the language. `.clang-format` does: it is a formatter that reads the code
> properly and rewrites the whitespace, it ships with the C/C++ extension in VS Code and as a
> standalone binary, and the style lives in one file at the repository root so every machine agrees
> without anybody remembering anything. **Have it before the first real function rather than after.**
> Adopting a formatter once a few thousand lines exist turns one small commit into a rewrite of every
> file it touches, and a genuine change hidden inside a whole-file reflow is unreviewable — the same
> problem as line endings, arriving the same way. Stage 1 sharpens it, because CubeMX regenerates
> code in its own style directly on top of yours.

### Conventional Commits, and the two types this project adds

A commit message format, and the reason to have one is that a history is only evidence if it is
legible.

```
<type>(<scope>): <subject>
```

`feat`, `fix`, `docs`, `test`, `refactor`, `build`, `ci`, `chore` are the standard set. Two more are
local to Mimic and worth knowing why:

- **`tune`** — a gain, constant or threshold changed on evidence. `tune(pid): raise Kd to 0.05,
  overshoot 22% -> 9%`. It is not a `feat`, because no behaviour was added, and it is not a `fix`,
  because nothing was broken. It is the most common kind of change in a control project and it
  deserves its own word.
- **`hw`** — wiring, mounting, bill of materials, CAD. `hw(stage0): move the 100nF from the
  breadboard to the motor terminals`. Hardware has no `git diff`, so the commit message is the only
  record that the change happened at all.

**What it costs:** a few seconds per commit, and the discipline of deciding what a change actually
was before you describe it — which is most of the value.

### GitHub Actions — what CI proves

A **CI (continuous integration) service** runs a script on somebody else's computer every time you
push. GitHub's is called Actions; the script is a YAML file in `.github/workflows/`; and a **runner**
is the machine it runs on — here `ubuntu-latest`, a fresh virtual machine that is destroyed
afterwards.

That freshness is the entire point. The workflow in this repository does one thing: clone the
repository from scratch and run `pio run -e uno`. It proves the firmware **compiles from a clean
checkout** — no local file you forgot to commit, no tool installed once and never recorded, no
`platformio.ini` key that only works because of something on your machine.

It sounds like a small claim. It is not: a large fraction of hobby repositories will not build for
anybody but their author, and the difference is invisible until somebody tries.

> **DEFINITION** — **Pinning, and why the version after the `@` matters.** `uses: actions/checkout@v5`
> pins a third-party action to a major version. Pin nothing and a change somebody else makes breaks
> your build on a day you did not touch it; pin exactly and you never get security fixes. A major
> version is the usual compromise. It also has to be *maintained* — GitHub retires the runtime these
> actions execute on every few years, and an action pinned to a retired major starts warning and then
> stops working. Check the versions when a warning appears, rather than when the build fails.

---

## The ROS 2 Stack

Required before Stage 2 bring-up, and worth installing earlier — having ROS 2 working removes an
obstacle from a stage that has plenty already, and the official tutorials at `docs.ros.org` are a good
use of an evening long before you need them. Nodes, topics, services, actions, parameters and launch
files are pure concept work: you can do all of it in simulation, on this machine, with nothing plugged
in.

| | |
|---|---|
| **Distribution** | Ubuntu 24.04 LTS, native, on the laptop — already installed |
| **ROS 2** | Jazzy Jalisco — LTS, targets 24.04, supported to May 2029. **This is a deliberate choice over the newer LTS — see below.** |
| **Simulator** | Gazebo Harmonic — **not** Gazebo Classic |
| **Deadline** | Before Stage 2 bring-up. `can-utils` earlier, if you buy a CANable |
| **Cost** | Nothing but the evening |

> **WATCH OUT** — **Jazzy is no longer the newest LTS, and you are choosing it on purpose.** ROS 2
> **Lyrical Luth** was released in May 2026, pairs with **Ubuntu 26.04**, and is supported to May 2031.
> Jazzy plus Ubuntu 24.04 is still the recommendation for Mimic, for three reasons: the third-party
> package ecosystem you actually depend on — MoveIt 2, `ros2_control`, `whisper_ros` — is most mature
> and best documented on Jazzy; almost every tutorial and book you will find targets it; and it is
> supported to 2029, which outlasts this project comfortably. **But make it a decision, not a
> default.** Write an ADR in `docs/decisions/` saying you knew a newer LTS existed and chose
> the older one, and why. Re-check when you actually install, because the balance shifts as packages
> migrate — and "I evaluated the current release and deliberately stayed one back" is a far better
> answer than being one behind without noticing.

### The install order

1. **ROS 2 Jazzy Jalisco**, desktop variant, following the current instructions at `docs.ros.org`.
   **Do not follow a third-party blog** — the official apt setup changes periodically, and stale
   instructions are the most common reason an install fails confusingly.
2. **Gazebo Harmonic**, the simulator paired with Jazzy.
3. Build tooling: `python3-colcon-common-extensions`, `python3-rosdep`, `python3-vcstool`.
4. **CAN tooling**: `can-utils`, which gives you `candump` and `cansend`. It is a thin userspace layer
   over a kernel subsystem, which is the practical reason this host is a machine rather than an
   environment inside one.
5. `sudo usermod -aG dialout $USER`, so you can open serial devices without `sudo`. Log out and back
   in. If you did this already for PlatformIO, it is done.

> **WATCH OUT** — Gazebo Classic is end-of-life and unsupported from Jazzy onward. Any tutorial using it
> is stale and following one will cost you a weekend. The tell is in the names: Classic is `gazebo` and
> `gazebo_ros`; Harmonic is `gz sim` and `ros_gz`. Check before committing an afternoon to any tutorial,
> including ones that look current.

### Prove it now, not in Stage 2

Four checks, worth running the evening you install and then never again:

```bash
# 1. ROS 2 core is alive and two nodes can find each other
ros2 run demo_nodes_cpp talker
#    ... in a second terminal:
ros2 run demo_nodes_py listener

# 2. The visualiser opens and renders
rviz2

# 3. The simulator opens and renders — note 'gz sim', not 'gazebo'
gz sim shapes.sdf

# 4. socketCAN works, using a virtual bus — no hardware needed
sudo modprobe vcan
sudo ip link add dev vcan0 type vcan
sudo ip link set up vcan0
candump vcan0 &
cansend vcan0 001#1122334455667788
```

Check 4 is the one that reaches past the applications and into the kernel. If `candump` prints that
frame, this machine is ready for Stage 1's bus work and Stage 2's bring-up.

> **CHECK YOURSELF** — The host is ready when talker and listener see each other, `rviz2` and `gz sim`
> both open and render smoothly, a virtual CAN frame round-trips through `candump`, and you can open a
> serial device without `sudo`. Note the date in `docs/decisions/` — it is the moment Stage 2 stopped
> being blocked on infrastructure.

---

# PART V — GETTING READY

---

## What to Learn, What to Ignore

Substantially less than instinct suggests. The prerequisite list is short, the genuinely new material
is one topic, and the list of things to deliberately *not* study yet is longer than both.

### Audit, do not study

Be comfortable with: digital and analogue I/O · PWM · the read–map–write loop · non-blocking timing
with `millis()` · serial debugging · I²C · reading a datasheet without panic.

If any are shaky, patch them now — otherwise Stage 0 will feel like fighting on two fronts.
**Non-blocking timing is the one worth being honest about**, because a `delay()` anywhere near a
control loop makes the loop rate a fiction and every step response meaningless.

**The last item on that list is the one nobody was ever taught**, so it gets its own section rather than
a line — and unlike the rest of the audit, it is genuinely new material. Read it before you order
anything.

### The skill nobody teaches: reading a datasheet

"Reading a datasheet without panic" is on the audit list above, and it is the one item there you have
probably never actually been taught. It is not a reading-comprehension problem. It is that nobody
tells you **what the documents are, which one holds which kind of fact, and which numbers are lies.**
Twenty minutes here saves you a fortnight across this project, and it is the difference between an
engineer and someone who copies wiring diagrams.

Every number in this document set that came from a manufacturer, you should be able to go and find for
yourself. Several sessions will ask you to. When one does, the answer is not in the workbook — the
*page reference* is, and that is deliberate.

#### One part, four documents, and why you keep getting lost

The word "datasheet" is used for a family of documents that are not interchangeable. For a simple part
there is one; for a microcontroller there are four or five, and looking in the wrong one is why the
information you need "does not exist."

| Document | What is in it | Example |
|---|---|---|
| **Datasheet** | What the part *is*: pinout, package, absolute maximums, electrical characteristics, timing specs. Every part has one. For a microcontroller it is mostly **electrical** — voltages, currents, temperatures, pin capabilities — and deliberately says almost nothing about how to *program* it. | `TB6612FNG` datasheet, ~30 pages. `STM32F446xC/E` datasheet, ~200 pages |
| **Reference manual** | How to *program* it: every peripheral, every register, every bit. Microcontrollers only. This is where "which bit turns on the encoder mode" lives, and it is the document people mean when they say "the STM32 docs are enormous." | `RM0390` for the STM32F446, ~1,300 pages |
| **User manual** | How to use a *board*, as opposed to a chip: which pin of the chip goes to which header, which solder bridges are fitted, what the on-board debugger does. | `UM1724` for the Nucleo-64 boards |
| **Application note** | How to do one specific thing well, written by the manufacturer. Often the clearest writing they produce. | `AN4013` on STM32 timers; `AN2606` on the bootloader |
| **Errata sheet** | The list of ways the silicon does not match its own datasheet. Short, dry, and occasionally the answer to a bug you have spent two days on. **Read the errata for any part that is behaving impossibly.** | `ES0298` for the STM32F446 |

**The practical rule:** electrical question → datasheet. Register question → reference manual. "Which
pin is that on my board" → user manual. "This is impossible" → errata.

#### Where to get them

**From the manufacturer, every time.** Search `"STM32F446RE" site:st.com` or `"TB6612FNG"
site:toshiba.semicon-storage.com`. Aggregator PDFs are frequently a revision or three out of date, and
a datasheet revision changes numbers — Toshiba's TB6612FNG has revisions from 2007 and 2012 in
circulation with different formatting and different diagrams.

When you do not know who makes it, **Octopart** or **FindChips** will resolve a part number to a
manufacturer and a current datasheet link, and will also tell you whether the part is still in
production. Both are free and neither wants an account.

**Check the revision date and the revision letter on the front page, and write them into
`docs/motor-spec.md` or your ADR next to any number you quote.** "1.2 A, TB6612FNG datasheet Rev 3.0,
2012-11-01, Table 'Absolute Maximum Ratings'" is a citation. "1.2 A" is a rumour.

**And keep the document itself.** The PDF goes in `docs/reference/`, tracked by Git LFS, which is
what that folder is for — anything you fetched from somebody else, including a page you converted to
Markdown so it can be quoted. Two reasons it is worth the thirty seconds rather than a bookmark:
manufacturers move and retire PDFs, so the revision you designed against is the one that has to
survive; and a citation nobody can follow is only marginally better than no citation. Record the
document, revision, date and table name *inside* the file when you save it, exactly as
`docs/reference/README.md` asks. **Nothing you produce yourself ever goes in there** — your algebra
is `docs/derivations/`, your measurements are `docs/tuning/` and `docs/motor-spec.md`, and the two
folders are kept apart precisely so that "where did this number come from" has a one-word answer.

#### The three kinds of number, and why confusing them destroys a design

This is the whole game. Almost every datasheet has three tables, and they mean completely different
things.

| Table | What it means | How to use it |
|---|---|---|
| **Absolute Maximum Ratings** | The point at which the part is **damaged**. Not a place to operate. Exceeding it even briefly may destroy the part, and operating *at* it will not damage it instantly but voids everything else in the document. | A wall you never touch. |
| **Recommended Operating Conditions** | The range within which the rest of the datasheet's promises hold. | **This is your design envelope.** |
| **Electrical Characteristics** | Measured behaviour, given as **Min / Typ / Max**, each with **conditions** attached. | Design to **Min** or **Max** — whichever is the pessimistic one for your case. Never to **Typ**. |

**"Typical" is not a promise.** It is what a part in the middle of the distribution does on a good day
at 25 °C. You may not receive that part. If a pull-up's typical value is 40 kΩ and its range is
30–50 kΩ, your circuit must work at 30 and at 50.

Your TB6612FNG is the worked example, and it is already in this project: **15 V is an absolute maximum,
13.5 V is the top of the recommended range, and 12 V is where you operate.** The safety table later in
this document says "design to 13.5 V" for exactly this reason. Look at all three numbers in the actual
datasheet before Stage 0 S2 and satisfy yourself that you can find all three and say which table each
came from.

#### Every number has conditions attached, and they are the number

A figure in a datasheet is meaningless without its test conditions, and the conditions are always in
the same row, in a column people skip.

- **Temperature.** Ratings are usually at 25 °C ambient. A motor driver's current rating collapses as
  the package heats, and there is normally a derating curve — a graph, further back — showing how much.
- **Supply voltage.** "Output high voltage 2.4 V min" means nothing until you know at what VCC and at
  what output current.
- **Duty cycle and pulse width.** This one has already changed a decision in this project. The
  TB6612FNG's **3.2 A peak** is qualified by a maximum pulse width and a duty cycle. That is why Stage 2
  can say a *bounded* stall is inside the pulse rating and a sustained one is not — the qualification
  is the whole content of the number, and reading "3.2 A" alone would have told you the opposite thing.

**Habit to build now:** when you write a manufacturer number down, write its conditions beside it.
If you cannot find the conditions, you have not finished reading.

#### How to actually read one, in order

Do not read front to back. A 200-page datasheet is a reference, not a book.

1. **Front page.** One paragraph of what the part is, plus the revision date. Confirm you have the
   right part *and the right variant* — suffix letters mean package, temperature grade and flash size,
   and `STM32F446RE` and `STM32F446ZE` are different pin counts.
2. **Block diagram.** Two minutes, and it tells you what is inside and what connects to what.
3. **Pinout and pin description table.** For a microcontroller this includes the **alternate function
   table** — which peripheral each pin can become. This is the table that decides your pin map, and it
   is the reason Stage 1's pin map can say "PA0 is `TIM2_CH1`" with confidence.
4. **Absolute maximums, then recommended operating conditions.** In that order, so you know the wall
   before you know the room.
5. **Only then**, the specific electrical or timing section you came for.

**Use the PDF's search.** Searching a reference manual for `TIM2_CH1` or `NJTRST` gets you there in
seconds. Searching for a *concept* ("encoder") also works and is how you find the section you did not
know existed.

#### Timing diagrams

They look intimidating and they carry three things: which signal changes relative to which, the names
of the intervals between those changes, and a table underneath giving each named interval a min and a
max. Read the picture to learn the *order*, then read the table to learn the *numbers*. Setup time is
how long a signal must be stable *before* a clock edge; hold time is how long *after*. Almost every
timing diagram you meet in this project reduces to those two ideas.

You will meet a real one in Stage 1: the CAN bit is a timing diagram, and S1.6 has you redraw it as
fifteen boxes.

#### When there is no datasheet

Two parts in this project have none, and that is a fact about the parts rather than a failure of your
searching.

- **Your 12GA-N20 motor.** Vendor listings disagree with each other by an order of magnitude. Stage 0
  S1 has you *measure* winding resistance, stall current and counts per revolution, and
  `docs/motor-spec.md` becomes the datasheet — which is why the Guide's resource index lists that file
  as a Stage 0 resource.
- **The SG90 servo.** "SG90" is a form factor made by dozens of factories, and the universally quoted
  1.8 kg·cm has no manufacturer document behind it. Stage 2 S2.10 has you measure it.

The habit is the same in both cases: **screenshot the listing you actually bought from**, record the
claim, measure the reality, and write down the gap. A recorded discrepancy is a better portfolio
artifact than a number that happened to be right.

The screenshot is somebody else's document, so it goes in `docs/reference/` with the vendor, the part
string and the date you took it written beside it — an AliExpress listing is edited and deleted
without notice, and once it is gone your "the vendor claimed 300:1" is unsupported. Your measurement
of the same quantity goes in `docs/motor-spec.md`. **The claim and the measurement live in different
folders on purpose**, and the gap between them is the artifact.

> **CHECK YOURSELF** — Before Stage 0, do this once, on the bench, in about twenty minutes. Find the
> **TB6612FNG datasheet on Toshiba's own site** and answer five questions from it, writing the table
> name and page beside each answer:
>
> 1. What is the absolute maximum `VM`, and what is the top of the *recommended* range? (Two different
>    tables. If you got one number, you have found only one of them.)
> 2. What is the output current rating, and what conditions are attached to the peak figure?
> 3. What does the truth table say `AIN1 = AIN2 = HIGH` does — and what does `STBY = LOW` do?
> 4. What is the minimum `VCC` for the logic side, and is 3.3 V inside it? (You need this in Stage 1,
>    where the STM32 drives it instead of the UNO.)
> 5. What revision of the datasheet are you looking at, and what is its date?
>
> If you can answer all five with citations, you can read a datasheet, and you never need to take a
> number in this document set on trust again. **That is the point — every manufacturer figure quoted
> anywhere in these documents is one you are able to go and check, and several sessions will ask you
> to.**

### The one thing to actually learn: PID

- **Brett Beauregard, "Improving the Beginner's PID"** — the practical problems, in the order you will
  hit them. Read before Stage 0 and again during.
- **The Arduino PID library source.** Short, readable, and the comments explain design decisions
  rather than mechanics.
- **Curio Res** — the encoder-reading and PID series on YouTube. Watch it *after* you have derived the
  quadrature transition table yourself, so you are checking your reasoning rather than copying.

> **DEFINITION** — **Counts per revolution at the output shaft** is the encoder's native pulses per
> revolution, multiplied by the quadrature decoding factor, multiplied by the gear ratio. For your
> motor: 7 PPR per channel × 4 × ~300 ≈ **8,400 counts per output revolution**, or 0.043° per count.
> Get it wrong and every angle you compute is wrong by a constant factor, which looks exactly like a
> badly tuned gain. **Derive it, then verify empirically** by turning the output shaft ten full
> revolutions and dividing.

### The do-not-study-yet list

> **WATCH OUT** — Reading a ROS 2 tutorial during Stage 0 is a pleasant way to avoid doing Stage 0. It
> feels like progress, it is genuinely interesting, and it produces nothing. Installing Jazzy is setup.
> Working through its tutorials before Stage 0 is finished is procrastination wearing a lab coat.

| Not yet | Because |
|---|---|
| MoveIt 2, tf2, URDF | Stage 2. Meaningless without an arm to describe, and you will have forgotten it by then. |
| Inverse kinematics | Stage 2 — and you are meant to derive the two-link case by hand, which is a different and better exercise than reading about solvers. |
| FreeRTOS | Stage 1. Learn it against a real control task you already have working. |
| CAN framing and arbitration | Stage 1. The physical layer matters more than the software here, and it lands better with a transceiver in your hand. |
| EMG, Kalman filters, quaternions | Stage 4. About five to six months out — see Project Guide Appendix G. |
| KiCad | Optional, between Stages 1 and 2, for the joint carrier board. |
| Buying a 3D printer | Stage 2, and **not before the torque budget in Workbook session S2.4** — that calculation may change your link lengths and your actuation entirely. |

---

## Safety Baseline

Nothing in the *robot* runs above 24 V, so shock risk from the arm itself is negligible. Two things
on your bench are nonetheless mains-powered — the soldering station and the 12 V supply — and Stage 4
puts electrodes on your skin, which is a category of its own. The main risks are mechanical, and two
of them arrive in Stage 0.

| Risk | What to do about it |
|---|---|
| **Pinch injuries** | A geared motor has far more torque than you expect and no sense of what it is closing on. Keep fingers out of joint gaps when powered. This applies to a bare motor with a coupler on it, not only to a finished arm. |
| **Runaway motion** | A sign error does not produce a gentle drift; it produces full-speed motion into a hard stop. Bolt things down — the rigid base is a safety item as much as a measurement one. Fit the emergency stop before Stage 2, not after the first incident. |
| **Stall current vs driver rating** | Your motor stalls at roughly 1.0 A; the TB6612FNG is rated 1.2 A continuous, 3.2 A peak. Its *recommended* supply range tops out around **13.5 V**, and **15 V is the absolute maximum** — a destruction limit, not a design one, so design to 13.5 V. A stalled motor is legal and thermally uncomfortable, and **integral windup against a held shaft is a sustained near-stall condition**. Never leave the rig powered and unattended with integral action enabled. |
| **Eye protection** | Safety glasses are **not** in the 31 July order — the *Order Manifest* lists them under *Deliberately deferred*, so assume you do not own a pair. Stage 0 has you drill plywood, solder, snip component legs and cut heat-shrink, and all four throw something. About C$8, in Tier B of *What's Left to Buy*. Buy them, or write down that you chose not to. |
| **Soldering fumes** | Extractor or an open window. Rosin flux is an irritant and you will solder more than you expect. |
| **Electrode safety** | Stage 4, but worth knowing now: with electrodes on your skin, either isolate the USB connection galvanically **or** run the microcontroller from a battery. Both is better. This is why a USB power bank and a USB isolator are on the parts list. |

> **WATCH OUT** — The rigid base is the cheapest item on the entire parts list and one of the few that
> can cost you a week by its absence. A motor that skitters under load makes step responses unreadable,
> and you will tune gains against a mechanical problem for days.

---

## The Checklist

In order. Nothing in the first block needs a single part to have arrived.

### Tonight

- Create the `mimic` repository on GitHub.
- Commit the directory skeleton, the `.gitignore`, `.gitattributes`, a `LICENSE`, and a
  three-sentence `README.md` saying what Mimic is.
- Run `git lfs install`. Confirm `git push` works without a password prompt.
- Install Git, Git LFS, VS Code and PlatformIO. Add PlatformIO's udev rules, put yourself in
  `dialout`, then log out and back in.
- Create the virtual environment and install `tools/requirements.txt` into it — `pyserial`,
  `matplotlib`, `pandas`.

### This week

- **Find a ~2 mm precision screwdriver, or order one.** Your XL4015, LM2596 and MP1584 each set their
  output with a multi-turn trim pot that needs one, and Stage 0's S2 is the session that uses it.
  **It is in no manifest section, so check rather than assume** — and if you do not have one, it is
  C$5–8 in Tier B and it needs to arrive before S2. Once found, put it in the bin with the buck
  converters.
- Install STM32CubeIDE and let it finish its first-run updates.
- Install PulseView **and `sigrok-firmware-fx2lafw`**. The second is the one that is easy to miss.
- **Pick a CAD package and do one tutorial in it.** FreeCAD or Onshape — the comparison is
  in Part IV. It is not needed until Stage 2, and the reason to meet it now is that "learn CAD" and
  "design a link" are two problems and you do not want them on the same evening.
- **Find the plank, two G-clamps and a drill**, or decide what you are doing instead. See the table in
  Part I → "Money, and what you need on day one".
- Audit the prerequisite list above; patch anything shaky, especially non-blocking timing.
- Read "Improving the Beginner's PID" once, cold.

### When the boxes land

- **Label as you unpack.** Twenty minutes now, or an afternoon in three weeks trying to tell an
  LM2596 from an MP1584 by sight.
- **Bolt the motor to the plank** and clamp the plank to the desk — Stage 0 session S1. Heat-set
  inserts or through-bolts with washers; not wood screws into the plywood face.
- Identify the motor's six wires with the multimeter. **Do not trust the colours.**
- Measure winding resistance; compute stall current; compare it to the TB6612's 1.2 A rating.
- Check the AS5600 magnet is **diametric** — spin it near the sensor and confirm the angle sweeps
  smoothly through 360°. Jumps or sticks means the wrong magnet type.
- Check the JCD stand's bore fits the 907 handle.
- Set the XL4015 to 5.00 V with **nothing** connected to its output.
- Solder a 100 nF ceramic directly across the motor terminals. **At the motor, not on the breadboard.**
- Measure counts-per-output-revolution: mark the shaft, turn it exactly ten revolutions, read the
  counter, divide by ten.

> **GO TO THE WORKBOOK** — That last item is Stage 0 Workbook session S1, and it is where this document
> hands over. From here on, the workbook is what is open on the bench and this document is what you
> flip back to when a word stops making sense.

### Before Stage 1

- Order the **Nucleo-F446RE from DigiKey** — not AliExpress. **C$28.01** as of August 2026. Bundle the
  SN65HVD230 transceivers and the rest of the Stage 1 list to clear the C$100 free-shipping threshold;
  DigiKey Canada ships DDP, so there is no customs exposure.
- Decide whether you are buying a **CANable**. If yes, `can-utils` and the socketCAN half of the host
  setup move up from Stage 2 to Stage 1, because socketCAN is the entire reason to own one. Write the
  decision down either way.

### Before Stage 2 — the hard deadline

- Install ROS 2 Jazzy, Gazebo Harmonic, colcon, and `can-utils`.
- Run all four checks above, including the virtual CAN loopback.
- Add your user to `dialout`.
- Tag `v0.1-stage1-exit` — and only then think about the printer.

> **CHECK YOURSELF** — You are set up when a fresh clone of your repository builds the firmware for
> the stage you are on, when you can flash a board and open its serial port without reaching for
> `sudo`, and when `docs/tuning/` has at least one file in it. The third is the one people skip.

### At the end of every session

Every session, for the next seven months. It takes about five minutes and it is the difference
between a build and a build somebody else can see.

- **Commit the code**, in small commits, including the ones that did not work.
- **Write the session README** — `docs/sessions/<slug>/README.md`. Three to five bullets on what
  actually happened, what the objective did not predict, and what you got wrong first.
- **Check you captured the evidence** — the broken state, before you fixed it, and the shot the
  session's `**Site:**` line asked for.
- **Write the numbers down** where they belong, with their units and their conditions.
- **Write the decision down** — if you chose between real alternatives tonight, it owes an ADR in
  `docs/decisions/` before you close the laptop. Four sentences per section. The test is below.
- **Tick the line** in `.website-capture.md`.

The first and the last take seconds. **The middle four are the ones that cannot be done later, and
they are the ones that get skipped** — which is the whole reason this list is six lines rather than
a paragraph.

#### The tracker, since this is the only place it appears

`.website-capture.md` sits at the repository root and is **gitignored on purpose.** It is a to-do
list about the build rather than a record of it, so it never gets committed; it is the one file in
this project you are allowed to be sloppy in. It carries one line per session, already written, for
all fifty-two of them. Tick a line when that session's evidence exists somewhere you can find it —
one tick, whole session — and send the file to the website repository when a stage is done. If
ticking it takes longer than a minute at the end of an evening you will stop doing it, which is the
only way this file fails.

The slug on each line is the same string as the `docs/sessions/<slug>/` folder name and the website's
step key. **Those three must agree exactly**; renaming one and not the other two is how a session's
evidence becomes unfindable.

#### How to tell when you owe an ADR

The other four items on that list are unambiguous — you either measured something or you did not.
This one needs a test, because "a decision" is the kind of word that expands until it means nothing
or contracts until it means only the big ones.

**You owe an ADR when you picked one option and a competent person could have picked another.** That
is the whole test. Not "was it hard", not "was it important" — *was there a real alternative you
rejected.* If you can finish the sentence "I did X rather than Y, because…", the file is already
mostly written.

Three signals that you are standing in front of one, and every session in the workbooks that
generates one is flagged in its own text:

- **The workbook tells you to.** Some sessions say so outright — coast or brake at zero command,
  hold or coast or brake on silence, the derivative filter's α. When the text says *decide
  deliberately and write it down*, that is this.
- **You wrote a number into the code that you could defend two ways.** A timeout, a gain limit, a
  threshold, a window length. If the comment beside it would have to say "because it felt right",
  it is a decision wearing a constant's clothes.
- **You found yourself arguing with the guide.** These documents make choices on your behalf and
  tell you to disagree on purpose rather than by drift. Agreeing is also a decision; write down what
  you weighed.

And the counter-test, because a folder of forty ADRs is as useless as an empty one: **if there was
only one way to do it, it is not a decision.** Using `#pragma once` is not an ADR. Using D2 and D3
for the encoder is not an ADR — the UNO has exactly two interrupt pins. Write those in a code
comment, where they belong.

> **WATCH OUT** — **The one that gets skipped is the decision you made without noticing you made
> it.** Nobody forgets to write up an agonised choice. What evaporates is the one you settled in
> four seconds at 11 p.m. — you set the stall window to 200 ms, moved on, and eight months later
> cannot say whether that was derived or typed. The catch for it is the last question of the
> session, not a separate habit: *did I put a number in the code tonight that I cannot derive?*

### The things to keep saying to yourself

Not a procedure. These are the sentences to have running in your head while you work, until you stop
needing them.

- **Photograph the broken thing before you fix it.** Once you understand the bug you cannot produce
  it convincingly again.
- **Film it the first time it works.** There is no second first time.
- **Write the number down now, not later.** You will not remember the conditions, and a number
  without its conditions is not a measurement.
- **Photograph the page of algebra, not a tidy retyping of it.** The crossings-out are the evidence.
- **Say why you rejected the other option while you still remember what it was.**

Five lines. Read them again in a month.

---

## None of this is the project

An evening on the repository and the toolchain, and one more evening on Ubuntu whenever it suits.

Stage 0 needs one motor, one driver, one encoder, a plank, and the patience to plot a step response
and ask why it looks like that. Everything in this document exists so that when the plot looks wrong,
**the plot is the only thing that could be wrong.**

---

## Figure index

Both figures in this document are plain ASCII/box-drawing art inside a fenced code block, tagged
`FIGURE <id> — <title>` on the first line, so they stay diffable in Git and render in any Markdown
viewer. A PDF export needs a monospace font with full box-drawing coverage — DejaVu Sans Mono or
similar; the core PDF monospace fonts do not carry the characters these two figures use, which are
`↓ → ·`, and will drop or substitute them.

| Figure | Title | Where |
|---|---|---|
| **0.1** | The two layers, and the seam between them | The Architecture, Plainly |
| **0.2** | One tick of the control loop, in order | Inside One Joint |
