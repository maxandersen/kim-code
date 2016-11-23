/*
Dette er header filen for ultralydssensoren
*/

#ifndef HCSR04_H_TVZMT
#define HCSR04_H_TVZMT

/** A distance measurement class using ultrasonic sensor HC-SR04.
 *  
 * Example of use:
 * @code
 * #include "mbed.h"
 * #include "HCSR04.h"
 *
 * Serial pc(USBTX, USBRX);
 *
 * int main() {
 *     HCSR04 sensor(p5, p7);
 *     sensor.setRanges(10, 110);
 *     pc.printf("Min. range = %g cm\n\rMax. range = %g cm\n\r",
 *       sensor.getMinRange(), sensor.getMaxRange());
 *     while(1) {
 *         pc.printf("Distance: %5.1f mm\r", sensor.getDistance_mm());
 *         wait_ms(500);
 *     }
 * }
 * @endcode
 */
class HCSR04 {
    
    public:
    
    /** Receives two PinName variables.
     * @param echoPin mbed pin to which the echo signal is connected to
     * @param triggerPin mbed pin to which the trigger signal is connected to
     */
    HCSR04(PinName echoPin, PinName triggerPin);
    
    /** Calculates the distance in cm, with the calculation time of approximatelly 23.7 ms.
     * @returns distance of the measuring object in cm.
     */
    float getDistance_cm();
    
    /** Calculates the distance in mm, with the calculation time of approximatelly 23.7 ms.
     * @returns distance of the measuring object in mm.
     */
    float getDistance_mm();
    
    /** Sets the minimum and maximum ranges between the factory values of 2 cm and 400 cm.
     *  @param minRange Minimum range in cm. Must be between 2 cm and maxRange.
     *  @param maxRange Maximum range in cm. Must be between minRange and 400 cm.
     */
    void setRanges(float minRange, float maxRange);
    
    /** Retreives the minimum sensor range set by the user.
     * @returns the minimum sensor range set by the user in cm.
     */
    float getMinRange();
    
    /** Retreives the maximum sensor range set by the user.
     * @returns the maximum sensor range set by the user in cm.
     */
    float getMaxRange();
    
    private:
    
    InterruptIn echo;       // echo pin
    DigitalOut trigger;     // trigger pin
    Timer timer;            // echo pulsewidth measurement
    float distance;         // store the distance in cm
    float minDistance;      // minimum measurable distance
    float maxDistance;      // maximum measurable distance
    
    /** Start the timer. */
    void startTimer();
    
    /** Stop the timer. */
    void stopTimer();
    
    /** Initialization. */
    void init();
    
    /** Start the measurement. */
    void startMeasurement();
};

#endif