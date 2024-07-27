#include "EventController.h"
#include"TaskController.h"
#include "tabulate/single_include/tabulate/tabulate.hpp"
#include "Validation.h"
#include <iostream>

void Run() {
    TaskController task_controller;
    EventController event_controller;
    std::cout << "=======================================================\n";
    std::cout << "      Welcome to your daily events/tasks manager";
    std::cout << "=======================================================\n";
    std::cout << "-------------------------------------------------------\n";
    std::cout << "                        Main menu                       ";
    std::cout << "-------------------------------------------------------\n";
    while (true) {
        tabulate::Table table;
        table.add_row({"Press","To..."});
        table.add_row({"0","Exit"});
        table.add_row({"1","Go to tasks"});
        table.add_row({"2","Go to events"});
        table.add_row({"3","See users instruction"});
        std::cout << table << "\n";
        std::cout << "Your choice is:";
        int choice = GetValidIntegerInput();
        if (choice == 0) {
            break;
        }
        switch (choice) {
            case 1:
                task_controller.Run();
                break;
            case 2:
                event_controller.Run();
                break;
            case 3:
                std::cout << "Users manual book in files\n";
                break;
            default:
                std::cerr << "Out of range option\n";
        }
    }
}

int main()
{
    Run();
    return 0;
}
