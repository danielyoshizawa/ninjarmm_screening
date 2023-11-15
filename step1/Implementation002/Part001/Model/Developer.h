#pragma once
#ifndef HEADER_DEVELOPER
#define HEADER_DEVELOPER

#include "Job.h"

// Default constructor for now
// Rule of 0, no dinamically allocated memory so far
class Developer : public Job
{
public:
    Developer(const std::string & id);
    std::string ClockIn(std::string date, std::string time) override;
    std::string ClockOut(std::string date, std::string time) override;
    std::string ScheduleVacation(std::string begin, std::string end) override;
    std::string CallSickDay(std::string date) override;
    std::string Report() const override;
    const std::string Id() const noexcept override;
};

#endif // HEADER_DEVELOPER