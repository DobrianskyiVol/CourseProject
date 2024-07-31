#include "EventController.h"
#include "tabulate/single_include/tabulate/tabulate.hpp"
#include "Validation.h"
#include <iostream>


void Run() {
    EventController event_controller;
    std::cout << "=======================================================\n";
    std::cout << "      Welcome to your daily events manager\n";
    std::cout << "=======================================================\n";
    std::cout << "-------------------------------------------------------\n";
    std::cout << "                        Main menu                      \n";
    std::cout << "-------------------------------------------------------\n";
    while (true) {
        tabulate::Table table;
        table.add_row({"Press","To..."});
        table[0][0].format().font_color(tabulate::Color::green);
        table[0][1].format().font_color(tabulate::Color::green);
        table.add_row({"0","Exit"});
        table.add_row({"1","Go to events"});
        table.add_row({"2","See users instruction"});
        std::cout << table << "\n";
        std::cout << "Your choice is:";
        int choice = GetValidIntegerInput();
        if (choice == 0) {
            break;
        }
        switch (choice) {
            case 1:
                event_controller.Run();
                break;
            case 2:
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
