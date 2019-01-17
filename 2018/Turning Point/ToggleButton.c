typedef struct {
	bool previouslyPressed;
	bool isTrue;
} ToggleButton;

// RobotC doesn't support functions returning structs... even though the official documentation has an example of this
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
