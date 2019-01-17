typedef struct {
	bool previouslyPressed;
	ubyte state;
	ubyte numStates;
} NToggleButton;

void initializeNToggleButton(struct NToggleButton* nToggleButton, ubyte initialState, ubyte numStates) {
	nToggleButton->previouslyPressed = false;
	nToggleButton->state = initialState;
	nToggleButton->numStates = numStates;
}

bool NToggleButtonSetter(struct NToggleButton* nToggleButton, bool buttonIsPressed) {
	if (buttonIsPressed && !nToggleButton->previouslyPressed) {
		nToggleButton->previouslyPressed = true;
		nToggleButton->state = (nToggleButton->state + 1) % nToggleButton->numStates;
		return true;
	}
	nToggleButton->previouslyPressed = buttonIsPressed;
	return false;
}
