#pragma once

#include "api.h"

// Your motors, sensors, etc. should go here.  Below are examples

inline pros::Motor intake1(-5);
inline pros::Motor intake2(7);

// inline pros::Motor liftR(-5);
// inline pros::Motor liftL(7);

inline pros::adi::DigitalOut lift('E');
inline pros::adi::DigitalOut mogo('F');
// inline pros::adi::DigitalOut tilter('C');
inline pros::adi::DigitalOut stick('H');
inline pros::adi::DigitalOut redirect('G');

// inline pros::Motor intake(1);
// inline pros::adi::DigitalIn limit_switch('A');

// rotation sensor: port 20