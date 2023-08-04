/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       10jac                                                     */
/*    Created:      5/26/2023, 2:55:52 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

// A global instance of vex::controller used for taking inputs from the controller
controller controller_1 = controller(primary);

// A global instance of vex::brain used for printing to the V5 brain screen
brain brain_1;


// Motor definations 
motor left_motor_back = motor(PORT1, ratio18_1, false);
motor left_motor_front = motor(PORT2, ratio18_1, false);
motor right_motor_back = motor(PORT10, ratio18_1, false);
motor right_motor_front = motor(PORT9, ratio18_1, false);

motor topmotor = motor(PORT3, ratio18_1, false);

// Motor group definitons
motor_group left_motor_group = motor_group(left_motor_back,left_motor_front);
motor_group right_motor_group = motor_group(right_motor_back,right_motor_front);




//-----------A,B,X & Y buttons-----------------------------

void ControllerButtonAPressed(void){
    brain_1.Screen.printAt(10, 20, "A button pressed !!!" );
    printf("A button pressed !!!\n");
    //topmotor.setVelocity(10, percent);
    //topmotor.spin(forward);
};
void ControllerButtonBPressed(void){
    brain_1.Screen.printAt(10, 20, "B button pressed !!!" );
    printf("B button pressed !!!\n");
    //topmotor.setVelocity(0, percent);
    //topmotor.spin(forward);
};
void ControllerButtonXPressed(void){
    brain_1.Screen.printAt(10, 20, "X buAtton pressed !!!" );
    printf("X button pressed !!!\n");
    //topmotor.setVelocity(10, percent);
    //topmotor.spin(reverse);
};
void ControllerButtonYPressed(void){
    brain_1.Screen.printAt(10, 20, "Y button pressed !!!" );
    printf("Y button pressed !!!\n");
};
//-----------Bumper buttons--------------------------------

void ControllerButtonL1Pressed(void){
    brain_1.Screen.printAt(10, 20, "L1 button pressed !!!" );
    printf("L1 button pressed !!!");
};
void ControllerButtonL2Pressed(void){
    brain_1.Screen.printAt(10, 20, "L2 button pressed !!!" );
    printf("L2 button pressed !!!");
};
void ControllerButtonR1Pressed(void){
    brain_1.Screen.printAt(10, 20, "R1 button pressed !!!" );
    printf("R1 button pressed !!!");
};
void ControllerButtonR2Pressed(void){
    brain_1.Screen.printAt(10, 20, "R2 button pressed !!!" );
    printf("R2 button pressed !!!");
};
//-----------Up,Down,<,> buttons---------------------------

void ControllerButtonUpPressed(void){
    brain_1.Screen.printAt(10, 20, "Up button pressed !!!" );
    printf("Up button pressed !!!");
};
void ControllerButtonDownPressed(void){
    brain_1.Screen.printAt(10, 20, "Down button pressed !!!" );
    printf("Down button pressed !!!");
};
void ControllerButtonLeftPressed(void){
    brain_1.Screen.printAt(10, 20, "Left button pressed !!!" );
    printf("Left button pressed !!!");
};
void ControllerButtonRightPressed(void){
    brain_1.Screen.printAt(10, 20, "Right button pressed !!!" );
    printf("Right button pressed !!!");
};

//Setsup the callback events for each button on the contorller
//these are the functions that will be called when each button is pressed
//The functions are in a seperate object which is created from the the class above
void CallBackSetup(){
    printf("Call Back Setup function called...");
    //callback functions for A,B,X and Y buttons
    controller_1.ButtonA.pressed(ControllerButtonAPressed);
    controller_1.ButtonB.pressed(ControllerButtonBPressed);
    controller_1.ButtonX.pressed(ControllerButtonXPressed);
    controller_1.ButtonY.pressed(ControllerButtonYPressed);

    //callback functions for the bumbpers on the front of the controller
    controller_1.ButtonL1.pressed(ControllerButtonL1Pressed);
    controller_1.ButtonL2.pressed(ControllerButtonL2Pressed);
    controller_1.ButtonR1.pressed(ControllerButtonR1Pressed);
    controller_1.ButtonR2.pressed(ControllerButtonR2Pressed);

    //callback functions for the up,donw,left and right arrow buttons
    controller_1.ButtonUp.pressed(ControllerButtonUpPressed);
    controller_1.ButtonDown.pressed(ControllerButtonDownPressed);
    controller_1.ButtonLeft.pressed(ControllerButtonLeftPressed);
    controller_1.ButtonRight.pressed(ControllerButtonRightPressed);
    printf("Call back setup function compleated");

}
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

    right_motor_back.setReversed(true);
    right_motor_front.setReversed(true);
  

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  return;
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

    //creates a drive train object for the autonomus phase
    //left motor, right motor, wheel travel aka wheel circumference, track width aka distance between left and right wheels
    //,wheel base aka distance between front and rear axles, measurment unit, gear ratio 
    drivetrain auto_drive_train =drivetrain(left_motor_group,right_motor_group,319,370,310,mm,1);

    //sets the drive trains velocity in percent 
    auto_drive_train.setDriveVelocity(50,percent);

    //sets the drive trains stopping type
    auto_drive_train.setStopping(brake);

    //..........................................................................
    // Commands for moving autonomusly go here
    //..........................................................................
    auto_drive_train.driveFor(forward,848,mm,true);

    auto_drive_train.turnFor(-45,deg,true);
    //auto_drive_train.turnFor(-180,deg,true);

    auto_drive_train.driveFor(reverse,200,mm,true);

    topmotor.setVelocity(50, percent);

    topmotor.spinFor(5,seconds);

    auto_drive_train.driveFor(forward,257,mm,true);



  //vison test code 
  vision auto_camera = vision(PORT3);
  
  vision::signature green_obj = vision::signature(1,10,300,140,10,300,140,1,1);


}

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
  //calls the CallBackSetup function to setup the button callbacks
  CallBackSetup();

  //REMOVE IN REAL CODE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  autonomous();
  //REMOVE IN REAL CODE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    // User control code here, inside the loop
    while (1) {
        
        left_motor_group.setVelocity(controller_1.Axis3.position(), percent);

        right_motor_group.setVelocity(controller_1.Axis2.position(), percent);


        topmotor.setVelocity(30, percent);

        if (controller_1.ButtonR1.pressing() == true){
            topmotor.spin(forward);
        }
        else if(controller_1.ButtonL1.pressing() == true){
            topmotor.spin(reverse);
        }
        else {
            topmotor.stop();
        }

        left_motor_group.spin(forward);
        right_motor_group.spin(forward);
        
        

    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

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
