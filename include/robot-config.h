using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern motor IntakeLeft;
extern motor IntakeRight;
extern motor Escalator;
extern motor Ramp;
extern controller Controller1;
extern signature FrontVision__RED_BALL;
extern signature FrontVision__BLUE_BALL;
extern signature FrontVision__GOAL;
extern signature FrontVision__SIG_4;
extern signature FrontVision__SIG_5;
extern signature FrontVision__SIG_6;
extern signature FrontVision__SIG_7;
extern vision FrontVision;
extern signature InnerVision__BLUE_BALL;
extern signature InnerVision__RED_BALL;
extern signature InnerVision__SIG_3;
extern signature InnerVision__SIG_4;
extern signature InnerVision__SIG_5;
extern signature InnerVision__SIG_6;
extern signature InnerVision__SIG_7;
extern vision InnerVision;
extern smartdrive Drivetrain;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );