#pragma config(Sensor, dgtl1,  liftLimit,      sensorTouch)
#pragma config(Motor,  port1,           FR,            tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           MR,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           liftL,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           armL,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           claw,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           BLFL,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           armR,          tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           liftR,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           ML,            tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          BR,            tmotorVex393_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton()
{
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
	// Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
	bStopTasksBetweenModes = true;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////


//Auto: Drive to mobile goal, pick up, back up next to high goal facing zones, drive forwards, drop, drive back a lil

const int mobileGoalSpeed = 127;

const int minDriveSpeed = 5;
const int clawSpeed = 50;

const int armSpeed = 127;
int correctJoystick(int min, int val) {
	//Joystick not always centered at 0. If below certain threshold, returns 0
	if (-min < val || val < min) {
		return 0;
	}
	else {
		return val;
	}

}


void setMotorSpeed(int l, int r) {
	motor[BLFL] = motor[ML] = l;
	motor[BR] = motor[MR] = motor[FR] = r;
}




task autonomous()
{


}


/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////



task usercontrol()
{

	while(true) {
		wait1Msec(1);
		setMotorSpeed(vexRT[Ch3], vexRT[Ch2]);

		//Lift mobile goal
		if (vexRT[Btn8D] && !SensorValue[liftLimit]) {
			motor[liftL] = motor[liftR] = -mobileGoalSpeed;
		}
		else if (vexRT[Btn8U]) {
			motor[liftL] = motor[liftR] = mobileGoalSpeed;
		}
		else {
			motor[liftL] = motor[liftR] = 0;
		}


		//Arm
		if (vexRT[Btn6D]) {
			motor[armL] = motor[armR] = -armSpeed;
		}
		else if (vexRT[Btn6U]) {
			motor[armL] = motor[armR] = armSpeed;
		}
		else {
			motor[armL] = motor[armR] = 0;
		}


		//Claw
		if (vexRT[Btn5U]) {
			motor[claw] = -clawSpeed;
		}
		else if (vexRT[Btn5D]) {
			motor[claw] = clawSpeed;
		}
		else {
			motor[claw] = 0;
		}
	}
}
