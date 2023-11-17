#pragma once
#ifndef HEADER_PILOT
#define HEADER_PILOT

#include "Job.h"
#include <string>

// Default constructor for now
// Rule of 0, no dinamically allocated memory so far
class Pilot : public Job
{
public:
    Pilot(const std::string & id, Clock_t & clock);
    std::string ClockIn(std::string date, std::string time) override;
    std::string ClockOut(std::string date, std::string time) override;
    std::string ScheduleVacation(std::string begin, std::string end) override;
    bool CallSickDay(std::string date) override;
    std::string Report() const override;
    const std::string Id() const noexcept override;
};

#endif // HEADER_PILOT