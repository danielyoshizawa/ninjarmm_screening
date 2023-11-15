#include "Controller.h"
#include "Menu.h"
#include "Item.h"

#include "Job.h"
#include "Developer.h"
#include "Pilot.h"

#include <iostream>

void Controller::initializeCallbacks()
{
    clockIn_Callback = [&]
    {
        std::string start_time{};
        std::string start_date{};
        bool c = true;
        do {
            std::cout << "|| Clock In ||" << std::endl;
            std::cout << "Start Time (hh:mm) : " << std::endl;
            std::cin >> start_time;
            std::cout << "Start Date : " << std::endl;
            std::cin >> start_date;
            c = !(validator.is_time(start_time) && validator.is_date(start_date));
            if (c) {
                std::cout << "Invalid input, please enter again" << std::endl;
            }
        } while(c);

        // TODO : Figure out how to refactor this bit
        if (
            auto it = jobs_container.find(current->key());
            it != std::end(jobs_container))
        {
            it->second->ClockIn(start_time, start_date);
            std::cout << "ClockIn : " << start_time << " | " << start_date << " - succeed" << std::endl;
        }
        else
        {
            std::cout << "Something went wrong, no action performed" << std::endl;
        }
    };
    clockOut_Callback = [&]
    {
        std::string end_time{};
        std::string end_date{};
        bool c = true;
        do {
            std::cout << "|| Clock Out ||" << std::endl;
            std::cout << "End Time (hh:mm): " << std::endl;
            std::cin >> end_time;
            std::cout << "End Date (yyyy-mm-dd) : " << std::endl;
            std::cin >> end_date;
            c = !(validator.is_time(end_time) && validator.is_date(end_date));
            if (c) {
                std::cout << "Invalid input, please enter again" << std::endl;
            }
        } while(c);
        if (
            auto it = jobs_container.find(current->key());
            it != std::end(jobs_container))
        {
            it->second->ClockOut(end_time, end_date);
            std::cout << "ClockOut : " << end_time << " | " << end_date << " - succeed" << std::endl;
        }
        else
        {
            std::cout << "Something went wrong, no action performed" << std::endl;
        }
    };
    sickDay_Callback = [&]
    {
        std::string date{};
        bool c = true;
        do {
            std::cout << "|| Sick Day ||" << std::endl;
            std::cout << "Date (yyyy-mm-dd) : " << std::endl;
            std::cin >> date;
            c = !(validator.is_date(date));
            if (c) {
                std::cout << "Invalid input, please enter again" << std::endl;
            }
        } while(c);
        if (
            auto it = jobs_container.find(current->key());
            it != std::end(jobs_container))
        {
            it->second->CallSickDay(date);
            std::cout << "Sick Day : " << date << " - succeed" << std::endl;
        }
        else
        {
            std::cout << "Something went wrong, no action performed" << std::endl;
        }
    };
    vacation_Callback = [&]
    {
        std::string start_date{};
        std::string end_date{};
        bool c = true;
        do {
            std::cout << "|| Vacations ||" << std::endl;
            std::cout << "Start Date (yyyy-mm-dd) : " << std::endl;
            std::cin >> start_date;
            std::cout << "End Date (yyyy-mm-dd) : " << std::endl;
            std::cin >> end_date;
            c = !(validator.is_date(start_date) && validator.is_date(end_date));
            if (c) {
                std::cout << "Invalid input, please enter again" << std::endl;
            }
        } while(c);
        if (
            auto it = jobs_container.find(current->key());
            it != std::end(jobs_container))
        {
            it->second->ScheduleVacation(start_date, end_date);
            std::cout << "Vacations : " << start_date << " | " << end_date << " - succeed" << std::endl;
        }
        else
        {
            std::cout << "Something went wrong, no action performed" << std::endl;
        }
    };
    report_Callback = [&]
    {
        if (
            auto it = jobs_container.find(current->key());
            it != std::end(jobs_container))
        {
            std::cout << "Calling Report on empty" << std::endl;
            try {
                std::cout << it->second->Report() << std::endl;
            } catch (const std::out_of_range & e)
            {
                std::cout << "No registers found!" << std::endl;
            }
        }
        else
        {
            std::cout << "Something went wrong, no action performed" << std::endl;
        }
    };
    add_developer_Callback = [&]
    {
        std::string id{};
        std::cout << "Please enter the worker id : " << std::endl;
        std::cin >> id;

        jobs_container.insert(std::pair(id, new Developer(id)));
        addJobMenu(id);
    };
    add_pilot_Callback = [&]
    {
        std::string id{};
        std::cout << "Please enter the worker id" << std::endl;
        std::cin >> id;
        jobs_container.insert(std::pair(id, new Pilot(id)));
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
    previous = new Item([]{}, "Return", "r");
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
