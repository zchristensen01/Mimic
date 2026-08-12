// encoder.h: Stage 0, S3. Quadrature decoding with x4 resolution, driven by both
// external interrupts. Declarations only. See Stage 0 Workbook, S3.

#pragma once
#include <Arduino.h>

class Encoder {
public:
  void begin(uint8_t pinA, uint8_t pinB);   // set pins, attach both ISRs, seed state_
  long  count() const;                       // atomic read of count_ (see note below)
  long  missed() const;                      // illegal-transition counter
  void  zero();                              // reset count_ to 0

  void  onEdge();                            // called from BOTH ISRs. Keep it tiny.

private:
  volatile long  count_  = 0;
  volatile long  missed_ = 0;
  volatile uint8_t state_ = 0;               // (A<<1)|B, previous
  uint8_t pinA_ = 0, pinB_ = 0;

  static const int8_t kTable[16];            // the table you derived above
};

// TODO: count() is const and still needs an interrupt guard against a torn read.
//       Write the RAII guard. Four lines.
//
// TODO: attachInterrupt takes a plain function pointer, so onEdge() needs a
//       file-scope shim. Decide single-instance or indexed NOW and write which,
//       at the shim: Stage 1 M1.7 constructs a second Joint.
