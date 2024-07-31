#include "EventController.h"

#include "Event.h"

auto EventController::FindEventByName(std::string &name) {
    return std::find_if(events_.begin(), events_.end(),
       [&name](const std::unique_ptr<Event>& event) {
           return event->GetName() == name;
       });

}

EventController::~EventController() {
    stop_event_reminder_ = false;
}

EventController::EventController():
    date_(std::make_unique<Date>()),file_manager_(std::make_unique<FileManager>()),stop_event_reminder_(true)
{
    date_->SetCurrentDate();
}
//Working with files
void EventController::ReadFromFile() {
    std::string folder = R"(D:\C++\Course_Project_Final_Final\Events\)";
    file_manager_->ReadFromFile<Event>(folder,date_->GetDate(),events_);
}

void EventController::ReadFromFile(std::list<std::unique_ptr<Event> > &events, const std::string& date_name) const {
    std::string folder = R"(D:\C++\Course_Project_Final_Final\Events\)";
    file_manager_->ReadFromFile<Event>(folder,date_name,events);
}

void EventController::AppendToFile(const std::string& date_name, Event &event) const {
    std::string folder = R"(D:\C++\Course_Project_Final_Final\Events\)";
    file_manager_->AppendToFile<Event>(folder,date_name,event);
}

void EventController::WriteToFile() {
    std::string folder = R"(D:\C++\Course_Project_Final_Final\Events\)";
    file_manager_->WriteToFile<Event>(folder,date_->GetDate(),events_);
}

void EventController::AppendToFile(Event &event) const {
    std::string folder = R"(D:\C++\Course_Project_Final_Final\Events\)";
    file_manager_->AppendToFile<Event>(folder,date_->GetDate(),event);
}
//CRUD operations
void EventController::Add() {
    std::string name, venue, people;
    int priority;

    // Get event name
    std::cout << "Enter name of the event(name must be unique):\n";
    while (true) {
        //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, name);
        if(name.empty()) {
            std::cerr << "You must fill this field\n";
            continue;
        }
        if (CheckUniqueName(name, events_))
            break;
        else {
            std::cerr << "The name must be unique. Please try to choose a new name.\n";
        }
    }

    // Get venue
    std::cout << "Enter venue of the event:\n";
    std::getline(std::cin, venue);

    // Get people
    while (true) {
        std::cout << "Enter people or person you will meet:\n";
        std::getline(std::cin, people);
        if (!name.empty()) {
            break;
        }else
            std::cerr << "You must fill this field\n";
    }
    // Get start time
    std::cout << "What time does it start:\n";
    Time time;
    time.SetTime();
    if (!events_.empty()) {
        while (!CheckTime(time, events_)) {
            std::cout << "The time is already occupied.\nHere is your free time:\n";
            //showFreeTime();
            std::cout << "Press 0 to continue with that time\nPress 1 to set another time\n";
            int choice = GetUserChoice({0, 1});
            if (choice == 1) {
                time.SetTime();
            } else {
                break;
            }
        }
    }

    // Get duration
    std::cout << "Enter the duration of event (in minutes):\n";
    int duration = GetValidIntegerInput();

    // Get priority
    std::cout << "Enter the priority from 1 to 5:\n";
    while (true) {
        priority = GetValidIntegerInput();
        if (priority >= 1 && priority <= 5)
            break;
        else
            std::cerr << "Priority must be in the range from 1 to 5. Please enter again.\n";
    }

    // Create and add the event
    std::unique_ptr<Event> event = std::make_unique<Event>(name, time, duration, priority, venue, people);
    events_.emplace_back(std::move(event));
    std::cout << "Event was added successfully\n";
}

