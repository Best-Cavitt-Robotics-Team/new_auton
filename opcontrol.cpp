
#include "main.h"
#include "pros/abstract_motor.hpp"
#define DRIVE_SCALE 1.27
#include "globals.h"
#include "helper_functions.h"

pros::Controller master(pros::E_CONTROLLER_MASTER);
void opcontrol() {
  while (true) {
    // Get input from controller
    double lefty_analog = master.get_analog(ANALOG_LEFT_Y);
    double rightx_analog = master.get_analog(
      ANALOG_RIGHT_X);

    // Convert analog input into quadratic / cubic drive depending on exponent
    prep_input(lefty_analog, 3);
    prep_input(rightx_analog, 3);

    double left_power = lefty_analog + rightx_analog;
    double right_power = lefty_analog - rightx_analog;

    // Move the motors at the desired speed (scaled to DRIVE_SCALE)
    moveMotors({left_back, left_mid, left_front},
               scale(left_power, DRIVE_SCALE));
    moveMotors({right_back, right_mid, right_front},
               scale(right_power, DRIVE_SCALE));
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
      intake_bottom.move_velocity(-600);
      intake_middle.move_velocity(200);
      intake_top.move_velocity(200);
    } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
      intake_bottom.move_velocity(600);
      intake_middle.move_velocity(-200);
      intake_top.move_velocity(-200);
    }

    // middle goal
    else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
      intake_bottom.move_velocity(-600);
      intake_middle.move_velocity(200);
      intake_top.move_velocity(-200);
    } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
      intake_bottom.move_velocity(-600);
      intake_middle.move_velocity(200);
      intake_top.set_brake_mode(MotorBrake::hold);
    } else {
      intake_bottom.move_velocity(0);
      intake_middle.move_velocity(0);
      intake_top.move_velocity(0);
    }

    // scraper
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
      descore.set_value(true);
      
    }
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
      descore.set_value(false);
    }

    // flap
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
      scraper1.set_value(true);
      scraper2.set_value(true);
    }
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) {
      scraper1.set_value(false);
      scraper2.set_value(false);
    }
     if (master.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
      ballblock.set_value(false);
      
    }
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
      ballblock.set_value(true);
      
    }
    // delay
    pros::delay(10);
  }
}
