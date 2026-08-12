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
| **This one** — Appendix Zero | *What am I looking at?* | Once at the start, then as a dictionary |
| **Mimic Project Guide** — Vol II | *Why this project, and what is each stage for?* | Once through, then whenever motivation dips |
| **Stage Workbooks** — Vols III–VI | *What do I do tonight?* | Open on the bench, every session |
| **What's Left to Buy** | *What do I still need?* | Before each stage's order |
| **Order Manifest** | *What did I already buy?* | Historical record. Never edit it. |

This document explains; the workbooks instruct. Anything that tells you what to do on a given
evening — session order, the arithmetic with your actual parts, code skeletons, and the test that
closes each session — lives in a workbook, not here.

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

An hour or two to read Part I. One evening for the repository and the Windows-side installs. A second
evening for native Ubuntu, any time in the next two months.

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

Every term the other documents assume you already know, grouped by what they are about rather than
alphabetically, because they make more sense in clusters. You do not need to memorise this — you need
to have read it once so the words stop being opaque.

**This is the canonical glossary for the whole document set.** Where a workbook defines a term at the
point you first need it, that definition is a convenience; this chapter is the complete list. Terms
appear here even when you will not meet them for months, because a dictionary you can only use after
you already know the word is not a dictionary.

### Words about places and roles

**Bench** *(also: workbench, "on the bench", "bench work")* — Your physical work surface. "Bench
electronics" means work done with loose components on that surface rather than on a finished machine,
which is what Stages 0 and 1 are. "On the bench" means "in my working setup." "Bench bring-up" means
powering something new for the first time and checking it behaves.

**Host** — The full-sized computer that runs the big, non-time-critical software: the planner, the
simulator, the camera and speech processing. In Mimic the host is your desktop, and the arm connects
to it by cable. "Host" is a role, not a particular machine.

**Target** — The small chip you are programming — the microcontroller that runs the control loop. It
is called the target because it is the target of the compiler and debugger. Host and target is the
standard pairing in embedded work.

**Rig** — A temporary assembly built to test one thing. Your Stage 0 rig is a motor, a driver board
and a microcontroller screwed to a plank. Not meant to be pretty or permanent.

**Node** — Used two ways, worth separating now. A **CAN node** is a physical device on the shared bus
— each joint is one. A **ROS 2 node** is a single small program on the host. Context tells you which;
the CAN meaning shows up in Stage 1, the ROS meaning in Stage 2.

**Degree of freedom (DOF)** — One independent way the arm can move. A joint that rotates is one. "Two-
DOF planar arm" means two rotating joints moving in a flat plane. Your gripper opening is usually
counted separately.

**End effector** — Whatever is on the end doing the actual work — here, the gripper. Also called the
tool; the point you care about positioning is the tool centre point.

**Joint space and Cartesian space** — Two ways of describing where the arm is. Joint space is a list
of angles. Cartesian space is a position in the room. Converting between them is the central
mathematical problem of Stage 2, and the shift from thinking in one to the other is the conceptual
core of arm robotics.

### Words about code

**Firmware** — The program running on a microcontroller. It is just software, but the name signals it
is small, close to the hardware, and usually the only thing running.

**Toolchain** — The chain of programs that turns source code into something a chip can run: compiler,
assembler, linker, and the utility that copies the result onto the chip. When the guide says "the
point is the toolchain, not the LED," it means the achievement is proving that chain works end to end.

**Flashing** *(also: uploading, programming, burning)* — Copying compiled firmware onto the chip's
permanent memory. "Flash it twice" in Stage 1 means putting the same firmware on two separate boards.

**IDE** — An editor bundled with compiler, uploader and debugger. Arduino IDE and STM32CubeIDE are
both this.

**Library** — Someone else's code you use rather than write. The Arduino ecosystem is largely
libraries — you call `analogWrite()` and never think about the timer underneath. Part of the point of
Stage 1 is removing that comfort deliberately.

**Debugger, breakpoint, watch** — A debugger halts the chip mid-execution so you can look inside it. A
breakpoint is a line you mark where it should stop. A watch is a variable you asked it to display.
This is the professional alternative to scattering print statements, and getting it working is the
single biggest quality-of-life jump from Arduino to real embedded work.

**Repository (repo)** — A folder tracked by git, holding your files plus the complete history of every
change. A **commit** is one saved snapshot with a note. A **branch** is a parallel line of work. A
**tag** is a permanent label on one commit. **GitHub** stores a copy so other machines — and other
people — can reach it.

**Superloop** — The simplest program structure on a microcontroller: one endless loop doing everything
in order. It is what Arduino's `loop()` is. Fine until two things need different schedules, which is
the problem an RTOS solves.

**Build system** — A program whose job is turning a described project into an artifact: it reads a
file saying what you are building and for what, works out what must be compiled and in what order,
fetches what is missing, and drives the compiler. **PlatformIO** is the one this project uses, and
the thing it buys you over an IDE is that the configuration is a committed file rather than a
setting inside an application — so cloning the project is getting the build. Part IV covers
`platformio.ini` key by key.

**Environment**, in PlatformIO — One named configuration: one target, one framework, one set of
flags, written as an `[env:name]` block. A project may have several. Stage 0 has two, and the split
is the useful part: `uno` cross-compiles for the chip, and `native` compiles for the machine you are
sitting at so that pure logic can be tested with no board attached.

**Cross-compilation** — Compiling on one kind of machine for a different kind. `pio run` invokes
`avr-gcc`, which runs on your desktop and emits instructions your desktop cannot execute. It is why
*host* and *target* are separate words, and why you cannot simply run your firmware to test it.

**Include guard, and `#pragma once`** — A header can be pulled into one compilation more than once,
and the second time every declaration in it is a duplicate, which is an error. An include guard is
the classic fix: a unique preprocessor symbol defined at the top and tested for, so the body is
skipped on the second pass. `#pragma once` is one line meaning the same thing, understood by every
compiler you will meet, and immune to the specific bug guards produce — copying a header and
forgetting to rename its symbol, after which the file silently does not exist.

**Unit-test framework, and Unity** — A library that runs small functions asserting things about your
code and reports which failed. **Unity** is the C one, small enough to run on a microcontroller:
assertion macros, a `setUp` that runs before every test so none can contaminate another, a
`tearDown` after, and a `RUN_TEST` per test called from `main()`. There is no discovery — you list
your tests by hand, which is the price of fitting in two kilobytes of RAM.

**CI, and a runner** — *Continuous integration*: a service that runs a script on a fresh machine
every time you push. GitHub's is **Actions**, the script is YAML in `.github/workflows/`, and the
**runner** is the throwaway virtual machine it executes on. The freshness is the whole value —
"it compiles from a clean checkout" is a claim about your project rather than about your laptop, and
a large fraction of hobby repositories cannot make it.

**Git LFS (Large File Storage)** — An extension that replaces large tracked files in the repository
with small text pointers and keeps the real bytes in a separate store, fetched only for the version
you check out. Which files are tracked is declared in `.gitattributes`, which is committed. **The
trap is that `.gitattributes` alone does nothing**: `git lfs install` is a separate act, once per
machine, and without it the rules are inert and your photographs go into git proper with no warning.

**Conventional Commits** — A commit message format, `<type>(<scope>): <subject>`, whose point is that
a history is only evidence if it is legible. Mimic adds two types to the standard set, both because
this is a hardware project: **`tune`** for a gain or threshold changed on evidence, which is neither
a feature nor a fix, and **`hw`** for wiring, mounting or CAD, where the commit message is the only
record because hardware has no `git diff`. Part IV explains both.

**`.editorconfig`** — A file declaring what your *editor* should write: indent style and width, final
newline, trailing whitespace, line length. Understood by VS Code, CubeIDE and most others. It is a
different layer from `.gitattributes`, which governs what lands in the *repository* — one prevents
the problem, the other catches it at commit time, and you want both.

### Words about control

**Control loop** — Code that runs at a fixed rate and each time reads where the motor actually is,
compares that to where it should be, and adjusts the power. That is the beating heart of this entire
project. Everything else is layers on top of it.

**Open loop and closed loop** — Open loop is commanding and hoping: "run at 40 % for half a second."
Closed loop is measuring the result and correcting continuously. The measurement is what closes the
loop, and the sensor that closes it is the encoder.

**Setpoint, error** — The setpoint is the position you are asking for. The error is setpoint minus
actual. Every control loop is fundamentally a machine for making the error small.

**PID** — The standard recipe, named for its three parts. **Proportional** responds to how wrong you
are right now. **Integral** responds to error accumulated over time, eliminating the stubborn small
offset P alone never closes. **Derivative** responds to how fast the error is changing, damping
overshoot. Stage 0 is entirely about this, and you implement it yourself rather than importing it.

**Gain** — The tuning multiplier on each part, written Kp, Ki, Kd. Tuning means hunting for values
that make the joint arrive quickly without oscillating. There is no formula that hands you the
answer — it is empirical, which is exactly why every value gets written down.

**Step response** — The standard diagnostic. Command an instant jump from one position to another and
graph what actually happened. **Rise time** is how long to get there (10 % to 90 %). **Overshoot** is
how far past it went. **Settling time** is how long until it stays within ±2 %. **Steady-state error**
is how far off it eventually settled.

**Integral windup** — A classic failure you will meet personally in Stage 0. If the motor cannot reach
the target for a while, the integral term keeps accumulating, growing enormous. When the motor frees
up it lurches violently past. The fix is to clamp the accumulator, and meeting the problem yourself is
part of the education.

