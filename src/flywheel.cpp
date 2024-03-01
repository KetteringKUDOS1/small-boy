#include "pros/motors.h"
#include "pros/motors.hpp"

pros::Motor flywheel(2, pros::E_MOTOR_GEARSET_06, true);

void start_wheel(){
    flywheel.move_velocity(600);
}

void stop_wheel(){
    flywheel.brake();
}