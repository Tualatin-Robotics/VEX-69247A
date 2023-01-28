#ifndef _SUCC_
#define _SUCC_

#include "replay.hpp"

bool succing_in = false;
bool succing_out = false;

void succ_op(pros::Controller* drive_con) {
    if (drive_con -> get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
		succing_in = !succing_in;
        succing_out = false;
    } else if (drive_con -> get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
        succing_out = !succing_out;
        succing_in = false;
    }
    if (succing_in) {
        succ.move_voltage(12000);
    } else if (succing_out) {
        succ.move_voltage(-12000);
    }
    else {
        succ.move_voltage(0);
    }
}

void succ_auton(VirtualController* vc) {
    if (vc->l1 == true) {
        succ.move_voltage(12000);
    } else if (vc->l2 == true) {
        succ.move_voltage(-12000);
    } else {
        succ.move_voltage(0);
    }
}

#endif