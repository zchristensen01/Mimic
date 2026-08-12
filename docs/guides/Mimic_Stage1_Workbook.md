# Mimic — Stage 1 Workbook

**Volume IV · The Smart Joint, session by session**

Ten sessions from a bare-metal blink to two joints running identical firmware on a CAN bus.
Written against the **STM32 Nucleo-F446RE**, FreeRTOS, and bxCAN.

---

## The standing rule, and why it matters more here than it did in Stage 0

**Capture the broken state before you fix it.** Each session's *What will go wrong* ends by naming
the specific one worth catching, and it is a screenshot or a phone photo of a screen — seconds, and
it does not need to be good.

Stage 0's failures were loud. A motor oscillating at `Ku` announces itself from the next room. **Stage
1's failures are silent**, and that changes what capturing them is worth. A CAN bus with a bit-rate
mismatch does not error — it is simply quiet. A filter with the wrong shift accepts everything, which
looks exactly like a working filter until a second node appears. A clock tree without Over-Drive runs
perfectly at 168 MHz while every timing number you own assumes 180. In every one of those cases the
evidence is a register value, a meter reading or an analyzer capture that exists for as long as you
are looking at it, and afterwards there is nothing at all.

**So the capture is doing a second job here.** In Stage 0 it was for the write-up. In Stage 1 it is
also how you tell later whether you actually fixed the thing or merely changed something and watched
the symptom move — which, with three silent failure modes in one session, is a real question.

Keep the ones that surprised you. The debugger halted on `<optimized out>`, the 60 Ω that read 120,
the two boards both announcing node 15.

---

## The board decision, made

Stage 1 runs on the **Nucleo-F446RE**. Here is the reasoning, so you can disagree with it on purpose
rather than by drift.

You own two ESP32-S3 boards, and on paper they are the cheaper path: each has two PCNT units that
decode quadrature in hardware, plus a native TWAI (CAN) controller. Two boards is four hardware
joints and a working bus for zero additional spend.

**Buy the Nucleo anyway.** Three reasons:

1. **It is the resume item.** STM32 with HAL and CubeMX is the dominant toolchain in medical devices
   and aerospace — the two fields you are aiming at. ESP32 is consumer IoT. The chips are comparable;
   the ecosystems are not, and it is the ecosystem that appears in job postings.
2. **The debugger.** The Nucleo has an ST-Link built onto the board. Setting a breakpoint, halting the
   processor, and inspecting a variable is the single largest quality-of-life jump between hobby and
   professional embedded work, and it is the thing most people skip because print statements feel
   sufficient. S1.1 exists entirely to make you do it.
3. **The visible layers.** CubeIDE puts `startup_stm32f446xx.s`, the vector table, and the `.ld`
   linker script in folders you can open. The question "how does the chip know to run my code" gets a
   visible answer. This is rung 4 of Interlude D's ladder, and the ESP-IDF hides more of it.

It is roughly **C$28 from DigiKey**, part **497-15882-ND** — check current pricing and stock before you
order. Do not buy a Nucleo on AliExpress — clone boards ship counterfeit
silicon and non-functional ST-Link, and debugging a fake chip as your introduction to STM32 is how
people quit.

**Record the choice in `docs/decisions/` before you order, not after.** The
reasoning above is somebody else's and the point of the first sentence in this section is that you
should be able to disagree with it on purpose — which is only possible if you write down what you
weighed. The ESP32-S3 is genuinely the cheaper path and it has two real jobs in this project; say
why the Nucleo won anyway, and what that cost you.

### What the ESP32-S3s are actually for

They are not spare parts. They have two defined jobs:

- **The bus monitor in S1.6.** One ESP32-S3 plus a transceiver running a receive-everything sketch is
  your budget CAN analyzer. It shows you frames on the wire, which is most of early bus debugging,
  and it costs nothing.
- **Joints three and four, later.** Once your protocol is defined and proven, a cheap node that
  speaks it is exactly what you want. The protocol is the artifact; the silicon underneath it is an
  implementation detail. Proving that by running a mixed-vendor bus is a genuinely good thing to be
  able to say.

---

## What to order before you start

**C$60 minimum, or C$146 with every optional item.** This is **Tier C** of *What's Left to Buy* — the
same list, and if the two ever disagree, that document is the one that gets corrected. The Nucleo is
the only part that must come from a real distributor.

| Item | Qty | Est. | Where | Note |
|---|---|---|---|---|
| **STM32 Nucleo-F446RE** | 1 | **C$28** | **DigiKey Canada** | Part 497-15882-ND — check current pricing. Free shipping over C$100, C$15 below that, so bundle the rest of this list in. DigiKey Canada ships DDP, so no customs exposure. |
| SN65HVD230 CAN transceiver module | 4 | C$12 | AliExpress | 3.3 V logic, correct for STM32. Buy spares; they are C$3. |
| Twisted pair / CAT5 offcut | 2 m | C$10 | local | Untwisted ribbon works on a bench and then fails next to a motor. |
| JST-XH 4-pin connectors | 1 set | C$10 | AliExpress | For a daisy-chainable joint bus. |
| 120 Ω resistors | — | **owned** | — | You bought 100 of them. Two get used. |
| Second gearmotor | — | **owned** | — | You bought two N20s. This is why. |
| Second TB6612FNG | — | **owned** | — | You bought five. |
| MCP2515 + TJA1050 CAN module | 2 | *C$8* | AliExpress | **Optional.** 5 V, SPI. Lets you prototype CAN framing on an UNO you already understand. |
| Second Nucleo-F446RE | 1 | *C$28* | DigiKey | **Optional.** The alternative to using an ESP32-S3 as the second node in S1.6. |
| **CANable 2.0** | 1 | *~C$50* | Openlight Labs | **Optional, and a real decision** — see the box below. Not AliExpress. |

**C$60 for the four required lines. C$146 with all three optional ones** — 60 + 8 + 28 + 50. Both
figures are the Tier C subtotals, and the optional items are the reason the second number is more
than twice the first.

> **WATCH OUT** — **Decide about the CANable before you order.** A CANable 2.0 (~US$36, from Openlight
> Labs or an authorised reseller, **not** AliExpress) plugs into your host and gives you socketCAN,
> `candump`, and `cansend`. It is the comfortable path and you will probably want it eventually. But
> socketCAN does not exist in a stock WSL2 kernel — **buying a CANable moves your native Ubuntu
> install from a Stage 2 deadline to a Stage 1 one.** Either buy it and install Ubuntu now, or use
> the ESP32-S3 monitor and defer. Both are legitimate. Pick one deliberately and write it in
> `docs/decisions/`.

---

## The standing pin map

| Function | Nucleo pin | Peripheral | Why |
|---|---|---|---|
| Encoder A | **PA0** | `TIM2_CH1` | TIM2 is **32-bit** on this chip — the encoder counter effectively never wraps. |
| Encoder B | **PA1** | `TIM2_CH2` | Same timer, channel 2. Hardware quadrature needs both. |
| Motor PWM | **PA8** | `TIM1_CH1` | Advanced timer on APB2. APB2 runs at 90 MHz, but the timer kernel clock is doubled to **180 MHz** whenever the APB2 prescaler is not 1 — which it is not, at 180 MHz system clock. Plenty of resolution at 20 kHz. |
| `AIN1` / `AIN2` | **PB4 / PB5** | GPIO | Direction. |
| `STBY` | **PB10** | GPIO | Same trap as Stage 0. Drive it high. |
| CAN TX / RX | **PB9 / PB8** | `CAN1` | bxCAN. Note this chip has CAN1 *and* CAN2 — you use CAN1. |
| Node ID jumpers | **PC0–PC3** | GPIO in, pull-up | Four bits, giving node IDs 1–15. |
| Loop-rate scope pin | **PC8** | GPIO | Same job as Stage 0's D5. |
| Debug UART | **PA2 / PA3** | `USART2` | Wired to the ST-Link's virtual COM port. Free serial over the same USB cable. |
| **I²C (INA219)** | **PB6 / PB7** | `I2C1` | SCL / SDA. Needed from S1.8. **Not** the Arduino-header default — see the trap below. |

> **WATCH OUT** — **The obvious I²C pins are already gone, and you will not find out until S1.8.** On a
> Nucleo-64 the Arduino-header I²C pins D15/D14 are **PB8/PB9** — which this pin map has assigned to
> `CAN1_RX`/`CAN1_TX`. Any tutorial or shield that assumes "I²C is on D15/D14" will collide with your
> CAN bus. The other obvious alternates are gone too: PB10 is `STBY`, and PA8 (an `I2C3_SCL` option)
> is your motor PWM. **PB6/PB7 for `I2C1` is free and is the right answer** — assign it in CubeMX now,
> in this session, rather than discovering the collision two sessions later with a transceiver and a
> current sensor on the bench at the same time.

> **WATCH OUT** — **PB4 is `NJTRST`.** It is available as ordinary GPIO when the debug interface is set to
> **SWD only**, which is CubeIDE's default for a Nucleo and what you want anyway. If you ever switch
> the project to full JTAG, PB4 stops being yours and `AIN1` silently dies. Set Debug = *Serial Wire*
> in CubeMX and leave it there.

> **DEFINITION** — **On the STM32F446, TIM2 and TIM5 are 32-bit; TIM3 and TIM4 are 16-bit.** (TIM1 and TIM8
> are the advanced-control timers and are also 16-bit.) A 16-bit encoder counter wraps every 65,536
> counts, which on your motor is about 7.8 output revolutions — provisional, since it is 65,536
> divided by your still-unmeasured counts-per-revolution.
> Handling that wraparound correctly is fiddly and a classic source of a robot that works for a
> minute. Using a 32-bit timer makes the problem disappear, and knowing *why* you chose that timer is
> the kind of answer that lands well in an interview.

---

# PART I — THE CHIP

---

## S1.0 · CubeIDE, and the shape of a generated project

**Goal:** STM32CubeIDE installed, updated, and a generated project you can navigate.

**You will be able to:** point at the file that runs before `main()`, the file that decides where your code lives in memory, and the file that holds your peripheral configuration — and say what each does. Arduino had all three and never showed you them.

### Concept

Arduino hid five things from you: that your sketch was not C++, that `main()` existed and you did not
write it, that the core was a hardware abstraction layer, that startup code and a linker script
existed, and that peripherals were configured on your behalf.

CubeMX hides exactly one of those — the peripheral configuration — and it hides it in a folder you
can open. Everything else is now visible. This is not a harder environment. It is the same
environment with the lid off.

### Build

Generate a project for the Nucleo-F446RE, board-selector mode, default peripheral initialisation.
Then **read the tree before you write anything**:

| File | What it is |
|---|---|
| `Core/Src/main.c` | Your `main()`. Note it is real, and note the `USER CODE BEGIN/END` fences. |
| `Core/Startup/startup_stm32f446retx.s` | The assembly that runs before `main` — zeroes `.bss`, copies `.data` from flash to RAM, sets the stack pointer. |
| `STM32F446RETX_FLASH.ld` | The linker script. Where code and variables live in the address space. |
| `Drivers/STM32F4xx_HAL_Driver/` | ST's HAL. The same category of thing as the Arduino core — a portable convenience layer over registers. |
| `mimic_joint.ioc` | The CubeMX configuration. **Commit this.** Regenerating from it is how you avoid hand-editing generated code. |

> **DEFINITION** — **Bare metal, the vector table, and the linker script.** **Bare metal** means your code
> runs directly on the processor with no operating system underneath it — there is no scheduler, no
> memory protection, and nothing to catch you. Everything in Stage 0 was bare metal; you just could
> not see the edges. The **vector table** is an array of function addresses at the very start of
> flash: the processor reads entry 0 to find its initial stack pointer, entry 1 to find the reset
> handler, and one entry per interrupt source thereafter. That is the literal, physical answer to
> "how does the chip know to run my code." The **linker script** (`.ld`) is the file that decides where
> everything lands in the address space — where flash starts, where RAM starts, where the stack grows
> from, where the vector table sits. Arduino had all three; it simply never showed them to you.

> **WATCH OUT** — Code you write outside the `USER CODE BEGIN/END` fences is **deleted** the next time you
> regenerate from the `.ioc`. This catches everyone once, usually at 1 a.m., usually after an hour of
> good work. The discipline: configuration changes happen in CubeMX, logic lives inside the fences or
> in your own files.

### What will go wrong

- **The first build takes twenty minutes and then fails on a missing toolchain.** CubeIDE downloads
  its compiler and device firmware pack on first use. This is not broken; it is slow. Let it finish
  before you conclude anything.
- **You picked the chip instead of the board.** Selecting `STM32F446RET6` from the MCU selector gives
  you a bare chip with nothing configured — no LD2 on PA5, no ST-Link UART on PA2/PA3, no HSE from
  the ST-Link MCO. Use the **Board Selector** and pick `NUCLEO-F446RE`, and answer *yes* when it
  offers to initialise peripherals to their default mode.
