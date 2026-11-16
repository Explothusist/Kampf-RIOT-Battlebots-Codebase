
#ifndef STORMBOT_CONTAINER_
#define STORMBOT_CONTAINER_

// #include "Automat/automat.h"
#include "../Kampf/kampf.h"
#include "Constants.h"

class RobotContainer {
    public:
        RobotContainer();
        ~RobotContainer();

        void configure_auto_bindings();
        void configure_bindings();

        // atmt::Command* getAutonomousCommand();
        static atmt::Command* getAutonomousCommand(int indicator, void* robot_container);
        static int getWhichAutonomousRoutine(void* robot_container);

        // Custom methods here
        static atmt::JoystickState getJoystickStateFromGPIO();
        static double getBatteryPercentFromGPIO();

        std::string m_receiver_name = "Gesundheit";
        
        // Declare Subsystems here (as public)
        atmt::Joystick* m_controller;
        atmt::ESPNowHandler* m_espnow_handler;
        
        kmpf::ESPNowReceiver* m_receiver;

    private:
};


#endif