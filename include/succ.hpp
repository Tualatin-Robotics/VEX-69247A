#ifndef _SUCC_
#define _SUCC_

#include "replay.hpp"

void succ_op(pros::Controller* drive_con) {
    if (drive_con -> get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
		succ.move_voltage(12000);
    } else if (drive_con -> get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
        succ.move_voltage(-12000);
    } else {
        succ.move_voltage(0);
    }
}

void succ_auton(VirtualController* vc) {
    if (vc -> l1) {
        succ.move_voltage(12000);
    } else if (vc -> l2) {
        succ.move_voltage(-12000);
    } else {
        succ.move_voltage(0);
    }
}

#endif