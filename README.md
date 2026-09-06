# Mimic

Mimic is a desk-sized robotic arm in which every joint runs its own microcontroller. It holds a commanded angle against gravity and external force with control code written from scratch rather than imported. No libraries. Those joint controllers are independent nodes all on a CAN bus, and a Linux host running ROS 2 sees, plans the motion, listens and records. 

It is my portfolio project to break me into the robotics industry after a 3 years of experience as a software engineer, but no experience in embedded work. The repository is the deliverable and the arm is the reason to have one. I figure a proper repository shows more than what following a youtube tutorial would do.

> **Mimic is a learning platform for learners. It is not a medical device and must not be used as one.** It is not developed to any safety or medical standard, it has no clinical validation, and nothing in it should be used on or around a person in a therapeutic context.

## How this was built

The planning documents in [`docs/guides/`](docs/guides/) and the initial repository scaffolding were drafted by Claude Code. I wanted to make sure I had a good foundation to learn from, and that the things that would stop me from learning, getting started, or missing any parts, would not hold me back. I directed and reviewed both, read them all through, and I use the tools the way I would expect to use them at work - for learning, clarity, and debugging as a last resort. No code was written by an LLM, and I take pride in that.

Everything the project is actually about is mine. Every number here is measured on my own bench, not taken from the internet. Every decision recorded here is my conclusion based on real testing. Every derivation is photographed from my own journal and own bench to document my progress in a way that AI cannot do for someone - to prove that I did this properly. The firmware, the debugging, the tuning, and the commit history, aside form the first commit of the scaffolding and guides, is all my work

## Status

S0: Guides and skeleton commited and toolchain works

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

Commits, branches and tags follow the scheme in [*Before You Build*](docs/guides/Mimic_Before_You_Build.md), Part III.

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
