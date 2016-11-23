/*
Dette er cpp filen for ultralydssensoren
*/
#include "mbed.h"
#include "HCSR04.h"

HCSR04::HCSR04(PinName echoPin, PinName triggerPin) : echo(echoPin), trigger(triggerPin) {
    init();
}

void HCSR04::init() {
    /** configure the rising edge to start the timer */
    echo.rise(this, &HCSR04::startTimer);
    
    /** configure the falling edge to stop the timer */
    echo.fall(this, &HCSR04::stopTimer);
    
    distance = -1;      // initial distance
    minDistance = 2;
    maxDistance = 400;
}

void HCSR04::startTimer() {
    timer.start(); // start the timer
}

void HCSR04::stopTimer() {
    timer.stop(); // stop the timer
}

void HCSR04::startMeasurement() {
    trigger = 1;
    wait_us(10);
    trigger = 0;
    wait_ms(25); // just enough time to measure 400 cm
    timer.stop(); // just in case echo fall did not occur
    distance = timer.read() * 1e6 / 58;
    if (distance < minDistance)
        distance = minDistance;
    if (distance > maxDistance)
        distance = maxDistance;
    timer.reset();
}

float HCSR04::getDistance_cm() {
    startMeasurement();
    return distance;
}

float HCSR04::getDistance_mm() {
    startMeasurement();
    return distance * 10;
}

void HCSR04::setRanges(float minRange, float maxRange) {
    if (minRange < maxRange) {
        if (minRange >= 2) 
            minDistance = minRange;
        if (maxRange <= 400)
            maxDistance = maxRange;
    }
}

float HCSR04::getMinRange() {
    return minDistance;
}

float HCSR04::getMaxRange() {
    return maxDistance;
}