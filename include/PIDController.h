#ifndef SPACE_SHOOTER_PIDCONTROLLER_H
#define SPACE_SHOOTER_PIDCONTROLLER_H

#include <algorithm>

class PIDController {

public:
    PIDController(float kp, float ki, float kd, float integralLimit);
    float pidOutput(float setpoint, float actualValue, float deltaTime);
    float pidOutput(float error, float deltaTime);

private:
    float kp_;
    float ki_;
    float kd_;
    float previousError_;
    float integral_;
    float integralLimit_;
};


#endif //SPACE_SHOOTER_PIDCONTROLLER_H
