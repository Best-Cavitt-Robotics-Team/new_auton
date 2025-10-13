#include "globals.h"

// Moves a list of motors with a list of powers
void moveMotors(vector<Motor> mtr_list, vector<float> powers) {
	for(int i = 0; i<mtr_list.size(); i++) {
		mtr_list[i].move_voltage(powers[i]);
	}
}

// Moves a list of motors with a single power
void moveMotors(vector<Motor> mtr_list, float power) {
	for(int i = 0; i<mtr_list.size(); i++) {
		mtr_list[i].move_voltage(power);
	}
}

// Moves a single motor with a single power
void moveMotors(Motor mtr, float power) {
	mtr.move_voltage(power * 127);
}

// Prepares scaled input for drive control
void prep_input(double &analog, int exponent) {
	bool shouldFlip = (exponent%2==0) && (analog<0);
	analog = (shouldFlip ? -1:1) * pow(analog,exponent) / pow(127, exponent-1);
}


// Scales a value to a range of -127 to 127
double scale(double value, double scale) {
	return std::clamp(value, -127.0, 127.0) * 12000 / 127 * scale;
}

// Averages the position of the drive motors
double averageDrivePosition(){
	double leftAvg = (left_front.get_position() + left_mid.get_position() + left_back.get_position())/3;
	double rightAvg = (right_front.get_position() + right_mid.get_position() + right_back.get_position())/3;

	return (leftAvg + rightAvg)/2;	
}

// Sets the drive motors to a given percentage speed
void setDrive(double left_percentSpeed, double right_percentSpeed) {

	//converting voltage to current; voltage range: -12000 to 12000
	double left_Voltage = std::clamp(120 * left_percentSpeed, -12000.0, 12000.0);
	double right_Voltage = std::clamp(120 * right_percentSpeed, -12000.0, 12000.0);

	left_front.move_voltage(left_Voltage);
	left_mid.move_voltage(left_Voltage);
	left_back.move_voltage(left_Voltage);

	right_front.move_voltage(right_Voltage);
	right_mid.move_voltage(right_Voltage);
	right_back.move_voltage(right_Voltage);
}

// Returns the sign of a value
float sgn(float val) {
    return (float(0) < val) - (val < float(0));
}