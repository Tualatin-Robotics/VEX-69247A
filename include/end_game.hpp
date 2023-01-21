#ifndef _ENDGAME_
#define _ENDGAME_


#include "main.h"

pros::ADIDigitalOut end_game_shooter(ENDGAME_PORT);

void end_game(pros::Controller* drive_con) {
    if (drive_con->get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
        end_game_shooter.set_value(true);
        pros::delay(1000);
        end_game_shooter.set_value(false);
    }
}

#endif

