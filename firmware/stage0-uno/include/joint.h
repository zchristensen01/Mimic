// joint.h: Stage 0, S12. One joint as an object, and the artifact Stage 1
// flashes to more than one board. Declarations only. See Stage 0 Workbook, S12.

#pragma once
#include "encoder.h"
#include "motor.h"
#include "pid.h"

// TODO (S12): begin() takes this and the workbook never gives its shape. Define
// it. At minimum: the four Motor pins, the two Encoder pins, the three gains, the
// soft limits, V_MAX and the command timeout. Decide whether it also carries the
// output limits.
struct JointConfig;

struct JointState {
  float   positionRad;
  float   velocityRadS;
  float   setpointRad;
  int16_t command;
  uint8_t flags;          // saturated | faulted | timeout | homed
};

class Joint {
public:
  void begin(const JointConfig& cfg);

  void setTarget(float rad);        // rejects out-of-range, returns via state flags
  void tick(float dt);              // sense, limit, think, act. Called at fixed rate.
  JointState state() const;         // this is what Stage 1 serialises into a CAN frame

  void clearFault();

private:
  Encoder       enc_;
  Motor         motor_;
  PIDController pid_;
  float targetRad_ = 0, setpointRad_ = 0;
  float minRad_ = 0, maxRad_ = 0, vMaxRadS_ = 0;
  uint32_t lastCommandMs_ = 0;
  uint8_t  flags_ = 0;
};

// TODO (S11): tick() owes soft limits, velocity limiting, fail-safe on silence
//             and stall detection, in that order. The failsafe behaviour is its
//             own decision: write the ADR as failsafe.md.
//
// TODO: state() returns by value from members the ISR updates, with no torn-read
//       guard. Same bug as count_ in S3, one level up.
