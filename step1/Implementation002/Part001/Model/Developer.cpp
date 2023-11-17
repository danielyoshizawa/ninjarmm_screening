#include <Developer.h>
#include <Clock.h>
#include <sstream>

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

std::string Developer::CallSickDay(std::string date)
{
    clock.Register(_id, "", date, "", date, "sickDay");
    return "Calling Sick";
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
