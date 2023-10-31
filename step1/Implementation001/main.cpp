#include <memory>
#include <vector>
#include <iostream>

class Job
{
public:
    virtual void function001() = 0;
    virtual void function002() = 0;
    virtual void function003() = 0;
    virtual void function004() = 0;
};

class Programmer : public Job
{
public:
    void function001() override
    {
        std::cout << "Programmer Function 001" << std::endl;
    };
    void function002() override
    {
        std::cout << "Programmer Function 002" << std::endl;
    };
    void function003() override
    {
        std::cout << "Programmer Function 003" << std::endl;
    };
    void function004() override
    {
        std::cout << "Programmer Function 004" << std::endl;
    };
};

class Pilot : public Job
{
public:
    void function001() override
    {
        std::cout << "Pilot Function 001" << std::endl;
    };
    void function002() override
    {
        std::cout << "Pilot Function 002" << std::endl;
    };
    void function003() override
    {
        std::cout << "Pilot Function 003" << std::endl;
    };
    void function004() override
    {
        std::cout << "Pilot Function 004" << std::endl;
    };
};

template <typename T, typename U>
void IsInBounds(T httpResponse, U lowerRange, U higherRange)
{
    std::cout << "Http Response Code : " << httpResponse << std::endl;
    std::cout << "Lower Range : " << lowerRange << std::endl;
    std::cout << "Higher Range : " << higherRange << std::endl;

    if (lowerRange <= httpResponse && higherRange >= httpResponse)
    {
        std::cout << "Within range" << std::endl;
    }
    else
    {
        std::cout << "Outside range" << std::endl;
    }
};

template<typename T>
int ContainsTheString(T && callback, std::vector<std::string> strings)
{
    int count = 0;
    for (auto s : strings)
    {
        if (callback(s))
        {
            count++;
        }
    }
    return count;
};

int main()
{
    auto programmer = std::make_unique<Programmer>();
    auto pilot = std::make_unique<Pilot>();
    std::vector<Job *> collection = {programmer.get(), pilot.get()};

    for (auto j : collection)
    {
        j->function001();
        j->function002();
        j->function003();
        j->function004();
    }

    uint32_t httpResponseCode = 550;
    IsInBounds<uint32_t>(httpResponseCode, 500, 599);

    auto theStrings = std::vector<std::string>{"one", "two", "test", "test"};
    auto count = ContainsTheString(
        [](const std::string &tested)
        {
            return tested == "test";
        },
        theStrings);

    std::cout << "Result : " << count << std::endl;

    return 0;
}