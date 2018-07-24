#pragma config(Motor,  port1,           driveLFront,   tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           driveLBack,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           armL,         tmotorVex269_MC29, openLoop)
#pragma config(Motor,  port8,           armR,         tmotorVex269_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           driveRBack,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          driveRFront,   tmotorVex393_HBridge, openLoop, reversed)
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

// const int armSpeed = 100;
// const int intakeSpeed = 127;


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

void drive(int l, int r) {
		motor[driveLFront] = motor[driveLBack] = l;
		motor[driveRFront] = motor[driveRBack] = r;
}


void arm(int speed) {
	motor[armR] = motor[armL] = speed;
}

// void driveStraight(int speed) {
// 	drive(speed, speed);
// }




task autonomous()
{
  // ..........................................................................
  // Insert user code here.
  // ..........................................................................

  // Remove this function call once you have "real" code.
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




bool driveIsTank = true;
bool driveWasPressed = false;

const int armSpeed = 127;
const int armSlowSpeed = 50;

task usercontrol()
{
  // User control code here, inside the loop

  while (true)
  {
  	if (vexRT[Btn8D] && !driveWasPressed) {
				driveIsTank = !driveIsTank;
				driveWasPressed = true;
  	}

  	else {
  		driveWasPressed = false;
  	}


  	if (driveIsTank) {
  		drive(vexRT[Ch3], vexRT[Ch2]);
  	}
  	else {
  		drive(vexRT[Ch3] + vexRT[Ch1], vexRT[Ch3] - vexRT[Ch1]);
  	}


  	if (vexRT[Btn5D] && vexRT[Btn5U]) {
  		arm(armSlowSpeed); //If both buttons pressed go up slowly
  	}	else if (vexRT[Btn5D]) {
  		arm(-armSpeed);
  	} else if (vexRT[Btn5U]) {
  		arm(armSpeed);
  	} else {
  		arm(0);
  	}

	}
}

// void flipPneumatics(bool direction) {
// 	SensorValue[swingArm] = direction?1:0;
// }

// bool currentPneumaticsDirection = true;
// bool pneumaticsWasPressed = false;

// task usercontrol()
// {
//   // User control code here, inside the loop

//   while (true)
//   {
//   	if (vexRT[Btn7D]) {
//   		if (!pneumaticsWasPressed) {
//   			flipPneumatics(currentPneumaticsDirection);
//   			currentPneumaticsDirection = !currentPneumaticsDirection;
//   			pneumaticsWasPressed = true;
//   		}
//   	}
//   	else pneumaticsWasPressed = false;

//   	if (vexRT[Btn8D]) {
//   		if (!driveWasPressed) {
//   				driveIsTank = !driveIsTank;
//   				driveWasPressed = true;
//   		}
//   	}
//   	else {
//   		driveWasPressed = false;
//   	}

//   	if (driveIsTank) {
//   		drive(vexRT[Ch3], vexRT[Ch2]);
//   	}
//   	else {
//   		drive(vexRT[Ch3] + vexRT[Ch1], vexRT[Ch3] - vexRT[Ch1]);
//   	}


// 		if (vexRT[Btn5D] && !SensorValue[armLimitUp]) armUp(-armSpeed); //Up
// 		else if (vexRT[Btn5U]) armUp(armSpeed);
// 		else armUp(0);


//   	if (vexRT[Btn6D]) motor[intake] = intakeSpeed;
// 		else if (vexRT[Btn6U]) motor[intake] = -intakeSpeed;
// 		else motor[intake] = 0;
// 		/*
// 		if (vexRT[Btn8U]) {
// 			auto();
// 		}*/
//   }
// }