- **The debugger cannot find the target.** Usually the ST-Link firmware is older than the IDE. There
  is an updater inside CubeIDE (*Help → ST-Link upgrade*); run it once and forget it.
- **Your edits vanished.** You wrote outside the `USER CODE` fences and regenerated. There is no
  recovery other than your Git history, which is the actual argument for committing before every
  regeneration.
- **`.ioc` changes do not appear.** Regeneration is not automatic on build. Save the `.ioc`, then
  answer the "generate code?" prompt, then build.

**Capture the broken state.** Nothing for the site — this session's `Site:` line is `nothing` and
that stands. But screenshot it for yourself the first time you write code outside the `USER CODE`
fences and regenerate it away. It happens to everyone once, it will happen to you at 1 a.m. after an
hour of good work, and a screenshot of the file with your hour missing is the cheapest possible way
to never do it again.

### Draw this

**The memory map, from the linker script, on half a page.** Open `STM32F446RETX_FLASH.ld`, find the
`MEMORY` block, and draw the two regions to scale as vertical bars: 512 KB of flash and 128 KB of RAM,
with their start addresses written on. Then mark where each section lands — `.text` and `.rodata` in
flash, `.data` and `.bss` in RAM, the stack growing *down* from the top of RAM and the heap up from
below it.

Beside it, draw the UNO's: 32 KB and 2 KB. Same drawing, same axes, and the two bars next to each other
are the whole reason Stage 1 feels roomy. Then answer one question on the page: **what happens when the
stack grows down far enough to meet your variables?** Nothing tells you, on either chip. That is the
corruption Interlude E warns about, and now you have seen the geometry of it.

### Look it up yourself — four documents, not one

This chip does not have "a datasheet." It has four documents, and the reason people describe STM32 as
overwhelming is that they go looking in the wrong one and conclude the information does not exist.
Download all four now — **into `docs/reference/`, committed, where Git LFS already tracks PDFs** —
and never search the internet for an STM32 fact again. That folder is for exactly this: material you
fetched from somebody else, as opposed to `docs/derivations/`, which is material in your handwriting.
Write the revision letter and date inside each file as you save it, because `RM0390` Rev 6 and Rev 4
do not agree everywhere and "the reference manual says" is not a citation without one.

| Document | What is in it | You will want it in |
|---|---|---|
| **Datasheet** `STM32F446xC/E` | Pinout, package, absolute maximums, electrical characteristics, and the **alternate function table** — which peripheral each pin can become | S1.2, and any time you change the pin map |
| **Reference manual** `RM0390` | Every peripheral, every register, every bit. ~1,300 pages, and you will read four of them | S1.3, S1.6 |
| **Board user manual** `UM1724` | The Nucleo-64 *board*: which chip pin reaches which header, the solder bridges, what the ST-Link does, where the 8 MHz comes from | S1.2, S1.6 |
| **Errata** `ES0298` | The ways this silicon does not match its own datasheet | The day something is impossible |

Answer three questions from them before you go on, writing the document and section beside each:

1. **From the datasheet's alternate-function table:** confirm that PA0 really can be `TIM2_CH1`, and
   find which alternate-function number that is. The standing pin map asserts it; go and verify it.
2. **From `UM1724`:** where does the 8 MHz `HSE` on this board actually come from? It is not a crystal,
   and knowing what it *is* explains why a Nucleo with its ST-Link section snapped off will not run.
3. **From `RM0390`'s `TIM2` chapter:** find the encoder-mode section and read the one table that says
   what counts on which edges. You need it in S1.3, and finding it yourself takes four minutes with
   the PDF search.

> **CHECK YOURSELF** — Which of the four documents would tell you the maximum current a single GPIO pin
> can source? Which would tell you how to configure that pin as an output? They are different
> documents, and being able to say which is which without opening either is the skill.

### Prove it

- The project builds and flashes, and LD2 responds to a change you made.
- You can open `startup_stm32f446retx.s`, find the reset handler, and point at the line that calls
  `main`. You do not need to understand the assembly — you need to have seen that it exists.
- You can open the `.ld` file and find the two numbers that say where flash starts and how big RAM is.
  Compare them to the UNO's 32 KB / 2 KB and notice what just happened to your constraints.
- The `.ioc` is committed, and you have made one change in CubeMX, regenerated, and confirmed your
  hand-written code inside the `USER CODE` fences survived.

That last one is the whole session. Do it deliberately, once, now — rather than discovering the
regeneration rule at 1 a.m. in S1.6.

### Artifacts

- **`docs/sessions/cubeide-project/README.md`** — written at the end of the session, not the
  start. Three to five bullets on what actually happened, what the objective did not predict,
  and what you got wrong first. See [the template](../sessions/_TEMPLATE.md).
- `firmware/stage1-stm32/` in the repo, `.ioc` committed.
- An ADR in `docs/decisions/` — Nucleo vs ESP32-S3, and what the ESP32s are for instead.
- **Site:** nothing yet. Generated-project tours do not photograph well and this session is scaffolding. Noted so its absence is a decision rather than an oversight.
  **The shot:** nothing.

---

## S1.1 · Blink, and the breakpoint that is the actual point

**Goal:** an LED blinking from generated code, and — the real deliverable — the processor halted on a
breakpoint with a variable's value visible in a watch window.

**You will be able to:** halt a running processor, read a variable out of memory, and look at the actual bit in the actual register that drives a pin — and say why that is categorically different from a print statement rather than just more convenient.

### Concept

The LED is a formality. The debugger is the milestone.

Everything you did in Stage 0 was debugged by printing. Printing is universal, coarse, and it changes
timing — which occasionally makes the bug move, and that is a genuinely maddening experience. A
hardware debugger over SWD stops the processor mid-instruction and lets you look at memory. Nothing
about the program's timing changes because the program is not running.

Analogy: the difference between asking someone to describe a room over the phone, and walking into it.

### Build

1. Blink LD2 (on **PA5**) with `HAL_GPIO_TogglePin` and `HAL_Delay`.
2. Set a breakpoint inside the loop. Run under the debugger. Confirm it halts.
3. Add a counter variable. Add it to the watch window. Step over the increment and watch the number
   change.
4. Open the peripheral register view and look at `GPIOA->ODR` while the LED is on and off. In
   CubeIDE that view is **Window → Show View → SFRs**, and it is not open by default — which is why
   most people never find it. Expand `GPIOA`, find `ODR`, and watch bit 5.

That fourth step is the one that makes the abstraction concrete: you are looking at the actual bit
in the actual register that the actual pin is wired to.

### What will go wrong

- **The breakpoint never seems to hit.** It is hitting, several hundred times a second, and the IDE is
  resuming faster than you can see. Put the breakpoint after `HAL_Delay`, or make the delay a second,
  or watch the counter rather than the LED.
- **Your variable shows `<optimized out>`.** The compiler removed it because nothing observable reads
  it. Either use it for something, or build the Debug configuration rather than Release — and notice
  what just happened, because it will happen again in Stage 2 when a value you are printing is fine and
  the same value in the debugger is not.
- **The debugger connects, then drops on the first step.** Usually the ST-Link firmware is older than
  the IDE. *Help → ST-Link upgrade*, once.
- **You single-step into HAL and get lost in someone else's code.** Step *over*, not into. Stepping
  into a HAL call is occasionally instructive and mostly a way to spend twenty minutes in
  `stm32f4xx_hal_gpio.c`.

**Capture the broken state.** The watch window showing your counter as `<optimized out>`. Screenshot
it. It is a one-word failure that teaches something real — that the compiler removed a variable
nothing observable reads — and it comes back in Stage 2 as a value that prints fine and cannot be
inspected.

### Draw this

**The path from `HAL_GPIO_TogglePin` to the pin, as a stack.** Four or five boxes: your call, the HAL
function, the register write, the GPIO peripheral, the physical pad. Beside each, write what it costs —
roughly ten cycles for the HAL call, one for the register write.

Then draw the *same* stack for `digitalWrite` on the UNO from Interlude D, with its ~50 cycles. Two
stacks, side by side. That drawing is the answer to "what does an abstraction layer cost", it is a
question you will be asked, and having drawn it once means the answer is a picture rather than a
recollection.

> **CHECK YOURSELF** — With the LED on, `ODR` bit 5 is 1. Toggle it *by typing a new value into the
> register view* rather than by running code, and watch the LED change. If you can do that, you have
> understood that `HAL_GPIO_TogglePin` is a convenience over a memory write and nothing more — which is
> the entire content of this session.

> **CHECK YOURSELF** — If you have not personally halted the processor and read a variable out of memory,
> you have not finished this session. There is no version of Stage 1 where skipping this saves you
> time. The rest of the stage assumes you can stop and look.

### Prove it

Not "the LED blinks." Four things, and the LED is not one of them:

1. The processor is **halted** on a breakpoint — not paused by a delay, halted, with the IDE showing
   the source line it stopped on.
2. A variable's value is visible in the watch window and **changes when you step over the line that
   changes it**.
3. `GPIOA->ODR` bit 5 in the SFR view matches the LED's actual state.
4. You changed that bit **by hand in the register view** and the LED followed.

### Artifacts

- **`docs/sessions/debugger/README.md`** — written at the end of the session, not the
  start. Three to five bullets on what actually happened, what the objective did not predict,
  and what you got wrong first. See [the template](../sessions/_TEMPLATE.md).
- Screenshot of the debugger halted with the watch window visible.
- **Site:** that screenshot. It is a small thing and it marks the boundary between hobby and
  professional tooling.
  **The shot:** one screenshot of the whole IDE window at full resolution — not a crop, and not a
  photo of the monitor. **Four things visible at once:** the source line it is halted on, the call
  stack, the watch window with your counter's value in it, and the SFR view with `GPIOA->ODR`
  expanded and bit 5 showing. If you must crop, keep the watch window and `ODR`; they are the two
  that make the claim.

---

## S1.2 · The clock tree, and why 180 MHz is not automatic

**Goal:** you can state your system clock, your APB1 and APB2 bus clocks, and your timer clocks — and
you know where each number came from.

**You will be able to:** derive a PLL configuration from an 8 MHz reference against its documented constraints, state what your timers are counting at as distinct from what their bus runs at, and name the two things that must happen before this chip will run at 180 MHz at all.

### Concept

On the UNO there was one clock: 16 MHz, from a crystal, forever. On an STM32 there is a *tree*: an
oscillator feeds a PLL, the PLL feeds the core, and prescalers divide that down to a set of
peripheral buses each with its own maximum. Get it wrong and everything still runs — just at a
different speed than you believe, which means every timing calculation downstream is quietly wrong.

This is the same class of bug as Stage 0's "my loop is running at half the rate I think." Same
lesson, one layer down.

> **DEFINITION** — **The four words in every clock tree.** **HSE** is the *high-speed external* oscillator —
> the reference the chip trusts. On a Nucleo it is not a crystal on your board at all; it is an 8 MHz
> square wave the ST-Link chip generates and feeds across (the MCO output), which is why removing the
> ST-Link section of a Nucleo breaks the clock. **HSI** is the *high-speed internal* RC oscillator,
> always present, always slightly wrong — around ±1 %, which is fine for blinking and not fine for
> CAN. The **PLL** (*phase-locked loop*) is a frequency multiplier: it divides HSE down to a low
> reference, multiplies that up to a high internal frequency, and divides the result back down to
> what you asked for. **AHB** is the fast bus the core and memory sit on; **APB1** and **APB2** are
> slower peripheral buses hanging off it, each with its own divider and its own hard maximum. Every
> number in the figure below is one of those five things.

```
FIGURE S1.2.1 — The F446 tree, and the three numbers the rest of Stage 1 uses

   8 MHz HSE
   (from ST-Link MCO)
        │
        ▼
   ┌─────────┐   /M      ×N        /P
   │   PLL   │  ────►  VCO  ────►  SYSCLK = 180 MHz
   └─────────┘                        │
                                      │  AHB prescaler /1
                                      ▼
                                  HCLK = 180 MHz ──► core, DMA, SysTick
                                      │
                     ┌────────────────┴────────────────┐
              /4     ▼                                 ▼   /2
          APB1 = 45 MHz                            APB2 = 90 MHz
          (max 45)                                 (max 90)
              │                                         │
              ├──► TIM2  (32-bit, encoder)              ├──► TIM1 (motor PWM)
              ├──► CAN1  ◄── bit timing derives         │
              │            from 45 MHz — see S1.6       │
              └──► USART2, I2C1                         │
                                                        │
   TIMER KERNEL CLOCK RULE — the one people miss:
   when an APB prescaler is NOT 1, that bus's timers are clocked at 2× the
   bus. So TIM2 runs at 90 MHz (2 × 45) and TIM1 at 180 MHz (2 × 90),
   even though the buses are 45 and 90.

   Three numbers to write on tape:  SYSCLK 180 · APB1 45 · APB2 90
```

