# Mimic — Project Guide

**Volume II · The map, the arc, and the reasoning**

Five stages from a single motor on a plank of plywood to a multi-joint arm running ROS 2,
commanded by voice, by camera, and by the muscles in your own forearm.

---


## Contents

- How to Use This Guide

**PART I — THE PROJECT**

- The Project
- Chapter 1 · What Mimic Is
- Chapter 2 · The Architecture
- Chapter 3 · Why This Project and Not Another
- Chapter 4 · Before You Start

**PART II — THE FIVE STAGES**

- The Five Stages
- Interlude A · What Signals Look Like
- Interlude B · The Shape of Time
- Stage 0 · The Single Joint
- Interlude C · Where the Numbers Come From
- Interlude D · Peeling Back Arduino
- Interlude E · From Code to Silicon
- Stage 1 · The Smart Joint
- Interlude F · Frames of Reference
- Stage 2 · The Arm and ROS 2
- Stage 3 · Eyes and Voice
- Stage 4 · The Biomech Payload
- Stage 5 · Optional · Impedance and Rehab Mode

**PART III — REFERENCE**

- Reference
- Appendix A · Skills Traceability
- Appendix B · Budget by Stage
- Appendix C · Resource Index
- Appendix D · Glossary
- Appendix E · What Comes After Mimic
- Appendix F · The Debugging Ladder
- Appendix G · Timeline at 2–3 Hours a Day
- Appendix H · Milestones to Workbook Sessions
- Figure index
- Now go bolt a motor to a plank.

---

## How to Use This Guide

This is not a build log to follow line by line. It is a map with checkpoints. The arm you end up with will differ in its details from the one described here — different link lengths, a different gripper, a different set of compromises — and that is fine. What matters is that each stage ends with a specific, testable capability you did not have before.

Your earlier Arduino work taught you components. This guide teaches you *systems*: how a control loop, a communication bus, a planning layer, and a human all fit together in one machine. That shift — from "make the LED blink" to "make the joint hold position while something else tells it where to go" — is the whole of the transition you are making.

### The three documents, and how they fit

This guide is one of three layers, and each answers a question the others cannot.

| Document | Answers | When you read it |
|---|---|---|
| **Before You Build** Appendix Zero | *What am I looking at?* | Once at the start, then as a dictionary when a word stops making sense. |
| **This guide** Volume II | *Why this project, and what is each stage for?* | Once through, then whenever motivation dips or a decision needs its reasoning back. |
| **The Stage Workbooks** Volumes III–VI | *What do I do tonight?* | Open on the bench, every session. Sessions, derivations, code skeletons, tests. |

The split matters. This guide tells you that unit errors are the most common bug category in the whole project and why; the workbook makes you derive your own conversion chain and checks your arithmetic. Neither works alone, and folding them together would produce something twice as long that you would stop reading.

> **GO TO THE WORKBOOK** — Wherever you see this box, stop reading and open the workbook for that stage. It means the argument is finished and the work begins.

> **PORTFOLIO MOMENT** — And wherever you see *this* box, stop and produce something — a photographed derivation, a plotted result, a written decision. Mimic exists to be shown to someone. An artifact made the day you understood something is evidence; a write-up assembled at the end is a claim, and the difference is visible.

#### The shape of every stage

Each stage chapter follows the same structure, so you always know where to look:

- **At a glance** — duration, cost, prerequisites, and the one sentence describing what you will own at the end.
- **Why this stage exists** — the argument for spending weeks on it. Read this when motivation dips.
- **What you are building** — the physical and software artifact.
- **Concepts first** — what to understand before touching hardware.
- **The build, in milestones** — numbered checkpoints, each independently testable.
- **What will go wrong** — the specific failure modes, so you recognise them instead of concluding you are bad at this.
- **Exit criteria** — the gate. Do not advance until you can do these things.
- **Skills retired** — which items on your robotics list this stage actually checks off.

#### The callout boxes

> **DEFINITION** — A term you have not met before, defined plainly before it gets used.

> **WHERE THIS POINTS** — The connection to prosthetics, rehabilitation, or human–machine interfaces. This is why you are building an arm and not a rover.

> **WATCH OUT** — A specific, common, expensive mistake. These are worth reading twice.

> **CHECK YOURSELF** — The exit gate. If you cannot do these things, the next stage will not work and you will not know why.

> **LOOK THIS UP** — A repository, course, or document worth an hour of your time at this point and not before.

#### What a portfolio moment actually costs you

Five minutes, usually. A photograph of the page you just did the algebra on. A plot saved with a date in the filename. Four sentences in `docs/decisions/` saying what you chose and what you rejected. None of it is writing; all of it is capture.

The reason to do it on the day is that the alternative does not work. Eight months from now you will not remember why you chose to hold position rather than coast when the host goes silent, and a reconstructed answer sounds exactly like a reconstructed answer. The specific claim a hiring manager cannot verify from a finished repository — and can verify instantly from a commit history — is that you understood the problem while you were solving it.

#### Three rules that apply throughout

**Git from the first commit.** One repository, branches per stage, tagged releases at each exit gate. You already do this professionally; the temptation with hardware is to treat firmware as disposable scratch work. Resist it. Your Stage 0 PID tuning history is the artifact a hiring manager will actually read.

**Photograph every wiring change.** Not for the README, though it helps there — for yourself, three weeks later, when a joint stops working and you need to know what changed. Hardware has no `git diff`.

**Write down the number.** When you tune a gain, log the value and what it did. When you measure a current draw, write it down. Control work is empirical, and an undocumented experiment is an experiment you will repeat.

> **WATCH OUT** — The most common way this project fails is not technical. It is starting Stage 2 before Stage 0 genuinely works, because printed parts are more exciting than a motor bolted to plywood. A wobbly PID loop that you papered over will resurface as an arm that oscillates, and by then you will have four joints, a bus, and a ROS 2 stack in the way of diagnosing it. The gates are the whole point.


---

# PART I — THE PROJECT



What you are building, how it is structured, why it is structured that way, and what you need in place before Stage 0 begins.

## Chapter 1 · What Mimic Is

A desktop robotic arm with a gripper, where every joint is its own microcontroller node on a CAN bus, a Linux machine runs ROS 2 as the host, and the arm can be commanded three ways — by voice, by vision, and by your own muscles.

The name comes from the through-line. It mirrors your arm from an inertial sensor, it reads your muscles through surface electromyography, and it obeys your voice. Three different channels into the same machine, each teaching a different discipline.

It is deliberately *not* a mobile robot. Almost every beginner robotics project is a thing with wheels that drives around a room, and the entire software stack that has grown up around that — navigation, mapping, localisation, path planning — is a large body of knowledge that points nowhere near prosthetics or rehabilitation. An arm points directly at them. A powered prosthesis is a set of instrumented joints with a control loop and a human intent signal. So is Mimic.

### What it will do when finished

- Hold a commanded joint angle against gravity and disturbance, with a control loop you wrote.
- Accept coordinated multi-joint motion planned in Cartesian space, so you can say "move the gripper here" rather than "set joint two to 43 degrees."
- Publish its full state — every joint angle, velocity, and current — as ROS 2 topics you can record, replay, and plot.
- Find an object with a camera and generate a grasp for it.
- Understand a spoken instruction, locally, with no cloud service involved, and turn it into motion.
- Mirror your own arm's posture from wearable inertial sensors.
- Open and close its gripper from the electrical activity of your forearm muscles.

### The honest scope

This is a learning platform and a portfolio piece. It is not a medical device, it will not be strong, and its grip force will be modest — every open 3D-printed hand and arm in the literature shares that limitation. You are building it to learn the architecture, the control theory, the firmware discipline, and the biosignal processing that real assistive devices are made of. That is a large and worthwhile thing to learn, and it is what the next employer in this field will actually test you on.

> **WHERE THIS POINTS** — Every commercially available powered prosthetic arm is, structurally, this: distributed joint controllers on a bus, a higher-level intent layer, and a biosignal front end. The differences are materials science, regulatory verification, battery engineering, and a decade of clinical iteration — not architecture. Build the architecture and the rest becomes learnable rather than mysterious.

### Time and money, honestly

Roughly a year at a steady hobby pace, with the five stages running about six, eight, twelve, eight, and ten weeks respectively. That is not a promise; it is a planning figure. Stage 2 is the one that most often doubles, because it is the first time mechanical design, firmware, and a large software framework all have to be correct simultaneously.

On the budget path outlined in Part III, the whole project lands somewhere around CA$1,400, of which the 3D printer is the single largest item. The computer that runs ROS 2 — the "host" — is not a purchase at all if you already own a desktop, which is the assumption throughout this guide. Stages 0 and 1 together, enough to be building today, came to about CA$594 — CA$534 spent on tooling and Stage 0, plus roughly CA$60 for the Stage 1 board and transceivers.

## Chapter 2 · The Architecture

One idea explains why this project is shaped the way it is, and it is the single most useful thing in this guide: every serious robot is two computers, and the interesting engineering lives in the seam between them.

### The two-layer model

There is a **real-time layer** — a microcontroller running a deterministic loop at a fixed rate, reading sensors, closing control loops, driving motors, never permitted to miss a deadline. And there is a **high-level layer** — a Linux machine running planning, perception, logging, speech, and everything that can afford to be a few milliseconds late. Between them sits a link.

```
FIGURE II.1 — The two layers, the seam, and the rates each side owes the other

  ┌──────────────────────────────────────────────────────────────┐
  │  HIGH-LEVEL LAYER — Linux, ROS 2, your desktop               │
  │  Planning · perception · speech · logging · MoveIt 2         │
  │  SOFT real-time: 20 ms late is degraded, not broken          │
  │  Hands down a target every 10 ms (100 Hz)                    │
  └───────────────────────────────┬──────────────────────────────┘
                                  │
                    ══════════════╪══════════════   ← THE SEAM
                                  │                   USB serial → gateway
                                  │                   → CAN at 500 kbit/s
                                  ▼
  ┌──────────────────────────────────────────────────────────────┐
  │  REAL-TIME LAYER — one microcontroller per joint             │
  │  Sense → think → act, and nothing else                       │
  │  HARD real-time: late IS the failure                         │
  │  Closes its own position loop every 1 ms (1 kHz)             │
  └──────────────────────────────────────────────────────────────┘

  The horizontal line is the concept; everything else is detail.

  Read the two rate lines together, because they are the whole
  argument. The host is TEN TIMES SLOWER than the joint, and that is
  fine — the joint is not waiting for it. A command that arrives late,
  or not at all, leaves the joint holding its last target rather than
  guessing. That is why a soft-real-time machine is allowed to command
  a hard-real-time one at all, and it is the property Stage 1 S1.8
  makes you build and Stage 2 S2.11 makes you rely on.
```

This is not an academic distinction. It is why your Arduino work does not get thrown away when you "graduate" to ROS 2 — the Arduino work *is* the bottom layer, and the bottom layer never goes away. A drone is this exact shape: flight control firmware on an STM32 closing an attitude loop at thousands of hertz, with an optional companion computer doing the intelligent parts. A powered prosthesis is this shape. A surgical robot is this shape.

> **DEFINITION** — **Hard real-time** means a missed deadline is a system failure, not a slowdown. Your joint control loop is hard real-time: if it runs late, the motor keeps doing whatever it was last told, and "whatever it was last told" during a fast movement is how joints slam into their limits. **Soft real-time** means late is degraded but tolerable — a path planner taking an extra 20 ms is fine.

### Why every joint gets its own microcontroller

You could run all four joints from one board. Many hobby arms do. Here is why Mimic does not.

**It is how the field actually works.** Dynamixel smart servos, ODrive controllers, automotive actuators, and the joint controllers inside real prostheses and exoskeletons are all independent nodes on a bus. Learning the distributed pattern once means the industrial version is familiar rather than foreign.

**It forces you to design a protocol.** When one board runs everything, "communication" is a function call. When four boards must agree on state, you have to decide message formats, update rates, timeouts, error handling, and what happens when a node goes silent. That is a genuinely different and more valuable skill, and it is invisible in single-board designs.

**It puts CAN on your résumé.** Controller Area Network appears constantly in embedded, automotive, robotics, and medical device job postings, and almost never in hobbyist portfolios. It is one of the highest-signal things you can demonstrate.

**It scales without redesign.** Write the joint firmware once, flash it four times with different node IDs. Adding a fifth joint is a wiring change and a constant, not a rewrite.

> **WATCH OUT** — The cost of this decision is real: four microcontrollers is more hardware, more soldering, and more things to go wrong than one. If you find yourself stalled on the bus for weeks, it is legitimate to run Stage 2 with a single controller driving all joints and retrofit the distributed version later. The architecture is the goal, not a purity test.

### The seam: how the two layers actually talk

Two options, and you will use both in sequence.

**A plain serial bridge first.** The host sends target positions over USB serial in a framing you designed; a small ROS 2 node on the Linux side parses the replies and republishes them as proper topics. You control every byte, you can debug it with a terminal, and nothing is hidden. Start here.

**micro-ROS second.** The microcontroller becomes a genuine ROS 2 node — it publishes and subscribes directly, with real message types, discovered by the ROS 2 graph like any other node. It rides on FreeRTOS and needs a reasonably capable chip. Migrating to it is a Stage 2 stretch goal, and doing it after the serial bridge means you will understand exactly what it is doing for you.

> **WATCH OUT** — micro-ROS is not developed to any safety or medical standard. It is entirely appropriate for learning and prototyping and entirely inappropriate for anything that touches a patient. Keep that distinction crisp in your head from the beginning; it is the kind of judgment the medical device world screens for.

## Chapter 3 · Why This Project and Not Another

Several well-documented open projects could serve as a first larger build. It is worth knowing why Mimic beat them, partly so you can change your mind on purpose rather than by drift.

### The alternatives, and their problems

#### A six-axis printed arm — AR4, SO-101, Koch

These are excellent machines with real communities. The AR4 in particular has a genuinely maintained ROS 2 driver with MoveIt 2 integration, and it is a beautiful portfolio object. The problem for *you, now* is that they are built on stepper motors or smart serial servos, both of which hide the control loop inside a driver you did not write. You would learn to integrate a robot arm. You would not learn to build one. They are excellent second projects, and Part III says so explicitly.

#### A printed prosthetic hand — InMoov, Ada, HACKberry

The most medically on-the-nose option, and genuinely inspiring to look at. But they are firmware-light: a set of servos pulling tendons, with no meaningful control theory, no bus, and no real ROS 2 story. As a Stage 4 or post-Mimic add-on driven by your EMG channel, a printed hand is a superb payload. As the spine of your learning, it teaches too little.

#### A rotary inverted pendulum — the Furuta pendulum

The best pure controls rig on the list, and the one alternative worth taking seriously. It teaches swing-up, state-space control, LQR, and system identification more directly than an arm does, at a fraction of the cost. Its weakness is that it points nowhere biomechanical and it neither sees nor speaks. If you discover during Stage 0 that control theory is the part you love, building a Furuta pendulum as a side project is a genuinely good decision, not a distraction.

#### A self-balancing robot or a mobile rover

The default beginner project, and the reason to skip it: everything downstream of it — navigation stacks, mapping, localisation, particle filters, LiDAR — is a large body of knowledge that does not transfer to assistive devices. It is a fine way to learn robotics in general and a poor way to learn *this* robotics.

