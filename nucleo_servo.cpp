#include "mbed.h"
#include "nucleo_servo.h"
   
Servo::Servo(PinName pin){
    servoPWM = new PwmOut(pin);
    servoPWM->period_ms(20);  //Do not change ;)
    servoPWM->pulsewidth_us(600);
    degrees = 0;
}
Servo::~Servo(){
    delete servoPWM;  
}

void Servo::set_position(float deg){
    degrees = deg;
    if(degrees > 180)degrees = 180;
    if(degrees < 0)degrees = 0;
    int pw_us = 640 + (degrees / 180 * 1900); 
    servoPWM->pulsewidth_us(pw_us);
}
    
void Servo::turn_left(float deg){
    degrees -= deg;
    set_position(degrees);
}

void Servo::turn_right(float deg){
    degrees += deg;
    set_position(degrees);
}