### The math — derive your own tree

The STM32F446RE runs at **up to 180 MHz**. The buses have hard limits:

```
SYSCLK   ≤ 180 MHz
APB1     ≤  45 MHz    (TIM2-7, TIM12-14, USART2, I2C, CAN1, CAN2, SPI2/3)
APB2     ≤  90 MHz    (TIM1, TIM8-11, USART1/6, SPI1/4)
```

So with SYSCLK at 180 MHz, APB1 needs a ÷4 prescaler and APB2 a ÷2.

**Now derive the PLL itself, because CubeMX will fill these in and you should be able to check it.**
The PLL has three dividers and two hard constraints: its input (after ÷M) must land between 1 and
2 MHz, and its VCO output (after ×N) must land between 100 and 432 MHz.

```
VCO input  = HSE / M      must be 1–2 MHz   (ST recommend exactly 2)
VCO output = VCO input × N   must be 100–432 MHz
SYSCLK     = VCO output / P

From the 8 MHz HSE:
   M = 4    →  8 / 4        = 2 MHz      ✓ at the recommended value
   N = 180  →  2 × 180      = 360 MHz    ✓ inside 100–432
   P = 2    →  360 / 2      = 180 MHz    ✓ SYSCLK
```

Several M/N pairs reach 360 MHz (5/225, 6/270, 8/360 all work), but **M = 4, N = 180, P = 2** puts
the VCO input at exactly 2 MHz, which is the value ST recommend for lowest jitter. Write those three
numbers down; they are the only part of the tree that is genuinely a choice.

> **WATCH OUT** — **Two things must happen before this chip will run at 180 MHz, and CubeMX does them
> silently.** Neither is optional and neither is visible unless you go looking.
>
> **1. Over-Drive mode.** The F446's internal regulator has to be pushed into a higher-voltage state
> before the core can be clocked above 168 MHz. The sequence is: enable the power-controller clock,
> select voltage scale 1, then set `ODEN` in `PWR_CR` and wait for `ODRDY`, then set `ODSWEN` and
> wait for `ODSWRDY` — and only then switch SYSCLK onto the PLL. In HAL terms that is one call,
> `HAL_PWREx_EnableOverDrive()`, sitting in `SystemClock_Config()` between the oscillator setup and
> the clock switch. Delete it and the chip does not fail loudly; it fails to reach 180 MHz, and every
> timing number in this workbook is then wrong by 168/180.
>
> **2. Five flash wait states.** Flash memory cannot keep up with a 180 MHz core. The chip inserts
> wait states to compensate, and at 180 MHz on a 3.3 V board that number is **5**
> (`FLASH_LATENCY_5`), passed as the second argument to `HAL_RCC_ClockConfig()`. Too few and you get
> hard faults that move around when you change unrelated code — the single most unpleasant class of
> bug on this chip.
>
> Open `SystemClock_Config()` in `main.c` and find both. They are four lines apart and they are the
> entire price of admission to 180 MHz.

> **WATCH OUT** — **180 MHz costs you the USB clock.** USB full-speed needs exactly 48 MHz, derived from
> the PLL's Q divider — and with the VCO at 360 MHz there is no integer Q that gives 48 (360/48 =
> 7.5). On the F446 the way out is the separate PLLSAI, selected as the 48 MHz source. This does not
> affect you, because your serial goes over the ST-Link's virtual COM port rather than the chip's own
> USB peripheral — but if you ever wonder why CubeMX turns the USB clock red at 180 MHz, that is why,
> and it is a genuine trade-off rather than a bug.

Now the rule that catches people:

> **DEFINITION** — **Timer clock doubling.** When an APB prescaler is greater than 1, the timers on that
> bus are clocked at **twice** the bus frequency. So with APB1 at 45 MHz (÷4), TIM2 is clocked at
> **90 MHz**, not 45. With APB2 at 90 MHz (÷2), TIM1 is clocked at **180 MHz**. This is documented,
> non-obvious, and responsible for an enormous number of PWM frequencies that come out exactly 2×
> wrong.

**Your PWM period, derived.** For 20 kHz PWM on TIM1 at 180 MHz, with prescaler 0 (÷1):

```
ARR = f_timer / f_pwm − 1
    = 180,000,000 / 20,000 − 1
    = 8,999
```

That gives you **9,000 discrete duty steps** instead of the UNO's 256. Roughly 35× the command
resolution, for free, because you configured the timer yourself instead of accepting `analogWrite`.

### Draw this

Your own clock tree, by hand, on one page — not a copy of the figure above. Start at the 8 MHz HSE and
write your actual M, N and P at the PLL, your actual SYSCLK, both APB prescalers, and both bus
frequencies. Then, at every timer you intend to use, write **two** numbers: the bus frequency and the
timer kernel frequency, so the doubling rule is visible rather than remembered. Mark the Over-Drive
and flash-latency requirements next to SYSCLK. Photograph it and put it next to the bench.

The test of this drawing is that you can answer "what is TIM2 counting at?" from the page, without
opening CubeMX. If you cannot, the drawing is incomplete.

### What will go wrong

- **Everything runs, and every frequency is wrong by a constant.** CubeMX defaulted to HSI rather than
  HSE. Check the clock-source radio button first; the tree looks identical either way.
- **CubeMX refuses to accept 180 MHz.** Voltage scaling is not on Scale 1, or Over-Drive is unticked.
  It will offer to resolve the conflict for you — read what it proposes rather than clicking through.
- **Hard faults that move when you add a `printf`.** Flash latency too low for the clock you chose.
- **PWM comes out at 10 kHz instead of 20, or 40 instead of 20.** The timer clock doubling rule, in
  one direction or the other. Recompute `ARR` from the *kernel* clock, not the bus clock.

**Capture the broken state.** The analyzer reading 10 kHz or 40 kHz where you expected 20. Save the
capture with the expected figure written on it. The timer kernel clock doubling rule catches people
twice — here, and again on TIM6 in S1.4 — and a saved capture of it catching you the first time is
what makes the second one take four minutes instead of an evening.

### Prove it

**Put the clock itself on a pin. This is the primary check, not the fallback**, and it is worth being
clear about why the obvious alternative does not work.

Toggling a GPIO in a tight loop looks like a clock measurement and is not one. The period you measure
is set by how many instructions the loop body compiles to, how the optimiser arranged them, and whether
you called a HAL function or wrote the register — none of which you control precisely, and all of which
change between builds. It tells you the chip is alive and roughly how fast. It cannot tell you whether
SYSCLK is 180 MHz or 168, which is exactly the failure this session exists to catch.

So: **MCO2 on PC9**, not MCO1. Two reasons, and both are worth
knowing rather than working around. **One: MCO1 cannot source SYSCLK.** Its four inputs on the F446
are HSI, LSE, HSE and PLLCLK — SYSCLK is an **MCO2** source. (You could select PLLCLK on MCO1 and get
the same waveform, because in this configuration SYSCLK *is* the PLL output; say it that way if you
do.) **Two: MCO1's pin is PA8, and PA8 is already `TIM1_CH1` — your motor PWM** — in the standing pin
map two pages up. MCO2 on PC9 is free. Divide by 4 or 5 to keep the output inside what your 24 MHz
analyzer can sample.

Then measure the actual PWM frequency on the analyzer. It should read 20.0 kHz. If it reads 10 or 40,
revisit the doubling rule.

A GPIO toggled in a tight loop is still worth doing as a thirty-second "is it alive" check — just do
not mistake it for a measurement of the core clock.

> **CHECK YOURSELF** — Predict the MCO2 reading before you look at it. You are dividing SYSCLK by 4 or
> 5 to stay inside your 24 MHz analyzer, so write down the number you expect to see. Then answer the
> question the session actually turns on: **if `HAL_PWREx_EnableOverDrive()` had been deleted, what
> would that reading be?** The arithmetic is one division and it is the difference between finding this
> class of fault in an evening and finding it in Stage 2.

### Artifacts

- **`docs/sessions/clock-tree/README.md`** — written at the end of the session, not the
  start. Three to five bullets on what actually happened, what the objective did not predict,
  and what you got wrong first. See [the template](../sessions/_TEMPLATE.md).
- `docs/derivations/clock-tree.jpg` — the tree, hand-drawn, with your numbers at every node.
- Analyzer capture confirming 20.0 kHz.
- **Site:** the hand-drawn clock tree. Almost nobody shows one, and a page with your own M, N and P on it — plus the two numbers at every timer — says you configured this chip rather than accepted a wizard's defaults.
  **The shot:** one still of the page, square on. Every node needs its number readable, and at
  each timer **both** numbers — the bus frequency and the kernel frequency — because the doubling
  rule being visible is the entire reason this drawing is worth showing.

---

## S1.3 · Hardware quadrature — the encoder that costs no CPU

**Goal:** TIM2 in encoder mode, counting your encoder in hardware, with your control loop doing
nothing but reading a register.

**You will be able to:** explain what a timer in encoder mode does in silicon that your Stage 0 ISR did in software, and prove the two agree by measuring the same counts per revolution twice on two different chips.

### Concept

In Stage 0 you computed, with real numbers, that your encoder was generating 14,000 interrupts per
second and consuming about 7 % of the UNO's CPU. That was a fine thing to do once, because it taught
you interrupt discipline and it taught you what a quadrature decoder actually does.

You are never doing it again. STM32 general-purpose timers contain a quadrature decoder in silicon.
You point it at two pins, and thereafter reading the shaft position is `TIM2->CNT`. Zero interrupts.
Zero CPU.

Analogy: you have been counting cars at an intersection by hand with a clicker. Someone points out
there is a traffic counter buried in the road.

### The math — what changes, and what does not

`TIM_ENCODERMODE_TI12` counts every edge on both channels — **this is ×4 decoding**, the same thing
you implemented in software. Your counts-per-revolution constant from Stage 0 carries over unchanged:

```
COUNTS_PER_OUTPUT_REV = <your measured figure>     ← the same number, still
```

That it carries over unchanged is a **test**. If the STM32 reads a different count per revolution
than the UNO did, one of the two is not doing ×4, and you want to know which before you tune anything.

Two new things to handle:

1. **Sign.** The hardware counts up in whichever direction it counts up. Same rule as Stage 0: verify
   empirically, and if it is backwards, fix it in one clearly marked place.
2. **The counter is unsigned.** `TIM2->CNT` is a `uint32_t` counting 0 → 4,294,967,295 → 0. Cast to
   `int32_t` and the arithmetic works out for both directions, and with 32 bits you would need about
   511,000 output revolutions to wrap (2³² ÷ 8,400 — recompute with your measured figure). Do the
   arithmetic yourself and satisfy yourself that this is true.

### Code — skeleton

```c
/* encoder.h — S1.3 */
#ifndef MIMIC_ENCODER_H
#define MIMIC_ENCODER_H
#include "stm32f4xx_hal.h"

typedef struct {
  TIM_HandleTypeDef *htim;   /* the timer in encoder mode */
  int32_t offset;            /* set by homing, Stage 2 */
  int8_t  sign;              /* +1 or -1, decided empirically */
} Encoder;

void    Encoder_Init(Encoder *e, TIM_HandleTypeDef *htim);
int32_t Encoder_Counts(const Encoder *e);   /* signed, offset- and sign-corrected */
float   Encoder_Rad(const Encoder *e);
void    Encoder_Zero(Encoder *e);

#endif
```

Note what is absent: no ISR, no volatile, no transition table, no `noInterrupts()`. That is the
entire point of the session.

### Draw this

**The two decoders, side by side, as what actually happens per edge.** Left: Stage 0. An edge arrives,
the AVR pushes registers, enters the ISR, reads a port, indexes a table, adds, restores, returns —
draw each step as a box and write the microseconds on it. Right: Stage 1. An edge arrives and a counter
in silicon changes. One box.

Underneath, write both CPU costs: 7 % of an AVR against 0 % of an STM32. **That drawing is the artifact
for this session** — it is one page, it needs no explanation, and it says something measured rather than
claimed.

### Prove it

> **CHECK YOURSELF** — Before you turn it: predict what the STM32 will read for ten revolutions. It is
> the same motor and the same encoder, so there is only one defensible answer, and committing to it is
> what makes the next paragraph a *test* rather than a measurement. If the two chips disagree, one of
> them is not doing ×4 — and the failure list below tells you what a factor of four and a factor of two
> each mean.

Turn the shaft ten revolutions by hand. Confirm you get the same counts-per-revolution figure you
measured in Stage 0. Then spin the motor at full speed under open-loop command and confirm the count
is still exact — this is where software decoding on a slower chip would start dropping edges and
hardware decoding simply does not.

### What will go wrong

- **The count never changes.** The timer is running but not in encoder mode, or only one channel is
  mapped. In CubeMX, TIM2's *Combined Channels* must be set to **Encoder Mode**, not to two separate
  input captures — and you must call `HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL)`. Starting
  `TIM_CHANNEL_1` alone gives you a decoder with one eye shut.