**Anti-windup** — The fix for integral windup, and there are two mechanisms worth knowing because
they address different halves of the problem. **Conditional integration** stops accumulating while
the output is already saturated and the error would push it further into the clamp. **Accumulator
clamping** bounds the stored value so the integral term alone cannot exceed the output range. Use
both; each catches a case the other misses.

**Plant** — Control-theory word for *the thing you are controlling*, taken as a whole: in Stage 0 the
motor, gearbox, driver, shaft and whatever is bolted to it. It is a useful word precisely because it
does not distinguish between them — when you tune, you are tuning against the plant's behaviour, not
against the motor's. A plant is **non-linear** when its response to a command depends on the size of
the command, which yours is: deadband and saturation mean a 90° step and a 10° step do not see the
same effective gain.

**Saturation** — What happens when a controller asks for more output than the hardware can give. Your
command is clamped to ±1.0 and then to ±255, so any demand beyond that is simply lost. It matters
twice: it is half of why integral windup happens, and it is what conditional integration watches for.

**Hysteresis** — Deliberately making a threshold behave differently on the way up and on the way down,
so a signal sitting exactly on it does not chatter. Switch on at 0.6, off at 0.4, and a noisy signal
hovering near 0.5 produces one clean transition instead of forty. You will want it the first time you
drive a gripper from an EMG envelope, and it costs two lines.

**Kinematic chain** — A sequence of rigid links connected by joints, described as a tree of coordinate
frames each defined relative to the one before it. "Walking the chain" means composing those
relationships from the base out to the tip, which is what forward kinematics does.

**Real-time, deterministic** — "Real-time" does not mean fast; it means predictable. A real-time loop
runs every millisecond, every millisecond. Deterministic means the timing does not wander. This
matters because a loop tuned for one rate behaves worse if the rate drifts — and a general-purpose OS
cannot promise it will not.

**Deadline, jitter, latency** — A deadline is when work must finish. Jitter is variation from cycle to
cycle. Latency is delay between cause and effect. **Control loops tolerate latency far better than
they tolerate jitter.**

**Fail-safe** — Designed so a failure produces a safe state rather than an arbitrary one. In Stage 1,
a joint that stops hearing from the host holds position rather than continuing its last velocity
command. The first is bounded; the second integrates without limit.

**Homing** — Finding out where "zero" is at startup. Drive slowly until a limit switch trips, then
call that zero. Necessary because a plain motor encoder counts changes and has no idea where it
started.

**Impedance control** — Stage 5 territory. Instead of commanding a position rigidly, you make the
joint behave like a spring of chosen stiffness, so it yields when pushed by a controlled amount. This
is what makes a rehabilitation robot safe to interact with, and it is why measuring motor current
matters.

### Words about signals and buses

**Bus** — A shared set of wires several devices connect to. I²C, SPI and CAN are buses. UART — plain
serial — is a point-to-point link between exactly two devices, not a bus.

**UART / serial** — The simplest digital link: two wires, one talking each way. This is what "serial
monitor" means. Your main window into Stage 0.

**I²C** — Two wires, many devices, each with an address. Slow but simple, and the standard way small
sensors attach. Your AS5600 angle sensor and INA219 current sensor both use it.

**SPI** — Four wires, faster than I²C, one extra wire per device to select it.

**CAN (Controller Area Network)** — The industrial bus this project is built on, the same one inside
every car. Two twisted wires carry everything. Devices do not have addresses; **messages have
identifiers**, and each device decides which identifiers it cares about. Lower identifier numbers
automatically win when two devices transmit at the same instant, so priority is built into the
addressing scheme itself. That is why the emergency stop gets the lowest identifier on the bus — in
Stage 1's scheme, `0x010` — so it beats every other message on a busy bus.

> **WATCH OUT** — **The message *type* and the *identifier* are not the same number**, and the two get
> confused constantly. Stage 1 packs a 7-bit type and a 4-bit node into the 11-bit identifier as
> `(type << 4) | node`, so the e-stop's type of `0x01` becomes an identifier of **`0x010`** — 16 —
> against 0x100 for a command and 0x300 for diagnostics. A literal identifier of `0x01` would decode
> as type 0, node 1, which the scheme never issues. The number you filter on in hardware is the
> identifier. Node ids run 1–15; **node 0 is reserved to mean broadcast**, which is what the e-stop
> uses.

**Frame** — One CAN message. A standard frame carries an identifier plus at most eight bytes of data.
That constraint is severe and it is a gift: it forces you to decide what actually matters.

**Arbitration** — What happens when two devices transmit simultaneously. Rather than colliding, the
lower identifier wins and the higher backs off and retries.

**Recessive and dominant** — The two states of a CAN wire pair. **Recessive** is the idle state, both
lines pulled to about 2.5 V, and it is what a logical 1 looks like. **Dominant** drives the lines
apart and is a logical 0, and it *overrides* recessive — any node transmitting dominant wins over any
node transmitting recessive on the same bit. That asymmetry is the entire mechanism of arbitration:
the lower identifier has more dominant bits earlier, so it survives.

**Bus-off** — The state a CAN node puts itself into after producing too many transmit errors. It stops
transmitting entirely and has to be reset before it will talk again. It is correct behaviour rather
than a fault — a node that is producing garbage removes itself so it cannot take the whole bus down —
and the symptom you observe is a node that was working and has gone silent on its own.

**SJW (synchronisation jump width)** — One of the four CAN bit-timing numbers, alongside the
prescaler and the two bit segments. It is how many time quanta a receiver may shift its sample point
by, per bit, to stay locked to a transmitter whose clock is slightly different from its own. One
quantum is almost always enough; it exists because no two crystals agree exactly.

**Transceiver** — The chip converting your microcontroller's ordinary logic voltages into the two-wire
differential signalling CAN actually uses. One per node.

**PCNT and TWAI** — Two ESP32 peripherals named in the board decision, and the whole reason the
ESP32-S3s have a job at all. **PCNT** is the *pulse counter*, which decodes quadrature in hardware the
way an STM32 timer in encoder mode does. **TWAI** — *two-wire automotive interface* — is Espressif's
name for its CAN controller, renamed for trademark reasons; it is CAN, and it interoperates with
everything else on the bus.

**Shield, and why you ground it at one end only** — A shielded cable wraps its conductors in a
conductive braid or foil. Grounded, that shield intercepts electric fields that would otherwise couple
into the signal inside it. **Ground it at one end and it works; ground it at both and it can make
things worse** — because two "grounds" a metre apart are never at exactly the same potential, so a
shield connected at both ends becomes a conductor joining them, and current flows along it. That is a
**ground loop**, the shield is now carrying current rather than only intercepting fields, and the
magnetic field of that current couples straight into the very wires it was supposed to protect. One
end, always the receiver-or-controller end, and leave the far end floating and insulated.

**Differential signalling** — Sending a signal as the difference between two wires rather than one
wire against ground. Noise hits both wires roughly equally, so subtracting cancels it. This is why CAN
survives next to a motor and plain wires do not.

**Termination** — A 120 Ω resistor at each of the **two physical ends** of a CAN bus, and nowhere
else. Without them signals bounce off the ends and corrupt the next bit. With one on every node the
bus is over-loaded and nothing works. Power off, meter across the bus: **you should read about 60 Ω.**

**PWM (Pulse Width Modulation)** — A pin can only be fully on or fully off. PWM switches it fast enough
that the average is anything in between. **Duty cycle** is the fraction of each period spent on.

**Encoder, quadrature, PPR, CPR** — An encoder reports shaft rotation. Yours produces two square waves
ninety degrees out of phase — **quadrature** — and which one leads tells you direction. **PPR** is
*pulses per revolution, per channel* — the raw thing the sensor emits. **CPR** is *counts per
revolution* — what your software ends up with after decoding. They are not the same number and
confusing them is a factor-of-four error: your motor is 7 PPR per channel and, with ×4 decoding,
28 CPR at the motor shaft. Decoding all four transitions per cycle is **×4 decoding** and gives four
times the resolution for free.

> **WATCH OUT** — When a datasheet says "counts per revolution" it usually will not tell you which
> decoding mode it assumes, and that is the single commonest way an encoder reads exactly four times
> too high or too low. Assume nothing; Stage 0 has you measure it.

**Pull-up and pull-down resistor** — A resistor tying a signal line to VCC (pull-up) or to ground
(pull-down), so the line has a defined level when nothing is actively driving it. Without one a
floating input reads as noise — it will happily report both 0 and 1 while you watch. Three places this
matters in Mimic: a switch wired to ground needs a pull-up so the pin reads HIGH when the switch is
open, which is what `INPUT_PULLUP` enables inside the AVR; I²C needs pull-ups on both lines because
every device only ever pulls them *down*; and Stage 1's node-ID jumpers use the STM32's internal
pull-ups, which is why "no jumpers fitted" reads as all-ones rather than all-zeros.

**Debounce** — A mechanical switch does not close once; it bounces, making and breaking several times
over a few milliseconds. Debouncing is ignoring everything after the first transition until the bounce
window has passed. Stage 2 S2.12 makes you cost this in degrees of overshoot rather than treating it as
a nuisance.

