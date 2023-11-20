#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

#include <Date.h>

TEST_CASE("Date Arithmetic library", "[Date]")
{
    SECTION("Parse")
    {
        Date date{"2023-11-09"};
        REQUIRE(date.year() == 2023);
        REQUIRE(date.month() == 11);
        REQUIRE(date.day() == 9);
    }
    SECTION("Exception")
    {
        REQUIRE_THROWS_AS(Date{"2023-11-31"}, std::invalid_argument);
        REQUIRE_NOTHROW(Date{"2023-11-30"});
    }
    SECTION("Difference")
    {
        Date date1{"2023-10-10"};
        Date date2{"2023-10-11"};
        REQUIRE((date1 - date1) == 0);
        REQUIRE((date2 - date1) == 1);
        REQUIRE((date1 - date2) == -1);
        Date date3{"2023-11-01"};
        REQUIRE((date3 - date1) == 22);
        Date date4{"2023-02-25"};
        Date date5{"2023-03-01"};
        REQUIRE((date5 - date4) == 4);
        Date date6{"2023-12-10"};
        Date date7{"2024-02-10"};
        REQUIRE((date7 - date6) == 62);
        REQUIRE((date6 - date7) == -62);
    }
}