### What Mimic gives you that none of them do

It is the only shape that forces distributed firmware, a communication bus, hand-derivable kinematics, a real control loop you wrote yourself, a perception layer, a natural language interface, and a biosignal front end — while remaining a single coherent machine rather than seven disconnected tutorials.

The two-link planar geometry matters more than it looks. It is the one arm configuration where you can derive both forward and inverse kinematics on paper, by hand, in an afternoon, and check your answer against the physical hardware. Every larger arm forces you to import someone's solver and trust it. Doing the algebra once, on a machine you can see moving, is how the mathematics stops being symbols.

> **WHERE THIS POINTS** — Rehabilitation robots for upper-limb therapy are frequently planar two-degree-of-freedom machines, for exactly the reasons that make this a good learning geometry: the kinematics are tractable, the workspace is a tabletop, and the human interacts with the endpoint. Stage 5 turns Mimic into one.

## Chapter 4 · Before You Start

### What you should have finished

What follows is a **capability list, not a reading list** — the things you should already be able to do, rather than material to work through now. You should be comfortable with digital and analog I/O, PWM, the read–map–write loop, non-blocking timing with `millis()`, serial debugging, I²C, and reading a datasheet without panic. *Before You Build*, Part V (“Audit, do not study”) is the authoritative version of this list and is the one to work from. If any of those are shaky, Stage 0 will feel like fighting on two fronts.

### What you should have on the bench

The specific bench, as ordered: two **12GA-N20** 12 V 100 RPM gearmotors with hall encoders and brackets, **TB6612FNG** drivers, a **12 V 5 A** supply, an **XL4015 CC/CV** module standing in for a bench supply (the current limit is the feature), an **AstroAI DM130B** multimeter, a **24 MHz 8-channel logic analyzer**, a **Quicko T12-952** soldering station, and a plywood board for a base. Two Arduino UNOs run the loop. You do not need the 3D printer, a Raspberry Pi, the EMG hardware, or a bench power supply to start.

> **WATCH OUT** — Do not buy the 3D printer yet. It will sit idle for two months while you work Stage 0 and Stage 1, and the money is better held until you know which arm geometry you are committing to. Everything before Stage 2 is bench electronics and firmware.

### Which microcontroller, and when

**Stage 0 runs on the Arduino UNO, throughout.** This is deliberate. The UNO’s constraints — two external interrupt pins, 490 Hz PWM, and an 8-bit core where reading a `long` can tear mid-read — are precisely what teach interrupt discipline, timer configuration, and atomicity. A faster chip would hide all three.

**Stage 1 runs on an STM32 Nucleo-F446RE**, bought from a real distributor. STM32 with HAL and CubeMX is the dominant toolchain in medical devices and aerospace; the on-board ST-Link means you can halt the processor and inspect memory; and CubeIDE puts the startup assembly, vector table and linker script in folders you can open. Never buy a Nucleo on AliExpress — clones ship counterfeit silicon and non-functional debuggers.

**The two ESP32-S3 boards on your bench have two defined jobs**, and neither is Stage 0. Each has two PCNT units that decode quadrature entirely in hardware plus a native CAN controller, which makes them an excellent budget bus monitor in Stage 1, and excellent joints three and four once your protocol is proven. Running a mixed-vendor bus on a protocol you designed is a better thing to be able to say than owning two identical boards.

### The computer that runs all this

Your existing desktop is the host. Nothing in Mimic requires the computer to be physically on the robot — the arm sits on your desk and connects by USB or Ethernet, and it stays that way through Stage 3 at least. A Raspberry Pi is an optional convenience for untethering later, not a prerequisite, and this guide assumes you do not buy one.

#### Native Ubuntu versus WSL — the honest version

If you already run WSL, you are further ahead than you think for some of this and blocked on other parts of it. The split is worth knowing before you plan around it rather than after.

**WSL handles well:** learning ROS 2 concepts, writing and building packages with colcon, Python nodes, authoring URDF, and all of the dataset and classifier work in Stage 4. If you want to start ROS 2 tutorials tonight, do it in WSL.

**WSL handles with effort:** flashing and serial-monitoring a microcontroller. USB devices can be attached into WSL with `usbipd-win`. It works; it is fiddly, and it adds a step every time you unplug something.

**WSL handles poorly or not at all:** `socketCAN`, which is simply not in the stock WSL2 kernel and needs a custom kernel build — that is a Stage 1 blocker if you use the CANable with standard Linux CAN tooling. Gazebo Harmonic's 3D acceleration through WSLg is inconsistent and slow when it misses. ROS 2's DDS discovery across the WSL network boundary is a well-known source of nodes that cannot see each other, and diagnosing it while also debugging your own robot is exactly the two-fronts problem this guide keeps warning about. And nothing about WSL is close to deterministic timing.

> **WATCH OUT** — The practical plan: keep WSL for software work in Stages 0 and 1 and for learning ROS 2 in simulation. Install **native Ubuntu 24.04** — dual boot, or a spare SSD — before Stage 2 hardware bring-up. Operationally: **flash and serial-monitor from Windows** with PlatformIO, plot from either side, learn ROS 2 in WSL, and clone the repository twice from GitHub rather than sharing a directory across `/mnt/c`. Do not use `usbipd-win` to flash from WSL — it adds a step to every unplug, and you will unplug the board dozens of times per session. Doing both costs nothing but an evening, and it means you are never guessing whether a problem is your robot or your virtualisation layer.

### The software you should install now

- **Ubuntu 24.04 LTS**, natively, on a dedicated SSD or dual-boot. Set this up before Stage 2 even if you do most early work in WSL.
- **ROS 2 Jazzy Jalisco**, an LTS release targeting Ubuntu 24.04 and supported to May 2029. It is **not** the newest LTS — Lyrical Luth arrived in May 2026 — and staying one release back is a deliberate choice you should make rather than inherit. *Before You Build*, Part IV → "Native Ubuntu Side" carries the reasoning and the ADR it asks you to write. Install it early even though you will not use it until Stage 2 — having it working removes an obstacle from a stage that has plenty already.
- **Gazebo Harmonic**, the simulator paired with Jazzy. Note that the older "Gazebo Classic" is end-of-life and unsupported from Jazzy onward; any tutorial that uses it is stale, and following one will cost you a weekend.
- **PlatformIO** or the Arduino IDE for Stage 0, and **STM32CubeIDE** for Stage 1.
- **Git**, and a GitHub account. Set `core.autocrlf = input` so line endings do not churn between Windows and Linux clones.
- **Python 3 with `pyserial`, `matplotlib` and `pandas`**. Stage 0 requires you to capture and plot a step response, and nothing else on this list can do it.
- **PulseView / sigrok** for the logic analyzer — plus **Zadig** on Windows, which installs the WinUSB driver the FX2-based analyzer needs. Without it PulseView cannot see the device and it looks like a faulty purchase.

> **WATCH OUT** — Two spec traps that block a stage each. First, the **AS5600 magnetic encoder is hardwired to I²C address 0x36 and it cannot be changed** — two of them on one bus requires a **TCA9548A multiplexer**, which costs about C$2.50. The failure without one is not an error message: one device answers and the other is simply invisible, which reads as a dead board. Second, the AS5600 has *no useful mount in Stage 0*: the 12GA-N20’s rear shaft is occupied by its own magnetic ring encoder and the output shaft is single-ended, 3 mm, and 9 mm long. The AS5600’s job begins in Stage 2, on the joint axis. Do not spend a weekend trying to fit one to a motor.

### A safety baseline

Nothing in Mimic runs above 24 V, so the electrical risk to you is negligible. The risks that are real:

- **Pinch injuries.** A geared motor with any reduction has far more torque than you expect and no sense of what it is closing on. Keep fingers out of joint gaps when powered.
- **Runaway motion.** A sign error in a control loop does not produce a gentle drift; it produces full-speed motion into a hard stop. Bolt things down, and fit the emergency stop before Stage 2, not after the first incident.
- **Eye protection.** Not in the 31 July order — safety glasses are under *Deliberately deferred* in the *Order Manifest*, which means you do not currently own a pair. This project has you drill plywood, solder, snip component legs and cut heat-shrink, and every one of those throws something. They are about C$8 and they are in Tier B of *What's Left to Buy*. Buy them or decide, in writing, that you are not going to.
- **Electrode safety in Stage 4.** When electrodes are on your skin, either isolate the USB connection galvanically or run the microcontroller from a battery. Both is better.
- **Stall current against driver rating.** Your motor stalls at roughly 1.0 A and the TB6612FNG is rated 1.2 A continuous, 3.2 A peak. Its *recommended* supply range tops out around 13.5 V; 15 V is the absolute maximum, which is a destruction limit rather than a design one — so treat 13.5 V as the number you design to. A stalled motor is legal and thermally uncomfortable, and integral windup against a held shaft is a sustained near-stall condition. Never leave the rig powered and unattended with integral action enabled.
- **Soldering fumes.** Extractor or an open window. Rosin flux is an irritant, and you will solder more than you expect.


---

# PART II — THE FIVE STAGES



From a motor bolted to plywood, to an arm that hears you. Each stage ends at a gate you can test. Do not pass a gate you have not met.

Interludes are set between the stages. They explain how a thing actually works rather than what to do next — read each one when you reach it, not ahead.

## Interlude A · What Signals Look Like

You are about to spend six weeks debugging things you cannot see. The logic analyzer makes them visible, but only if you know what you are looking at. This is the shape of the four or five waveforms that will make up almost everything in this project.

### PWM — how a digital pin makes an analog-ish output

A microcontroller pin is either at supply voltage or at ground. It cannot output half. What it can do is switch fast enough that the *average* is half — which, into an inductive load like a motor, is indistinguishable from half. **FIGURE II.2** draws the two duty cycles you should be able to recognise on an analyzer without measuring them.
```
FIGURE II.2 — PWM: how a digital pin makes an analog-ish output

  A pin is only ever fully on or fully off. PWM switches it fast enough
  that the AVERAGE is anything in between. Duty cycle is the fraction of
  each period spent on.

  25 % duty
      ┌──┐        ┌──┐        ┌──┐        ┌──┐
  ────┘  └────────┘  └────────┘  └────────┘  └────    avg ≈ 0.25 × V
      ├──┤
      on

  75 % duty
      ┌────────┐  ┌────────┐  ┌────────┐  ┌────────┐
  ────┘        └──┘        └──┘        └──┘        └─  avg ≈ 0.75 × V

      ├─── one period ───┤

  Arduino's analogWrite gives you 490 Hz and no say in it.
  Your STM32 timer gives you whatever you configure — and Stage 0 S11
  shows you that the UNO could do the same all along.
```

Two numbers matter and Arduino picks one of them for you. **Duty cycle** is the fraction of each period spent high — that is your command. **Frequency** is how often the period repeats, and `analogWrite()` silently gives you about 490 Hz on most pins. That is inside the audible range, which is why cheap motor drivers whine. On an STM32 you set it yourself, and 20 kHz puts the switching noise above human hearing.

### Quadrature — how two square waves encode direction

One channel alone tells you the shaft moved. Two channels, ninety degrees apart, tell you which way. There is no cleverness here: you are just watching which signal changes first. **FIGURE II.3** is the same waveform pair forward and reversed; the only difference between the two halves is which trace moves first.
```
FIGURE II.3 — Quadrature: how two square waves encode direction

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

  One cycle is 12 columns and the two channels are drawn 3 columns
  apart — a quarter period, which is what "ninety degrees" means. So
  all four AB states are the same width, and if yours are not, the
  offset on the wire is not 90°.

  Four distinct AB states per cycle: 00 → 01 → 11 → 10 → 00. Decode all
  four transitions and you get 4× the resolution for free.

  Note which channel leads in forward. If forward is defined as
  00 → 01 → 11 → 10, then from 00 it is B that rises first. Other
  references draw it the other way because they define forward as
  00 → 10 → 11 → 01; both are self-consistent, and what matters is that
  your figure, your table and your code use the same one. Stage 0 S3
  derives the full sixteen-entry table and has you verify it on the
  bench.
```

> **DEFINITION** — **×1, ×2, and ×4 decoding** refers to how many of the four state transitions per cycle you actually count. Counting only rising edges of A is ×1. Counting every transition of both channels is ×4 and gives you four times the resolution from the same encoder — for free, in software. Your datasheet's "counts per revolution" figure usually assumes one of these, and which one is a common source of an encoder that reads exactly four times too high or too low.

### The four buses, side by side

You will use all of these. The differences that matter in practice are wire count, whether there is a clock, and how many devices can share the line — which is what **FIGURE II.4** puts side by side.
```
FIGURE II.4 — The four buses, side by side

  UART — 2 wires, no clock, point-to-point ONLY (not a bus at all)
      ┌───────┐   TX / RX   ┌────────┐
      │  MCU  │◄───────────►│  HOST  │
      └───────┘             └────────┘

  I²C — 2 wires + clock, many devices, each with an ADDRESS
      SDA / SCL
      ═══╤═══════════╤═══════════╤═══
       ┌─┴──┐     ┌──┴─┐     ┌───┴┐
       │0x36│     │0x68│     │0x27│      addresses are fixed by the
       └────┘     └────┘     └────┘      chip — see the AS5600 trap

  SPI — 3 shared wires + 1 chip-select PER DEVICE. Fastest.
      SCK / MOSI / MISO
      ═══╤═══════════╤═══
       ┌─┴──┐     ┌──┴─┐
       │ CS0│     │ CS1│
       └────┘     └────┘

  CAN — 2 wires, differential, MESSAGES not addresses
      120Ω ╤═══════╤═══════╤═══════╤ 120Ω
           │       │       │       │
         ┌─┴─┐   ┌─┴─┐   ┌─┴─┐   ┌─┴─┐
         │J1 │   │J2 │   │J3 │   │…  │
         └───┘   └───┘   └───┘   └───┘

  The termination resistors on CAN are not optional decoration. They are
  the only thing stopping signal reflections, and they go at the TWO
  PHYSICAL ENDS of the bus — not on every node.

  Power off, measure across the bus: you should read about 60 Ω.
```

> **CHECK YOURSELF** — Before Stage 0, you should be able to: put a probe on a PWM pin and read off the duty cycle; look at a two-channel capture and say which direction the shaft turned; and explain why I²C needs addresses but SPI does not.

> **GO TO THE WORKBOOK** — Everything on this page becomes an instrument capture in **Stage 0 Workbook S3** (quadrature A and B, forward and reverse, on the analyzer) and **S5** (the loop-rate pin). Read the interlude, then go and photograph the real thing — the two side by side are the artifact.

## Interlude B · The Shape of Time

In application programming, "fast enough" is a performance concern. In control, timing is part of the mathematics. A loop that runs at an inconsistent rate does not compute a slightly worse answer — it computes the wrong answer, because the integral and derivative terms are both defined in terms of elapsed time.

### What a fixed-rate loop actually looks like in time

