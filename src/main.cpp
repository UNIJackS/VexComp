/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       10jac                                                     */
/*    Created:      5/26/2023, 2:55:52 PM                                     */
/*    Description:  Far side program                                          */
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
motor motor_left_back = motor(PORT20, ratio18_1, false);
motor motor_left_middle = motor(PORT19, ratio18_1, false);
motor motor_left_front = motor(PORT18, ratio18_1, false);

motor motor_right_back = motor(PORT11, ratio18_1, false);
motor motor_right_middle = motor(PORT12, ratio18_1, false);
motor motor_right_front = motor(PORT13, ratio18_1, false);

motor motor_top_conveyor = motor(PORT16, ratio18_1, false);
motor motor_top_raiser = motor(PORT15, ratio18_1, false);

// Motor group definitons
motor_group left_motor_group = motor_group(motor_left_back,motor_left_middle,motor_left_front);
motor_group right_motor_group = motor_group(motor_right_back,motor_right_middle,motor_right_front);


bumper raiser_bumper = bumper(brain_1.ThreeWirePort.A);


//-----------A,B,X & Y buttons-----------------------------
void ControllerButtonAPressed(void){
	//brain_1.Screen.drawImageFromFile("wink.png",0,0);
  printf("A button pressed !!!\n");
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

//Setsup the callback events for each button on the contorller
//these are the functions that will be called when each button is pressed
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

    // CRITICAL !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    motor_right_middle.setReversed(true);
    motor_left_back.setReversed(true);
    motor_left_front.setReversed(true);

    motor_top_raiser.resetPosition();
    // CRITICAL !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //IF THIS IS NOT PRESENT THEN THE GEAR BOX WILL DESTROY ITS SELF


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
    drivetrain auto_drive_train =drivetrain(left_motor_group,right_motor_group,319,370,320,mm,0.42);

    //sets the drive trains velocity in percent 
    auto_drive_train.setDriveVelocity(100,percent);

    //sets the drive trains stopping type
    auto_drive_train.setStopping(brake);

    motor_top_raiser.setVelocity(80, percent);

    motor_top_raiser.setStopping(hold);

    //..........................................................................
    // Commands for moving autonomusly go here
    //..........................................................................

    //..........................................................................
    // code for moving to score goal
    //..........................................................................
    //moves forward to allow turn
    auto_drive_train.driveFor(forward,100,mm,true);

    //turns towards the goal
    auto_drive_train.turnFor(40,deg,true);

    //moves to be inline with the goal
    auto_drive_train.driveFor(forward,781,mm,true);

    //turns the robot to face the goal 
    auto_drive_train.turnFor(-50,deg,true);

    //moves to be inline with the goal
    auto_drive_train.driveFor(reverse,200,mm,true);

    //pushes the triball off the top by spinning the top motor
    motor_top_conveyor.spinFor(2,seconds);

    //pushes the tri ball into the goal (142.8 is prefect)
    auto_drive_train.driveFor(forward,200,mm,true);


    //..........................................................................
    // code for moving to poll
    //..........................................................................
    //reverses to allow for turn    
    //auto_drive_train.driveFor(reverse,145,mm,true);

    //turns the robot to the left face the left
    //auto_drive_train.turnFor(-80,deg,true);

    

    //drives the robot to the square infront of the bumper
    //auto_drive_train.driveFor(forward,1341,mm,false);
    
    //loops to allow convayermotor to spin  
    //bool loop = true;
    //while(loop) {
      // 6300 = 35 * 180 cause i want it to move 180 degrees and the gear ratio is 1 to 35
      // but i use 6000 insted cause real world is wack :)
      //if(motor_top_raiser.position(degrees) < 6000){
        //spins the raiser motor till it reaches the desired angle
       //   motor_top_raiser.spin(reverse);
        //}
      // if the movement command is done then it starts to rotate the robot away from the elivation bar
      //if(auto_drive_train.isDone() == false){
        //tells the drive train to turn 125 degrees cause 45deg + 80deg
        //auto_drive_train.turnFor(125,deg,false);
      //}
    //}
    

    //turns the robot to face away from the climb poll
    

  //vison test code 
  //vision auto_camera = vision(PORT3);
  
  //::signature green_obj = vision::signature(1,10,300,140,10,300,140,1,1);


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
  int i = 0;
    // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................

    //sets the joy stick positons to the left and right motor speeds
    left_motor_group.setVelocity(controller_1.Axis3.position(), percent);
    right_motor_group.setVelocity(controller_1.Axis2.position(), percent);

    //spins the motors using the velocity from the joy sticks
    left_motor_group.spin(forward);
    right_motor_group.spin(forward);


    //sets the velocity for the convayer
    motor_top_conveyor.setVelocity(75, percent);

    //checks if the top bumpers are being pressed then spins the convayer if they are
    if (controller_1.ButtonR1.pressing() == true){
        motor_top_conveyor.spin(forward);
    }
    else if(controller_1.ButtonL1.pressing() == true){
        motor_top_conveyor.spin(reverse);
    }
    else {
        motor_top_conveyor.stop();
    }

    //sets the speed of the motor that raises the robot
    motor_top_raiser.setVelocity(80, percent);

    motor_top_raiser.setStopping(hold);
    
    i += 1;
      

    printf("%ideggrees:%f\n",i,motor_top_raiser.position(degrees));
    //checks if the bottom bumpers are being pressed then raises or lowers the convayer if they are
    if (controller_1.ButtonR2.pressing() == true){
        motor_top_raiser.spin(forward);
        
    }
    else if(controller_1.ButtonL2.pressing() == true){
        motor_top_raiser.spin(reverse);
        
    }
    else {
        motor_top_raiser.stop();
    }

    // ........................................................................
    
    //brain_1.Screen.drawImageFromFile("normal.png",0,0);
    //wait(1000, msec);
    //brain_1.Screen.drawImageFromFile("blink.png",0,0);

    wait(20, msec); // Sleep the task for a short amount of time to
                  // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.

  // Cute Face ^.^
  //brain_1.Screen.drawImageFromFile("normal.png",0,0);
  //test for commit
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
