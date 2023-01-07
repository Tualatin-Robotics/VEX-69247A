#ifndef _DRIVETRAIN_
#define _DRIVETRAIN

#include "replay.hpp"
#include "motors.h"

void init_drivetrain() {
    left_front.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	left_back.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	right_front.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	right_back.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void drive_auton(VirtualController* vc) {
    int left_stick = vc->ly;
	int right_stick = vc->ry;

    // Converted old drive to voltage direct drive
    left_front.move_voltage(MOVE_TO_VOLT * left_stick);
    left_back.move_voltage(MOVE_TO_VOLT * left_stick);
    right_front.move_voltage(MOVE_TO_VOLT * right_stick);
    right_back.move_voltage(MOVE_TO_VOLT * right_stick);
}

void drive_op(pros::Controller* drive_con) {
    int left_stick = drive_con->get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
	int right_stick = drive_con->get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
}

#endif