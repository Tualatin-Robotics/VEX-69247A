#ifndef _SHOOTER_
#define _SHOOTER_

#include "pros/rtos.h"
#include "replay.hpp"
#include "main.h"

// Pneumatics Setup
int shoot_count = 0;
int shoot_count_limit = 20;
pros::ADIDigitalOut shooter(SHOOT_PORT);

bool shooterSwitch;
bool aPrevious;
bool aCurrent;

void shoot_op(pros::Controller* drive_con) {
    if (drive_con->get_digital(pros::E_CONTROLLER_DIGITAL_B) && shoot_count == 0) {
        shooter.set_value(true);
        pros::delay(70);
        shooter.set_value(false);
        shoot_count = 1;
    }

    if (shoot_count > 0) {
        shoot_count++;
        std::cout << shoot_count << std::endl;
    } 
    if (shoot_count > shoot_count_limit) {
        shoot_count = 0;
        std::cout << "RESET" << std::endl;
    }
    
    aCurrent = drive_con->get_digital(pros::E_CONTROLLER_DIGITAL_A);
    
    //shooter toggle
    if (aCurrent && aCurrent != aPrevious) {
        shooterSwitch = !shooterSwitch;
    }

    aPrevious = aCurrent;


    if (shooterSwitch) {
        shooter_c = 255-100;
        shooter_r = 255;
    } else {
        shooter_c = 0;
        shooter_r = 0;
    }
}

void shoot_auton() {
    bool shooterSwitch;
	bool aPrevious;
	bool aCurrent;

    shooter_c = 255-100;
    pros::delay(200);
    shooter.set_value(true);
    pros::delay(70);
    shooter.set_value(false);
    pros::delay(30);
    shooter.set_value(true);
    pros::delay(70);
    shooter.set_value(false);
    shooter_c = 0;

    /*
    if (vc->b && shoot_count == 0) {
			shooter.set_value(true);
			pros::delay(70);
			shooter.set_value(false);
			shoot_count = 1;
	}

	if (shoot_count > 0) {
			shoot_count++;
			std::cout << shoot_count << std::endl;
		} 
	if (shoot_count > shoot_count_limit) {
			shoot_count = 0;
			std::cout << "RESET" << std::endl;
	}
		
	aCurrent = vc->a;

	//shooter toggle
	if (aCurrent && aCurrent != aPrevious) {
			shooterSwitch = !shooterSwitch;
	}

	aPrevious = aCurrent;
    */
/*
	if (shooterSwitch) {
        shooter_c = 255;
        shooter_r = 255;
    } else {
        shooter_c = 0;
        shooter_r = 0;
    }
    */

    //shooter_c = 255;
      //  shooter_r = 255;
}


#endif