**The fields of a CAN frame** — Worth having in one place, because Stage 1 has you redraw them from
the widths and the acronyms are opaque. **SOF** *start of frame*, one dominant bit that wakes
everybody up. **Identifier**, 11 bits, which is both the message's name and its priority. **RTR**
*remote transmission request* — 0 for a normal data frame, 1 for the rarely-used "please send me that
message" frame. **IDE** *identifier extension* — 0 for the 11-bit standard format you are using, 1 for
the 29-bit extended format. **r0**, a reserved bit, always dominant, kept for a future the standard
never used. **DLC** *data length code*, 4 bits saying how many payload bytes follow, 0 to 8. **CRC**,
15 bits of checksum, then a recessive delimiter. **ACK slot**, which the *transmitter* sends recessive
and any *receiver* that liked the frame overwrites dominant — which is why a single node talking to
itself never succeeds. **EOF** *end of frame*, 7 recessive bits. **IFS** *interframe space*, 3 more,
before anyone may start again.

**socketCAN** — The Linux kernel's CAN networking stack. It makes a CAN bus look like an ordinary
network interface, so `ip link` configures it and `candump`/`cansend` read and write it exactly the way
you would use `tcpdump` on Ethernet. It is a *kernel* feature, which is the entire reason native Linux
stops being optional in this project: a stock WSL2 kernel is not built with it, so the tools do not
merely misbehave — they have nothing to attach to.

**ISR (interrupt service routine)** — The small handler function an interrupt runs. "Keep the ISR
short" is the most repeated advice in embedded work, because your main program is stopped while it
executes. On the UNO that is literally everything; on the STM32 in Stage 1 a higher-priority
interrupt can still get in, which is a feature you will use deliberately rather than an exception to
the rule.

**Sampling, Nyquist, and aliasing** — Every digital measurement in this project is a *sample*: a
snapshot at one instant, with nothing recorded between snapshots. **Nyquist's rule** is the floor —
to represent a signal containing frequencies up to *f*, you must sample faster than **2 f**. Below
that, high frequencies do not merely get lost; they come back **disguised as low ones**, which is
**aliasing**, and it is the dangerous failure because the result looks like data. A wheel that appears
to spin backwards in a film is the everyday version.

Two is a floor, not a target. To *reconstruct* a waveform you want 2×; to **read the shape of a digital
edge on an analyzer** you want ten or more samples per period; and to run a **control loop** you want
the loop rate roughly ten to twenty times faster than the fastest thing the plant does, which is the
rule the Project Guide's Interlude B states. Three different jobs, three different multiples, one
underlying idea.

It bites in three specific places here. Your **logic analyzer** samples at up to 24 MHz, and choosing
the rate is a decision rather than a default. Your **derivative term** is a difference of two samples,
so it is a discrete approximation of a derivative and it inherits every sampling limitation — including
that it amplifies exactly the high-frequency noise Nyquist is about. And your **EMG chain** band-passes
to 450 Hz and samples at 1 kHz, which is only 1.11× above the Nyquist minimum of 900 Hz — adequate only
because an analogue filter has already removed what is above it, which is precisely what an
anti-aliasing filter is for.

**Deadband** — The range of small commands that produce no motion at all, because static friction
has not been overcome yet. Every geared motor has one. It is why a proportional controller stops a
degree or two short, and measuring it in Stage 0 S4 turns that from a mystery into a prediction.

**Trim pot (trimmer potentiometer)** — A small screw-adjusted resistor on a board, used to set
something once and leave it. Your buck converters set their output voltage with one, often
multi-turn — fifteen full rotations end to end — which is why a ~2 mm precision screwdriver, rather
than any driver in a general tool roll, is what session S2 actually needs. **Verify first** — no
precision driver appears anywhere in the *Order Manifest*, so do not assume you own one. C$5–8 if you
do not, and it is listed in Tier B of *What's Left to Buy*.

**Star ground** — A wiring topology where every return path meets at one single physical point rather
than daisy-chaining board to board. Wire has resistance, so if motor return current shares a length
of wire with your encoder's ground, the motor shifts your encoder's idea of what 0 V means. That is
not noise you can filter; it is a topology error.

**Bulk capacitance** — A large capacitor placed near a load to supply sudden current locally, so the
surge does not travel back up the wire and drag the whole rail down. The 1000 µF across your motor
driver is this.

**Torn read** — Reading a multi-byte variable on an 8-bit chip and being interrupted halfway, so you
get some old bytes and some new ones. A `long` on an AVR is four bytes and four chances. The fix is
to disable interrupts around the copy.

**Prescaler** — A divider between a clock source and a timer. Changing it changes how fast the timer
counts, and therefore PWM frequency. On the UNO it is one register write; on the STM32 it is a field
in CubeMX. Same idea, both times.

**Backdrivable** — Whether you can turn the output shaft by hand and have the motor turn with it.
High gear ratios are barely backdrivable: the gearbox multiplies the motor's friction and inertia as
seen from the output, so most of the force you apply at the shaft is spent fighting the gearbox
rather than turning the motor. It matters enormously in Stage 5, because you cannot make a joint feel
compliant if it physically resists being moved.

**Heat-set insert** — A small brass sleeve melted into 3D-printed plastic with a soldering iron, so
a screw threads into metal rather than into plastic. Screwing directly into printed plastic strips
on the second or third assembly, and you will assemble more than twice.

**ADR (Architecture Decision Record)** — A short file recording a decision that had real
alternatives: **Context, Decision, Alternatives Considered, Consequences**, four sentences each.
Kept in `docs/decisions/`. This is the single highest-leverage documentation habit in the project,
because these are precisely what an interview probes — and a note written the day you decided is
evidence, where a recollection eight months later is a guess.

**Absolute versus incremental** — An incremental encoder counts changes and knows nothing at power-up,
which is why homing exists. An absolute encoder like the AS5600 reports the actual angle immediately.

**Interrupt** — A hardware event that stops your program mid-line, runs a small handler, and returns.
Essential for encoders, and dangerous if the handler does too much.

**Polling** — Repeatedly checking something rather than being interrupted by it. Simpler, and wastes
time.

**ADC** — Analogue-to-digital converter. Turns a voltage into a number. How you read a potentiometer,
a current sensor, or an EMG signal.

**Datasheet, reference manual, user manual, errata** — Four different manufacturer documents that
people call "the datasheet" interchangeably, which is why the fact you want always seems to be missing.
The **datasheet** says what a part *is* — pinout, package, absolute maximums, electrical
characteristics. The **reference manual** says how to *program* it, register by register, and exists
only for complex parts. The **user manual** covers a *board* rather than a chip — which pin goes to
which header. The **errata sheet** lists the ways the silicon does not match its own datasheet, and is
where an impossible bug is occasionally explained. Part V of this document, "The skill nobody teaches:
reading a datasheet", covers which one holds what, how to find them, and the three kinds of number
inside them — **absolute maximum, recommended operating, and typical** — which mean completely
different things and which it is expensive to confuse.

Reading one without panic is a listed skill for a reason, and every manufacturer figure quoted anywhere
in this document set is one you can go and verify yourself.

> **WATCH OUT** — **Your motor has no datasheet.** The 12GA-N20 you bought ships without one, and vendor
> listings disagree about the gear ratio. This is not a problem to work around; it is the first real
> experiment in the project. Stage 0 Workbook session S1 has you derive the expected counts per
> revolution and then measure it. Your measured number goes in the code — nobody else's.

---

### Words about forces and mechanisms

**Moment arm** — The *perpendicular* distance from a pivot to the line along which a force acts.
Torque is force times moment arm, and "perpendicular" is the word that does the work: hold the arm
straight up and every weight still pulls downward, but the perpendicular distance from the shoulder
axis is zero, so the torque is zero. That is exactly why horizontal is the worst case in Stage 2's
torque budget.

**Free-body diagram** — The thing you are analysing, drawn in isolation with every force acting on it
marked as an arrow, and nothing else on the page. Isolating it is the entire point: it is what stops
you double-counting a force or silently forgetting one.

**Centre of gravity** — The single point at which a body's whole weight can be treated as acting. For
a uniform link that is its midpoint, which is why a 180 mm link's mass sits at 90 mm in the budget
rather than at the far end.

**kg·cm, and kgf** — The unit almost every hobby motor and servo listing quotes torque in, and it is
not an SI unit. A **kgf** (kilogram-force) is the force gravity exerts on one kilogram — 9.81 N — so
**kg·cm** is that force acting at one centimetre: `1 kg·cm = 0.01 m × 9.81 N = 0.0981 N·m`. To convert,
divide by about 10.2, or multiply by 0.0981. Every torque figure in Stage 2 gets converted to N·m
before it is compared to anything, because the requirement side of that comparison is in N·m and
mixing the two is the same class of error as mixing degrees and radians. Note also that a bare "kg" on
a spec table is *not* a torque at all — it is usually a load or a mass, and reading one as the other
is a real trap.

**Static, rated and stall torque** — Three different numbers that vendors mix freely, and keeping them
apart is what makes Stage 2's arithmetic honest. **Stall torque** is what a motor produces at zero
speed with full voltage applied — the biggest number on any listing, and a destructive operating
point rather than a design figure. **Rated torque** (sometimes *continuous* or *nominal*) is what it
can produce indefinitely without overheating, typically a quarter to a third of stall. **Static
torque** is what a joint must produce merely to hold a pose against gravity — a demand, not a
capability. A listing quoting one figure without saying which almost always means stall.

