#pragma config(Sensor, dgtl1, armLimiter, sensorTouch)
#pragma config(Motor, port1, BL, tmotorVex393_HBridge, openLoop)
#pragma config(Motor, port2, BR, tmotorVex393_MC29, openLoop)
#pragma config(Motor, port8, Arm, tmotorVex393_MC29, openLoop)
#pragma config(Motor, port9, FR, tmotorVex393_MC29, openLoop)
#pragma config(Motor, port10, FL, tmotorVex393_HBridge, openLoop)

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c" //Main competition background code...do not modify!

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton() {
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

task autonomous() {
	// .....................................................................................
	// Insert user code here.
	// .....................................................................................

	AutonomousCodePlaceholderForTesting(); // Remove this function call once you have "real" code.
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

bool wasPressed = false;
bool isPressed = false;
int armSpeed = 80;

void setDriveSpeed(int l, int r) {
	//Not omnidrive, so only two motors are required
	int minSpeed = 10; //Ensuring variation in default position of joystick does not move robot
	if (abs(l) > minSpeed) {
		motor[FL] = l;
		motor[BL] = l;
	}
	else {
		motor[FL] = 0;
		motor[BL] = 0;
	}

	if (abs(frontL) > minSpeed) {
		motor[FR] = r;
		motor[BR] = r;
	}
	else {
		motor[FR] = 0;
		motor[BR] = 0;
	}
}

task usercontrol() {
	// User control code here, inside the loop
	while (true) {
		//Arm
		if (vexRT[Btn5U]) {		
			motor[Arm] = armSpeed;
		}
		else if (vexRT[Btn5D] && !SensorValue[armLimiter]) {		
			//When 5D is pressed and the sensor is not triggered, allow movement
			motor[Arm] = -1 * armSpeed;
		}
		else {		
			motor[Arm] = 0;
		}

		//Switching modes
		if (vexRT[Btn6U] && !isPressed) {		
			//If switching button is pressed and is the first time it has been pressed
			isPressed = true;		  //Set isPressed to true
			wasPressed = !wasPressed; //Switch the mode
		}
		else if (!vexRT[Btn6U]) {		
			isPressed = false;
		}

		//Drive
		if (!wasPressed) {		
			//Default value. Arcade
			//uses right joystick
			setDriveSpeed(vexRT[Ch1] + vexRT[Ch3], vexRT[Ch1] - vexRT[Ch3]);
		}
		else {		
			//Tank Drive
			setDriveSpeed(vexRT[Ch3], -vexRT[Ch2]);
		}
	}
}
