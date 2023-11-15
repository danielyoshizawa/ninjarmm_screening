#include <catch2/catch_test_macros.hpp>

#include <Validator.h>

TEST_CASE("Matchs pattern", "[Validator]")
{
    Validator validator;
    SECTION("Time Pattern (hh:mm)")
    {
        // Hour
        REQUIRE(validator.is_time("09:10"));
        REQUIRE(validator.is_time("9:10"));
        REQUIRE(validator.is_time("09:10"));
        REQUIRE(validator.is_time("00:00"));
        REQUIRE_FALSE(validator.is_time("24:00"));
        REQUIRE_FALSE(validator.is_time("aa:01"));
        REQUIRE_FALSE(validator.is_time("123:01"));
        // Minute
        REQUIRE(validator.is_time("09:1"));
        REQUIRE(validator.is_time("09:59"));
        REQUIRE(validator.is_time("09:30"));
        REQUIRE(validator.is_time("09:0"));
        REQUIRE_FALSE(validator.is_time("09:60"));
        REQUIRE_FALSE(validator.is_time("09:a1"));
        REQUIRE_FALSE(validator.is_time("12:001"));
    }
    SECTION("Date Pattern (yyyy-mm-dd)")
    {
        // Year
        REQUIRE(validator.is_date("2023-1-11"));
        REQUIRE(validator.is_date("1997-1-11"));
        REQUIRE_FALSE(validator.is_date("202-1-11"));
        REQUIRE_FALSE(validator.is_date("1-1-2023"));
        // Month
        REQUIRE(validator.is_date("2023-1-11"));
        REQUIRE(validator.is_date("2023-12-11"));
        REQUIRE_FALSE(validator.is_date("2023-0-11"));
        REQUIRE_FALSE(validator.is_date("2023-13-11"));
        // Day
        REQUIRE(validator.is_date("2023-1-1"));
        REQUIRE(validator.is_date("2023-12-31"));
        REQUIRE_FALSE(validator.is_date("2023-1-0"));
        REQUIRE_FALSE(validator.is_date("2023-1-32"));
    }
}