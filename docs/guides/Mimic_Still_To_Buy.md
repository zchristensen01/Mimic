# Mimic — What's Left to Buy

**Reconciled against the order placed 31 July 2026, the parts already on your shelf, and the
decisions made in the Stage 0–5 workbooks.**

**Every figure on this page is Canadian dollars, before tax unless a line says otherwise.** The tier
tables drop the `C$` prefix for readability; the subtotals and the totals table carry it.

Every line with reasoning attached has that reasoning in a box below the table it appears in. Read
the boxes: several of them are the difference between buying the right part and buying a part with
the right name. Three lines on this page are genuine open decisions rather than recommendations, and
they are collected at the end.

---

## Answer first: what you have not bought

**You have not bought the Stage 1 board.** Nothing STM32 is in the 31 July order. It sits under
*Deliberately deferred* as a week 3–4 decision, and that decision is still open.

**And you have not bought anything that makes the Stage 2 arm move.** The torque budget in S2.4 rules
out the motors you own, and Tier D1 is the largest live decision in the project.

Everything else outstanding is below, in the order you will need it.

---

## Nothing is blocking — with six things to check tonight

No tier of parts stands between you and Stage 0's early sessions. But **three cheap items that Stage 0
assumes are not in the 31 July order**, and two of them are in no manifest section at all. Check for
them tonight rather than at 9 p.m. on the evening you wanted to run S2.

| Check | Status in the *Order Manifest* | If you do not have it |
|---|---|---|
| **~2 mm precision screwdriver** | **Absent entirely** — not "already owned", not deferred, not a line item | C$5–8. **S2 cannot run without it** — it is the only thing that turns a multi-turn trim pot. Tier B below. |
| **Safety glasses** | **Deliberately deferred** — "marked N in spreadsheet". You do not own a pair. | C$8. Stage 0 has you drill, solder, snip and cut. Tier B below. |
| **Inline DC switch** | Absent. The manifest's only switches are the ten roller-lever microswitches, which are limit switches. | C$3, or use a switched power bar. S8 and S10 both assume you can cut power in a second. Tier B below. |
| **Plywood board**, ~9.5 × 20 × 0.5 in | Absent — mentioned once, in passing, inside an unrelated *deferred* note | Offcut, or ~C$10. **S1 is built around it** and every document calls it one of the five things Stage 0 needs. Tier B below. |
| **Two G-clamps** | Absent | ~C$10 the pair. S1 clamps the board at both ends and its own check needs the second one. Tier B below. |
| **A drill and a 3 mm bit** | Absent | Borrow, or ~C$40. S1 drills the board for heat-set inserts or through-bolts, and there is no version of the mount that needs no hole. Tier B below. |

**None of the six is in the manifest, and that is exactly why they are listed.** They are the items
everybody assumes — a plank, some clamps, a drill, a small screwdriver — and an assumption is the one
kind of part that cannot be checked off a receipt. None of them blocks S0. All of them block or degrade
S1 and S2, which are two and three sessions away.

Tier letters below run **B to G**. There is no Tier A and no Tier 0: tooling and all of Stage 0 were
bought outright in the 31 July order rather than tiered, and the *Order Manifest* is the record of
that. The letters that are referenced elsewhere by name are **C** (Stage 1 Workbook), **D1** (Stage 2
Workbook S2.4), and **E** and **F** (Volume VI). B and G are named only here, and that is fine — they
are optional purchases rather than gates.

---

## TIER B — the three Stage 0 gaps, plus comfort. Cheap, and mostly not optional.