void EventController::Edit() {
    std::string event_name;
    std::cout << "Enter name of the event, you would like to change: \n";
   // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, event_name);

    auto it = FindEventByName(event_name);

    if (it != events_.end()) {
        std::string new_name;
        std::string new_place;
        std::string new_person;
        int new_priority;
        Time new_time;
        int new_duration;

        int choice;

        // Name
        while (true) {
            try {
                std::cout << "Current name is: " << it->get()->GetName() << "\n";
                std::cout << "Press 1 if you want to change the name \n";
                std::cout << "Press 0 to leave as it is \n";
                choice = GetValidIntegerInput();
                //std::cin.ignore(); // Ignore leftover newline character
                if (choice == 0)
                    break;
                if (choice == 1) {
                    std::cout << "Enter new name(Name must be unique): ";
                    std::getline(std::cin, new_name);
                    break;
                } else {
                    std::cerr << "No such option, please be more attentive\n";
                }
            } catch (const std::exception &e) {
                std::cerr << "An error occurred: " << e.what() << "\n";
            }
        }

        // Place
        while (true) {
            try {
                std::cout << "Current place is: " << it->get()->GetPlace() << "\n";
                std::cout << "Press 1 if you want to change the place \n";
                std::cout << "Press 0 to leave as it is \n";
                choice = GetValidIntegerInput();
               // std::cin.ignore(); // Ignore leftover newline character
                if (choice == 0) {
                    new_place = it->get()->GetPlace();
                    break;
                }
                if (choice == 1) {
                    std::cout << "Enter new place: ";
                    std::getline(std::cin, new_place);
                    break;
                } else {
                    std::cerr << "No such option, please be more attentive\n";
                }
            } catch (const std::exception &e) {
                std::cerr << "An error occurred: " << e.what() << "\n";
            }
        }

        // Person
        while (true) {
            try {
                std::cout << "Current people or person is: " << it->get()->GetPeopleToMeet() << "\n";
                std::cout << "Press 1 if you want to change the people(person) \n";
                std::cout << "Press 0 to leave as it is \n";
                choice = GetValidIntegerInput();
                //std::cin.ignore(); // Ignore leftover newline character
                if (choice == 0) {
                    new_person = it->get()->GetPeopleToMeet();
                    break;
                }
                if (choice == 1) {
                    std::cout << "Enter new people(person): ";
                    std::getline(std::cin, new_person);
                    break;
                } else {
                    std::cerr << "No such option, please be more attentive\n";
                }
            } catch (const std::exception &e) {
                std::cerr << "An error occurred: " << e.what() << "\n";
            }
        }

        // Priority
        while (true) {
            try {
                std::cout << "Current priority is: " << it->get()->GetPriority() << "\n";
                std::cout << "Press 1 if you want to change the priority \n";
                std::cout << "Press 0 to leave as it is \n";
                choice = GetValidIntegerInput();
                //std::cin.ignore(); // Ignore leftover newline character
                if (choice == 0) {
                    new_priority = it->get()->GetPriority();
                    break;
                }
                if (choice == 1) {
                    std::cout << "Enter new priority: ";
                    std::cin >> new_priority;
                    if (new_priority < 0 || new_priority > 5) {
                        throw std::out_of_range("Priority must be between 0 and 5");
                    }
                    break;
                } else {
                    std::cerr << "No such option, please be more attentive\n";
                }
            } catch (const std::exception &e) {
                std::cerr << "An error occurred: " << e.what() << "\n";
                std::cin.clear(); // Clear any error flags
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore leftover input
            }
        }

        // Time
        while (true) {
            try {
                std::cout << "Current arranged time for the event: " << it->get()->GetTime().GetTime() << "\n";
                std::cout << "Press 1 if you want to change the time \n";
                std::cout << "Press 0 to leave as it is \n";
                std::cin.ignore();
                choice = GetValidIntegerInput();
               // std::cin.ignore(); // Ignore leftover newline character
                if (choice == 0) {
                    new_time = it->get()->GetTime();
                    break;
                }
                if (choice == 1) {
                    std::cout << "Enter new time: ";
                    new_time.SetTime();
                    break;
                } else {
                    std::cerr << "No such option, please be more attentive\n";
                }
            } catch (const std::exception &e) {
                std::cerr << "An error occurred: " << e.what() << "\n";
            }
        }

        // Duration
        while (true) {
            try {
                std::cout << "Current duration is: " << it->get()->GetDuration() << "\n";
                std::cout << "Press 1 if you want to change the duration \n";
                std::cout << "Press 0 to leave as it is \n";
                choice = GetValidIntegerInput();
              //  std::cin.ignore(); // Ignore leftover newline character
                if (choice == 0) {
                    new_duration = it->get()->GetDuration();
                    break;
                }
                if (choice == 1) {
                    std::cout << "Enter new duration: ";
                    std::cin >> new_duration;
                    break;
                } else {
                    std::cerr << "No such option, please be more attentive\n";
                }
            } catch (const std::exception &e) {
                std::cerr << "An error occurred: " << e.what() << "\n";
                std::cin.clear(); // Clear any error flags
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore leftover input
            }
        }

        // Apply changes
        try {
            if (!new_name.empty()) it->get()->SetName(new_name);
            if (!new_place.empty()) it->get()->SetPlace(new_place);
            if (!new_person.empty()) it->get()->SetPeopleToMeet(new_person);
            it->get()->SetPriority(new_priority);
            it->get()->SetTime(new_time);
            it->get()->SetDuration(new_duration);
        } catch (const std::exception &e) {
            std::cerr << "Failed to apply changes: " << e.what() << "\n";
        }
        std::cout << "Changes were applied\n";
    } else {
        std::cerr << "Event not found.\n";
    }
}

