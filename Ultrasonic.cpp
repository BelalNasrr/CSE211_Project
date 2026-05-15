#include "Ultrasonic.h"

#define TIMEOUT_US 30000

Ultrasonic::Ultrasonic(PinName trigger_pin, PinName echo_pin)
    : _trigger(trigger_pin), _echo(echo_pin), _distance(-1)
{
    _trigger = 0;

    _echo.rise(callback(this, &Ultrasonic::echoRise));
    _echo.fall(callback(this, &Ultrasonic::echoFall));
}

int Ultrasonic::getDistance() {
    _distance = -1;

    _timer.stop();
    _timer.reset();

    // Trigger pulse
    _trigger = 1;
    wait_us(10);
    _trigger = 0;

    // Wait for result or timeout
    int timeout = TIMEOUT_US;
    while (_distance < 0 && timeout > 0) {
        wait_us(10);
        timeout -= 10;
    }

    return _distance;
}

void Ultrasonic::echoRise() {
    _timer.reset();
    _timer.start();
}

void Ultrasonic::echoFall() {
    _timer.stop();

    auto duration = _timer.elapsed_time();
    float time_us = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();

    _distance = (int)(time_us / 58.0f);

    _timer.reset();
}
