#ifndef PORTS_H
#define PORTS_H

//  ### CONSTANTS ###
const float MOVE_TO_VOLT = 12000 / 128;

//  ### PORT DEFINITION ###
#define LEFT_FRONT_MOTOR 20
#define LEFT_BACK_MOTOR 19
#define RIGHT_FRONT_MOTOR 16
#define RIGHT_BACK_MOTOR 17

//B Team Roller 11 A Team 10
#define ROLLER_MOTOR 11
#define SUCC_MOTOR 9

#define SHOOTER_R_MOTOR 15
#define SHOOTER_C_MOTOR 14

#define ENDGAME_PORT 'B'

#define SHOOT_PORT 'A'
#define ODOMETRY_PORT_0 'C'
#define ODOMETRY_PORT_1 'D'

//  ### MOTOR DEFINITIONS ###
pros::Motor left_front(LEFT_FRONT_MOTOR);
pros::Motor left_back(LEFT_BACK_MOTOR);
pros::Motor right_front(RIGHT_FRONT_MOTOR, true);
pros::Motor right_back(RIGHT_BACK_MOTOR, true);

pros::Motor roller(ROLLER_MOTOR);

pros::Motor shooter_r(SHOOTER_R_MOTOR, true);
pros::Motor shooter_c(SHOOTER_C_MOTOR, true);

pros::Motor succ(SUCC_MOTOR);

#endif