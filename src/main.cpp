#include "main.h"
#include "pros/misc.h"
#include "pros/rtos.hpp"
#include "pros/screen.h"

#include "libreplay/main.hpp"

typedef long int ull;

const float MOVE_TO_VOLT = 12000 / 128;

// MOTOR DEFINITIONS
pros::Controller drive_con(pros::E_CONTROLLER_MASTER);

pros::Motor left_front(LEFT_FRONT_MOTOR, true);
pros::Motor left_back(LEFT_BACK_MOTOR, true);
pros::Motor right_front(RIGHT_FRONT_MOTOR);
pros::Motor right_back(RIGHT_BACK_MOTOR);

pros::Motor roller(ROLLER_MOTOR);

pros::Motor shooter_r(SHOOTER_R_MOTOR, true);
pros::Motor shooter_c(SHOOTER_C_MOTOR, true);

pros::Motor succ(SUCC_MOTOR);

bool end_game_availible;

// Pneumatics Setup
int shoot_count = 0;
int shoot_count_limit = 30;
pros::ADIDigitalOut shooter(SHOOT_PORT);

void set_tank(int l, int r) {
	left_back = l;
	right_back = r;
	left_front = l;
	right_front = r;
}

void initialize() {
	pros::Task task{[=] {
		pros::delay(100*1000);
		end_game_availible = true;
		std::cout << "End Game avalible" << std::endl;
	}};
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

	roller = 55;
	pros::delay(225);
	roller = 0;
}

void opcontrol()
{

	left_front.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	left_back.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	right_front.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	right_back.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	roller.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);


	//varibles for shooter switch
	bool shooterSwitch;
	bool aPrevious;
	bool aCurrent;


	while(true) {
		int left_stick = drive_con.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int right_stick = drive_con.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

		// Converted old drive to voltage direct drive
		left_front.move_voltage(MOVE_TO_VOLT * left_stick);
		left_back.move_voltage(MOVE_TO_VOLT * left_stick);
		right_front.move_voltage(MOVE_TO_VOLT * right_stick);
		right_back.move_voltage(MOVE_TO_VOLT * right_stick);
	

		if (drive_con.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
			roller = 75;
		} else if (drive_con.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
			roller = -75;
		} else {
			roller = 0;
		}

		// SUCC Control
		if (drive_con.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
			succ.move_voltage(12000);
		} else if (drive_con.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
			succ.move_voltage(-12000);
		} else {
			succ.move_voltage(0);
		}

		if (drive_con.get_digital(pros::E_CONTROLLER_DIGITAL_B) && shoot_count == 0) {
			shooter.set_value(true);
			pros::delay(70);
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

		if (drive_con.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN) && end_game_availible) {
			std::cout << "End game used" << std::endl;
			end_game_availible = false;
		}



		// Replay code
		VirtualController vc;
		

		pros::delay(20);
	}	
}
