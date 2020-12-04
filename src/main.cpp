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
const int drivetrainTurnPowerAuto = 50;

const int drivetrainPowerAutoSkills = 40;

// Run Settings
const std::string team = "red";
const bool skills = true;
const signature& allySignature = FrontVision__RED_BALL;
const signature& enemySignature = FrontVision__BLUE_BALL;
// 0 = left corner
// 1 = middle 
// 2 = right corner
const int autoStrategy = 0;

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

void cornerStrategy ()
{
  int angleModifier = autoStrategy == 0 ? 1 : -1;
  Drivetrain.driveFor(forward, 36, inches);
  Drivetrain.turnFor(left, 135*angleModifier, degrees);
  centerOn(allySignature);
  Drivetrain.setDriveVelocity(drivetrainPowerAuto/3, percent);
  collectSignature(allySignature);
  Drivetrain.setDriveVelocity(drivetrainPowerAuto, percent);
  if (autoStrategy == 2)
  {
    Drivetrain.driveFor(forward, 6, inches);
  }
  centerOn(FrontVision__GOAL);
  intakeForward();
  Drivetrain.drive(forward);
  wait(500, msec);
  Drivetrain.stop();
  toggleRampMotor();
  escalatorForward();
  wait(3, sec);
  Drivetrain.driveFor(reverse, 6, inches);
  Drivetrain.driveFor(forward, 6, inches);
  wait(1, sec);
  Drivetrain.driveFor(reverse, 6, inches);
  wait(2, sec);
  intakeOff();
  toggleRampMotor();
  escalatorStop();
}

void autonomousMode ()
{
  autonomousConfig();
  switch (autoStrategy)
  {
    case (0):
    case (2):
      cornerStrategy();
    break;
    case (1):
      intakeBackward();
      Drivetrain.driveFor(forward, 5, inches);
      depositBalls(1);
      intakeForward();
      Drivetrain.driveFor(reverse, 40, inches);
      Drivetrain.turnFor(right, 100, degrees);
      centerOn(allySignature);
      intakeOff();
      escalatorForward();
      intakeForward();
      Drivetrain.setDriveVelocity(drivetrainPowerAuto/3, percent);
      collectSignature(allySignature);
      Drivetrain.setDriveVelocity(drivetrainPowerAuto, percent);
      wait(1500, msec);
      depositBalls(1);
      removeBalls(2);
    break;
  }
}

void skillsAutonomousMode ()
{
  autonomousConfig();

  Drivetrain.setDriveVelocity(drivetrainPowerAutoSkills, percent);

  depositBalls(1);

  Drivetrain.driveFor(reverse, 12, inches);
  Drivetrain.turnFor(left, 135, degrees);
  Drivetrain.driveFor(forward, 48, inches);
  Drivetrain.turnFor(right, 90, degrees);
  centerOn(enemySignature);
  driveForTime(forward, 750, msec);
  wait(500, msec);
  descoreCompletely();
  Drivetrain.driveFor(forward, 18, inches);
  Drivetrain.turnFor(right, 130, degrees);
  driveForTime(forward, 1, sec);
  centerOn(enemySignature);
  driveForTime(forward, 1, sec);
  centerOn(enemySignature);
  driveForTime(forward, 750, msec);
  centerOn(enemySignature);
  driveForTime(forward, 750, msec);
  centerOn(enemySignature);
  descoreCompletely();
  Drivetrain.driveFor(forward, 6, inches);
  Drivetrain.turnFor(right, 45, degrees);
  Drivetrain.driveFor(forward, 40, inches);
  Drivetrain.turnFor(right, 90, degrees);
  centerOn(enemySignature);
  driveForTime(forward, 1, sec);
  descoreCompletely();
  Drivetrain.driveFor(forward, 6, inches);
  Drivetrain.turnFor(left, 90, degrees);
  Drivetrain.driveFor(forward, 36, inches);
  Drivetrain.turnFor(right, 45, degrees);
  centerOn(enemySignature);
  driveForTime(forward, 1, sec);
  descoreCompletely();
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
