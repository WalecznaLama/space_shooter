#include "PIDController.h"

PIDController::PIDController(float kp, float ki, float kd, float integralLimit)
        : kp_(kp), ki_(ki), kd_(kd), integralLimit_(integralLimit), previousError_(0), integral_(0) {}

float PIDController::pidOutput(float error, float deltaTime) {
    integral_ += error * deltaTime;
    integral_ = std::clamp(integral_, -integralLimit_, integralLimit_);
    float _derivative = (error - previousError_) / deltaTime;

    float _output = (kp_ * error) + (ki_ * integral_) + (kd_ * _derivative);

    previousError_ = error;

    return _output;
}

float PIDController::pidOutput(float setpoint, float actualValue, float deltaTime) {
    float _error = setpoint - actualValue;
    return pidOutput(_error, deltaTime);
}