| Item | Qty | Est. | Where | Why |
|---|---|---|---|---|
| **~2 mm precision screwdriver** | 1 | **$6** | local / AliExpress | **Verify first** — it is in no section of the manifest, so do not assume you own one. **S2 requires it**: the XL4015, LM2596 and MP1584 all set their output with a multi-turn trim pot and nothing in a general tool roll turns one. |
| **Safety glasses** | 1 | **$8** | local | **You do not own these** — the manifest lists them under *Deliberately deferred*. Stage 0 drills plywood, solders, snips component legs and cuts heat-shrink. Buy them, or record the decision not to. |
| **Inline DC switch**, ≥5 A, for the 12 V lead | 1 | **$3** | AliExpress / local | Nothing in the order breaks the 12 V rail. S8 drives the rig to sustained oscillation and S10 stalls it deliberately; both say "power switch" and neither means "yank the barrel jack". A switched power bar substitutes. |
| **Plywood board**, ~9.5 × 20 × 0.5 in | 1 | **$10** | offcut / hardware store | **Verify first.** S1 bolts the motor to it and clamps it to the desk; a rigid base is the cheapest debugging tool in the project and its absence costs a week in S8. Any flat, stiff 12 mm board does — plywood, MDF or aluminium plate. |
| **G-clamps** | 2 | **$10** | local | **Verify first.** One at each end of the board. S1's own check is "if the assembly rocks, add the second clamp", so two is the requirement, not one. |
| **Drill + 3 mm bit** | 1 | **$0–40** | borrow / local | **Verify first.** Heat-set inserts and through-bolts both need a drilled hole, so there is no fixing method that avoids this. A cordless drill borrowed for an evening is entirely sufficient. |
| Smoke stopper | 1 | $8 | AliExpress | First power-up insurance. Your XL4015's current limit substitutes if you use it deliberately. |
| Activated carbon sheet + spare PC fan | 1 | $6 | AliExpress / your parts bin | DIY fume extractor. You built a PC — check for a spare fan first. |
| Spare INA219 | 1 | $3 | AliExpress | You own three and the project consumes exactly three. This is the spare — see the note in Tier F, which is where the allocation is worked out. |

**Subtotal: C$0 minimum · C$94 with everything.** Zero is only reachable if every check comes back
positive — you find a precision driver, glasses, a plank, two clamps and a drill, and you accept a
switched power bar as the switch. **C$77 of the C$94 is the six Stage 0 gaps** (6 + 8 + 3 + 10 + 10 +
40), and realistically most of that C$40 drill is a borrow rather than a purchase. That is the number
to spend if you spend anything on this page before Stage 1.

---

## TIER C — Stage 1. Order now, or by week 1 at the latest.

| Item | Qty | Est. | Where | Note |
|---|---|---|---|---|
| **STM32 Nucleo-F446RE** | 1 | **$28** | **DigiKey Canada** | **Not AliExpress.** Part 497-15882-ND — check current pricing and stock before ordering. See below. |
| **SN65HVD230 CAN transceiver** | 4 | $12 | AliExpress | 3.3 V logic — correct for STM32. Buy four; they are C$3 and you will kill one. |
| Twisted pair / CAT5 offcut | 2 m | $10 | local | Untwisted ribbon works on a bench and fails next to a motor. |
| JST-XH 4-pin connectors | 1 set | $10 | AliExpress | Daisy-chainable joint bus. **A "set" is housings plus loose crimp terminals** — you need the tool below, or buy pre-crimped pigtails instead. |
| **Crimp tool** for JST-XH (SN-01BM class) | 1 | *$25* | AliExpress | *Optional, and read the note.* Nothing in the 31 July order crimps — the 6-in-1 electrician's pliers strip and cut, they do not form a JST terminal. Either buy the tool, or buy **pre-crimped JST-XH pigtails** for a few dollars and solder to them. Decide before you order the connectors, not after. |
| MCP2515 + TJA1050 module | 2 | $8 | AliExpress | *Optional.* Lets you prototype CAN framing on an UNO first. |
| Second Nucleo-F446RE | 1 | $28 | DigiKey | *Optional.* Alternative to using an ESP32-S3 as the second node. |
| **CANable 2.0** | 1 | ~$50 | Openlight Labs | *Decision point.* See below. |

**Subtotal: C$60 minimum · C$171 with everything optional**

> **Why "now" and not "week 3".** The rule this page uses is *stage start minus lead time*, and Stage 1
> starts around week 4. The DigiKey items would arrive in days; the **AliExpress transceivers are two to
> four weeks**, so ordering at week 3 lands them at week 5–7, after Stage 1 has begun. You would get
> away with it — the transceivers are not needed until S1.6, the seventh of ten sessions — but "I will
> get away with it" is how a stage stalls waiting on a C$3 part. Order the whole tier together, early.

> DigiKey Canada ships **DDP** — duty and customs paid — so unlike the AliExpress order there is no
> border exposure at all. Free delivery over C$100, C$15 below it, which is worth bundling for.

