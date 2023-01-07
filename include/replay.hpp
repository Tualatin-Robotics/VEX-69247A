#ifndef _REPLAY_
#define _REPLAY_

#include "main.h"
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>

const int file_size = 40 * 1024;

class VirtualController {
    public:
    int lx, ly, rx, ry;
    bool l1, l2, r1, r2;
    bool a, b, x, y;
    FILE* usd_file;

    pros::Controller* cont;

    VirtualController(pros::Controller* _cont, bool isReading) {
        cont = _cont;
        if (isReading) {
            usd_file = fopen("/usd/rec_01.txt", "r");
        } else {
            //usd_file = fopen("/usd/rec_01.txt", "w");
        }
        
    }

    void record_frame() {
        // Analog records
        lx = cont->get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
        ly = cont->get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        rx = cont->get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
        ry = cont->get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

        // Digital records
        l1 = cont->get_digital(pros::E_CONTROLLER_DIGITAL_R1);
        l2 = cont->get_digital(pros::E_CONTROLLER_DIGITAL_R2);
        r1 = cont->get_digital(pros::E_CONTROLLER_DIGITAL_L1);
        r2 = cont->get_digital(pros::E_CONTROLLER_DIGITAL_L2);
        a = cont->get_digital(pros::E_CONTROLLER_DIGITAL_A);
        b = cont->get_digital(pros::E_CONTROLLER_DIGITAL_B);
        x = cont->get_digital(pros::E_CONTROLLER_DIGITAL_X);
        y = cont->get_digital(pros::E_CONTROLLER_DIGITAL_Y);
    }

    std::string encode() {
        std::stringstream ss;
        ss << lx << "," << ly << "," << rx << "," << ry << ",";
        ss << l1 << "," << l2 << "," << r1 << "," << r2 << ",";
        ss << a << "," << b << "," << x << "," << y << std::endl;
        return ss.str();
    }

    void decode(std::string str) {
        std::stringstream ss(str);

        char temp;

        // Analog decode
        ss >> lx;
        ss >> temp;
        ss >> ly;
        ss >> temp;
        ss >> rx;
        ss >> temp;
        ss >> ry;
        ss >> temp;

        // Digital decode
        ss >> l1;
        ss >> temp;
        ss >> l2;
        ss >> temp;
        ss >> r1;
        ss >> temp;
        ss >> r2;
        ss >> temp;

        ss >> a;
        ss >> temp;
        ss >> b;
        ss >> temp;
        ss >> x;
        ss >> temp;
        ss >> y;
        ss >> temp;
    }

    void write_to_file() {
        std::ifstream file("usd/rec_01.txt");

        if(!file) {
            //std::cout << "No SD card insterted" << std::endl;
        } else {
            usd_file = fopen("/usd/rec_01.txt", "a");
            std::cout << encode();
            bool status = fputs(this->encode().c_str(), usd_file);
            if (status) {
                // Good status
            } else {
                // Bad status
            }

            fclose(usd_file);
        } 
    }

    void read_from_file() {
        char buf[1024]; // This just needs to be larger than the contents of the file
        bool status = fgets(buf, sizeof(buf), usd_file);
        if(status) {
            std::string s(buf);
            std::cout << s;
            decode(s);
        } else {
            std::cout << "File read error or EOF" << std::endl;
        }
        
    }

    ~VirtualController() {
        fclose(usd_file);
    }
};

#endif 