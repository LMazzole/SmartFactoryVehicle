/**
 * @file Hoist.h
 * @brief Library for mechatronic component hoist.
 * 
 * The hoist module consists of a lifting mechanism powered by a servo motor.
 * 
 * @author Glenn Huber (glenn.patrick.huber@hsr.ch)
 * @author Robert Paly (robert.paly@hsr.ch)
 * 
 * @version 2.0 - Refactored to match FSM Funccall  - Luca Mazzoleni (luca.mazzoleni@hsr.ch)  - 2019-04-23
 * @version 1.1 - Added Doxygen-Documentation  - Luca Mazzoleni (luca.mazzoleni@hsr.ch)  - 2019-03-20
 * @version 1.0 - BA FTS FS 2018
 * 
 * @date 2019-03-20
 * @copyright Copyright (c) 2019
 * 
 * @todo add const and private
 * 
 */

#ifndef Hoist_h
#define Hoist_h

#include "Arduino.h"
#include "Configuration.h"
#include "LogConfiguration.h"
// #include "Modular.h"
#include "Servo.h"

/**
 * @brief Hoist class controlls the Hoist
 * 
 */
// class Hoist : public Component {
class Hoist {
   public:
    Hoist();
    /**
    * @brief Construct a new Hoist object
    * 
    * @param hoistServoPin - Pin-number on with the Servocontroll is connected
    * @param hoistServoDelay - Duration of the Delay in ms between the position-updates 
    * @param posMax - Upper Limit for servo-positon in degree
    * @param posMin - Lower Limit for servo-position in degree
    */
    Hoist(int hoistServoPin, int hoistServoDelay, int posMax, int posMin);

    /**
     * @brief Initialise the Hoist in the low possition
     * 
     */
    void init();

    /**
     * @brief Raise the Hoist 1° per call until it's at positionMax
     * 
     */
    bool raise();

    /**
     * @brief Lower the Hoist 1° per call until it's at positionMin
     * 
     */
    bool lower();

    /**
     * @brief attache Servo to Servopin
     * 
     */
    inline void attach() {
        DBFUNCCALLln("Hoist::attach()");
        hoistServo.attach(servoPin);
    }

    /**
     * @brief detach servo from servopin
     * 
     */
    inline void detach() {
        DBFUNCCALLln("Hoist::detach()");
        hoistServo.detach();
    }

   private:
    Servo hoistServo;  ///< instance of servo object
    int servoPin;      ///< servopin
    int position;      ///< actual position
    int positionMin;   ///< minimal Position (Hardware)
    int positionMax;   ///< maximal Position (Hardware)
    int servoDelay;    ///<
};

#endif