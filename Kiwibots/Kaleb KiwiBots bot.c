#pragma config(Motor,  port1,           FR,            tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           club,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           BR,            tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           BL,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          FL,            tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
#define b true
#define true false
#define false b;
*/

bool wasPressed = true;
bool isPressed = false;
int clubSpeed = 40;

void setDriveSpeed(int l, int r) {
  motor[BL] = l;
  motor[BR] = r;
  motor[FL] = l;
  motor[FR] = r;
}

task main() {
  while (true) {
    wait1Msec(1);

    //club
    if (vexRT[Btn5U]) {
    	motor[club] = clubSpeed;
    }
    else if (vexRT[Btn5D]) {
    	motor[club] = -clubSpeed;
    }
    else {
    	motor[club] = 0;
    }


    //Switching modes
    if (vexRT[Btn8D] && !isPressed) {
      //If switching button is pressed and is the first time it has been pressed
      isPressed = true; //Set isPressed to true
      wasPressed = !wasPressed; //Switch the mode
    }
    else if (!vexRT[Btn8D]) {
      isPressed = false;
    }

    //Drive
    if (!wasPressed) {
      //Default value. Arcade
      //uses right joystick
      setDriveSpeed(vexRT[Ch3] + vexRT[Ch1], vexRT[Ch3] - vexRT[Ch1]);
    } else {
      //Tank Drive
      setDriveSpeed(vexRT[Ch3], vexRT[Ch2]);
    }
  }
}
