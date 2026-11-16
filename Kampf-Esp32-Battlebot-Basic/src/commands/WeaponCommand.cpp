
#include "WeaponCommand.h"
#include <Arduino.h>
#include <cmath>

WeaponCommand::WeaponCommand(kmpf::WeaponMotor* weapon_motor, double percent_power):
    atmt::Command(),
    m_weapon_motor{ weapon_motor },
    m_percent_power{ percent_power }
{
    usesSubsystem(m_weapon_motor);
};
WeaponCommand::WeaponCommand(const WeaponCommand& command):
    atmt::Command(command)
{
    m_weapon_motor = command.m_weapon_motor;
    m_percent_power = command.m_percent_power;
};
WeaponCommand::~WeaponCommand() {
    // Will run ~Command() after this is complete
};
atmt::Command* WeaponCommand::cloneSelf() const {
    return new WeaponCommand(m_weapon_motor, m_percent_power);
};

void WeaponCommand::initialize() {
    atmt::platform_printf("WEAPON BEGUN$$$$$$$$$$$$$$$$$$$$$$$\n");
};
void WeaponCommand::execute() {
    atmt::platform_printf("Running Weapon!!!!!!\n");
};
void WeaponCommand::end(bool interrupted) {
    
};

bool WeaponCommand::is_finished() {
    return false;
}