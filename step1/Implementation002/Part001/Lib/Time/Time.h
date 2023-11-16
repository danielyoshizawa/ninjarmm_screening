#ifndef HEADER_TIME
#define HEADER_TIME

#include <string>
// Have a class to do time arithmetics
// Receive strings, parse to int, overload -
// This lib will only operate on hh:mm
// The date doesn't matter much since its just a comparission
// (e.g. 2023-10-10 == 2023-10-10)
class Time
{
private:
    // Types (Using basic types, more specialized ones on next implementation)
    int _hour{0};
    int _minute{0};

private:
    // Helper functions
    void parseString(const std::string &input)
    {
        // Split the string using : as delimitator
        // add 0 to hour 1 to minute
        // here we assume that the input was treated
        // However we will check for cast problems
        auto pos = input.find(':'); // size_t
        _hour = std::stoi(input.substr(0, pos));
        _minute = std::stoi(input.substr(pos + 1, input.length()));
    };

public:
    // Once time is defined we cannot change it
    // Arithmetics will return a new object (value) of time
    Time(const std::string &time)
    {
        parseString(time);
    };
    int hour() const noexcept
    {
        return _hour;
    };
    int minute() const noexcept
    {
        return _minute;
    };
    std::string toString() const
    {
        return std::to_string(_hour) + ":" + std::to_string(_minute);
    };
    friend Time operator-(const Time &l, const Time &r);
    friend std::ostream &operator<<(std::ostream &out, const Time &o);
};

Time operator-(const Time &l, const Time &r)
{
    int diff_time = ((l.hour() * 60) + l.minute()) - ((r.hour() * 60) + r.minute());

    return Time{std::to_string(diff_time / 60) + ":" + std::to_string(diff_time % 60)};
};

std::ostream &operator<<(std::ostream &out, const Time &time)
{
    return out << time.toString();
};
#endif // HEADER_TIME