#pragma once
#ifndef HEADER_PILOT
#define HEADER_PILOT

#include "Job.h"
#include <string>
#include <Date.h>

// Default constructor for now
// Rule of 0, no dinamically allocated memory so far
class Pilot : public Job
{
public:
    Pilot(const std::string & id, Clock_t & clock);
    std::string ClockIn(Date date, Time time) override;
    std::string ClockOut(Date date, Time time) override;
    bool ScheduleVacation(Date begin, Date end) override;
    bool CallSickDay(Date date) override;
    std::string Report() const override;
    const std::string Id() const noexcept override;
};

#endif // HEADER_PILOT