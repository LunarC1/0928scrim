#include "main.h"

/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// pros::Controller master(pros::E_CONTROLLER_MASTER);
																				
pros::Imu imu(18);

// Chassis constructor
ez::Drive chassis(
    // These are your drive motors, the first motor is used for sensing!
    {-8, -9, 10},  // Left Chassis Ports (negative port will reverse it!)
    {-2, 3, 4},  // Right Chassis Ports (negative port will reverse it!)

    18,     // IMU Port
    2.75,  // Wheel Diameter (Remember, 4" wheels without screw holes are actually 4.125!)
    480);   // Wheel RPM

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  // Print our branding over your terminal :D
  ez::ez_template_print();

  pros::delay(500);  // Stop the user from doing anything while legacy ports configure

  // Configure your chassis controls
  chassis.opcontrol_curve_buttons_toggle(true);  // Enables modifying the controller curve with buttons on the joysticks
  chassis.opcontrol_drive_activebrake_set(0);    // Sets the active brake kP. We recommend ~2.  0 will disable.
  chassis.opcontrol_curve_default_set(0, 0);     // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)

  // Set the drive to your own constants from autons.cpp!
  default_constants();

  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // chassis.opcontrol_curve_buttons_left_set(pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT);  // If using tank, only the left side is used.
  // chassis.opcontrol_curve_buttons_right_set(pros::E_CONTROLLER_DIGITAL_Y, pros::E_CONTROLLER_DIGITAL_A);

  // Autonomous Selector using LLEMU
  ez::as::auton_selector.autons_add({
      Auton("PosRed:\nMogo side", posRed),
      Auton("NegRed:\nRing scoring side", negRed),
      Auton("NegBlue:\nRing scoring side", negBlue),
      // Auton("Drive and Turn\n\nDrive forward, turn, come back. ", drive_and_turn),
      // Auton("Drive and Turn\n\nSlow down during drive.", wait_until_change_speed),
      // Auton("Swing Example\n\nSwing in an 'S' curve", swing_example),
      // Auton("Motion Chaining\n\nDrive forward, turn, and come back, but blend everything together :D", motion_chaining),
      // Auton("Combine all 3 movements", combining_movements),
      // Auton("Interference\n\nAfter driving forward, robot performs differently if interfered or not.", interfered_example),
  });

  // Initialize chassis and auton selector
  chassis.initialize();
  ez::as::initialize();
  master.rumble(".");
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
  // . . .
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
  // . . .
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
  chassis.pid_targets_reset();                // Resets PID targets to 0
  chassis.drive_imu_reset();                  // Reset gyro position to 0
  chassis.drive_sensor_reset();               // Reset drive sensors to 0
  chassis.drive_brake_set(MOTOR_BRAKE_HOLD);  // Set motors to hold.  This helps autonomous consistency

  // drive_example();
  // turn_example();
  // negRed();
  

  ez::as::auton_selector.selected_auton_call();  // Calls selected auton from autonomous selector
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
  // This is preference to what you like to drive on
  pros::motor_brake_mode_e_t driver_preference_brake = MOTOR_BRAKE_COAST;

  chassis.drive_brake_set(driver_preference_brake);

  bool mogoc = false;
  // bool tiltc = false;
  bool stickc = false;
  bool redirectc = false;
  bool liftc = false;
  // int leftY, rightX;
  while (true) {
    // leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y); // Input from Axis 3
		// rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X); // Input from Axis 1

    

    // // PID Tuner
    // // After you find values that you're happy with, you'll have to set them in auton.cpp
    // if (!pros::competition::is_connected()) {
    //   // Enable / Disable PID Tuner
    //   //  When enabled:
    //   //  * use A and Y to increment / decrement the constants
    //   //  * use the arrow keys to navigate the constants
    //   if (master.get_digital_new_press(DIGITAL_X))
    //     chassis.pid_tuner_toggle();

    //   // Trigger the selected autonomous routine
    //   if (master.get_digital(DIGITAL_B) && master.get_digital(DIGITAL_DOWN)) {
    //     // autonomous();
    //     chassis.pid_drive_set(24_in, 100);
    //     chassis.pid_wait();

    //     chassis.pid_drive_set(-24_in, 100);
    //     chassis.pid_wait();
    //     // drive_example();
    //     chassis.drive_brake_set(driver_preference_brake);
    //   }

    //   chassis.pid_tuner_iterate();  // Allow PID Tuner to iterate
    // }


    // chassis.opcontrol_drive_activebrake_set(2.0);
    // chassis.opcontrol_tank();  // Tank control
    chassis.opcontrol_arcade_standard(ez::SPLIT);   // Standard split arcade
    // chassis.opcontrol_arcade_standard(ez::SINGLE);  // Standard single arcade
    // chassis.opcontrol_arcade_flipped(ez::SPLIT);    // Flipped split arcade
    // chassis.opcontrol_arcade_flipped(ez::SINGLE);   // Flipped single arcade

    // . . .
    // Put more user control code here!
    // . . .

    if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
      mogoc = !mogoc; 
      // tiltc = !tiltc; 
      mogo.set_value(mogoc);
      // pros::Task::delay(130);
      // tilter.set_value(tiltc);
    }
		// Mogo tilter + redirect mech
		if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
      redirectc = !redirectc; 
      redirect.set_value(redirectc);
    }
    if(redirectc == false){
      if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) { intake1.move(127); intake2.move(127);}
      else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) { intake1.move(-127); intake2.move(-127);}
      else { intake1.move(0); intake2.move(0); }
    }
    else if(redirectc == true){
      if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) { intake1.move(127); intake2.move(127); }
      else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) { intake1.move(-127); intake2.move(-127); }
      else { intake1.move(0); intake2.move(0); }
    }
    if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) {
      stickc = !stickc; 
      stick.set_value(stickc);
    }

		// Wall Stakes Motor
    if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
      liftc = !liftc; 
      lift.set_value(liftc);
    } 
		// if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) { liftL.move(95); liftR.move(95); }
		// else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) { liftL.move(-50); liftR.move(-50); }
		// else { liftL.set_brake_mode_all(pros::v5::MotorBrake::hold); liftR.set_brake_mode_all(pros::v5::MotorBrake::hold); liftL.brake(); liftR.brake();}

    pros::delay(ez::util::DELAY_TIME);  // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
  }
}