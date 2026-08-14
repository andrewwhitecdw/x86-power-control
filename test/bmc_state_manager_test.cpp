#include <cstdio>
#include <fstream>
#include <string>

#include <gtest/gtest.h>

// Regression test for the sysfs bootstatus read falsely failing on EOF.
// Sysfs files often contain only the value with no trailing newline, so
// reaching EOF immediately after a successful formatted extraction is normal
// and must not throw.
TEST(BMCStateManager, SysfsReadWithoutNewlineDoesNotThrow)
{
    const std::string path = "/tmp/watchdog_bootstatus_test";

    {
        std::ofstream ofs(path);
        ASSERT_TRUE(ofs.good());
        ofs << "32"; // WDIOF_CARDRESET value, no trailing newline
    }

    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    uint64_t value = 0;
    file.open(path);
    ASSERT_TRUE(file.is_open());

    EXPECT_NO_THROW(file >> value);
    EXPECT_EQ(value, 32u);

    std::remove(path.c_str());
