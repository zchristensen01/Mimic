// main.cpp: Mimic Stage 0, The Single Joint.
//
// STUB. Empty setup()/loop() so the project builds from a clean checkout. All
// logic is TODO, session by session, in the Stage 0 Workbook.

#include <Arduino.h>

// #include "units.h"
// #include "encoder.h"
// #include "motor.h"
// #include "pid.h"
// #include "joint.h"
// #include "telemetry.h"

// The standing pin map is in the workbook and is fixed for the whole of Stage 0.
//   TODO (S3):  constexpr uint8_t PIN_ENC_A = 2;   // INT0
//   TODO (S3):  constexpr uint8_t PIN_ENC_B = 3;   // INT1
//   TODO (S4):  constexpr uint8_t PIN_PWMA  = 9;   // Timer1
//   TODO (S4):  constexpr uint8_t PIN_AIN1  = 7;
//   TODO (S4):  constexpr uint8_t PIN_AIN2  = 8;
//   TODO (S4):  constexpr uint8_t PIN_STBY  = 4;
//   TODO (S5):  constexpr uint8_t PIN_SCOPE = 5;   // loop-rate proof
//   TODO (S11): constexpr uint8_t PIN_LIMIT = 6;   // INPUT_PULLUP

// The fixed-rate schedule (S5).
//   TODO: static const uint32_t DT_US = 10000;   // 100 Hz, raised to 500 Hz in S11
//   TODO: static const float    DT_S  = DT_US / 1e6f;
//   TODO: uint32_t nextUs   = 0;                 // seeded in setup(), NOT here
//   TODO: uint32_t overruns = 0;

void setup() {
  // TODO (S0):  Serial.begin(250000);
  // TODO (S3):  encoder.begin(PIN_ENC_A, PIN_ENC_B);
  // TODO (S4):  motor.begin(PIN_PWMA, PIN_AIN1, PIN_AIN2, PIN_STBY);
  // TODO (S5):  pinMode(PIN_SCOPE, OUTPUT);
  // TODO (S5):  nextUs = micros();   // seed HERE, not at file scope
  // TODO (S11): pinMode(PIN_LIMIT, INPUT_PULLUP);
  // TODO (S11): reconfigure Timer1 for 31 kHz. Be able to explain why at the S12
  //             gate.
}

void loop() {
  // TODO (S5): the fixed-rate gate, then SENSE -> THINK -> ACT, with the scope
  //            pin raised at the top of the tick and lowered at the bottom.
  //            Advance the deadline by the period, and count overruns.
  //
  //   TODO (S3):  long  pos = encoder.count();          // SENSE
  //   TODO (S8):  int16_t u = pid.update();             // THINK
  //   TODO (S4):  motor.write(u);                       // ACT
  //   TODO (S7):  logRow();                             // TALK, last of all
}
