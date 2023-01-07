#ifndef _SHOOTER_
#define _SHOOTER_

#include "replay.hpp"

//pros::Controller drive_con(pros::E_CONTROLLER_MASTER);

pros::Motor shooter_r(SHOOTER_R_MOTOR, true);
pros::Motor shooter_c(SHOOTER_C_MOTOR, true);

// Pneumatics Setup
int shoot_count = 0;
int shoot_count_limit = 20;
pros::ADIDigitalOut shooter(SHOOT_PORT);

void shoot_op(pros::Controller drive_con) {
    bool shooterSwitch;
	bool aPrevious;
	bool aCurrent;
    if (drive_con.get_digital(pros::E_CONTROLLER_DIGITAL_B) && shoot_count == 0) {
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
    
    aCurrent = drive_con.get_digital(pros::E_CONTROLLER_DIGITAL_A);
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

void shoot_auton(pros::Controller drive_con) {
    bool shooterSwitch;
	bool aPrevious;
	bool aCurrent;

    VirtualController vc(&drive_con, true);

    if (vc.b && shoot_count == 0) {
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
		
	aCurrent = vc.a;
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