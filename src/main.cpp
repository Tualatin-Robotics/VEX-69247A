#include "main.h"
#include "pros/misc.h"
#include "pros/rtos.hpp"
#include "pros/screen.h"

#include "replay.hpp"
#include "drivetrain.hpp"
#include <chrono>

using namespace std::chrono_literals;

typedef long int ull;

// MOTOR DEFINITIONS
pros::Controller drive_con(pros::E_CONTROLLER_MASTER);

bool end_game_availible;

// Pneumatics Setup
int shoot_count = 0;
int shoot_count_limit = 20;
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
	init_drivetrain();
	roller.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

	//varibles for shooter switch
	bool shooterSwitch;
	bool aPrevious;
	bool aCurrent;

	// Replay
	VirtualController vc(&drive_con, true);
	std::chrono::high_resolution_clock clock;

	while(true) {
		// Get recorded frame
		vc.read_from_file();

		auto t1 = clock.now(); // Start record
		drive_auton(&vc);
	

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

		if (vc.b && shoot_count == 0) {
			shooter.set_value(true);
			pros::delay(70);
			shooter.set_value(false);
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
		
		aCurrent = vc.a;
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

		// Record time for replay adjustment
		//auto t2 = clock.now();
		//std::chrono::milliseconds ms_adjust = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

		pros::delay(20);
	}	
}

void opcontrol()
{
	init_drivetrain();
	roller.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

	//varibles for shooter switch
	bool shooterSwitch;
	bool aPrevious;
	bool aCurrent;

	// Replay
	VirtualController vc(&drive_con, false);
	std::chrono::high_resolution_clock clock;

	while(true) {
		auto t1 = clock.now(); // Start record
		drive_op(&drive_con);
	

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
			shooter.set_value(false);
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
		vc.record_frame();
		vc.write_to_file();

		// Record time for replay adjustment
		auto t2 = clock.now();
		//double ms_adjust = std::chrono::milliseconds(t2 - t1).count();
		//std::cout << "Op control took " << ms_adjust << " ms" << std::endl;

		pros::delay(20);
	}	
}
