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
template<typename T>
bool CheckUniqueName(std::string &name,std::list<std::unique_ptr<T>> &items) {
    bool unique = std::all_of(items.begin(), items.end(),
                              [&name](const std::unique_ptr<T>& item) {
                                  return item->GetName() != name;
                              });
    return unique;
}
template<typename T>
bool CheckTime(Time &time,std::list<std::unique_ptr<T>> &items) {
    bool isOnTheTasks = std::none_of(items.begin(), items.end(),
        [&time](const std::unique_ptr<T>& item) {
            return (time == item->GetTime()) ||
                (time < item->GetTime().addMinutes(item->GetDuration()) &&
                    time > item->GetTime());
        });
    return isOnTheTasks;
}
#endif //VALIDATION_H