- **The count changes by a quarter of what Stage 0 measured.** You are in `TIM_ENCODERMODE_TI1` or
  `TI2`, which count one channel's edges only. `TIM_ENCODERMODE_TI12` is the ×4 mode.
- **It counts the wrong way.** Expected, and the fix is the same discipline as Stage 0: change it in
  exactly one place. Either invert one channel's polarity in the timer configuration, or set
  `Encoder.sign = -1`. Pick one, comment it, and never compensate a second time downstream.
- **It counts backwards only sometimes, near zero.** You are reading `TIM2->CNT` into a signed
  variable without casting, so 4,294,967,295 is being read as four billion rather than as −1.

  **The fix, concretely.** `TIM2->CNT` is a `uint32_t`. Start it at zero, turn the shaft backwards one
  count, and the register holds `0xFFFFFFFF` — which as an unsigned number is four billion and as a
  *signed* 32-bit number is exactly −1. So read it and cast the whole value: `int32_t counts =
  (int32_t)(__HAL_TIM_GET_COUNTER(&htim2));` and the arithmetic works in both directions with no
  wraparound handling at all. That is the whole fix, and it is one cast rather than a difference —
  **taking differences is what you would need on a 16-bit timer**, which is the reason the pin map
  chose a 32-bit one. If you find yourself writing wraparound logic here, you are solving a problem
  this pin choice already removed.
- **The count is right by hand and drifts under power.** Not a decoder problem. That is the Stage 0
  100 nF at the motor terminals, missing — hardware decoding does not make noise go away, it just
  stops charging you CPU time for it.

**Capture the broken state.** The debugger showing `TIM2->CNT` as 4,294,967,295 while the shaft is
one count below zero. Screenshot the register view. That single number is the entire argument for
the cast, it is far more convincing than the sentence explaining it, and it is a genuinely pleasant
thing to be able to point at.

### Artifacts

- **`docs/sessions/hardware-quadrature/README.md`** — written at the end of the session, not the
  start. Three to five bullets on what actually happened, what the objective did not predict,
  and what you got wrong first. See [the template](../sessions/_TEMPLATE.md).
- `docs/tuning/hardware-vs-software-encoder.md` — both counts-per-rev figures, and the fact that they
  agree.
- **Site:** worth one sentence. "Moved quadrature decoding from a software ISR consuming 7 % of an
  AVR to a hardware peripheral consuming none" is a very legible improvement.
  **The shot:** one sentence and one still: the side-by-side drawing of the two decoders with `7
  %` and `0 %` written on it. The sentence quotes the measured figures; the drawing is why they
  are different.

---

## S1.4 · The control loop in C, on bare metal

**Goal:** your Stage 0 controller, ported to STM32, running from a timer interrupt at 1 kHz, with
identical behaviour.

**You will be able to:** explain why a control loop belongs in a timer interrupt rather than in a polled superloop, and demonstrate that gains tuned at one rate on one chip transfer unchanged to another rate on another chip — which is a claim about your arithmetic, not about your tuning.

### Concept

The controller does not change. The scheduling does.

On the UNO you polled `micros()` in `loop()` and returned early when it was not time yet. That works
and it is imprecise — your tick happens whenever the superloop gets around to checking. On an STM32
you configure a timer to fire an interrupt at exactly your control period, and the control loop *is*
the interrupt handler. It runs at the right time because the hardware makes it, not because your code
remembered to.

Analogy: Stage 0 was you glancing at a clock between chores and starting the next one when you noticed
the hour had come. This is an alarm. You are not more punctual because you are trying harder; you are
punctual because something else is keeping time and it interrupts you.

### The math — a real loop rate, finally

Stage 0 *started* at 100 Hz because `analogWrite()` gave you 490 Hz PWM, and finished at 500 Hz once
S11 reconfigured Timer1 to 31 kHz. That constraint is gone entirely here:

```
PWM:  20 kHz  (S1.2)
Loop: 1 kHz   → 20 PWM periods per control tick. Comfortable.
dt = 0.001 s
```

**Your gains should transfer.** `Kp` is dimensionless in command-per-radian and does not care about
rate. `Ki` and `Kd` are defined in terms of `dt`, so if your implementation multiplies and divides by
`dt` correctly, going from your Stage 0 exit rate of 500 Hz to 1 kHz changes nothing about the tuned
behaviour. (Nor did 100 Hz to 500 Hz, which you already proved in S11 — this is the same test, one
more time, across a change of chip as well as a change of rate.) Test this first, before you retune
anything — if the gains do *not* transfer, you have a `dt` bug in one of the
two implementations and finding it now is cheap.

One thing genuinely does *not* improve: derivative noise. From Stage 0, velocity quantisation was
`1 count / dt`. At 1 kHz that is ten times larger per tick than at 100 Hz — **worse**, not better.
Higher rate means finer time resolution and coarser velocity resolution. If your derivative gets
noisier after the port, that is why, and the answer is the same low-pass filter, retuned.

> **DEFINITION** — **The NVIC.** The *nested vectored interrupt controller* is the block on every
> Cortex-M that decides which interrupt runs, and when. Three things about it differ from the AVR you
> came from. It is **vectored**: each source has its own entry in the vector table, so there is no
> dispatch code to write. It is **prioritised**: you assign each interrupt a numeric priority, and —
> confusingly — **lower numbers mean higher priority**. And it is **nested**: a higher-priority
> interrupt can pre-empt one already running. That last point is the real change. On the AVR, entering
> an ISR disabled interrupts globally, so an ISR was automatically atomic with respect to every other
> ISR. On Cortex-M it is not, and "my ISR was interrupted" becomes a thing that can happen to you.
> This is also the mechanism the RTOS is built on: FreeRTOS runs the scheduler out of the lowest
> priority exception, which is why your control-loop interrupt can still be exactly on time while the
> scheduler is doing something else.

> **WATCH OUT** — Do not do heavy work in the timer ISR. Your control loop is short and bounded, which is
> why it belongs there. Telemetry formatting, floating-point printing, and anything that blocks do
> not. Set a flag in the ISR and let the main loop do the slow parts — which is the argument that S1.5
> is about to make properly.

### The math — the timer that makes the tick

You need a spare timer interrupting at exactly 1 kHz. **TIM6** is the conventional choice on this part
— it is a basic timer, it does nothing but count and interrupt, and it is not `TIM2` (your encoder) or
`TIM1` (your PWM). It sits on APB1.

Derive its two numbers the same way you derived `ARR` for the PWM in S1.2, and notice that the timer
kernel clock rule applies here too:

```
TIM6 kernel clock = 2 × APB1 = 90 MHz          (APB1 prescaler is not 1)

You need 1 kHz. One divider is not enough range on a 16-bit timer, so use both:

   f_tick = f_kernel / ((PSC + 1) × (ARR + 1))

   PSC = 89   →  90 MHz / 90        =  1 MHz counting rate  (1 µs per count)
   ARR = 999  →  1 MHz / 1000       =  1 kHz                ✓

Both fields hold one less than the number you mean — the same N−1 rule as
ARR in S1.2 and, in two sessions' time, every field in CAN_BTR.
```

Choosing a 1 µs counting rate rather than some arbitrary split is deliberate: `PSC` sets the resolution
of anything else you ever do with this timer, and 1 µs is a number you can reason about. Write down why
you chose the split you chose.

> **CHECK YOURSELF** — If you had put this on **TIM3** instead, would `PSC = 89` still give you 1 µs?
> Answer from your clock-tree drawing, not from CubeMX. Then answer the harder one: what if you had put
> it on a timer hanging off **APB2**?

### Code — skeleton

```c
/* control.c — S1.4 */
#include "stm32f4xx_hal.h"
#include "encoder.h"
#include "pid.h"

#define DT_S  0.001f            /* 1 kHz. Must match the TIM6 arithmetic above. */

static Encoder        enc;
static PIDController  pid;
static volatile JointState state;   /* written here, read by main. See S1.5. */

/* HAL calls this for EVERY timer that interrupts. There is exactly one of
   these functions in the whole program, so it must ask which timer called it
   — this is the single most common reason a second timer silently does
   nothing, or does the wrong thing. */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance != TIM6) return;        /* not ours */

  HAL_GPIO_WritePin(SCOPE_GPIO_Port, SCOPE_Pin, GPIO_PIN_SET);   /* tick start */

  /* SENSE  — one register read, no ISR, no volatile, no table. That is S1.3. */
  /* TODO: float pos_rad = Encoder_Rad(&enc); */

  /* THINK  — the same PIDController you wrote in Stage 0, in C.
     TODO: float u = PID_Update(&pid, target_rad, pos_rad, DT_S); */

  /* ACT    — write the compare register. Sign selects direction on the two
     GPIOs, magnitude sets duty.
     TODO: __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, duty_from(u)); */

  /* TODO: publish state for the telemetry path. In S1.5 this stops being a
           plain struct write and becomes the session's whole problem. */

  HAL_GPIO_WritePin(SCOPE_GPIO_Port, SCOPE_Pin, GPIO_PIN_RESET); /* tick end */
}
```

Three things the skeleton deliberately does not tell you:

1. **Starting the timer.** Generating the peripheral is not the same as running it. There is one call,
   and if you omit it everything compiles and nothing ever ticks. Find it — the name is unsurprising.
2. **`duty_from(u)`.** `u` is a clamped ±1.0 fraction, exactly as in Stage 0. `ARR` for the PWM timer
   is 8,999. The conversion is one line and it is the same chain as FIGURE III.S6.1, one layer along.
3. **Direction.** Two GPIOs, the same `AIN1`/`AIN2` truth table you looked up in the TB6612 datasheet
   in Stage 0 S1. Write it as one function that takes a signed command, not as sign tests scattered
   through the ISR.

### Draw this

**The tick, as a timeline, on half a page.** Draw one 1 ms period. Mark where TIM6 fires, where your
handler starts and ends, and — this is the part worth drawing — how much of the period is left over.
Then mark, above the same timeline, where a `TIM2` encoder edge might land, and satisfy yourself that
it does not matter, because hardware quadrature does not interrupt at all.

Underneath, draw the same period as it looked in Stage 0: a superloop, a polled comparison, and the
tick starting *whenever the loop came round*. The two drawings next to each other are the whole
difference between the two stages, and the second one is why S1.5 is about to be necessary.

### What will go wrong

- **Nothing ticks at all.** The timer was configured and never started, or its NVIC interrupt is not
  enabled in CubeMX. Two separate checkboxes, and missing either produces the same silence.
- **It ticks at half or twice the rate you expect.** The kernel-clock doubling rule, again — you sized
  `PSC` against the APB1 bus frequency rather than against the timer's clock. This is the same failure
  as S1.2's PWM and it will not feel familiar the second time.
- **A second timer interrupt does nothing, or fires your control loop.** You did not check
  `htim->Instance`. One callback serves every timer, and the default behaviour of forgetting that is
  either "my new timer is dead" or "my control loop now runs twice as often", depending on which one
  you added.
- **A hard fault the moment the ISR does floating-point maths.** The FPU is not enabled in the project
  settings. It is a build-configuration checkbox, not a code problem, and the fault will point at a
  perfectly innocent line.
- **`HAL_Delay` inside the handler locks the chip.** `HAL_Delay` waits on the HAL tick, and the HAL
  tick is an interrupt at lower or equal priority that can never run while you are inside this one.
  There is no delay in a control loop, ever — but people put one in to "slow it down and see."
- **The gains do not transfer and you retune them.** Stop, and read the paragraph above again. That is
  a `dt` bug in one of your two implementations and you have just been handed it for free.

**Capture the broken state.** The scope pin ticking at half or twice 1 kHz, captured before you go
back to the clock tree. Save it beside your S1.2 drawing — the drawing predicted a number and the
capture disagreed with it, and that pairing is worth keeping precisely because the drawing turned
out to be the reliable one.

### Prove it

- Same step response as Stage 0, same gains, at 1 kHz. Plot both on the same axes.
- Scope pin toggled in the ISR, measured at exactly 1.000 ms — and the *high* time measured too, so you
  know your headroom before S1.5 starts spending it.

### Artifacts

- **`docs/sessions/bare-metal-loop/README.md`** — written at the end of the session, not the
  start. Three to five bullets on what actually happened, what the objective did not predict,
  and what you got wrong first. See [the template](../sessions/_TEMPLATE.md).
- Overlay plot: UNO at 100 Hz vs STM32 at 1 kHz, same gains.
- **Site:** that overlay. It is a claim that your code is dimensionally correct, and those are rare.
  **The shot:** one plot, both traces on one set of axes, with a legend naming the chip and the
  rate for each — `UNO, 100 Hz` and `STM32, 1 kHz` — and the gains printed once. Without the
  legend it is two indistinguishable curves.

---

# PART II — TIME, SHARED

---

## S1.5 · FreeRTOS — two tasks, and the demonstration that justifies it

