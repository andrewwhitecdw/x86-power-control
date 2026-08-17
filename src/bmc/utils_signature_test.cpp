#include "utils.hpp"

#include <sdbusplus/bus.hpp>

#include <gtest/gtest.h>

#include <string>
#include <type_traits>

namespace
{
using ServiceGetter = std::string (*)(sdbusplus::bus_t&, const std::string&,
                                      const std::string&);

TEST(UtilsSignature, GetServiceTakesConstStringReferences)
{
    static_assert(
        std::is_same_v<
            decltype(&phosphor::state::manager::utils::getService),
            ServiceGetter>,
        "getService must take const string references");
}
} // namespace
