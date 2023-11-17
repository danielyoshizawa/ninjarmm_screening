#pragma once
#ifndef HEADER_JOB
#define HEADER_JOB

#include <string>
#include <Clock.h>

typedef Clock<std::string, std::string, std::string, std::string, std::string> Clock_t;

// TODO : First implementation - Everything is based on strings
//        Second implementation - Try to move to std::date and std::time
//        Third implementation - If possible, std::chronos (had some problems with it)
class Job
{
public:
    std::string _id{};
    // TODO : Maybe keep a pointer, in case we need to move things around
    // startTime, startDate, endTime, endDate, nature
    // TODO : Use composition for the clock, need to be shared between instances,
    //        I guess it makes sense
    Clock_t &clock;

public:
    // TODO : Maybe return a std::variant or a response {status, msg} or smth
    //        Since we don't have many possible outputs for the methods
    //        I'll change the return to bool, or it does work or not
    // C++20 : Job(const std::string & id, auto & clock)
    Job(const std::string &id, Clock_t &clock) : _id(id), clock(clock){};
    virtual std::string ClockIn(std::string date, std::string time) = 0;
    virtual std::string ClockOut(std::string date, std::string time) = 0;
    virtual std::string ScheduleVacation(std::string begin, std::string end) = 0;
    virtual bool CallSickDay(std::string date) = 0;
    virtual std::string Report() const = 0;
    virtual const std::string Id() const noexcept = 0;
};

#endif // HEADER_JOB