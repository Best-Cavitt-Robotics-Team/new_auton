#include "helper_functions.h"
#include "main.h"
#include "globals.h"

void autonomous() {
    switch (selected_auton){
        case 0:

            //move to match loader and turn
            translate(32,0,1500);
            setHeading(0, 90, 750);
            scraper1.set_value(true);
            scraper2.set_value(true);
            pros::delay(100);

            //run intake and go into match loader and come out
            intake_bottom.move_velocity(-600);
            intake_middle.move_velocity(600);
            translate(18,90,3000);
            pros::delay(500);
            intake_bottom.move_velocity(-600);
            intake_middle.move_velocity(600);
            translate(-12,90,1200);

            //move out of match loader
            scraper1.set_value(false);
            scraper2.set_value(false);
            setHeading(0,-87,1200);

            //turn and go into long goal
            translate(20,-90,1500);
            intake_bottom.move_velocity(-600);
            intake_middle.move_velocity(600);
            intake_top.move_velocity(200);
            pros::delay(250);
            intake_bottom.move_velocity(600);
            intake_middle.move_velocity(-600);
            intake_top.move_velocity(-200);
            pros::delay(250);
            intake_bottom.move_velocity(-600);
            intake_middle.move_velocity(600);
            intake_top.move_velocity(200);
            pros::delay(2000);
            intake_top.move_velocity(0);
            intake_middle.move_velocity(0);
            intake_bottom.move_velocity(0);

            //go backwards and into 3 blocks
            translate(-10,-90,1500);
            setHeading(0,74, 750);
            // translate(10,-180,1500);
            // setHeading(0, -45, 750);
            // intake_bottom.move_velocity(-600);
            // intake_middle.move_velocity(600);
            // translate(20, -45, 1000);
        
            // pros::delay(100);
            // intake_bottom.move_velocity(0);
            // intake_middle.move_velocity(0);
            // translate(10, -45, 1000);
            // intake_bottom.move_velocity(600);
            // intake_middle.move_velocity(-600);
            break;
        case 1: 
            //move to match loader and turn
            translate(32,0,1500);
            setHeading(0, -90, 750);
            scraper1.set_value(true);
            scraper2.set_value(true);
            pros::delay(100);

            //run intake and go into match loader and come out
            intake_bottom.move_velocity(-600);
            intake_middle.move_velocity(600);
            translate(18,-90,3000);
            pros::delay(500);
            intake_bottom.move_velocity(-600);
            intake_middle.move_velocity(600);
            translate(-12,-90,1200);

            //move out of match loader
            scraper1.set_value(false);
            scraper2.set_value(false);
            setHeading(0,87,1200);

            //turn and go into long goal
            translate(20,90,1500);
            intake_bottom.move_velocity(-600);
            intake_middle.move_velocity(600);
            intake_top.move_velocity(200);
            pros::delay(250);
            intake_bottom.move_velocity(600);
            intake_middle.move_velocity(-600);
            intake_top.move_velocity(-200);
            pros::delay(250);
            intake_bottom.move_velocity(-600);
            intake_middle.move_velocity(600);
            intake_top.move_velocity(200);
            pros::delay(2500);
            intake_top.move_velocity(0);
            intake_middle.move_velocity(0);
            intake_bottom.move_velocity(0);

            //go backwards and into 3 blocks
            translate(-10,90,1500);
            setHeading(0,-90, 750);
            // translate(10,180,1500);
            // setHeading(0, 45, 750);
            // intake_bottom.move_velocity(-600);
            // intake_middle.move_velocity(600);
            // translate(20, 45, 1000);
        
            // pros::delay(100);
            // intake_bottom.move_velocity(0);
            // intake_middle.move_velocity(0);
            // translate(10, 45, 1000);
            // intake_bottom.move_velocity(600);
            // intake_middle.move_velocity(-600);
        break;

        
}
}

