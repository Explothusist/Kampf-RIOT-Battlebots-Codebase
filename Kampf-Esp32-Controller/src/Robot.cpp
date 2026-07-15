
#include "Robot.h"
// #include "Automat/automat.h"
#include "Constants.h"
#include "utils/U8g2_utils.h"
#include "kampf.h"

Robot::Robot():
    atmt::TimedRobot(consts::robot::AutonomousLength), // Set Autonomous length here
    m_bot_cont{ new RobotContainer() } // There are important architectural reasons for RobotContainer, but they are too long to explain here
{

};
Robot::~Robot() {
    delete m_bot_cont;
    m_bot_cont = nullptr;
};

void Robot::environmentInit() { // Runs once before anything else
    atmt::platform_println("Environment Init!");
    
    // Register all Subsystems
    // All Subsystems MUST be registered for periodics to run and for commands on those subsystems to run!
    registerSubsystem(m_bot_cont->m_transmitter);

    // Add all Joysticks
    // All Joysticks MUST be registered for events to trigger!

    // Add SerialReaders/HTTPServers (if applicable)
    // Add Heartbeats/HeartbeatMakers (if applicable)
    registerESPNowHandler(m_bot_cont->m_espnow_handler);
    
    // Set up Autonomous (Do not edit unless you understand what you are doing)
    setAutonomousCommandGetter(RobotContainer::getAutonomousCommand, RobotContainer::getWhichAutonomousRoutine, m_bot_cont);

    // Configure bindings (Do not edit unless you understand what you are doing)
    m_bot_cont->configure_auto_bindings();
    m_bot_cont->configure_bindings();
};

void Robot::robotInit() { // Runs once after the command-based environment has been set up
    atmt::platform_print("Robot Init!           ");

    u8g2::initializeU8G2();

    pinMode(kmpf::consts::Controller::GPIO::k_LeftTrigger, INPUT);
    pinMode(kmpf::consts::Controller::GPIO::k_RightTrigger, INPUT);
    pinMode(kmpf::consts::Controller::GPIO::k_BottomButton, INPUT);
    pinMode(kmpf::consts::Controller::GPIO::k_TopButton, INPUT);

    pinMode(kmpf::consts::Controller::GPIO::k_AxisLX, INPUT);
    pinMode(kmpf::consts::Controller::GPIO::k_AxisLY, INPUT);
    pinMode(kmpf::consts::Controller::GPIO::k_AxisRX, INPUT);
    pinMode(kmpf::consts::Controller::GPIO::k_AxisRY, INPUT);

    u8g2::drawRIOTLogo();
    m_bot_cont->m_initialized_timestamp = atmt::getSystemTime();
};
void Robot::robotPeriodic() { // Runs continuously regardless of mode
    // atmt::platform_print("Robot Periodic...     ");

    if (m_bot_cont->m_initialized_timestamp.getTimeDifference(atmt::getSystemTime()) < kmpf::consts::Controller::k_DisplayLogoTimeSec) {
        return; // Logo for two seconds
    }

    if (m_bot_cont->m_transmitter->isConnected()) {
        if (m_bot_cont->m_draw_loop_timeout.checkTimeout()) {
            double battery_percent = RobotContainer::getBatteryPercentFromGPIO();
            u8g2::printMainMenu(RobotContainer::getJoystickStateFromGPIO(), true, static_cast<int>((battery_percent * 4) - 1));
        }
        return; // Else handled by transmitter periodic
    }

    if (m_bot_cont->m_transmitter->isAttemptingConnection()) {
        if (m_bot_cont->m_draw_loop_timeout.checkTimeout()) {
            u8g2::drawConfirmReceiver(m_bot_cont->m_espnow_handler->GetTargetMACAddress());
        }
        return; // Else handled by transmitter periodic
    }

    if (m_bot_cont->m_draw_loop_timeout.checkTimeout()) {
        const std::vector<kmpf::KnownReceiver> &known_receivers = m_bot_cont->m_transmitter->getKnownReceivers();
        atmt::JoystickState state = RobotContainer::getJoystickStateFromGPIO();

        
        if (atmt::getJoystickStateButton(state, atmt::L1Button)) {
            if (!known_receivers.empty() && m_bot_cont->m_selected_mac_address < known_receivers.size()) {
                m_bot_cont->m_transmitter->pairWithReceiver(known_receivers[m_bot_cont->m_selected_mac_address]);
            }
        }
        if (atmt::getJoystickStateButton(state, atmt::BButton) && !m_bot_cont->m_last_scroll_button_state) {
            m_bot_cont->m_selected_mac_address += 1;
            if (m_bot_cont->m_mac_address_scroll <= m_bot_cont->m_selected_mac_address - kmpf::consts::Controller::k_MACsDrawnPerScreen) {
                m_bot_cont->m_mac_address_scroll += 1;
            }
            m_bot_cont->m_last_scroll_button_state = true;
        }else if (atmt::getJoystickStateButton(state, atmt::AButton) && !m_bot_cont->m_last_scroll_button_state) {
            m_bot_cont->m_selected_mac_address -= 1;
            if (m_bot_cont->m_selected_mac_address < 0) {
                m_bot_cont->m_selected_mac_address = known_receivers.size() - 1;
                m_bot_cont->m_mac_address_scroll = known_receivers.size() - kmpf::consts::Controller::k_MACsDrawnPerScreen;
            }
            m_bot_cont->m_last_scroll_button_state = true;
            if (m_bot_cont->m_mac_address_scroll > m_bot_cont->m_selected_mac_address) {
                m_bot_cont->m_mac_address_scroll -= 1;
            }
        }else {
            m_bot_cont->m_last_scroll_button_state = false;
        }

        if (m_bot_cont->m_selected_mac_address >= known_receivers.size()) {
            m_bot_cont->m_selected_mac_address = 0;
            m_bot_cont->m_mac_address_scroll = 0;
        }


        u8g2::drawSelectReceiver(known_receivers, m_bot_cont->m_selected_mac_address, m_bot_cont->m_mac_address_scroll);
    }
};
void Robot::robotExit() { // Runs once when the the robot is reset or powered off
    atmt::platform_print("Robot Exit            ");
};

void Robot::disabledInit() { // Runs once whenever the robot enters the Disabled mode
    atmt::platform_println("Disabled Init!");
};
void Robot::disabledPeriodic() { // Runs continuously whenever the robot is in the Disabled mode
    // atmt::platform_println("Disabled Periodic...");
};
void Robot::disabledExit() { // Runs once whenever the robot leaves the Disabled mode
    atmt::platform_println("Disabled Exit");
};

void Robot::autonomousInit() { // Runs once whenever the robot enters the Autonomous mode
    atmt::platform_println("Autonomous Init!");
};
void Robot::autonomousPeriodic() { // Runs continuously whenever the robot is in the Autonomous mode
    // atmt::platform_println("Autonomous Periodic...");
};
void Robot::autonomousExit() { // Runs once whenever the robot leaves the Autonomous mode
    atmt::platform_println("Autonomous Exit");
};

void Robot::teleopInit() { // Runs once whenever the robot enters the Teleop mode
    atmt::platform_println("Teleop Init!");
};
void Robot::teleopPeriodic() { // Runs continuously whenever the robot is in the Teleop mode
    // atmt::platform_println("Teleop Periodic...");
};
void Robot::teleopExit() { // Runs once whenever the robot leaves the Teleop mode
    atmt::platform_println("Teleop Exit");
};