**FIGURE II.5** contrasts the loop you intend with the loop you get. The difference between them has a name, and the name is the point of this interlude.
```
FIGURE II.5 — What a fixed-rate loop looks like in time

  IDEAL — every period identical
    ┌──┐        ┌──┐        ┌──┐        ┌──┐        ┌──┐
  ──┘  └────────┘  └────────┘  └────────┘  └────────┘  └──── idle → sleep
    ├─── 10,000 µs ──┤   exactly, every time

  REAL — with encoder interrupts and one slow telemetry write
              ▌           ▌                 ▌
    ┌──┐      ▌ ┌──┐      ▌ ┌──┐┌───────┐  ▌┌──┐        ┌──┐
  ──┘  └────────┘  └────────┘  └┘telemet└───┘  └────────┘  └──
                                              ▲
    ▌ = encoder ISR (fires whenever the shaft moves — you do not
        control when)                         │
                     ← this loop started late. That is JITTER.

  The offset is drawn exaggerated so you can see it. On a real 10 ms
  loop you are chasing single-digit microseconds, and Stage 0 S5's
  acceptance criterion is jitter well under 100 µs.

  Latency = how long after an event you respond.
  Jitter  = how much the START of your loop moves around.
  For control, jitter hurts more: it corrupts dt, and dt is in the maths.
```

The `▌` marks in FIGURE II.5 are your encoder interrupts. They fire whenever the shaft moves, at rates you do not control, and they preempt whatever was running. The `telemet` block is a low-priority task doing something slow — printing, logging, formatting a string. In a superloop, that block pushes your next control iteration late, which is the lateness the figure marks with `▲`. Under an RTOS with priorities, it does not, because the scheduler preempts it.

That difference is the entire argument for an RTOS, and it is why Stage 1 milestone M1.3 exists. Stage 1 Workbook FIGURE S1.5.1 draws both cases side by side and tells you to produce the analyzer capture that proves it rather than to believe the drawing.

> **DEFINITION** — **Jitter** is the variation in when your loop actually runs versus when it should have. **Latency** is how long after an event you respond to it. A loop can have low latency and terrible jitter, and for control purposes the jitter usually hurts more, because it corrupts your dt.

### Why `next += period` and not `next = now + period`

This is a two-character difference with a real consequence.
```
// WRONG — drifts. Each period is (period + however late you were).
if (micros() - next >= 0) { next = micros() + PERIOD; ... }

// RIGHT — absolute schedule. Lateness does not accumulate.
if ((int32_t)(micros() - next) >= 0) { next += PERIOD; ... }
```

The first version resets the schedule from the current time, so every microsecond you were late becomes permanently baked into the period. Over ten thousand iterations that is a loop running measurably slower than you believe. The second version keeps an absolute timetable: if one iteration is late, the next one is simply less late.

Look carefully at the first line and you will find *two* bugs, not one. `micros()` returns an unsigned value, so `micros() - next` is also unsigned, and an unsigned quantity is **always** `>= 0` — that condition is true on every single pass, and the guard does nothing at all. The drift is the bug you were looking for; the always-true comparison is the one that was hiding behind it. This is what unsigned arithmetic does when you are not paying attention to it, and it is why the cast below is not decoration.

> **WATCH OUT** — The cast to `int32_t` is not decoration. `micros()` returns an unsigned value that rolls over roughly every 71 minutes. Comparing unsigned values across a rollover gives you the wrong answer and your loop stops for 71 minutes. Subtracting first and casting to signed makes the comparison rollover-safe. This idiom appears in every serious embedded codebase and is worth memorising.

### Choosing a rate

Faster is not automatically better. A control loop should run roughly ten to twenty times faster than the fastest thing it needs to respond to. For a geared DC motor driving a link, a few hundred hertz to about a kilohertz is the sensible range. Below that you feel sluggish; far above it, you are mostly amplifying encoder quantisation noise into your derivative term.

Pick a rate, write it down as a named constant, and — this is the part people skip — *verify it*. Toggle a spare pin at the top of the loop and measure the period on your logic analyzer. Loops that quietly run at half their intended rate are extremely common and produce tuning behaviour that makes no sense until you measure.

> **WHERE THIS POINTS** — Every safety argument in medical device firmware eventually reduces to a timing argument: the worst-case time from a sensed event to an actuator response. Learning to think in terms of guaranteed periods rather than average performance is the habit that transfers directly, and it is a habit most application programmers never develop.

> **GO TO THE WORKBOOK** — **Stage 0 Workbook S5** is this interlude, executed: the fixed-rate loop, the `next += period` idiom, the rollover-safe comparison, and an analyzer capture that proves the rate rather than asserting it. **S4** derives why that rate is 100 Hz and not 500.

## Stage 0 · The Single Joint

| | |
|---|---|
| **Duration** | About six weeks at a steady pace |
| **Cost** | **CA$534 actual** (tooling + all of Stage 0, ordered 31 Jul 2026) — see Appendix B for how that compares to the estimate. |
| **Needs first** | The capability audit in *Before You Build*, Part V |
| **Printer?** | No |
| **You will own** | A motor that holds a commanded angle against your hand pushing on it, with a control loop you wrote and tuned yourself |

> **GO TO THE WORKBOOK** — **Stage 0 Workbook, Volume III** — thirteen sessions, S0 to S12, built against the exact parts on your bench. It carries the pin map, the measured motor constants, the serial-bandwidth budget, the code skeletons, and the tests. Read this chapter for the argument; work from the workbook.

### Why this stage exists

Everything else in Mimic rests on one skill: closing a feedback loop on real hardware, in real time, and understanding why it behaves the way it does. Not a servo, which hides the loop inside a sealed case. Not a simulation, which lies to you about friction, backlash, and encoder noise. A physical motor that you command and that fights back.

This is also the stage that separates people who can integrate robots from people who can build them. Reading a PID tutorial takes twenty minutes. Watching your own loop oscillate, understanding *why* from the shape of the oscillation, and fixing it, takes weeks — and it is the difference.

### What you are building

One geared DC motor with a quadrature encoder, bolted rigidly to a plank, driven by an H-bridge, commanded by a microcontroller running a fixed-rate position control loop. A potentiometer or serial command sets the target angle. The motor goes there and stays there.

### Concepts first

> **DEFINITION** — A **quadrature encoder** produces two square waves, A and B, ninety degrees out of phase. Counting edges gives you position; which signal leads tells you direction. It is *incremental* — it knows how far you have moved, not where you are — so every power-up needs a homing routine or an absolute reference.

> **DEFINITION** — **PID** is three corrections summed. **P**roportional pushes in proportion to how far off you are — fast, but leaves a steady offset. **I**ntegral accumulates that leftover offset and eliminates it — but winds up badly if the motor saturates. **D**erivative pushes against the rate of change, damping oscillation — but amplifies encoder noise. Nearly all of tuning is trading these three failure modes against each other.

#### The concept that matters most: fixed-rate execution

Your handbook taught you to avoid `delay()`. This is where that lesson gets its payoff. A control loop must run at a *known, constant* rate, because the integral and derivative terms are both defined in terms of elapsed time. If your loop runs at 100 Hz sometimes and 60 Hz other times, your gains mean different things at different moments, and no amount of tuning will make it stable.
```
// The shape of every control loop you will ever write.
const uint32_t DT_US = 10000;       // 100 Hz on an UNO. Derived, not guessed.
uint32_t next_us = 0;

void loop() {
  if ((int32_t)(micros() - next_us) < 0) return;  // not yet
  next_us += DT_US;                              // schedule next, no drift

  long pos = readEncoder();                    // SENSE
  float u   = pidUpdate(target, pos);          // THINK
  driveMotor(u);                                // ACT
}
```

**Why 100 Hz and not 500.** `analogWrite()` gives you about 490 Hz PWM on an UNO, and a control loop should not update duty faster than roughly one fifth of the PWM frequency — 490 / 5 ≈ 98 Hz. Stage 0 therefore runs at 100 Hz until you reconfigure Timer1 to 31 kHz, at which point 500 Hz becomes available and your tuned gains should carry over unchanged — which is itself a test of whether your `dt` handling is dimensionally correct. On the STM32 in Stage 1, with a 20 kHz timer, 1 kHz is the right answer.

Notice that 100 Hz is fractionally *over* the bound just derived: a 10 ms tick contains 4.9 PWM periods, not 5. That is deliberate. “Five periods per tick” is a rule of thumb about letting motor current settle between duty updates, not a threshold with a cliff behind it, and 100 Hz buys you a `dt` of exactly 0.01 s, which keeps every hand-check of your integral and derivative terms in round numbers. If you would rather sit strictly inside the bound, 90 Hz is fine and nothing else changes. **Either answer is defensible; not having noticed is not.**

Sense, think, act, at a fixed rate. Note that `next_us += DT_US` rather than being reset from the current time — that prevents accumulated drift.

> **PORTFOLIO MOMENT** — Before M0.1, derive your **counts per output revolution** on paper — 7 PPR, ×4 decoding, gear ratio — then *measure* it by turning the output shaft ten revolutions. Photograph both the derivation and the disagreement, if there is one. This is the first artifact of the project and it is the one that proves you check numbers rather than accept them. Into `docs/derivations/`.

### The build, in milestones

#### M0.0 · Mount it rigidly

Bolt the motor to plywood, MDF, or an aluminium plate. Clamp that to your desk. This sounds trivial and is not: a motor that skitters, twists, or flexes under load makes your step responses unreadable, and you will spend days tuning gains against a mechanical problem. Rigid mounting is the first debugging tool.

#### M0.1 · Decode quadrature without losing counts

Attach interrupts to both encoder channels. Decode the quadrature state transitions into a signed count. Verify by hand: **your motor has no datasheet**, so rotate the output shaft exactly *ten* revolutions, read the counter and divide by ten. Ten turns divides your measurement error by ten; one turn divides it by one. That measured figure — not any published one — is what goes in your code. Then spin it fast and confirm you still land on the right number. Losing counts at speed is the classic failure, and it is almost always caused by doing too much work inside the interrupt handler.

#### M0.2 · Drive both directions, and fix the sign once

Wire the TB6612FNG. Confirm open-loop control: a signed command produces proportional speed in the correct direction. Confirm the encoder count increases for positive commands. If it decreases, fix the sign *now*, in one clearly marked place, rather than compensating for it later in three places.

#### M0.3 · Prove the loop rate on an instrument

Toggle a spare pin at the top of the control loop and measure the period on the logic analyzer. Not inferred from behaviour — measured. Loops that quietly run at half their intended rate are extremely common, and every gain you tune against the wrong rate is wrong. Write the *measured* figure, not the intended one, at the top of your tuning log.

#### M0.4 · Build telemetry that fits the serial budget

Instrumentation has a cost and has to be budgeted. A 22-byte CSV row at 100 Hz is 2,200 bytes/s against 11,520 available at 115200 baud — comfortable. The same row at 500 Hz is 95 % of the link, the transmit buffer fills, and `Serial.write` begins blocking inside your control loop. Send integers rather than floats, use 250000 baud (which has zero error on a 16 MHz AVR where 115200 has 2.1 %), and re-measure M0.3 afterwards to confirm the period held.

#### M0.5 · Close a proportional loop and find Ku

P only, integral and derivative at zero. Set a target. Watch it move there, and watch it stop short — that leftover gap is steady-state error, and seeing it is the point of this milestone. Raise the gain until it oscillates. Note the value. You have just found your stability boundary empirically, which is what tuning actually is.

#### M0.6 · Add D, then I, with kick and windup handled

Derivative first to damp the oscillation, which lets you raise P further. Integral last, to remove the residual error — and immediately implement anti-windup, because the first time you hold the shaft still by hand, the integral term will accumulate an enormous correction and release it violently when you let go. Clamping the accumulator is two lines and prevents an alarming experience.

#### M0.7 · Log a step response and name its four metrics

Stream target, actual, and command over serial at your loop rate. Capture a step from 0° to 90°. Plot it. You are looking at rise time, overshoot, settling time, and steady-state error — the four numbers that describe every control system. Save these plots; they are your portfolio evidence and your tuning record.

#### M0.8 · Fit the safety envelope

Clamp the commanded velocity and refuse targets outside a safe range. This is the habit that stops a sign error from becoming a broken part later, and it is what turns a bench experiment into a joint you can trust in an assembly.

#### M0.9 · Refactor to Joint, Encoder, and PIDController

Rung 2 of Interlude D's ladder, and the thing that makes a four-joint arm cheap instead of expensive. With globals, four joints means forty suffixed variables; with objects it is an array. That `Joint` class is literally the artifact you flash to multiple boards in Stage 1, its `state()` method is what your CAN telemetry frame serialises, and in Stage 2 the `ros2_control` hardware interface becomes a thin adapter over objects that already exist.

### What will go wrong

- **Encoder counts drift or jump.** Almost always too much work in the ISR, or missing pull-ups, or long unshielded encoder wires running alongside motor wires. Keep the interrupt handler to a table lookup and an increment. Route encoder wiring away from motor wiring.
- **The motor hums but does not turn.** Insufficient supply current, or a driver in standby. The TB6612 has a standby pin that must be driven high — this catches nearly everyone once.
- **It oscillates no matter what you do.** Check your loop rate is actually what you think it is by toggling a pin and looking at it on the logic analyzer. Loops that quietly run at half the intended rate are extremely common.
- **It works, then violently does not.** Integral windup. See M0.6.
- **The whole thing resets when the motor starts.** Motor inrush is dragging your logic rail down. Separate the motor supply from logic, share only ground, and add bulk capacitance across the motor supply.

> **WATCH OUT** — Never connect motor power and logic power without a common ground, and never assume a USB port can supply motor current. Both mistakes produce symptoms that look like software bugs and will consume days.

> **CHECK YOURSELF** — You may proceed to Stage 1 when you can: (1) state your loop rate and prove it with a scope or analyzer; (2) hold a target angle while pushing the shaft with your hand, and have it return; (3) show a plotted step response and explain its overshoot; (4) explain what each of P, I, and D changed when you altered it; and (5) point at your Git history and see the tuning progression.

> **WHERE THIS POINTS** — This is a prosthetic joint's inner loop, unadorned. A powered elbow does exactly this, at a higher rate, with a better motor and a safety layer on top. Everything you add later — planning, perception, intent detection — ultimately reduces to producing a target angle for a loop that looks like this one.

> **PORTFOLIO MOMENT** — At the Stage 0 gate, stop for one evening and write up what you learned — not a tutorial, a record. What the oscillation looked like at your ultimate gain and why. What integral windup felt like when you held the shaft. Which of your bugs turned out to be electrical rather than software. Publish it with the step-response plots and the disturbance-rejection video, and tag `v0.0-stage0-exit`. This is the first thing anyone will read, and "here is what surprised me" reads far better than "here is what I built".

#### Skills retired

Encoders and motor drivers · interrupts and timers · non-blocking code · PWM and ADC · PID · feedback loops, stability, and tuning · reading datasheets · C++ on embedded hardware.

> **LOOK THIS UP** — Brett Beauregard's "Improving the Beginner's PID" series is the clearest writing on the practical problems — derivative kick, windup, sample time, and on-the-fly gain changes — that separate a textbook PID from one that works. Read it after M0.3, when you have felt the problems yourself.

## Interlude C · Where the Numbers Come From

The most common category of bug in this whole project is not a logic error. It is a unit error — a number that is correct in one system of units and is being used as though it were in another. Robot code is a chain of conversions from counts to physics, and every link is a place to be wrong by a factor of four, or 2π, or 57.3.

