/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       zhang769641                                               */
/*    Created:      24/09/2024, 15:13:36                                      */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}
motor frontLeft = motor(2); // 2
motor frontRight = motor(3, true); // 3
motor backLeft = motor(0); // 0
motor backRight = motor(1, true); // 1
motor_group allWheels = motor_group(frontLeft, frontRight, backLeft, backRight);
controller Controller1 = controller();
brain bigbrain = brain();
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    int rx = Controller1.Axis1.position(percent);
    int ry = Controller1.Axis2.position(percent);
    int lx = Controller1.Axis4.position(percent);
    int ly = Controller1.Axis3.position(percent);

    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1,1);
    Controller1.Screen.print(rx);
    Controller1.Screen.setCursor(1,2);
    Controller1.Screen.print(ry);

    double velocity1 = sqrt(2)/2 * (ly + lx);
    double velocity2 = sqrt(2)/2 * (ly - lx);

    double rotation = rx;
      
    // movement
    frontLeft.setVelocity(velocity1, percent);
    backRight.setVelocity(velocity1, percent);

    frontRight.setVelocity(velocity2, percent);
    backLeft.setVelocity(velocity2, percent);

    // rotation
    if (rx) {
      frontRight.setVelocity(-rotation, percent);
      frontLeft.setVelocity(rotation, percent);
      backLeft.setVelocity(rotation, percent);
      backRight.setVelocity(-rotation, percent);
    }

    allWheels.spin(forward);

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
