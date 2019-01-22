typedef struct {
	bool previouslyPressed;
	bool isTrue;
} ToggleButton;

// RobotC doesn't support functions returning structs... even though the official documentation has an example of this
// Initialization of all variables is needed to avoid running into undefined behaviour
void initializeToggleButton(struct ToggleButton* toggleButton, bool initialState) {
	toggleButton->previouslyPressed = false; // Always starts with no press
	toggleButton->isTrue = initialState;
}


// Updates the state of a ToggleButton
// Args. toggleButton: pointer to ToggleButton struct; buttonIsPressed: whether or not the button is pressed
// Return. true if the state has been changed, false if not
bool toggleButtonSetter(struct ToggleButton* toggleButton, bool buttonIsPressed) {
	if (buttonIsPressed && !toggleButton->previouslyPressed) { // Check if pressed and wasn't previously pressed
		toggleButton->previouslyPressed = true; // Now, have previously pressed it.
		toggleButton->isTrue = !toggleButton->isTrue; // If so, toggle the value and return true
		return true;
	}
	toggleButton->previouslyPressed = buttonIsPressed; // If pressed, previously pressed is true. If not pressed, false. So just set to buttonIsPressed.
	return false; // No change to value, so return false
}

// Example usage

/*
// Using ToggleButton to switch between tank and arcade drive
task main() {
	struct ToggleButton driveModeIsTank; // Create the struct. Can be done outside of any function
	initializeToggleButton(&driveModeIsTank, true); // Starts in tank drive. The '&' means a pointer to the struct is passed so that the function can modify it in-place. This must be done inside a function or task.

	while (true) {
		toggleButtonSetter(&driveModeIsTank, vexRT[Btn8D]); // Runs the setter so the value can be updated if needed. It will return a boolean, but we don't need any special behaviours when the mode changes - we just need to know what state it's in
		if (driveModeIsTank.isTrue) drive(vexRT[Ch3], vexRT[Ch2]); // If true, drive in tank mode. 'driveModeIsTank.isTrue' is used instead of 'driveModeIsTank->isTrue' as in the functions, a pointer to the struct is being passed while in this, the struct is being accessed directly
		else drive(vexRT[Ch3] + vexRT[Ch1], vexRT[Ch3] - vexRT[Ch1]);
	}
}

// Using ToggleButton to toggle pneumatics state
// This does not use the isTrue property, only needing to know when the state changes
task main() {
	struct ToggleButton pneumaticsToggler;
	initializeToggleButton(&pneumaticsToggler);

	while (true) {
		if (toggleButtonSetter(&pneumaticsToggler, vexRT[Btn7D])) { // Function returns true when the value changes
			SensorValue[pneumaticsSensor] = !SensorValue[pneumaticsSensor]; // Invert the value
		}
	}

}
*/