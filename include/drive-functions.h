#import "robot-config.h"

bool escalatorRunning = false;
int escalatorDir;
bool rampRunning = false;

void toggleRampMotor ()
{
  if (rampRunning)
  {
    Ramp.stop();
    rampRunning = false;
  } else {
    Ramp.spin(directionType::fwd);
    rampRunning = true;
  }
}

void rampOn ()
{
  Ramp.spin(directionType::fwd);
  rampRunning = true;
}

void rampOff ()
{
  Ramp.stop();
  rampRunning = false;
}

void intakeForward ()
{
  IntakeLeft.spin(directionType::rev);
  IntakeRight.spin(directionType::fwd);
}


void intakeBackward ()
{
  IntakeLeft.spin(directionType::fwd);
  IntakeRight.spin(directionType::rev);
}

void intakeOff()
{
  IntakeLeft.stop();
  IntakeRight.stop();
}

void escalatorForward ()
{
  escalatorRunning = true;
  Escalator.spin(directionType::rev);
}

void escalatorBackward ()
{
  escalatorRunning = true;
  Escalator.spin(directionType::fwd);
}

void escalatorStop ()
{
  escalatorRunning = false;
  Escalator.stop();
}

void escalatorToggleOrSwitch (int newDir)
    {      
      if (escalatorRunning)
      {
        if (newDir != escalatorDir)
        {
          if (newDir > 0)
          {
            escalatorForward();
          } else
          {
            escalatorBackward();
          }
        } else 
        {
          escalatorStop();
        }
      } else
      {
        if (newDir > 0)
        {
          escalatorForward();
        } else
        {
          escalatorBackward();
        }
      }
      escalatorDir = newDir;
    }

void depositBalls (int number)
{
  rampOn();
  escalatorForward();
  wait(2*number, sec);
  rampOff();
  escalatorStop();
}

void removeBalls (int number)
{
  intakeBackward();
  escalatorForward();
  for (int i = 0; i < number; i++)
  {
    Drivetrain.driveFor(reverse, 6, inches);
    Drivetrain.driveFor(forward, 6, inches);
  }
  intakeOff();
  escalatorStop();
}