#import "drive-functions.h"

int centerX = 150;
int centerY = 190;
int collectedW = 150;
int slack = 80;

void centerOn (vision::signature type)
{
  bool aligned = false;
  int loopCounter = 0;
  FrontVision.takeSnapshot(type);
  while (!aligned)
  {
    if (FrontVision.largestObject.exists)
    {
      if (centerX - slack > FrontVision.largestObject.centerX)
      {
        Drivetrain.turn(left);
      } 
      else if (centerX + slack < FrontVision.largestObject.centerX)
      {
        Drivetrain.turn(right);
      } 
      else 
      {
        Drivetrain.stop();
        aligned = true;
      }
      FrontVision.takeSnapshot(type);
    } else
    {
      if (++loopCounter > 5)
      {
        break;
      }
    }
  }
}

void collectSignature (vision::signature front_type)
{
  intakeForward();
  while (!BumperG.pressing())
  {
    wait(100, msec);
    centerOn(front_type);
    Drivetrain.drive(forward);
  }
  Drivetrain.stop();
  intakeOff();
}