**Rotational inertia, and τ = I·α** — The rotational twin of `F = ma`. **Rotational inertia** `I`
(also *moment of inertia*, in kg·m²) is how hard a body is to spin up about an axis; for point masses
it is `Σ m·r²`. Torque equals `I` times **angular acceleration** `α`. The r is **squared**, which is
why mass out at the tip of an arm is expensive twice over — once in the static torque sum, where it
scales with r, and much harder here. Static torque tells you what it takes to *hold* an arm; this tells
you what it takes to *move* it, and a torque budget with only the first half is incomplete.

**Second moment of area, and why a beam's shape matters more than its size** — Written `I` as well,
confusingly, and in m⁴ rather than kg·m². It measures how a cross-section's material is distributed
about the axis it bends around, and it is what decides stiffness: a cantilever's tip deflection is
`δ = F·L³ / (3·E·I)`. For a rectangle `I = b·h³/12`, where **h is the dimension in the direction of
bending** — and it is cubed. Rotate a flat bar ninety degrees and you change nothing about its mass,
its material or its cost, and change its stiffness by a factor of tens. `E` is **Young's modulus**, the
stiffness of the *material* (about 3.5 GPa for PETG-CF); `I` is the stiffness of the *shape*, and it is
the one you control in CAD.

**Counterbalance** — A spring or a weight arranged to cancel some of the torque gravity imposes.
Cheap and effective, with the catch that it cancels correctly at one pose and progressively less well
as you move away from it.

**Belt reduction, and GT2** — A toothed belt between a small pulley on the motor and a large one on
the joint, trading speed for torque in the ratio of their tooth counts. **GT2** names the tooth
profile — 2 mm pitch, curved teeth designed not to slip — and it is the 3D-printer standard, hence
cheap and available. A single stage tops out around 4:1 or 5:1, limited by the *small* pulley: below
about sixteen teeth, too few are engaged at once and the belt skips under load.

**Safety factor, and derating** — A **safety factor** is how many times more capability you have
than you need: 1.33× means the thing can just about do it, and a friction grasp is normally designed to
2–4×. **Derating** is the opposite move, done to the supply side: taking a manufacturer's headline
number and deliberately using a fraction of it, because the headline is a limit rather than an
operating point. Both are choices, not standards — so whenever you use one, **say which number you
picked and why**, because "25 % of stall" and "30 % of stall" are conventions someone made up and an
interviewer is entitled to ask where they came from. Stage 2 makes this argument twice, once for a
motor and once for a servo, and in both places the honest move is to pick the margin you want first and
let the derate fall out of it.

**Threadlocker** — A liquid adhesive put on a screw thread so vibration cannot back the fastener out.
Blue is medium-strength and comes apart with hand tools, which is the one you want; red is effectively
permanent without heat. A two-DOF arm vibrates more than you expect, and a fastener working loose
mid-motion is both a failure and a hazard.

**Backlash** — The free play in a gear train: the small angle you can rotate the output before the
input starts to move. It is what makes a joint feel loose at reversal, it is invisible to an encoder
mounted on the motor side, and it is why an encoder on the *joint* tells you something the motor's
own encoder cannot.

**Revolute, prismatic, fixed, continuous** — The joint types you will describe in URDF. A **revolute**
joint rotates about an axis between limits; a **continuous** joint is the same with no limits; a
**prismatic** joint slides along an axis; a **fixed** joint does not move at all and exists to attach
one frame rigidly to another. All of these describe the *motion*, not the mechanism — a parallel-jaw
gripper is usually prismatic even though a servo rotates to drive it.

**Workspace, and annulus** — The workspace is the set of points the end effector can reach. For a
planar two-link arm it is an **annulus** — the region between two concentric circles, a disc with a
smaller disc removed from the middle. The outer radius is the sum of the link lengths; the inner
radius is set by whichever is larger, the difference between the link lengths or the limit you impose
on the elbow angle.

**Jacobian** — The matrix of partial derivatives of the forward kinematics: the best linear
approximation, at the pose you are currently in, to the map from joint angles to tip position. One
equation defines it, `ẋ = J·θ̇` — tip velocity equals `J` times joint velocity — and it does three
jobs. Forwards it converts joint rates into tip motion. Inverted it answers "what joint rates give me
the tip motion I want." Transposed it maps the other way, `τ = Jᵀ·F`, turning a desired force at the
fingertips into joint torques, which is how Stage 5 works.

**Singularity** — A configuration where the Jacobian cannot be inverted, meaning some direction of tip
motion would require infinite joint velocity. For a two-link arm those are full extension and full
fold, and the practical response is to design them out of the workspace with joint limits rather than
to discover them when the arm lunges.

---

### Words about C and C++ on a small chip

**Bare metal** — Code running directly on the processor with no operating system underneath it: no
scheduler, no memory protection, nothing to catch you. Everything in Stage 0 is bare metal; Stage 1
is the point at which you can see the edges of it.

**Vector table** — An array of addresses at the very start of flash. The processor reads entry zero to
find its initial stack pointer, entry one to find the reset handler, and one entry per interrupt
source after that. It is the literal answer to "how does the chip know to run my code."

**Linker script** — The file (`.ld`) deciding where everything lands in the address space: where flash
starts, where RAM starts, which direction the stack grows, where the vector table sits. Arduino had
one; it simply never showed it to you.

**`volatile`** — A keyword telling the compiler a variable can change by means it cannot see — an
interrupt, usually — so it must not cache the value in a register or optimise the read away. What it
does **not** give you is atomicity: it guarantees the read happens, not that it happens all at once.
That second problem is the torn read, and its fix is disabling interrupts, not `volatile`. You
generally need both, for two different reasons.

**Translation unit** — One `.cpp` file plus everything it includes, compiled as a single lump. A
header is pasted into every unit that includes it, which is why a header containing a plain
definition causes duplicate-symbol errors at link time, and why `constexpr` and `inline` are safe
there when a bare global variable is not.

**`constexpr` versus `#define`** — `#define` is textual substitution performed before the compiler
sees your code: no type, no scope, and error messages that point at the expansion rather than at your
mistake. `constexpr` is a real typed constant evaluated at compile time — the same zero runtime cost,
with the type system involved. It also lets the derivation stay in the source, so one measured number
can feed every constant downstream of it.

**Function pointer versus member function** — A non-static member function needs to know *which
object* it acts on, and that hidden `this` argument has nowhere to live in a plain `void(*)()`. So
the signatures genuinely do not match and no cast makes it safe. The standard workaround is a
file-scope pointer to the single instance plus a free function that supplies `this` explicitly. You
meet this anywhere C callbacks meet C++ objects, which in this project is `attachInterrupt` and the
STM32 HAL.

**RAII** — *Resource acquisition is initialisation*: a small object whose constructor takes something
and whose destructor gives it back. The value is that the destructor runs on **every** exit path,
including an early `return` or a thrown exception, which a hand-written cleanup line at the bottom of
a function does not. Wrapping `noInterrupts()` / `interrupts()` in one is four lines and the same
idea as a lock guard in any language you already know.

---

### Words about tasks and time

**RTOS** — A real-time operating system: a small scheduler that lets several tasks share one
processor with predictable timing. The thing it buys you over a superloop is **pre-emption** — a
high-priority task interrupting a low-priority one mid-execution, so the slowest thing in the program
no longer sets the pace for everything.

**Task** — One independent thread of execution with its own stack and its own priority. Every task
must contain a blocking call somewhere in its loop; one that spins instead starves everything below
it, and that is the scheduler working correctly rather than failing.

**Context switch** — The scheduler saving one task's registers and stack pointer, loading another's,
and jumping into it. It can happen between any two machine instructions — which includes the middle
of a C statement, and is the entire source of the shared-data problem below.

**Mutex** — *Mutual exclusion*: a lock protecting a resource. It has an owner, only the owner may
release it, and a good kernel will temporarily raise that owner's priority so a waiting high-priority
task is not held up. That last property is **priority inheritance** and it is the reason a mutex is
not interchangeable with a semaphore.

**Semaphore** — A counter used for signalling — "an event happened," or "three buffers are free." It
has no owner, so anyone may give it. Using a binary semaphore where you meant a mutex compiles, runs,
looks correct, and silently discards priority inheritance.

**Queue** — A kernel-owned buffer that **copies** data from a producer to a consumer. Because nothing
is shared, there is nothing to exclude anyone from, and a send with a zero timeout cannot block —
which is what makes it the usual right answer for getting state out of a control task.

**Priority inversion** — A high-priority task waits on a resource held by a low-priority task, which
is itself pre-empted by a medium-priority one, so the high-priority task effectively runs at the
medium priority. The classic RTOS failure, famous for delaying the Mars Pathfinder mission, and the
standard mitigation is priority inheritance on mutexes.

**Stack high-water mark** — The deepest a task's stack has ever been used. Reading it lets you size
stacks from evidence rather than by guessing, which matters because an overflow does not announce
itself — it quietly corrupts whatever is next in memory.

---

### Words about power and analogue electronics

**H-bridge** — Four switches arranged around a load in the shape of the letter H, with the motor as
the crossbar. Close one diagonal pair and current runs one way through the motor; close the other and
it runs the other way. That is the only way to reverse a brushed DC motor from a single-polarity
supply, and the TB6612FNG *is* two of them. It also explains `brake` (both switches on one side
closed, so the motor's terminals are shorted and its own back-EMF opposes motion) and `coast` (all
four open). Closing both switches on the same *leg* is **shoot-through**, a dead short across the
supply, and preventing it is what the chip's internal logic is for.

