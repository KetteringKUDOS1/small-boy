#include "pros/motors.h"
#include "pros/motors.hpp"
#include "pros/rotation.h"
#include "pros/rotation.hpp"
#include "cata.hpp"

pros::Motor intake(18, pros::E_MOTOR_GEARSET_36, true);


void intakein(int speed){
    intake.move_velocity(speed);
}

void intakeout(int speed){
    intake.move_velocity(-speed);
}