// telemetry.h: Stage 0, S7. CSV rows out of the control loop, within a budget.
// Declarations only. See Stage 0 Workbook, S7.

#pragma once
#include <Arduino.h>

// Emit one CSV row. Integers only, no floats on the wire.
// Called from the control loop, AFTER motor.write(), so logging cost
// is never between sensing and acting.
void logRow(uint32_t tMs, long targetCounts, long posCounts, int16_t cmd);

// Decimation: log every Nth tick. Set to 1 for full rate.
// DECLARED here, DEFINED exactly once in telemetry.cpp.
extern uint8_t logEveryN;

// TODO (S7): size the row against the serial budget before writing it, and
//            recheck it when S11 raises the loop rate.
// TODO: emit a header row once at startup, or pandas loads every column as a
//       string and the plot silently makes no sense.
