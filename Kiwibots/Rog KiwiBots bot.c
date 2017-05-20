#pragma config(Sensor, dgtl1,  armLimiter,     sensorTouch)
#pragma config(Sensor, dgtl2,  btnL,           sensorTouch)
#pragma config(Sensor, dgtl8,  ultrasound,     sensorSONAR_cm)
#pragma config(Sensor, dgtl10, lr,             sensorTouch)
#pragma config(Sensor, dgtl11, btnR,           sensorTouch)
#pragma config(Motor,  port1,           BL,            tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           BR,            tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           Arm,           tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           FR,            tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          FL,            tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

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

/*Read ability*/

void setDriveSpeed(int l, int r);

void Startup() {
	bool leftChir = !!SensorValue[lr];
	int driveSpeed = 50;
	setDriveSpeed(driveSpeed, driveSpeed);
	wait1Msec(1200);

	setDriveSpeed(0,0);
	wait1Msec(100); //Wait 0.1sec so better for motor
	if (leftChir)
	{
		setDriveSpeed(driveSpeed, -driveSpeed);
	}
	else
	{
		setDriveSpeed(-driveSpeed, driveSpeed);
	}
	wait1Msec(900);//turn for x milliseconds
	setDriveSpeed(0,0);

	wait1Msec(100);

	setDriveSpeed(driveSpeed, driveSpeed);
	wait1Msec(800);

	setDriveSpeed(127, 127);
	wait1Msec(1000);
	setDriveSpeed(0,0);
}


/*
void Startup(){
	int wallLimit = 15;
	bool leftChir = !!SensorValue[lr];
	int driveSpeed = 50;
	while (SensorValue[ultrasound] > wallLimit && SensorValue[ultrasound] != -1)
	{
		setDriveSpeed(driveSpeed,driveSpeed);
	}
	setDriveSpeed(0,0);
	wait1Msec(100); //Wait 0.1sec so better for motor
	if (leftChir)
	{
		setDriveSpeed(driveSpeed, -driveSpeed);
	}
	else
	{
		setDriveSpeed(-driveSpeed, driveSpeed);
	}
	wait1Msec(800);//turn for 2 seconds
	setDriveSpeed(0,0);
	wait1Msec(100); //Wait 0.1sec so better for motor

	while (!SensorValue[btnL] && !SensorValue[btnR] && SensorValue[ultrasound] > 5 && SensorValue[ultrasound] != 1){
		setDriveSpeed(driveSpeed, driveSpeed );
	}
	setDriveSpeed(127, 127);
	wait1Msec(2000);
	setDriveSpeed(0, 0);
}
*/

task autonomous() {
		Startup();
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

bool wasPressed = true;
bool isPressed = false;
int armSpeed = 80;

int absInt(int a) {
	return (a > 0)?a:-a;
}

void setDriveSpeed(int l, int r) {
	//Not omnidrive, so only two motors are required
	int minSpeed = 10; //Ensuring variation in default position of joystick does not move robot
	if (absInt(l) > minSpeed) {
		motor[FL] = l;
		motor[BL] = l;
	}
	else {
		motor[FL] = 0;
		motor[BL] = 0;
	}

	if (absInt(r) > minSpeed) {
		motor[FR] = r;
		motor[BR] = r;
	}
	else {
		motor[FR] = 0;
		motor[BR] = 0;
	}
}

/*task usercontrol() {
	setDriveSpeed(127,127);
	wait1Msec(1000);
	setDriveSpeed(0,0);

}*/
task usercontrol() {
	//Startup();


	// User control code here, inside the loop
	while (true) {
		wait1Msec(1); //Wait 1 millisecond. For button or something.
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
		/*
		//If you trgger sensor/hit ball:
		if (SensorValue[btnR]&& SensorValue[btnL])) {
			setDriveSpeed(-60, -60); //Drive backwards
			wait1Msec(200);
			setDriveSpeed(0,0);
			wait1Msec(50);
		}
		else if (SensorValue[btnR]) {
			setDriveSpeed(-60, -60); //Drive backwards
			wait1Msec(200);
			setDriveSpeed(0,0);
			wait1Msec(50);
		}
		else if (SensorValue[btnL]) {
			setDriveSpeed(-60, -60); //Drive backwards
			wait1Msec(200);
			setDriveSpeed(0,0);
			wait1Msec(50);

		}
		*/
		if (vexRT[Btn7D]) {
			Startup();
		}
		//Delete: automonous



		//Switching modes
		if (vexRT[Btn8D] && !isPressed) {
			//If switching button is pressed and is the first time it has been pressed
			isPressed = true;		  //Set isPressed to true
			wasPressed = !wasPressed; //Switch the mode
		}
		else if (!vexRT[Btn8U]) {
			isPressed = false;
		}

		//MODE TO CONTROL SOMETHING WITH A MOTOR
		if (vexRT[Btn6D] && vexRT[Btn6U]) {
			motor[BL] = vexRT[Ch2];
		}

		//Drive
		else if (!wasPressed) {
			//Default value. Arcade
			//uses right joystick
			setDriveSpeed(vexRT[Ch3] + vexRT[Ch1], vexRT[Ch3] - vexRT[Ch1]);
		}
		else {
			//Tank Drive
			setDriveSpeed(vexRT[Ch3], vexRT[Ch2]);
		}
	}
}
