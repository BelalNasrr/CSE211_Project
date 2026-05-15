//Include the motor header file
#include "Motor.h"

/*
    Function to attach motor pins to microcontroller pins
*/
Motor::Motor(PinName pwm_pin, PinName forward_pin, PinName reverse_pin)
    : _pwm(pwm_pin), _forward(forward_pin), _reverse(reverse_pin)
{

    _pwm.period(0.02f);//set pwm frequency  50 Hz
    stop();//Initialize motors to stop 
}

/*
    Function to move motors forward
    Maps speed % to be between 1(100%) and 0(0%) and sets direction of motors 
    Input: speed
*/
void Motor::moveForward(float speed) {
    if (speed > 1.0f) speed = 1.0f;
    if (speed < 0.0f) speed = 0.0f;
    _forward = 1;
    _reverse = 0;
    _pwm = speed;
}
/*
    Function to move stop the motors
*/
void Motor::stop() {
    _forward = 0;
    _reverse = 0;
    _pwm = 0;
}
