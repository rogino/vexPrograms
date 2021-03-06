#pragma config(Motor,  port2,           frontLeft,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           frontRight,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           backLeft,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           backRight,     tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//NOTE TO SELF: ADD SOME CALIBRATION OF JOYSTICK?
//GET FOUR VARIABLES FOR JOYSTICK, SUBTRACT THAT NUMBER
task main() {
	char switcher = 1;
		while (true) {
		while (switcher) {
			//Ch1: Right Joystick Y-Axis (Fowards/Backwards)
			//Ch2: Right Joystick X-Axis (Strafe Left/Right)
			//Ch4: Left  Joystick X-Axis (Rotate Robot C/Cc)
		  motor[frontLeft]  =  vexRT[Ch2] + vexRT[Ch1] + vexRT[Ch4];
			motor[frontRight] = -vexRT[Ch2] + vexRT[Ch1] + vexRT[Ch4];
			motor[backLeft]   =  vexRT[Ch2] - vexRT[Ch1] + vexRT[Ch4];
			motor[backRight]  = -vexRT[Ch2] - vexRT[Ch1] + vexRT[Ch4];
			if (vexRT[Btn8D]) {
				switcher = 0;
			}

		}

		while(!switcher) {
			motor[frontLeft]  = ( vexRT[Ch2] + vexRT[Ch1] + vexRT[Ch4])/2;
			motor[frontRight] = (-vexRT[Ch2] + vexRT[Ch1] + vexRT[Ch4])/2;
			motor[backLeft]   = ( vexRT[Ch2] - vexRT[Ch1] + vexRT[Ch4])/2;
			motor[backRight]  = (-vexRT[Ch2] - vexRT[Ch1] + vexRT[Ch4])/2;
			if (vexRT[Btn8D]) {
				switcher = 1;
			}
		}
	}
}
