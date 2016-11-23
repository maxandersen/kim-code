#ifndef ODOMETRY_H
#define ODOMETRY_H

#include "mbed.h"
#include "hack_motor.h"
#include "math.h"

//  ODOMETRY VALUES
#define N 20 // ticks on wheel
#define R 32.5 // radius = 32.5 mm
#define L 133 // 133 mm distance between wheels
#define PI 3.141592
int tickL = 0; // tick on left wheel
int tickR = 0; // tick on right wheel

//  PID VALUES
#define P_TERM 1.0
#define I_TERM 0.1
#define D_TERM 0
#define MAX 1.0 
#define MIN 0

//  GLOBAL DEFINITIONS
double right,left;
double speed=0.5;

//  ANALOG POWER
AnalogIn   ain(PC_4);
DigitalOut dout(PB_13);
DigitalOut greenout(PB_12);
int stop=0;         //DigitalOut DEFINITION OF RED LED!!

//  COORDINATES TO REACH
const double xPosition [] =
{
    [0] = 0,
    [1] = 1000,
    [2] = 2000,
    [3] = 3000,
    [4] = 4000,
    [5] = 5000,
    [6] = 4000,
    [7] = 3000,
    [8] = 2000,
    [9] = 1000,
    [10] = 2000,
    [11] = 3000,
    [12] = 4000,
    [13] = 5000,
    [14] = 1000
};
const double yPosition [] = 
{
    [0] = 0,
    [1] = 2000,
    [2] = 3000,
    [3] = 4000,
    [4] = 5000,
    [5] = 2000,
    [6] = 4000,
    [7] = 3000,
    [8] = 2000,
    [9] = 1000,
    [10] = 3000,
    [11] = 2000,
    [12] = 1000,
    [13] = 2000,
    [14] = 3000
};
const double THETA [] =
{
    [0] = 0.785,
    [1] = 1.047,
    [2] = 0.698,
    [3] = 0.524,
    [4] = 1.047,
    [5] = 0.698,
    [6] = 0.785,
    [7] = 0.873,
    [8] = 0.349,
    [9] = 0.349,
    [10] = 0.611,
    [11] = 0.611,
    [12] = 0.436,
    [13] = 0.96
}; //INCLUDE ANGLE TO HEAD BACK TO ORIGIN POSITION!!!!!

const double DISTANCES [] = 
{
    [0] = sqrt(pow((xPosition[1] - xPosition[0]), 2) + pow((yPosition[1] - yPosition[0]), 2)),
    [1] = sqrt(pow((xPosition[2] - xPosition[1]), 2) + pow((yPosition[2] - yPosition[1]), 2)),
    [2] = sqrt(pow((xPosition[3] - xPosition[2]), 2) + pow((yPosition[3] - yPosition[2]), 2)),
    [3] = sqrt(pow((xPosition[4] - xPosition[3]), 2) + pow((yPosition[4] - yPosition[3]), 2)),
    [4] = sqrt(pow((xPosition[5] - xPosition[4]), 2) + pow((yPosition[5] - yPosition[4]), 2)),
    [5] = sqrt(pow((xPosition[6] - xPosition[5]), 2) + pow((yPosition[6] - yPosition[5]), 2)),
    [6] = sqrt(pow((xPosition[7] - xPosition[6]), 2) + pow((yPosition[7] - yPosition[6]), 2)),
    [7] = sqrt(pow((xPosition[8] - xPosition[7]), 2) + pow((yPosition[8] - yPosition[7]), 2)),
    [8] = sqrt(pow((xPosition[9] - xPosition[8]), 2) + pow((yPosition[9] - yPosition[8]), 2)),
    [9] = sqrt(pow((xPosition[10] - xPosition[9]), 2) + pow((yPosition[10] - yPosition[9]), 2)),
    [10] = sqrt(pow((xPosition[11] - xPosition[10]), 2) + pow((yPosition[11] - yPosition[10]), 2)),
    [11] = sqrt(pow((xPosition[12] - xPosition[11]), 2) + pow((yPosition[12] - yPosition[11]), 2)),
    [12] = sqrt(pow((xPosition[13] - xPosition[12]), 2) + pow((yPosition[13] - yPosition[12]), 2)),
    [13] = sqrt(pow((xPosition[14] - xPosition[13]), 2) + pow((yPosition[14] - yPosition[13]), 2))
};  //REMEMBER TO INCLUDE DISTANCE FOR TRAVELLING BACK AGAIN

