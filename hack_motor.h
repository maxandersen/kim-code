#ifndef HACK_MOTOR_H
#define HACK_MOTOR_H
#include "mbed.h"

class Wheel {
 
public:
    
    Wheel(PinName M1A_pin, PinName M1B_pin, PinName M2A_pin, PinName M2B_pin);
    ~Wheel();
    void FW(); // Forward
    void BW(); // Backwards
    void right(); // Right
    void left(); // Left
    void stop(); // Stop
    void init(); // Init
    void set_speed(float speed); // set your wanted speed (0..1.0)
    float get_speed(); // get the actual speed
    void FW(float right, float left); // Overload Forward with right motor speed, left motor speed
    
private:
    float fw, bw;
    float speed;
    PwmOut *M1A;
    PwmOut *M2A;    
    DigitalOut *M1B; 
    DigitalOut *M2B;
};

#endif