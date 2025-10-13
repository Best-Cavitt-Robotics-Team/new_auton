#include "main.h"
using namespace pros;
using namespace std;

extern pros::Motor left_front;
extern pros::Motor left_mid;
extern pros::Motor left_back;
extern pros::Motor right_front;
extern pros::Motor right_mid;
extern pros::Motor right_back;
extern pros::Motor intake_bottom;
extern pros::Motor intake_middle;
extern pros::Motor intake_top;

extern pros::Imu inertial_sensor;

extern double inch_constant;
extern int selected_auton;
extern pros::adi::DigitalOut scraper1;
extern pros::adi::DigitalOut scraper2;
extern pros::adi::DigitalOut ballblock;
extern pros::adi::DigitalOut descore;