**Decoupling capacitor** *(also: bypass capacitor)* — A small capacitor placed as physically close as
possible to a noise source or a noise-sensitive part, giving high-frequency current a short local
loop instead of a long one through the power wiring. *Close* is the entire specification: a
decoupling capacitor ten centimetres away has been decoupled from the thing it was meant to decouple.
The 100 nF soldered at your motor's terminals is decoupling a source; a 100 nF next to the
microcontroller decouples a victim.

**Back-EMF** — The voltage a spinning motor generates all by itself, opposing the voltage you applied.
A motor is a generator running backwards: turn the shaft and the windings moving through the magnetic
field produce a voltage proportional to speed. That is why current falls as a motor speeds up (the
back-EMF cancels most of the supply), why a stalled motor draws the most current of all (zero speed,
zero back-EMF, only the winding resistance limits it), and why shorting a motor's terminals *brakes*
it — the back-EMF now drives a current that opposes the motion. The constant relating speed to that
voltage is **Ke**, and measuring it is the easy way to get **Kt**, the torque constant, because for a
brushed motor the two are numerically equal in SI units.

**Smoke stopper** *(also: smoke arrestor, current-limited first-power-up jig)* — A cheap device placed
in series with a supply the first time you power something new, which limits the current to a few
hundred milliamps so a wiring mistake browns out instead of releasing the magic smoke. You do not own
one, which is why Stage 0 S2 has you use the XL4015's current-limit pot for the same job — turned
fully down before anything is connected, then raised deliberately.

**Brownout** — A supply voltage sagging below the minimum a chip needs to work correctly, without
falling to zero. Most microcontrollers deliberately hold themselves in reset while this is true,
because a processor running on marginal voltage does not fail cleanly — it computes wrong answers. So
the reset you observe is the protection working, and the word matters because "brownout" and "crash"
point you at completely different parts of the bench.

**Dropout, and LDO** — A linear regulator burns off the difference between its input and output as
heat, so it needs the input to stay some minimum above the output. That minimum is its **dropout
voltage**. An **LDO** is a *low-dropout* regulator, needing only a few hundred millivolts rather than
a couple of volts. A switching regulator such as a buck converter does not have this constraint at
all, which is why one is in your power tree.

**Galvanic isolation** — Two circuits that exchange information but share **no conductive path** —
no wire, no shared ground, no return through a supply. Signals cross by a mechanism that does not
conduct: a transformer's magnetic field, an optocoupler's light, or a tiny on-chip capacitor or
transformer, which is what the ADuM3160 uses. The point is that a fault on one side cannot push current
through the other, and the rating (2.5 kV for that part) is how much voltage the barrier withstands
before it stops being one.

This is the safety concept the whole of Stage 4 rests on, so be precise about what breaks it: **any**
conductive path across the barrier defeats it completely, including a "just for now" ground wire, a
shared USB shield, or powering both sides of the isolator from the same battery because the far side is
not lighting up. Isolation is not a property you have more or less of; you either have no path or you
have a path.

**Ground loop** — What you get when two points both called "ground" are joined by more than one path,
so current can circulate around the loop they enclose. The two ends then sit at slightly different
potentials, and every signal referenced to one of them is measured against the wrong zero. A star
topology has exactly one path to each return, which is why it does not have this problem.

---

### Words about the chip's clocks and interrupts

**HSE and HSI** — The *high-speed external* and *high-speed internal* oscillators. HSE is the
reference the chip trusts; on a Nucleo it is not a crystal on your board at all but a square wave the
on-board debugger generates and feeds across. HSI is an internal RC oscillator — always present,
always slightly wrong, around ±1 %, which is fine for blinking and not fine for CAN.

**PLL** — *Phase-locked loop*, used here as a frequency multiplier: it divides the reference down to a
low frequency, multiplies that up to a high internal one, and divides the result back down to what
you asked for. The three dividers are usually called M, N and P, and each has a legal range you must
respect rather than a value you may pick freely.

**AHB, APB1, APB2** — The internal buses. AHB is the fast one the core and memory sit on; APB1 and
APB2 are slower peripheral buses hanging off it, each with its own divider and its own hard maximum
frequency. The trap worth knowing in advance: when an APB divider is greater than one, timers on that
bus are clocked at **twice** the bus frequency.

**ARR, and the N−1 rule** — **ARR** is a timer's *auto-reload register*: the value the counter
counts up to before it resets. It sets the period, so PWM frequency is the timer's clock divided by
`ARR + 1`. The `+ 1` is the whole trap, and it generalises: **when a hardware field configures a
divider or a count, expect the register to hold one less than the number you mean**, because a field
of zero has to be able to mean "divide by one". You meet the same rule again in the CAN bit-timing
fields, where the value you type into the tool and the value in the register differ by exactly one.

**SysTick** — A small 24-bit countdown timer built into every Cortex-M core, intended as the operating
system's heartbeat. It matters in Stage 1 for one reason: ST's HAL uses it to drive `HAL_Delay`, and
FreeRTOS wants it for the scheduler. They cannot both own it, which is why S1.5 moves the HAL's
timebase onto a spare timer.

**DMA** — *Direct memory access*: a block that moves data between a peripheral and memory without the
processor being involved. Not used in Mimic, but it appears on every embedded job posting and it is the
standard answer to "how do I stream an ADC at 100 kHz without spending all my CPU on interrupts."

**JTAG and SWD** — Two debug interfaces. **JTAG** is the older, five-pin standard; **SWD** *serial wire
debug* is ARM's two-pin replacement and does everything you need. The distinction has one practical
consequence in this project: several pins are shared with JTAG and are only yours as ordinary GPIO when
the debug interface is set to SWD, which is why Stage 1's pin map insists on *Serial Wire* and warns
that PB4 is `NJTRST`.

**NVIC** — The *nested vectored interrupt controller*, which decides which interrupt runs and when.
It is **vectored**, so each source has its own vector-table entry and there is no dispatch code to
write; **prioritised**, with the confusing convention that lower numbers mean higher priority; and
**nested**, so a higher-priority interrupt can pre-empt one already running. That last point is the
real change from an 8-bit AVR, where entering an interrupt disabled interrupts globally and every
handler was therefore automatically atomic with respect to every other.

---

### Words about ROS 2

**Topic, service, action** — The three ways ROS 2 nodes talk. A **topic** is a named stream that
anyone may publish to and anyone may subscribe to, with no reply — sensor data and joint states. A
**service** is a request and a single response, for quick queries. An **action** is a long-running
request with progress feedback and the ability to cancel — which is what moving an arm is, and why
trajectories are actions rather than services.

**Message type** — The schema of what travels on a topic. Publishers and subscribers must agree on it
exactly; a mismatch means they simply do not connect.

**DDS** — The middleware underneath ROS 2 that handles discovery and delivery. Nodes find each other
over the network with no central master, which is a genuine improvement and also the reason a network
boundary — such as the one around WSL — breaks discovery in ways that look like your code failing.

**QoS (quality of service)** — Per-publisher and per-subscriber settings governing delivery:
*reliability* (retry until delivered, or fire and forget), *durability* (does a late subscriber get
the last message or only new ones), and history depth. This matters because **incompatible QoS
profiles do not connect** — no error, no warning, just a topic with a publisher and a subscriber and
no messages passing between them.

**Workspace, overlay, and `source install/setup.bash`** — A workspace is a directory with a `src/`
folder of packages, which `colcon build` turns into `build/`, `install/` and `log/`. Sourcing
`install/setup.bash` prepends that workspace to the environment ROS 2 searches, so your version of a
package **overlays** the system one. Two consequences bite everyone once: a new terminal knows
nothing until you source it, and sourcing a workspace whose build is stale runs old code under a new
name, which is far more confusing than an outright build error.

**Launch file** — A script, usually Python, that starts a set of nodes with their parameters,
remappings and conditions, so bringing up a robot is one command instead of six terminals. It is
ordinary code, which is both its strength and the reason launch files quietly become the least
readable part of a project.

**tf2** — The transform library. Nodes publish the relationships between coordinate frames, and tf2
lets any node ask "where is this point, expressed in that frame," at a given time. It is the
bookkeeping that keeps a camera's view and an arm's geometry in the same world.

**URDF, and xacro** — **URDF** is the XML description of a robot as a tree of links joined by joints,
with axes, limits, visual geometry, collision geometry and inertias. Nearly everything in the
manipulation stack reads it, so an error here is an error everywhere at once. **xacro** is a macro
preprocessor adding constants, arithmetic and reusable macros, expanding to plain URDF before anything
else sees it — use it from the first line, so that changing a link length is one edit rather than
eleven.

**SDF** — Gazebo's own description format. It describes worlds as well as robots: lights, physics,
ground planes, sensors. Gazebo converts your URDF to SDF when it spawns it, which is why URDF stays
the single source of truth. What you add to the URDF are `<gazebo>` tags — blocks meaning nothing to
the visualiser and passed through to the simulator.

**ros2_control, and its four words** — The framework standardising how controllers talk to hardware. A
**state interface** is one named readable number coming up from the hardware; a **command interface**
is one named writable number going down. The **controller manager** owns the update loop, calling the
hardware plugin's `read()`, then each active controller's `update()`, then `write()`, at a fixed
rate. A **controller** is a plugin that claims some command interfaces, reads some state interfaces,
and turns a goal into numbers. Nothing in the framework knows what a robot is — it moves named
doubles across a seam at a fixed rate, and all of its usefulness comes from that being all it does.

