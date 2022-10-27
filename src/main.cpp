#include "main.h"
#include "motors.hpp"

#define MOTOR_LEFT 4

void opcontrol()
{
	pros::Controller drive_con(pros::E_CONTROLLER_MASTER);

	pros::Motor left_front(2);
	pros::Motor left_back(1);
	pros::Motor right_front(3, true);
	pros::Motor right_back(4, true);

	pros::Motor roller(5);

	left_front.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	left_back.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	right_front.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	right_back.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	roller.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);


	while(true) {
		int left_stick = drive_con.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int right_stick = drive_con.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

		left_front = left_stick;
		left_back = left_stick;
		right_front = right_stick;
		right_back = right_stick;

		if (drive_con.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
			roller = 40;
		} else {
			roller = 0;
		}

		pros::delay(50);
	}	
}
