#pragma once
#ifndef HEADER_DATE
#define HEADER_DATE

#include <vector>
#include <stdexcept>
#include <numeric>
#include <sstream>
#include <iomanip>

class Date
{
private:
    const std::vector<int> days_in_month{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int _year;
    int _month;
    int _day;

private:
    // Helper functions
    void parseString(const std::string &input)
    {
        auto pos_first = input.find('-'); // size_t
        auto pos_last = input.find_last_of('-');
        _year = std::stoi(input.substr(0, pos_first));
        _month = std::stoi(input.substr(pos_first + 1, pos_last));
        _day = std::stoi(input.substr(pos_last + 1, input.length()));
    };
    bool validate() const
    {
        if (_month < 1 || _month > 12)
        {
            return false;
        }

        int max_days = days_in_month.at(_month);

        if (_day < 1 || _day > max_days)
        {
            return false;
        }

        return true;
    };
    int inDays() const noexcept
    {
        int days = _day;
        days += std::accumulate(std::begin(days_in_month), std::begin(days_in_month) + (_month), 0);
        days += (_year - 1) * 365;

        return days;
    }

public:
    ~Date() = default;
    Date(const std::string &date)
    {
        parseString(date);
        if (!validate())
        {
            throw std::invalid_argument("Invalid date format");
        }
    }
    Date(const Date &other)
    {
        _day = other._day;
        _month = other._month;
        _year = other._year;
    }
    Date &operator=(const Date &other)
    {
        _day = other._day;
        _month = other._month;
        _year = other._year;

        return *this;
    }
    Date( Date && other) = default;
    Date &operator=(Date && other) = default;
    int year() const noexcept
    {
        return _year;
    }
    int month() const noexcept
    {
        return _month;
    }
    int day() const noexcept
    {
        return _day;
    }
    std::string toString() const
    {
        std::stringstream ss;
        ss << std::to_string(_year) << "-";
        ss << std::setfill('0') << std::setw(2) << std::to_string(_month) << "-";
        ss << std::setw(2) << std::to_string(_day);
        return ss.str();
    };

    friend int operator-(const Date &l, const Date &r);
    friend std::ostream &operator<<(std::ostream &out, const Date &o);
};

inline int operator-(const Date &l, const Date &r)
{
    return l.inDays() - r.inDays();
};

inline std::ostream &operator<<(std::ostream &out, const Date &time)
{
    return out << time.toString();
};
#endif // HEADER_DATE