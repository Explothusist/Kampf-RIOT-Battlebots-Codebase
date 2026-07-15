
#include "RobotContainer.h"

RobotContainer::RobotContainer():
    m_espnow_handler{ new atmt::ESPNowHandler(random()) },
    m_transmitter{ new kmpf::ESPNowTransmitter(m_espnow_handler, RobotContainer::getJoystickStateFromGPIO) },
    m_initialized_timestamp{ 0 },
    m_draw_loop_timeout{ kmpf::consts::Controller::k_DrawScreenDelaySec },
    m_selected_mac_address{ 0 },
    m_mac_address_scroll{ 0 },
    m_last_scroll_button_state{ false }
{

};
RobotContainer::~RobotContainer() { // Subsystems deleted by atmt::TimedRobot

};


void RobotContainer::configure_auto_bindings() {
    
};
void RobotContainer::configure_bindings() {
    
};

atmt::JoystickState RobotContainer::getJoystickStateFromGPIO() {
    atmt::JoystickState new_state;

    atmt::setJoystickStateButton(new_state, atmt::AButton, digitalRead(kmpf::consts::Controller::GPIO::k_TopButton));
    atmt::setJoystickStateButton(new_state, atmt::BButton, digitalRead(kmpf::consts::Controller::GPIO::k_BottomButton));
    atmt::setJoystickStateButton(new_state, atmt::L1Button, digitalRead(kmpf::consts::Controller::GPIO::k_LeftTrigger));
    atmt::setJoystickStateButton(new_state, atmt::R1Button, digitalRead(kmpf::consts::Controller::GPIO::k_RightTrigger));

    new_state.axes[atmt::LXAxis] = analogRead(kmpf::consts::Controller::GPIO::k_AxisLX);
    new_state.axes[atmt::LYAxis] = analogRead(kmpf::consts::Controller::GPIO::k_AxisLY);
    new_state.axes[atmt::RXAxis] = analogRead(kmpf::consts::Controller::GPIO::k_AxisRX);
    new_state.axes[atmt::RYAxis] = analogRead(kmpf::consts::Controller::GPIO::k_AxisRY);

    new_state.axis_range[0] = 0;
    new_state.axis_range[1] = 4096;

    return new_state;
};

atmt::JoystickState RobotContainer::getJoystickStateFromGPIO() {
    atmt::JoystickState new_state;

    atmt::setJoystickStateButton(new_state, atmt::AButton, digitalRead(kmpf::consts::Controller::GPIO::k_TopButton));
    atmt::setJoystickStateButton(new_state, atmt::BButton, digitalRead(kmpf::consts::Controller::GPIO::k_BottomButton));
    atmt::setJoystickStateButton(new_state, atmt::L1Button, digitalRead(kmpf::consts::Controller::GPIO::k_LeftTrigger));
    atmt::setJoystickStateButton(new_state, atmt::R1Button, digitalRead(kmpf::consts::Controller::GPIO::k_RightTrigger));

    new_state.axes[atmt::LXAxis] = analogRead(kmpf::consts::Controller::GPIO::k_AxisLX);
    new_state.axes[atmt::LYAxis] = analogRead(kmpf::consts::Controller::GPIO::k_AxisLY);
    new_state.axes[atmt::RXAxis] = analogRead(kmpf::consts::Controller::GPIO::k_AxisRX);
    new_state.axes[atmt::RYAxis] = analogRead(kmpf::consts::Controller::GPIO::k_AxisRY);

    new_state.axis_range[0] = 0;
    new_state.axis_range[1] = 4096;

    return new_state;
};
double RobotContainer::getBatteryPercentFromGPIO() {
    return analogRead(kmpf::consts::Controller::GPIO::k_AnalogBatteryPower) / 255;
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
