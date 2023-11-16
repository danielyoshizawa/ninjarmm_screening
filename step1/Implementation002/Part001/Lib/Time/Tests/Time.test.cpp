#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

#include <Time.h>

TEST_CASE("Time Arithmetic library", "[Time]")
{
    Time time{"10:22"};
    SECTION("Parsing string to int")
    {
        REQUIRE(time.hour() == 10);
        REQUIRE(time.minute() == 22);
        REQUIRE_FALSE(time.hour() == 9);
        REQUIRE_FALSE(time.minute() == 12);
    }
    SECTION("Hours difference")
    {
        Time time2{"22:11"};
        // The difference between time2 and time should be
        // 11:49 (eleven hours and 49 minutes)
        Time result = time2 - time;
        REQUIRE(result.hour() == 11);
        REQUIRE(result.minute() == 49);
        // This should return a negative value
        Time result_negative = time - time2;
        REQUIRE(result_negative.hour() == -11);
        REQUIRE(result_negative.minute() == -49);
        // This should return 00:00
        Time result_zero = time - time;
        REQUIRE(result_zero.hour() == 0);
        REQUIRE(result_zero.minute() == 0);
    }
    SECTION("To string")
    {
        std::stringstream ss;
        ss << time;
        REQUIRE_THAT(time.toString(), Catch::Matchers::Equals("10:22"));
        REQUIRE_THAT(ss.str(), Catch::Matchers::Equals("10:22"));
        REQUIRE_THAT(ss.str(), !Catch::Matchers::Equals("10:23"));
    }
}