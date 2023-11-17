#pragma once
#ifndef HEADER_CLOCK
#define HEADER_CLOCK

#include <string>
#include <map>
#include <vector>

template <typename... Args>
struct Record
{
    std::tuple<Args...> tuple;
    Record(Args... args)
    {
        tuple = std::forward_as_tuple(args...);
    }

    auto get() -> std::tuple<Args...>
    {
        return tuple;
    }
};

template <typename... Args>
class Recorder
{
private:
    std::vector<Record<Args...>> operations;

public:
    // TODO : All by copy, improve later (maybe)
    void add(Record<Args...> record)
    {
        operations.push_back(record);
    }
    auto history() const noexcept -> std::vector<Record<Args...>>
    {
        return operations;
    }

    template <typename V>
    void accept(V &&visitor) const
    {
        visitor(operations);
    }

    // C++20
    // void accept(auto const && visitor) const {
    //     visitor(operations);
    // }
};

// TODO : Rename Clock -> Register or smth like it
template <typename... Args>
class Clock
{
private:
    std::map<std::string, Recorder<Args...>> operations;

public:
    void Register(const std::string &id, Args... args)
    {
        auto newRecord = Record{args...};
        // Retrive recorder
        auto recorder = operations.find(id);
        if (recorder == std::end(operations))
        {
            // TODO :: Check if the operation succeed before assigning the
            // iterator
            recorder = operations.insert(std::pair{id, Recorder<Args...>{}}).first;
        }
        // Add new entry
        recorder->second.add(newRecord);
    }

    auto Historic(const std::string &id) const -> Recorder<Args...>
    {
        return operations.at(id);
    };
};
#endif // HEADER_CLOCK