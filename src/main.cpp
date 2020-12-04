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
// BumperG              bumper        G               
// ---- END VEXCODE CONFIGURED DEVICES ----

#import "vex.h"
#import "drive-functions.h"
#import "vision-functions.h"

using namespace vex;

//Constants
const int intakePower = 100;
const int escalatorPower = 100;
const int rampPower = 100;
const int drivetrainPower = 50;
const int drivetrainTurnPower = 100;

const int intakePowerAuto = 100;
const int escalatorPowerAuto = 100;
const int rampPowerAuto = 100;
const int drivetrainPowerAuto = 100;
const int drivetrainTurnPowerAuto = 100;

// Run Settings
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
}

void autonomousConfig ()
{
  // Set Autonomous Specific Speeds
  Ramp.setVelocity(rampPowerAuto, velocityUnits::pct);
  Escalator.setVelocity(escalatorPowerAuto, velocityUnits::pct);
  IntakeLeft.setVelocity(intakePowerAuto, velocityUnits::pct);
  IntakeRight.setVelocity(intakePowerAuto, velocityUnits::pct);
  Drivetrain.setDriveVelocity(drivetrainPowerAuto, velocityUnits::pct);
  Drivetrain.setTurnVelocity(drivetrainTurnPowerAuto, velocityUnits::pct);
}

void autonomousMode ()
{
  autonomousConfig();

  Drivetrain.driveFor(forward, 36, inches);
  Drivetrain.turnFor(left, 135, degrees);
  centerOn(allySignature);
  Drivetrain.setDriveVelocity(drivetrainPowerAuto/3, percent);
  collectSignature(allySignature);
  Drivetrain.setDriveVelocity(drivetrainPowerAuto, percent);
  centerOn(FrontVision__GOAL);
  Drivetrain.drive(forward);
  wait(500, msec);
  Drivetrain.stop();
  toggleRampMotor();
  escalatorForward();
  wait(3, sec);
  Drivetrain.driveFor(reverse, 6, inches);
  Drivetrain.driveFor(forward, 6, inches);
  Drivetrain.driveFor(reverse, 6, inches);
  intakeOff();
  wait(1, sec);
  toggleRampMotor();
  escalatorStop();
}

void skillsAutonomousMode ()
{
  autonomousConfig();
  
  intakeBackward();
  Drivetrain.driveFor(forward, 18, inches);
  toggleRampMotor();
  escalatorForward();
  wait(1, sec);
  escalatorStop();
  toggleRampMotor();
  Drivetrain.driveFor(reverse, 10, inches);
  Drivetrain.turnFor(left, 90, degrees);
  collectSignature(allySignature);
  centerOn(FrontVision__GOAL);
  // collectSignature(allySignature);
  // collectSignature(allySignature);
  // Drivetrain.turnFor(left, 45, degrees);
  // Drivetrain.driveFor(forward, 12, inches);
  // intakeBackward();
  // wait(1, sec);
  intakeOff();
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
  Drivetrain.setTurnVelocity(drivetrainTurnPower, velocityUnits::pct);

  if (!skills)
  {
    Competition.autonomous(autonomousMode);
  } else 
  {
    Competition.autonomous(skillsAutonomousMode);
  }
  
  Competition.drivercontrol(driverControlMode);
}
