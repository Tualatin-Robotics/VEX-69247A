#include "main.h"
#include "pros/misc.h"
#include "pros/rtos.hpp"
#include "pros/screen.h"

#include "shooter.hpp"
#include "roller.hpp"
#include "succ.hpp"
#include "end_game.hpp"

#include "replay.hpp"
#include "drivetrain.hpp"
#include <chrono>

using namespace std::chrono_literals;

// MOTOR DEFINITIONS
pros::Controller drive_con(pros::E_CONTROLLER_MASTER);

bool end_game_availible;

// End game functions
void initialize() {
	pros::Task end_game_task{[=] { 
		pros::delay(1*1000);
		end_game_availible = true;
		std::cout << "End Game avalible" << std::endl;
	}};
}

void autonomous() {
	// Drive train
	init_drivetrain();

	// Replay
	VirtualController vc(&drive_con, true);
	std::chrono::high_resolution_clock clock;

	// Main loop
	while(true) {
		auto t1 = clock.now();

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
		auto t2 = clock.now();
		std::chrono::milliseconds ms_adjust = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
		std::cout << "Auton control took " << ms_adjust.count() << " ms" << std::endl;
		pros::delay(14);
	}
}

void opcontrol()
{
	// Drive train
	init_drivetrain();

	// Replay
	VirtualController vc(&drive_con, false);
	std::chrono::high_resolution_clock clock;

	while(true) {
		auto t1 = clock.now();

		//Drivetrain Control
		drive_op(&drive_con);
		//Roller Control
		roller_op(&drive_con);
		// SUCC Control
		succ_op(&drive_con);
		//Shoot Controll
		shoot_op(&drive_con);

		if (end_game_availible && drive_con.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
			end_game(&drive_con);
			end_game_availible = false;
		}

		// Replay code
		vc.record_frame();
		vc.write_to_file();

		// Record time for replay adjustment
		auto t2 = clock.now();
		std::chrono::milliseconds ms_adjust = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
		std::cout << "Op control took " << ms_adjust.count() << " ms" << std::endl;
		pros::delay(10);
	}	
}
