#pragma once
#ifndef HEADER_CONTROLLER
#define HEADER_CONTROLLER

#include <functional>
#include <map>
#include <string>
#include <Validator.h>
#include <optional>

// General purpose controller
// Our application is very simple so there is no need to multiple controllers here
// TODO : Implement the rule of 3 here, OR, delete all
class Item;
class Menu;
class Job;
class Controller
{
private:
    // TODO : think about this design choice,
    //        should the menu id be the key? is't kind messy?
    Validator validator;
    std::map<std::string, Job *> jobs_container;
    // TODO : Clock, use composition passing a pointer to clock to all jobs
    // Clock<...> clock or register, idk
    // Callbacks
    std::function<void()> clockIn_Callback;
    std::function<void()> clockOut_Callback;
    std::function<void()> sickDay_Callback;
    std::function<void()> vacation_Callback;
    std::function<void()> report_Callback;
    std::function<void()> add_developer_Callback;
    std::function<void()> add_pilot_Callback;
    // Job Items
    Item * clockIn;
    Item * clockOut;
    Item * sickDay;
    Item * vacations;
    Item * report;
    Item * previous;
    // Menu Items
    Item * add_developer;
    Item * add_pilot;
    // Menus
    Menu * current; // Who manages you?
    Menu * add_menu;
    Menu * list_menu;
private:
    void initializeCallbacks();
    void initializeItems();
    void initializeMenus();
    void buildView();
    void addJobMenu(const std::string & id);
    std::string getTime(const std::string& question, std::optional<std::string> error = std::nullopt);
    std::string getDate(const std::string& question, std::optional<std::string> error = std::nullopt);
public:
    // TODO : Create a destructor or use smart pointer
    void Build();
    void Execute(); // Only this is called we will be inside the infinity loop
};

#endif // HEADER_CONTROLLER