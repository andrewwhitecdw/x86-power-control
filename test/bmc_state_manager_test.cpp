// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: Copyright OpenBMC Authors

#include <gtest/gtest.h>

#include <cstdio>
#include <fstream>

TEST(BMCStateManagerTest, BootstatusReadWithoutEofbitDoesNotThrow)
{
    const char* testPath = "/tmp/test_bootstatus";

    auto writeAndRead = [testPath](const char* content, uint64_t expected) {
        std::remove(testPath);

        // Mimic a sysfs-style file containing a single integer
        {
            std::ofstream out(testPath);
            out << content;
        }

        uint64_t bootReason = 0;
        std::ifstream file;

        // Same exception mask used by discoverLastRebootCause
        file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        file.open(testPath);
        EXPECT_NO_THROW(file >> bootReason);
        EXPECT_EQ(bootReason, expected);

        std::remove(testPath);
    };

    // EOF immediately after the value
    writeAndRead("32", 32);

    // Newline before EOF (also common for sysfs files)
    writeAndRead("32\n", 32);
}
