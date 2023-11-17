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

TEST_CASE( "Developer Test Suit", "[Job][Developer]" ) {

    // TODO : Don't need a pointer here, stack is fine
    Clock_t clock;
    auto developer = std::make_unique<Developer>("", clock);

    SECTION("Clock In") {
        auto response = developer->ClockIn("2023-11-06", "10:05");
        REQUIRE(response == "Clock In");

    }
    SECTION("Clock Out") {
        auto response = developer->ClockOut("2023-11-06", "18:05");
        REQUIRE(response == "Clock Out");
    }

    SECTION("Vacations") {
        auto response = developer->ScheduleVacation("2023-12-05", "2023-01-04");
        REQUIRE(response == "Vactions Scheduled");
    }

    SECTION("Calling Sick") {
        REQUIRE(developer->CallSickDay("2023-11-07"));
    }

    SECTION("Report Status") {
        std::stringstream output;
        output << "------------------" << "\n";
        output << "Start Time : " << "10:05" << "\n";
        output << "Start Date : " << "2023-11-06" << "\n";
        output << "End Time   : " << "\n";
        output << "End Date   : " << "\n";
        output << "Nature     : " << "clockin" << "\n";

        developer->ClockIn("2023-11-06", "10:05");
        auto response = developer->Report();

        REQUIRE_THAT(response, Catch::Matchers::Equals(output.str()));
    }
}