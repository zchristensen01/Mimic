// pid.h: Stage 0, S8, extended in S10. A PID controller you wrote.
// Declarations only. See Stage 0 Workbook, S8 and S10.

#pragma once

class PIDController {
public:
  void  setGains(float kp, float ki, float kd);
  void  setOutputLimits(float lo, float hi);
  void  reset();                                  // clears integral_ and prevMeas_

  // dt in seconds. Returns a clamped command in [lo, hi].
  float update(float target, float measured, float dt);

private:
  float kp_ = 0, ki_ = 0, kd_ = 0;                // units: cmd/rad, cmd/(rad·s), cmd·s/rad
  float integral_ = 0;
  float prevMeas_ = 0;                             // measurement, not error. See S10
  float lo_ = -1.0f, hi_ = 1.0f;
};

// TODO (S8):  kp_ only. The rest stay declared and unused until S10.
// TODO (S10): D on measurement and negated, both anti-windup mechanisms, and a
//             guard on Ki == 0.
//
// TODO: the derivative filter constant is its own decision. Write the ADR as
//       derivative-filter.md.
