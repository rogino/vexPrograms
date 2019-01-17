#include "Helper.c"

typedef struct {
	int error;
	int integral;
	short derivative;
	bool errorSignPositive; // Sign of the error

	int target;

	// Constants that need to be set
	float P;
	float I;
	float D;
	bool powerNeededToHoldPosition; // Whether or not power is needed to hold at the current position. If not, the integral will be set to zero when the sign of the error changes.
	int maxIntegral; // Max value the integral can take
	short maxPower; // Max motor strength

	short numLittleMovement; // Number of consecutive runs in which there has been little movement (abs(derivative) < something)
	short numLittleMovementForEnd; // Number of consecutive runs in which there is little movement for PID to finish
	short littleMovementDefinition; // Cannot change by more than this amount to be defined as little movement
	bool pidFinished; // PID has ended. Not neccesarily goal reached, but no/little movement for some time
	short power; // Output power
} PidStruct;

void resetPid(struct PidStruct *pid) {
	pid->error = pid->integral = pid->derivative = pid->power = pid->numLittleMovement = 0;
	pid->pidFinished = false;
	pid->errorSignPositive = true;
}

void initializePidStruct(struct PidStruct* pid, float P, float I, float D, bool powerNeededToHoldPosition, int maxIntegral, short maxPower) {
	pid->P = P;
	pid->I = I;
	pid->D = D;
	pid->powerNeededToHoldPosition = powerNeededToHoldPosition;
	pid->maxIntegral = maxIntegral;
	pid->maxPower = maxPower;
	pid->littleMovementDefinition = 3;
	pid->numLittleMovementForEnd = 50;

	resetPid(pid); // need to initialize all variables
}


short runPid(struct PidStruct *pid, int currentImeValue) {
	if (pid->pidFinished) return 0;

	int error = pid->target - currentImeValue;

	pid->integral += error;

	if (abs(pid->integral) > pid->maxIntegral) pid->integral = 0; // If too large, set to zero
	if (!pid->powerNeededToHoldPosition && signsDifferent(error, pid->error)) pid->integral = 0; // If sign changes, set integral to zero

	pid->derivative = error - pid->error; // Find the rate of change. pid->error gives the previous error

	if (abs(pid->derivative) < pid->littleMovementDefinition) pid->numLittleMovement++;
	else pid->numLittleMovement = 0; // Reset if movement larger
	if (pid->numLittleMovement > pid->numLittleMovementForEnd) pid->pidFinished = true; //Stop movement

	pid->error = error; // Set the new error

	short power = pid->error * pid->P + pid->integral * pid->I + pid->derivative * pid->D;

	// Limit power
	if (power > pid->maxPower) power = pid->maxPower;
	else if (power < -pid->maxPower) power = -pid->maxPower;

	pid->power = power;
	return power;
}