> **Nucleo-F446RE, not your ESP32-S3s.** Your two ESP32-S3s are the cheaper path on paper: each has
> two PCNT units that decode quadrature in hardware plus a native CAN controller. Buy the Nucleo
> anyway, for three reasons. **One:** STM32 with HAL and CubeMX is the dominant toolchain in medical
> devices and aerospace — your two target fields. ESP32 is consumer IoT. The chips are comparable;
> the ecosystems are not, and it is the ecosystem that appears in job postings. **Two:** the on-board
> ST-Link. Halting the processor on a breakpoint and inspecting memory is the largest quality-of-life
> jump between hobby and professional embedded work, and it is what most people skip. **Three:**
> CubeIDE puts the startup assembly, vector table and linker script in folders you can open, which is
> rung 4 of the guide's ladder. ESP-IDF hides more of it.
>
> **Do not buy a Nucleo on AliExpress.** Clones ship counterfeit silicon and non-functional ST-Link.
> Debugging a fake chip as your introduction to STM32 is how people quit. It is C$28.
>
> **Your ESP32-S3s are not wasted.** They have two defined jobs in the Stage 1 workbook: the CAN bus
> monitor in S1.6, and joints three and four once your protocol is proven. Running a mixed-vendor bus
> on a protocol you designed is a better thing to say than owning two identical boards.

> **The CANable decision — this one is yours, not mine.** A CANable 2.0 gives you socketCAN,
> `candump` and `cansend` on the host, and it is the comfortable path. But **socketCAN does not exist
> in a stock WSL2 kernel**, so buying one moves your native Ubuntu install from a Stage 2 deadline to
> a Stage 1 one. Either buy it and install Ubuntu now, or use an ESP32-S3 with a transceiver as the
> monitor and defer both. Both are legitimate. Pick deliberately and write an ADR.

---

## TIER D — Stage 2. The expensive one, and the one with a live decision in it.

### D1 · Actuation — the decision the torque budget makes for you

Stage 2's S2.4 computes the static torque budget for a 14.2-inch arm at 180 mm links:
**the shoulder needs ≈ 0.64 N·m unloaded and ≈ 0.99 N·m holding a 100 g payload.** Your N20s deliver
**≈ 0.049 N·m** if you derate 25 % from a claimed 2 kg·cm stall — and only **0.0098 N·m** if you use
the same vendor's *rated* continuous torque, which is the honest figure. So the shoulder gap is
**20× on the optimistic reading and about 100× on the honest one.**

> **Belt reduction is the option most likely to look as though it should work, and it does not.** It
> is cheaper, it uses motors you already own, and it teaches a real technique — which is exactly why
> it deserves the multiplication rather than the instinct. **Multiply it out: 0.049 × 3 = 0.147 N·m,
> 0.049 × 4 = 0.196 N·m — against a 0.99 N·m requirement, still 5× to 6.7× short.** A single-stage GT2
> reduction tops out around 4:1 or 5:1 before the small pulley runs out of teeth in mesh, and you need
> roughly 20:1. That is two stages, two sets of backlash, and a genuinely difficult build. **Belt
> reduction is a good technique and it is the wrong tool for a 20× gap.** The full arithmetic,
> including the stacked best case, is in S2.4.

**Path A — bigger motors. Recommended.**

| Item | Qty | Est. | Note |
|---|---|---|---|
| **JGB37-520 / GB37Y3530 12 V gearmotor with encoder**, high ratio | 2 | $55 | The 270:1 variant is rated **30 kg·cm ≈ 2.94 N·m** — a **2.4× margin** against the 1.20 N·m loaded requirement once the motor's own mass is counted. |
| **Higher-current motor driver** (BTS7960 or DRV8871 class) | 2 | $18 | **Consequence of the above.** See below. |
| Bearings (MR series / 608) for joint axes | 8 | $15 | **Needed on any path.** |
| | | **$88** | |

**Path B — belt reduction on the motors you own. Insufficient alone.**

| Item | Qty | Est. | Note |
|---|---|---|---|
| GT2 pulley + belt set, 3:1 or 4:1 | 2 sets | $25 | Reaches 0.20 N·m at best. **Does not close the gap.** |
| Bearings (MR series / 608) for joint axes | 8 | $15 | Needed on any path. |
| | | **$40** | Rejected on arithmetic, not on instinct — S2.4 computes the *stacked* best case too. See below. |

> **The stacked version of Path B, computed rather than waved away.** It is fair to ask whether belt
> reduction plus shorter links plus a counterbalance plus base-mounted motors gets there together.
> S2.4 multiplies it out: 125 mm links with the elbow motor moved to the base need **0.343 N·m
> unloaded, 0.589 N·m loaded**; a counterbalance cancelling the unloaded term leaves **0.245 N·m** near
> one pose. Against that, a 4:1 belt gives 0.196 N·m (**1.25× short**) and a 5:1 gives 0.245 N·m
> (**exactly break-even, zero margin**) — on the *optimistic* 25 %-of-stall figure. On the
> manufacturer's rated torque the same stack is **5× short at that same 5:1**. So it is not rejected because the
> multiplication is hopeless; it is rejected because break-even is not a design, the counterbalance
> only holds near one pose, and the honest torque figure ends the argument. **It also costs you
> reach** — 250 mm instead of 360 mm — and a parallel linkage and a tuned spring in CAD. Cheaper in
> parts, considerably more expensive in everything else.

