#pragma once
#ifndef HEADER_VALIDATOR
#define HEADER_VALIDATOR

#include <string>
#include <regex>

// Minute Regex -> ([0-9]{1})|([0-5]{1}[0-9]{1})
// Hour Regex -> ([0-9]{1})|([01][0-9]{1})|(2[0-3]{1})
// Day Regex -> ([1-9]{1})|(0[1-9]{1})|([12]{1}[0-9]{1})|(3[01]{1})
// Month Regex -> ([1-9])|(0[1-9]{1})|(1[0-2]{1})
// Year Regex -> ([0-9]{4})

class Validator
{
private:
    std::regex time_pattern{"^(([0-9]{1})|([01]{1}[0-9]{1})|(2[0-3]{1}))(:)(([0-9]{1})|([0-5]{1}[0-9]{1}))$"};
    std::regex date_pattern{"^([0-9]{4})(-)(([1-9])|(0[1-9]{1})|(1[0-2]{1}))(-)(([1-9]{1})|(0[1-9]{1})|([12]{1}[0-9]{1})|(3[01]{1}))$"};

    bool match(const std::string &subject, std::regex pattern)
    {
        return std::regex_match(subject, pattern);
    }

public:
    bool is_time(const std::string &time)
    {
        return match(time, time_pattern);
    }

    bool is_date(const std::string & date)
    {
        return match(date, date_pattern);
    }
};

#endif // HEADER_VALIDATOR