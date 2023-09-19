#ifndef _FLIP_
#define _FLIP_

#include "replay.hpp"

bool flipped = false;

void flip(pros::Controller* drive_con) {
    if (drive_con->get_digital(pros::E_CONTROLLER_DIGITAL_UP)) 
    {
        if (!flipped) {
            flippy = 100;
        }
        else {
            flippy = -100;
        }
        pros::delay(2);
        flippy = 0;
        flipped = !flipped;
    }
}
#endif
