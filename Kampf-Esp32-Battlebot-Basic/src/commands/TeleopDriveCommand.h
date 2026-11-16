
#ifndef Kampf_Battlebot_TeleopDriveCommand_
#define Kampf_Battlebot_TeleopDriveCommand_

#include "../Kampf/kampf.h"

class TeleopDriveCommand : public atmt::Command {
    public:
        TeleopDriveCommand(kmpf::Drivetrain* drivetrain, atmt::Joystick* controller); // Put subsystems as parameters
        TeleopDriveCommand(TeleopDriveCommand& command); // Copy constructor
        ~TeleopDriveCommand();
        atmt::Command* cloneSelf() const override;

        void initialize() override; // User-made
        void execute() override; // User-made
        void end(bool interrupted) override; // User-made
        bool is_finished() override; // User-made
        
    private:
        kmpf::Drivetrain* m_drivetrain;
        atmt::Joystick* m_controller;
};

#endif