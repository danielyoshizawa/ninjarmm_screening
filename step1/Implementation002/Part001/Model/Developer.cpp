#include <Developer.h>
#include <Clock.h>
#include <sstream>
#define MAX_SICK_DAYS 9

// Developer Model Rules:
// - They need to work 8h per day (How to reinforce it?)
// - Can have 9 sick days per year (This is easy, can check for all the entries or keep an internal state) - DONE
// - 30 days vacations (Same as the previous one)
// - Work only on weekdays (I'm not keeping a calendar, maybe I'll need to ignore this one)
// - Report should have a resume of activity -DONE

// TODO : Does const & makes sense here?
//        should I go for R-Value, since I don't want the id to be outside this
//        object?
Developer::Developer(const std::string &id, Clock_t &clock) : Job(id, clock)
{
}

// Clock::Register data order
// startTime, startDate, endTime, endDate, nature
// TODO : Reinforce the rules defined for this class
std::string Developer::ClockIn(std::string date, std::string time)
{
    // TODO : Maybe we have a design flaw here
    //        I'll have many empty fields for each entry
    //        I guess I'll go with it for now, but need
    //        to rethink the way I register things
    //        maybe use variadic templates is not the best approach
    // TODO : Hardcoded Id for now, Developer == 1, Pilot == 2
    // TODO : Increasing the problem, maybe create a enum to
    //        nature. This is getting uglier
    clock.Register(_id, time, date, "", "", "clockin");
    return "Clock In";
}

std::string Developer::ClockOut(std::string date, std::string time)
{
    clock.Register(_id, "", "", time, date, "clockout");
    return "Clock Out";
}

std::string Developer::ScheduleVacation(std::string begin, std::string end)
{
    clock.Register(_id, "", begin, "", end, "vacation");
    return "Vactions Scheduled";
}

bool Developer::CallSickDay(std::string date)
{
    bool exceed_days{false};
    try
    {
        int count_sick_days{0};
        std::string input_year = date.substr(0, 4);
        clock.Historic(_id).accept([&](auto &operations)
                                   {
            for (auto op : operations)
            {
                if (input_year.compare(std::get<1>(op.get()).substr(0, 4)) == 0)
                {
                    ++count_sick_days;
                }
            }
        exceed_days = count_sick_days >= MAX_SICK_DAYS; });
    }
    catch (const std::out_of_range &e)
    {
        // We can ignore the exception,
        // meaning that are no sick days registered for the id
    }

    if (exceed_days)
    {
        return false;
    }

    clock.Register(_id, "", date, "", date, "sickDay");
    return true;
}

std::string Developer::Report() const
{
    std::stringstream output{""};

    clock.Historic(_id).accept(
        [&](auto operations)
        {
            for (auto op : operations)
            {
                auto tp = op.get();
                output << "------------------"
                       << "\n";
                output << "Start Time : " << std::get<0>(tp) << "\n";
                output << "Start Date : " << std::get<1>(tp) << "\n";
                output << "End Time   : " << std::get<2>(tp) << "\n";
                output << "End Date   : " << std::get<3>(tp) << "\n";
                output << "Nature     : " << std::get<4>(tp) << "\n";
            }
        });

    return output.str();
}

const std::string Developer::Id() const noexcept
{
    return Job::_id;
}
