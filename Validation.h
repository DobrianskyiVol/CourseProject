#ifndef VALIDATION_H
#define VALIDATION_H
#include <memory>
#include <iostream>
#include <vector>
#include<algorithm>
#include<list>
#include"Date.h"
#include "Task.h"

inline int GetValidIntegerInput() {
    while (true) {
        std::string input;
        std::getline(std::cin, input);
        try {
            return std::stoi(input);
        } catch (const std::invalid_argument &) {
            std::cerr << "Invalid input. Please enter a number.\n";
        }
    }
}

inline void FutureDateValidation(Date &date) {
    while (true) {
        date.SetDate();
        if (date < Date::getCurrentDate() || date == Date::getCurrentDate()) {
            std::cerr << "You have entered past or todays date. Please try again.\n";
            continue;
        }
        break;

    }
}

inline int GetUserChoice(const std::vector<int> &validChoices) {
    while (true) {
        std::string input;
        std::getline(std::cin, input);
        try {
            int choice = std::stoi(input);
            if (std::find(validChoices.begin(), validChoices.end(), choice) != validChoices.end()) {
                return choice;
            } else {
                std::cerr << "Invalid choice. Please select a valid option.\n";
            }
        } catch (const std::invalid_argument &) {
            std::cerr << "Invalid input. Please enter a number.\n";
        }
    }
}

inline bool CheckUniqueName(std::string &name,std::list<std::unique_ptr<Task>> &tasks) {
    bool unique = std::all_of(tasks.begin(), tasks.end(),
                              [&name](const std::unique_ptr<Task>& event) {
                                  return event->GetName() != name;
                              });
    return unique;
}

inline bool CheckTime(Time &time,std::list<std::unique_ptr<Task>> &tasks) {
    bool isOnTheTasks = std::none_of(tasks.begin(), tasks.end(),
        [&time](const std::unique_ptr<Task>& event) {
            return (time == event->GetTime()) ||
                (time < event->GetTime().addMinutes(event->GetDuration()) &&
                    time > event->GetTime());
        });
    return isOnTheTasks;
}
#endif //VALIDATION_H
