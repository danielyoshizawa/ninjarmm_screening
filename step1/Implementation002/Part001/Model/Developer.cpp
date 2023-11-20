#include <Developer.h>
#include <Clock.h>
#include <sstream>
#define MAX_SICK_DAYS 9

// Developer Model Rules:
// - They need to work 8h per day (How to reinforce it?)
// - Can have 9 sick days per year (This is easy, can check for all the entries or keep an internal state) - DONE
// - 30 days vacations per year (Same as the previous one)
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
std::string Developer::ClockIn(Date date, Time time)
{
    // TODO : Maybe we have a design flaw here
    //        I'll have many empty fields for each entry
    //        I guess I'll go with it for now, but need
    //        to rethink the way I register things
    //        maybe use variadic templates is not the best approach
    // TODO : Hardcoded Id for now, Developer == 1, Pilot == 2
    // TODO : Increasing the problem, maybe create a enum to
    //        nature. This is getting uglier
    // TODO : Think about empty dates, those will throw
    Time t = Time{"10:00"};
    Date d = Date{"2023-10-10"};
    clock.Register(_id, time.toString(), date.toString(), "", "", "clockin");
    return "Clock In";
}

std::string Developer::ClockOut(Date date, Time time)
{
    clock.Register(_id, "", "", time.toString(), date.toString(), "clockout");
    return "Clock Out";
}

// TODO : Write a function to return the number of vacations days in the register
bool Developer::ScheduleVacation(Date begin, Date end)
{
    // Group by year
    // Calc range (2023-10-01 -> 2023-10-30 should return 30)
    // If exceed 30 days fail and return remaining days (use std::variant c++20)
    // TODO : Ignore feb 29th
    // TODO : Keep track of each month length
    // TODO : Think about vacations at the end of the year that passes to the next year
    //        Maybe only work with begin, if the end is next year, cap to last day of the month
    //        And the reminder goes to the next year.
    // 2023-01-01 : 2023-01-09 = 10 days
    // 2023-02-01 : 2023-02-14 = 15 days
    // 2023-12-26 : 2024-01-16 =  6 days (won't accept)
    // 2023-12-27 : 2024-01-15 =  5 days (2023) -> 15 days (2024)
    // 2024-06-10 : 2024-06-19 = 10 days
    // 2024-07-10 : 2024-06-15 =  6 days (won't accept)
    // 2024-07-10 : 2024-06-14 =  5 days
    // First thread input
    // Means begin > end, invalid input

    // TODO : All by copy for now, improvements on the next iteration
    // TODO : Refactor it all!!!
    if (begin.year() != end.year())
    {
        std::string prev_year_date = std::to_string(begin.year()) + "-12-31";
        std::string next_year_date = std::to_string(end.year()) + "-01-01";
        Date partial_begin{next_year_date};
        Date partial_end{prev_year_date};

        int partial_days_prev = partial_end - begin;
        if (partial_days_prev < 0 || partial_days_prev > 30)
        {
            return false;
        }
        int partial_days_next = end - partial_begin;
        if (partial_days_next < 0 || partial_days_next > 30)
        {
            return false;
        }
    }
    else
    {
        int days = end - begin;
        if (days < 0 || days > 30)
        {
            return false;
        }
    }

    // Accumulator
    try
    {
        // Map to keep track of diff years
        std::map<int, int> count_vacation_days_map;
        clock.Historic(_id).accept([&](auto &operations)
                                   {
            for (auto & op : operations) {
                // TODO : as ‘this’ argument discards qualifiers [-fpermissive]
                // auto tp = op.get();
                // However
                auto tp = op.tuple; // Works
                // op.get() is only failing in this context, need to investigate why
                std::string op_start_date = std::get<1>(tp);
                std::string op_end_date = std::get<3>(tp);
                Date tmp_start{op_start_date};
                Date tmp_end{op_end_date};

                // Accumulate every year, then compare
                if (tmp_start.year() == tmp_end.year()) {
                    count_vacation_days_map[tmp_start.year()] += tmp_end - tmp_start;
                } else {
                    std::string prev_year_date = std::to_string(tmp_start.year()) + "-12-31";
                    std::string next_year_date = std::to_string(tmp_end.year()) + "-01-01";
                    Date partial_begin{next_year_date};
                    Date partial_end{prev_year_date};
                    count_vacation_days_map[tmp_start.year()] += partial_begin - tmp_start;
                    count_vacation_days_map[tmp_end.year()] += tmp_end - partial_end;
                }
            } });
        // If end and begin years are equal
        if (begin.year() == end.year())
        {
            int days = end - begin;
            if ((count_vacation_days_map.at(begin.year()) + days) > 30)
            {
                return false;
            }
        }
        else
        {
            std::string prev_year_date = std::to_string(begin.year()) + "-12-31";
            std::string next_year_date = std::to_string(end.year()) + "-01-01";
            Date partial_begin{next_year_date};
            Date partial_end{prev_year_date};
            int partial_start_days = partial_begin - begin;
            int partial_end_days = end - partial_end;
            try
            {
                if ((count_vacation_days_map.at(begin.year()) + partial_start_days) > 30)
                {
                    return false;
                }
            }
            catch (...)
            {
            } // If don't find the element means we don't have vacations planned

            if ((count_vacation_days_map.at(end.year()) + partial_end_days) > 30)
            {
                return false;
            }
        }
    }
    catch (const std::out_of_range &ex)
    {
    }

    clock.Register(_id, "", begin.toString(), "", end.toString(), "vacation");
    return true;
}

// TODO : Check for duplicates
bool Developer::CallSickDay(Date date)
{
    bool exceed_days{false};
    try
    {
        int count_sick_days{0};
        int input_year = date.year();
        clock.Historic(_id).accept([&](auto &operations)
                                   {
            for (auto op : operations)
            {
                Date dt = std::get<1>(op.get());
                if (input_year == dt.year())
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

    clock.Register(_id, "", date.toString(), "", date.toString(), "sickDay");
    return true;
}

std::string Developer::Report() const
{
    std::stringstream output{""};
    // TODO : try/catch - Historic can throw
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
