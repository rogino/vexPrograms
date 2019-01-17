bool signsDifferent(int num1, int num2) {
	// As of 2018-01-18, used in: PidStruct.c, Team 1.C
	return num1 >= 0 && num2 < 0 || num2 >= 0 && num1 < 0;
}
