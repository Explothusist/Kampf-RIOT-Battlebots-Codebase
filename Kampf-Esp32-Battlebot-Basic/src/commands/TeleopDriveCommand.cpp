
#include "TeleopDriveCommand.h"

TeleopDriveCommand::TeleopDriveCommand(kmpf::Drivetrain* drivetrain, atmt::Joystick* controller):
    atmt::Command(),
    m_drivetrain{ drivetrain },
    m_controller{ controller }
{
    usesSubsystem(m_drivetrain);
};
TeleopDriveCommand::TeleopDriveCommand(TeleopDriveCommand& command):
    atmt::Command(command)
{
    m_drivetrain = command.m_drivetrain;
    m_controller = command.m_controller;
};
TeleopDriveCommand::~TeleopDriveCommand() {
    // Will run ~Command() after this is complete
};
atmt::Command* TeleopDriveCommand::cloneSelf() const {
    return new TeleopDriveCommand(m_drivetrain, m_controller);
};

void TeleopDriveCommand::initialize() {

};
void TeleopDriveCommand::execute() {
    atmt::platform_printf(
        "Driving: %f, %f\n",
        m_controller->getRawAxis(atmt::LXAxis) * 100,
        m_controller->getRawAxis(atmt::LYAxis) * 100
    );
};
void TeleopDriveCommand::end(bool interrupted) {

};
bool TeleopDriveCommand::is_finished() {
    return false;
};