/*
=============================================================================
TIMER, TACHO'S AND ATTACHED PINS TO H-BRIDGE
=============================================================================*/
Timer t; // DEFINE A TIMER T
Serial pc(USBTX, USBRX); // not used here because we only have one serial
// connection
InterruptIn tacho_left(PC_3); // Set PC_2 to be interupt in for tacho left - Ledningsfarve: Hvid
InterruptIn tacho_right(PC_2);// Set PC_3 to be interupt in for tacho right - Ledningsfarve: Grå

Wheel robot(PB_2, PB_1, PB_15, PB_14);  //PB_15: grøn PB_14: blå PB_2: orange PB_1: gul
// create an object of robot H-bridge. ---(M1A, M1B, M2A, M2B)---

/*      USED FUNCTIONS IN ROBOT.CPP*/

void read_analog() // comes here every second in this case
// could be flagged with global variables like "stop"
{
    if(ain > 0.6f) { // 60% power, time for recharge
        dout = 1;
        stop=0;
    } else {
        dout = not dout;
        stop=1; // flash red led
    }

    if (ain==1.0f) greenout = 1; // full power
    else greenout = 0;
}

//  INIT YOUR PARAMETERS
void init()
{
    tickL=0;
    tickR=0;
}

//  SENSOR INFO FROM TACO SENSORS
void tickLeft() // UPDATE LEFT TICK ON INTERRUPT
{
    tickL++;
}
void tickRight() // UPDATE RIGHT TICK ON INTERRUPT
{
    tickR++;
}
float Dleft() // DISTANCE FOR LEFT WHEEL
{
    return 2*PI*R*tickL/N;
}

float Dright() // DISTANCE FOR RIGHT WHEEL
{
    return 2*PI*R*tickR/N;
}

float Dcenter() // DISTANCE FOR CENTER
{
    return (Dleft()+Dright())/2;
}

float DeltaTHETA()  //UPDATE ON ANGLE
{
    return (Dright()-Dleft())/2*L;
}

    //  X POSITIONS
float DeltaX_1()    //  1. X POSITION
{
    return Dcenter()*cos(THETA[0]+DeltaTHETA()/2);
}

    //  Y POSITIONS
float DeltaY_1()    //1. Y POSITION
{
    return Dcenter()*sin(THETA[0]+DeltaTHETA()/2);
}
    //  DISTANCES TRAVELLED 
float Dtravel_1()   //  1. DISTANCE
{
    return sqrt(pow(DeltaX_1(), 2) + pow(DeltaY_1(), 2));
}

    //  PID REGULATOR
void get_to_goal ( ) // FUNCTION TO REACH GOAL WITH ERROR CONSIDERATION
{   
    double e = 0; // angle error
    double THETA_D1 = atan((yPosition[1]-yPosition[0])/(xPosition[1]-xPosition[0]));    //  THETA DESIRED CALCULATED
    double output = 0;
    double derivative = 0;
    double proportional = 0;
    double integral = 0;
    double e_old = 0;   

    while (Dtravel_1() <= DISTANCES[0])    //  INDSTIL TIL RIGTIGE PUNKTER!!! SKER I ET PARALLELT TIDSFORLØB MED KØRSEL AF ROBOT TIL PUNKTER
    {
        if(THETA_D1 < -PI)    //  EVALUATES IF THE ANGLE IS LESS THAN -3.14
        {
            THETA_D1 = -PI;
        }
    
        else if(THETA_D1 > PI)  //  EVALUATES IF THE ANGLE IS MORE THAN 3.14
        {
            THETA_D1 = PI;   
        }
        
        e = THETA_D1 - THETA[0];    //  ERROR VALUE

        // Compute the proportional
        proportional = e; // get the error

        // Compute the integral
        integral += proportional;

        // Compute the derivative
        derivative = e - e_old;

        // Remember the last error.
        e_old = e;

        // Compute the output
        output = (proportional * (P_TERM)) + (integral * (I_TERM))
                + (derivative * (D_TERM));

        // Compute new speeds of both wheels
        right = speed - output;//if power is 0, no error and same speed on wheels
        left = speed + output;

        // limit checks
        if (right < MIN)
            right = MIN;
        else if (right > MAX)
            right = MAX;

        if (left < MIN)
            left = MIN;
        else if (left > MAX)
            left = MAX;

        robot.FW(right,left); // set new positions
        printf("\n\r Dcenter = %3.2f tickL= %4d  tickR = %4d left %3.2f right %3.2f",
               Dcenter(),tickL,tickR,left,right);
               
        printf("\n\r Error: %.2lf", e); //  HUSK DETTE!

        wait_ms(20); // should be adjusted to your context. Give the motor time
        // to do something before you react
    }
    t.stop(); // stop timer
}
#endif