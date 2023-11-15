#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <Clock.h>

TEST_CASE("Testing register and historic", "[Clock]")
{
    Clock<std::string, std::string, std::string, std::string, std::string> ck;
    ck.Register(1, "startTime0", "endTime0", "startDate0", "endDate0", "nature0");
    ck.Register(1, "startTime1", "endTime1", "startDate1", "endDate1", "nature1");
    ck.Register(1, "startTime2", "endTime2", "startDate2", "endDate2", "nature2");
    ck.Register(1, "startTime3", "endTime3", "startDate3", "endDate3", "nature3");

    ck.Register(2, "startTime0", "endTime0", "startDate0", "endDate0", "nature0");
    ck.Register(2, "startTime1", "endTime1", "startDate1", "endDate1", "nature1");
    ck.Register(2, "startTime2", "endTime2", "startDate2", "endDate2", "nature2");
    ck.Register(2, "startTime3", "endTime3", "startDate3", "endDate3", "nature3");

    auto requirements =
        [](auto operations)
        {
            int i = 0;
            for (auto op : operations)
            {
                auto tp = op.get();
                std::string ci = std::to_string(i);
                REQUIRE_THAT(std::get<0>(tp), Catch::Matchers::Equals("startTime" + ci));
                REQUIRE_THAT(std::get<1>(tp), Catch::Matchers::Equals("endTime" + ci));
                REQUIRE_THAT(std::get<2>(tp), Catch::Matchers::Equals("startDate" + ci));
                REQUIRE_THAT(std::get<3>(tp), Catch::Matchers::Equals("endDate" + ci));
                REQUIRE_THAT(std::get<4>(tp), Catch::Matchers::Equals("nature" + ci));
                ++i;
            }
        };

    ck.Historic(1).accept(requirements);
    ck.Historic(2).accept(requirements);
}

TEST_CASE("Testing mixed types - Variadic Template", "[Clock]")
{
    struct test_type
    {
        int i;
        std::string s;
    };

    Clock<std::string, int, test_type, float> ck;
    ck.Register(1, "string", 10, test_type{1, "Test Type"}, 4.5f);
    
    auto requirements =
        [](auto operations)
        {
            int i = 0;
            for (auto op : operations)
            {
                auto tp = op.get();
                test_type t = std::get<2>(tp);
                REQUIRE_THAT(std::get<0>(tp), Catch::Matchers::Equals("string"));
                REQUIRE(std::get<1>(tp) == 10);
                REQUIRE(t.i == 1);
                REQUIRE_THAT(t.s, Catch::Matchers::Equals("Test Type"));
                REQUIRE_THAT(std::get<3>(tp), Catch::Matchers::WithinRel(4.5, 0.1));
            }
        };

    ck.Historic(1).accept(requirements);
}