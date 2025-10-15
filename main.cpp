#pragma region VEXcode Generated Robot Configuration
// Make sure all required headers are included.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>




#include "vex.h"


using namespace vex;


// Brain should be defined by default
brain Brain;




// START V5 MACROS
#define waitUntil(condition)                                                   \
 do {                                                                         \
   wait(5, msec);                                                             \
 } while (!(condition))


#define repeat(iterations)                                                     \
 for (int iterator = 0; iterator < iterations; iterator++)
// END V5 MACROS




// Robot configuration code.






// generating and setting random seed
void initializeRandomSeed(){
 int systemTime = Brain.Timer.systemHighResolution();
 double batteryCurrent = Brain.Battery.current();
 double batteryVoltage = Brain.Battery.voltage(voltageUnits::mV);


 // Combine these values into a single integer
 int seed = int(batteryVoltage + batteryCurrent * 100) + systemTime;


 // Set the seed
 srand(seed);
}






void vexcodeInit() {


 //Initializing random seed.
 initializeRandomSeed();
}




// Helper to make playing sounds from the V5 in VEXcode easier and
// keeps the code cleaner by making it clear what is happening.
void playVexcodeSound(const char *soundName) {
 printf("VEXPlaySound:%s\n", soundName);
 wait(5, msec);
}


#pragma endregion VEXcode Generated Robot Configuration


/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       {author}                                                  */
/*    Created:      {date}                                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/


// Include the V5 Library
#include "vex.h"
 // Allows for easier use of the VEX Library
using namespace vex;


competition Competition;


motor m_left_fwd(PORT19, true);
motor m_left_rev(PORT20, true);


motor m_right_fwd(PORT13);


motor m_right_rev(PORT12);


motor_group m_left(m_left_fwd, m_left_rev);
motor_group m_right(m_right_fwd, m_right_rev);


controller Controller(primary);


// inertial Inertial(PORT14);


void driver_control() {


 double TURNWHEELRATIO = 1.5;
 double TURNADJUSTMENTSCALING = 1/(TURNWHEELRATIO - 1);


 // Brain.Screen.clearScreen();
 // Brain.Screen.setCursor(1, 1);
 // Brain.Screen.print("Calibrating...");
 // while (Inertial.isCalibrating()) {
 //   Inertial.calibrate();
 //   wait(200, msec);
 // }


 while (true) {


   int crVertical = Controller.Axis3.position();
   int crHorizontal = Controller.Axis1.position();


   double forwardSpeed = crVertical;
   double turnMagnitude = crHorizontal;


   Brain.Screen.clearScreen();
   Brain.Screen.setCursor(1, 1);
   Brain.Screen.print("Testing...");
   // Brain.Screen.print(Inertial.rotation(degrees));


   //m_left.spin(vex::forward, (forwardSpeed + turnMagnitude) / 2, percent);
   //m_right.spin(vex::forward, (forwardSpeed - turnMagnitude) / 2, percent);


   if (forwardSpeed >= 10) {


     if (turnMagnitude >= 10) {


       m_left.spin(vex::forward, (forwardSpeed + turnMagnitude / TURNADJUSTMENTSCALING) / TURNWHEELRATIO, percent);
       m_right.spin(vex::forward, forwardSpeed / TURNWHEELRATIO, percent);


     }
     else if (turnMagnitude <= -10) {


       m_left.spin(vex::forward, forwardSpeed / TURNWHEELRATIO, percent);
       m_right.spin(vex::forward, (forwardSpeed - turnMagnitude / TURNADJUSTMENTSCALING) / TURNWHEELRATIO, percent);


     }
     else {


       m_left.spin(vex::forward, forwardSpeed / TURNWHEELRATIO, percent);
       m_right.spin(vex::forward, forwardSpeed / TURNWHEELRATIO, percent);


     }


   }
   else if (forwardSpeed <= -10) {


     if (turnMagnitude >= 10) {


       m_left.spin(vex::forward, (forwardSpeed - turnMagnitude / TURNADJUSTMENTSCALING) / TURNWHEELRATIO, percent);
       m_right.spin(vex::forward, forwardSpeed / TURNWHEELRATIO, percent);


     }
     else if (turnMagnitude <= -10) {


       m_left.spin(vex::forward, forwardSpeed / TURNWHEELRATIO, percent);
       m_right.spin(vex::forward, (forwardSpeed + turnMagnitude / TURNADJUSTMENTSCALING) / TURNWHEELRATIO, percent);


     }
     else {


       m_left.spin(vex::forward, forwardSpeed / TURNWHEELRATIO, percent);
       m_right.spin(vex::forward, forwardSpeed / TURNWHEELRATIO, percent);


     }


   }
   else {


     m_left.spin(vex::forward, (forwardSpeed + turnMagnitude) / TURNWHEELRATIO, percent);
     m_right.spin(vex::forward, (forwardSpeed - turnMagnitude) / TURNWHEELRATIO, percent);


   }
    // Controller.Screen.print("Axis 1: ");
   // Controller.Screen.print(crVertical);
   // Controller.Screen.newLine();
   // Controller.Screen.print("Axis 3: ");
   // Controller.Screen.print(crHorizontal);
   wait(1, msec);




 }


}


void autonomous_control() {


}


int main() {
 // Initializing Robot Configuration. DO NOT REMOVE!
 vexcodeInit();


 Brain.Screen.print("Starting...");
  Competition.drivercontrol(driver_control);
 Competition.autonomous(autonomous_control);


 return 0;
}





