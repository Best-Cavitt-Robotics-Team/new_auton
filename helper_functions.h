#include "main.h"
#include "globals.h"

void moveMotors(vector<Motor> mtr_list, vector<float> powers);
void moveMotors(vector<Motor> mtr_list, float power);
void moveMotors(Motor mtr, float power);
void prep_input(double &analog, int exponent);

void setHeading(int turnType, double desiredHeading, double howLong);
void setHeading(double desiredHeading, double howLong, double LmaxSpeed, double RmaxSpeed);
void translate(double desiredInches, double desiredHeading);
void translate(double desiredInches, double desiredHeading, double howLong); 
void translate(double desiredInches, double desiredHeading, double howLong, double maxSpeed);

double averageDrivePosition();
void setDrive(double left_percentSpeed, double right_percentSpeed);
double scale(double value, double scale);
float sgn(float val);