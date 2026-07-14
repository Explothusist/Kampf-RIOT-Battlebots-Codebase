
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

        // Declare Subsystems here (as public)
        atmt::ESPNowHandler* m_espnow_handler;
        
        kmpf::ESPNowTransmitter* m_transmitter;

        atmt::Timestamp m_initialized_timestamp;
        atmt::TimeoutManager m_draw_loop_timeout;
        int m_selected_mac_address;
        int m_mac_address_scroll;
        bool m_last_scroll_button_state;
    private:
};


#endif