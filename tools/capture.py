# tools/capture.py
"""Read CSV rows from the UNO and write them to a timestamped file.

STUB. The body is TODO. See Stage 0 Workbook, S7.

Usage (intended):
    python tools/capture.py --port COM3 --tag step-90deg
"""

import argparse, csv, sys, time
import serial          # pyserial

# TODO:
#  - open the port at 250000 baud, discard the first line
#  - read until KeyboardInterrupt, writing to docs/tuning/raw/<date>-<tag>.csv
#  - on exit report rows, elapsed time and measured rows/sec. That last one is a
#    second, independent check on the loop rate.
