# Tuning

Gains, plots, and every measured number.

| Path | Contents |
|---|---|
| `YYYY-MM-DD-<tag>.md` | One file per bench session. The log |
| [`raw/`](raw/) | Captured CSVs off the serial port, written by `tools/capture.py` |
| [`plots/`](plots/) | Generated PNGs, written by `tools/plot.py` at 150 dpi |

Both `raw/` and `plots/` are committed: the CSV is the evidence and the PNG is regenerable from it,
but a plot you can open straight from a GitHub diff is worth more than one somebody has to run a
script to see.

Not here: decisions (those are ADRs), handwritten algebra (that is
[`../derivations/`](../derivations/)), and the motor's own constants rather than the controller's
(that is [`../motor-spec.md`](../motor-spec.md)).

The log format is in *Before You Build*, Part III. Two things it asks for that are easy to skip:
the **measured** loop rate at the top of every log rather than the intended one, and the units next
to each gain.

## Naming

```
docs/tuning/2026-08-04-step-response.md
docs/tuning/raw/2026-08-04-run5.csv
docs/tuning/plots/2026-08-04-run5.png
```

ISO dates, so chronological order is alphabetical order.