### The chain, end to end

**FIGURE II.6** is the whole conversion chain in both directions, with the trap marked at each end. Stage 0 S6 has you redraw it with your own measured numbers on every arrow.
```
FIGURE II.6 — Where the numbers come from: the conversion chain

  SENSING — from the shaft to a number you can reason about

   ┌────────────┐   ┌────────────────┐   ┌──────────────┐   ┌─────────┐
   │ edge count │──►│  shaft revs    │──►│ output revs  │──►│ radians │
   │ raw integer│   │     ÷ CPR      │   │ ÷ gear ratio │   │  × 2π   │
   └────────────┘   └────────────────┘   └──────────────┘   └─────────┘

  DIVIDE BY CPR ONCE. CPR is already the post-decoding number — it is
  PPR × 4 when you decode all four edges — so dividing by CPR and then
  multiplying by the decode factor counts quadrature twice and gives
  you four times too many shaft revolutions. It is ÷ CPR, or
  equivalently ÷ PPR ÷ 4. Never both.

  Worked example — 12GA-N20: 7 PPR/channel, ×4 decoding, ~300:1 gearbox

     28 counts per motor rev  ×  300  =  8,400 counts per output rev
     1 count = 2π / 8,400 = 0.000748 rad = 0.043°

  Both figures are PROVISIONAL. The ratio is a single-vendor claim, and
  Stage 0 S1 has you measure it. Your number goes in the code.

  COMMANDING — from a controller output to volts at the motor

   ┌────────────┐   ┌────────────┐   ┌────────────────┐   ┌──────────┐
   │ PID output │──►│  clamped   │──►│  duty + sign   │──►│  volts   │
   │  unitless  │   │  to ±1.0   │   │ 0..255, DIR pin│   │ × supply │
   └────────────┘   └────────────┘   └────────────────┘   └──────────┘

  THE TRAP — your PID gains have units. Kp is "command per radian of
  error." If you later change the encoder decoding, the gear ratio, or
  your angle units, every gain you tuned is now wrong by that same
  factor. Write the units in the comment beside each gain.
```

> **PORTFOLIO MOMENT** — Draw the conversion chain by hand — counts to radians to command to volts — with *your* numbers at every arrow, and pin it above the bench. Photograph it for `docs/derivations/`. It is the single clearest piece of evidence that you know what your controller is actually computing, and it takes ten minutes.

### The rule that prevents most of this

**Convert once, at the boundary, and work in physical units everywhere else.** Read counts, convert immediately to radians, and let the entire controller think in radians. Convert back to duty cycle at the very last step before the hardware write. Never let a raw count travel more than a few lines from where it was read.

This is exactly the same discipline as parsing untrusted input at the edge of a system and working with validated types internally. You already do this instinctively in application code; the embedded version just has physics attached.
```
// Name your constants with their units. Future-you will thank present-you.
constexpr float COUNTS_PER_OUTPUT_REV = 8400.0f;
constexpr float RAD_PER_COUNT = 6.283185f / COUNTS_PER_OUTPUT_REV;

float angleRad() { return encoderCount() * RAD_PER_COUNT; }
```

> **WATCH OUT** — Degrees are for humans and for printing. Radians are for mathematics. Pick radians internally and convert only at the display boundary. Mixing them is the single most common source of a control loop that is wrong by a factor of 57.3 and behaves as though the gains are wildly miscalibrated.

> **CHECK YOURSELF** — You should be able to state, from memory, how many encoder counts correspond to one degree of output rotation on your specific motor — and show the arithmetic. If you cannot, you do not yet know what your controller is actually doing.

> **GO TO THE WORKBOOK** — **Stage 0 Workbook S1** derives the encoder chain and has you measure it; **S6** builds the conversion into `units.h` and works out what the quantisation costs you in S10. S1 also carries the list of everything that moves if the gear ratio turns out not to be 300:1 — read that before you trust any number on this page.

## Interlude D · Peeling Back Arduino

You have a computer science degree, so you already understand the only idea in this chapter: abstraction layers, and what it costs to remove one. The reason the jump from Arduino to STM32 feels like learning an unrelated subject is that nobody showed you the layers. There are five, they stack in a sensible order, and Arduino hides all of them at once.

### Five things the Arduino IDE is doing without telling you

#### 1 · Your sketch is not C++

The IDE concatenates your `.ino` files, auto-generates function prototypes, prepends `#include <Arduino.h>`, and hands the result to `avr-gcc`. The auto-prototyping is why you can call a function defined further down the file — real C++ will not let you do that. Your sketch is *preprocessed into* C++, which is a different claim.

#### 2 · `main()` exists, and you did not write it

Inside the Arduino core there is a real `main.cpp`. Stripped of detail, it is:
```
int main() {
  init();              // timers, ADC prescaler, millis() interrupt
  setup();             // yours
  for (;;) {
    loop();            // yours, called forever
    if (serialEventRun) serialEventRun();
  }
}
```

Your `loop()` is a callback into somebody else's event loop. Once you have seen this, "moving to bare-metal" stops sounding mystical — you are just going to write that `for(;;)` yourself.

#### 3 · The Arduino core *is* a HAL

This is the realisation that reframes everything. `digitalWrite(13, HIGH)` looks like a primitive. It is not. It looks up which port and bit correspond to pin 13 in a table, checks whether a timer is using that pin and disables it if so, disables interrupts, read-modify-writes a register, and restores interrupt state. Roughly fifty cycles.
```
// Same effect, three layers of abstraction:
digitalWrite(13, HIGH);              // Arduino core   ~50 cycles
PORTB |= (1 << 5);                    // AVR register    ~2 cycles
HAL_GPIO_WritePin(GPIOA, 5, SET);   // STM32 HAL      ~10 cycles
GPIOA->BSRR = (1 << 5);              // STM32 register   1 cycle
```

Arduino's core and ST's HAL are the same category of thing: a portable convenience layer over registers. Arduino hides that it exists; ST puts it in a folder you can open. That is genuinely the main difference, and it is why the transition is less dramatic than it looks.

#### 4 · Startup code, vector table, and linker script

Something has to run before `main()` — zeroing `.bss`, copying initialised data from flash to RAM, setting up the stack pointer. Something has to map "timer 2 overflowed" to "call this function." Something has to decide where in the address space your code and variables live. Arduino hides all three. On STM32 you will see `startup_stm32f446xx.s`, a vector table, and a `.ld` linker script, and the question "how does the chip know to run my code" finally has a visible answer.

#### 5 · Peripheral configuration

`analogWrite()` picks a timer, a prescaler, and a mode for you — and gives you 490 Hz whether you wanted it or not. Configuring it yourself is more work and is why you *can* have 20 kHz PWM, and why you can put a timer into hardware quadrature mode and count encoder edges with zero CPU involvement.

### The ladder

Five rungs. Each one is a real, testable step, and the guide's stages walk you up them in order. **FIGURE II.7** names which stage and which session lands on each rung — worth finding yourself on it before you read on.
```
FIGURE II.7 — The ladder: peeling back Arduino, one rung at a time

  ┌──────────────────────────────────────────────────┬────────────────┐
  │ 5 · Registers, own build system                  │ Stage 1, later │
  │   STM32 + LL/CMSIS · CMake + arm-none-eabi-gcc   │ optional depth │
  │   · gdb over SWD                                 │                │
  ├──────────────────────────────────────────────────┼────────────────┤
  │ 4 · STM32 + HAL / CubeMX                         │ Stage 1        │
  │   You see main(), startup.s, the linker script,  │ M1.1 – M1.2    │
  │   the vector table                               │                │
  ├──────────────────────────────────────────────────┼────────────────┤
  │ 3 · Bypass Arduino where timing matters          │ Stage 0        │
  │   Direct registers, hardware timers, your own    │ S11 (part B)   │
  │   ISRs — on the same UNO                         │                │
  ├──────────────────────────────────────────────────┼────────────────┤
  │ 2 · PlatformIO, .cpp files, real C++ classes     │ Stage 0        │
  │   Still the Arduino framework — but a real build │ M0.9 · S12     │
  │   and real structure                             │                │
  ├──────────────────────────────────────────────────┼────────────────┤
  │ 1 · Arduino IDE, one .ino, one big loop()        │ Today          │
  │   Where most self-taught embedded work starts,   │                │
  │   and there is nothing wrong with it             │                │
  └──────────────────────────────────────────────────┴────────────────┘

  Each rung removes one layer and hands you one more thing to be
  responsible for. Do not skip two at once.
```

> **WATCH OUT** — The Arduino-to-STM32 move is usually described as a jump from rung 1 straight to rung 4, which makes it read as a discontinuity. It is not one. Rungs 2 and 3 happen on hardware you already own, inside Stage 0, and they are where most of the actual learning is — which is why S12's refactor and S11's register-level PWM are in the workbook rather than being skipped past.

> **GO TO THE WORKBOOK** — Rungs 2 and 3 of this ladder are **Stage 0 Workbook sessions S11 and S12** — bypassing `analogWrite()` with a Timer1 prescaler write, then the refactor to `Joint`, `Encoder` and `PIDController`. Rung 4 is the whole of the **Stage 1 Workbook**.

### Rung 2 in detail: the refactor that makes Mimic possible

Right now your handbook code is almost certainly one `loop()` with file-scope variables. The move to real C++ classes is not a style preference — it is the thing that makes a four-joint arm cheap instead of expensive.

With globals, four joints means four copies of every variable with numeric suffixes, and four copies of every function that touches them. With objects, four joints is an array.
```
class Encoder {
  volatile long count_ = 0;
  const float radPerCount_;
public:
  void onEdge();                  // called from the ISR
  float angleRad() const;
};

class PIDController {
  float kp_, ki_, kd_;           // gains are state, not globals
  float integral_ = 0, prevErr_ = 0;
public:
  float update(float target, float actual, float dt);
  void reset();
};

class Joint {                     // ← the unit you flash four times
  Motor motor_;
  Encoder enc_;
  PIDController pid_;
  float target_ = 0, minRad_, maxRad_;
public:
  void setTarget(float rad);
  void tick(float dt);          // sense, think, act
  JointState state() const;
};

Joint joints[4];                    // instead of forty suffixed globals
```

Three consequences worth naming. That `Joint` class is literally the artifact you flash to four boards in Stage 1 milestone M1.7 — the distributed architecture becomes a deployment detail rather than a rewrite. The `state()` method is what your CAN telemetry frame serialises, so the protocol design in Stage 1 falls out of the class interface. And in Stage 2, the `ros2_control` hardware interface becomes a thin adapter over objects that already exist, rather than a from-scratch translation layer.

> **DEFINITION** — **PlatformIO** is a build system and dependency manager for embedded projects that works inside VS Code. It uses real `.cpp` and `.h` files, has a proper `platformio.ini` instead of hidden IDE settings, supports unit testing on the host machine, and can target both AVR and STM32. For someone who uses Git daily and expects a build to be reproducible, it is a large quality-of-life improvement over the Arduino IDE and costs an afternoon to learn.

> **CHECK YOURSELF** — You are ready for Stage 1 when: (1) your Stage 0 code builds under PlatformIO from `.cpp` files; (2) it has at least a `Joint`, an `Encoder`, and a `PIDController` class with no file-scope mutable state; (3) you can point at one line where the abstraction is bypassed for timing reasons and explain why; and (4) you can describe what `digitalWrite` does that a register write does not.

> **WHERE THIS POINTS** — Medical and safety-critical firmware lives at rungs 4 and 5, in C or tightly-constrained C++, with the build system, memory map, and every peripheral configuration under version control and subject to review. Nothing about that world is reachable from rung 1, and all of it is reachable from rung 3.

## Interlude E · From Code to Silicon

One more layer worth un-hiding: what actually happens between pressing Upload and the motor moving. You know this pipeline for hosted software. The embedded version has two extra steps and one very different memory model.

### The pipeline

**FIGURE II.8** is the pipeline, with the two steps that do not exist in hosted software marked underneath it.
```
FIGURE II.8 — From code to silicon

  ┌───────────┐  ┌──────────────┐  ┌────────────┐  ┌──────────────┐
  │.ino / .cpp│─►│  preprocess  │─►│  compile   │─►│    link      │
  │your source│  │#include,     │  │→ .o objects│  │+ core, + libs│
  │           │  │macros        │  │            │  │              │
  └───────────┘  └──────────────┘  └────────────┘  └──────┬───────┘
                                                          ▼
                                                  ┌──────────────┐
                                                  │ .elf / .hex  │
                                                  │    image     │
                                                  └──────────────┘

  THE TWO STEPS THAT DO NOT EXIST IN HOSTED SOFTWARE

   The linker script decides addresses  │  Flashing writes to the chip
   There is no OS to load you anywhere. │  avrdude via bootloader on the
   .text goes to flash, .data and .bss  │  UNO; ST-Link over SWD on the
   to RAM.                              │  Nucleo.

  MEMORY, AND WHY YOU DO NOT CALL malloc HERE

   FLASH — 32 KB / 512 KB    RAM — 2 KB / 128 KB    EEPROM / backup
   code, constants.          globals, stack, heap.  calibration that
   Read-only at run time.    All of it.             must survive
                                                    power-off
```

The UNO has two kilobytes of RAM. Not two megabytes. Every global, your entire call stack, and any heap all share it, and nothing tells you when the stack has grown down into your variables — the symptom is corruption that looks random and moves when you add a print statement.

Which is why embedded practice avoids dynamic allocation in a control loop. Not superstition: a heap that fragments has non-deterministic allocation time, and non-deterministic time in a hard real-time loop is the one thing you cannot have. Fixed-size buffers, statically allocated objects, and no `String` concatenation inside `loop()`.

> **WATCH OUT** — Arduino's `String` class is the classic RAM killer. Every concatenation allocates, and in a loop it fragments your two kilobytes into uselessness over minutes to hours. Use fixed `char` buffers and `snprintf`. This is the single most common cause of an Arduino project that works for ten minutes and then behaves insanely.

### What a debugger actually does

On the UNO you debug by printing, because there is no debug hardware. On the Nucleo there is an on-board ST-Link connected to the chip's SWD port — two wires that let an external device halt the core, read and write registers and memory, set hardware breakpoints, and single-step.

That is a categorical upgrade, not a convenience. Instead of inferring what happened from a trail of print statements, you stop time and look. Getting a breakpoint to actually hit and inspecting a variable is Stage 1 milestone M1.1 for exactly this reason — it is the highest-leverage half-hour in the entire embedded portion of this project.

> **GO TO THE WORKBOOK** — **Stage 1 Workbook S1.0** walks the generated project tree — `startup_stm32f446retx.s`, the linker script, the vector table — and **S1.1** is the breakpoint, with the explicit instruction not to consider the session finished until you have halted the processor and read a variable out of memory.

> **DEFINITION** — **SWD** (Serial Wire Debug) is ARM's two-pin debug interface. **ST-Link** is ST's implementation of a probe that speaks it. On a Nucleo board the probe is built onto the same PCB, which is most of why a Nucleo is worth CA$28 over an CA$8 Black Pill.

## Stage 1 · The Smart Joint

