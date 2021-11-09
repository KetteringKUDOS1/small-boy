#include "main.h"

#include <iostream>
#include <tuple>

// Chassis constructor
drive chassis (
  // Left Chassis Ports (negative port will reverse it!)
  {-11, -5, -7},

  // Right Chassis Ports (negative port will reverse it!)
  {3, 2, 17},

  // IMU Port
  18,

  // Wheel Diameter (Remember, 4" wheels are actually 4.125!)
  3.25,

  // Cartridge RPM
  600,

  // External Gear Ratio
  1.66666666667
);



/**
 * Disables all tasks.
 *
 * This runs during disabled and initialize to turn off all user created tasks.
 */

void disable_all_tasks()
{
  chassis.drive_pid.suspend();
  chassis.turn_pid. suspend();
  chassis.swing_pid.suspend();
}



/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {

  ez::print_ez_template(); // Print our branding over your terminal :D
  pros::lcd::initialize();
  pros::delay(500); // Stop the user from doing anything while legacy ports configure.

  // Disable tasks
  disable_all_tasks();

  // Check if SD card is pluged in
  if (!ez::IS_SD_CARD) printf("No SD Card Found!\n");

  // Configure your chassis controls
  chassis.init_curve_sd();
  chassis.toggle_modify_curve_with_controllerr(true);
  chassis.set_active_brake(0.1);

  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // chassis.set_left_curve_buttons (pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT);
  // chassis.set_right_curve_buttons(pros::E_CONTROLLER_DIGITAL_Y,    pros::E_CONTROLLER_DIGITAL_A);

  // Autonomous Selector using LLEMMU
  ez::as::autoSelector.AddAutons({
    Auton("Autonomous 1", auto1),
    Auton("Autonomous 2", auto2),
    Auton("Autonomous 3", auto3),
  });

  //pros::delay(100);

  //printf("\n");

  // Initialize auto selector and LLEMU
  ez::as::init_auton_selector();
  printf("autoselector init\n");


  // Callbacks for auto selector
  ez::as::autoSelector.PrintSelectedAuto();
  printf("autoselector printed\n");
  pros::lcd::register_btn0_cb(ez::as::page_down);
  pros::lcd::register_btn2_cb(ez::as::page_up);

  // Calibrate IMU
  if (!chassis.imu_calibrate())
    pros::lcd::set_text(7, "IMU failed to calibrate!");
}



/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
  disable_all_tasks();
}



/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
  disable_all_tasks();
}



/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  chassis.reset_gyro();
  chassis.reset_drive_sensor();
  chassis.set_drive_brake(MOTOR_BRAKE_HOLD);

  ez::as::autoSelector.CallSelectedAuto();
}



/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
  disable_all_tasks();
  chassis.reset_drive_sensor();

  // This is preference to what you like to drive on.
  chassis.set_drive_brake(MOTOR_BRAKE_COAST);

  while (true) {

    chassis.tank(); // Tank control
    // chassis.arcade_standard(ez::SPLIT); // Standard split arcade
    // chassis.arcade_standard(ez::SINGLE); // Standard single arcade
    // chassis.arcade_flipped(ez::SPLIT); // Flipped split arcade
    // chassis.arcade_flipped(ez::SINGLE); // Flipped single arcade

    // . . .
    // Put more user control code here!
    // . . .

    pros::delay(ez::util::DELAY_TIME); // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
  }
}
