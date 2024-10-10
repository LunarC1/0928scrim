#pragma once

#include "api.h"

// Your motors, sensors, etc. should go here.  Below are examples

inline pros::Motor intake1(-6);
inline pros::Motor intake2(19);

// inline pros::Motor liftR(-5);
// inline pros::Motor liftL(7);

inline pros::adi::DigitalOut lift('D');
inline pros::adi::DigitalOut mogo('C');
// inline pros::adi::DigitalOut tilter('C');
inline pros::adi::DigitalOut stick('A');
inline pros::adi::DigitalOut redirect('B');

// inline pros::Motor intake(1);
// inline pros::adi::DigitalIn limit_switch('A');