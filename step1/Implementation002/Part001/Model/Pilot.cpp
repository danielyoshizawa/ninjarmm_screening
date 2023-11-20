#include "Pilot.h"

Pilot::Pilot(const std::string &id, Clock_t &clock) : Job(id, clock){};

std::string Pilot::ClockIn(Date date, Time time)
{
    return "";
}

std::string Pilot::ClockOut(Date date, Time time)
{
    return "";
}

bool Pilot::ScheduleVacation(Date begin, Date end)
{
    return true;
}

bool Pilot::CallSickDay(Date date)
{
    return true;
}

std::string Pilot::Report() const
{
    return "";
}

const std::string Pilot::Id() const noexcept
{
    return Job::_id;
}