#ifndef _SELECTION_HPP_
#define _SELECTION_HPP_    
#pragma once

#include <string>

//selector configuration
#define HUE 360 
#define DEFAULT 1
#define AUTONS "Near AWP", "Near Elims", "Far AWP", "Far Elims"

namespace selector
{
extern int auton;
const char *x[] = {AUTONS, ""};

void init(int hue = HUE, int default_auton = DEFAULT, const char **autons = x);
}

#endif