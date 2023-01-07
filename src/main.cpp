#include "main.h"
#include "pros/misc.h"
#include "pros/rtos.hpp"
#include "pros/screen.h"

#include "shooter.hpp"

#include "replay.hpp"
#include <chrono>

using namespace std::chrono_literals;

typedef long int ull;

const float MOVE_TO_VOLT = 12000 / 128;

// MOTOR DEFINITIONS
pros::Controller drive_con(pros::E_CONTROLLER_MASTER);

pros::Motor left_front(LEFT_FRONT_MOTOR);
pros::Motor left_back(LEFT_BACK_MOTOR);
pros::Motor right_front(RIGHT_FRONT_MOTOR, true);
pros::Motor right_back(RIGHT_BACK_MOTOR, true);

pros::Motor roller(ROLLER_MOTOR);

pros::Motor succ(SUCC_MOTOR);

bool end_game_availible;

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
	left_front.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	left_back.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	right_front.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	right_back.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	roller.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

	// Replay
	VirtualController vc(&drive_con, true);
	std::chrono::high_resolution_clock clock;

	while(true) {
		// Get recorded frame
		vc.read_from_file();

		auto t1 = clock.now(); // Start record
		int left_stick = vc.ly;
		int right_stick = vc.ry;

		// Converted old drive to voltage direct drive
		left_front.move_voltage(MOVE_TO_VOLT * left_stick);
		left_back.move_voltage(MOVE_TO_VOLT * left_stick);
		right_front.move_voltage(MOVE_TO_VOLT * right_stick);
		right_back.move_voltage(MOVE_TO_VOLT * right_stick);
	

		if (vc.r1) {
			roller = 75;
		} else if (vc.r2) {
			roller = -75;
		} else {
			roller = 0;
		}

		// SUCC Control
		if (vc.l1) {
			succ.move_voltage(12000);
		} else if (vc.l2) {
			succ.move_voltage(-12000);
		} else {
			succ.move_voltage(0);
		}

		shoot_auton(drive_con);

		if (drive_con.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN) && end_game_availible) {
			std::cout << "End game used" << std::endl;
			end_game_availible = false;
		}

		// Record time for replay adjustment
		//auto t2 = clock.now();
		//std::chrono::milliseconds ms_adjust = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

		pros::delay(20);
	}	
}

void opcontrol()
{
	left_front.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	left_back.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	right_front.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	right_back.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	roller.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

	// Replay
	VirtualController vc(&drive_con, false);
	std::chrono::high_resolution_clock clock;

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

		shoot_op(drive_con);


		if (drive_con.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN) && end_game_availible) {
			std::cout << "End game used" << std::endl;
			end_game_availible = false;
		}

		// Replay code
		vc.record_frame();
		vc.write_to_file();

		pros::delay(20);
	}	
}