**Goal:** a 1 kHz control task and a slow telemetry task coexisting, with proof that the slow one
cannot damage the fast one.

**You will be able to:** explain what pre-emption buys you that a superloop cannot give you, produce the analyzer capture that proves it, and name four ways to move data between two tasks and defend the one you chose.

### Concept

A superloop runs everything in one sequence, so the slowest thing in the loop sets the pace for
everything. Add a function that occasionally takes 8 ms and your 1 kHz control loop is now
occasionally a 125 Hz control loop, and your carefully tuned gains mean something different for those
8 milliseconds.

A pre-emptive scheduler solves this by letting a high-priority task interrupt a low-priority one
mid-execution. The control task runs when it is time, regardless of what else was happening.

Analogy: a superloop is a single-lane road where an ambulance queues behind a truck. A scheduler is a
road with a hard shoulder the ambulance is allowed to use.

```
FIGURE S1.5.1 — The demonstration you must actually produce

    SUPERLOOP — telemetry blocks the control loop
                      ├── 8 ms telemetry write ──┤
    ┌─┐      ┌─┐      ┌─────────────────────────┐ ┌─┐      ┌─┐
    │C│      │C│      │        TELEMETRY        │ │C│      │C│
    └─┘      └─┘      └─────────────────────────┘ └─┘      └─┘
    ├──1 ms──├──1 ms──├──────── 8 ms gap ───────┤ ├──1 ms──┤
                                  ↑
    eight control deadlines missed here, silently
  
    PRE-EMPTIVE RTOS — control task at higher priority
    ┌─┐      ┌─┐      ┌─┐      ┌─┐      ┌─┐      ┌─┐      ┌─┐
    │C│      │C│      │C│      │C│      │C│      │C│      │C│        prio HIGH
    └─┘      └─┘      └─┘      └─┘      └─┘      └─┘      └─┘
        ┌──┐     ┌──┐     ┌──┐     ┌──┐     ┌──┐     ┌──┐
    ├──1 ms──├──1 ms──├──1 ms──┤ telemetry is chopped up and runs in the gaps
  

  BOTH HALVES SHARE ONE TIME AXIS: a control tick is 9 columns in each, so
  you can lay a finger across and compare. The one distortion is deliberate —
  the 8 ms telemetry block is drawn about three times narrower than true
  scale, because at 9 columns per millisecond it would be 72 columns wide and
  would not fit. Read the LABEL for the duration and the PITCH for the rate.

  PROVE IT ON THE ANALYZER, not in prose: toggle PC8 at the top of the
  control task and measure the period spread with telemetry off, then on.
  Superloop: the spread blows out. RTOS: it does not. That capture is the
  artifact — it is the whole argument for the RTOS in one screenshot.
```

### The build — do it in this order, because the demonstration is the point

1. Enable FreeRTOS in CubeMX (CMSIS-RTOS v2 interface). While you are there, set **HAL's timebase
   source to TIM6** — see the first failure below, because this one stops everything dead.
2. Create `ControlTask` at high priority, period 1 ms. CMSIS-RTOS v2 priorities are an **enum, not a
   number**: `osPriorityLow`, `osPriorityNormal`, `osPriorityHigh`, `osPriorityRealtime` and the
   variants between them. Give the control task `osPriorityRealtime` or `osPriorityHigh` and note that
   — unlike the NVIC, where lower numbers win — **a numerically higher CMSIS priority is the more
   urgent one.** Two priority schemes, opposite conventions, in one project. Write that down somewhere
   you will see it again.
3. Create `TelemetryTask` at low priority — `osPriorityLow` — period 20 ms.
4. **Deliberately break it.** Put a 5 ms busy-wait inside the telemetry task. A busy-wait, not
   `osDelay` — the point is to occupy the CPU, and `osDelay` yields it.
5. **Measure the control task's period on the analyzer while telemetry is stalling.** It should still
   be 1.000 ms.
6. Now make them equal — set both tasks to `osPriorityNormal` — and measure again. Watch the control
   period develop 5 ms gaps. (Setting priorities equal is the cleaner experiment than turning
   `configUSE_PREEMPTION` off in the FreeRTOS config, because it changes exactly one thing.)

Step 6 is the session. Seeing the failure you are being protected from, once, is worth more than a
chapter of theory about why RTOSes exist.

> **DEFINITION** — **Priority inversion.** A high-priority task waits on a resource held by a low-priority
> task, which is itself pre-empted by a medium-priority task — so the high-priority task effectively
> runs at the medium priority. It is the classic RTOS failure, it took down the Mars Pathfinder
> mission, and the standard mitigation is priority inheritance on mutexes. You are unlikely to hit it
> with two tasks. Know the name; it comes up in interviews.

### The problem you have just created — two tasks, one set of numbers

The control task produces joint state. The telemetry task consumes it. Nothing in the build above
says how the number gets from one to the other, and the obvious answer — a global `JointState` that
one writes and the other reads — is broken in a way that will not announce itself.

```
FIGURE S1.5.2 — The torn read, one layer up from Stage 0

  JointState is sixteen bytes. ControlTask writes it at 1 kHz;
  TelemetryTask reads it at 50 Hz. Neither operation is a single
  instruction, and the scheduler may switch between any two of them.

  ControlTask (HIGH)                 TelemetryTask (LOW)
  ──────────────────                 ───────────────────
                                     reads pos   = 1000   ◄── tick N
                                     reads vel   = 0.00   ◄── tick N
       ◄──── pre-empts ───────────────────┤  (suspended mid-read)
  writes pos   = 2000                     │
  writes vel   = 3.14                     │
  writes flags = FAULT                    │
       ───── yields ──────────────────────►
                                     reads flags = FAULT  ◄── tick N+1

  Telemetry now transmits position 1000 alongside a fault flag that was
  raised a millisecond later. That state never existed on the machine.
  Nothing crashed, nothing logged an error, and the only evidence is a
  point on a plot that is not physical.

  This is Stage 0's torn read exactly — a multi-byte value read across a
  boundary you do not control. There the boundary was an ISR and the fix
  was noInterrupts(). Here it is a context switch, and noInterrupts() is
  no longer the right tool.
```

> **DEFINITION** — **Context switch.** The scheduler saving one task's registers and stack pointer,
> loading another's, and jumping into it. It can happen between any two machine instructions, which is
> the entire source of the problem above — your C statement `state.pos = x;` may be three instructions,
> and "between any two instructions" includes those.

**Four standard fixes. You should be able to name all four and defend the one you chose.**

| Fix | What it does | What it costs |
|---|---|---|
| **Critical section** — `taskENTER_CRITICAL()` / `taskEXIT_CRITICAL()` | Masks interrupts for the duration of the copy. The direct descendant of Stage 0's `noInterrupts()`. | Blocks *everything*, including your control loop. Acceptable for a sixteen-byte copy, indefensible for anything longer. Keep it to a handful of instructions or not at all. |
| **Mutex** — `xSemaphoreCreateMutex()` | Only tasks wanting the same data wait. FreeRTOS mutexes carry priority inheritance, which is the mitigation for the inversion defined above. | Your high-priority control task can now **block** — the exact thing you adopted an RTOS to prevent. A control loop that can wait on a lock held by telemetry no longer has a worst-case period you can state. |
| **Queue** — `xQueueSend()` / `xQueueReceive()` | Copies the data into the kernel. There is no shared memory left, so there is nothing to exclude anyone from. | One copy per message, and a fixed-size buffer you have to size. |
| **Double buffer** | Two `JointState` buffers; the writer fills the spare and publishes it by overwriting a single aligned pointer, which is atomic on Cortex-M. | Lock-free and never blocks, and the easiest of the four to get subtly wrong. The reader may hold a buffer that is one tick stale. |

**For a producer/consumer pair like this one, the queue is usually the right answer,** and it is worth
being able to say why rather than just doing it — in `docs/decisions/`,
because "name all four and defend the one you chose" is a decision record in every respect and the
constraint that decides it is the one you adopted an RTOS to get:

- The control task must never wait. `xQueueSend(q, &state, 0)` with a zero timeout **cannot** block —
  if the queue is full it returns a failure code and the control loop carries on. No other option
  gives you that guarantee for free.
- The data is copied, so every question about who owns what and for how long simply stops existing.
- A full queue is *information*. Count the failed sends and you have measured the fact that telemetry
  cannot keep up — a real number, discovered early, instead of a mystery later.
- For "latest state wins" telemetry, a length-1 queue with `xQueueOverwrite()` is exactly the right
  shape: the reader always gets the most recent sample and never a backlog of stale ones.

> **DEFINITION** — **Mutex, semaphore, and why they are not the same thing.** A **mutex** protects a
> resource: it has an owner, only the owner may release it, and the kernel can temporarily raise that
> owner's priority so a waiting high-priority task is not held up by a medium-priority one. A
> **semaphore** is a counter used for signalling — "an event happened," or "there are three buffers
> free" — and it has no owner, so anyone may give it. Using a binary semaphore where you meant a mutex
> compiles, runs, looks correct, and silently discards priority inheritance. That is the classic
> version of the Pathfinder bug, and it is why FreeRTOS provides both types separately.

### Code — skeleton, the queue

The four fixes above are the design decision; this is the twenty lines that implement the one you
should choose. Note how little there is to it — that is the argument.

```c
/* joint_state_queue.c — S1.5 */
#include "cmsis_os2.h"

/* A length-1 queue used as a "latest value wins" mailbox. Telemetry does not
   want a backlog of stale samples; it wants the most recent one. */
static osMessageQueueId_t stateQ;

void StateQueue_Init(void)
{
  /* TODO: create a queue of 1 element, each sizeof(JointState).
           osMessageQueueNew(...) — three arguments, and the third can be NULL. */
}

/* Called from ControlTask at 1 kHz. MUST NOT BLOCK. */
void StateQueue_Publish(const JointState *s)
{
  /* TODO: send with a timeout of 0 so a full queue returns an error
           instead of waiting. Count the failures — see below. */
}

/* Called from TelemetryTask at 50 Hz. May block; it has nothing better to do. */
bool StateQueue_Take(JointState *out, uint32_t timeout_ms)
{
  /* TODO: receive, returning false on timeout. */
}
```

Three things to work out rather than be told:

1. **The timeout argument is the whole safety property.** Find the constant that means "do not wait at
   all" and use it on the publish side. If the control task can ever block on this call, you have
   given back the guarantee you adopted an RTOS to get.
2. **Count the failed publishes.** A full queue is not an error to swallow, it is a measurement:
   telemetry cannot keep up, and the count tells you by how much. Put that counter in your telemetry.
3. **A length-1 queue overflows constantly by design** — you publish at 1 kHz and read at 50 Hz, so 19
   of every 20 sends fail. That is correct behaviour for "latest wins", and it means the counter in
   point 2 needs a different interpretation here than it would on a length-32 queue. Decide which
   shape you want and write down why. CMSIS-RTOS v2 has no direct equivalent of FreeRTOS's
   `xQueueOverwrite`, so if you want strict latest-wins semantics you either drain-then-send or drop to
   the native FreeRTOS API — and choosing deliberately between those is the exercise.

> **LOOK THIS UP** — Read the FreeRTOS documentation's own pages on *Queue Management* and *Mutexes and
> Binary Semaphores* before you implement this. They are short, they are written by the people who
> wrote the kernel, and the mutex page states the semaphore-versus-mutex distinction above more
> precisely than any tutorial will. Read them *after* you have drawn the failure in FIGURE S1.5.2 for
> yourself, so you are looking for a solution to a problem you already understand.

### Draw this

**Predict FIGURE S1.5.1 before you measure it.** Two timelines on one page, drawn by hand: what you
think the control task's period will look like with pre-emption on, and what you think it will look
like with the two tasks at equal priority. Mark where you expect the telemetry stall to land and what
you expect it to do to the tick either side of it.

Then take the two analyzer captures and put them beside your drawing. **The value is entirely in
having committed to a prediction first** — if the captures match, you understand the scheduler, and if
they do not, you have found the more interesting result and you should chase it before moving on.

Underneath, draw the torn read from FIGURE S1.5.2 as a timeline of your own: two columns, the moment
of pre-emption marked, and the specific bytes that are stale. Then mark on it where each of the four
fixes would go. That drawing is what makes the choice between them an argument rather than a
preference.

### The math — stack sizing, and why it bites

Each task gets its own stack, sized by you, in words. Too small and it silently overflows into
whatever is next in memory, producing corruption that looks like anything at all.

```
Control task: locals + float maths + HAL call depth  →  start at 512 words (2 KB)
Telemetry:    string formatting is stack-hungry      →  start at 512 words (2 KB)
```

Enable `configCHECK_FOR_STACK_OVERFLOW` and write the hook. Then use
`uxTaskGetStackHighWaterMark()` to see how much each task actually used, and size down with evidence
rather than guessing. Record the numbers.

