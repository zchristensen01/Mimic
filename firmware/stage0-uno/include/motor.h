// motor.h: Stage 0, S4. TB6612FNG channel A, driven as one motor.
// Declarations only. See Stage 0 Workbook, S4.

#pragma once
#include <Arduino.h>

class Motor {
public:
  void begin(uint8_t pwmPin, uint8_t in1, uint8_t in2, uint8_t stby);

  // cmd in [-255, +255]. Sign selects direction, magnitude sets duty.
  // Clamps internally. Positive cmd MUST make Encoder::count() increase.
  void write(int16_t cmd);

  void coast();     // both inputs low, motor free-wheels
  void brake();     // both inputs high, motor terminals shorted
  void enable(bool on);   // STBY

private:
  uint8_t pwm_ = 0, in1_ = 0, in2_ = 0, stby_ = 0;
};

// TODO: fix the sign convention here and only here. If +100 makes count()
//       decrease, swap AIN1 and AIN2 in this file rather than swapping the wires
//       or negating the encoder.
//
// TODO: coast or brake at zero command. Decide it deliberately and write the ADR.
