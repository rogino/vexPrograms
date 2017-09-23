#pragma config(Sensor, dgtl1,  liftLimit,      sensorTouch)
#pragma config(Sensor, dgtl2,  shaftEncL1,     sensorQuadEncoder)
#pragma config(Sensor, dgtl4,  shaftEncR1,     sensorQuadEncoder)
#pragma config(Motor,  port1,           BL,            tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           liftL,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           FL,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           rotateArm,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           armL,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           liftR,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           armR,          tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           claw,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           FR,            tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          BR,            tmotorVex393_HBridge, openLoop)
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

	/*while(true) {
			writeDebugStreamLine("L: %d", SensorValue[shaftEncL1]);
			writeDebugStreamLine("R: %d", SensorValue[shaftEncR1]);
			wait10Msec(10);
			}*/
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



int shaftEncLVal = SensorValue[shaftEncL1];
int shaftEncRVal = SensorValue[shaftEncR1];

const int minDriveSpeed = 5;
const int clawSpeed = 127;

const int rotateSpeed = 100;

const int armSpeed = 40;
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
	motor[BL] = motor[FL] = l;
	motor[BR] = motor[FR] = r;
}




task autonomous()
{
	// .....................................................................................
	// Insert user code here.
	// .....................................................................................

	/*while(SensorValue[shaftEncL1] < 1380)
	{
		if(SensorValue[shaftEncL1] > SensorValue[shaftEncR1])
		{
			setMotorSpeed(50, -63);
		}
		else if(SensorValue[shaftEncL1] < SensorValue[shaftEncR1])
		{
			setMotorSpeed(63, -50);
		}
		else
		{
			setMotorSpeed(63, -63);
		}
		wait1Msec(10);
	}*/



}

void autoTest()
{

	while(SensorValue[shaftEncL1] < 1380)
	{
		if(SensorValue[shaftEncL1] > SensorValue[shaftEncR1])
		{
			setMotorSpeed(50, -63);
		}
		else if(SensorValue[shaftEncL1] < SensorValue[shaftEncR1])
		{
			setMotorSpeed(63, -50);
		}
		else
		{
			setMotorSpeed(63, -63);
		}
		wait1Msec(1);
	}

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
	// User control code here, inside the loop
SensorValue[shaftEncL1] = 0;
SensorValue[shaftEncR1] = 0;

	while(true) {
		writeDebugStreamLine("!");
		setMotorSpeed(vexRT[Ch3], -vexRT[Ch2]);
		/*
		motor[BL] = vexRT[Ch3];
		motor[FL] = vexRT[Ch3];

		motor[BR] = vexRT[Ch2];
		motor[FR] = vexRT[Ch2];
		*/

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


		//Rotate Arm
		/*if (vexRT[Btn7D]) {
			motor[rotateArm] = -rotateSpeed;
		}
		else if (vexRT[Btn7U]) {
			motor[rotateArm] = rotateSpeed;
		}
		else {
			motor[rotateArm] = 0;
		}*/

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

		//Set shaft encoder variables
		shaftEncLVal = SensorValue[shaftEncL1];
		shaftEncRVal = SensorValue[shaftEncR1];


		//Print shaft encoder variables
		if(vexRT[Btn7U])
		{
			if(SensorValue[shaftEncL1] < 1000)
			{
				motor[FL] = 127;
			}
			else
			{
				motor[FL] = 0;
			}
			writeDebugStreamLine("%d", shaftEncLVal);
			writeDebugStreamLine("%d", shaftEncRVal);
		}
		if(vexRT[Btn7D]) autoTest();


		wait1Msec(1);
	}
}