| | |
|---|---|
| **Duration** | About eight weeks |
| **Cost** | ~CA$60, or ~CA$146 with the MCP2515 module, a second Nucleo and a dedicated CAN analyzer |
| **Needs first** | Stage 0 exit criteria met |
| **Printer?** | No |
| **You will own** | A self-contained joint module that accepts position commands and reports state over a CAN bus, running on an RTOS, with firmware you can flash to four identical boards |

> **GO TO THE WORKBOOK** — **Stage 1 Workbook, Volume IV** — ten sessions on the Nucleo-F446RE. It derives the clock tree, the CAN bit timing (prescaler 6, BS1 = 12 tq, BS2 = 2 tq for 500 kbit/s at an 86.7 % sample point — which reach the `CAN_BTR` register as 5, 11 and 1, because a hardware divider field always holds one less than the number you mean) and the bus load, rather than copying any of them from a forum post.

### Why this stage exists

Stage 0 gave you a control loop. It runs on a board you talk to over USB, in a language that hides the hardware. Stage 1 takes that same loop and makes it *professional*: written in C against a vendor HAL, scheduled by a real-time operating system, and exposed to the world through an industrial fieldbus rather than a serial print.

This is the stage with the highest ratio of employability to effort in the entire project. The specific cluster of skills it produces — STM32, HAL and CubeMX, FreeRTOS, CAN, and interrupt-driven peripheral work in C — is what embedded and medical device firmware postings ask for, over and over, far more often than they ask for ROS.

### What you are building

The Stage 0 rig, rebuilt on an STM32 Nucleo, with the control loop running as an RTOS task at a guaranteed rate, and a CAN interface through which a host can set targets and read back position, velocity, current, and fault status. When it is done, it is a component rather than an experiment.

### Concepts first

> **DEFINITION** — A **HAL** (hardware abstraction layer) is the vendor's C library that sits between your code and the chip's registers. STM32CubeMX is the graphical tool that generates HAL initialisation code from a pin and clock configuration. It is verbose and occasionally infuriating, and it is what industry uses.

> **DEFINITION** — **CAN** (Controller Area Network) is a multi-drop, differential, message-oriented bus. Nodes do not have addresses; *messages* have identifiers, and every node decides which identifiers it cares about. Lower identifier numbers win arbitration when two nodes transmit simultaneously, which means priority is built into the addressing scheme. It needs a 120 Ω terminating resistor at each physical end of the bus and nowhere else.

> **DEFINITION** — An **RTOS** gives you tasks with priorities and a scheduler that guarantees a high-priority task preempts a low-priority one. Your control loop becomes a task that runs every 1 ms no matter what else is happening — which is a much stronger guarantee than "I checked `micros()` in a superloop and hoped."

### The build, in milestones

#### M1.1 · Blink an LED from CubeMX-generated code

Trivial, and the point is the toolchain, not the LED. Install STM32CubeIDE, configure a pin, generate, build, flash, debug with a breakpoint. Getting the debugger working — actually stopping at a breakpoint and inspecting a variable — is the single biggest quality-of-life difference between Arduino and professional embedded work. Do not skip past it.

#### M1.2 · Port the control loop to bare STM32, in C

Hardware timer for the encoder — the STM32 has a dedicated encoder mode that counts quadrature in hardware, with zero CPU cost, which is a revelation after doing it with interrupts. Hardware timer for PWM. Your PID from Stage 0, translated to C. Compare the step response against your Arduino plots; they should be very close, and where they differ, understand why.

#### M1.3 · Introduce FreeRTOS

Two tasks: a high-priority control task at 1 kHz, and a low-priority telemetry task. Watch what happens when the telemetry task does something slow — on a superloop it would wreck your timing; under the scheduler it does not. That demonstration is the reason RTOS exists, and seeing it once is worth more than a chapter of theory.

#### M1.4 · Get two nodes talking on CAN

Two boards, two transceivers, twisted pair, 120 Ω at each end. Send a counter from one and print it on the other. Nothing else. Get this working in isolation before any of it touches the motor, because debugging bus problems and control problems simultaneously is miserable.

#### M1.5 · Design and implement your joint protocol

See the next section. This is design work, not typing, and it deserves an afternoon with paper before an afternoon with a keyboard.

#### M1.6 · Fault handling and the silent-host problem

What should a joint do when it stops hearing from the host? Hold position is usually right; continuing the last velocity command is usually catastrophic. Implement a command timeout that fails safe. Add over-current detection through the INA219 and a fault state that refuses to drive until cleared. This is the part that makes it an engineering artifact rather than a demo.

#### M1.7 · Flash it twice

Same firmware, second board, different node ID — read the ID from GPIO jumpers or a stored constant. Two joints on one bus, both controllable, both reporting. You have now built a scalable system, and adding joints three and four is an afternoon rather than a project.

> **PORTFOLIO MOMENT** — `docs/protocol.md` is the highest-signal document you will produce in this whole project. Write it as though handing it to another engineer: message table, bit layouts, rates, units, endianness, and what happens when a sequence number skips. Then write an ADR for each decision that had alternatives. Almost no portfolio can support the conversation "why is that field two bytes and not four" — yours will.

### Designing your CAN protocol

You get eight bytes per standard CAN frame. That constraint is a gift: it forces you to decide what actually matters.

A reasonable starting scheme uses the identifier to encode both message type and node, so filtering is cheap in hardware:
```
// 11-bit standard identifier layout
//   bits 10..4  : message type
//   bits  3..0  : node id (1..15; 0 is reserved for broadcast)
//
//   identifier = (type << 4) | node

enum class MsgType : uint8_t {
  Command   = 0x10,   // host -> joint : target position, mode
  State     = 0x20,   // joint -> host : position, velocity
  Diag      = 0x30,   // joint -> host : current, temp, faults
  Estop     = 0x01,   // broadcast (node 0) -> identifier 0x010
};

struct CommandFrame {       // 8 bytes exactly
  int32_t target_counts;    // 4
  uint16_t vel_limit;       // 2
  uint8_t  mode;            // 1 : idle / position / hold
  uint8_t  seq;             // 1 : detect dropped frames
};
```

Note that `0x01` is the emergency stop's *type* field, not its identifier. Run it through the layout above and the identifier is `(0x01 << 4) | 0` = **0x010**, or 16 — against 0x100 for a command, 0x200 for state and 0x300 for diagnostics. It is still the lowest number on the bus, so it still wins arbitration against every other message even when the bus is saturated. That is not a trick; it is what the priority-encoded identifier scheme is for. Keeping the type and the identifier apart in your head is worth doing now, because the number you filter on in hardware is the identifier.

Decisions worth making deliberately: what rate does each joint publish state at, and does the host poll or do joints publish autonomously? How does a joint signal that it has faulted? What is the sequence number for, and what do you do when it skips? None of these have a single right answer, and having reasoned about them is the skill.

> **WATCH OUT** — If you are working in WSL, `socketCAN` is not present in the stock kernel, so the standard Linux CAN tooling will not run there without building a custom kernel. This is the point in the project where a native Ubuntu install stops being optional. Plan for it before you order the analyzer, not after.

> **WATCH OUT** — Two termination mistakes account for most beginner CAN failures: resistors on every node instead of only the two physical ends, and no termination at all because "it worked on the bench with short wires." Both produce intermittent, distance-dependent, maddening behaviour. Measure across the bus with the power off — you should read about 60 Ω, two 120 Ω resistors in parallel.

> **CHECK YOURSELF** — Proceed to Stage 2 when: (1) two joints run identical firmware on one bus with different IDs; (2) a joint holds position safely when the host goes silent; (3) you can capture and explain a bus trace; (4) your control task is provably running at its intended rate under load; and (5) you can explain why your emergency stop message has the identifier it has.

> **WHERE THIS POINTS** — This is the actual architecture of a modern powered prosthesis or exoskeleton joint. When you later read a paper describing a device with "distributed joint controllers communicating over CAN," you will not be reading about something foreign — you will be reading about a smaller, better-funded version of what is on your desk.

> **PORTFOLIO MOMENT** — Capture the control task’s period on the analyzer twice: once with pre-emption enabled while the telemetry task deliberately stalls for 5 ms, and once without. Publish the two traces side by side. It is the clearest possible answer to "why does an RTOS matter," and most people who list FreeRTOS on a resume have never produced it.

#### Skills retired

C for firmware · STM32 with HAL and CubeMX · RTOS basics (FreeRTOS) · CAN bus · UART and SPI in anger · timers, DMA concepts, interrupt priorities · distributed system design · fault handling and fail-safe design.

## Interlude F · Frames of Reference

Two joints holding angles is not an arm. An arm is a chain of coordinate systems, each defined relative to the one before it, and almost every question you will want to ask — where is the gripper, can it reach that, what did the camera see — is a question about transforming between them.

### The tree

Every link on your robot carries its own coordinate frame, rigidly attached. A transform describes how to get from one frame to its neighbour: a rotation and a translation. Chain them and you can express anything in any frame. **FIGURE II.9** shows the tree and the geometry it describes on one page, because the tree is unreadable until you can see which physical thing each box is.
```
FIGURE II.9 — Frames of reference

  THE TREE                          THE GEOMETRY IT DESCRIBES

  world                                              ● tip
  fixed, never moves                               ╱
    │                                            ╱
    ▼                                      L2  ╱
  base_link ──────► camera_link              ╱ ) θ2
  bolted to the desk   fixed, once         ●╱───────────
    │                  calibrated       elbow
    ▼                       │                ╲
  shoulder                  ▼                  ╲  L1
  rotates by θ1          object                  ╲
    │                    seen, transient           ● base_link
    ▼                                              ) θ1
  elbow                                     ───────────────► +x
  rotates by θ2
    │
    ▼
  gripper_tip
  what you actually aim

  Forward kinematics answers: given θ1 and θ2, where is the tip?
  For a two-link planar arm it is two lines of trigonometry, and
  Stage 2 S2.2 has you derive both of them.
```

### The two directions, and why one is harder

**Forward kinematics** goes from joint angles to endpoint position. It is a straightforward composition of transforms, it always has exactly one answer, and for your two-link planar arm it is:
```
x = L1·cos(θ1) + L2·cos(θ1 + θ2)
y = L1·sin(θ1) + L2·sin(θ1 + θ2)
```

**Inverse kinematics** goes the other way — given a target position, what angles get me there? This is where the difficulty lives, because the answer may not exist, and when it does exist there are usually several. For a two-link arm there are generally two: elbow-up and elbow-down.

> **WATCH OUT** — Your solver must *choose* between elbow-up and elbow-down, and it must choose consistently. If it picks a different branch mid-trajectory, the arm flips configuration in a fast, alarming motion that can collide with itself or your desk. Decide the rule — nearest to current configuration is a good default — and enforce it. This is a design decision, not an edge case.

> **PORTFOLIO MOMENT** — Derive forward *and* inverse kinematics on paper before you open CAD — a full page of algebra for the inverse case, using the law of cosines. Photograph it. Handwritten algebra for a machine you then built is the single most differentiating artifact in this entire project, and it is the reason the two-link planar geometry was chosen.

### Why tf2 exists rather than you doing this by hand forever

Derive the two-link case yourself, once, on paper, and implement it. That is a Stage 2 exit criterion and it is non-negotiable, because it is how the algebra becomes real.

Then let tf2 take over, because the thing it actually solves is not the trigonometry — it is the *bookkeeping*. Frames move over time, sensor readings arrive with timestamps, the camera saw the object 40 milliseconds ago and the arm has moved since, and you want the answer in base coordinates as of a specific instant. Doing that correctly by hand across a whole robot is where errors accumulate invisibly. tf2 maintains the time-stamped tree and answers the query.

> **DEFINITION** — A **homogeneous transform** packs a rotation and a translation into one 4×4 matrix, so that composing transforms is matrix multiplication and inverting one is a matrix inverse. This is why the linear algebra on your skills list is on it: the mathematics of robot geometry is matrix composition, and once you see it that way the notation stops being decorative.

> **WHERE THIS POINTS** — Motion capture, gait analysis, and prosthetic control all reduce to frame problems: where is this segment relative to that one, and how has it moved. An IMU strapped to your upper arm is publishing a rotation of one frame relative to another, and Stage 4 is the same tree with a human limb in it.

> **GO TO THE WORKBOOK** — **Stage 2 Workbook S2.2** and **S2.3** are the derivations, with the round-trip test that catches every sign error; **S2.6** turns the frame tree into a URDF and checks rviz2’s answer against your own forward kinematics. Do the algebra before the XML.

## Stage 2 · The Arm and ROS 2

| | |
|---|---|
| **Duration** | About twelve weeks, and this is the one that stretches |
| **Cost** | ~CA$700 on the budget path, of which the printer is most of it; no host computer purchase assumed |
| **Needs first** | Stage 1 exit criteria met; native Ubuntu installed |
| **Printer?** | Yes — this is where it earns its keep |
| **You will own** | A physical multi-joint arm you can command in Cartesian space, visualise in rviz2, simulate in Gazebo, and record with ros2 bag |

> **GO TO THE WORKBOOK** — **Stage 2 Workbook, Volume V** — fifteen sessions. Note in particular session **S2.4, the torque budget**: it concludes that the N20 motors from Stage 0 cannot build this arm, short by roughly **20× at the loaded shoulder** on an optimistic reading of the motor spec and 100× on the manufacturer’s own rated figure — and that belt reduction, the cheap-looking alternative, does not close the gap either. Do sessions S2.2 through S2.4 — geometry, kinematics, torque — *before* you buy a printer or choose motors. They are three evenings of paper and they determine every mechanical decision that follows.

### Why this stage exists

Two joints that each hold an angle are two independent machines. An arm is a *kinematic chain* — the joints are coupled through geometry, and commanding it usefully means thinking about where the endpoint is, not what each motor is doing. That shift, from joint space to Cartesian space, is the conceptual core of manipulation robotics, and it is where the mathematics on your skills list stops being abstract.

It is also where you meet the framework the field runs on. ROS 2 is not a library you import; it is a set of conventions about how robot software is decomposed, and learning it is mostly learning those conventions.

### What you are building

A two-link planar arm plus a gripper, built from printed links on a rigid base, driven by your Stage 1 smart joints on a shared bus, with a Linux host running ROS 2 that models the arm in URDF, publishes its state, plans motions with MoveIt 2, and shows all of it in rviz2.

### Simulate before you solder

The single best decision available in this stage: build the URDF and get the arm moving in Gazebo Harmonic *before* you cut a single part. Simulation lets you debug your kinematics, your joint limits, your frame conventions, and your ROS 2 plumbing while the only cost of a mistake is a rerun.

When you then connect real hardware, any remaining problem is a hardware problem — which halves your search space. Trying to debug a sign error in a transform while simultaneously wondering whether a joint is miswired is how weeks disappear.

> **DEFINITION** — **URDF** (Unified Robot Description Format) is an XML description of a robot's links, joints, geometry, and inertias. Nearly everything in the ROS 2 manipulation stack reads it: the visualiser, the planner, the simulator, and the transform tree all derive their understanding of your robot from this one file.

> **DEFINITION** — **tf2** maintains the tree of coordinate frame transformations over time, and answers questions like "where is the gripper tip relative to the base, right now?" Once you have it, most geometry questions become a library call rather than trigonometry — which is exactly why you should do the trigonometry by hand first.

### The build, in milestones

#### M2.1 · Derive the kinematics on paper

