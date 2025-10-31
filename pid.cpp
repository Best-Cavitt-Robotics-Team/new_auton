#include "helper_functions.h"
#include "globals.h"



// Translate PID Constants
double kP = 0.12;
double kI = 0.0;
double kD = 0.4;
double rampSpeed = 55;

// Turn PID Constants
double tkP = 1.0;
double tkI = 0.0;
double tkD = 0.8;
double tRampSpeed = 40;


double calculateHeadingError(double current, double target) {
    double error = target - current;
    if (error > 180) error -= 360;
    if (error < -180) error += 360;
    return error;
}

// turnType = -1 means only the left side moves when turning
// turnType = 1 means only the right side moves when turning
// turnType = 0 means both sides move when turning
void setHeading(int turnType, double desiredHeading, double howLong){

	double error = desiredHeading;
	double prevError = 0;
	double derivative;
	double totalError = 0;
	
	double prevTpower = 0;

	int time = 0;

	while(time <= howLong){
		error = desiredHeading - inertial_sensor.get_rotation();
		derivative = error - prevError;
		totalError += error;
		double motorPower = (error * tkP) + (derivative * tkD) + (totalError * tkI);
					
		if (std::abs(motorPower-prevTpower)>tRampSpeed){
			motorPower = (motorPower>prevTpower) ? prevTpower+tRampSpeed : prevTpower-tRampSpeed;
		}
					
		setDrive(turnType <= 0 ? motorPower:0, turnType >= 0 ? -motorPower:0);

		prevError = error;
		prevTpower = motorPower;
		pros::delay(20);
		time += 20;
	}
	setDrive(0, 0);
}

void setHeading(double desiredHeading, double howLong, double LmaxSpeed, double RmaxSpeed){

	double error = calculateHeadingError(inertial_sensor.get_rotation(), desiredHeading);
    double prevError = 0;
    double derivative;
    double totalError = 0;

    double prevTpower = 0;
    double minPower = 10; // Minimum power to overcome friction
    double headingTolerance = 1; // Stop when within 0.5 degrees of the target

    int time = 0;

    while (howLong > time || fabs(error) > headingTolerance) {
        error = calculateHeadingError(inertial_sensor.get_rotation(), desiredHeading);
        derivative = error - prevError;
        totalError += error;

        double motorPower = (error * tkP) + (derivative * tkD) + (totalError * tkI);

        // Apply minimum power threshold
        if (fabs(motorPower) < minPower && fabs(error) > 0) {
            motorPower = (motorPower > 0) ? minPower : -minPower;
        }

        // Smooth ramping
        if (std::abs(motorPower - prevTpower) > tRampSpeed) {
            motorPower = (motorPower > prevTpower) ? prevTpower + tRampSpeed : prevTpower - tRampSpeed;
        }

		setDrive(std::clamp(motorPower, -LmaxSpeed, LmaxSpeed), std::clamp(-motorPower, -RmaxSpeed, RmaxSpeed));

		prevError = error;
        prevTpower = motorPower;
        pros::delay(20);
        time += 20;
    }
    setDrive(0, 0);
}

void translate(double desiredInches, double desiredHeading) {
    double desiredValue = (desiredInches * inch_constant) + averageDrivePosition();

    double error = desiredValue - averageDrivePosition();
    double derivative = 0;
    double totalError = 0;
    double prevError = 0;

    double prevPow = 0;
    double minPower = 15; // Minimum power to overcome friction

    while (fabs(error) > 70) { // Smaller threshold for settling
        error = desiredValue - averageDrivePosition();
        derivative = error - prevError;
        totalError += error;

        double motorPower = (error * kP) + (derivative * kD) + (totalError * kI);

        // Apply minimum power threshold
        if (fabs(motorPower) < minPower && fabs(error) > 0) {
            motorPower = (motorPower > 0) ? minPower : -minPower;
        }

        // Smooth ramping
        if (std::abs(motorPower - prevPow) > rampSpeed) {
            motorPower = (motorPower > prevPow) ? prevPow + rampSpeed : prevPow - rampSpeed;
        }

        // Continuous heading correction
        double headingError = inertial_sensor.get_rotation() - desiredHeading;
        double headingCorrection = 3 * headingError;

        double leftPower = motorPower - headingCorrection;
        double rightPower = motorPower + headingCorrection;

        setDrive(leftPower, rightPower);

        prevPow = motorPower;
        prevError = error;
        pros::delay(20);
    }
    setDrive(0, 0);
}

void translate(double desiredInches, double desiredHeading, double howLong){

	double desiredValue = (desiredInches * inch_constant) + averageDrivePosition();

	double error = desiredValue - averageDrivePosition();
	double headingError = sgn(desiredInches) * (desiredHeading - inertial_sensor.get_rotation());

	double derivative = 0;
	double totalError = 0;
	double prevError = 0;

	double prevPow = 0;

	int time = 0; 
	double minPower = 15; // Minimum power to overcome friction

	while(howLong > time){
		error = desiredValue - averageDrivePosition();
        derivative = error - prevError;
        totalError += error;

        double motorPower = (error * kP) + (derivative * kD) + (totalError * kI);

        // Apply minimum power threshold
        if (fabs(motorPower) < minPower && fabs(error) > 0) {
            motorPower = (motorPower > 0) ? minPower : -minPower;
        }

        // Smooth ramping
        if (std::abs(motorPower - prevPow) > rampSpeed) {
            motorPower = (motorPower > prevPow) ? prevPow + rampSpeed : prevPow - rampSpeed;
        }

        // Continuous heading correction
        double headingError = inertial_sensor.get_rotation() - desiredHeading;
        double headingCorrection = 3 * headingError;

        double leftPower = motorPower - headingCorrection;
        double rightPower = motorPower + headingCorrection;

        setDrive(leftPower, rightPower);

        prevPow = motorPower;
        prevError = error;
        pros::delay(20);
        time += 20;
	}
	setDrive(0,0);
}

void translate(double desiredInches, double desiredHeading, double howLong, double maxSpeed){

	double desiredValue = (desiredInches * inch_constant) + averageDrivePosition();

	double error = desiredValue - averageDrivePosition();
	double derivative = 0;
	double totalError = 0;
	double prevError = 0;

	double prevPow = 0;

	int time = 0; 
	double minPower = 10; // Minimum power to overcome friction

	while(howLong>time){
		error = desiredValue - averageDrivePosition();
        derivative = error - prevError;
        totalError += error;

        double motorPower = (error * kP) + (derivative * kD) + (totalError * kI);

        // Apply minimum power threshold
        if (fabs(motorPower) < minPower && fabs(error) > 0) {
            motorPower = (motorPower > 0) ? minPower : -minPower;
        }

        // Smooth ramping
        if (std::abs(motorPower - prevPow) > rampSpeed) {
            motorPower = (motorPower > prevPow) ? prevPow + rampSpeed : prevPow - rampSpeed;
        }

        // Continuous heading correction
        double headingError = inertial_sensor.get_rotation() - desiredHeading;
        double headingCorrection = 3 * headingError;

        double leftPower = motorPower - headingCorrection;
        double rightPower = motorPower + headingCorrection;

        setDrive(std::clamp(leftPower, -maxSpeed, maxSpeed), std::clamp(rightPower, -maxSpeed, maxSpeed));;

        prevPow = motorPower;
        prevError = error;
        pros::delay(20);
        time += 20;
	}
	setDrive(0,0);
}
