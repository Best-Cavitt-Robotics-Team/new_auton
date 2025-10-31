#include "main.h"
#include "globals.h"
#include "helper_functions.h"

pros::Motor left_front(-17);
pros::Motor left_mid(11);
pros::Motor left_back(-6);
pros::Motor right_front(3);
pros::Motor right_mid(-16);
pros::Motor right_back(9);
pros::Motor intake_bottom(10);
pros::Motor intake_middle(13);
pros::Motor intake_top(8);

pros::Imu inertial_sensor(14);

double inch_constant=33.75;
int selected_auton=0;
pros::adi::DigitalOut scraper1('A');
pros::adi::DigitalOut scraper2('B');
pros::adi::DigitalOut ballblock('C');
pros::adi::DigitalOut descore('D');