> **The driver upgrade, stated precisely — because the tempting summary is wrong.** A JGB37-520 class
> motor is rated at **≤ 1 A** and **stalls at 2.3 A**. Your TB6612FNG is **1.2 A continuous, 3.2 A
> peak**. Compare them honestly — the comparison is immediately below this box.

```
  rated  1.0 A  vs  1.2 A continuous  →  INSIDE, 17 % headroom
  stall  2.3 A  vs  3.2 A PULSE rating →  read the note below before
                                          you call this "inside"
```

> **The second line needs care, because the two numbers are not the same kind of number.** The
> TB6612's 3.2 A is a **pulse** figure, qualified in the datasheet by a duty cycle and a maximum
> pulse width on the order of tens of milliseconds. A stall is not a pulse — it persists until
> something intervenes. So "2.3 < 3.2, therefore fine" is only true for a stall that is *bounded*, and
> what bounds it is software: **Stage 0's stall-detection latch (S11) is what turns a 2× over-rating
> into a transient.** Size its window against the driver's pulse-width limit rather than against what
> feels responsive.
>
> **So the TB6612FNG is not invalidated — it is thermally marginal.** Normal operation sits inside its
> continuous rating with 17 % to spare, and a *latched* stall stays inside the pulse rating. **Buy the
> bigger driver anyway, and say why in that language: the argument is margin, not incompatibility.**
> Seventeen percent is not a margin you want on a part driving a heavier arm than it was sized for, in
> an enclosure, for hours. So Path A is C$88 rather than C$55.
>
> **Keep the five TB6612FNGs.** They remain correct for the Stage 0 rig, for bench testing, and as
> spares. Nothing here obsoletes them.
>
> One more thing from the same vendor tables: they carry a **"blocking is not allowed / the motor is
> forbidden to be locked"** warning for this gearbox family. That is about the gears, not the winding —
> a high-ratio steel train can shed a tooth under stall long before anything gets hot. Whatever driver
> you buy, Stage 0's stall-detection latch is not optional on this motor.

> **Three more consequences of Path A, none of them obvious.** **One: the new motor is heavier, and
> that eats into the gain you just bought.** At 200 g for the elbow motor the shoulder requirement
> rises from 0.64 to 0.85 N·m unloaded and 1.20 N·m loaded — a **2.4× margin** against the rated
> 2.94 N·m rather than the 4.6× you would have assumed, but you only know that because S2.4 redoes the
> sum. (That 200 g is an *estimate* for a 37 mm gearmotor;
> weigh yours when it arrives and redo the line.) **Two: the JGB37-520 encoder is 11 PPR per channel,
> not 7.** Your `COUNTS_PER_OUTPUT_REV` becomes 11 × 4 × 270 = 11,880, and therefore every PID gain you
> tuned in Stage 0 changes with it. Budget an evening to retune, and do not be alarmed when it
> happens — it is dimensional correctness working, not a regression. **Three, and this is the one
> nobody mentions: you are buying torque with speed.** The 270:1 variant runs **37 RPM no-load, 28 RPM
> rated**, against your N20's 100 RPM. The arm gets **2.7× slower**. Be precise about which number
> moves: the **no-load ceiling** falls from 10.47 rad/s to about 3.87 rad/s, and `V_MAX` — the limit
> you *chose* in Stage 0 S11 — was 3.0 rad/s, which is 77 % of the new ceiling and therefore
> unreachable under load. Keep the same margin and `V_MAX` becomes about **1.1 rad/s**. That is fine
> for a desk arm and it is not fine if you had a fast pick-and-place in mind. Decide before you order.

> **Order by ratio and RPM, not by part number.** "JGB37-520" is a motor *body*, not a
> specification. The same string is sold as a 10:1 / 1000 RPM / 1.6 kg·cm unit and as the 270:1 /
> 37 RPM / 30 kg·cm unit these figures come from — an order of magnitude apart on torque, 27× apart on
> ratio. This is the identical trap your N20 set, and buying the wrong variant would silently undo the
> entire S2.4 argument. **Match 12 V, 270:1, ~37 RPM explicitly, and screenshot the listing.**