**pluginlib** — The ROS 2 library that loads C++ classes by *name*, at run time, out of shared
objects. It is how `ros2_control` swaps a mock hardware interface for a Gazebo one for your real one
by changing a single string in the URDF, and how a controller type in a YAML file becomes a running
object. Two consequences worth knowing before you meet them: the string is
`package_name/ClassName`, and it is case-sensitive; and a plugin that fails to load produces an error
about *the export XML*, not about your C++.

**Lifecycle node** — A ROS 2 node with a defined state machine — *unconfigured*, *inactive*, *active*,
*finalized* — and a callback for each transition: `on_configure`, `on_activate`, `on_deactivate`,
`on_cleanup`, `on_shutdown`, `on_error`. The point is that "allocate your resources" and "start
producing output" become two separate, externally-triggered moments, so a system can be brought up in
a controlled order rather than everything racing at launch. Both `ros2_control` hardware components
and its controllers are lifecycle objects, which is why Stage 2 S2.11 has you implement six methods
that look like ceremony and are not.

**SRDF** — The *semantic* robot description format, MoveIt's companion to the URDF. The URDF says
what the robot physically is; the SRDF says what the parts of it *mean* to a planner — which joints
form a "planning group" you can command as a unit, which named poses exist ("home", "ready"), and which
pairs of links can never collide and may therefore be skipped in collision checking. The Setup
Assistant generates it, and the reason to know the word is that when MoveIt refuses a reachable target,
the joint limits it is refusing on may be in either file.

**MoveIt 2** — The motion planning stack. You give it a target pose; it produces a collision-free,
time-parameterised trajectory and hands it to a controller as an action.

**rosbag** — Recording of topics to a file, replayable later. The ROS 2 equivalent of the CSV pipeline
you build in Stage 0, with the difference that it captures everything rather than the fields you
thought to log.

**micro-ROS** — A ROS 2 client library small enough to run on a microcontroller, so a joint can be a
ROS 2 node itself rather than sitting behind a bridge. Appropriate for learning and prototyping; it
is not developed to any safety or medical standard, and keeping that distinction crisp matters.

---

### Words about printing and materials

**PETG, PETG-CF, PA6-CF, TPU** — **PETG** is the general-purpose engineering choice: tougher and more
heat-tolerant than PLA, far easier to print than ABS, and it does not creep under sustained load the
way PLA does — which matters for a bracket holding a motor for months. **PETG-CF** and **PA6-CF** are
the same base polymers with chopped carbon fibre mixed in: much stiffer and more dimensionally
stable, and abrasive. PA6-CF is nylon, stronger still, and it absorbs water from the air so
aggressively that it must be dried before printing. **TPU** is rubber — flexible and high-friction,
which is why gripper pads are specified in it.

**Hardened nozzle** — A nozzle in steel or a coated alloy rather than brass. Carbon-filled filaments
saw through a brass nozzle within a few hundred grams, so this is a requirement rather than an
upgrade if you intend to print CF materials at all.

**CoreXY** — A printer motion layout in which two fixed motors drive one long belt path, and the
print head moves in X and Y as the *sum and difference* of the two motors' rotations. Nothing heavy
moves except the head itself, which is why CoreXY machines can be fast and accurate at once, and why
they enclose easily — the enclosure is what makes engineering filaments printable. It is the layout
named in the C$420 printer line, and it is the reason that line is not "any printer will do."

**Overhang** — Printed material with nothing underneath it. A printer lays each layer on the one
below, so a surface leaning more than roughly 45° from vertical has less and less to sit on and starts
to droop or fail. You either design them out — which is what "avoid overhangs" means — or add support
material and accept a rough surface and cleanup work. It is the main reason a part that looks fine in
CAD prints badly, and it is a design decision rather than a slicer setting.

**Infill** — The percentage of internal lattice inside a printed part. Worth knowing that for a part
loaded in bending, **wall count matters far more than infill**, because bending stress lives at the
surface.

**Layer lines, and print orientation** — Layer lines are the boundaries between printed layers, and
they are the weak plane: parts break *along* them. Orientation is therefore a structural decision,
not a convenience — orient a link so the load runs along the layers rather than across them.

**Tolerance and clearance fit** — The deliberate gap left between two parts that must assemble.
Printers over-extrude slightly, so a hole modelled at exactly 5 mm comes out under 5 mm. Print a
tolerance test block once, measure what your machine actually does, and reuse that number everywhere.

---

### Words about cameras, muscles and force

**Intrinsic matrix, and distortion coefficients** — The intrinsic matrix describes the camera itself —
focal lengths and optical centre, in pixels — and does not change when the camera moves. The
distortion coefficients describe how the lens bends straight lines. Both are properties of the camera
alone, which is why calibration is a one-time job.

**Extrinsics** — The rotation and translation describing where a camera *is* relative to some other
frame. They change the moment anything moves. Keeping this word apart from *intrinsics* is worth the
effort: an intrinsics problem is a lens problem and shows up as curvature, while an extrinsics
problem is geometry and shows up as a consistent offset in one direction.

**Fiducial, and ArUco** — A **fiducial** is a marker deliberately placed in a scene to be easy to
detect and locate. **ArUco** is a specific family of square black-and-white fiducials with built-in
identifiers, widely supported, and enough to recover a full six-degree-of-freedom pose from a single
calibrated image.

**Reprojection error** — The standard scoreboard for a camera calibration. Take the 3D points you
know, push them back through the calibration you just computed, and measure how far the predicted
pixel lands from the pixel you actually detected. It is reported in pixels, averaged over every
image, and **under about 0.5 px is good** for a webcam. It is the acceptance criterion for M3.1, and
it is the only number that tells you whether the rest of Stage 3 is standing on solid ground.

**PnP (perspective-n-point)** — The problem of recovering a camera's pose relative to an object from
known 3D points and their pixel positions. Detecting a marker gives you the pixels; PnP turns them
into a transform.

**Gimbal lock** — The failure mode of describing a 3D rotation with three sequential angles: at
certain orientations two of the three axes line up, a degree of freedom vanishes, and the angles
become ambiguous and jump. It is a property of the *representation*, not of the physical rotation,
and it is the reason quaternions exist and the reason Stage 4 uses them for IMU work.

**Hand-eye calibration** — Finding the fixed transform between a camera's frame and a robot's base
frame, classically by solving `AX = XB` over several arm poses with a marker on the gripper. Skipping
it produces grasps that miss by a consistent amount in a consistent direction — and consistency is
the diagnostic, because random error is noise while systematic error is geometry.

**sEMG (surface electromyography)** — Measuring the electrical activity of muscle from electrodes on
the skin. Microvolt-scale, bipolar, and heavily contaminated by mains hum and motion artifact, which
is why the processing chain — band-pass, rectify, smooth — exists at all.

**Feature window, RMS, MAV** — EMG is not used raw; features are computed over a sliding window of
samples. **RMS** and **MAV** (mean absolute value) both capture amplitude, roughly corresponding to
effort. Window length is a real trade-off: too short and the features are noisy, too long and the
control lag becomes perceptible to whoever is wearing it.

**Hudgins set** — The four time-domain EMG features named after Hudgins and colleagues: mean absolute
value, waveform length, zero crossings, and slope sign changes. They are the canonical feature set in
myoelectric control and they are what most of the literature means by "time-domain features." They
dominate not because nothing better exists but because they are cheap enough to compute on a
microcontroller in real time and still capture most of the discriminative information.

**Ag/AgCl electrode** — Silver/silver-chloride, the standard material for recording biopotentials
from skin. It matters because the electrode–skin junction is itself a small battery, and most metals
make an unstable one that drifts as you move — which shows up as the slow wandering baseline that
swamps a microvolt signal. Ag/AgCl has an unusually low and stable half-cell potential, so it drifts
much less. The disposable gel electrodes sold for ECG are Ag/AgCl and are what you want.

**Band-pass, rectify, envelope** — The three steps that turn raw sEMG into something you can control
with, and they are worth having as separate ideas rather than as one word. **Band-pass filtering**
keeps only a chosen range of frequencies — for sEMG, roughly 20–450 Hz — which throws away the slow
motion artifact below it and the noise above it. **Rectifying** takes the absolute value, because the
raw signal swings equally positive and negative, so its *average* is about zero no matter how hard you
clench; rectification turns "how much is it swinging" into "how big is it." **The envelope** is what
you get by smoothing the rectified signal — a slow curve that tracks effort rather than individual
muscle-fibre firings. The MyoWare board does all three in analogue hardware and gives you the envelope
on one pin; doing it yourself in software is M4.1's exercise and is the reason to understand the steps
separately.

**Kalman filter** — A recursive estimator that fuses a *model* of how something moves with *noisy
measurements* of it, weighting the two by how much it currently trusts each. Where a complementary
filter blends gyroscope and accelerometer with a fixed coefficient α that you guessed, a Kalman filter
computes the equivalent weighting every step from stated noise characteristics — so α stops being a
magic number and becomes a result. That is the whole conceptual difference and it is why M4.5 has you
build both and compare them on one recording.

