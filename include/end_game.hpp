#ifndef _ENDGAME_
#define _ENDGAME_


#include "main.h"

pros::ADIDigitalOut end_game_shooter(ENDGAME_PORT);
pros::Motor end_game_motor(13);

void end_game(pros::Controller* drive_con) {
    /*
    end_game_shooter.set_value(true);
    pros::delay(1000);
    end_game_shooter.set_value(false);
    */

    end_game_motor = -100;
    pros::delay(40);
    end_game_motor = 0;

    std::cout << "Fire End Game" << std::endl;
}

#endif

