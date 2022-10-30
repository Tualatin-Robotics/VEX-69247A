#include "main.h"
#include "motors.hpp"

#define MOTOR_LEFT 4
#define SHOOT_PORT 'A'

// MOTOR DEFINITIONS
pros::Controller drive_con(pros::E_CONTROLLER_MASTER);

pros::Motor left_front(2);
pros::Motor left_back(1);
pros::Motor right_front(3, true);
pros::Motor right_back(4, true);

pros::Motor roller(5);

pros::Motor shooter_r(6);
pros::Motor shooter_c(7, true);

int shoot_count = 0;
int shoot_count_limit = 30;
pros::ADIDigitalOut shooter(SHOOT_PORT);

void set_tank(int l, int r) {
	left_back = l;
	right_back = r;
	left_front = l;
	right_front = r;
}

void autonomous() {
	roller.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

	left_back = 30;
	right_back = 30;
	left_front = 30;
	right_front = 30;

	pros::delay(500);

	left_back = 0;
	right_back = 0;
	left_front = 0;
	right_front = 0;

	//A Auton
	//roller = 55;
	//pros::delay(225);
	//roller = 0;

	//B Auton
	roller = 70;
	pros::delay(300);
	roller = 0; 
}

void opcontrol()
{
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
			roller = 75;
		} else if (drive_con.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
			roller = -75;
		} else {
			roller = 0;
		}

		if (drive_con.get_digital(pros::E_CONTROLLER_DIGITAL_B) && shoot_count == 0) {
			shooter.set_value(true);
			pros::delay(70);
			//shooter.set_value(false);

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



		shooter_r = 255;
		shooter_c = 255;

		pros::delay(20);
	}	
}