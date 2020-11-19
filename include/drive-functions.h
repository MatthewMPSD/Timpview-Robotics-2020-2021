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