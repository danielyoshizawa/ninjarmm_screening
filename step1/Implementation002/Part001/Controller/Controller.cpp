#include "Controller.h"
#include "Menu.h"
#include "Item.h"

#include "Developer.h"
#include "Pilot.h"

#include <iostream>

Controller::Controller()
{
    // clock = std::make_unique<Clock_t>();
}

std::string Controller::getTime(const std::string &question, std::optional<std::string> error)
{
    return getInput(question, std::bind(&Validator::is_time, &validator, std::placeholders::_1), error);
};

std::string Controller::getDate(const std::string &question, std::optional<std::string> error)
{
    return getInput(question, std::bind(&Validator::is_date, &validator, std::placeholders::_1), error);
}

std::string Controller::getInput(const std::string &question, std::function<bool(std::string)> &&validation, std::optional<std::string> error)
{
    std::string input{};
    bool c = true;
    do
    {
        std::cout << question << std::endl;
        std::cin >> input;

        c = !(validation(input));
        if (c)
        {
            std::cout << error.value_or("Invalid input, please enter again") << std::endl;
        }
    } while (c);

    return input;
}

void Controller::executeCommand(std::function<void(Job &)> &&command)
{
    if (
        auto it = jobs_container.find(current->key());
        it != std::end(jobs_container))
    {
        command(*it->second);
    }
    else
    {
        std::cout << "Something went wrong, no action performed" << std::endl;
    }
}

void Controller::initializeCallbacks()
{
    clockIn_Callback = [&]
    {
        std::cout << "|| Clock In ||" << std::endl;
        std::string start_time = getTime("Start Time (hh:mm) : ");
        std::string start_date = getDate("Start Date (yyyy-mm-dd) : ");
        executeCommand([&](Job &job)
                       {
            job.ClockIn(Date{start_date}, Time{start_time});
            std::cout << "ClockIn : " << start_time << " | " << start_date << " - succeed" << std::endl; });
    };
    clockOut_Callback = [&]
    {
        std::cout << "|| Clock Out ||" << std::endl;
        std::string end_time = getTime("End Time (hh:mm): ");
        std::string end_date = getDate("End Date (yyyy-mm-dd) : ");
        executeCommand([&](Job &job)
                       {
            job.ClockOut(Date{end_date}, Time{end_time});
            std::cout << "ClockOut : " << end_time << " | " << end_date << " - succeed" << std::endl; });
    };
    sickDay_Callback = [&]
    {
        std::cout << "|| Sick Day ||" << std::endl;
        std::string date = getDate("Date (yyyy-mm-dd) : ");
        executeCommand([&](Job &job)
                       {
            if (job.CallSickDay(Date{date}))
            {
                std::cout << "Sick Day : " << date << " - registered" << std::endl;
            } else {
                std::cout << "Sick days exceed for " << date.substr(0,4) << std::endl;
            } });
    };
    vacation_Callback = [&]
    {
        std::cout << "|| Vacations ||" << std::endl;
        std::string start_date = getDate("Start Date (yyyy-mm-dd) : ");
        std::string end_date = getDate("End Date (yyyy-mm-dd) : ");
        executeCommand([&](Job &job)
                       {
            // TODO : Date can throw
            job.ScheduleVacation(Date{start_date}, Date{end_date});
            // TODO : Evaluate the function return
            std::cout << "Vacations : " << start_date << " | " << end_date << " - succeed" << std::endl; });
    };
    report_Callback = [&]
    {
        executeCommand([&](Job &job)
                       {
            std::cout << "Calling Report on empty" << std::endl;
            try
            {
                std::cout << job.Report() << std::endl;
            }
            catch (const std::out_of_range &e)
            {
                std::cout << "No registers found!" << std::endl;
            } });
    };
    add_developer_Callback = [&]
    {
        std::string id{};
        std::cout << "Please enter the worker id : " << std::endl;
        std::cin >> id;

        jobs_container.insert(std::pair(id, new Developer(id, clock)));
        addJobMenu(id);
    };
    add_pilot_Callback = [&]
    {
        std::string id{};
        std::cout << "Please enter the worker id" << std::endl;
        std::cin >> id;

        jobs_container.insert(std::pair(id, new Pilot(id, clock)));
        addJobMenu(id);
    };
}

void Controller::addJobMenu(const std::string &id)
{
    Menu *menu = new Menu(list_menu, id, id);
    menu
        ->add(clockIn)
        .add(clockOut)
        .add(sickDay)
        .add(vacations)
        .add(report)
        .add(previous);
    list_menu->add(menu);
}

void Controller::initializeItems()
{
    clockIn = new Item(clockIn_Callback, "Clock In", "ci");
    clockOut = new Item(clockOut_Callback, "Clock Out", "co");
    sickDay = new Item(sickDay_Callback, "SickDay", "sd");
    vacations = new Item(vacation_Callback, "Vacations", "vc");
    report = new Item(report_Callback, "Report", "rp");
    previous = new Item([] {}, "Return", "r");
    add_developer = new Item(add_developer_Callback, "Developer", "dv");
    add_pilot = new Item(add_pilot_Callback, "Pilot", "pt");
}

void Controller::initializeMenus()
{
    current = new Menu(nullptr, "", ""); // Root;
    add_menu = new Menu(current, "Add", "ad");
    list_menu = new Menu(current, "List Jobs", "lj");
}

void Controller::buildView()
{
    add_menu
        ->add(add_developer)
        .add(add_pilot)
        .add(previous);

    list_menu
        ->add(previous);

    current
        ->add(add_menu)
        .add(list_menu);
}

void Controller::Build()
{
    initializeCallbacks();
    initializeItems();
    initializeMenus();
    buildView();
}

void Controller::Execute()
{
    std::string c{" "};
    while (c.compare("x") != 0)
    {
        auto menus = current->menus();
        auto items = current->items();
        for (auto menu : menus)
        {
            std::cout << "(" << menu->key() << ") - " << menu->description() << std::endl;
        }
        for (auto item : items)
        {
            std::cout << "(" << item->key() << ") - " << item->description() << std::endl;
        }

        std::cout << "(x) - Exit" << std::endl;

        std::cin >> c;
        if (c.compare("r") == 0 && current->previous())
        {
            current = current->previous();
        }
        else
        {
            current = current->triggerKey(c);
        }
    }
}
