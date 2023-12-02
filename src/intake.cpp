#include "pros/motors.h"
#include "pros/motors.hpp"
#include "pros/rotation.h"
#include "pros/rotation.hpp"
#include "intake.hpp"

pros::Motor intake_motor(20, pros::E_MOTOR_GEARSET_06, true);


void intakein(int speed){
    intake_motor.move_velocity(-speed);
}

void intakeout(int speed){
    intake_motor.move_velocity(speed);
}

void intakestop(){
    intake_motor.move_velocity(0);
}