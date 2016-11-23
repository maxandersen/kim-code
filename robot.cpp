/*
 ============================================================================
 Name        : robot.cpp
 Author      : Team 5
 Version     : 0.1
 Date        : 13-10-2016
 Copyright   : Open for all
 Description : Program to serve the platform for Pro1 2016
 ============================================================================
 */
#include "odometry.h"
#include "mbed.h"
#include "HCSR04.h"
#include "nucleo_servo.h"
#include "hack_motor.h"
#include <math.h> 

void startfunction( );
Ticker T1; // create an object T1 of Ticker

/*
----------------------------------------------------------------------------
                                MAIN FUNCTION
----------------------------------------------------------------------------*/
int main()
{
/*
=============================================================================
Driving and stopping the robot with member functions from the wheel class
=============================================================================*/
    startfunction();    //  1. DRIVE  
    while(Dtravel_1() <= DISTANCES[0])  //  OVERVEJ AT SMIDE "get_to_goal" funktionen ind i selve while loopet, sådan, at beregningerne sker parallelt. 
    {
        get_to_goal(); //   TJEK DETTE
        robot.FW(0.5, 0.5);
        wait_ms(5000);
    }
    
    robot.stop(); 
    printf("\n\rtimeused = %4d tickL= %4d  tickR = %4d \n", t.read_ms(),tickL,
           tickR);   
    wait_ms(3000);
} 
/*  
----------------------------------------------------------------------------
                            END OF MAIN FUNCTION
----------------------------------------------------------------------------*/

void startfunction()
{
    T1.attach(&read_analog, 1.0); // attach the address of the read_analog
    //function to read analog in every second

    tacho_left.rise(&tickLeft);  // attach the address of the count function
    //to the falling edge
    tacho_right.rise(&tickRight);  // attach the address of the count function
    //to the falling edge

    HCSR04 sensor(PC_5,PC_6); // Create an object of HCSR04 ultrasonic with pin
    // (echo,trigger) on pin PC_5, PC6
    Servo servo1(PC_8);     //Create an object of Servo class on pin PC_8

    sensor.setRanges(2, 400); // set the range for Ultrasonic

/*
=============================================================================
Demo of the servor and ulta sonic sensor
=============================================================================*/  
    wait_ms(2000); // just get time for you to enable your screeen
    servo1.set_position(0); // Servo right position (angle = 0 degree) for servo
    wait_ms (500);
    printf("\r\nDistance: %5.1f mm \n", sensor.getDistance_mm()); // display the
    //readings from ultra sonic at this position
    servo1.set_position(180); // Servo left position (angle = 180 degree)
    //for servo
    wait_ms (500);
    printf("\r\nDistance: %5.1f mm \n", sensor.getDistance_mm());
    servo1.set_position(90); // Straight ahead (angle = 90 degree) for servo
    wait_ms (500);
    printf("\r\nDistance: %5.1f mm \n", sensor.getDistance_mm());

    init(); // initialise parameters (just for you to remember if you need to)

    wait_ms(1000); //wait 1 secs here before you go
    t.start();      // start timer (just demo of how you can use a timer)
}