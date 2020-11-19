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

void collectSignature (vision::signature front_type, vision::signature inner_type)
{
  bool bCollected = false;
  InnerVision.takeSnapshot(inner_type);
  while (!(InnerVision.objectCount > 0))
  {
    centerOn(front_type);
    FrontVision.takeSnapshot(front_type);
    if (FrontVision.largestObject.width >= collectedW)
    {
      intakeBackward();
    }
    else
    {
      Drivetrain.drive(forward);
    }
    InnerVision.takeSnapshot(inner_type);
  }
  Drivetrain.stop();
}