# Mimic

Mimic is a desk-sized robotic arm in which every joint runs its own microcontroller, holding a
commanded angle against gravity and disturbance with control code written from scratch rather than
imported. Those joint controllers are independent nodes on a CAN bus, and a Linux host running ROS 2
plans motion, sees, listens and records. It is a portfolio project: the repository is the deliverable
and the arm is the reason to have one.

> **Mimic is a learning platform. It is not a medical device and must not be used as one.** It is not
> developed to any safety or medical standard, it has no clinical validation, and nothing in it
> should be used on or around a person in a therapeutic context.

## How this was built

<!-- DRAFT. Your voice and your call, so rewrite it or cut it back. -->

The planning documents in [`docs/guides/`](docs/guides/) and the initial repository scaffolding were
drafted with AI assistance. I directed and reviewed both, and I use the tools the way I would expect
to use them at work.

Everything the project is actually about is mine. Every number here is measured on my own bench, not
quoted from a listing. Every decision recorded here is my reasoning about my own trade-offs. Every
derivation is photographed in my handwriting. The firmware, the debugging, the tuning and the commit
history from session S0 onward are my work.

## Status

Stage 0, The Single Joint. Nothing tagged yet; the first will be `v0.0-stage0-exit`.

<!-- TODO: one line on what works today. Update at every exit gate. -->

## The argument

<!-- TODO: this README becomes an argument rather than usage documentation, one section per decision
     that had real alternatives. Write each section as the stage that decides it lands, not before. -->

## Layout

| Path | What is in it |
|---|---|
| [`firmware/stage0-uno/`](firmware/stage0-uno/) | Stage 0 PlatformIO project, the single-joint PID rig |
| [`firmware/stage1-stm32/`](firmware/stage1-stm32/) | Stage 1 STM32CubeIDE project, FreeRTOS and CAN |
| [`hardware/`](hardware/) | CAD sources and exports, dated wiring photographs, bill of materials |
| [`docs/derivations/`](docs/derivations/) | Scanned handwritten maths, dated the day it was done |
| [`docs/tuning/`](docs/tuning/) | Gain logs, captured CSVs, generated plots |
| [`docs/reference/`](docs/reference/) | Datasheets and vendor material brought in from elsewhere |
| [`docs/guides/`](docs/guides/) | The document set this project is built from |
| [`docs/protocol.md`](docs/protocol.md) | The CAN message specification |
| [`docs/motor-spec.md`](docs/motor-spec.md) | Measured motor constants |
| [`tools/`](tools/) | Host-side capture and plotting |

Commits, branches and tags follow the scheme in
[*Before You Build*](docs/guides/Mimic_Before_You_Build.md), Part III.

## Stages

| Stage | What it ends with | Gate tag |
|---|---|---|
| 0 · The Single Joint | One motor holding a commanded angle against a disturbance | `v0.0-stage0-exit` |
| 1 · The Smart Joint | Two joints on a CAN bus running identical firmware | `v0.1-stage1-exit` |
| 2 · The Arm and ROS 2 | A physical arm commanded in Cartesian space | `v0.2-stage2-exit` |
| 3 · Eyes and Voice | An arm that sees and listens | TBD |
| 4 · The Biomech Payload | An arm driven by muscle activity | TBD |
| 5 · Impedance (optional) | An arm that is compliant rather than stiff | TBD |

## Building

```bash
# Stage 0 firmware
pio run -e uno -d firmware/stage0-uno

# Stage 0 host-side unit tests, no board required. Not usable until S12: the
# classes are declarations with no bodies yet, so this environment has nothing
# to build. CI builds the firmware only, for the same reason.
pio test -e native -d firmware/stage0-uno
```

## Licence

MIT. See [LICENSE](LICENSE).
