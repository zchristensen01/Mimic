# Mimic — Glossary

**Appendix Zero-A · every term the guide set assumes, in the order you need it**

This is the canonical glossary for the whole document set. It was the middle third of *Before You
Build* and it is a separate document now for one reason: as a single chapter you were told to read
it in one sitting, and nobody can. Split by session, it is six to ten terms on the evening you need
them.

---

## How to use this

**Read one block, then go and work.** Each block below is headed with the session it belongs to, and
each workbook session's *Before you start* box names the block by title. You are never asked to read
ahead.

| If you are | Read |
|---|---|
| Starting the project, today | *Before anything* — eighteen terms, twenty minutes |
| Opening a Stage 0 session | That session's block. Six to ten terms |
| Reading a workbook and stuck on a word | Search this file. Every term the set uses is here |
| Months ahead, curious | Anything. Nothing here spoils a session's exercise |

**A term appears once, under the session that first needs it.** Later sessions reuse terms freely
without repeating them — so if S8 uses a word you do not recognise, it was introduced earlier and
searching is faster than re-reading.

**Where a workbook defines a term at the point you need it, that definition is a convenience and
this file is the complete one.** Terms appear here even when you will not meet them for months,
because a dictionary you can only use after you already know the word is not a dictionary.

---

## Contents