**Quaternion** — A four-number representation of a 3D rotation. Rotations do not compose by adding
angles, and describing one with three sequential angles hits gimbal lock; quaternions have neither
problem, compose by multiplication, and interpolate smoothly, which is why every serious robotics and
graphics stack stores orientation this way. You do not need to derive the algebra to use them — you
need to know that a rotation is one object rather than three angles, and that ROS 2 message types carry
orientation as `x, y, z, w` for this reason.

**Confusion matrix, and cross-validation** — A **confusion matrix** is the table of what your
classifier predicted against what was true, one row per actual class and one column per predicted one.
The diagonal is correct answers and everything off it tells you *which* gestures get mistaken for which
— information a single accuracy percentage throws away. **Cross-validation** is splitting your data
into folds, training on all but one and testing on the one held out, repeated so every fold gets a
turn. It exists because testing on data you trained on measures memorisation rather than learning, and
it is the difference between an accuracy figure you can quote and one you cannot.

**Median frequency** — The frequency that splits an EMG signal's power spectrum into two equal
halves. It matters because it **falls as a muscle fatigues**, which makes it a measurable index of
fatigue rather than a guess — and it is why an amplitude threshold tuned when you are rested stops
working when you are tired. Amplitude and frequency both move; a threshold only watches one of them.

**Complementary filter** — A one-line sensor fusion: trust the gyroscope over short intervals
(accurate but drifting) and the accelerometer over long ones (noisy but absolute), blended by a single
coefficient. It works because it is a first-order high-pass on one signal and a low-pass on the other,
summing to unity.

**Feedforward** — Commanding a known-required output directly rather than waiting for feedback to
discover it. Gravity compensation is the clearest example: you can compute the torque needed to hold
the arm's own weight at any pose, so you apply it outright and let the feedback loop handle only what
you could not predict.

**Torque constant, `Kt`** — The proportionality between current through a motor's winding and the
torque it produces, in newton-metres per amp. It is what makes current usable as a force sensor, and
for a brushed motor it is numerically equal in SI units to the back-EMF constant `Ke` — which is the
easier thing to measure: spin the motor at a known speed and divide the generated voltage by the
angular velocity.

---

### Words about buying things across a border

Three terms that appear in the money documents and nowhere else, and all three change what a parcel
costs you.

**De minimis** — The value below which a shipment is waved through without duty or tax being
assessed. It is not one number: it depends on the country of *origin* and on how the goods travel.
For courier shipments from the United States or Mexico, Canada's CUSMA thresholds are CAD $150 for
duty and CAD $40 for tax; for a parcel from anywhere else, including China, the figure is **CAD $20**.
Any single number quoted without naming the origin is wrong somewhere.

> **WATCH OUT** — **The *Order Manifest* quotes CAD $150 against the AliExpress order, and that is the
> US/Mexico figure rather than the China one.** The manifest is a dated record of a purchase and is
> never edited, so read this entry as the correct rule and that line as superseded. The manifest's
> *conclusion* still holds and for the better of its two reasons: most electronic components and bare
> boards carry a **0 % MFN rate**, so they attract no duty by **classification** rather than by staying
> under a threshold. What changes is the expectation — at a CAD $20 threshold, more of your parcels are
> technically assessable than that page implies, so keep the C$20–40 buffer it recommends rather than
> treating "under the limit" as the reason nothing will be charged.

**HST (harmonized sales tax)** — The combined federal and provincial sales tax charged in several
Canadian provinces, including Nova Scotia, where it is **14 %**. It applies to essentially everything in
this project, it is charged at checkout by any registered vendor — including AliExpress and DigiKey
Canada — and it is not optional or avoidable. Every total in these documents is shown twice, before and
after it, for that reason.

**MFN (most-favoured-nation) rate** — The default tariff rate Canada applies to goods from any WTO
member. Most electronic components, bare boards and modules carry an MFN rate of **0 %**, which is why
the AliExpress order is very likely to attract no duty at all — by *classification*, not by staying
under a threshold. Those are two different reasons to pay nothing and it is worth knowing which one
is doing the work.

**DDP (delivered duty paid)** — An Incoterm meaning the seller has already paid the duty, tax and
brokerage, so nothing is collected at your door. DigiKey Canada ships DDP, which is the real reason
the Nucleo costs C$28 and not C$28 plus a surprise.

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

> **DEFINITION** — **Hard real-time** means a missed deadline is a system failure, not a slowdown. Your
> joint control loop is hard real-time: if it runs late the motor keeps doing whatever it was last
> told, and during fast movement that is how joints slam into their limits. **Soft real-time** means
> late is degraded but tolerable — a path planner taking an extra 20 ms is fine.

### Why every joint gets its own microcontroller

You could run all four joints from one board. Many hobby arms do.

**It is how the field actually works.** Dynamixel servos, ODrive controllers, automotive actuators and
the joint controllers inside real prostheses are all independent nodes on a bus.

**It forces you to design a protocol.** When one board runs everything, communication is a function
call. When four boards must agree on state, you have to decide message formats, update rates,
timeouts, error handling, and what happens when a node goes silent.

**It puts CAN on your resume.** Controller Area Network appears constantly in embedded, automotive,
robotics and medical device postings, and almost never in hobbyist portfolios.

**It scales without redesign.** Write the firmware once, flash it four times with different node IDs.

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
| **Microcontroller** | Runs the control loop | Arduino UNO (Stage 0) → STM32 (Stage 1) |
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
| **Windows desktop** | Editing, flashing, serial monitoring, plotting | Day one |
| **WSL (Ubuntu 24.04)** | Learning ROS 2, running Python tooling | Optional, any time |
| **Native Ubuntu 24.04** | ROS 2 host, Gazebo, socketCAN | **Required before Stage 2** |
| **Arduino UNO** | Stage 0 control loop | Day one |
| **STM32 Nucleo-F446RE** | Stage 1 joint firmware | Week 3–4 |
| **ESP32-S3 ×2** | Stage 1 CAN bus monitor; later, joints 3 and 4 | Stage 1 |

### The WSL question, settled

**Flash from Windows. Plot from either. Learn ROS 2 in WSL. Build in native.**

WSL handles well: ROS 2 concepts, colcon builds, Python nodes, URDF authoring, and all the Stage 4
dataset work.

WSL handles with effort: flashing and serial-monitoring a microcontroller. USB devices can be attached
with `usbipd-win`. It works, it is fiddly, and it adds a step every time you unplug something — which
you will do fifty times per session.

WSL handles poorly or not at all: **socketCAN**, which is simply not in the stock WSL2 kernel; Gazebo
Harmonic's 3D acceleration through WSLg; and ROS 2's DDS discovery across the WSL network boundary,
which is a well-known source of nodes that cannot see each other.

> **WATCH OUT** — Keep the repository clone on the Linux filesystem, under `~/`, **not** under `/mnt/c/`.
> Cross-filesystem access in WSL is dramatically slower and a colcon build on `/mnt/c` is genuinely
> painful. If you want the same code visible to Windows tools, **clone it twice from GitHub** rather
> than sharing one directory.

### Native Ubuntu: why, where, when

**Why it has to be native:** `socketCAN` is a kernel feature. `candump` and `cansend` do not exist
without it. Gazebo needs real GPU access. ROS 2 discovery needs a real network stack.

**Which machine:** desktop dual-boot, a spare SSD, or the laptop. Your Kali install is the wrong
distribution for this — Kali is a security-testing distribution with a different package set and a
rolling release model, and ROS 2 Jazzy targets Ubuntu 24.04 specifically. Wipe and install Ubuntu.

**By when:** before Stage 2 bring-up. **Earlier if you buy a CANable**, because socketCAN tooling is
the whole reason to own one.

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
  ├── tools/                       # capture.py, plot.py, kinematics.py
  ├── .github/workflows/ci.yml     # builds the firmware on every push
  ├── .gitignore
  ├── .gitattributes               # LFS tracking — set up on day one
  ├── .editorconfig                # what your EDITOR writes. A different layer
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

## Windows Side

The set that matters this week, because Stages 0 and 1 both live here. Everything below is free.

| Software | Why, and when |
|---|---|
| **Git for Windows** | Includes Git Bash. Set `user.name`, `user.email`, and `core.autocrlf = input` so line endings do not churn between Windows and Linux clones. |
| **Git LFS** | Run `git lfs install` once. Writing `.gitattributes` without this does nothing. |
| **VS Code** | Host for PlatformIO and a decent editor on both sides of the WSL boundary. The WSL extension is worth having. |
| **PlatformIO** (VS Code extension) *or* Arduino IDE | Stage 0. PlatformIO is the better long-term choice — real dependency management, per-project configuration, host-side unit tests, and it targets ESP32 and STM32 as easily as AVR. Arduino IDE gets you a first blink faster. |
| **Python 3.12+** with `pyserial`, `matplotlib`, `pandas` | **Stage 0 requires this and nothing else on this list provides it.** Session S7 captures a step response over serial and plots it. Tick *Add to PATH* during install. |
| **Zadig** | One-time. Installs the WinUSB driver your FX2-based logic analyzer needs. **Without it PulseView cannot see the device and it looks like a faulty purchase.** |
| **PulseView / sigrok** | Logic analyzer software. Install now; confirm it sees the device when it arrives. |
| **STM32CubeIDE** | Stage 1. Bundles CubeMX, the compiler and the debugger. Install it early — it is a large download with a fussy first run, and you do not want to meet it on the evening you are excited to start Stage 1. |
| **A serial terminal** | PuTTY, or the monitor built into PlatformIO. You will live in this during Stage 0. |
| **A CAD package** | **Stage 2, and nothing else on this list replaces it.** Pick one and commit: **FreeCAD** (free, open source, exports STEP, and — the reason it matters here — nothing you make is hostage to a licence you might lose), **Onshape** (free hobby tier, browser-based, easy; but hobby documents are *public*, which is fine for an open portfolio and not fine for anything else), or **Fusion 360** (free personal tier, most tutorials, most restrictions). Install it now and do one tutorial; do not meet it for the first time on the evening you want to design a link. |
| **A slicer** | Turns your CAD into printer instructions. **OrcaSlicer**, **PrusaSlicer** or whatever ships with your printer. Only needed once the printer arrives, but it is a free download and a concept worth meeting early. |
| `usbipd-win` | **Only** if you intend to flash from inside WSL. Skippable, and skipping is the simpler path. |

