
#ifndef Kampf_Battlebot_ArmWeaponCommand_
#define Kampf_Battlebot_ArmWeaponCommand_

#include "../Kampf/kampf.h"

class ArmWeaponCommand : public atmt::Command { // Add more functionality to this, but this is a basic framework
    public:
        ArmWeaponCommand(kmpf::WeaponMotor* weapon_motor); // Put subsystems as parameters
        ArmWeaponCommand(const ArmWeaponCommand& command); // Copy constructor
        ~ArmWeaponCommand();
        atmt::Command* cloneSelf() const override;

        void initialize() override; // User-made
        void execute() override; // User-made
        void end(bool interrupted) override; // User-made
        bool is_finished() override; // User-made
        
    private:
        kmpf::WeaponMotor* m_weapon_motor;
};

#endif