
#include "Robot.h"
// #include "Automat/automat.h"
#include "Constants.h"
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
    registerSubsystem(m_bot_cont->m_receiver);
    registerSubsystem(m_bot_cont->m_drivetrain);
    registerSubsystem(m_bot_cont->m_weapon);

    // Add all Joysticks
    // All Joysticks MUST be registered for events to trigger!
    registerJoystick(m_bot_cont->m_controller);

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
};
void Robot::robotPeriodic() { // Runs continuously regardless of mode
    // atmt::platform_print("Robot Periodic...     ");
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