> **WATCH OUT** — `printf` and `sprintf` with `%f` pull in a large, stack-hungry formatting routine. On a
> 2 KB task stack this can overflow on its own. If your telemetry task starts behaving strangely the
> moment you print a float, this is the first thing to check — and the fix is the same as Stage 0's:
> send integers, convert on the host.

### What will go wrong

- **Nothing runs at all after enabling FreeRTOS.** The default CubeMX FreeRTOS configuration puts
  SysTick under the kernel's control while HAL also wants it. Set HAL's timebase source to a spare
  timer — **TIM6** is the conventional choice and you are not using it — in *System Core → SYS →
  Timebase Source*. CubeMX warns about this and the warning is easy to click past.
- **One task runs and the other never does.** Your high-priority task never blocks. A task that spins
  instead of calling `osDelay()` or waiting on a queue starves everything below it, and that is not a
  scheduler bug, it is the scheduler working. Every task must have a blocking call in its loop.
- **Random corruption that changes when you add a variable.** Stack overflow. Turn on
  `configCHECK_FOR_STACK_OVERFLOW` (level 2) and write the hook so it traps loudly instead of
  corrupting quietly. Then check high-water marks rather than guessing.
- **It works until you print a float.** `printf` with `%f` needs far more stack than the rest of the
  task put together. Either raise that task's stack deliberately and record why, or send integers.
- **`osDelay(1)` gives you something other than 1 ms.** The tick rate is
  `configTICK_RATE_HZ`, and a delay is quantised to it. At the default 1000 Hz a 1 ms delay is one
  tick, which means it is somewhere between just-under and just-over 1 ms. For a 1 kHz control loop
  this is exactly why the loop belongs on a hardware timer interrupt (S1.4) and not on `osDelay`.

**Capture the broken state.** The equal-priority capture — the control period developing 5 ms gaps.
**This is the more valuable of the two captures this session asks for**, and it is the one you can
only take by deliberately breaking something that already works. The flat 1.000 ms trace is a claim;
the two side by side are a demonstration, and nobody who has only ever run the working configuration
can produce the pair.

### Prove it

Two analyzer captures: control task period with telemetry stalling under pre-emption (flat 1 ms), and
without it (5 ms gaps). Side by side.

### Artifacts

- **`docs/sessions/freertos-tasks/README.md`** — written at the end of the session, not the
  start. Three to five bullets on what actually happened, what the objective did not predict,
  and what you got wrong first. See [the template](../sessions/_TEMPLATE.md).
- The two captures, and `docs/tuning/rtos-preemption.md` with the stack high-water marks.
- **Site:** the two captures. This is the clearest possible visual answer to "why does an RTOS
  matter," and most people who list FreeRTOS on a resume have never produced it.
  **The shot:** two analyzer captures at the same time base, stacked vertically rather than side
  by side, so the 5 ms gaps in the lower one line up against the flat trace above. Label which is
  which on the image.

---

# PART III — THE BUS

---

## S1.6 · CAN, physically — two nodes and a counter

**Goal:** two boards, one twisted pair, and a number arriving at the other end. Nothing else.

**You will be able to:** derive a CAN bit timing from a bus clock and a target rate rather than copying it, explain what a sample point is and why it sits late in the bit, and diagnose a silent bus from the meter reading across it.

### Concept

CAN is not addressed like I²C. There are no device addresses. Every node hears every frame, and each
frame carries an **identifier** that describes *what the message is*, not who it is for. Nodes filter
in hardware for the identifiers they care about.

The identifier is also the priority. When two nodes transmit simultaneously, the one with the
numerically lower identifier wins, and — this is the elegant part — the loser detects the collision
and backs off without any data being corrupted or any time being lost. That is **arbitration**, and
it is why CAN is used where timing guarantees matter.

Analogy: a room where everyone can hear everyone, and there is an agreed rule that if two people
start talking at once, the one discussing the more urgent topic continues and the other stops
mid-word and waits.

### The math — bit timing, derived

This is the calculation nobody explains and everybody copies from a forum post. Do it yourself once.

bxCAN is on **APB1, which you clocked at 45 MHz** in S1.2. A CAN bit is divided into **time quanta**,
and one bit is `SYNC_SEG (always 1) + BS1 + BS2` quanta.

Target: **500 kbit/s**, sample point near **87.5 %** (the CiA recommendation).

```
Bit time = 1 / 500,000 = 2 µs

Pick total quanta per bit, then solve for the prescaler:
  15 tq →  prescaler = 45,000,000 / (15 × 500,000) = 6      ← integer. Use this.
  16 tq →  prescaler = 45,000,000 / (16 × 500,000) = 5.625  ← not an integer. Reject.

With prescaler = 6:  t_q = 6 / 45 MHz = 133.3 ns
                     15 × 133.3 ns = 2.00 µs ✓

Split the 15 quanta for an 87.5 % sample point:
  BS1 = 12, BS2 = 2   →  sample at (1 + 12) / 15 = 86.7 %   ✓ close enough
  SJW = 1
```

So: **prescaler = 6, BS1 = 12 tq, BS2 = 2 tq, SJW = 1 tq.** Enter those in CubeMX and know why.

> **WATCH OUT** — **Every one of those four numbers is stored in the register as one less than you just
> derived, and CubeMX hides the subtraction.** The bxCAN `CAN_BTR` register holds `BRP = prescaler − 1`,
> `TS1 = BS1 − 1`, `TS2 = BS2 − 1` and `SJW = SJW − 1`, because a field of zero has to mean a divider
> of one — there is no such thing as dividing by zero. So the four values you typed into CubeMX as
> **6, 12, 2, 1** appear in the silicon as **5, 11, 1, 0**. Check that they still add up — the
> arithmetic is immediately below this box.

```
bit time = 1 (SYNC_SEG) + (TS1 + 1) + (TS2 + 1)
         = 1 + (11 + 1) + (1 + 1)
         = 15 tq                              ✓ matches the derivation
```

> **WATCH OUT, continued** — This matters the moment you read the register back in the debugger to
> check your work, or port the configuration to a chip whose tool does *not* do the subtraction for
> you. It is the same class of off-by-one as `ARR = N − 1`, which this workbook flags explicitly in
> S1.2 — and it is worth internalising the general rule rather than the two instances: **when a
> hardware field configures a divider or a count, expect the register to hold one less than the number
> you mean.**

> **DEFINITION** — **The sample point** is where in the bit the receiver decides whether it saw a 1 or a 0.
> Late in the bit is better, because signal reflections and propagation delay have had time to settle.
> Every node on the bus must agree on the bit rate; they should also roughly agree on the sample
> point, and nodes that disagree badly produce a bus that works between some pairs of devices and not
> others.

### The math — bus load, so you know your budget

A standard CAN data frame with 8 payload bytes is 111 bits (1 SOF + 11 ID + RTR + IDE + r0 + 4 DLC
+ 64 data + 15 CRC + CRC delimiter + ACK slot + ACK delimiter + 7 EOF + 3 IFS — add them up). Bit
stuffing applies to the 98 bits from SOF through CRC and can insert at most `⌊(98 − 1) / 4⌋ = 24`
extra bits. So the true worst case is **135 bits**, not the 130 commonly quoted:

```
FIGURE S1.6.1 — Where 111 bits comes from, field by field

  ├────────────── stuffed region: 98 bits ──────────────┤├── not stuffed ───┤

  ┌───┬──────────┬───┬───┬───┬──────┬──────────┬────────┬─┬─┬─┬───────┬─────┐
  │SOF│ ID       │RTR│IDE│r0 │ DLC  │ DATA     │ CRC    │D│A│D│  EOF  │ IFS │
  │ 1 │   11     │ 1 │ 1 │ 1 │  4   │   64     │  15    │1│1│1│   7   │  3  │
  └───┴──────────┴───┴───┴───┴──────┴──────────┴────────┴─┴─┴─┴───────┴─────┘
    1  +   11   + 1 + 1 + 1 +   4  +    64    +   15   +1+1+1+   7   +  3
                                                                 = 111 bits

  D = CRC delimiter · A = ACK slot · D = ACK delimiter

  The four acronyms in the middle, since you are about to redraw them:
    RTR  remote transmission request — 0 for a normal data frame
    IDE  identifier extension — 0 for the 11-bit standard format you use
    r0   reserved, always dominant, kept for a future that never came
    DLC  data length code — 4 bits saying how many payload bytes follow

  ACK is the one worth understanding rather than memorising: the TRANSMITTER
  sends it recessive, and any RECEIVER that liked the frame overwrites it
  dominant. That is why a single node talking to itself never succeeds, and
  it is the first failure in the list below.

  Bit stuffing: after 5 identical consecutive bits the transmitter inserts
  one opposite bit. Worst case over N stuffable bits is ⌊(N−1)/4⌋:

        ⌊(98 − 1) / 4⌋  =  ⌊24.25⌋  =  24 stuff bits

        111 + 24 = 135 bits worst case      ← use this, not 130

  At 500 kbit/s:  135 / 500,000 = 270 µs per frame.
```

```
Frame time at 500 kbit/s = 135 / 500,000 = 270 µs

Planned traffic for four joints:
  4 joints × 1 state frame  @ 100 Hz =  400 frames/s
  4 joints × 1 diag frame   @ 100 Hz =  400 frames/s
  Host    × 4 command frames @ 100 Hz =  400 frames/s
                                      = 1,200 frames/s

Bus load = 1,200 × 270 µs = 324 ms/s = 32 %
```

Under the 50 % rule of thumb, with room for the emergency stop to arbitrate instantly. **Do this
calculation before you design the protocol in S1.7, not after** — it is what tells you whether your
intended publish rates are affordable.

### Build

1. Two nodes: the Nucleo, and either the second Nucleo (if you bought one) or an ESP32-S3 with a
   transceiver, or an UNO with the MCP2515 module.
2. **SN65HVD230** transceivers — 3.3 V, correct for STM32. `CTX`/`CRX` to PB9/PB8.
3. **Twisted pair** between the two `CANH`/`CANL` pairs.
4. **120 Ω at each physical end of the bus. Only the two ends.**
5. Send an incrementing counter from one. Print it on the other.

Nothing else. No motor. Debugging bus problems and control problems simultaneously is miserable and
entirely avoidable.

> **WATCH OUT** — Two termination mistakes account for most beginner CAN failures: a resistor on every
> node instead of only the two ends, and no termination at all because it worked on the bench with
> short wires. Both produce intermittent, distance-dependent behaviour. **Power off, meter across
> CANH–CANL: you should read about 60 Ω** — two 120 Ω resistors in parallel. Any other reading and
> your termination is wrong. Do this measurement every time you add a node.

### Draw this

Two drawings, both by hand, both on one page.

**The frame.** Redraw FIGURE S1.6.1 from the field widths rather than by copying the picture: SOF, the
11 identifier bits, RTR, IDE, r0, the 4 DLC bits, your payload, CRC, the three delimiter/ACK bits, EOF
and IFS. Add them up yourself and confirm you land on 111. Then mark the stuffed region — SOF through
the end of the CRC sequence, and **not** the CRC delimiter, which is where this is most often drawn
wrong — and write `⌊(98 − 1)/4⌋ = 24` beside it.

**The bit.** Underneath, draw one bit time as a strip of 15 boxes: one SYNC_SEG, twelve for BS1, two
for BS2. Mark the sample point at the boundary between BS1 and BS2 and write the percentage. Then
write both sets of numbers next to it — the four you type into CubeMX and the four that end up in the
register — because that pair is the thing you will want in front of you when the bus does not work.

### What will go wrong

- **Nothing arrives, and nothing errors.** The commonest cause by far: the transmitter never leaves
  initialisation because it cannot see a single acknowledgement. CAN requires *another node* to ACK,
  so a single node talking to itself will retry forever. Check the other end is powered and running
  before you suspect anything subtle. If you must test one node alone, bxCAN has a loopback mode —
  use it deliberately, and remember you are then testing the controller, not the wire.
- **Both nodes are alive and the bus is silent.** Bit-rate mismatch. Both ends must agree exactly, and
  a node clocked from HSI instead of HSE can be 1 % out, which is enough. This is the first thing to
  check and the last thing people check.
- **CANH and CANL swapped.** The bus does not work at all, and no error tells you why. Meter them:
  idle recessive should sit both lines at about 2.5 V, and dominant should push CANH up and CANL down.
- **It works with two nodes on the desk and fails when you add the third.** Termination. Power off,
  meter across CANH–CANL, expect ~60 Ω. Anything else and you have too many resistors or too few.
- **Error counters climb and the node goes quiet on its own.** That is bus-off, and it is correct
  behaviour — a node that has produced too many errors removes itself so it cannot take the bus down.
  Read `CAN_ESR` for the transmit and receive error counters and the last error code; that register is
  where the diagnosis lives, and it is worth printing it in your telemetry from the start.

