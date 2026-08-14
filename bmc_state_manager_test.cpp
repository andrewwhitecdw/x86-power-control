// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: Copyright OpenBMC Authors

#include <gtest/gtest.h>

#include <cstdint>
#include <filesystem>
#include <fstream>

// Regression test for the bootstatus read in discoverLastRebootCause().
// A sysfs file that contains only a single integer followed by EOF must
// not throw when eofbit is not enabled in the ifstream exception mask.
TEST(BMCStateManager, ReadBootstatusWithoutEofThrow)
{
    auto tmp = std::filesystem::temp_directory_path() / "bootstatus_test";
    constexpr uint64_t expected = 16; // WDIOF_CARDRESET
    {
        std::ofstream ofs(tmp);
        ofs << expected;
    }

    uint64_t bootReason = 0;
    std::ifstream file;
    // Match the production exception mask after the fix: failbit and
    // badbit are enabled, but eofbit is not, so a normal EOF after the
    // value does not cause an exception.
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    file.open(tmp);
    ASSERT_NO_THROW(file >> bootReason);
    EXPECT_EQ(bootReason, expected);

    std::filesystem::remove(tmp);
}