- [Before anything · the words the rest of the set assumes](#before-anything--the-words-the-rest-of-the-set-assumes) — 18 terms
- [Before S0 · Bench, toolchain, and the repository](#before-s0--bench-toolchain-and-the-repository) — 13 terms
- [Before S1 · Motor forensics, and bolting it down](#before-s1--motor-forensics-and-bolting-it-down) — 9 terms
- [Before S2 · Power — draw the topology before you wire it](#before-s2--power--draw-the-topology-before-you-wire-it) — 10 terms
- [Before S3 · The encoder — interrupts and ×4 decoding](#before-s3--the-encoder--interrupts-and-4-decoding) — 8 terms
- [Before S4 · Open loop — making it turn, in both directions](#before-s4--open-loop--making-it-turn-in-both-directions) — 2 terms
- [Before S5 · The fixed-rate loop, and proving your rate](#before-s5--the-fixed-rate-loop-and-proving-your-rate) — 3 terms
- [Before S7 · Telemetry that fits — the bandwidth problem](#before-s7--telemetry-that-fits--the-bandwidth-problem) — 2 terms
- [Before S8 · P only — steady-state error and the stability boundary](#before-s8--p-only--steady-state-error-and-the-stability-boundary) — 4 terms
- [Before S9 · Step-response metrics — the four numbers](#before-s9--step-response-metrics--the-four-numbers) — 1 term
- [Before S10 · D, then I — derivative on measurement and anti-windup](#before-s10--d-then-i--derivative-on-measurement-and-anti-windup) — 2 terms
- [Before S11 · The safety envelope, and getting off `analogWrite()`](#before-s11--the-safety-envelope-and-getting-off-analogwrite) — 2 terms
- [Before S12 · The refactor, and the exit gate](#before-s12--the-refactor-and-the-exit-gate) — 4 terms
- [Before S1.0 · CubeIDE, and the shape of a generated project](#before-s10--cubeide-and-the-shape-of-a-generated-project) — 3 terms
- [Before S1.1 · Blink, and the breakpoint that is the actual point](#before-s11--blink-and-the-breakpoint-that-is-the-actual-point) — 1 term
- [Before S1.2 · The clock tree, and why 180 MHz is not automatic](#before-s12--the-clock-tree-and-why-180-mhz-is-not-automatic) — 3 terms
- [Before S1.3 · Hardware quadrature — the encoder that costs no CPU](#before-s13--hardware-quadrature--the-encoder-that-costs-no-cpu) — 1 term
- [Before S1.4 · The control loop in C, on bare metal](#before-s14--the-control-loop-in-c-on-bare-metal) — 2 terms
- [Before S1.5 · FreeRTOS — two tasks, and the demonstration that justifies it](#before-s15--freertos--two-tasks-and-the-demonstration-that-justifies-it) — 9 terms
- [Before S1.6 · CAN, physically — two nodes and a counter](#before-s16--can-physically--two-nodes-and-a-counter) — 13 terms
- [Before S1.7 · Designing the joint protocol — paper before keyboard](#before-s17--designing-the-joint-protocol--paper-before-keyboard) — 2 terms
- [Before S2.1 · ROS 2, the graph](#before-s21--ros-2-the-graph) — 6 terms
- [Before S2.2 · Forward kinematics, derived](#before-s22--forward-kinematics-derived) — 3 terms
- [Before S2.3 · Inverse kinematics, derived](#before-s23--inverse-kinematics-derived) — 2 terms
- [Before S2.4 · The torque budget](#before-s24--the-torque-budget) — 8 terms
- [Before S2.5 · CAD, and design for printing](#before-s25--cad-and-design-for-printing) — 4 terms
- [Before S2.6 · URDF, and seeing it in rviz2](#before-s26--urdf-and-seeing-it-in-rviz2) — 1 term
- [Before S2.7 · Gazebo Harmonic](#before-s27--gazebo-harmonic) — 1 term
- [Before S2.8 · ros2_control with mock hardware](#before-s28--ros2control-with-mock-hardware) — 3 terms
- [Before S2.9 · Print and assemble](#before-s29--print-and-assemble) — 3 terms
- [Before S2.12 · Homing and calibration](#before-s212--homing-and-calibration) — 1 term
- [Before S2.13 · MoveIt 2 and Cartesian commands](#before-s213--moveit-2-and-cartesian-commands) — 2 terms
- [Before S2.14 · Record and replay](#before-s214--record-and-replay) — 1 term
- [Stage 3 · Eyes and Voice](#stage-3--eyes-and-voice) — 9 terms
- [Stage 4 · The Biomech Payload](#stage-4--the-biomech-payload) — 11 terms
- [Stage 5 · Impedance and Rehab Mode](#stage-5--impedance-and-rehab-mode) — 3 terms
- [Ordering · what a parcel actually costs](#ordering--what-a-parcel-actually-costs) — 4 terms

---

## Before anything · the words the rest of the set assumes

Eighteen terms. Read these once, before you read anything else in the set. Every other document uses
them without stopping to explain, and they are the difference between a sentence that is opaque and
one that is merely new.

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

**Control loop** — Code that runs at a fixed rate and each time reads where the motor actually is,
compares that to where it should be, and adjusts the power. That is the beating heart of this entire
project. Everything else is layers on top of it.

**Open loop and closed loop** — Open loop is commanding and hoping: "run at 40 % for half a second."
Closed loop is measuring the result and correcting continuously. The measurement is what closes the
loop, and the sensor that closes it is the encoder.

**Setpoint, error** — The setpoint is the position you are asking for. The error is setpoint minus
actual. Every control loop is fundamentally a machine for making the error small.

**Plant** — Control-theory word for *the thing you are controlling*, taken as a whole: in Stage 0 the
motor, gearbox, driver, shaft and whatever is bolted to it. It is a useful word precisely because it
does not distinguish between them — when you tune, you are tuning against the plant's behaviour, not
against the motor's. A plant is **non-linear** when its response to a command depends on the size of
the command, which yours is: deadband and saturation mean a 90° step and a 10° step do not see the
same effective gain.

**Kinematic chain** — A sequence of rigid links connected by joints, described as a tree of coordinate
frames each defined relative to the one before it. "Walking the chain" means composing those
relationships from the base out to the tip, which is what forward kinematics does.

---

## Before S0 · Bench, toolchain, and the repository

The vocabulary of the tools rather than the robot. You meet all of it on the first evening, and none
of it again until it breaks.

**Repository (repo)** — A folder tracked by git, holding your files plus the complete history of every
change. A **commit** is one saved snapshot with a note. A **branch** is a parallel line of work. A
**tag** is a permanent label on one commit. **GitHub** stores a copy so other machines — and other
people — can reach it.

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

**`.clang-format`** — A file declaring how your *C and C++* should be laid out: where the braces go,
how far a continuation indents, how a long parameter list breaks. `.editorconfig` sets the tab width
for every file type and stops there; `.clang-format` knows the language, and one keystroke reformats
a file to match. Part IV says why it is worth having on day one rather than at Stage 1.

**Debugger, breakpoint, watch** — A debugger halts the chip mid-execution so you can look inside it. A
breakpoint is a line you mark where it should stop. A watch is a variable you asked it to display.
This is the professional alternative to scattering print statements, and getting it working is the
single biggest quality-of-life jump from Arduino to real embedded work.

**ADR (Architecture Decision Record)** — A short file recording a decision that had real
alternatives: **Context, Decision, Alternatives Considered, Consequences**, four sentences each.
Kept in `docs/decisions/`. This is the single highest-leverage documentation habit in the project,
because these are precisely what an interview probes — and a note written the day you decided is
evidence, where a recollection eight months later is a guess.

---

## Before S1 · Motor forensics, and bolting it down

**The encoder entry is the one to read first.** S1 asks you to multiply by four without having
explained why, and this is where the four comes from. The torque entries matter because your motor's
listing quotes three different kinds of torque and calls them all torque.

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

**Absolute versus incremental** — An incremental encoder counts changes and knows nothing at power-up,
which is why homing exists. An absolute encoder like the AS5600 reports the actual angle immediately.

**Static, rated and stall torque** — Three different numbers that vendors mix freely, and keeping them
apart is what makes Stage 2's arithmetic honest. **Stall torque** is what a motor produces at zero
speed with full voltage applied — the biggest number on any listing, and a destructive operating
point rather than a design figure. **Rated torque** (sometimes *continuous* or *nominal*) is what it
can produce indefinitely without overheating, typically a quarter to a third of stall. **Static
torque** is what a joint must produce merely to hold a pose against gravity — a demand, not a
capability. A listing quoting one figure without saying which almost always means stall.

**kg·cm, and kgf** — The unit almost every hobby motor and servo listing quotes torque in, and it is
not an SI unit. A **kgf** (kilogram-force) is the force gravity exerts on one kilogram — 9.81 N — so
**kg·cm** is that force acting at one centimetre: `1 kg·cm = 0.01 m × 9.81 N = 0.0981 N·m`. To convert,
divide by about 10.2, or multiply by 0.0981. Every torque figure in Stage 2 gets converted to N·m
before it is compared to anything, because the requirement side of that comparison is in N·m and
mixing the two is the same class of error as mixing degrees and radians. Note also that a bare "kg" on
a spec table is *not* a torque at all — it is usually a load or a mass, and reading one as the other
is a real trap.

**Backdrivable** — Whether you can turn the output shaft by hand and have the motor turn with it.
High gear ratios are barely backdrivable: the gearbox multiplies the motor's friction and inertia as
seen from the output, so most of the force you apply at the shaft is spent fighting the gearbox
rather than turning the motor. It matters enormously in Stage 5, because you cannot make a joint feel
compliant if it physically resists being moved.

**Heat-set insert** — A small brass sleeve melted into 3D-printed plastic with a soldering iron, so
a screw threads into metal rather than into plastic. Screwing directly into printed plastic strips
on the second or third assembly, and you will assemble more than twice.

**Threadlocker** — A liquid adhesive put on a screw thread so vibration cannot back the fastener out.
Blue is medium-strength and comes apart with hand tools, which is the one you want; red is effectively
permanent without heat. A two-DOF arm vibrates more than you expect, and a fastener working loose
mid-motion is both a failure and a hazard.

**Backlash** — The free play in a gear train: the small angle you can rotate the output before the
input starts to move. It is what makes a joint feel loose at reversal, it is invisible to an encoder
mounted on the motor side, and it is why an encoder on the *joint* tells you something the motor's
own encoder cannot.

---

## Before S2 · Power — draw the topology before you wire it

Everything here is about current going where you did not intend. Read *Star ground*, *Bulk
capacitance* and *Decoupling capacitor* together — they are three answers to one problem.

**H-bridge** — Four switches arranged around a load in the shape of the letter H, with the motor as
the crossbar. Close one diagonal pair and current runs one way through the motor; close the other and
it runs the other way. That is the only way to reverse a brushed DC motor from a single-polarity
supply, and the TB6612FNG *is* two of them. It also explains `brake` (both switches on one side
closed, so the motor's terminals are shorted and its own back-EMF opposes motion) and `coast` (all
four open). Closing both switches on the same *leg* is **shoot-through**, a dead short across the
supply, and preventing it is what the chip's internal logic is for.

**Star ground** — A wiring topology where every return path meets at one single physical point rather
than daisy-chaining board to board. Wire has resistance, so if motor return current shares a length
of wire with your encoder's ground, the motor shifts your encoder's idea of what 0 V means. That is
not noise you can filter; it is a topology error.

**Bulk capacitance** — A large capacitor placed near a load to supply sudden current locally, so the
surge does not travel back up the wire and drag the whole rail down. The 1000 µF across your motor
driver is this.

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

**Trim pot (trimmer potentiometer)** — A small screw-adjusted resistor on a board, used to set
something once and leave it. Your buck converters set their output voltage with one, often
multi-turn — fifteen full rotations end to end — which is why a ~2 mm precision screwdriver, rather
than any driver in a general tool roll, is what session S2 actually needs. **Verify first** — no
precision driver appears anywhere in the *Order Manifest*, so do not assume you own one. C$5–8 if you
do not, and it is listed in Tier B of *What's Left to Buy*.

**Ground loop** — What you get when two points both called "ground" are joined by more than one path,
so current can circulate around the loop they enclose. The two ends then sit at slightly different
potentials, and every signal referenced to one of them is measured against the wrong zero. A star
topology has exactly one path to each return, which is why it does not have this problem.

---

---

## Before S3 · The encoder — interrupts and ×4 decoding

The heaviest vocabulary session in Stage 0, and the one where the words are load-bearing rather than
descriptive. *Torn read* and `volatile` are the same bug seen from two sides.

**Interrupt** — A hardware event that stops your program mid-line, runs a small handler, and returns.
Essential for encoders, and dangerous if the handler does too much.

**ISR (interrupt service routine)** — The small handler function an interrupt runs. "Keep the ISR
short" is the most repeated advice in embedded work, because your main program is stopped while it
executes. On the UNO that is literally everything; on the STM32 in Stage 1 a higher-priority
interrupt can still get in, which is a feature you will use deliberately rather than an exception to
the rule.

**Polling** — Repeatedly checking something rather than being interrupted by it. Simpler, and wastes
time.

**Debounce** — A mechanical switch does not close once; it bounces, making and breaking several times
over a few milliseconds. Debouncing is ignoring everything after the first transition until the bounce
window has passed. Stage 2 S2.12 makes you cost this in degrees of overshoot rather than treating it as
a nuisance.

**Torn read** — Reading a multi-byte variable on an 8-bit chip and being interrupted halfway, so you
get some old bytes and some new ones. A `long` on an AVR is four bytes and four chances. The fix is
to disable interrupts around the copy.

**`volatile`** — A keyword telling the compiler a variable can change by means it cannot see — an
interrupt, usually — so it must not cache the value in a register or optimise the read away. What it
does **not** give you is atomicity: it guarantees the read happens, not that it happens all at once.
That second problem is the torn read, and its fix is disabling interrupts, not `volatile`. You
generally need both, for two different reasons.

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

**Pull-up and pull-down resistor** — A resistor tying a signal line to VCC (pull-up) or to ground
(pull-down), so the line has a defined level when nothing is actively driving it. Without one a
floating input reads as noise — it will happily report both 0 and 1 while you watch. Three places this
matters in Mimic: a switch wired to ground needs a pull-up so the pin reads HIGH when the switch is
open, which is what `INPUT_PULLUP` enables inside the AVR; I²C needs pull-ups on both lines because
every device only ever pulls them *down*; and Stage 1's node-ID jumpers use the STM32's internal
pull-ups, which is why "no jumpers fitted" reads as all-ones rather than all-zeros.

---

## Before S4 · Open loop — making it turn, in both directions

Two terms. *Deadband* is the one that will confuse you on the bench, because a motor that does not
move looks like a wiring fault rather than a duty cycle below the threshold.

**PWM (Pulse Width Modulation)** — A pin can only be fully on or fully off. PWM switches it fast enough
that the average is anything in between. **Duty cycle** is the fraction of each period spent on.

**Deadband** — The range of small commands that produce no motion at all, because static friction
has not been overcome yet. Every geared motor has one. It is why a proportional controller stops a
degree or two short, and measuring it in Stage 0 S4 turns that from a mystery into a prediction.

---

## Before S5 · The fixed-rate loop, and proving your rate

The session where *when* your code runs starts to matter as much as what it does.

**Superloop** — The simplest program structure on a microcontroller: one endless loop doing everything
in order. It is what Arduino's `loop()` is. Fine until two things need different schedules, which is
the problem an RTOS solves.

**Real-time, deterministic** — "Real-time" does not mean fast; it means predictable. A real-time loop
runs every millisecond, every millisecond. Deterministic means the timing does not wander. This
matters because a loop tuned for one rate behaves worse if the rate drifts — and a general-purpose OS
cannot promise it will not.

**Deadline, jitter, latency** — A deadline is when work must finish. Jitter is variation from cycle to
cycle. Latency is delay between cause and effect. **Control loops tolerate latency far better than
they tolerate jitter.**

---

## Before S7 · Telemetry that fits — the bandwidth problem

S6 (units) introduces no new vocabulary — it uses what S1 and S3 already gave you. S7 needs two
terms about getting bytes off the board.

**Bus** — A shared set of wires several devices connect to. I²C, SPI and CAN are buses. UART — plain
serial — is a point-to-point link between exactly two devices, not a bus.

**UART / serial** — The simplest digital link: two wires, one talking each way. This is what "serial
monitor" means. Your main window into Stage 0.

---

## Before S8 · P only — steady-state error and the stability boundary

The control vocabulary proper. You have been running a loop since S5; this is where it gets a
controller in it.

**PID** — The standard recipe, named for its three parts. **Proportional** responds to how wrong you
are right now. **Integral** responds to error accumulated over time, eliminating the stubborn small
offset P alone never closes. **Derivative** responds to how fast the error is changing, damping
overshoot. Stage 0 is entirely about this, and you implement it yourself rather than importing it.

**Gain** — The tuning multiplier on each part, written Kp, Ki, Kd. Tuning means hunting for values
that make the joint arrive quickly without oscillating. There is no formula that hands you the
answer — it is empirical, which is exactly why every value gets written down.

**Saturation** — What happens when a controller asks for more output than the hardware can give. Your
command is clamped to ±1.0 and then to ±255, so any demand beyond that is simply lost. It matters
twice: it is half of why integral windup happens, and it is what conditional integration watches for.

**Hysteresis** — Deliberately making a threshold behave differently on the way up and on the way down,
so a signal sitting exactly on it does not chatter. Switch on at 0.6, off at 0.4, and a noisy signal
hovering near 0.5 produces one clean transition instead of forty. You will want it the first time you
drive a gripper from an EMG envelope, and it costs two lines.

---

## Before S9 · Step-response metrics — the four numbers

One term, and the whole session is about measuring it precisely.

**Step response** — The standard diagnostic. Command an instant jump from one position to another and
graph what actually happened. **Rise time** is how long to get there (10 % to 90 %). **Overshoot** is
how far past it went. **Settling time** is how long until it stays within ±2 %. **Steady-state error**
is how far off it eventually settled.

---

## Before S10 · D, then I — derivative on measurement and anti-windup

Two terms, and they are the same phenomenon and its cure. Read them in order.

**Integral windup** — A classic failure you will meet personally in Stage 0. If the motor cannot reach
the target for a while, the integral term keeps accumulating, growing enormous. When the motor frees
up it lurches violently past. The fix is to clamp the accumulator, and meeting the problem yourself is
part of the education.

**Anti-windup** — The fix for integral windup, and there are two mechanisms worth knowing because
they address different halves of the problem. **Conditional integration** stops accumulating while
the output is already saturated and the error would push it further into the clamp. **Accumulator
clamping** bounds the stored value so the integral term alone cannot exceed the output range. Use
both; each catches a case the other misses.

---

## Before S11 · The safety envelope, and getting off `analogWrite()`

*Prescaler* is the one that turns S11 Part B from magic into arithmetic.

**Fail-safe** — Designed so a failure produces a safe state rather than an arbitrary one. In Stage 1,
a joint that stops hearing from the host holds position rather than continuing its last velocity
command. The first is bounded; the second integrates without limit.

**Prescaler** — A divider between a clock source and a timer. Changing it changes how fast the timer
counts, and therefore PWM frequency. On the UNO it is one register write; on the STM32 it is a field
in CubeMX. Same idea, both times.

---

## Before S12 · The refactor, and the exit gate

C++ vocabulary. You have been writing C-with-classes; this is where the language starts paying you
back for it.

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

---

## Before S1.0 · CubeIDE, and the shape of a generated project

Three terms, and together they are the answer to "what was Arduino doing that I never saw?" You are
about to open the three files that do it.

**Bare metal** — Code running directly on the processor with no operating system underneath it: no
scheduler, no memory protection, nothing to catch you. Everything in Stage 0 is bare metal; Stage 1
is the point at which you can see the edges of it.

**Vector table** — An array of addresses at the very start of flash. The processor reads entry zero to
find its initial stack pointer, entry one to find the reset handler, and one entry per interrupt
source after that. It is the literal answer to "how does the chip know to run my code."

**Linker script** — The file (`.ld`) deciding where everything lands in the address space: where flash
starts, where RAM starts, which direction the stack grows, where the vector table sits. Arduino had
one; it simply never showed it to you.

---

## Before S1.1 · Blink, and the breakpoint that is the actual point

One term. The LED is not the deliverable; the halted processor is.

**JTAG and SWD** — Two debug interfaces. **JTAG** is the older, five-pin standard; **SWD** *serial wire
debug* is ARM's two-pin replacement and does everything you need. The distinction has one practical
consequence in this project: several pins are shared with JTAG and are only yours as ordinary GPIO when
the debug interface is set to SWD, which is why Stage 1's pin map insists on *Serial Wire* and warns
that PB4 is `NJTRST`.

---

## Before S1.2 · The clock tree, and why 180 MHz is not automatic

Three terms. Read them before the session rather than during it — this is the one Stage 1 session
where the vocabulary *is* the content.

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

---

## Before S1.3 · Hardware quadrature — the encoder that costs no CPU

One term, and it is the source of the commonest off-by-one in timer configuration.

**ARR, and the N−1 rule** — **ARR** is a timer's *auto-reload register*: the value the counter
counts up to before it resets. It sets the period, so PWM frequency is the timer's clock divided by
`ARR + 1`. The `+ 1` is the whole trap, and it generalises: **when a hardware field configures a
divider or a count, expect the register to hold one less than the number you mean**, because a field
of zero has to be able to mean "divide by one". You meet the same rule again in the CAN bit-timing
fields, where the value you type into the tool and the value in the register differ by exactly one.

---

## Before S1.4 · The control loop in C, on bare metal

Two terms about how an interrupt actually reaches your code on this chip.

**NVIC** — The *nested vectored interrupt controller*, which decides which interrupt runs and when.
It is **vectored**, so each source has its own vector-table entry and there is no dispatch code to
write; **prioritised**, with the confusing convention that lower numbers mean higher priority; and
**nested**, so a higher-priority interrupt can pre-empt one already running. That last point is the
real change from an 8-bit AVR, where entering an interrupt disabled interrupts globally and every
handler was therefore automatically atomic with respect to every other.

---

**SysTick** — A small 24-bit countdown timer built into every Cortex-M core, intended as the operating
system's heartbeat. It matters in Stage 1 for one reason: ST's HAL uses it to drive `HAL_Delay`, and
FreeRTOS wants it for the scheduler. They cannot both own it, which is why S1.5 moves the HAL's
timebase onto a spare timer.

---

## Before S1.5 · FreeRTOS — two tasks, and the demonstration that justifies it

**Nine terms, the heaviest block in the set.** Read the first five before the session and the last
four when the session reaches the queue — they will not stick otherwise.

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

**DMA** — *Direct memory access*: a block that moves data between a peripheral and memory without the
processor being involved. Not used in Mimic, but it appears on every embedded job posting and it is the
standard answer to "how do I stream an ADC at 100 kHz without spending all my CPU on interrupts."

---

## Before S1.6 · CAN, physically — two nodes and a counter

Thirteen terms, but they divide cleanly: the electrical ones (*Differential signalling*,
*Termination*, *Transceiver*, *Recessive and dominant*, *Shield*) explain the wire, and the rest
explain the protocol on it. `I²C` and `SPI` are here for contrast — knowing what CAN does that they
do not is most of understanding why it exists.

**Bus-off** — The state a CAN node puts itself into after producing too many transmit errors. It stops
transmitting entirely and has to be reset before it will talk again. It is correct behaviour rather
than a fault — a node that is producing garbage removes itself so it cannot take the whole bus down —
and the symptom you observe is a node that was working and has gone silent on its own.

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

**I²C** — Two wires, many devices, each with an address. Slow but simple, and the standard way small
sensors attach. Your AS5600 angle sensor and INA219 current sensor both use it.

**SPI** — Four wires, faster than I²C, one extra wire per device to select it.

**Recessive and dominant** — The two states of a CAN wire pair. **Recessive** is the idle state, both
lines pulled to about 2.5 V, and it is what a logical 1 looks like. **Dominant** drives the lines
apart and is a logical 0, and it *overrides* recessive — any node transmitting dominant wins over any
node transmitting recessive on the same bit. That asymmetry is the entire mechanism of arbitration:
the lower identifier has more dominant bits earlier, so it survives.

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

**socketCAN** — The Linux kernel's CAN networking stack. It makes a CAN bus look like an ordinary
network interface, so `ip link` configures it and `candump`/`cansend` read and write it exactly the way
you would use `tcpdump` on Ethernet. It is a *kernel* feature, which is the entire reason this project
runs on a real Linux machine: where the module is absent the tools do not merely misbehave — they have
nothing to attach to. A stock Ubuntu kernel carries it, and `sudo modprobe vcan` is how you prove that
on an evening with no hardware on the desk.

---

## Before S1.7 · Designing the joint protocol — paper before keyboard

Two terms, and the session is an argument about both. *Arbitration* is why the identifier is also a
priority, which is the single idea your emergency-stop message depends on.

**Arbitration** — What happens when two devices transmit simultaneously. Rather than colliding, the
lower identifier wins and the higher backs off and retries.

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

---

## Before S2.1 · ROS 2, the graph

Six terms, and this is the session that exists to make them concrete. Read them, then go and run the
commands — none of it lands from reading alone.

**Topic, service, action** — The three ways ROS 2 nodes talk. A **topic** is a named stream that
anyone may publish to and anyone may subscribe to, with no reply — sensor data and joint states. A
**service** is a request and a single response, for quick queries. An **action** is a long-running
request with progress feedback and the ability to cancel — which is what moving an arm is, and why
trajectories are actions rather than services.

**Message type** — The schema of what travels on a topic. Publishers and subscribers must agree on it
exactly; a mismatch means they simply do not connect.

**DDS** — The middleware underneath ROS 2 that handles discovery and delivery. Nodes find each other
over the network with no central master, which is a genuine improvement and also the reason a network
boundary — a VM's NAT, a container, a firewall, a second subnet — breaks discovery in ways that look
like your code failing.

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

---

## Before S2.2 · Forward kinematics, derived

Three terms. *tf2* is here rather than later because a frame tree is the thing you are deriving,
whether or not you are using the library yet.

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

**tf2** — The transform library. Nodes publish the relationships between coordinate frames, and tf2
lets any node ask "where is this point, expressed in that frame," at a given time. It is the
bookkeeping that keeps a camera's view and an arm's geometry in the same world.

---

## Before S2.3 · Inverse kinematics, derived

Two terms, and the second one is why this session is harder than the last. A singularity is not an
edge case you can ignore; it is a place your arm will actually go.

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

---

## Before S2.4 · The torque budget

**Eight terms, and this is the session that changes your parts list.** *Static, rated and stall
torque* is in the Before-S1 block and worth re-reading first — the whole budget turns on keeping
those three apart.

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

---

## Before S2.5 · CAD, and design for printing

Four terms. All four are the difference between a model that looks right and a part that comes off
the bed usable.

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

---

## Before S2.6 · URDF, and seeing it in rviz2

One term, and it is the file format the next four sessions all read.

**URDF, and xacro** — **URDF** is the XML description of a robot as a tree of links joined by joints,
with axes, limits, visual geometry, collision geometry and inertias. Nearly everything in the
manipulation stack reads it, so an error here is an error everywhere at once. **xacro** is a macro
preprocessor adding constants, arithmetic and reusable macros, expanding to plain URDF before anything
else sees it — use it from the first line, so that changing a link length is one edit rather than
eleven.

---

## Before S2.7 · Gazebo Harmonic

One term. The distinction between it and URDF is the distinction between visualising and simulating.

**SDF** — Gazebo's own description format. It describes worlds as well as robots: lights, physics,
ground planes, sensors. Gazebo converts your URDF to SDF when it spawns it, which is why URDF stays
the single source of truth. What you add to the URDF are `<gazebo>` tags — blocks meaning nothing to
the visualiser and passed through to the simulator.

---

## Before S2.8 · ros2_control with mock hardware

Three terms, and the first one has four words inside it that the session depends on completely.

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

---

## Before S2.9 · Print and assemble

Three terms about the machine rather than the model. Read them before you buy a printer, not after.

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

---

## Before S2.12 · Homing and calibration

One term, and *Absolute versus incremental* in the Before-S1 block is the other half of it.

**Homing** — Finding out where "zero" is at startup. Drive slowly until a limit switch trips, then
call that zero. Necessary because a plain motor encoder counts changes and has no idea where it
started.

---

## Before S2.13 · MoveIt 2 and Cartesian commands

Two terms.

**SRDF** — The *semantic* robot description format, MoveIt's companion to the URDF. The URDF says
what the robot physically is; the SRDF says what the parts of it *mean* to a planner — which joints
form a "planning group" you can command as a unit, which named poses exist ("home", "ready"), and which
pairs of links can never collide and may therefore be skipped in collision checking. The Setup
Assistant generates it, and the reason to know the word is that when MoveIt refuses a reachable target,
the joint limits it is refusing on may be in either file.

**MoveIt 2** — The motion planning stack. You give it a target pose; it produces a collision-free,
time-parameterised trajectory and hands it to a controller as an action.

---

## Before S2.14 · Record and replay

One term.

**rosbag** — Recording of topics to a file, replayable later. The ROS 2 equivalent of the CSV pipeline
you build in Stage 0, with the difference that it captures everything rather than the fields you
thought to log.

---

## Stage 3 · Eyes and Voice

Nine terms. The camera cluster is a geometry problem before it is a vision problem, which is why
*Interlude F · Frames of Reference* matters more here than any library documentation.

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

**Quaternion** — A four-number representation of a 3D rotation. Rotations do not compose by adding
angles, and describing one with three sequential angles hits gimbal lock; quaternions have neither
problem, compose by multiplication, and interpolate smoothly, which is why every serious robotics and
graphics stack stores orientation this way. You do not need to derive the algebra to use them — you
need to know that a rotation is one object rather than three angles, and that ROS 2 message types carry
orientation as `x, y, z, w` for this reason.

**Hand-eye calibration** — Finding the fixed transform between a camera's frame and a robot's base
frame, classically by solving `AX = XB` over several arm poses with a marker on the gripper. Skipping
it produces grasps that miss by a consistent amount in a consistent direction — and consistency is
the diagnostic, because random error is noise while systematic error is geometry.

**micro-ROS** — A ROS 2 client library small enough to run on a microcontroller, so a joint can be a
ROS 2 node itself rather than sitting behind a bridge. Appropriate for learning and prototyping; it
is not developed to any safety or medical standard, and keeping that distinction crisp matters.

---

---

## Stage 4 · The Biomech Payload

Eleven terms. Start the software months early against a public dataset — the electrode terms are not
needed until you put something on your skin, and *Galvanic isolation* is not optional when you do.

**ADC** — Analogue-to-digital converter. Turns a voltage into a number. How you read a potentiometer,
a current sensor, or an EMG signal.

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

**sEMG (surface electromyography)** — Measuring the electrical activity of muscle from electrodes on
the skin. Microvolt-scale, bipolar, and heavily contaminated by mains hum and motion artifact, which
is why the processing chain — band-pass, rectify, smooth — exists at all.

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

**Feature window, RMS, MAV** — EMG is not used raw; features are computed over a sliding window of
samples. **RMS** and **MAV** (mean absolute value) both capture amplitude, roughly corresponding to
effort. Window length is a real trade-off: too short and the features are noisy, too long and the
control lag becomes perceptible to whoever is wearing it.

**Hudgins set** — The four time-domain EMG features named after Hudgins and colleagues: mean absolute
value, waveform length, zero crossings, and slope sign changes. They are the canonical feature set in
myoelectric control and they are what most of the literature means by "time-domain features." They
dominate not because nothing better exists but because they are cheap enough to compute on a
microcontroller in real time and still capture most of the discriminative information.

**Median frequency** — The frequency that splits an EMG signal's power spectrum into two equal
halves. It matters because it **falls as a muscle fatigues**, which makes it a measurable index of
fatigue rather than a guess — and it is why an amplitude threshold tuned when you are rested stops
working when you are tired. Amplitude and frequency both move; a threshold only watches one of them.

**Confusion matrix, and cross-validation** — A **confusion matrix** is the table of what your
classifier predicted against what was true, one row per actual class and one column per predicted one.
The diagonal is correct answers and everything off it tells you *which* gestures get mistaken for which
— information a single accuracy percentage throws away. **Cross-validation** is splitting your data
into folds, training on all but one and testing on the one held out, repeated so every fold gets a
turn. It exists because testing on data you trained on measures memorisation rather than learning, and
it is the difference between an accuracy figure you can quote and one you cannot.

**Kalman filter** — A recursive estimator that fuses a *model* of how something moves with *noisy
measurements* of it, weighting the two by how much it currently trusts each. Where a complementary
filter blends gyroscope and accelerometer with a fixed coefficient α that you guessed, a Kalman filter
computes the equivalent weighting every step from stated noise characteristics — so α stops being a
magic number and becomes a result. That is the whole conceptual difference and it is why M4.5 has you
build both and compare them on one recording.

**Complementary filter** — A one-line sensor fusion: trust the gyroscope over short intervals
(accurate but drifting) and the accelerometer over long ones (noisy but absolute), blended by a single
coefficient. It works because it is a first-order high-pass on one signal and a low-pass on the other,
summing to unity.

---

## Stage 5 · Impedance and Rehab Mode

Three terms, and they are the whole stage: an arm that is compliant rather than stiff needs to
command torque, which needs a motor constant and a term that is not feedback at all.

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


Three terms that appear in the money documents and nowhere else, and all three change what a parcel
costs you.

**Impedance control** — Stage 5 territory. Instead of commanding a position rigidly, you make the
joint behave like a spring of chosen stiffness, so it yields when pushed by a controlled amount. This
is what makes a rehabilitation robot safe to interact with, and it is why measuring motor current
matters.

---

## Ordering · what a parcel actually costs

Four terms that appear in the money documents and nowhere else, and all four change what a parcel
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