**Capture the broken state.** The meter reading anything other than about 60 Ω across CANH–CANL.
Photograph the display with the bus visible behind it. 120 Ω with a terminator missing, or 40 with
one too many, is the fastest diagnostic you own for the rest of the project, and a photo of the
wrong reading is what makes the right one mean something.

### Prove it

> **CHECK YOURSELF** — Before you power anything: predict the meter reading across CANH–CANL with both
> nodes wired and both terminators fitted. Then predict it with one terminator removed. Two numbers,
> ten seconds, and they are the fastest diagnostic you own for the rest of this project — the point of
> predicting them is that you will meter this bus dozens of times and you want to know instantly when
> the reading is wrong.

Counter arriving intact. Then pull one termination resistor and watch it degrade — do this
deliberately, once, so you recognise the symptom later.

### Artifacts

- **`docs/sessions/can-physical-layer/README.md`** — written at the end of the session, not the
  start. Three to five bullets on what actually happened, what the objective did not predict,
  and what you got wrong first. See [the template](../sessions/_TEMPLATE.md).
- `docs/derivations/can-bit-timing.jpg` — your bit timing arithmetic.
- `docs/tuning/can-bus-load.md` — the load calculation with your actual planned rates.
- Photo of the meter reading 60 Ω.
- **Site:** the bit-timing derivation beside the 60 Ω meter photo. Paper and instrument, same page — it is physical-layer competence in two images and it is rare in a portfolio.
  **The shot:** two stills. The derivation page square on, with the four CubeMX numbers and the
  four register numbers both readable — the pair is the point. And the meter, close enough to read
  the digits, with the twisted pair and both terminators visible behind it so it is obviously
  *this* bus.

---

## S1.7 · Designing the joint protocol — paper before keyboard

**Goal:** a written message specification you could hand to someone else, in `docs/protocol.md`.

**You will be able to:** justify the width of every field in a message you designed, explain why your emergency stop has the identifier it has, and say what a message *type* is and why it is not the same number as the identifier.

### Concept

You get **eight bytes** per standard CAN frame. That constraint is a gift, because it forces you to
decide what actually matters rather than serialising a struct and moving on.

This is design work. It deserves an afternoon with paper before an afternoon with a keyboard, and it
is the single most interview-relevant thing in Stage 1 — not because CAN is hard, but because
"I designed a protocol and here is why each field is the width it is" is a conversation almost no
portfolio can support.

### The starting scheme

Encode both message type and node into the 11-bit standard identifier, so hardware filtering is cheap:

```
bits 10..4 : message type
bits  3..0 : node id (1..15; 0 is reserved and means BROADCAST)

identifier = (type << 4) | node
```

```c
typedef enum {
  MSG_ESTOP   = 0x01,   /* type 0x01, node 0 (broadcast) -> identifier 0x010.
                           Lowest identifier on the bus = wins arbitration. */
  MSG_COMMAND = 0x10,   /* host -> joint : target, mode */
  MSG_STATE   = 0x20,   /* joint -> host : position, velocity */
  MSG_DIAG    = 0x30,   /* joint -> host : current, temperature, faults */
} MsgType;

typedef struct {          /* exactly 8 bytes */
  int32_t  target_counts; /* 4 */
  uint16_t vel_limit;     /* 2 */
  uint8_t  mode;          /* 1 : idle / position / hold */
  uint8_t  seq;           /* 1 : detect dropped frames */
} CommandFrame;
```

### The decisions you have to make, and record

None of these have a single right answer. Write four sentences per decision in `docs/decisions/`.

| Decision | The tension |
|---|---|
| **Do joints publish autonomously, or does the host poll?** | Autonomous is simpler and uses constant bus bandwidth. Polling is deterministic and scales worse. |
| **What rate does state publish at?** | Faster is better feedback and more bus load. Your S1.6 budget says what you can afford. |
| **What is the sequence number for?** | Detecting dropped frames. But then — what do you *do* when one skips? Ignore, log, or fault? |
| **How does a joint signal it has faulted?** | A flag in the state frame, or a dedicated frame, or both? |
| **What are the units on the wire?** | Counts are exact and encoder-specific. Milliradians are portable and lossy. Pick one and justify it. |
| **Endianness?** | It does not matter until the day a different chip joins the bus, and then it matters enormously. Write it down. |

> **DEFINITION** — **The message type and the identifier are two different numbers, and this is where
> people conflate them.** `MSG_ESTOP = 0x01` is the *type*. Push it through the layout above and the
> identifier is `(0x01 << 4) | 0` = **`0x010`**, or 16 — because the e-stop is a broadcast and
> broadcast is node 0, which is why node ids start at 1. Compare the others: a command to node 3 is
> `0x103`, its state frame is `0x203`, its diagnostics `0x303`. So the e-stop is still the lowest
> identifier on the bus by a wide margin and still wins arbitration even when the bus is saturated —
> that is not a trick, it is exactly what a priority-encoded identifier scheme is for. **The number
> you configure a hardware filter with is the identifier, not the type**, and being able to say all
> of that is a good two-minute interview answer.

### Draw this

The 11-bit identifier, as eleven labelled boxes, before you write a line of code. Mark where the type
field ends and the node field begins, and write the resulting numeric identifier underneath each
message you have defined — `MSG_ESTOP` broadcast, `MSG_COMMAND` to node 3, `MSG_STATE` from node 3,
and so on. Then sort that list numerically and check that the order you get is the priority order you
intended, because on a CAN bus those are the same thing and there is no separate priority field to
adjust later.

Underneath, draw the eight payload bytes of each message as a row of eight boxes with the field
boundaries marked and the byte offsets written in. Do this on paper first: the constraint is eight
bytes, and a drawing makes an over-budget message obvious in a way that a struct definition does not.

### What will go wrong

- **Your struct is nine bytes and you did not notice.** The compiler inserts padding to align a
  4-byte field on a 4-byte boundary. `sizeof(CommandFrame)` is the truth; check it with a
  `static_assert` rather than by counting. Order fields widest-first and the padding usually vanishes.
- **The frame arrives with the bytes in a different order.** Endianness. Both ends here are
  little-endian ARM so it works, and it will keep working right up until an ESP32 or a host tool joins
  the bus. Write the byte order into `docs/protocol.md` now, while it costs nothing.
- **The filter accepts everything, or nothing.** bxCAN filters are configured as an identifier and a
  mask, and it is easy to get the shift wrong — the standard 11-bit identifier sits in the *upper*
  bits of the filter register, not the lower. Test the filter by sending a frame it should reject.

**Capture the broken state.** The line of output where `sizeof(CommandFrame)` prints 12 and you
expected 8. Screenshot it. Silent struct padding is a bug with no symptom until a frame does not
fit, and a `static_assert` firing on it is a good artifact — but the surprising number, seen once,
is what makes you write the assert at all.

### Prove it

A design session still has an acceptance test, and this one is done on paper before any code exists.

1. **The width test.** Go through `docs/protocol.md` field by field and, for each, write one sentence
   saying why it is that many bits or bytes and not fewer. Any field you cannot justify is either too
   wide or not thought about. This is the exact question an interviewer asks and it is much easier to
   answer now.
2. **The range test.** For every numeric field, state what happens at both ends. `int32_t
   target_counts` at 11,880 counts per revolution covers ±180,000 revolutions — fine. `uint16_t
   vel_limit` in what units, and what is the largest value it can express? If the answer is "more than
   the joint can physically do", the field is wider than it needs to be; if it is "less", you have a
   silent clamp.
3. **The stranger test.** Hand `docs/protocol.md` to someone who has not read this workbook — or to
   yourself in a week — and ask them to write down what identifier a state frame from joint 2 carries.
   If they cannot get it from the document alone, the document is not finished.
4. **The priority test.** Sort every identifier you defined numerically and check the order is the
   priority order you intended. On CAN those are the same thing and there is no separate field to fix
   it with later.

> **CHECK YOURSELF** — Which of your messages would you most regret having made one byte too narrow,
> and which one byte too wide? If both answers are "none", you have not committed to anything yet.

### Artifacts

- **`docs/sessions/protocol-design/README.md`** — written at the end of the session, not the
  start. Three to five bullets on what actually happened, what the objective did not predict,
  and what you got wrong first. See [the template](../sessions/_TEMPLATE.md).
- `docs/protocol.md` — the full specification. Message table, bit layouts, rates, units, endianness.
- Four to six ADRs in `docs/decisions/`.
- **Site:** the protocol document itself. It reads as engineering in a way that photographs cannot.
  **The shot:** the document itself, rendered — a screenshot of the message table and one payload
  layout, at a size where the field names and byte offsets are readable. Link the file as well;
  the image is what makes anybody click it.

---

## S1.8 · Implementing it, and the silent-host problem

**Goal:** command and state frames flowing, and a joint that does something sensible when the host
stops talking.

**You will be able to:** explain what a joint should do when its host goes silent and why holding position is bounded where continuing a velocity is not, and turn that argument into a timeout you derived from a command rate rather than guessed.

### Concept

Everything up to here has assumed things work. This session assumes they do not, which is the
difference between a demo and an engineering artifact.

### The build

1. **Hardware filters.** Configure the bxCAN filter banks so this node only receives frames addressed
   to its own ID plus broadcasts. Do it in hardware, not by checking in software — the whole point of
   the identifier layout was to make this cheap.
2. **Command timeout.** If no `MSG_COMMAND` has arrived in N milliseconds, hold position.
3. **E-stop handling.** On `MSG_ESTOP`, cut output immediately and latch. Require an explicit clear.
4. **Over-current.** The INA219 you already own, on **I²C1, PB6/PB7** (see the standing pin map —
   *not* the Arduino-header default, which your CAN bus is using), reading motor current. Fault above
   a threshold you derive from your S1 stall-current measurement.
5. **Sequence checking.** Detect a skipped `seq` and do whatever you decided in S1.7.

### Code — skeleton, the hardware filter

Filter configuration is the hardest register work in Stage 1 and it is where the session's one real
trap lives, so it gets a skeleton rather than a sentence.

```c
/* can_filter.c — S1.8 */
#include "stm32f4xx_hal.h"

/* Accept exactly two things: frames addressed to THIS node, and broadcasts.
   Everything else is rejected in silicon and never reaches your code. */
void CAN_ConfigureFilters(CAN_HandleTypeDef *hcan, uint8_t node_id)
{
  CAN_FilterTypeDef f = {0};

  f.FilterBank           = 0;
  f.FilterMode           = CAN_FILTERMODE_IDMASK;   /* id + mask, not a list */
  f.FilterScale          = CAN_FILTERSCALE_32BIT;
  f.FilterFIFOAssignment = CAN_FILTER_FIFO0;
  f.FilterActivation     = CAN_FILTER_ENABLE;

  /* THE TRAP, and it is the whole reason this skeleton exists.
     A standard 11-bit identifier does NOT sit in the low bits of these
     registers. The register layout places the 11 identifier bits at the
     TOP of the 16-bit half-word, with IDE/RTR below them — so the value
     you write is your identifier shifted LEFT, not your identifier.

     Work out the shift from RM0390's bxCAN filter section (search for
     "CAN_FxR1"), and check your answer the way the failure list below
     says to: send a frame the filter SHOULD reject and confirm it does.
     A filter that accepts everything looks exactly like a working filter
     until a second node joins the bus. */

  /* TODO: f.FilterIdHigh / FilterMaskIdHigh — accept (type<<4)|node_id
           for any type, i.e. mask the low 4 bits against node_id and
           leave the type bits don't-care.                              */
  /* TODO: a second bank, or a second half of this one, for node 0
           broadcasts — the e-stop must reach you whatever your id.     */

  HAL_CAN_ConfigFilter(hcan, &f);
}
```

Two things worth noticing before you write it. **Filtering is free** — it happens in silicon, before
any interrupt, so a node on a busy bus spends nothing on messages that are not its business; that is
the whole reason S1.7's identifier layout put the node id in the low bits. And **a wrong filter is not
an error**: it either accepts everything, which works perfectly until joint two appears, or accepts
nothing, which looks like a dead bus. Neither tells you.

### The math — choosing the timeout

Too short and normal jitter faults you. Too long and a dead host means a joint carrying on for a
dangerous interval.

```
Command rate     = 100 Hz  → one command every 10 ms
Tolerate 3 missed frames   → 30 ms
Add margin                 → timeout = 50 ms
```

At 50 ms, a joint moving at your Stage 0 velocity limit of 3 rad/s travels 0.15 rad — about 8.6°
— before it notices. Decide whether that is acceptable. If it is not, either raise the command rate
or lower the velocity limit, and note that those are the only two levers.

> **WHERE THIS POINTS** — Hold position is almost always right; continuing the last velocity command is
> almost always catastrophic. That sentence is the whole of fail-safe design in one line, and being
> able to explain *why* — that a stale position command is bounded and a stale velocity command
> integrates without limit — is exactly the reasoning medical device work screens for.

### What will go wrong

This session writes the code whose entire purpose is to behave correctly when something else has
already failed, so every bug in it hides behind a system that looks fine.

