# Bill of materials

The assembly-oriented view: what each part is for, per stage. Not the purchase history, which is
[the Order Manifest](../docs/guides/Mimic_Order_Manifest.md) and is never edited, and not the forward
plan, which is [What's Left to Buy](../docs/guides/Mimic_Still_To_Buy.md) with its costed tiers.

Prices in CAD, pre-tax and post-tax shown separately. Nova Scotia HST is 14%.

The spec traps to check before each order are in *What's Left to Buy*. Read them there rather than
keeping a second copy here that can go stale against the first.

## Stage 0: The Single Joint

| Part | Qty | Vendor | Unit | Ext. | For | Status |
|---|---|---|---|---|---|---|
| 12GA-N20 12 V 100 RPM encoder gearmotor | | | | | The joint | Owned |
| TB6612FNG motor driver | | | | | Drives the motor | Owned |
| Arduino UNO | | | | | Control loop | Owned |
| 12 V 5 A supply | | | | | Motor rail | Owned |
| XL4015 buck converter | | | | | 12 V to 5 V logic | Owned |
| 1000 µF electrolytic | | | | | Bulk capacitance at the driver | Owned |
| 100 nF ceramic | | | | | Decoupling, at the motor terminals | Owned |
| Roller-lever microswitch | | | | | Limit switch, S11 | Owned |
| 24 MHz 8-channel logic analyzer | | | | | Loop-rate and PWM proof | Owned |
| Plywood board, ~9.5 × 20 × 0.5 in | 1 | offcut / local | ~10 | | The rigid base | VERIFY |
| Two G-clamps | 2 | local | ~10/pr | | Clamp the plank to the desk | VERIFY |
| Drill and a 3 mm bit | 1 | borrow / local | ~40 | | Inserts and through-bolts | VERIFY |
| ~2 mm precision screwdriver | 1 | local | 5-8 | | Turns a multi-turn trim pot | VERIFY |
| Safety glasses | 1 | local | ~8 | | Drilling, soldering, snipping legs | VERIFY |
| Power switch | 1 | | | | Breaks the 12 V rail | VERIFY |

The rows marked VERIFY appear in no parts document at all. They were assumed rather than bought, so
check for them this week rather than at 9 p.m. on the evening you wanted to run a session.

**Stage 0 subtotal:** TODO pre-tax / TODO with HST

## Stage 1: The Smart Joint

| Part | Qty | Vendor | Unit | Ext. | For | Status |
|---|---|---|---|---|---|---|
| Nucleo-F446RE | 1 | DigiKey | 28.01 | | The joint board | Order |
| SN65HVD230 CAN transceiver module | 4 | AliExpress | ~3 | 12 | 3.3 V logic, correct for STM32 | Order |
| Twisted pair / CAT5 offcut | 2 m | local | | 10 | The bus | Order |
| JST-XH 4-pin connectors | 1 set | AliExpress | | 10 | Daisy-chainable joint bus | Order |
| 120 Ω resistors | 2 | | | | Termination, one at each physical end | Owned (100) |
| Second gearmotor | 1 | | | | Joint 2 | Owned |
| Second TB6612FNG | 1 | | | | Joint 2 | Owned |
| MCP2515 + TJA1050 module | 2 | AliExpress | | 8 | Optional. Prototype CAN framing on an UNO | Decide |
| Second Nucleo-F446RE | 1 | DigiKey | 28 | | Optional. Alternative to an ESP32-S3 | Decide |
| CANable 2.0 | 1 | Openlight Labs | ~50 | | Optional, and a real decision | Decide |

C$60 for the four required lines. C$146 with all three optional ones.

## Stage 2 and beyond

**TODO.** Populate from *What's Left to Buy* Tiers D to G as each order is placed. The actuation line
is blocked on the arm-actuation ADR, 0011: the torque budget in S2.4 decides which motors get bought.

## Parts with no datasheet

Two, and that is a fact about the parts rather than a failure of your searching. For both:
screenshot the listing you bought from, record the claim, measure the reality, write down the gap.

| Part | Where the real numbers come from |
|---|---|
| 12GA-N20 motor | [`docs/motor-spec.md`](../docs/motor-spec.md), measured in S1 and S3 |
| SG90 servo | A form factor made by dozens of factories. Stage 2 S2.10 measures it |
