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
 #define waitUntil(condition) \
 do { \
 wait(5, msec); \
 } while (!(condition))


 #define repeat(iterations) \
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
/* */
/* Module: main.cpp */
/* Author: {author} */
/* Created: {date} */
/* Description: V5 project */
/* */
/*----------------------------------------------------------------------------*/


// Include the V5 Library
#include "vex.h"


// Allows for easier use of the VEX Library
using namespace vex;


// Create competition instance.
competition Competition;


// Create motor instances
motor leftFront(PORT1, true);
motor leftBack(PORT2, true);
motor rightFront(PORT3);
otor rightBack(PORT4);


// Create motor group instances
motor_group leftMotors(leftFront, leftBack);
motor_group rightMotors(leftFront, leftBack);


// Create controller instance
controller Controller(primary); // primary keyword optional??


// Copied from Raiyan can change later
float curveMod(int x) {
return 1 / (1 + exp(-abs(x / 300)));
}


void driverControl() {
while (true) {
// Controller input
int ctrlVertical = Controller.Axis3.position();
int ctrlHorizontal = Controller.Axis4.position();


// Speed values
float speedMod = 1;
// TODO speed modifier stuff for rotations specifically


double leftSpeed = ctrlVertical;
double rightSpeed = ctrlVertical;


leftSpeed = curveMod(leftSpeed) * speedMod;
rightSpeed = curveMod(rightSpeed) * speedMod;


// Spin motor groups
leftMotors.spin(forward, leftSpeed, rpm);
rightMotors.spin(forward, rightSpeed, rpm);


// Brain management
Brain.Screen.clearScreen();
Brain.Screen.print("NOAH IS SUPER COOL");


// Controller management
Controller.Screen.clearScreen();


Controller.Screen.print("Vertical: ");
Controller.Screen.newLine();
Controller.Screen.print(ctrlVertical);


Controller.Screen.print("Horizontal: ");
Controller.Screen.newLine();
Controller.Screen.print(ctrlHorizontal);
  }
}


void autonomousControl() {
}


int main() {
// Initializing Robot Configuration. DO NOT REMOVE!
vexcodeInit();


// Set up callback for the autonomous control period.
Competition.autonomous(autonomousControl);


// Set up callback for the driver control period.
Competition.drivercontrol(driverControl);
}
