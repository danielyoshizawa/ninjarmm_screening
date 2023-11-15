// TODO : Delete this file, it's just a sandbox not part of the project

#include <Clock.h>
#include <string>
#include <iostream>

int main()
{
// Instanciation of Clock, defining the variadic template types
    Clock<std::string, int, double, float> ck;

    // Register an entry on our clock, its signature is
    //
    // void Register(int id, Args... args)
    //
    // Note that the first argument is an id,
    // this is used to differentiate between
    // Elements that follow the same data type structure. 
    ck.Register(1, "string", 10, 6.8, 4.5f);

    // Clock has a function called Historic, where it returns
    // a Recorder with all entries for a given id.
    // Its signature is
    //
    // auto Historic(int id) const noexcept -> Recorder<Args...>
    //
    auto recorder = ck.Historic(1);

    // Recorder is the class resposible to store in memory
    // all the entries registered using clock.
    // It offers two options to iterate over the entries.
    //
    // auto history() const noexcept -> std::vector<Record<Args...>>
    //
    // or
    //
    // template <typename V>
    // void accept(V visitor) const
    //
    // The former accepts a lambda function, functor or std::function
    // with the following signature:
    //
    // void function(auto operations);
    //
    // This implementation takes advantage of the Visitor pattern,
    // however it's not implemented in the traditional way it has the
    // same behavior.

    auto visitor =
        [](auto operations)
        {
            for (auto op : operations)
            {
                // operations is a vector of tuples
                // to access the tuple members you have some options
                // here we are using std::get passing the position
                // this is a good approach if you have duplicated types
                // in yout tuple, if you are sure that you don't have
                // duplicates, you can use std::get<type>, to retrieve
                // the data.
                auto tp = op.get(); // Record::get() -> std::tuple<Args...>
                std::string s = std::get<0>(tp);
                
                // Do your thing!
                std::cout << s << std::endl;
            }
        };

    // Calling Recorder::accept( <lambda> ) to execute our lambda function
    // on the collection of records
    recorder.accept(visitor);

    return 0;
}