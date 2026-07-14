
#ifndef Robot_
#define Robot_

// #include "Automat/automat.h"
#include "../Kampf/kampf.h"
#include "RobotContainer.h"

class Robot : public atmt::TimedRobot {
    public:
        Robot();
        ~Robot();

        void environmentInit() override;

        void robotInit() override;
        void robotPeriodic() override;
        void robotExit() override;
        
        void disabledInit() override;
        void disabledPeriodic() override;
        void disabledExit() override;
        
        void autonomousInit() override;
        void autonomousPeriodic() override;
        void autonomousExit() override;
        
        void teleopInit() override;
        void teleopPeriodic() override;
        void teleopExit() override;

    private:
        RobotContainer* m_bot_cont;
};

#endif