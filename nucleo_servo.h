#ifndef _NUCLEO_H_
#define _NUCLEO_H_

class Servo {

public:
    Servo(PinName pin);
    ~Servo();
    void set_position(float deg);  
    void turn_left(float deg); 
    void turn_right(float deg); 
private:
    PwmOut *servoPWM;
    float degrees;
};
    

#endif