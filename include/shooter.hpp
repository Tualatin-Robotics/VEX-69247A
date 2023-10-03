#ifndef _SHOOTER_
#define _SHOOTER_

#include "replay.hpp"
#include "main.h"

// Pneumatics Setup
int timer = 0;
int shoot_time_max = 20;
pros::ADIDigitalOut shooter(SHOOT_PORT);

bool shooterSwitch = false;
bool aPrevious = false;
bool aCurrent = false;

void shoot_op(pros::Controller* drive_con) {
    //Timer determines when you can shoot. When the timer is 0, you can shoot
    if (drive_con->get_digital(pros::E_CONTROLLER_DIGITAL_B) && timer <= 0) {
        shooter.set_value(true);
        pros::delay(70);
        shooter.set_value(false);
        timer = shoot_time_max;
    }


    //Timer is constantly counting down to zero
    timer -= 1;
    if (timer < 0) {
        //Make sure timer doesn't go super negative. Probably doesn't matter, but it helps me sleep better
        timer = 0;
    }
    
    aCurrent = drive_con->get_digital(pros::E_CONTROLLER_DIGITAL_A);
    
    //shooter toggle
    if (aCurrent && aCurrent != aPrevious) {
        shooterSwitch = !shooterSwitch;
    }

    aPrevious = aCurrent;


    if (shooterSwitch) {
        shooter_c = 255;
        shooter_r = 255;
    } else {
        shooter_c = 0;
        shooter_r = 0;
    }
}

void shoot_auton(VirtualController* vc) {
    //The timer stuff is explain in op above
    if (vc->b && timer <= 0) {
		shooter.set_value(true);
		pros::delay(70);
		shooter.set_value(false);
		timer = shoot_time_max;
	}

	timer -= 1;
    if (timer < 0) {
        timer = 0;
    }
		
	aCurrent = vc->a;

	//shooter toggle
	if (aCurrent && aCurrent != aPrevious) {
		shooterSwitch = !shooterSwitch;
	}

	aPrevious = aCurrent;

	if (shooterSwitch) {
		shooter_c = 255;
		shooter_r = 255;
	} else {
		shooter_c = 0;
		shooter_r = 0;
	}
}


#endif