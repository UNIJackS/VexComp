#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

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
};
void ControllerButtonBPressed(void){
};
void ControllerButtonXPressed(void){
};
void ControllerButtonYPressed(void){
};
//-----------Bumper buttons--------------------------------

void ControllerButtonL1Pressed(void){
};
void ControllerButtonL2Pressed(void){
};
void ControllerButtonR1Pressed(void){
};
void ControllerButtonR2Pressed(void){
};
//-----------Up,Down,<,> buttons---------------------------

void ControllerButtonUpPressed(void){
};
void ControllerButtonDownPressed(void){
};
void ControllerButtonLeftPressed(void){
};
void ControllerButtonRightPressed(void){
};

//Setup the callback events for each button on the contorller
//these are the functions that will be called when each button is pressed
//The functions are in a seperate object which is created from the the class above
void CallBackSetup(){
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

}
// Pre-Autonomous Functions

void pre_auton(void) {

    right_motor_back.setReversed(true);
    right_motor_front.setReversed(true);
  

  // All activities that occur before the competition starts
  return;
}

// Autonomous

void autonomous(void) {
    // Insert autonomous user code here.

    //creates a drive train object for the autonomus phase
    //left motor, right motor, wheel travel aka wheel circumference, track width aka distance between left and right wheels
    //,wheel base aka distance between front and rear axles, measurment unit, gear ratio 
    drivetrain auto_drive_train =drivetrain(left_motor_group,right_motor_group,319,370,310,mm,1);

    //sets the drive trains velocity in percent 
    auto_drive_train.setDriveVelocity(50,percent);

    //sets the drive trains stopping type
    auto_drive_train.setStopping(brake);

    // Commands for moving autonomusly go here
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

//User Control Task
void usercontrol(void) {
  //calls the CallBackSetup function to setup the button callbacks
  CallBackSetup();

  //REMOVE IN REAL CODE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! 
  autonomous();

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
        
        

    wait(20, msec); // Sleep.
  }
}

// Main will set up the competition functions and callbacks.
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
