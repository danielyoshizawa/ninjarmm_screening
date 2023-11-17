#include "Pilot.h"

Pilot::Pilot(const std::string &id, Clock_t &clock) : Job(id, clock){};

std::string Pilot::ClockIn(std::string date, std::string time)
{
    return "";
}

std::string Pilot::ClockOut(std::string date, std::string time)
{
    return "";
}

std::string Pilot::ScheduleVacation(std::string begin, std::string end)
{
    return "";
}

std::string Pilot::CallSickDay(std::string date)
{
    return "";
}

std::string Pilot::Report() const
{
    return "";
}

const std::string Pilot::Id() const noexcept
{
    return Job::_id;
}