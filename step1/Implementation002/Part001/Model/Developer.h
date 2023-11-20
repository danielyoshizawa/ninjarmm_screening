#pragma once
#ifndef HEADER_DEVELOPER
#define HEADER_DEVELOPER

#include "Job.h"

// Default constructor for now
// Rule of 0, no dinamically allocated memory so far
class Developer : public Job
{
private:
    bool exceedVacationDaysLimits(const Date & begin, const Date & end) const noexcept;
    bool validateVacationDates(const Date & begin,const Date & end) const noexcept;
public:
    Developer(const std::string & id, Clock_t & clock);
    std::string ClockIn(Date date, Time time) override;
    std::string ClockOut(Date date, Time time) override;
    bool ScheduleVacation(Date begin, Date end) override;
    bool CallSickDay(Date date) override;
    std::string Report() const override;
    const std::string Id() const noexcept override;
};

#endif // HEADER_DEVELOPER