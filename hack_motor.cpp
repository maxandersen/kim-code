#include "mbed.h"
#include "hack_motor.h"
#include "PwmOut.h"

Wheel::Wheel(PinName M1A_pin, PinName M1B_pin, PinName M2A_pin, PinName M2B_pin)
{
    M1A = new PwmOut(M1A_pin);
    M2A = new PwmOut(M2A_pin);
    M1B = new DigitalOut(M1B_pin);
    M2B = new DigitalOut(M2B_pin);
    init();
}

Wheel::~Wheel() // Destructor, cleans up
{
    delete M1A;
    delete M2A;
    delete M1B;
    delete M2B;
}

void Wheel::init() //Initialize the driver pwm to 50Hz
{
    M1A->period_ms(20);
    M2A->period_ms(20);
    speed = 0.0;
}

void Wheel::set_speed(float speed)
{
    this->speed = speed;
}

float Wheel::get_speed()
{
    return speed;
}

void Wheel::FW()
{
    fw = speed;
    M1A->write(fw); //Set the duty cycle to the wanted percent, from speed variable
    M2A->write(fw); // -//-
    *M1B = 0;
    *M2B = 0;
    wait_ms(1);
}

void Wheel::FW(float right, float left) // set the actual speed for right, left motor
{
    
    M1A->write(right); //Set the duty cycle to the wanted percent, from speed variable
    M2A->write(left); // -//-
    *M1B = 0;
    *M2B = 0;
    wait_ms(1); 
}

void Wheel::BW()
{
    bw = 1 - speed;
    M1A->write(bw); //Set the duty cycle to the wanted percent, from speed variable
    M2A->write(bw); // -//-
    *M1B = 1;
    *M2B = 1;
}

void Wheel::right()
{
    /*    M1A->write(0.75f * speed);
        M2A->write(1 - 0.25f * speed);
        *M1B = 0;
        *M2B = 1;
        */

    M1A->write(speed);
    M2A->write(0.0f);
    *M1B = 0;
    *M2B = 0;
}

void Wheel::left()
{
    /*
     M1A->write(1 - 0.25f * speed);
     M2A->write(0.75f * speed);
     *M1B = 1;
     *M2B = 0;
     */
    M1A->write(0.0f);
    M2A->write(speed);
    *M1B = 0;
    *M2B = 0;
}

void Wheel::stop()
{
    M1A->write(0.0f);
    M2A->write(0.0f);
    *M1B = 0;
    *M2B = 0;
}