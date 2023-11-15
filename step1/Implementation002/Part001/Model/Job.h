#pragma once
#ifndef HEADER_JOB
#define HEADER_JOB

#include <string>
#include <Clock.h>

// TODO : First implementation - Everything is based on strings
//        Second implementation - Try to move to std::date and std::time
//        Third implementation - If possible, std::chronos (had some problems with it)
class Job
{
public:
    std::string _id {};
    // TODO : Maybe keep a pointer, in case we need to move things around
    // startTime, startDate, endTime, endDate, nature
    // TODO : Use composition for the clock, need to be shared between instances,
    //        I guess it makes sense
    Clock<std::string, std::string, std::string, std::string, std::string> clock;
public:
// TODO : Maybe return a std::variant or a response {status, msg} or smth
    virtual std::string ClockIn(std::string date, std::string time) = 0;
    virtual std::string ClockOut(std::string date, std::string time) = 0;
    virtual std::string ScheduleVacation(std::string begin, std::string end) = 0;
    virtual std::string CallSickDay(std::string date) = 0;
    virtual std::string Report() const = 0;
    virtual const std::string Id() const noexcept = 0;
};

#endif // HEADER_JOB