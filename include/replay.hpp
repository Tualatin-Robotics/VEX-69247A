#ifndef REPLAY_H
#define REPLAY_H

#include "main.h"
#include <string>
#include <sstream>

class VirtualController {
    int x1, y1, x2, y2;
    bool a, b, l1, l2, r1, r2;

    std::string encode() {
        std::stringstream ss;
        ss << x1 << ',';
        ss << y1 << ',';  
        ss << x2 << ',';  
        ss << y2 << ',';  
        ss << a << ',';    
        ss << b << ',';  
        ss << l1 << ',';  
        ss << l2 << ',';  
        ss << r1 << ',';  
        ss << r2 << ',';  

        return ss.str();
    }

    std::ostream& operator<<(const pros::Controller& cont) {

    }
};

#endif