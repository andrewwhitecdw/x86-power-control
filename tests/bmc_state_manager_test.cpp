// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: Copyright OpenBMC Authors

#include <gtest/gtest.h>

#include <cstdio>
#include <fstream>

TEST(WatchdogBootstatus, EofAfterValueDoesNotThrow)
{
    // Simulate a sysfs file that contains a value and then immediately ends.
    const char* path = "/tmp/phosphor_state_manager_bootstatus_test";
    {
        std::ofstream out(path);
        out << "32\n";
    }

    std::ifstream file(path);
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    uint64_t value = 0;
    EXPECT_NO_THROW(file >> value);
    EXPECT_EQ(value, 32u);

    std::remove(path);
}
