#ifndef _ROLLER_
#define _ROLLER_

#include "replay.hpp"

void roller_op(pros::Controller* drive_con) {
    if (drive_con -> get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
		roller = 125;
	} else if (drive_con -> get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
		roller = -75;
	} else {
		roller = 0;
	}
}

void roller_auton(VirtualController* vc) {
    if (vc->r1 == true) {
		roller = 75;
	} else if (vc->r2 == true) {
		roller = -75;
	} else {
		roller = 0;
	}
}

#endif