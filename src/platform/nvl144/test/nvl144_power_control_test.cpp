// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: Copyright OpenBMC Authors

#include "nvl144_power_control.hpp"

#include <gtest/gtest.h>

namespace power_control
{

TEST_F(NVL144PowerControlTest, HandleShutdownRequest_PowerCycleAlreadyOff)
{
    // Simulate power already off and a forceful power-cycle context.
    setSystemPowerOff(true);
    setAction(PowerAction::POWER_CYCLE);
    handleShutdownRequest(Event::powerOffRequest);
    EXPECT_EQ(getPowerState(), PowerState::waitForPowerCycleDelay);
    EXPECT_EQ(getAction(), PowerAction::POWER_CYCLE);
}

TEST_F(NVL144PowerControlTest, HandleShutdownRequest_GracefulPowerCycleAlreadyOff)
{
    // Simulate power already off and a graceful power-cycle context.
    setSystemPowerOff(true);
    setAction(PowerAction::GRACEFUL_POWER_CYCLE);
    handleShutdownRequest(Event::gracefulPowerOffRequest);
    EXPECT_EQ(getPowerState(), PowerState::waitForPowerCycleDelay);
    EXPECT_EQ(getAction(), PowerAction::GRACEFUL_POWER_CYCLE);
}

