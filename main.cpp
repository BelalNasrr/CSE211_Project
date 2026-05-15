#include "mbed.h"
#include "Ultrasonic.h"
#include "Motor.h"
#include <cstdio>

// Ultrasonic sensor pins
#define TRIG_PIN    D9
#define ECHO_PIN    D10

// Motor 1 driver pins  
#define MOTOR1_PWM   D5 // controls speed 
#define MOTOR1_FWD   D3 // both control direction 
#define MOTOR1_REV   D4

// Motor 2 driver pins 
#define MOTOR2_PWM   D6  // controls speed 
#define MOTOR2_FWD   D7 // both control direction 
#define MOTOR2_REV   D8

#define FORWARD_SPEED      0.3f

int main() {
    Ultrasonic sensor(TRIG_PIN, ECHO_PIN);
    
    // Initialize both motors
    Motor motor1(MOTOR1_PWM, MOTOR1_FWD, MOTOR1_REV);
    Motor motor2(MOTOR2_PWM, MOTOR2_FWD, MOTOR2_REV);
    
    while (true) {
        int distance = sensor.getDistance();
        
        if ((distance <=15) || (distance >=40))  { // stop if dist >=40 or dist<=15
            // Sensor error - stop both motors
            motor1.stop();
            motor2.stop();
            printf("Too colose ! stopping.\r\n");
        }
        else {
            // Clear path - move forward with both motors
           motor1.moveForward(FORWARD_SPEED);
           motor2.moveForward(FORWARD_SPEED);
           printf("Object at %d cm -  MOVING FORWARD at %.1f%%\r\n", 
                   distance, FORWARD_SPEED * 100);
        }
        
        ThisThread::sleep_for(100ms);
    }
}
