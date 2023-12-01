#include "pros/motors.h"
#include "pros/motors.hpp"
#include "pros/rotation.h"
#include "pros/rotation.hpp"
#include "cata.hpp"

pros::Motor cata(19, pros::E_MOTOR_GEARSET_36, true);
pros::Rotation cata_rot(11);


void catastop(){
    cata.move_velocity(0);
    cata.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void move_cata(int degrees, int velocity){
    int error = -2;
    cata.move_relative(degrees, velocity);
    if (cata.tare_position()==1){
        pros::delay(1);
    }
    while(!((cata.get_position() < (degrees + error)) && (cata.get_position() > (degrees - error)))){
        pros::delay(100);
        //master.rumble("-*-");
        //std::vector<double> positions = cata.get_positions();
        master.clear();
        master.print(0,0,"position: %f", cata.get_position());
        master.print(0,1,"target: %f", degrees+error);
        //std::cout<<positions[0];
    }
}


void reset_cata(){
    int limit = 7000;
    int target = 4840;
    // 4740 is the best angle when cata is loose 
    // Increasing means cata stops earlier, this will solve prefiring
    cata.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    while(cata_rot.get_position()>target){
        pros::delay(10);
        if (cata_rot.get_position()>limit){
            cata.move_velocity(200);
        }
        else{
            cata.move_velocity(70);
        }
        
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
            break;
        }
        master.rumble("- * -");
    }
    
    cata.brake();
    //pros::delay(250);
    //move_cata(-1*((target-cata_rot.get_position())/5), 15);
}
   void cata_move(int speed){
    cata.move_velocity(speed);
   }
