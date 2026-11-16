
#ifndef Kampf_Battlebot_WeaponCommand_
#define Kampf_Battlebot_WeaponCommand_

#include "../Kampf/kampf.h"

class WeaponCommand : public atmt::Command { // Add more functionality to this, but this is a basic framework
    public:
        WeaponCommand(kmpf::WeaponMotor* weapon_motor, double percent_power); // Put subsystems as parameters
        WeaponCommand(const WeaponCommand& command); // Copy constructor
        ~WeaponCommand();
        atmt::Command* cloneSelf() const override;

        void initialize() override; // User-made
        void execute() override; // User-made
        void end(bool interrupted) override; // User-made
        bool is_finished() override; // User-made
        
    private:
        kmpf::WeaponMotor* m_weapon_motor;
        double m_percent_power;
};

#endif