### D2 · Everything else in Stage 2

| Item | Qty | Est. | Note |
|---|---|---|---|
| **TCA9548A I²C multiplexer** | 2 | $5 | Easy to miss and it blocks two-joint absolute encoding entirely. See below. |
| **12 V 8–10 A power supply** | 1 | *$25* | ***Optional — buy it for margin, and measure first.*** S2.4 itemises it: your existing 12 V 5 A adapter is at **44 %** running normally and **70 %** with one joint stalled, but **96 %** with both stalled. The fault case has no headroom left. See below before you spend anything. |
| **Emergency stop** — latching mushroom, wired to cut *motor* power | 1 | $15 | The guide is emphatic: fit it **before** the first powered test of the assembled arm. |
| Flexible shaft couplers, 4/5/6 mm assortment | 1 set | $12 | Was on the First Order list, not purchased. |
| Threadlocker, blue medium-strength | 1 | $10 | Every fastener that sees vibration. |
| Diametric magnets for AS5600 | 2 | $5 | **Verify first** — check what shipped with your AS5600 boards. |
| Shielded twisted pair for encoder runs | 3 m | $12 | Ground the shield at **one end only**. |
| 3D printer — budget enclosed CoreXY, hardened nozzle | 1 | $420 | Verify the nozzle material on the specific SKU. |
| Filament — PETG-CF or PA6-CF, PETG, TPU | — | $120 | Links, brackets, gripper pads respectively. |
| **Gripper servo** | — | **$0** | You own an SG90 in the starter kit — ***verify it is actually there; the manifest does not itemise the kit.*** If it is not, an SG90 is about C$2 — buy **two**, because S2.10 has you stall-test one to measure its real torque, and **this tier becomes C$603**. Sized in **S2.10**: ~1.3 N of usable grip at a 40 mm finger, which is marginal for a 100 g object and depends on TPU pads. |

**Subtotal D2: C$599 minimum · C$624 with the supply · Tier D total: C$687–712 (Path A, recommended)
or C$639–664 (Path B, insufficient alone)**

> **Your existing supply, stated precisely — because it is easy to over- and under-react to this.**
> Stage 0 sized the 12 V 5 A adapter against **one N20** and nothing redid it after Path A. S2.4 does,
> itemising the 5 V rail rather than guessing at it:
>
> | | 12 V draw | of 5 A |
> |---|---|---|
> | Running normally, both motors at rated current | 2.18 A | 44 % |
> | One joint stalled | 3.48 A | 70 % |
> | **Both stalled, gripper holding** | **4.78 A** | **96 %** |
> | Both stalled and the gripper stalled too | 5.03 A | 101 % |
>
> **So it is not inadequate — it has run out of fault-case margin.** Everything you do on purpose sits
> under 70 %. What has gone is the headroom for a double stall, on a rating specified at 25 °C that
> derates as the brick warms up.
>
> **Whether that matters is a software question.** If your S11 stall latch fires, the excursion lasts
> tens of milliseconds and your bulk capacitance carries it. If it does not, the adapter is asked for
> 100 % continuously, folds back, and browns out the controller that was supposed to be latching the
> fault.
>
> **So: measure before you buy.** You will own the motors by then — stall one, watch the 12 V rail with
> the meter, then stall both. If it sags under a hundred millivolts you are fine. If you do decide to
> spend, **a separate C$12 5 V supply for logic is arguably the better buy than more amps**, because it
> fixes the failure mode rather than the number: the motor rail can collapse without taking the
> controller with it. Write down which you chose and why — this is an ADR.

> **TCA9548A.** You own two AS5600 boards and they are **both hardwired to I²C address 0x36, which
> cannot be changed** — there is no solder jumper and no register write that moves it. Two of them on
> one bus is therefore impossible, and the failure is not an error message: one device answers and the
> other is invisible, which reads as a dead board. A multiplexer gives each sensor its own switched
> segment of the bus. It costs about C$2.50 and without it two-joint absolute encoding does not work
> at all.

---

## TIER E — Stage 3. Order around month 4. Possibly free.

Stage 3 is the cheapest stage in the project and may cost nothing at all, which is exactly why it is
worth listing rather than leaving under "optional" — an unlisted stage is one you discover you are
not ready for. Appendix G puts the start of Stage 3 around calendar week 20; order in month 4 so the
webcam is not the thing you are waiting on. The Project Guide budgets about C$60 here; the four lines below are what that money is
for, and three of them are free if your shelf and your printer cooperate.

