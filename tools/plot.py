# tools/plot.py
"""Plot a captured run and print its step-response metrics.

STUB. The body is TODO. See Stage 0 Workbook, S7 and S9.

Usage (intended):
    python tools/plot.py docs/tuning/raw/2026-08-04-run5.csv
"""

import pandas as pd
import matplotlib.pyplot as plt

# TODO:
#  - load CSV, convert counts to degrees, plot target and actual against command
#  - annotate the four S9 metrics, using one definition of each everywhere
#  - savefig to docs/tuning/plots/<date>-run<N>.png at 150 dpi. Do not show():
#    there is no display on a headless or WSL machine.
#
# COUNTS_PER_OUTPUT_REV comes from one place. Do not retype it here.
