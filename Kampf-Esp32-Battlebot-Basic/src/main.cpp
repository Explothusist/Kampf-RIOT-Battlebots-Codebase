
#include <Arduino.h>
#include "Robot.h"

Robot m_robot{ Robot() }; // Bindings and init configured here

void setup() { // NO OTHER CODE GOES IN THIS FILE! Use Robot.cpp instead
    Serial.begin(115200);
    atmt::platform_println("Starting");

    m_robot.startLoop();
    
};

void loop() {

    m_robot.runLoop();

};
