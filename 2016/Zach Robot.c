#pragma config(Motor,  port1,           leftDrive,     tmotorVex393, openLoop)
#pragma config(Motor,  port2,           rightDrive,    tmotorVex393, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main(){
	while(true) {
		motor[leftDrive] = vexRT[Ch2] + vexRT[Ch1];
		motor[rightDrive]= vexRT[Ch2] - vexRT[Ch1];

	}
}
