#include "main.h"
#include "globals.h"
#include "helper_functions.h"
void autonomous() {
    switch (selected_auton){
        case 0:
            translate(31, 0, 2000);
            setHeading(0, 90, 600);
            scraper1.set_value(true);
            scraper2.set_value(true);
            pros::delay(500);
            intake_bottom.move_velocity(600);
            intake_middle.move_velocity(600);
            translate(12, 90, 800);
            pros::delay(1000);
            break;
    }
}