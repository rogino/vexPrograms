#pragma config(Motor,  port2,           r,             tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           claw,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           arm,           tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           l,             tmotorVex393_MC29, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

const int armSpeed = 50;
const int clawSpeed = 50;

bool driveIsTank = true;
bool driveWasPressed = false;

void drive(int left, int right) {
	motor[r] = right;
	motor[l] = left;
}



void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks
  // running between Autonomous and Driver controlled modes. You will need to
  // manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	// bDisplayCompetitionStatusOnLcd = false;

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
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

void auto() {
	motor[arm] = 50;
	wait1Msec(900);
	motor[arm] = 0;

	motor[claw] = -50;
	wait1Msec(1000);

	drive(50, 70);
	wait1Msec(2000);
	drive(-100, -100);
	wait1Msec(1000);
	drive(0,0);

}


task autonomous()
{
//	auto();
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


task usercontrol()
{
  // User control code here, inside the loop

  while(true) {

	 if (vexRT[Btn8D] && !driveWasPressed) {
  			//pressing 8D switches drive mode
				driveIsTank = !driveIsTank;
				// auto(); // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				driveWasPressed = true;
  	}

  	else {
  		//prevents drive mode from constantly changing
  		driveWasPressed = false;
  	}


  	if (driveIsTank) {
  		//tank drive -> drives each side individually
  		drive(vexRT[Ch3], vexRT[Ch2]);
  	}
  	else {
  		// arcade drive -> left joystick for forward/back, right joystick for left/right
  		drive(vexRT[Ch3] + vexRT[Ch1], vexRT[Ch3] - vexRT[Ch1]);
  	}

/*	motor[l] = vexRT[Ch3];
	motor[r] = vexRT[Ch2];
	*/
	if (vexRT[Btn5D]) motor[arm] = -armSpeed;
	else if (vexRT[Btn5U]) motor[arm] = armSpeed;
	else motor[arm] = 0;

	if (vexRT[Btn6D]) motor[claw] = -clawSpeed;
	else if (vexRT[Btn6U]) motor[claw] = clawSpeed;
	else motor[claw] = 0;
	}
}