| Item | Qty | Est. | Where | Note |
|---|---|---|---|---|
| USB webcam, 1080p, manual focus if possible | 1 | $0–40 | shelf / Amazon | **Check your shelf first.** Fixed focus is *better* here — autofocus silently invalidates your M3.1 calibration every time it hunts. |
| USB microphone or headset | 1 | $0–30 | shelf | Anything with a decent noise floor. A headset you already own is fine. |
| Checkerboard + ArUco markers | — | **$0** | your printer | Print on paper, glue to something rigid and **flat**. A warped target quietly corrupts every intrinsic you compute. |
| Camera mount | — | **$0** | your 3D printer | Rigid, and fixed relative to `base_link` — if it moves, M3.3's hand-eye transform is void. |

**Subtotal: C$0 minimum · C$70 if you own neither camera nor microphone**

> **The one that is not obvious: fixed focus beats autofocus.** M3.1 recovers an intrinsic matrix and
> distortion coefficients for *one* optical configuration. An autofocus webcam changes that
> configuration whenever the scene changes, so your calibration is valid only for the focus setting it
> was captured at. If your webcam autofocuses and cannot be told not to, expect grasp positions that
> are confidently wrong in a way that comes and goes — the hardest class of bug in the whole stage.

---

## TIER F — Stage 4. Order around month 5.

> **Before this tier: check your INA219 count.** You own three, and three is exactly what the project
> consumes — **one per joint for Stage 5's current-based force estimation, plus one on the gripper
> servo for S2.10's `isHolding()`.** Stage 1's over-current diagnosis reuses the two joint sensors
> rather than adding to the count, so nothing competes, but nothing is spare either. **The spare is a
> line item in Tier B at C$3** rather than a note you will forget; and if you ever go to four joints,
> that is four more, not two.

> **And check your ESP32-S3 count against what you intend to run at once.** You own two, and the set
> gives them **three** jobs: the CAN bus monitor in S1.6, the **serial-to-CAN gateway in S2.11**, and
> joints three and four once the protocol is proven. The monitor and the gateway are the same hardware
> — an ESP32-S3 plus a transceiver — but they are not the same *board* once Stage 2 runs, because the
> gateway is occupied permanently from then on.
>
> So: two boards cover Stage 1 comfortably. From S2.11 onward one is the gateway, which leaves exactly
> one spare, and **watching the bus while the arm is live needs a third** — about C$12. The alternative
> is the optional second Nucleo in Tier C, which makes a better gateway if you would rather not have a
> second toolchain in play. Neither is a problem today; both are worth knowing before the evening you
> want to debug an arm and monitor its bus at the same time.

| Item | Qty | Est. | Note |
|---|---|---|---|
| MyoWare 2.0 muscle sensor | 1 | $90 | Start with one channel. Add a second only if you need it. |
| Disposable Ag/AgCl electrodes | 1 pack | $20 | Consumable. |
| **USB isolator** (ADuM3160-based) | 1 | $25 | **Non-negotiable.** See below. |
| USB power bank | 1 | $20 | Check your shelf first. |
| Raw 6-axis IMU (MPU6050 or ICM-20948) | **1** | $5 | M4.5 needs two (one per limb segment). **Verify first** — the "one you own" is the starter-kit MPU6050, which the manifest does not itemise. If it is not on your shelf, buy **two**, and this tier becomes C$170. |
| Elastic band, markable | 1 | $5 | Repeatable electrode placement is what makes yesterday's model work today. |

**Subtotal: C$165**

> **The USB isolator is the one item on this page I would not let you skip.** Stage 4 is the only
> part of Mimic with a genuine physical risk to you: electrodes on your skin connected to
> mains-powered equipment. The rule is battery power **or** galvanic isolation, and the correct answer
> is both. The parts doc lists the isolator under "places not to economise" and it is right. Being
> able to articulate *why* — that a fault in a mains-connected device can put current across your
> chest through the electrode path — is also exactly the reasoning a medical device employer will
> expect you to have internalised.

---

## TIER G — Optional, worth considering

| Item | Est. | Why you might |
|---|---|---|
| KiCad joint carrier PCB, 5 boards from JLCPCB | $25 | Turns a fragile nest of jumper wires into a module you can replicate. PCB design is a line item on most embedded postings. Fits between Stage 1 and Stage 2. |
| Bench power supply | $120 | Your XL4015 with current limit genuinely substitutes. Defer indefinitely. |

**Subtotal: C$145**

---

## Totals, with the arithmetic shown

| Tier | Order by | Minimum | With optionals |
|---|---|---|---|
| B — Stage 0 gaps + comfort | **now** | $0 | $94 |
| C — Stage 1 | **now** | $60 | $171 |
| D — Stage 2 | week 6–7 (≈ month 1.5) | $687 | $712 |
| E — Stage 3 | month 4 | $0 | $70 |
| F — Stage 4 | month 5 | $165 | $165 |
| G — optional | — | $0 | $145 |
| **Pre-tax** | | **$912** | **$1,357** |
| NS HST @ 14% | | $128 | $190 |
| **Total remaining** | | **$1,040** | **$1,547** |

> **Where those dates come from, and why they are earlier than they look.** They are *stage start
> minus lead time*, and both halves are derived rather than quoted.
>
> **Stage starts.** Appendix G gives per-stage durations (2–3, 4, 8, 3–4, 4–5 weeks at your pace) and a
> total of 28–30 *calendar* weeks against 21–24 active — so calendar time runs about 1.3× active time.
> Accumulate the durations and apply that stretch and the stages begin around **week 4, week 9, week 20
> and week 24**. Appendix G does not print that table; this is it, and you should re-derive it rather
> than trust it if your actual pace differs.
>
> **Lead time.** This set's own figure for AliExpress to Nova Scotia is **two to four weeks**, and
> occasionally six. Ordering in the week a stage begins means starting it without parts.
>
> Subtract one from the other and you get the column above. **Tiers B and C are both "now"** — B
> because S2 is two sessions away, C because a two-to-four-week lead against a week-4 start leaves no
> room at all.

Tier D's two columns differ only by the power supply, which is a margin purchase you should measure
before making. The *actuation* decision inside it is not an optionality — it has one arithmetically
viable answer (Path A). See D1.

> **Two notes on the *Order Manifest*, which is a dated record and is never edited.** First, its
> customs section quotes a **CAD $150** duty de minimis against the AliExpress order; that is the
> CUSMA figure for shipments from the **US or Mexico**, and for a parcel from China it is **CAD $20**.
> *Before You Build*'s glossary carries the correct rule. The manifest's conclusion still holds, and
> for the better of its two reasons — most of what you bought carries a **0 % MFN rate**, so it is
> duty-free by classification rather than by threshold — but keep its C$20–40 buffer rather than
> treating "under the limit" as the reason nothing will be charged.
>
> Second, its *Deliberately deferred* section estimates Stage 1 at ~C$140 and Stage 4 at ~C$190. Those
> were July guesses made before either list existed. **Tiers C and F on this page supersede them**
> (C$60 and C$165), and the variance table below is computed against the Project Guide's Appendix B
> estimates rather than against the manifest's.

### Against the original budget

```
Already spent (pre-tax)          C$  534
Remaining, minimum path          C$  912
                                 ─────────
Project total, pre-tax           C$1,446
Project total, with 14% HST      C$1,648

Project Guide Appendix B estimate:  C$1,380 pre-tax (budget path)
Variance:                          +C$   66
```

**Do not read that +C$66 as "the estimate held up."** It is a net figure hiding movements nearly three
times its own size, and the interesting engineering is in the components rather than the sum. Written
out: **+$184 of tooling overrun, offset by −$118 of downstream under-spend — and 184 − 118 = 66.**

| Against the Guide's per-stage estimate | Estimated | Now | Variance |
|---|---|---|---|
| Tooling + Stage 0 (the 31 July order) | $350 | **$534 actual** | **+$184** |
| Stage 1 | $90 | $60 | −$30 |
| Stage 2 | $700 | $687 | −$13 |
| Stage 3 | $60 | $0 | −$60 |
| Stage 4 | $180 | $165 | −$15 |
| **Net** | | | **+$66** |

The honest reading: **the tooling and Stage 0 estimate was wrong by 53 %** — $184 over on $350 — and
that overrun is being concealed by four downstream stages coming in slightly under. Two of those four
are under only because you already own hardware (the second motor, the spare TB6612FNGs, the 120 Ω
resistors, the SG90), and one — Stage 3 at zero — is under only if your shelf actually contains a
webcam and a microphone. **That is a forecast with two soft assumptions in it, not a forecast that came
true.** Say so; a hiring manager who has ever run a budget will notice which version you wrote.

