/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\mm023739                                         */
/*    Created:      Thu Sep 03 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// IntakeLeft           motor         5               
// IntakeRight          motor         6               
// Escalator            motor         7               
// Ramp                 motor         8               
// Controller1          controller                    
// FrontVision          vision        10              
// InnerVision          vision        11              
// Drivetrain           drivetrain    1, 2, 3, 4, 9   
// ---- END VEXCODE CONFIGURED DEVICES ----

#import "vex.h"
#import "drive-functions.h"
#import "vision-functions.h"

using namespace vex;

//Constants
const int intakePower = 100;
const int escalatorPower = 100;
const int rampPower = 100;
const int drivetrainPower = 10;
const std::string team = "red";
const bool skills = false;

const signature& allySignature = FrontVision__RED_BALL;
const signature& enemySignature = FrontVision__BLUE_BALL;

//Define competition object
competition Competition;

void driverControlMode ()
{
  // Directional controls are already handled through drivetrain control

  //Intake system
  Controller1.ButtonL2.pressed([](){intakeForward();}); //In
  Controller1.ButtonL2.released([](){intakeOff();}); //In
  Controller1.ButtonL1.pressed([](){intakeBackward();}); //Out
  Controller1.ButtonL1.released([](){intakeOff();}); //Out
  
  // Target
  Controller1.ButtonX.pressed([](){centerOn(allySignature);});
  Controller1.ButtonY.pressed([](){centerOn(enemySignature);});

  //Escalator system
  Controller1.ButtonR2.pressed([](){escalatorToggleOrSwitch(1);});
  Controller1.ButtonR1.pressed([](){escalatorToggleOrSwitch(-1);});

  //Ramp
  Controller1.ButtonA.pressed(toggleRampMotor);

  //Main loop
  while (Competition.isDriverControl()) 
  {
  }
}

void autonomousMode ()
{
  // Drivetrain.driveFor(forward, 36, inches);
  // Drivetrain.turnFor(left, 135, degrees);
  // centerOn(FrontVision__RED_BALL);
  collectSignature(FrontVision__RED_BALL, InnerVision__RED_BALL);
  // centerOn(FrontVision__GOAL);
  // Drivetrain.drive(forward);
  // wait(10, msec);
  // Drivetrain.stop();

  // //Main Loop
  // while (Competition.isAutonomous())
  // {
  //   centerOn(FrontVision__RED_BALL);
  //   escalatorBackward();
  // }
}

void skillsAutonomousMode ()
{
  // Main Loop
  while (Competition.isAutonomous())
  {

  }
}


int main() 
{
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  //Extra Initialization
  Ramp.setVelocity(rampPower, velocityUnits::pct);
  Escalator.setVelocity(escalatorPower, velocityUnits::pct);
  IntakeLeft.setVelocity(intakePower, velocityUnits::pct);
  IntakeRight.setVelocity(intakePower, velocityUnits::pct);
  Drivetrain.setDriveVelocity(drivetrainPower, velocityUnits::pct);

  if (!skills)
  {
    Competition.autonomous(autonomousMode);
  } else 
  {
    Competition.autonomous(skillsAutonomousMode);
  }
  
  Competition.drivercontrol(driverControlMode);
}
