task main()
{
	int targetAngle = -15;
	short armMotorVariableThing = 0;//Motor variable which will be incremented
	
	
	if (!(vexRT[Btn5D] || vexRT[Btn5U])) {//If neither buttons are pressed
		if (targetAngle != -15) {//Potentiometer value is 0-1024, so setting it to a value that cannot be reached unless by manual setting
			targetAngle = sensorPotentiometer; //Set the target angle 
	}
	
	
		if (targetAngle > sensorPotentiometer) {//If the potentiometer value is smaller than the target angle,
			armMotorVariableThing++; //Increase the speed of the armMotor by one
		}
		
		else if (targetAngle < sensorPotentiometer) {//If it is bigger (going up)
			armMotorVariableThing--; //Decrease the speed
		}
		
		motor[armMotor] = armMotorVariableThing; //Set the speed for the motor
	}
	
	
	else if(vexRT[Btn5D] || vexRT[Btn5U]) { //Resetting variables if a arm button is pressed
		angle = 0;
		armMotorVariableThing = -15;
	}
}