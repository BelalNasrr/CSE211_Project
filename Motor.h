#ifndef MOTOR_H
#define MOTOR_H

#include "mbed.h"

class Motor {
public:
    // Constructor
    Motor(PinName pwm_pin, PinName forward_pin, PinName reverse_pin);

    // Move motor forward at specified speed (0.0 to 1.0)
    void moveForward(float speed);

    // Stop the motor immediately
    void stop();

private:
    PwmOut _pwm;          // PWM output for speed control
    DigitalOut _forward;  // Forward direction control
    DigitalOut _reverse;  // Reverse direction control
};  
#endif