Note also that Stage 2's minimum sits $13 under while carrying a **known, quantified, deliberately
deferred** margin purchase — the power supply. A line that says "measured, adequate for now, upgrade
costed at C$25 if the measurement says otherwise" is a healthier budget entry than one that is simply
lower, and it is worth writing it that way rather than banking the saving silently.

Note also which direction the net has moved and why. It is smaller than the tooling overrun alone
because tooling is bought once, up front, and everything after it is bought against a list — which is
the same asymmetry the lesson below names, seen from the other end.

The lesson worth taking is the one the first order already taught: tooling is systematically
under-estimated because it is bought once and remembered vaguely, while parts are itemised and
remembered precisely.

---

## Verify before ordering — spec traps

Every trap in this table has cost somebody a part or a weekend. Read it before each order.

| Trap | Check |
|---|---|
| Nucleo authenticity | **DigiKey only.** Clone ST-Link is non-functional and the silicon may be counterfeit. |
| CAN transceiver logic level | **SN65HVD230 is 3.3 V** — correct for STM32. TJA1050 is 5 V and wrong for it. |
| AS5600 magnet | **Diametric, not axial.** They look identical and axial silently fails. |
| AS5600 address | **0x36, unchangeable.** Two sensors require the TCA9548A. |
| Motor driver current | TB6612FNG is **1.2 A continuous / 3.2 A *pulse*** — the second figure carries a duty and pulse-width limit and does **not** bound a sustained stall. The JGB37-520 family is **≤ 1 A rated, 2.3 A stall**: inside the continuous rating by 17 %, and over it by 2× during a stall that your S11 latch has to cut short. Buy a bigger driver on **margin**, not because the TB6612 is incompatible. Check rated *and* stall current before ordering motors, not after. |
| Printer nozzle | **Hardened nozzle and hotend temperature rating**, for carbon-filled filament. Verify per SKU. |
| Motor torque figures | Vendor listings for the same part number disagree by an order of magnitude. Compare **rated** (continuous) torque, not stall, and note which you used. |
| **JGB37-520 variant** | The part number is a *body*, not a spec — the same string covers 10:1/1000 RPM/1.6 kg·cm and 270:1/37 RPM/30 kg·cm. **Order by ratio and RPM.** Buying the wrong variant silently undoes S2.4. |
| **JGB37-520 encoder resolution** | Vendor listings quote `11 × ratio` = 2,970 counts/rev. That is a **×1** figure. With ×4 quadrature decoding you will measure **11,880**. Same PPR/CPR trap, new motor. |
| **Joint speed after Path A** | 270:1 gives **37 RPM**, not 100. The arm is 2.7× slower: the no-load ceiling drops to ~3.87 rad/s, and `V_MAX` has to come down from 3.0 to ~1.1 rad/s to keep the margin you chose. Confirm that is acceptable *before* ordering. |
| Webcam focus | **Fixed focus beats autofocus** for Stage 3. Autofocus silently invalidates your camera calibration. |
| IMU fusion | **Raw six-axis.** A chip that fuses internally removes the exercise. |
| E-stop wiring | Cuts **motor** power, not logic — so the system survives to report what happened. |
| ESP32-S3 cable | **USB-C.** Your UNOs are USB-B. |
| Encoder shield grounding | **One end only.** Grounding both ends creates a ground loop. |
| INA219 count | You own **three** and the project consumes exactly three: two joints plus the gripper. **Zero spare — one is costed in Tier B at C$3.** If you ever go to four joints that is four more, not two. |

---

## The three decisions still open

1. **CANable, or ESP32-S3 as bus monitor?** Buying it moves native Ubuntu earlier. *(Tier C)*
2. **How do you close the shoulder torque gap?** Path A (bigger motors) is the only option that
   reaches the number with margin. Path B alone is 5–6.7× short; the full stacked combination —
   shorter links, counterbalance, base-mounted motors, 5:1 belt — reaches *exactly* break-even on the
   optimistic torque figure and is 5× short at the same ratio on the honest one, while costing you
   110 mm of reach and
   a much harder CAD problem. The arithmetic is in S2.4. Path A also costs you 2.7× in joint speed —
   weigh that too. *(Tier D1)*
3. **KiCad carrier board, yes or no?** Adds about a week between Stages 1 and 2, and adds PCB design
   to your resume. *(Tier G)*

Write an ADR — an **Architecture Decision Record**, a short file recording a choice that had real
alternatives — for each when you decide. Those three files are exactly the kind of thing an interview
probes, and a note written the day you decided is evidence where a recollection eight months later is
a guess.
