#pragma config(Sensor, dgtl1,  armBottom,      sensorTouch)
#pragma config(Sensor, dgtl2,  armTop,         sensorTouch)
#pragma config(Sensor, dgtl9,  l1,             sensorDigitalOut)
#pragma config(Sensor, dgtl10, l2,             sensorDigitalOut)
#pragma config(Sensor, dgtl11, r1,             sensorDigitalOut)
#pragma config(Sensor, dgtl12, r2,             sensorDigitalOut)
#pragma config(Motor,  port1,           BL,            tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           FL,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           armL,          tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           claw,          tmotorServoStandard, openLoop, reversed)
#pragma config(Motor,  port8,           armR,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           FR,            tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          BR,            tmotorVex393_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

int setMinSpeed(int min, int val) {
	if (abs(val) > min) {
		return val;
	}
	else {
		return 0;
	}
}

void drive(int left, int right) {
	int min = 5;
	motor[BL] = motor[FL] = setMinSpeed(min, left);
	motor[BR] = motor[FR] = setMinSpeed(min, right);
}


void setArmSpeed(int speed) {
	motor[armL] = motor[armR] = speed;
}

void triggerPneumatics(bool dir) {
	SensorValue[l1] = SensorValue[l2] = SensorValue[r1] = SensorValue[r2] = dir?1:0;
}

int armSpeed = 80;
int armSlowSpeed = 40;
int clawSpeed = 100;
int clawSlowSpeed = 40;
bool isTank = false;
bool previouslyPressed = false;
task main() {

	while(true) {
		wait1Msec(1);
		if (isTank) {
			drive(vexRT[Ch3], vexRT[Ch2]);
		}
		else {
			drive(vexRT[Ch3] + vexRT[Ch1], vexRT[Ch3] - vexRT[Ch1]);
		}

		if (vexRT[Btn8D]) {
			if (!previouslyPressed) {
				//If was not previously pressed
				isTank = !isTank; //Change mode
			}
			previouslyPressed = true;
		}
		else {
			previouslyPressed = false;
		}

		//Arm
		if (vexRT[Btn5D] && vexRT[Btn5U]) {
			setArmSpeed(armSlowSpeed);
		}
		else if (vexRT[Btn5D] && !SensorValue[armBottom]) {
			setArmSpeed(-armSpeed);
		}
		else if (vexRT[Btn5U] && !SensorValue[armTop]) {
			setArmSpeed(armSpeed);
		}
		else {
			setArmSpeed(0);
		}

		//Claw
		if (vexRT[Btn6D] && vexRT[Btn6U]) {
			motor[claw] = clawSlowSpeed;
		}
		else if (vexRT[Btn6U]) {
			motor[claw] = clawSpeed;
		}
		else if (vexRT[Btn6D]) {
			motor[claw] = -clawSpeed;
		}
		else {
			motor[claw] = 0;
		}
		triggerPneumatics((vexRT[Btn7D])?false:true);
	}



}
