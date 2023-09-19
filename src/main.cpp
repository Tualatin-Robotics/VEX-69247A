#include "main.h"
#include "pros/misc.h"
#include "pros/rtos.hpp"
#include "pros/screen.h"

#include "shooter.hpp"
#include "roller.hpp"
#include "succ.hpp"

#include "replay.hpp"
#include "drivetrain.hpp"
#include <chrono>

//#define _SAFE_AUTON_B_

using namespace std::chrono_literals;

// MOTOR DEFINITIONS
pros::Controller drive_con(pros::E_CONTROLLER_MASTER);

bool end_game_availible;

void set_tank(int l, int r) {
	left_back = l;
	right_back = r;
	left_front = l;
	right_front = r;
}

// End game functions
void initialize() {
	pros::Task end_game_task{[=] { 
		pros::delay(100*1000);
		end_game_availible = true;
		std::cout << "End Game avalible" << std::endl;
	}};
}

void autonomous() {
	#ifdef _SAFE_AUTON_B_

	roller.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

	left_back = 255;
	right_back = 255;
	left_front = 255;
	right_front = 255;

	pros::delay(500);

	left_back = 0;
	right_back = 0;
	left_front = 0;
	right_front = 0;

	roller = 55;
	succ = -55;

	pros::delay(225);

	roller = 0;
	succ = 0;

	#else
	// Drive train
	init_drivetrain();

	// Replay
	VirtualController vc(&drive_con, true);

	// Main loop
	while(true) {
		double old_time = pros::micros();

		// Get recorded frame
		vc.read_from_file();

		drive_auton(&vc);
	
		roller_auton(&vc);

		// SUCC Control
		succ_auton(&vc);

		shoot_auton(&vc);

		// End game
		if (drive_con.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN) && end_game_availible) {
			std::cout << "End game used" << std::endl;
			end_game_availible = false;
		}

		// Record time for replay adjustment
		double new_time = pros::micros();
		std::cout << "Auton control took " << new_time - old_time << " microseconds";
		pros::delay(14);
		double new_new_time = pros::micros();
		std::cout << " Total time: control took " << new_new_time - new_time << " microseconds" << std::endl;
	}
	#endif
}

void opcontrol()
{
	// Drive train
	init_drivetrain();

	// Replay
	VirtualController vc(&drive_con, false);

	while(true) {
		double old_time = pros::micros();

		drive_op(&drive_con);
	
		roller_op(&drive_con);

		// SUCC Control
		succ_op(&drive_con);

		shoot_op(&drive_con);


		if (drive_con.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN) && end_game_availible) {
			std::cout << "End game used" << std::endl;
			end_game_availible = false;
		}

		// Replay code
		vc.record_frame();
		vc.write_to_file();

		// Record time for replay adjustment
		double new_time = pros::micros();
		std::cout << "Auton control took " << new_time - old_time << " microseconds";
		pros::delay(10);
		double new_new_time = pros::micros();
		std::cout << "Total time: control took " << new_new_time - new_time << " microseconds" << std::endl;
	}	
}