void EventController::Delete() {
    std::string event_name;
    std::cout << "Enter name of event you would like to delete: \n";
    //std::cin.ignore();
    std::getline(std::cin, event_name);

    auto it = FindEventByName(event_name);

    if (it != events_.end()) {
        std::cout << "Are you sure you want to delete that event? \n";
        while (true) {
            try {
                std::cout << "Press 1 if yes, or 0 to cancel the action\n";
                int choice = GetValidIntegerInput();
                //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore leftover input
                if (choice == 0) {
                    std::cout << "You have canceled deleting \n";
                    break;
                } else if (choice == 1) {
                    events_.erase(it);
                    std::cout << "Event deleted successfully.\n";
                    break;
                } else {
                    std::cerr << "No such option; Please be more attentive\n";
                }
            } catch (const std::exception &e) {
                std::cerr << "An error occurred: " << e.what() << "\n";
                std::cin.clear(); // Clear any error flags
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore leftover input
            }
        }
    } else {
        std::cerr << "No such event \n";
    }
}

void EventController::DeleteAll() {
    std::string folder = R"(D:\C++\Course_Project_Final_Final\Events\)";
    try {
        std::cout << "To delete events press 1\n";
        std::cout << "To cancel press 0\n";

        while (true) {
            int choice = GetValidIntegerInput();

            if (choice == 1) {
                events_.clear();
                std::cout << "Events have been deleted.\n";

                // Delete file with the name of current date
                std::string filename = folder + date_->GetDate() + ".txt";

                if (std::filesystem::exists(filename)) {
                    std::filesystem::remove(filename);
                    std::cout << "File " << filename << " has been deleted.\n";
                } else {
                    std::cerr << "File " << filename << " does not exist.\n";
                }

                break; // Exit the loop after deleting
            } else if (choice == 0) {
                std::cout << "You have canceled the deletion.\n";
                break; // Exit the loop
            } else {
                std::cerr << "No such option. Please be more attentive.\n";
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << "\n";
    } catch (...) {
        std::cerr << "An unknown error occurred.\n";
    }
}

void EventController::DeletePassedEvents() {
    Time now = Time::getCurrentTime();
    std::cout << "To delete passed events enter 1;\n";
    std::cout << "To cancel enter 0;\n";
    std::cout << "Your choice:";
    int choice = GetUserChoice({0,1});
    if (choice == 1) {
        events_.remove_if([&now](const std::unique_ptr<Event>& ev) {
            return ev->GetTime() < now;
        });
        std::cout << "Passed events was deleted successfully\n";
    }
    else
        std::cout << "You've cancelled the deletion\n";

}

void EventController::Reschedule() {

    std::string name_of_event;
    std::cout << "Enter the name of the event you'd like to reschedule: ";
    //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, name_of_event);

    auto it = std::find_if(events_.begin(), events_.end(),
        [&name_of_event](const std::unique_ptr<Event>& t) {
            return (t->GetName() == name_of_event);
        });

    if (it != events_.end()) {
        std::cout << "The event was found.\n";
        Time new_time;
        std::cout << "Current time is: " << it->get()->GetTime().GetTime() << "\n";
        std::cout << "Enter new time:\n";

        while (true) {
            new_time.SetTime();
            if (new_time < Time::getCurrentTime()) {
                std::cerr << "You can't reschedule the event to a past time.\n";
                std::this_thread::sleep_for(std::chrono::microseconds(50));
            } else {
                std::cout << "Press 1 to confirm the changes\n";
                std::cout << "Press 0 to cancel\n";
                int choice = GetValidIntegerInput();
                if (choice == 1) {
                    it->get()->SetTime(new_time);
                    std::cout << "Changes have been applied.\n";
                    break;
                } else if (choice == 0) {
                    std::cout << "You cancelled the changes.\n";
                    break;
                } else {
                    std::cerr << "Invalid option. Please choose 1 to confirm or 0 to cancel.\n";
                }
            }
        }
    } else {
        std::cerr << "No such event found in the database.\n";
    }
}

void EventController::Delay() {
    try {
        std::cout << "To delay a specific event, please enter its name: \n";
        std::string event_name;
        //std::cin.ignore();
        std::getline(std::cin, event_name);

        auto it = FindEventByName(event_name);

        if (it == events_.end()) {
            std::cerr << "No such event name.\n";
            return;
        }

        Date date;
        while (true) {
            if (!(Date::getCurrentDate() == *date_))
                std::cout << "Press 1 to rearrange event for today\n";
            std::cout << "Press 2 to rearrange for another day\n";
            std::cout << "Press 0 to exit\n";

            int choice = GetValidIntegerInput();

            if (choice == 0) {
                break;
            }

            switch (choice) {
                case 1:
                    if (!(Date::getCurrentDate() == *date_))
                        date.SetCurrentDate();
                    else {
                        std::cerr << "This function is unable for todays events\n";
                        continue;
                    }
                break;
                case 2:
                    while (true) {
                        FutureDateValidation(date);
                        if (date < Date::getCurrentDate()) {
                            std::cerr << "You can't rearrange the event to the past, only to the future or now.\n";
                        } else {
                            break;
                        }
                    }
                break;
                default:
                    std::cerr << "No such option. Please be more attentive.\n";
                continue;
            }

            std::string date_name = date.GetDate();
            CheckName(date_name, event_name);
            AppendToFile(date.GetDate(), **it);
            events_.erase(it);
            break;
        }
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << "\n";
    } catch (...) {
        std::cerr << "An unknown error occurred.\n";
    }
}
//Sort methods
void EventController::SortByName() {
    events_.sort(
        [](const std::unique_ptr<Event>& event_1, const std::unique_ptr<Event>& event_2) {
            return (event_1->GetName() > event_2->GetName());
        });
}

void EventController::SortByTime() {
    events_.sort(
        [](const std::unique_ptr<Event>& event_1, const std::unique_ptr<Event>& event_2) {
            return (event_1->GetTime() < event_2->GetTime());
        });
}

void EventController::SortByPriority() {
    events_.sort(
        [](const std::unique_ptr<Event>& event_1, const std::unique_ptr<Event>& event_2) {
            return (event_1->GetPriority() < event_2->GetPriority());
        });
}

void EventController::SortByPeopleToMeet() {
    events_.sort(
       [](const std::unique_ptr<Event>& event_1, const std::unique_ptr<Event>& event_2) {
           return (event_1->GetPeopleToMeet() < event_2->GetPeopleToMeet());
       });
}

//Show methods
void EventController::Show() {
    if (events_.empty()) {
        std::cerr << "\nNo tasks for the current day.\n\n";
        return;
    }

    if (events_.size() > 1) {
        std::cout << "\nWould you like to sort the events?\n";
        std::cout << "1. Yes\n";
        std::cout << "0. No\n";
        std::cout << "Your choice:";
        int choice = GetUserChoice({1, 0});
        if (choice == 1) {
            std::cout << "\nSort by:\n";
            std::cout << "1. Name\n";
            std::cout << "2. Priority\n";
            std::cout << "3. Time\n";
            std::cout << "4. People to Meet\n";
            std::cout << "Your choice:";
            choice = GetUserChoice({1, 2, 3, 4});
            switch (choice) {
                case 1:
                    SortByName();
                break;
                case 2:
                    SortByPriority();
                break;
                case 3:
                    SortByTime();
                break;
                case 4:
                    SortByPeopleToMeet();
                break;
                default:
                    std::cerr << "Invalid choice. Please try again.\n";
            }
        }
    }

    tabulate::Table table;
    table.add_row({"Name", "Place", "Priority", "People", "Start at", "Duration"});
    for (int i = 0; i < 6; i++) {
        table[0][i].format().font_color(tabulate::Color::cyan)
                             .font_style({tabulate::FontStyle::bold});
    }

    for (const auto& event : events_) {
        table.add_row({
            event->GetName(),
            event->GetPlace(),
            std::to_string(event->GetPriority()),
            event->GetPeopleToMeet(),
            event->GetTime().GetTime(),
            std::to_string(event->GetDuration())
        });
    }

    std::cout << "\n" << table << "\n\n";
}

void EventController::PrintMenu() {
    tabulate::Table table;
        table.add_row({"Press","To..."});
        table.add_row({"0","Exit to Events menu"});
        table.add_row({"1","To add the Event"});
        table[0][0].format().font_color(tabulate::Color::magenta);
        table[0][1].format().font_color(tabulate::Color::magenta);
        if (events_.empty()) {
            std::cout << "-------------------------------------------------------\n";
            std::cout << "           Nothing was arranged\n";
            std::cout << "-------------------------------------------------------\n";
            std::cout << table << "\n";
        }else {
            table.add_row({"2","Edit the Event by name"});
            table.add_row({"3","Delete the Event by name"});
            table.add_row({"4","Show event table"});
            table.add_row({"5","Change time for the Event"});
            table.add_row({"6","Analyze conflicts"});
            if (*date_ ==  Date::getCurrentDate()) {
                table.add_row({"7","Delete Passed Events"});
            }
            table.add_row({"8","See if the time is free"});
            table.add_row({"9","Change the date for event"});
            table.add_row({"10","Delete all events"});
            std::cout << table << "\n";
        }
}

void EventController::AnalyzeConflicts() {
    SortByTime();

    tabulate::Table table;
    table.add_row({"Name", "Place", "Priority", "People", "Start at", "Duration"});
    for (int i = 0; i < 6; i++) {
        table[0][i].format().font_color(tabulate::Color::blue);
    }

    auto it = events_.begin();
    int rowIndex = 1;
    std::vector<int> conflictRows;

    while (it != events_.end()) {
        table.add_row({
            it->get()->GetName(),
            it->get()->GetPlace(),
            std::to_string(it->get()->GetPriority()),
            it->get()->GetPeopleToMeet(),
            it->get()->GetTime().GetTime(),
            std::to_string(it->get()->GetDuration()),
        });

        auto currentTaskEnd = it->get()->GetTime().addMinutes(it->get()->GetDuration());

        auto next = std::next(it);
        while (next != events_.end()) {
            auto nextTaskStart = next->get()->GetTime();
            auto nextTaskEnd = nextTaskStart.addMinutes(next->get()->GetDuration());

            if (nextTaskStart < currentTaskEnd) {
                conflictRows.push_back(rowIndex);
                conflictRows.push_back(rowIndex + 1);
            }

            if (nextTaskEnd > currentTaskEnd) {
                break;
            }

            ++next;
        }

        ++it;
        ++rowIndex;
    }

    // Color conflict rows red
    for (int i : conflictRows) {
        for (int j = 0; j < 6; j++) {
            table[i][j].format().font_color(tabulate::Color::red);
        }
    }

    std::cout << table << "\n";
}

//Execution methods
void EventController::ExecuteChoice(int choice) {
    switch (choice) {
        case 1:
            Add();
        break;
        case 2:
            Edit();
        break;
        case 3:
            Delete();
        break;
        case 4:
            Show();
        break;
        case 5:
            Reschedule();
        break;
        case 6:
            AnalyzeConflicts();
        break;
        case 7:
            if (*date_ == Date::getCurrentDate())
                DeletePassedEvents();
            else
                std::cerr << "Out of range option\n";
        break;
        case 8:
            CheckHour();
        break;
        case 9:
            Delay();
        break;
        case 10:
            DeleteAll();
            break;
        default:
            std::cerr <<  "Out of range option";
    }
}

void EventController::Execution() {
    while(true) {
        //EventReminder();
        std::cout << "Loading...\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));
        PrintMenu();
        if (events_.empty()) {
            std::cout << "Your choice is: ";
            int choice = GetUserChoice({0,1});
            if (choice == 0)
                break;
            else if(choice == 1) {
                Add();
            }
        }else {
            //PrintMenu();
            std::cout << "Your choice is: ";
            std::vector<int> choices = {0,1,2,3,4,5,6,7,8,9,11,12,13};
            if (*date_ == Date::getCurrentDate())
                choices.push_back(10);
            int choice = GetUserChoice(choices);
            if (choice == 0)
                break;
            ExecuteChoice(choice);

        }
        WriteToFile();
    }
}

void EventController::CheckName(std::string &date, std::string &event_name) {
    std::list<std::unique_ptr<Event>> events;
    ReadFromFile(events, date);

    while (!CheckUniqueName(event_name, events)) {
        std::cout << "It seems that there is a event with the same name.\n";
        std::cout << "Rename this event.\n";

        std::cout << "Enter name: ";
        std::getline(std::cin, event_name);

        if (!CheckUniqueName(event_name, events)) {
            std::cout << "You can't enter this name either. Please make it unique.\n";
        }
    }
}

void EventController::CheckHour() {
    std::unique_ptr<Time> time = std::make_unique<Time>();
    std::cout << "Enter the time you would like to check\n";
    time->SetTime();
    auto it = std::find_if(events_.begin(),events_.end(),
        [&time](const std::unique_ptr<Event> &ev) {
            return(*time > ev->GetTime() && *time < ev->GetTime().addMinutes(ev->GetDuration()));
        });
    if (it != events_.end()) {
        std::cout << "The time is already occupied by:\n";
        it->get()->ShowTask();
    }else {
        std::cout << "This time is free\n";
    }
}

//Handling events
void EventController::HandleTodaysEvents() {
   // EventReminder();
    ReadFromFile();
    std::cout << "-------------------------------------------------------\n";
    std::cout << "                    Todays Events \n";
    std::cout << "-------------------------------------------------------\n";
    Execution();
    WriteToFile();
}

void EventController::HandleFutureEvents() {
   // EventReminder();
    ReadFromFile();
    std::cout << "-------------------------------------------------------\n";
    std::cout << "                    Future Events \n";
    std::cout << "-------------------------------------------------------\n";
    std::cout << "Date: " << date_->GetDate() << "\n";
    Execution();
    WriteToFile();
}

void EventController::HandleYesterdaysEvents() {
    //EventReminder();
        ReadFromFile();
        std::cout << "-------------------------------------------------------\n";
        std::cout << "                    Yesterday Events \n";
        std::cout << "-------------------------------------------------------\n";
        std::cout << "Date: " << date_->GetDate() << "\n";

        while(true) {
            if(events_.empty()) {
                std::cout << "Nothing had been arranged for yesterday.Or you have already dealt with that\n";
                return;
            }
            Show();
            tabulate::Table table;
            table.add_row({"Press:","To..."});

            table[0][0].format().font_color(tabulate::Color::magenta);
            table[0][1].format().font_color(tabulate::Color::magenta);

            table.add_row({"0","Exit"});
            table.add_row({"1","Delete all Events"});
            table.add_row({"2","Reschedule Event for another day by specific name"});

            std::cout << table <<"\n";
            std::cout << "Your choice: ";
            int choice = GetUserChoice({0,1,2});
            if (choice == 0)
                break;
            switch (choice) {
                case 1:
                    DeleteAll();
                break;
                case 2:
                    Delay();
                WriteToFile();
                break;
                default:
                    std::cerr << "Out of range option\n";
            }
        }
}
//Event reminder
void EventController::EventReminder() {
    std::string folder = R"(D:\C++\Course_Project_Final_Final\Events\)";

        std::list<std::unique_ptr<Event>> events;
        Date date;
        date.SetCurrentDate();
        file_manager_->ReadFromFile<Event>(folder,date.GetDate(),events);
        Time current_time;
        current_time.SetCurrentTime();
        auto it = std::find_if(events.begin(),events.end(),
            [&current_time](const std::unique_ptr<Event> &ev) {
                return(current_time > ev->GetTime().addMinutes(-5) && current_time < ev->GetTime());

            });
        if (it != events.end()) {
           // std::lock_guard<std::mutex> lock(mutex_);
            tabulate::Table ev_table = it->get()->GetEventTable();
            std::stringstream ss;
            ss << ev_table;

            // Convert the stringstream to a std::string
            std::string table_string = ss.str();
            MessageBox(NULL,table_string.c_str(),"Event Reminder",MB_OK);
        }


}

void EventController::StartEventReminder() {
    reminder_thread_ = std::thread([this]() {
        while (stop_event_reminder_) {
            EventReminder();
            std::this_thread::sleep_for(std::chrono::seconds(30));
        }
    });
}

//Main function
void EventController::Run() {
    StartEventReminder();
    std::cout << "=======================================================\n";
    std::cout << "                    Events manager \n";
    std::cout << "=======================================================\n";
    while (true) {
        //EventReminder();
        std::cout << "---------------------\n";
        std::cout << "    Main menu: \n";
        std::cout << "=====================\n";

        tabulate::Table table;

        table.add_row({"Press","To..."});
        table[0][0].format().font_color(tabulate::Color::yellow);
        table[0][1].format().font_color(tabulate::Color::yellow);

        table.add_row({"0","Exit"});
        table.add_row({"1","See todays events"});
        table.add_row({"2","See future arranged events"});
        table.add_row({"3","See yesterdays events"});
        std::cout << table << "\n";
        std::cout << "Your choice is: ";
        int choice = GetUserChoice({0,1,2,3});
        if (choice == 0) {
            std::cout << "Bye,bye\n";
            break;
        }
        switch (choice) {
            case 1:
                date_->SetCurrentDate();
            HandleTodaysEvents();
            break;
            case 2:
                FutureDateValidation(*date_);
            HandleFutureEvents();
            break;
            case 3:
                date_->SetYesterdayDay();
            HandleYesterdaysEvents();
            break;
            default:
                std::cerr << "Out of range option\n";
        }
        events_.clear();
    }
}