> **CHECK YOURSELF** — Windows is ready when PlatformIO builds and uploads a blink sketch to a board, a
> serial monitor shows output from it, `git push` works without prompting for a password, PulseView
> lists your analyzer, `python -c "import serial, matplotlib, pandas"` runs without error, and
> STM32CubeIDE has finished its first launch and update cycle.

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
default_envs = uno            ; which env runs when you do not name one

[env]                         ; settings shared by EVERY environment below
build_flags = -Wall -Wextra   ; extra compiler warnings, on by choice

[env:uno]
platform      = atmelavr      ; the CHIP FAMILY toolchain. Which compiler, which
                              ;   uploader, which register definitions.
board         = uno           ; the specific BOARD. Sets the exact chip, the clock
                              ;   speed, the flash and RAM sizes, and the upload
                              ;   protocol. platform is the family; board is the part.
framework     = arduino       ; the API layer you write against. `arduino` gives you
                              ;   pinMode, digitalWrite, Serial and the core that
                              ;   defines main() for you. Omit it and you are bare
                              ;   metal, which is where Stage 1 goes deliberately.
monitor_speed = 250000        ; baud rate `pio device monitor` opens at. It must match
                              ;   your Serial.begin(). 250000 rather than 115200 is
                              ;   derived in Stage 0 S7 and it is not arbitrary.

[env:native]
platform       = native       ; no cross-compiler at all — build for THIS machine
test_framework = unity        ; which unit-test framework `pio test` should expect
build_flags    = -std=c++17 -I include
```

Four of those deserve a sentence more than they look like they need.

**`platform` versus `board`.** `platform` chooses a whole toolchain — the compiler that targets AVR
chips, the tool that talks to their bootloader, the headers that define `TCCR1B`. `board` picks one
part within it and fills in the specifics: 16 MHz, 32 KB of flash, 2 KB of RAM, `avrdude` over
serial at a particular baud. Getting `board` wrong compiles fine and produces an image for the wrong
chip.

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

> **WATCH OUT** — **You have not run `git lfs install` on the Ubuntu machine.** It is in the Tonight
> checklist for the Windows side, and native Ubuntu arrives later — so the day you first clone this
> repository there, run it before you commit anything. Undoing this means rewriting history, which is
> a bad evening. `git lfs env` tells you in one line whether it is active where you are standing.

### Line endings, and why `core.autocrlf` has to be set before the first clone

Windows ends a line with two characters, `CR LF`. Linux and macOS use one, `LF`. Git can translate,
and the setting that decides how is `core.autocrlf`:

| Value | What it does | Use it |
|---|---|---|
| `input` | Convert `CRLF` to `LF` on commit; do not convert on checkout | **Always, here** |
| `true` | Convert both ways — `LF` in the repo, `CRLF` in your working tree | The Windows default. Not this project |
| `false` | Never convert | Only if every machine already agrees |

`.gitattributes` says `* text=auto eol=lf`, which is the repository stating what it wants regardless
of anybody's local setting — belt and braces, and the belt is the one that fails silently.

**The reason the order matters** is that this is a *commit-time* conversion. Clone with the wrong
setting, edit a file, and Windows line endings go into your history. Fix the setting afterwards and
every one of those lines shows as changed the next time anything touches the file, producing diffs
where a one-character fix appears as a 200-line rewrite. **The damage is in the history and the
setting is not retroactive** — which is why *Before You Build* puts it in the same breath as
installing Git, and why the fix, if you get it wrong, is to correct the setting and re-clone.

> **DEFINITION** — **`.editorconfig`, and why it is a different layer.** `.gitattributes` governs
> what lands **in the repository**; `.editorconfig` governs what your **editor writes** in the first
> place — indent style and width, final newline, trailing whitespace, maximum line length — and it is
> understood natively or by plugin in VS Code, CubeIDE and essentially everything else. The two are
> complementary rather than redundant: one is a last line of defence at commit time, the other stops
> the problem happening. Note the entry in this repository's file exempting `docs/guides/*.md` from
> trimming and wrapping, because these documents' figures are drawn to the column and a reflow
> destroys them silently.

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

## WSL Side

Optional, and useful mainly as a place to become fluent in ROS 2 before Stage 2 requires it.

Install **Ubuntu 24.04** from the Microsoft Store — matching the version you will eventually run
natively, so what you learn transfers exactly. Then:

```bash
sudo apt update && sudo apt upgrade
sudo apt install build-essential git python3-pip python3-venv cmake
```

ROS 2 Jazzy can be installed here too, and it is a fine place to work through the official tutorials
at `docs.ros.org` — nodes, topics, services, actions, parameters, launch files. That is pure concept
work and WSL handles it well.

### What not to do here

Do not build your Stage 2 workspace in WSL intending to move it. Not because moving is hard, but
because you will unknowingly work around WSL's discovery and rendering quirks and then be unable to
tell which of your workarounds were ever necessary. **Learn in WSL; build in native.**

---

## Native Ubuntu Side

Required before Stage 2 bring-up, and worth doing earlier — having ROS 2 working removes an obstacle
from a stage that has plenty already.

| | |
|---|---|
| **Distribution** | Ubuntu 24.04 LTS, native — dual-boot, spare SSD, or laptop |
| **ROS 2** | Jazzy Jalisco — LTS, targets 24.04, supported to May 2029. **This is a deliberate choice over the newer LTS — see below.** |
| **Simulator** | Gazebo Harmonic — **not** Gazebo Classic |
| **Deadline** | Before Stage 2 bring-up; earlier if you buy a CANable |
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

1. **Ubuntu 24.04 LTS.** Dual-boot alongside what is there, or a dedicated SSD. Back up first.
2. **ROS 2 Jazzy Jalisco**, desktop variant, following the current instructions at `docs.ros.org`.
   **Do not follow a third-party blog** — the official apt setup changes periodically, and stale
   instructions are the most common reason an install fails confusingly.
3. **Gazebo Harmonic**, the simulator paired with Jazzy.
4. Build tooling: `python3-colcon-common-extensions`, `python3-rosdep`, `python3-vcstool`.
5. **CAN tooling**: `can-utils`, which gives you `candump` and `cansend`. This is the software that
   does not exist in WSL and the practical reason this machine has to be real.
6. `sudo usermod -aG dialout $USER`, so you can open serial devices without `sudo`. Log out and back
   in.

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

Check 4 is the one that cannot pass in WSL. If `candump` prints that frame, this machine is ready for
Stage 1's bus work and Stage 2's bring-up.

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

- Run `uname -r` on every Linux environment you own; write down which are native and which are WSL.
- Create the `mimic` repository on GitHub.
- Commit the directory skeleton, the `.gitignore`, `.gitattributes`, a `LICENSE`, and a
  three-sentence `README.md` saying what Mimic is.
- Run `git lfs install`. Confirm `git push` works without a password prompt.
- Install Git, VS Code, PlatformIO, and Python 3 with `pyserial`, `matplotlib`, `pandas`.
- Start the Ubuntu 24.04 ISO downloading in the background.

### This week

- **Find a ~2 mm precision screwdriver, or order one.** Your XL4015, LM2596 and MP1584 each set their
  output with a multi-turn trim pot that needs one, and Stage 0's S2 is the session that uses it.
  **It is in no manifest section, so check rather than assume** — and if you do not have one, it is
  C$5–8 in Tier B and it needs to arrive before S2. Once found, put it in the bin with the buck
  converters.
- Install STM32CubeIDE and let it finish its first-run updates.
- Install PulseView **and Zadig**.
- **Pick a CAD package and do one tutorial in it.** FreeCAD, Onshape or Fusion 360 — the comparison is
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
- Decide whether you are buying a **CANable**. If yes, native Ubuntu moves up to a Stage 1
  requirement, because socketCAN is the entire reason to own one.
- Decide where native Ubuntu is going to live: desktop dual-boot, spare SSD, or the laptop.

### Before Stage 2 — the hard deadline

- Install native Ubuntu 24.04.
- Install ROS 2 Jazzy, Gazebo Harmonic, colcon, and `can-utils`.
- Run all four checks above, including the virtual CAN loopback.
- Add your user to `dialout`.
- Tag `v0.1-stage1-exit` — and only then think about the printer.

> **CHECK YOURSELF** — You are set up when a fresh clone of your repository on any of your machines
> builds the firmware for the stage you are on, when you know without checking which of your Linux
> environments is native, and when `docs/tuning/` has at least one file in it. The third is the one
> people skip.

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
