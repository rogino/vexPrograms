#pragma config(Motor,  port1,           theLeftDriveMotor,          tmotorVex393, openLoop)
#pragma config(Motor,  port2,           theRightDriveMotor,         tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port3,           arm,           tmotorVex393, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	motor[theRightDriveMotor] = vexRT[Ch2];
	motor[theLeftDriveMotor] = vexRT[Ch3];
	if(vexRT[btn5U]) {
		motor[arm] = 50;
	}
	else if(vexRT[btn5D]) {
		motor[arm] = -50;
	}
}
