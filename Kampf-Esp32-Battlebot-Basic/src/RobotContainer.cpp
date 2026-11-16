
#include "RobotContainer.h"

RobotContainer::RobotContainer():
    m_controller{ new atmt::Joystick(atmt::PollMode_Manual) },
    m_espnow_handler{ new atmt::ESPNowHandler(random()) },
    m_receiver{ new kmpf::ESPNowReceiver(m_receiver_name, m_controller, m_espnow_handler) }
{

};
RobotContainer::~RobotContainer() { // Subsystems deleted by atmt::TimedRobot

};


void RobotContainer::configure_auto_bindings() {
    
};
void RobotContainer::configure_bindings() {
    
};

atmt::Command* RobotContainer::getAutonomousCommand(int indicator, void* robot_container) {
    RobotContainer* self = static_cast<RobotContainer*>(robot_container);
    switch (indicator) {
        case 0:
            return new atmt::EmptyCommand();

        // Add more case statements to create more routines
        
        default:
            return new atmt::EmptyCommand();
    }
};
int RobotContainer::getWhichAutonomousRoutine(void* robot_container) {
    RobotContainer* self = static_cast<RobotContainer*>(robot_container);
    return 0; // Change this value to select which autonomous routine is run
};
