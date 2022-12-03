#include "main.h"
#include "pros/screen.h"
#include "smile_vex.c"

const float MOVE_TO_VOLT = 12000 / 128;

// MOTOR DEFINITIONS
pros::Controller drive_con(pros::E_CONTROLLER_MASTER);

pros::Motor left_front(LEFT_FRONT_MOTOR);
pros::Motor left_back(LEFT_BACK_MOTOR);
pros::Motor right_front(RIGHT_FRONT_MOTOR, true);
pros::Motor right_back(RIGHT_BACK_MOTOR, true);

pros::Motor roller(ROLLER_MOTOR);

pros::Motor shooter_r(SHOOTER_R_MOTOR);
pros::Motor shooter_c(SHOOTER_C_MOTOR, true);

pros::Motor succ(SUCC_MOTOR);

// Pneumatics Setup
int shoot_count = 0;
int shoot_count_limit = 30;
pros::ADIDigitalOut shooter(SHOOT_PORT);

lv_obj_t * Red_btn;
lv_obj_t * Blue_btn;
lv_obj_t * label;

lv_obj_t * A_Team_btn;
lv_obj_t * B_Team_btn;

lv_obj_t * A_Label;
lv_obj_t * B_Label;
lv_obj_t * Red_Label;
lv_obj_t * Blue_Label;

lv_obj_t * img;

enum Team {
	A,
	B
};

Team selected_team;

void set_tank(int l, int r) {
	left_back = l;
	right_back = r;
	left_front = l;
	right_front = r;
}

lv_res_t Blue(lv_obj_t * btn) {
	img = lv_img_create(lv_scr_act(), NULL);
	lv_img_set_src(img, &smile_vex);

	if (selected_team == A){
		//A Team blue auton goes here
	}
	else if (selected_team == B) {
		//B Team blue auton goes here
	}

	lv_obj_del(Red_btn);
	lv_obj_del(Blue_btn);

	return LV_RES_OK;
}

lv_res_t Red(lv_obj_t * btn) {
	img = lv_img_create(lv_scr_act(), NULL);
	lv_img_set_src(img, &smile_vex);

	if (selected_team == A){
		//A Team blue auton goes here
	}
	else if (selected_team == B) {
		//B Team blue auton goes here
	}

	lv_obj_del(Red_btn);
	lv_obj_del(Blue_btn);

	return LV_RES_OK;
}

lv_res_t A_Team(lv_obj_t * btn) {
	selected_team = A;
	Red_btn = lv_btn_create(lv_scr_act(), NULL);
	lv_obj_set_pos(Red_btn, 10, 10);
	lv_obj_set_size(Red_btn, 200, 200);
	lv_btn_set_action(Red_btn, LV_BTN_ACTION_CLICK, Red);

	Blue_btn = lv_btn_create(lv_scr_act(), NULL);
	lv_obj_set_pos(Blue_btn, 210, 10);
	lv_obj_set_size(Blue_btn, 200, 200);
	lv_btn_set_action(Blue_btn, LV_BTN_ACTION_CLICK, Blue);

	lv_obj_del(A_Team_btn);
	lv_obj_del(B_Team_btn);

	return LV_RES_OK;
}

lv_res_t B_Team(lv_obj_t * btn) {
	selected_team = B;
	Red_btn = lv_btn_create(lv_scr_act(), NULL);
	lv_obj_set_pos(Red_btn, 10, 10);
	lv_obj_set_size(Red_btn, 200, 200);
	lv_btn_set_action(Red_btn, LV_BTN_ACTION_CLICK, Red);

	Blue_btn = lv_btn_create(lv_scr_act(), NULL);
	lv_obj_set_pos(Blue_btn, 210, 10);
	lv_obj_set_size(Blue_btn, 200, 200);
	lv_btn_set_action(Blue_btn, LV_BTN_ACTION_CLICK, Blue);

	Red_Label = lv_label_create(Red_btn, NULL);
	lv_label_set_text(label, "Red auton");
	lv_label_set_align(label, LV_LABEL_ALIGN_CENTER);	

	Blue_Label = lv_label_create(Blue_btn, NULL);
	lv_label_set_text(label, "Blue auton");
	lv_label_set_align(label, LV_LABEL_ALIGN_CENTER);

	lv_obj_del(A_Team_btn);
	lv_obj_del(B_Team_btn);

	return LV_RES_OK;
}



void initialize() {
	/*
	// Create button
	A_Team_btn = lv_btn_create(lv_scr_act(), NULL);
	lv_obj_set_pos(A_Team_btn, 10, 10);
	lv_obj_set_size(A_Team_btn, 200, 200);
	lv_btn_set_action(A_Team_btn, LV_BTN_ACTION_CLICK, A_Team);
	
	B_Team_btn = lv_btn_create(lv_scr_act(), NULL);
	lv_obj_set_pos(B_Team_btn, 10, 10);
	lv_obj_set_size(B_Team_btn, 200, 200);
	lv_btn_set_action(B_Team_btn, LV_BTN_ACTION_CLICK, B_Team);

	// Create label for button
	A_Label = lv_label_create(A_Team_btn, NULL);
	lv_label_set_text(label, "A team auton");
	lv_label_set_align(label, LV_LABEL_ALIGN_CENTER);	

	B_Label = lv_label_create(B_Team_btn, NULL);
	lv_label_set_text(label, "B team auton");
	lv_label_set_align(label, LV_LABEL_ALIGN_CENTER);
	*/
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
	roller = 55;
	pros::delay(225);
	roller = 0;

	//B Auton
	/*
	roller = 70;
	//pros::delay(300);
	//roller = 0;
	*/ 
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
