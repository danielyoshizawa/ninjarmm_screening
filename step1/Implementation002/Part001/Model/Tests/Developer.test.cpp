// Job have 4 functionalities
// 1. clock in and out
//     - Clock in and out should receive a date and time each, this will be 2 different functions
// 2. schedule vacation
//     - Schedule Vacation should receive two dates (start and end inclusive)
// 3. call a sick day
//     - Call a sick day should receive a date
// 4. report status
//     - report status should print out a report with 
//     - total worked time
//     - Sick days
//     - Extra hours
//     - Missing hours
//     - Planned Vacations
      
// ##### Developer

// Developer should log their hours using the ClockSystem, and the rules are as follow:
// - They need to work 8h per day
// - Can have 9 sick days per year
// - 30 days vacations
// - Work only on weekdays
// - Report should have a resume of activity
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include "Developer.h"
#include <memory>
#include <sstream>
#include <Date.h>

TEST_CASE( "Developer Test Suit", "[Job][Developer]" ) {

    // TODO : Don't need a pointer here, stack is fine
    Clock_t clock;
    auto developer = std::make_unique<Developer>("", clock);

    SECTION("Clock In") {
        auto response = developer->ClockIn(Date{"2023-11-06"}, Time{"10:05"});
        REQUIRE(response == "Clock In");

    }
    SECTION("Clock Out") {
        auto response = developer->ClockOut(Date{"2023-11-06"}, Time{"18:05"});
        REQUIRE(response == "Clock Out");
    }

    SECTION("Vacations") {
        // End date should be later than the start date
        REQUIRE_FALSE(developer->ScheduleVacation(Date{"2024-01-01"}, Date{"2023-12-25"}));
        // Shouldn't exceed 30 days
        REQUIRE_FALSE(developer->ScheduleVacation(Date{"2023-01-01"}, Date{"2023-02-02"}));
        // // Last rule shouldn't apply directly if end date is in the next year
        REQUIRE(developer->ScheduleVacation(Date{"2020-12-15"}, Date{"2021-01-15"}));
        // // Except if any part is more than 30 days
        REQUIRE_FALSE(developer->ScheduleVacation(Date{"2023-11-30"}, Date{"2024-01-01"}));
        REQUIRE_FALSE(developer->ScheduleVacation(Date{"2023-12-31"}, Date{"2024-02-01"}));
        // 2023-01-01 : 2023-01-09 =  8 days
        // 2023-02-01 : 2023-02-16 = 15 days // 23
        // 2023-11-26 : 2023-12-15 = 19 Days (won't accept)
        // 2023-12-20 : 2024-01-16 = 11 days (2023) (won't accept)
        // 2023-12-27 : 2024-01-15 =  5 days (2023) -> 15 days (2024)
        // 2024-06-10 : 2024-06-19 = 10 days
        // 2024-07-10 : 2024-06-15 =  6 days (won't accept)
        // 2024-06-10 : 2024-06-15 =  5 days
        REQUIRE(developer->ScheduleVacation(Date{"2023-01-01"}, Date{"2023-01-09"}));
        REQUIRE(developer->ScheduleVacation(Date{"2023-02-01"}, Date{"2023-02-14"}));
        REQUIRE_FALSE(developer->ScheduleVacation(Date{"2023-11-26"}, Date{"2023-12-15"}));
        REQUIRE_FALSE(developer->ScheduleVacation(Date{"2023-12-20"}, Date{"2024-01-16"}));
        REQUIRE(developer->ScheduleVacation(Date{"2023-12-27"}, Date{"2024-01-15"}));
        REQUIRE(developer->ScheduleVacation(Date{"2024-06-10"}, Date{"2024-06-19"}));
        REQUIRE_FALSE(developer->ScheduleVacation(Date{"2024-07-10"}, Date{"2024-06-15"}));
        REQUIRE(developer->ScheduleVacation(Date{"2024-06-10"}, Date{"2024-06-15"}));
    }

    SECTION("Calling Sick") {
        // Our current limit of sick days is 9 per year
        REQUIRE(developer->CallSickDay(Date{"2023-11-01"}));
        REQUIRE(developer->CallSickDay(Date{"2023-11-02"}));
        REQUIRE(developer->CallSickDay(Date{"2023-11-03"}));
        REQUIRE(developer->CallSickDay(Date{"2023-11-04"}));
        REQUIRE(developer->CallSickDay(Date{"2023-11-05"}));
        REQUIRE(developer->CallSickDay(Date{"2023-11-06"}));
        REQUIRE(developer->CallSickDay(Date{"2023-11-07"}));
        REQUIRE(developer->CallSickDay(Date{"2023-11-08"}));
        REQUIRE(developer->CallSickDay(Date{"2023-11-09"}));
        REQUIRE_FALSE(developer->CallSickDay(Date{"2023-11-10"}));
        // 2024 should work
        REQUIRE(developer->CallSickDay(Date{"2024-01-01"}));
        // 2023 should still fail
        REQUIRE_FALSE(developer->CallSickDay(Date{"2023-11-11"}));
    }

    SECTION("Report Status") {
        std::stringstream output;
        output << "------------------" << "\n";
        output << "Start Time : " << "10:05" << "\n";
        output << "Start Date : " << "2023-11-06" << "\n";
        output << "End Time   : " << "\n";
        output << "End Date   : " << "\n";
        output << "Nature     : " << "clockin" << "\n";

        developer->ClockIn(Date{"2023-11-06"}, Time{"10:05"});
        auto response = developer->Report();

        REQUIRE_THAT(response, Catch::Matchers::Equals(output.str()));
    }
}