Forward kinematics, then inverse kinematics by the law of cosines, then the Jacobian and where its determinant goes to zero. This is three evenings of algebra and it determines your joint limits, so it comes before CAD rather than after. Workbook sessions S2.2 and S2.3.

#### M2.2 · Compute the torque budget, and let it change your parts list

Static torque at each joint, with a payload, against your motor's *rated* continuous torque rather than its stall figure. This milestone exists because its answer is "the motors you own cannot build this arm," and finding that out on paper costs an evening while finding it out after printing costs a month and a printer's worth of filament. **Do not buy a printer or choose motors before this milestone is finished.** Workbook session S2.4.

#### M2.3 · Design the arm in CAD

Two links, joint housings that hold your motors and bearings, a rigid base. Design for printing: avoid overhangs where you can, put heat-set inserts everywhere a screw enters plastic, and make the link lengths a round number, because you will be typing them into your kinematics repeatedly. Keep the first version ugly and simple — you will print version three.

#### M2.4 · Write the URDF and see it in rviz2

Links, joints, axes, limits. Run `robot_state_publisher` with a joint state slider and watch it move. Getting frame conventions and joint axes right here, in isolation, saves enormous pain later.

#### M2.5 · Simulate in Gazebo Harmonic

Spawn the URDF, add `ros2_control` with a simulated hardware interface, and command joint positions. The arm moves in simulation with no physical hardware involved. This is a real milestone, not a rehearsal.

#### M2.6 · Print and assemble, and build the gripper

Links in PETG-CF or PA6-CF, brackets in PETG, gripper pads in TPU. Heat-set inserts everywhere. Threadlocker on every fastener that will see vibration. Expect to reprint at least one part because of a tolerance you got wrong — this is normal and is why the printer beats an outsourced print service for iteration.

The gripper is its own session (Workbook S2.10) and it is not optional: Stage 3 has nothing to pick up without it and Stage 4’s whole payoff is opening and closing it from your own muscles. Size the servo, build it, and then **weigh it and put the real mass back into the M2.2 torque budget** — that number was assumed, and this is the moment it stops being an assumption.

#### M2.7 · Write the ros2_control hardware interface

A C++ class implementing the `SystemInterface` lifecycle: `on_init`, `read`, `write`. Your `read` pulls the latest joint states from the CAN bus; your `write` pushes target positions out. This is the seam between the two layers, and it is where your firmware work and your ROS 2 work finally meet.

Start with a plain serial bridge from the host to one gateway microcontroller that talks CAN to the joints. Migrate to micro-ROS later if you want the joints to be ROS 2 nodes themselves.

#### M2.8 · Homing and calibration

Incremental encoders do not know where they are at power-up. Write a homing routine — drive slowly toward a limit switch, zero the count, retreat to a known pose. Every real robot does this on boot, and building it now is far easier than retrofitting it.

#### M2.9 · MoveIt 2 and Cartesian commands

Configure MoveIt 2 for your arm, then command the gripper to a position in space and watch coordinated multi-joint motion happen. This is the moment it stops being two motors and becomes a robot.

#### M2.10 · Record and replay

Capture a session with `ros2 bag` — every joint state, command, and diagnostic. Replay it. Plot it. This is the infrastructure that makes everything after this stage debuggable, and it costs one command.

> **PORTFOLIO MOMENT** — The torque budget is a portfolio artifact in its own right. Compute the static torque at each joint, compare it to your motor’s derated continuous figure, and write the ADR: here is the number, here are the five ways out, here is the one I chose and what it costs me. An engineering decision with its arithmetic attached is worth more in an interview than any amount of working code.

### Kinematics you derive yourself

Do not skip this by importing a solver. For a two-link planar arm with lengths L1 and L2 and joint angles θ1 and θ2, forward kinematics is two lines of trigonometry, and inverse kinematics is about a page of algebra using the law of cosines. Derive both on paper. Implement them in Python. Check them against MoveIt 2's answers and against the physical arm.

The payoff is that the concepts on your skills list — transforms, rotations, rigid body motion, and eventually quaternions — stop being vocabulary and become things you have personally computed. Every larger arm forces you to trust a numerical solver. This geometry does not, and that is precisely why it was chosen.

> **WATCH OUT** — Inverse kinematics for a two-link arm generally has *two* solutions — elbow-up and elbow-down. Your solver must choose, and choosing badly means the arm flips configuration mid-motion in a way that looks alarming and can collide with itself. Deciding how to pick, and enforcing it, is part of the exercise rather than an edge case.

> **WATCH OUT** — Fit the emergency stop before the first powered test of the assembled arm. A multi-joint arm with a sign error moves fast, in an unexpected direction, with real torque. Wire the stop to cut motor power — not logic power, so the system can report what happened.

> **CHECK YOURSELF** — Proceed when: (1) the arm moves in Gazebo and in reality from the same commands; (2) you can command a Cartesian target and get coordinated motion; (3) rviz2 shows the real arm's live state; (4) you can derive the forward and inverse kinematics on paper without notes; (5) homing works reliably from any starting pose; and (6) you have a recorded bag file you can replay and plot.

#### Skills retired

ROS 2 nodes, topics, services, actions · custom messages · parameters and launch files · colcon · rviz2 · ros2 bag · tf2 · URDF · ros2_control · MoveIt 2 · Gazebo · forward and inverse kinematics · rigid body motion · linear algebra, transforms, rotations · modern C++ · Linux command line fluency.

> **LOOK THIS UP** — Josh Newans' *Articulated Robotics* series is the clearest available material on URDF, ros2_control, and Gazebo integration. It is framed around a mobile robot, but the URDF, tf2, and ros2_control content transfers directly. Antonio Brandi's *Robotics and ROS 2 — Learn by Doing! Manipulators* is built around a 3D-printed arm driven by ROS 2 and an Arduino, with MoveIt 2 and a voice interface — close enough to Mimic to be worth working through, though it targets an older ROS 2 release, so expect to port a few things.

## Stage 3 · Eyes and Voice

| | |
|---|---|
| **Duration** | About eight weeks |
| **Cost** | CA$0–70 — nothing at all if a webcam and a microphone are already on your shelf |
| **Needs first** | Stage 2 exit criteria met |
| **Printer?** | Only for camera and microphone mounts |
| **You will own** | An arm that finds an object with a camera and picks it up when you ask it to, out loud, with no cloud service involved |

> **GO TO THE WORKBOOK** — **Stages 3–5 Workbook, Volume VI** — milestone depth rather than session depth, deliberately. These stages are six to twelve months out and almost entirely software, and the speech and language tooling will have moved by the time you arrive. The volume carries the mathematics that does not go stale — the pinhole model, the EMG feature set, the complementary filter, the impedance relation — and points at current documentation for the rest. Write the sessions when you reach the Stage 2 gate.

### Why this stage exists

Everything so far has been about making the arm *capable*. This stage is about making it *commandable by a human who is not a programmer* — which, for assistive technology, is the entire point. A device that requires you to type joint angles is not assistive.

It is also the stage that makes the project legible to other people. "I built a robot arm" produces polite interest. "I built a robot arm that I talk to" produces a conversation.

### What you are building

Two independent input pipelines feeding the same motion interface. A vision pipeline that locates an object and produces a grasp pose. A speech pipeline that transcribes what you said, interprets it, and issues a goal.

### The build, in milestones

#### M3.1 · Camera, calibrated

A USB webcam is fine to start. Run camera calibration to get intrinsics and correct lens distortion. This is unglamorous and everything downstream depends on it — an uncalibrated camera produces grasp positions that are confidently wrong.

#### M3.2 · ArUco markers before neural networks

Stick a printed fiducial marker on a block. Detect it, recover its full pose, and publish it as a tf2 frame. Now the arm knows where the block is in its own coordinate system, and you have a complete perception-to-motion pipeline with no machine learning at all. Resist the temptation to start with an object detector; this milestone teaches you the geometry, which is the hard part.

#### M3.3 · Hand-eye calibration

The camera sees things in camera coordinates. The arm moves in base coordinates. Finding the fixed transform between them is hand–eye calibration, and it is the step people skip and then wonder why the gripper always misses by two centimetres in the same direction.

#### M3.4 · Pick and place, closed loop

Detect, plan, approach, grasp, lift, place. Handle failures — what happens when the object is out of reach, or the marker is occluded mid-motion? Getting the failure paths right is most of the work.

#### M3.5 · Local speech to text

A Whisper-based ROS 2 node with voice activity detection so it only transcribes when you are actually speaking. Run it locally. Confirm you get reliable text out before adding any interpretation layer.

#### M3.6 · Language to intent

A local language model that takes the transcript and emits a structured command — an action name and parameters — rather than prose. Constrain the output format hard, validate it, and reject anything malformed. The model proposes; your code decides whether it is a legal, safe motion.

#### M3.7 · Speak back

Text to speech for confirmations and refusals. "Moving to the blue block." "I can't reach that." Closing the loop conversationally matters more for perceived quality than any other single thing in this stage.

> **WATCH OUT** — Never let a language model's output reach the motion layer unvalidated. It should select from a fixed set of actions with bounded parameters, and your code should check reachability and joint limits before anything moves. This is not paranoia about models — it is the same discipline you would apply to any untrusted input, and it is exactly the habit that safety-critical work demands.

> **PORTFOLIO MOMENT** — Two artifacts here, and both are cheap on the day and impossible to reconstruct afterwards. **The hand–eye residual:** record the gripper’s miss distance before and after M3.3, as two numbers and a scatter plot. “It missed by 23 mm in a consistent direction; after solving *AX = XB* it missed by 2 mm in no particular direction” is a complete engineering story in one line, and nobody who skipped the calibration has it. **And film a failure:** ask for something out of reach, on camera, and let the arm refuse and say why. Every portfolio has a success video. Almost none has a graceful refusal — and refusals are what assistive-technology reviewers actually look for.

> **CHECK YOURSELF** — Proceed when: (1) a spoken instruction reliably produces the right motion; (2) the arm picks up a marked object from a position it was not told about; (3) it refuses impossible requests gracefully and says why; and (4) the whole pipeline runs locally with the network cable unplugged.

> **WHERE THIS POINTS** — Assistive robotics for people with limited mobility lives or dies on the input modality. Voice and gaze are the dominant research directions precisely because a joystick is not available to everyone. Building a voice-commanded manipulator puts you in direct contact with the actual design problem of the field.

#### Skills retired

OpenCV · camera calibration · Python for robotics · perception-to-motion pipelines · ROS 2 actions in practice · local model deployment · input validation and safe command handling.

## Stage 4 · The Biomech Payload

| | |
|---|---|
| **Duration** | About ten weeks |
| **Cost** | ~CA$150–250 on the budget path |
| **Needs first** | Stage 3, though the dataset work can start any time |
| **Printer?** | For electrode mounts and wearable brackets |
| **You will own** | An arm that mirrors your own arm's posture and opens and closes its gripper from your forearm muscle activity |

> **GO TO THE WORKBOOK** — **Stages 3–5 Workbook, Volume VI** — milestones M4.1 to M4.6, at milestone depth rather than session depth. It carries the EMG feature set, the window-length trade-off, the complementary filter and the electrode-safety reasoning, and points at current documentation for the tooling. **M4.1 needs no hardware at all** — start it during Stage 2’s print waits.

### Why this stage exists

This is the stage the whole project was aimed at. Everything before it was building a machine capable of being controlled. This is where a human body becomes the controller — which is the definition of the field you are heading into.

> **PORTFOLIO MOMENT** — Report **within-session and cross-session accuracy separately**, and be honest about the gap. The gap is the interesting finding, not a flaw in your work — it is one of the central unsolved problems in myoelectric control, and discussing it knowledgeably marks you as someone who has read the field rather than a tutorial.

### Start with the software, months early

You do not need any hardware to begin. Public surface EMG datasets exist specifically for this — the Ninapro family being the standard benchmark, recorded from both able-bodied subjects and amputees performing dozens of distinct movements with research-grade equipment.

Download one. Build a feature extraction pipeline and a gesture classifier. Get a confusion matrix. Learn what root-mean-square, waveform length, zero crossings, and slope sign changes are, and why those particular features dominate the literature. Do all of this while Stage 2 is still printing, so that when your electrodes arrive you already know what a good signal looks like.

> **DEFINITION** — **Surface EMG** measures the electrical activity of muscle fibres through the skin. The raw signal is microvolt-scale, bipolar, noisy, and heavily contaminated by mains hum and motion artifacts. It is not proportional to force in any simple way, and the processing chain — band-pass, rectify, smooth, extract features — exists to turn something nearly unusable into a control signal.

### The build, in milestones

#### M4.1 · Dataset work, no hardware

Feature extraction, a classifier, cross-validation, and an honest accuracy figure. Notice how much worse cross-subject accuracy is than within-subject — that gap is one of the central unsolved problems in myoelectric control, and meeting it early calibrates your expectations.

#### M4.2 · Your first real signal, safely

Electrodes on your forearm, MyoWare 2.0, microcontroller on battery *or* behind a USB isolator. Clean the skin properly. Look at the raw waveform. Clench, release, and watch it. This is a genuinely memorable moment and it is worth doing carefully.

#### M4.3 · Threshold control

Rectify, smooth, threshold, and open or close the gripper. Crude, immediate, and enormously satisfying. It also teaches you why crude is not enough — the threshold that works when you are rested does not work when you are fatigued.

#### M4.4 · Your own classifier, on your own signal

Record your own gesture data with consistent electrode placement. Train on it. Run inference on the microcontroller or the host. Map gestures to grip commands. Repeatable electrode placement is what makes yesterday's model still work today — an elastic band with marked positions is a legitimate engineering solution.

#### M4.5 · Wearable IMUs and your own sensor fusion

Two inertial sensors, one on the upper arm and one on the forearm. Write a complementary filter, then a Kalman filter, and compare them. Use the raw six-axis parts rather than a chip that does fusion internally — the fusion is the skill you are here for, and buying a part that does it for you removes the exercise.

#### M4.6 · Mirroring

Your shoulder and elbow angles, estimated from the fused IMU data, become the arm's joint targets. It follows you. Combined with M4.4, you now have posture from your limb and grip from your muscles — which is, in miniature, the control scheme of a myoelectric prosthesis.

> **WATCH OUT** — Electrode safety is the one genuine physical risk in this project. When anything is attached to your skin, the microcontroller must be either battery-powered or galvanically isolated from mains-powered equipment. Do both. This is also the habit the medical device world will expect you to have internalised, and the reasoning behind it is worth being able to articulate.

> **WATCH OUT** — Nothing here is a medical device, and nothing here should be used as one. Mimic is a learning platform. Keeping that boundary explicit — in your README, in conversation, in your own head — is part of behaving correctly in this field.

> **CHECK YOURSELF** — You have finished Mimic when: (1) you can explain your EMG processing chain from electrode to decision; (2) a trained classifier works across sessions on different days; (3) the arm mirrors your posture with a filter you wrote and can explain; (4) you can state the difference between your within-session and cross-session accuracy and why the gap exists; and (5) the whole thing runs end to end without you touching a keyboard.

#### Skills retired

Sensor fusion · Kalman and extended Kalman filters · quaternions · probability and statistics · biosignal processing · applied machine learning on real sensor data · human–machine interface design · electrical safety reasoning.