- **The filter accepts everything and you conclude it works.** It does work — for one node. Test it by
  sending a frame it should *reject* and confirming your receive callback does not fire. This is a
  thirty-second test that catches the commonest error in the session, and almost nobody does it.
- **The filter accepts nothing and you suspect the wiring.** Same root cause, other direction: the
  identifier shift is wrong. Before you re-meter the bus, put the node into a state where it accepts
  everything (mask all zeros) and confirm frames arrive at all. That splits "filter wrong" from "bus
  wrong" in one step, which is the two-fronts rule applied to a register.
- **The timeout never fires.** You are measuring elapsed time with a counter that the control loop
  updates, and the control loop is still running happily — so "time since last command" is being
  compared against something that never advances, or is being reset somewhere it should not be. Reset
  the timestamp **only** where a valid command is accepted, and nowhere else.
- **The e-stop latch clears itself.** The same frame that sets the fault is still being processed, or
  the clear condition is "no e-stop frame received recently", which is not a clear — it is a timeout
  in the wrong direction. Clearing must require a *positive, explicit* action.
- **Over-current faults immediately, on a healthy motor.** The INA219 measures in milliamps and your
  threshold is in amps, or you are sampling during the inrush at the start of every move rather than
  after it settles. Both produce a fault on the first command.
- **Everything passes and you never tested it under load.** Unplugging the host while the joint is
  *stationary* proves almost nothing. All four tests below say "mid-motion" for a reason.

> **CHECK YOURSELF** — Before you run the four tests, predict for each one what the *plot* will look
> like, not just whether it passes. What does "holds position" look like on a position trace — flat,
> or flat with a small step at the moment of the timeout? Your answer tells you whether you have
> understood what the joint is doing with its last setpoint, and the trace will tell you whether you
> were right.

**Capture the broken state.** The log showing a frame addressed to another node arriving in your
receive callback. Capture it before you fix the shift. **A filter that accepts everything looks
exactly like a working filter**, so this is a failure you have to go looking for — which makes the
log that proves you went looking worth more than the corrected filter.

### Draw this

**The fault state machine, on one page, before you write it.** Boxes for the states a joint can be in
— running, timed out, over-current, e-stopped — and an arrow for every transition, each labelled with
what causes it. Then mark, on every arrow, whether it is automatic or requires an explicit clear.

Two things the drawing will surface that prose does not. **Can two faults be active at once**, and if
so what does clearing one do? And **what state does the joint boot into** — running, or refusing until
something says otherwise? Both are decisions, both belong in `docs/decisions/`, and
neither is obvious until the states are boxes on a page.

### Prove it

Four deliberate failures, each demonstrated and filmed or logged:

1. Unplug the host mid-motion. The joint holds.
2. Send an e-stop while moving. It stops and stays stopped until cleared.
3. Stall the motor by hand. Over-current faults.
4. Pull a termination resistor. Watch errors accumulate, and watch the bus recover when you replace
   it.

### Artifacts

- **`docs/sessions/fault-handling/README.md`** — written at the end of the session, not the
  start. Three to five bullets on what actually happened, what the objective did not predict,
  and what you got wrong first. See [the template](../sessions/_TEMPLATE.md).
- The CAN fail-safe ADR in `docs/decisions/`, and the fault state machine drawing.
- A log capture of each of the four failures.
- **Site:** the four failures, as four short clips or four annotated logs. Fault handling is what separates a demo from a product, and most portfolios show only the happy path.
  **The shot:** four items, one per failure, and they may be mixed — a clip where the arm's
  behaviour is the evidence, an annotated log where a counter or a fault flag is. **Each needs to
  show the fault being provoked, not just the state afterwards.** For the two clips, 10 to 15
  seconds each, with the joint and your hand on the switch or the cable in the same frame.

---

## S1.9 · Flash it twice

**Goal:** two joints, identical firmware, different node IDs, both controllable and both reporting.

**You will be able to:** explain why one binary flashed twice is a stronger claim than two binaries that work, and prove it byte for byte rather than asserting it.

### Concept

This is the session that makes the architecture real. Up to now "distributed" has been an intention.
Now it is a deployment detail: same binary, different jumpers.

### Build

- Read the node ID from **PC0–PC3** with internal pull-ups, at boot, once. Four bits gives IDs 1–15.
- **Do not** compile a different binary per joint. If you find yourself doing that, the architecture
  has quietly collapsed back into four bespoke controllers, which is the thing Mimic exists to avoid.
- Both joints on one bus. Command both. Verify both report.

> **CHECK YOURSELF** — Verify the binaries are literally identical: hash both `.bin` files and compare.
> If they differ, some configuration is baked in at compile time that should be read at runtime. This
> is a thirty-second check that catches a design error you would otherwise discover at joint three.

### Draw this

**The bus, as it now physically is, with everything on it.** Two joints, the monitor, the transceivers,
the twisted pair, and the 120 Ω at each *physical* end — drawn where they actually sit on your bench
rather than schematically. Mark the two terminated ends and write "60 Ω" across the pair.

Then annotate every node with the three numbers that define it: its **node ID** from the jumpers, the
**identifiers it transmits** (`0x2xx`, `0x3xx` with its own low nibble), and the **identifiers its
filter accepts**. That third one is the column people cannot fill in, and being unable to fill it in is
exactly why a filter bug is hard to find.

Keep this page. S2.11 adds the gateway to it, and a drawing that grows as the bus grows is worth more
than three separate ones.

### What will go wrong

This session is the hinge between Stage 1 and Stage 2, and hinges are where the thin sessions hide
their failures. Four to expect:

- **Both nodes come up as the same ID.** The jumper pins read floating-high with nothing fitted, so
  "no jumpers" is ID 15 on both boards, not ID 0 and ID 1. Two nodes with one ID on a CAN bus is not
  a collision you will see as an error — both simply answer the same command, and the state frames
  interleave into something that looks like one very confused joint. Read the ID once at boot, print
  it in the banner, and check the banner before you check anything else.
- **The binaries differ and you cannot see why.** A build timestamp, a `__DATE__`, or a path baked
  into an assert string is enough. Diff the two `.bin` files rather than staring at the hashes; the
  offset of the first difference usually names the cause.
- **Node ID 0.** Your scheme reserves 0 for broadcast, so a board that reads 0 is silently
  indistinguishable from a broadcast address. Refuse to run at ID 0 and flash the LED instead of
  starting the control task.
- **It works with two nodes on the bench and the third breaks it.** Termination, again — power off,
  meter across CANH/CANL, expect ~60 Ω. Do this every single time you add a node, including now.

**Capture the broken state.** The two boot banners, side by side, both announcing node 15 with no
jumpers fitted. Screenshot both terminals in one frame. Two nodes sharing an ID does not produce an
error anywhere on a CAN bus — the state frames simply interleave into one very confused joint — so
the banner is the only place the truth is visible.

### Prove it

1. Hash both flashed `.bin` files and confirm they match, byte for byte.
2. Command joint 1 to 30° and joint 2 to −30° **in the same second**, and confirm each moves only to
   its own target. That is the test that the identifier filtering actually works, and it is the one
   thing two joints can do that one cannot.
3. Pull the command stream to joint 1 only, mid-motion. It holds; joint 2 keeps taking commands. The
   fail-safe is per-node, and this proves it.
4. Capture a bus trace with both nodes live and read off the identifiers. You should see `0x1xx`
   commands going down and `0x2xx` states coming back, with the low nibble naming the node.

### Artifacts

- **`docs/sessions/flash-it-twice/README.md`** — written at the end of the session, not the
  start. Three to five bullets on what actually happened, what the objective did not predict,
  and what you got wrong first. See [the template](../sessions/_TEMPLATE.md).
- Matching SHA-256 hashes of the two flashed binaries, in the tuning log.
- Video of both joints responding to independent commands on one bus.
- **Site:** this video. It is the moment the project stops being a bench experiment.
  **The shot:** one clip, 25 to 40 seconds, landscape. **Both joints and the bus between them in
  one shot** — the twisted pair has to be visible or this is a video of two motors rather than of
  a bus. Command +30° and −30° in the same second and let both move at once. Put the two matching
  SHA-256 hashes on screen as text before or after, since that is the actual claim and it cannot
  be filmed.

---

## The Stage 1 exit gate

| # | Criterion | Evidence |
|---|---|---|
| 1 | Two joints run **identical** firmware on one bus with different IDs | Matching binary hashes |
| 2 | A joint holds position safely when the host goes silent | Logged failure test |
| 3 | You can capture and explain a bus trace | Saved capture |
| 4 | Your control task is provably running at rate **under load** | Analyzer capture during telemetry stall |
| 5 | You can explain why your e-stop message has the identifier it has | `docs/protocol.md` |
| 6 | You derived your CAN bit timing rather than copying it | `docs/derivations/` |
| 7 | You have halted the processor on a breakpoint and inspected memory | Screenshot |
| 8 | Your Stage 0 gains transferred from 500 Hz to 1 kHz unchanged | Overlay plot |
| 9 | Tag `v0.1-stage1-exit` pushed | GitHub |

---

## What goes on the site

| Session | Artifact | Why it reads well |
|---|---|---|
| S1.1 | Debugger halted, watch window visible | Marks the hobby/professional boundary |
| S1.2 | Hand-drawn clock tree | Almost nobody shows this |
| S1.3 | "7 % of an AVR → 0 % in hardware" | A measured improvement, not a claim |
| S1.4 | UNO 100 Hz vs STM32 1 kHz, same gains | Evidence the code is dimensionally correct |
| S1.5 | Control period with and without pre-emption | The best possible answer to "why an RTOS" |
| S1.6 | Bit-timing derivation, 60 Ω meter photo | Physical-layer competence |
| S1.7 | `docs/protocol.md` | The highest-signal document in the repo |
| S1.8 | The four deliberate failures | Fault handling is what separates demo from product |
| S1.9 | Two joints, one bus, one binary | The architecture, working |

---

## The milestone map

The Project Guide numbers Stage 1 as milestones **M1.1–M1.7**; this workbook numbers it
**S1.0–S1.9**. Same work, two levels of detail. Every milestone in the set carries its stage as a
prefix, so `M1.6` is unambiguously Stage 1's sixth and not Stage 0's or Stage 2's.

| Guide milestone | Workbook session |
|---|---|
| **M1.1** · Blink an LED from CubeMX-generated code, and the debugger | **S1.0** + **S1.1** |
| **M1.2** · Port the control loop to bare STM32, in C | **S1.2** (clock tree) + **S1.3** (hardware quadrature) + **S1.4** (loop) |
| **M1.3** · Introduce FreeRTOS | **S1.5** |
| **M1.4** · Get two nodes talking on CAN | **S1.6** |
| **M1.5** · Design and implement your joint protocol | **S1.7** |
| **M1.6** · Fault handling and the silent-host problem | **S1.8** |
| **M1.7** · Flash it twice | **S1.9** |

---

## Session index

| # | Session | Hours |
|---|---|---|
| S1.0 | CubeIDE and the generated project | 3 |
| S1.1 | Blink, and the breakpoint | 3 |
| S1.2 | The clock tree | 3 |
| S1.3 | Hardware quadrature | 3 |
| S1.4 | Control loop in C, on bare metal | 5 |
| S1.5 | FreeRTOS, two tasks | 5 |
| S1.6 | CAN physical layer, bit timing | 5 |
| S1.7 | Protocol design | 4 |
| S1.8 | Implementation and fail-safe | 6 |
| S1.9 | Flash it twice | 3 |
| | **Total** | **~40 h** |

**~40 h is about three weeks of bench time at two to three hours a day. Appendix G budgets four**, and
the extra week is deliberate: this is the only stage where the binding constraint is the toolchain
learning curve rather than the work. CubeIDE's first run, the clock tree, and the first breakpoint
each absorb an evening that does not look like progress, and S1.6's bit timing is the kind of thing
you get wrong once and re-derive. Plan four; be pleased if it takes three.

---

## Figure index

Every figure in this document is plain ASCII/box-drawing art inside a fenced code
block, tagged `FIGURE <id> — <title>` on its first line. That is deliberate: it
renders correctly in GitHub and in any Markdown viewer, and it stays diffable in
Git. For a PDF export, set the monospace font to one with full box-drawing and
half-block coverage — **DejaVu Sans Mono** is the usual answer; the core PDF
monospace fonts do not carry the geometric and box-drawing characters these figures use — in this
volume: `◄ ► ▼ ↑ ← ·` — and will drop or substitute them.

| Figure | Title | Where |
|---|---|---|
| **S1.2.1** | The F446 tree, and the three numbers the rest of Stage 1 uses | S1.2 |
| **S1.5.1** | The demonstration you must actually produce | S1.5 |
| **S1.5.2** | The torn read, one layer up from Stage 0 | S1.5 |
| **S1.6.1** | Where 111 bits comes from, field by field | S1.6 |
