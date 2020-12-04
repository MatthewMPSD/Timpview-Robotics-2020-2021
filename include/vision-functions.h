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

bool detectSignature (vision::signature sig)
{
  FrontVision.takeSnapshot(sig);
  if (FrontVision.largestObject.exists)
  {
    return true;
  } else
  {
    return false;
  }
}

void descoreCompletely ()
{
  int descored = 0;
  int maxDescored = 3;
  int maxAttempts = 5;

  intakeForward();
  escalatorForward();
  for (int attempts = 0; attempts < maxAttempts && descored < maxDescored; attempts++)
  {
    Drivetrain.drive(forward);
    wait(500, msec);
    Drivetrain.driveFor(reverse, 6, inches);
    if (BumperG.pressing())
    {
      descored++;
    }
    wait(500, msec);

    if (descored == 0 && attempts >= 3)
    {
      driveForTime(forward, 500, msec);
      Controller1.Screen.clearLine();
      Controller1.Screen.print("READJUSTING...");
    }
  }
  Drivetrain.driveFor(reverse, 6, inches);
  Drivetrain.turnFor(left, 180, degrees);
  rampOn();
  wait(4, sec);
  intakeOff();
  rampOff();
  escalatorStop();
}