> **LOOK THIS UP** — Alongside the hardware, the musculoskeletal simulation ecosystem is worth picking up on the software side: MuJoCo for fast physics, MyoSuite for physiologically accurate arm and hand models built on it, and OpenSim for anatomically detailed biomechanics. These let you model tendon-driven hands and assistive devices without building them, and they are pure Python — well within your existing skill set.

## Stage 5 · Optional · Impedance and Rehab Mode

| | |
|---|---|
| **Duration** | Open-ended |
| **Cost** | Minimal — mostly software on hardware you already have |
| **Needs first** | Stage 2 at minimum; Stage 4 makes it richer |
| **You will own** | An arm that is compliant rather than stiff, and can guide, assist, or resist a human hand |

> **GO TO THE WORKBOOK** — **Stages 3–5 Workbook, Volume VI**, final chapter — the impedance relation, current-based force estimation, gravity compensation, virtual constraints, and an honest caution about what a non-backdrivable gearbox will and will not let you achieve.

### Why you might do this

Every controller so far has been a *position* controller: the arm goes where it is told and resists being moved. That is exactly wrong for anything that physically contacts a person. A rehabilitation robot must be soft, must yield, and must apply gentle forces rather than hold rigid positions.

Impedance control is the answer, and it is the single most valuable additional concept for the direction you are heading. It is also the concept that turns Mimic from "a robot arm" into "a device that could plausibly do therapy," which is a meaningfully different portfolio story.

> **DEFINITION** — **Impedance control** commands a *relationship* between position and force rather than a position. You specify a virtual stiffness, damping, and mass, and the arm behaves as though the endpoint were attached to its target by a spring and damper with those properties. Low stiffness gives you an arm you can push around; high stiffness approaches position control.

### What to build

- **Current-based force estimation.** Motor current is roughly proportional to torque. With the INA219 already on each joint, you can estimate endpoint force without a force sensor. Crude, but sufficient and free.
- **Gravity compensation.** Compute the torque needed to hold the arm's own weight at any pose and apply it feedforward — the same expression you derived in the Stage 2 torque budget, evaluated continuously at the current angles rather than once at worst case. The arm becomes weightless in your hand: a striking demonstration and a prerequisite for everything else here.
- **Virtual constraints.** A software wall the endpoint cannot cross, or a groove it is guided along. This is the mechanism behind guided rehabilitation exercises.
- **Assistive and resistive modes.** Help the user complete a movement, or oppose it for strength training. Adjust assistance based on measured performance.

> **PORTFOLIO MOMENT** — **Film the gravity compensation, the day it works.** Thirty seconds of your hand moving a powered arm around as though it weighed nothing, then the same arm rigid with compensation switched off, is the most legible artifact this project will ever produce — it needs no plot, no explanation and no domain knowledge to land. It is also the one you cannot reshoot: it depends on a gravity model fitted to a specific arm on a specific day, and the moment you change a link or a motor it is gone. Straight into the website repository, and put it at the top of the site.

> **WHERE THIS POINTS** — This is the actual working principle of upper-limb rehabilitation robots, which are frequently planar two-degree-of-freedom machines for the same reasons Mimic is. If any part of your future work heads toward therapy devices, exoskeletons, or anything that shares physical space with a person, impedance control is the foundational concept — and having implemented it, however crudely, on hardware you built is a genuinely distinguishing thing to be able to say.


---

# PART III — REFERENCE



Where each skill gets checked off, what each stage costs, what to read, and what to build after this.

## Appendix A · Skills Traceability

Your robotics skills list, mapped to where Mimic actually retires each item. Anything marked *not covered* is either deferred by design or genuinely outside this project.

### Languages and embedded

| Skill | Where |
|---|---|
| Modern C++ (C++17+) | Stage 0 loop, Stage 2 hardware interface |
| C for firmware | Stage 1 |
| Python | Stages 2–4: nodes, kinematics, classifiers |
| GPIO, PWM, ADC | Stage 0 |
| UART, I²C, SPI | Stages 0–1 |
| CAN bus | Stage 1 |
| Interrupts and timers | Stages 0–1 |
| Non-blocking code | Stage 0, milestone M0.3 (Workbook S5) |
| Encoders and motor drivers | Stage 0 |
| Reading datasheets | Every stage, unavoidably |
| STM32 (HAL/CubeMX); ESP32 as a second-vendor node | Stage 1 core. The ESP32-S3s are *not* a Stage 0 board — see Chapter 4 |
| RTOS basics (FreeRTOS) | Stage 1, milestone M1.3 |

### Control and mathematics

| Skill | Where |
|---|---|
| PID | Stage 0 — the whole stage |
| Feedback loops, stability, tuning | Stage 0 |
| State-space control | *Not covered.* Build a Furuta pendulum, or extend Stage 5 |
| Kinematics, forward and inverse | Stage 2, derived by hand |
| Rigid body motion | Stage 2 |
| Linear algebra, transforms, rotations | Stage 2 |
| Quaternions | Stage 4, IMU fusion |
| Probability and statistics | Stage 4, classifier evaluation |
| Kalman and extended Kalman filters | Stage 4, milestone M4.5 |
| Sensor fusion | Stage 4 |
| Particle filters | *Not covered.* Localisation technique; deferred by design |

### ROS 2, simulation, and Linux

| Skill | Where |
|---|---|
| Nodes, topics, services, actions | Stages 2–3 |
| Custom message types | Stage 2 |
| Parameters and launch files | Stage 2 |
| colcon | Stage 2 |
| rviz2 | Stage 2 |
| ros2 bag | Stage 2, milestone M2.10 |
| tf2 | Stages 2–3 |
| URDF | Stage 2 |
| ros2_control, MoveIt 2 | Stage 2 — the manipulation stack that matters for you |
| Gazebo | Stage 2, milestone M2.5 |
| Nav2, slam_toolbox, AMCL | *Not covered, deliberately.* Mobile robot navigation |
| Behaviour trees | *Not covered.* Optional Stage 3 extension |
| Command line, systemd, gdb | Stages 1–2 |
| Cross-compilation, real-time scheduling | Stage 1 partially; deepen later |

### Perception and medtech

| Skill | Where |
|---|---|
| OpenCV, camera calibration | Stage 3 |
| LiDAR, SLAM, point clouds | *Not covered, deliberately* |
| IEC 62304, safety-critical practice | *Not covered.* Read once, years out. Stage 1 fault handling is the habit that prepares you |

## Appendix B · Budget by Stage

Approximate Canadian dollars, mid-2026, before tax. The budget path assumes the substitutions discussed in the parts document: an N20 motor for Stage 0, a budget enclosed printer, **your existing desktop as the ROS 2 host**, a webcam and microphone you already own, and raw six-axis IMUs rather than chips that fuse internally.

| Stage | Budget path | Comfortable path | The difference |
|---|---|---|---|
| Tooling | ~$230 | ~$450 | Bench PSU, crimpers, organizers. |
| Stage 0 | ~$120 | ~$200 | Premium gearmotor and encoder |
| Stage 1 | ~$90 | ~$140 | Dedicated USB-CAN analyzer |
| Stage 2 | ~$700 | ~$1,200 | Printer tier; optional Raspberry Pi |
| Stage 3 | ~$60 | ~$180 | Dedicated camera, microphone array |
| Stage 4 | ~$180 | ~$330 | Fusion IMUs, extra EMG shields |
| **Total** | **~$1,380** | **~$2,500** |  |

The table above is the estimate. Against it, the first order was placed on 31 July 2026 and came to
**CA$534 before tax, CA$609 after 14 % NS HST**, covering the tooling tier and all of Stage 0 in one
purchase — the itemised record is in the *Order Manifest*. The remaining spend, itemised in *What's
Left to Buy*, is about **CA$912 pre-tax**, which brings the project total to roughly **CA$1,446
pre-tax, CA$1,648 with HST** — **CA$66 over** the budget-path figure in the table.

**That CA$66 is a net figure and you should not read it as the estimate having held up.** It is two
much larger movements very nearly cancelling:

```
Tooling + Stage 0            est ~$350, actual $534   + $184   (53 % over)
Stages 1 through 4           est $1,030, now  $912    − $118
                                                      ───────
Net                                                    + $66
```

Note on naming: the tooling row above is not a lettered tier. The tiers in
*What's Left to Buy* run **B to G** and cover only what is still unbought;
tooling and all of Stage 0 were bought outright in the 31 July order and are
recorded in the *Order Manifest* instead.

The overrun is real and the offset is soft. Stages 1 through 4 have come down partly through
genuinely better pricing, and partly because Stage 3 is currently costed at zero on the assumption
that a webcam and a microphone are already on the shelf — an assumption, not a fact. **One large miss
and two soft assumptions, summing to something that looks like accuracy.**

Stage 2 additionally carries a **quantified deferral** rather than a saving. Workbook session S2.4's
supply arithmetic shows the existing 12 V 5 A adapter running at 44 % normally and 96 % with both joints
stalled — adequate today, with no fault-case margin — so a larger supply sits in Tier D as a costed
option to be taken *after* a measurement rather than before one. **A budget line that says "measured,
adequate, upgrade costed if the measurement changes" is a healthier entry than one that is simply
lower**, and it is worth a sentence in the README.

> **WHERE THIS POINTS** — Tooling is systematically under-estimated on projects like this, because it is bought once and remembered vaguely while parts are itemised and remembered precisely. The useful habit is not a better first estimate — it is re-forecasting against actuals at every stage gate and saying which way it moved. A budget that was wrong and got corrected is a normal engineering artifact; a budget that claims to have been right is one nobody believes.

The single decision that moves the total most is the printer. A budget enclosed CoreXY with a hardened nozzle handles the engineering filaments an arm actually needs, and at current pricing it costs roughly half what the premium option does while having a *higher* hotend temperature rating — which is what matters for carbon-filled filament. Verify the nozzle material on whichever SKU you buy.

The host computer is deliberately not a line item. Your desktop runs ROS 2, Gazebo, and the whole perception and speech stack, and the arm reaches it by cable. If you eventually want the arm untethered, a used small-form-factor office PC is both cheaper and more capable than a single-board computer for something that never leaves a desk — a Raspberry Pi earns its place only when portability or battery operation genuinely matters.

> **WATCH OUT** — The places not to economise: the multimeter, the STM32 development board, any biosignal front end, the USB isolator, the emergency stop, and any mains-connected power supply. Everything else on the list has an acceptable budget substitute.

## Appendix C · Resource Index

Grouped by when they become useful. Reading a ROS 2 tutorial during Stage 0 is a pleasant way to avoid doing Stage 0.

### Stage 0 — control fundamentals

- Brett Beauregard, "Improving the Beginner's PID" — the practical problems, in order.
- The Arduino PID library source. Short, readable, and the comments explain design decisions.
- **Curio Res** — the encoder-reading and PID series on YouTube. The clearest walkthrough of the ISR problem in M0.1. Watch it *after* deriving the transition table yourself, so you are checking your reasoning rather than copying.
- **PulseView / sigrok documentation**, plus the Zadig driver step on Windows.
- **The Arduino Serial Plotter** — a live trace with no host code at all. A sanity check, not a substitute for the CSV pipeline.
- **Your own `docs/motor-spec.md`**. Listed as a resource deliberately: for this motor it is the only datasheet that exists.

### Stage 1 — embedded and CAN

- STMicroelectronics' HAL documentation and the CubeMX user guide. Dry, authoritative, necessary.
- The FreeRTOS official documentation and its task-scheduling tutorials.
- Any solid introduction to CAN framing, arbitration, and termination — the physical layer material matters more than the software.

### Stage 2 — ROS 2 and manipulation

- **docs.ros.org** — the official Jazzy tutorials. Start here, always.
- **Articulated Robotics** (Josh Newans) — URDF, ros2_control, and Gazebo explained clearly. Mobile-robot framing, transferable content.
- **Antonio Brandi, *Robotics and ROS 2 — Learn by Doing! Manipulators*** — a printed arm with ROS 2, an Arduino, MoveIt 2, and voice control. The closest existing analogue to Mimic. Targets an older release; expect to port.
- The MoveIt 2 documentation and its configuration assistant tutorials.
- **The Construct** — structured courses if you prefer guided material.

### Stage 3 — perception and speech

- OpenCV's official camera calibration and ArUco tutorials.
- **whisper_ros** and its companion packages by mgonzs13 — local speech-to-text and language model nodes for ROS 2, including voice activity detection.

### Stage 4 — biosignals and biomechanics

- **Ninapro** — the benchmark surface EMG gesture dataset family, including both able-bodied and amputee subjects.
- SparkFun's MyoWare 2.0 hookup guide, particularly the electrode placement material.
- **MuJoCo** and **MyoSuite** for musculoskeletal simulation; **OpenSim** when anatomical fidelity matters more than speed.

### Reference builds worth studying, not copying

- **AR4 / Annin Robotics** and its community ROS 2 driver — a genuinely maintained ROS 2 arm with MoveIt 2 integration.
- **SO-101 / LeRobot** — the imitation-learning arm ecosystem.
- **InMoov**, **Open Bionics Ada**, **HACKberry** — printable hands, good Stage 4 payload candidates.
- **Furuta pendulum** open builds — the controls rig, if that is the direction you find you love.

## Appendix D · Glossary

**The glossary for this document set lives in *Before You Build*, Chapter "The Vocabulary".** It is
the canonical list: every term the Guide, the workbooks and the parts documents assume, grouped by
subject rather than alphabetically, and it covers considerably more ground than a reference appendix
sensibly could — mechanics, C and C++ on a small chip, RTOS vocabulary, power electronics, the
STM32's clock and interrupt hardware, ROS 2, printing materials, and the camera and biosignal terms
that arrive in Stages 3 and 4.

Two glossaries that partially overlap is worse than one, because the reader has to work out which is
authoritative. So this appendix does not duplicate it.

If a word in this Guide is unfamiliar, that chapter is where to look. The workbooks additionally
define terms at the point you first need them, which is a convenience rather than a second list —
those definitions and the canonical chapter agree.

## Appendix E · What Comes After Mimic

Mimic is a platform, not a terminus. Everything below reuses the hardware, the firmware, and the codebase you already have.

### Extensions that reuse everything

**More degrees of freedom.** A third and fourth joint turns a planar arm into a spatial one and makes inverse kinematics genuinely hard — the point at which importing a numerical solver becomes the right call rather than a shortcut, and you will understand what it is doing.

**A tendon-driven hand.** Replace the gripper with a printed multi-finger hand pulled by Dyneema line with spring returns. Drive it from your Stage 4 EMG classifier. This is the most direct prosthetics project available to you and it plugs straight into what you have built.

**Brushless joints.** Swap geared DC motors for brushless motors with field-oriented control. Quieter, backdrivable, far better for impedance control — and a substantial firmware project in its own right.

**Learning from demonstration.** You have a bag-file pipeline recording every state and command. That is exactly the substrate imitation learning needs. This is where the LeRobot ecosystem becomes relevant to you.

### The second project

With a printer, a working ROS 2 stack, and real firmware experience, an AR4 build stops being an intimidating kit and becomes a weekend of assembly plus a driver you already understand. It is a strong second portfolio piece precisely because it is a *different* skill — integration rather than construction — and having both is more convincing than having either.

