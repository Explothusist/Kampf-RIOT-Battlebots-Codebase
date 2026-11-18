
#include "ArmWeaponCommand.h"

ArmWeaponCommand::ArmWeaponCommand(kmpf::WeaponMotor* weapon_motor):
    atmt::Command(),
    m_weapon_motor{ weapon_motor }
{
    usesSubsystem(m_weapon_motor);
};
ArmWeaponCommand::ArmWeaponCommand(const ArmWeaponCommand& command):
    atmt::Command(command)
{
    m_weapon_motor = command.m_weapon_motor;
};
ArmWeaponCommand::~ArmWeaponCommand() {
    // Will run ~Command() after this is complete
};
atmt::Command* ArmWeaponCommand::cloneSelf() const {
    return new ArmWeaponCommand(m_weapon_motor);
};

void ArmWeaponCommand::initialize() {
    m_weapon_motor->armMotor();
};
void ArmWeaponCommand::execute() {

};
void ArmWeaponCommand::end(bool interrupted) {

};

bool ArmWeaponCommand::is_finished() {
    return true;
}