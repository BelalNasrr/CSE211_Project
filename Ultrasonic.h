/**
 * @file Ultrasonic.h
 * @brief HC-SR04 ultrasonic distance sensor interface

 */

#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include "mbed.h"

/**
 * @class Ultrasonic
 * @brief Measures distance using HC-SR04 ultrasonic sensor
 * 
 * Usage example:
 * @code
 * Ultrasonic sensor(PA_6, PA_7);  // Trigger pin, Echo pin
 * int distance = sensor.getDistance();  // Get distance in cm
 * @endcode
 */
class Ultrasonic {
public:
    /**
     * @brief Construct an Ultrasonic sensor object
     * @param trigger_pin Pin connected to sensor TRIG (DigitalOut)
     * @param echo_pin    Pin connected to sensor ECHO (InterruptIn)
     */
    Ultrasonic(PinName trigger_pin, PinName echo_pin);
    
    /**
     * @brief Get current distance measurement
     * @return Distance in centimeters (integer)
     * 
     * Triggers a measurement and waits for result.
     * Returns -1 if measurement times out (object too far).
     */
    int getDistance();

private:
    DigitalOut   _trigger;   // Trigger pin - sends start pulse
    InterruptIn  _echo;      // Echo pin - receives return pulse
    Timer        _timer;     // Timer for measuring echo duration
    volatile int _distance;  // Stores last measured distance (volatile for ISR)
    
    /**
     * @brief Interrupt handler for rising edge of echo pulse
     * Starts the timer when echo goes HIGH
     */
    void echoRise();
    
    /**
     * @brief Interrupt handler for falling edge of echo pulse
     * Stops timer and calculates distance when echo goes LOW
     */
    void echoFall();
};

#endif // ULTRASONIC_H