### What a hiring manager will actually look at

> **PORTFOLIO MOMENT** — The running order that works, because it is chronological rather than curated: the handwritten derivation, the hand-drawn power tree, the quadrature capture, the loop-rate proof, the two plots showing a gain too low and too high, the disturbance-rejection video, the RTOS pre-emption traces, the protocol document, the torque budget ADR, and the arm moving in simulation and reality from the same command. Ten artifacts, each dated, each produced on the day. That sequence *is* the portfolio — the arm is what generated it.

Not the arm. The repository. Specifically: whether your commit history shows iteration and debugging rather than a single dump; whether your README explains decisions and not just usage; whether there are plots, measured numbers, and evidence you tuned things empirically; whether the firmware has fault handling; and whether you can talk about the failure modes you hit and what you did about them.

The arm is the reason to have all of that. It is not, itself, the artifact.

> **WHERE THIS POINTS** — The specific cluster this project produces — C and C++ on microcontrollers, STM32, SPI, I²C, UART and CAN, interrupts, an RTOS, real debugging with real instruments, plus a demonstrated integration into a larger software system — is close to the exact intersection that embedded, robotics, and medical device firmware postings describe. You will have built it rather than listed it, which is the difference that matters in an interview.

## Appendix F · The Debugging Ladder

Hardware debugging feels different from software debugging because the failure can be in a layer you cannot inspect. The cure is a fixed order of questions, worked from the bottom up, refusing to skip a rung. Almost every hour lost on this project will be an hour spent guessing at rung five when the fault was at rung one.

### Work upward. Never skip.

#### 1 · Is it powered, and at what voltage?

Meter on the actual pin, not the supply's display. Measure again *while the motor is running* — a rail that reads 5.0 V idle and 3.8 V under load explains almost every "random" reset. Check ground continuity between every board that shares signals. The single most diagnostic measurement in Stage 0: meter the 5 V rail at the UNO’s own pin twice, once idle and once with the motor at full command. The delta between those two numbers explains almost every “random” reset.

#### 2 · Is it physically connected?

Continuity test, end to end, with the power off. Breadboard contacts wear out and jumper wires fail inside the insulation where you cannot see it. A wire that looks connected and reads open is common enough that it should be your second guess, not your last.

#### 3 · Is the signal present on the wire?

Logic analyzer. Not inference from behaviour — actually look. Is the PWM there, at the frequency and duty you expect? Are both encoder channels toggling? Is there traffic on the bus at all? This rung is why the analyzer was the first tool on the list.

#### 4 · Is my code actually running, and at the rate I believe?

Toggle a spare pin at the top of the loop and measure it. Loops that quietly run at half their intended rate are extremely common, and every gain you tuned against the wrong rate is wrong. On the Nucleo, set a breakpoint and confirm it hits.

#### 5 · Are the values what I think they are?

Print or watch the actual numbers — encoder count, computed angle, error, controller output — at each stage of the chain. This is where unit errors surface, and they will surface as a number that is wrong by exactly 4, 2π, 57.3, or the gear ratio. Those four factors account for most of them.

#### 6 · Is my logic wrong?

Only now. If rungs one through five all check out, the bug is in your reasoning, and you can debug it the way you debug any software — which you are already good at.

### Two habits that shorten every session

**Change one thing at a time and write down what you changed.** The temptation when stuck is to alter three things and retest. It works occasionally and teaches you nothing, and when it does not work you have tripled your search space.

**Have a known-good baseline you can return to.** A tagged Git commit where the joint held position correctly is worth more than any amount of cleverness at two in the morning. If you cannot get back to working, you cannot bisect.

> **WATCH OUT** — The specific trap in this project: symptoms that look like software but are electrical. Resets under load are a power problem. Erratic encoder counts are usually noise coupling or too much work in the interrupt handler. Intermittent faults that appear weeks in are almost always a wire fatiguing at a joint. If a bug behaves in a way software cannot explain, drop back to rung one.

### The instruments, and what each one is for

- **Multimeter** — is it powered, is it connected, what is the resistance. Rungs 1 and 2.
- **Logic analyzer** — is the digital signal there and correct. Rung 3, and it is the tool you will reach for most.
- **Debugger over SWD** — is the code running, what is in this variable, stop time and look. Rungs 4 and 5, and only available once you are on the STM32.
- **Serial print** — coarse but universal. Rungs 4 and 5 on any board. Beware that printing changes timing, which occasionally makes the bug move.
- **Oscilloscope** — analog shape, noise, ringing. Not needed until Stage 4, when you are looking at biosignals rather than logic levels.

## Appendix G · Timeline at 2–3 Hours a Day

About five months of active work, landing at about seven months of calendar time. The extra two months are shipping, printing, and the fact that some things do not go faster when you throw hours at them.

### The estimate

The durations in each stage's at-a-glance panel assume a casual hobby pace of five to eight hours a week. At two to three hours a day — call it fifteen to twenty hours a week — you are moving at roughly twice that (44 hobby weeks compress to 21–24). But it does not scale linearly, and being honest about why is more useful than a smaller number.

| Stage | Hobby pace | At 2–3 h/day | Binding constraint |
|---|---|---|---|
| Stage 0 — single joint | 6 weeks | **2–3 weeks** | Parts shipping, not your hours |
| Stage 1 — smart joint | 8 weeks | **4 weeks** | Toolchain learning curve |
| Stage 2 — arm + ROS 2 | 12 weeks | **8 weeks** | Print time and mechanical iteration |
| Stage 3 — eyes and voice | 8 weeks | **3–4 weeks** | Compresses well; mostly software |
| Stage 4 — biomech payload | 10 weeks | **4–5 weeks** | Dataset work can run in parallel earlier |
| **Total active** | **44 weeks** | **21–24 weeks** | ≈ 5 months |
| **Calendar, realistically** | — | **28–30 weeks** | ≈ 7 months, with the gaps below |

21–24 weeks is 4.8 to 5.5 months, so "about five months active, seven calendar" is the figure to quote — here, in *Before You Build*, and anywhere else you state it. Do not round the active figure up to six; the table is the arithmetic and the prose has to match it.

### What does not compress, no matter how many hours you put in

**Shipping.** AliExpress to Nova Scotia is two to four weeks and occasionally six. This is the dominant constraint on Stage 0's calendar time — not the work, the wait. Order the first batch before you need it and spend the gap on modern C++, the Curio Res encoder and PID series, and Brett Beauregard’s PID writing — none of which needs a single part to have arrived.

**Print time and mechanical iteration.** An arm link is a six to twelve hour print. The loop is design, print, discover a tolerance is wrong, redesign, reprint — and you will go around it two or three times per part. You can work on firmware while the printer runs, which helps, but the iteration count is fixed by how good your CAD is, and early CAD is not good. This is why Stage 2 is the stage that stretches.

**Debugging plateaus.** There are days where three hours produces nothing and the fourth hour produces worse than nothing, because you start changing multiple things and lose your baseline. When you hit one of these, stopping is genuinely the correct engineering decision. The bug is very often solved in the shower the next morning.

**Consolidation.** Control theory and coordinate transforms are the kind of material that needs sleep between exposures. You can read about integral windup in twenty minutes; understanding it takes watching it happen, thinking about it, and coming back.

### What compresses very well

Reading, watching, coding, and assembly all scale close to linearly with hours. So does the entire software side of Stage 3, and the dataset portion of Stage 4. If you want to convert hours into progress efficiently, front-load these.

### Running things in parallel

Three overlaps are worth deliberately engineering, and together they are most of the difference between seven months and nine:

- **During the first shipping wait:** patch anything shaky on the capability audit, work through modern C++, watch the Curio Res encoder and PID series, and install Ubuntu and ROS 2. None of this needs parts.
- **During Stage 2 print waits:** start the Stage 4 dataset work. Feature extraction and a gesture classifier on Ninapro data needs no hardware at all, and arriving at Stage 4 already knowing what a clean EMG signal looks like removes weeks.
- **During Stage 1:** build the URDF and get the arm moving in Gazebo before any physical part exists. Simulation debugging is free and it means Stage 2's hardware problems are only hardware problems.

### A sustainable shape for the week

Two hours on five or six days beats three hours on seven. The seventh day is where burnout accumulates and where the debugging plateaus turn into a stalled project, and a stalled project at month four is the most common way builds like this die — not because the work was too hard, but because the momentum went.

A shape that works: one longer session at the weekend for the messy physical work — assembly, soldering, printing, wiring — and shorter weekday sessions for firmware, reading, and tuning. Physical work has setup and teardown cost and rewards a long block. Code does not.

> **CHECK YOURSELF** — Useful pace markers. One month in: a joint holding position with a plotted step response. Three months in: two smart joints talking over CAN. Five months in: an arm moving under MoveIt 2. Seven months in: it hears you and reads your muscles. If you are well behind these, the usual cause is skipping an exit gate — not a lack of hours.

## Appendix H · Milestones to Workbook Sessions

This guide numbers the work as **milestones**. The workbooks number it as **sessions**. They are the same work at two levels of detail, and this is the map between them. When a chapter says “see M0.6”, this is how you find the evening it corresponds to.

> **DEFINITION** — A **milestone** is a capability — something that is true afterwards that was not true before. A **session** is two to four hours at a bench. Milestones are what you claim; sessions are what you do. Some sessions carry no milestone at all, which is fine and is noted below — setup and units are not achievements, they are the price of them.

> **Milestone numbering.** Every milestone is prefixed with its stage: `M0.6` is Stage 0's sixth, `M1.6` is Stage 1's, `M2.6` is Stage 2's. Without the prefix `M6` names five different pieces of work and no cross-reference resolves.

### Stage 0 — Workbook Volume III, thirteen sessions S0–S12

| Guide milestone | Session | Note |
|---|---|---|
| **M0.0** · Mount it rigidly | S1 | The “bolt it down” build block |
| **M0.1** · Decode quadrature without losing counts | S1 + S3 | Derive in S1, implement and measure in S3 |
| **M0.2** · Drive both directions, fix the sign once | S4 |  |
| **M0.3** · Prove the loop rate on an instrument | S5 |  |
| **M0.4** · Telemetry that fits the serial budget | S7 |  |
| **M0.5** · Close a proportional loop and find *Ku* | S8 |  |
| **M0.6** · Add D, then I, with kick and windup handled | S10 |  |
| **M0.7** · Log a step response and name its four metrics | S9 | The workbook does this *before* M0.6, deliberately — you cannot tune what you cannot measure |
| **M0.8** · Fit the safety envelope | S11 (part A) |  |
| **M0.9** · Refactor to Joint, Encoder, PIDController | S12 | Rung 2 of Interlude D’s ladder |
| *no milestone* | S0 | Bench, toolchain, repository |
| *no milestone* | S2 | Power topology — this guide covers it only under “what will go wrong” |
| *no milestone* | S6 | Units and the conversion chain — see Interlude C |
| *no milestone* | S11 (part B) | Register-level PWM. Rung 3 of the ladder |

### Stage 1 — Workbook Volume IV, ten sessions S1.0–S1.9

| Guide milestone | Session | Note |
|---|---|---|
| **M1.1** · Blink, and the breakpoint | S1.0 + S1.1 | Project tour, then the debugger |
| **M1.2** · Port the control loop to bare STM32, in C | S1.2 – S1.4 | Clock tree, hardware quadrature, then the loop |
| **M1.3** · Introduce FreeRTOS | S1.5 |  |
| **M1.4** · Get two nodes talking on CAN | S1.6 | Also where the ESP32-S3 bus monitor lives |
| **M1.5** · Design and implement your joint protocol | S1.7 |  |
| **M1.6** · Fault handling and the silent-host problem | S1.8 |  |
| **M1.7** · Flash it twice | S1.9 |  |

### Stage 2 — Workbook Volume V, fifteen sessions S2.0–S2.14

| Guide milestone | Session | Note |
|---|---|---|
| **M2.1** · Derive the kinematics on paper | S2.2 + S2.3 |  |
| **M2.2** · Compute the torque budget | S2.4 | The one that changes your parts list |
| **M2.3** · Design the arm in CAD | S2.5 |  |
| **M2.4** · Write the URDF and see it in rviz2 | S2.6 |  |
| **M2.5** · Simulate in Gazebo Harmonic | S2.7 + S2.8 | Gazebo, then ros2_control against mock hardware |
| **M2.6** · Print and assemble, and build the gripper | S2.9 + S2.10 |  |
| **M2.7** · Write the ros2_control hardware interface | S2.11 |  |
| **M2.8** · Homing and calibration | S2.12 |  |
| **M2.9** · MoveIt 2 and Cartesian commands | S2.13 |  |
| **M2.10** · Record and replay | S2.14 |  |
| *no milestone* | S2.0 + S2.1 | Host bring-up and ROS 2 fundamentals |

### Stages 3–5 — Workbook Volume VI

These are one-to-one and now share the same names: this guide’s Stage 3 milestones **M3.1–M3.7** are the workbook’s M3.1–M3.7, and Stage 4’s **M4.1–M4.6** are M4.1–M4.6. Stage 5 is a list of four things to build in order, in both documents. Volume VI is deliberately at milestone depth rather than session depth — write the sessions when you reach the Stage 2 exit gate, by which point you will know what your arm actually is.

> **WHERE THIS POINTS** — Keeping this table current is a two-minute job at every gate and it is worth doing, because a document set whose cross-references resolve is itself evidence. Anyone who has maintained real specifications knows how quickly they stop pointing at anything, and a reader who checks one reference and finds it correct will stop checking.

---

## Figure index

Every figure in this document is plain ASCII/box-drawing art inside a fenced code
block, tagged `FIGURE <id> — <title>` on its first line. That is deliberate: it
renders correctly in GitHub and in any Markdown viewer, and it stays diffable in
Git. For a PDF export, set the monospace font to one with full box-drawing
coverage — **DejaVu Sans Mono** is the usual answer; the core PDF monospace fonts
do not carry the geometric and box-drawing characters these figures use — in this
volume: `═ ╤ ╪ ╱ ╲ ▌ ◄ ► ▲ ▼ ↑ ← → ≈ · … ●` — and will drop or substitute them.

Figure ids here carry the volume number, so `II.5` is "Volume II, figure 5" and
cannot be confused with a workbook's session-scoped ids.

| Figure | Title | Where |
|---|---|---|
| **II.1** | The two layers, the seam, and the rates each side owes the other | Ch. 2 · The Architecture |
| **II.2** | PWM: how a digital pin makes an analog-ish output | Interlude A |
| **II.3** | Quadrature: how two square waves encode direction | Interlude A |
| **II.4** | The four buses, side by side | Interlude A |
| **II.5** | What a fixed-rate loop looks like in time | Interlude B |
| **II.6** | Where the numbers come from: the conversion chain | Interlude C |
| **II.7** | The ladder: peeling back Arduino, one rung at a time | Interlude D |
| **II.8** | From code to silicon | Interlude E |
| **II.9** | Frames of reference | Interlude F |

---

## Now go bolt a motor to a plank

Stage 0 does not need the printer, the Pi, the electrodes, or the bus. It needs one motor, one driver, one encoder, and the patience to plot a step response and ask why it looks like that.

Everything in this guide is downstream of that one thing working.