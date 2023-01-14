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

using namespace std::chrono_literals;

// MOTOR DEFINITIONS
pros::Controller drive_con(pros::E_CONTROLLER_MASTER);

bool end_game_availible;

//std::chrono::milliseconds auton_adjust;
std::chrono::milliseconds op_adjust;

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
	init_drivetrain();
	roller.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

	// Replay
	VirtualController vc(&drive_con, true);
	std::chrono::high_resolution_clock clock;

	while(true) {
		auto t1 = clock.now();

		// Get recorded frame
		vc.read_from_file();

		drive_auton(&vc);
	
		roller_auton(&vc);

		// SUCC Control
		succ_auton(&vc);

		shoot_auton(&vc);

		if (drive_con.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN) && end_game_availible) {
			std::cout << "End game used" << std::endl;
			end_game_availible = false;
		}

		// Record time for replay adjustment
		auto t2 = clock.now();
		std::chrono::milliseconds ms_adjust = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
		std::cout << "Auton control took " << ms_adjust.count() << " ms" << std::endl;
		pros::delay(23);
	}
}

void opcontrol()
{
	init_drivetrain();
	roller.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

	// Replay
	VirtualController vc(&drive_con, false);
	std::chrono::high_resolution_clock clock;

	while(true) {
		auto t1 = clock.now();

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
		auto t2 = clock.now();
		std::chrono::milliseconds ms_adjust = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
		std::cout << "Op control took " << ms_adjust.count() << " ms" << std::endl;
		op_adjust = ms_adjust;
		pros::delay(20);
	}	
}
