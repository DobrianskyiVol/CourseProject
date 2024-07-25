#include "TaskController.h"

#include <thread>

TaskController::TaskController():date_(std::make_unique<Date>()) {
    date_->SetCurrentDate();
}

//Working with files
void TaskController::ReadFromFile() {
    std::string folder = R"(D:\C++\Course_Project_Final_Final\Tasks\)";
    std::string nameoffile = (folder  +  date_->GetDate() + ".txt");
    std::ifstream of(nameoffile);
    if (!of) {
        //std::cout << "No events for current day\n";
        return;
    }

    while (!of.eof()) {
        std::unique_ptr<Task> task = std::make_unique<Task>();
        of >> *task;
        if (task->GetPriority() == 0)
            break;
        tasks_.emplace_back(std::move(task));
    }
    of.close();
}

void TaskController::ReadFromFile(std::list<std::unique_ptr<Task>> &tasks,std::string date_name) {
    std::string folder = R"(D:\C++\Course_Project_Final_Final\Tasks\)";
    std::string nameoffile = (folder  +  date_name + ".txt");
    std::ifstream of(nameoffile);
    if (!of) {
        //std::cout << "No events for current day\n";
        return;
    }

    while (!of.eof()) {
        std::unique_ptr<Task> task = std::make_unique<Task>();
        of >> *task;
        if (task->GetPriority() == 0)
            break;
        tasks.emplace_back(std::move(task));
    }
    of.close();
}

void TaskController::WriteToFile() {
    std::string folder = R"(D:\C++\Course_Project_Final_Final\Tasks\)";
    std::string nameoffile = (folder  +  date_->GetDate() + ".txt");
    std::ofstream of(nameoffile);
    if (!of) {
        std::cerr << "Error opening file: " << nameoffile << std::endl;
        return;
    }
    if (!tasks_.empty()) {
        std::for_each(tasks_.begin(), tasks_.end(), [&of](const std::unique_ptr<Task> &event) {
            of << *event;
        });
    }
    of.close();
}

void TaskController::AppendToFile(Task *task) {
    std::string folder = R"(D:\C++\Course_Project_Final_Final\Tasks\)";
    std::string nameoffile = (folder  +  date_->GetDate() + ".txt");
    std::ofstream of(nameoffile,std::ios::app);
    if (!of) {
        std::cerr << "Error opening file: " << nameoffile << std::endl;
        return;
    }
    of << *task;

    of.close();
}

void TaskController::AppendToFile(std::string date_name, Task *task) {
    std::string folder = R"(D:\C++\Course_Project_Final_Final\Tasks\)";
    std::string nameoffile = (folder  +  date_name + ".txt");
    std::ofstream of(nameoffile,std::ios::app);
    if (!of) {
        std::cerr << "Error opening file: " << nameoffile << std::endl;
        return;
    }else
        of << *task;
    of.close();
}

//CRUD operations
void TaskController::Add() {
    std::string name;
    std::unique_ptr<Time> time = std::make_unique<Time>();
    //Name
    std::cout << "Enter name of the event(name must be unique):\n";
    while (true) {
        //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, name);
        if (CheckUniqueName(name,tasks_))
            break;
        else {
            std::cout << "The name must be unique. Please try to choose a new name.\n";
        }
    }
    //Time
    std::cout << "What time does it start:\n";

    time->SetTime();
    if (!tasks_.empty()) {
        while (!CheckTime(*time,tasks_)) {
            std::cout << "The time is already occupied.\n";
            std::cout << "Press 0 to continue with that time\nPress 1 to set another time\n";
            int choice = GetUserChoice({0, 1});
            if (choice == 1) {
                time->SetTime();
            } else {
                break;
            }
        }
    }
    //Duration
    std::cout << "Enter the duration of event (in minutes):\n";
     int duration = GetValidIntegerInput();
    int priority;
    std::cout << "Enter the priority from 1 to 5:\n";
    while (true) {
        priority = GetValidIntegerInput();
        if (priority >= 1 && priority <= 5)
            break;
        else
            std::cerr << "Priority must be in the range from 1 to 5. Please enter again.\n";
    }

    std::unique_ptr<Task> task = std::make_unique<Task>(name,*time,duration,priority);
    AppendToFile(&*task);
    std::cout << "Task was added successfully\n";
    tasks_.emplace_back(std::move(task));
}

void TaskController::Edit() {
    std::string event_name;
    std::cout << "Enter name of the event, you would like to change: \n";
    std::getline(std::cin, event_name);

    auto it = std::find_if(tasks_.begin(), tasks_.end(),
        [&event_name](const std::unique_ptr<Task>& event) {
            return event->GetName() == event_name;
        });

    if (it != tasks_.end()) {
        std::string new_name;
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
                    new_priority = GetValidIntegerInput();
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
                    new_duration = GetValidIntegerInput();
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
            it->get()->SetPriority(new_priority);
            it->get()->SetTime(new_time);
            it->get()->SetDuration(new_duration);
        } catch (const std::exception &e) {
            std::cerr << "Failed to apply changes: " << e.what() << "\n";
        }
        std::cout << "Changes was applied successfully\n";
    } else {
        std::cerr << "Event not found.\n";
    }

}

void TaskController::Delete() {
    std::string event_name;
    std::cout << "Enter name of event you would like to delete: \n";
    //std::cin.ignore();
    std::getline(std::cin, event_name);

    auto it = std::find_if(tasks_.begin(), tasks_.end(),
        [&event_name](const std::unique_ptr<Task>& event) {
            return event->GetName() == event_name;
        });

    if (it != tasks_.end()) {
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
                    tasks_.erase(it);
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

void TaskController::DeleteAll() {
    try {
        std::cout << "To delete tasks press 1\n";
        std::cout << "To cancel press 0\n";

        while (true) {
            int choice = GetValidIntegerInput();

            // Check for invalid input

            //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear newline character

            if (choice == 1) {
                tasks_.clear();
                std::cout << "Yesterday's tasks have been deleted.\n";

                // Delete file with the name of current date
                std::string folder = R"(D:\C++\Course_Project_Final_Final\Tasks\)";
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

void TaskController::Reschedule() {

        std::string name_of_task;
        std::cout << "Enter the name of the task you'd like to reschedule: ";
        //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, name_of_task);

        auto it = std::find_if(tasks_.begin(), tasks_.end(),
            [&name_of_task](const std::unique_ptr<Task>& t) {
                return (t->GetName() == name_of_task);
            });

        if (it != tasks_.end()) {
            std::cout << "The task was found.\n";
            Time new_time;
            std::cout << "Current time is: " << it->get()->GetTime().GetTime() << "\n";
            std::cout << "Enter new time:\n";

            while (true) {
                new_time.SetTime();
                if (new_time < Time::getCurrentTime()) {
                    std::cerr << "You can't reschedule the task to a past time.\n";
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

void TaskController::CheckName(std::string &date, std::string &task_name) {
    std::list<std::unique_ptr<Task>> tasks;
    ReadFromFile(tasks, date);

    while (!CheckUniqueName(task_name, tasks)) {
        std::cout << "It seems that there is a task with the same name.\n";
        std::cout << "Rename this task.\n";

        std::cout << "Enter name: ";
        std::getline(std::cin, task_name);

        if (!CheckUniqueName(task_name, tasks)) {
            std::cout << "You can't enter this name either. Please make it unique.\n";
        }
    }
}

void TaskController::Delay() {
    try {
        std::cout << "To delay a specific task, please enter its name: \n";
        std::string task_name;
        //std::cin.ignore();
        std::getline(std::cin, task_name);

        auto it = std::find_if(tasks_.begin(), tasks_.end(),
            [&task_name](const std::unique_ptr<Task>& task) {
                return task->GetName() == task_name;
            });

        if (it == tasks_.end()) {
            std::cerr << "No such task name.\n";
            return;
        }

        Date date;
        while (true) {
            std::cout << "Press 1 to rearrange event for today\n";
            std::cout << "Press 2 to rearrange for another day\n";
            std::cout << "Press 0 to exit\n";

            int choice = GetValidIntegerInput();

            if (choice == 0) {
                break;
            }

            switch (choice) {
                case 1:
                    date.SetCurrentDate();
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
            CheckName(date_name, task_name);
            AppendToFile(date.GetDate(), it->get());
            tasks_.erase(it);
            break;
        }
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << "\n";
    } catch (...) {
        std::cerr << "An unknown error occurred.\n";
    }
}

//Sort operations
void TaskController::SortByName() {
    tasks_.sort(
        [](const std::unique_ptr<Task>& task_1, const std::unique_ptr<Task>& task_2) {
            return (task_1->GetName() > task_2->GetName());
        });
}

void TaskController::SortByPriority() {
    tasks_.sort(
        [](const std::unique_ptr<Task>& task_1, const std::unique_ptr<Task>& task_2) {
            return (task_1->GetPriority() < task_2->GetPriority());
        });
}

void TaskController::SortByTime() {
    tasks_.sort(
        [](const std::unique_ptr<Task>& task_1, const std::unique_ptr<Task>& task_2) {
            return (task_1->GetTime() < task_2->GetTime());
        });
}

//Show
void TaskController::Show() {
    if (tasks_.empty()) {
        std::cerr << "No tasks for current day\n";
        return;
    }

    tabulate::Table table;
    table.add_row({"Name", "Start at", "Duration", "Priority"});
    for (int i = 0; i < 4; i++) {
        table[0][i].format().font_color(tabulate::Color::blue);
    }

    std::for_each(tasks_.begin(), tasks_.end(), [&table](const std::unique_ptr<Task>& task) {
        table.add_row({
            task->GetName(),
            task->GetTime().GetTime(),
            std::to_string(task->GetDuration()),
            std::to_string(task->GetPriority()),
        });
    });

    std::cout << table << std::endl;
}

void TaskController::PrintMenu() {
    tabulate::Table table;
    table.add_row({"Press","To..."});
    table.add_row({"0","Exit to tasks menu"});
    table.add_row({"1","To add the task"});
    table[0][0].format().font_color(tabulate::Color::blue);
    table[0][1].format().font_color(tabulate::Color::blue);
    if (tasks_.empty()) {
        std::cout << "-------------------------------------------------------\n";
        std::cout << "           Nothing was arranged\n";
        std::cout << "-------------------------------------------------------\n";
        std::cout << table << "\n";
    }else {
        table.add_row({"2","Edit the task by name"});
        table.add_row({"3","Delete the task by name"});
        table.add_row({"4","Sort the tasks by Name"});
        table.add_row({"5","Sort the tasks by Time"});
        table.add_row({"6","Sort the tasks by Priority"});
        table.add_row({"7","Reschedule the task by name"});
        table.add_row({"8","Analyze conflicts"});
        table.add_row({"9","See the tasks"});
        std::cout << table << "\n";
    }
}

void TaskController::AnalyzeConflicts() {
    SortByTime();

    tabulate::Table table;
    table.add_row({"Name", "Start at", "Duration", "Priority"});
    for (int i = 0; i < 4; i++) {
        table[0][i].format().font_color(tabulate::Color::blue);
    }

    auto it = tasks_.begin();
    int rowIndex = 1;
    std::vector<int> conflictRows;

    while (it != tasks_.end()) {
        table.add_row({
            it->get()->GetName(),
            it->get()->GetTime().GetTime(),
            std::to_string(it->get()->GetDuration()),
            std::to_string(it->get()->GetPriority())
        });

        auto currentTaskEnd = it->get()->GetTime().addMinutes(it->get()->GetDuration());

        auto next = std::next(it);
        while (next != tasks_.end()) {
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
        for (int j = 0; j < 4; j++) {
            table[i][j].format().font_color(tabulate::Color::red);
        }
    }

    std::cout << table << "\n";
}


//Execute
void TaskController::ExecuteChoice(int choice) {
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
              SortByName();
            Show();
          break;
          case 5:
              SortByTime();
          break;
          case 6:
              SortByPriority();
          break;
          case 7:
              Reschedule();
          break;
          case 8:
              AnalyzeConflicts();
              break;
          case 9:
              Show();
          break;
          default:
              std::cerr <<  "Out of range option";
      }
}

void TaskController::Execution() {
    while(true) {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        PrintMenu();
        if (tasks_.empty()) {
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
            int choice = GetUserChoice({0,1,2,3,4,5,6,7,8,9});
            if (choice == 0)
                break;
            ExecuteChoice(choice);

        }
    }
}

//Handle Events Method
void TaskController::HandleTodaysEvents() {
    ReadFromFile();
    std::cout << "-------------------------------------------------------\n";
    std::cout << "                    Todays Tasks \n";
    std::cout << "-------------------------------------------------------\n";
    Execution();
    WriteToFile();
}

void TaskController::HandleFutureEvents() {
    ReadFromFile();
    std::cout << "-------------------------------------------------------\n";
    std::cout << "                    Future Tasks \n";
    std::cout << "-------------------------------------------------------\n";
    std::cout << "Date: " << date_->GetDate() << "\n";
    Execution();
    WriteToFile();
}

void TaskController::HandleYesterdaysEvents() {
    ReadFromFile();
    std::cout << "-------------------------------------------------------\n";
    std::cout << "                    Yesterday Tasks \n";
    std::cout << "-------------------------------------------------------\n";
    std::cout << "Date: " << date_->GetDate() << "\n";

    while(true) {
        if(tasks_.empty()) {
            std::cout << "Nothing had been arranged for yesterday.Or you have already dealt with that\n";
            return;
        }
        Show();
        tabulate::Table table;
        table.add_row({"Press:","To..."});

        table[0][0].format().font_color(tabulate::Color::blue);
        table[0][1].format().font_color(tabulate::Color::blue);

        table.add_row({"0","Exit"});
        table.add_row({"1","Delete all tasks"});
        table.add_row({"2","Reschedule task for another day by specific name"});

        std::cout << table <<"\n";
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
    //WriteToFile();


//Execution Method
void TaskController::Run() {
    std::cout << "=======================================================\n";
    std::cout << "                    Tasks manager \n";
    std::cout << "=======================================================\n";
    while (true) {
        std::cout << "=====================\n";
        std::cout << "    Main menu: \n";
        std::cout << "=====================\n";

        tabulate::Table table;

        table.add_row({"Press","To..."});
        table[0][0].format().font_color(tabulate::Color::yellow);
        table[0][1].format().font_color(tabulate::Color::yellow);

        table.add_row({"0","Exit"});
        table.add_row({"1","See todays tasks"});
        table.add_row({"2","See future arranged tasks"});
        table.add_row({"3","See yesterdays tasks"});
        std::cout << table << "\n";
        std::cout << "Your choice is: ";
        int choice = GetUserChoice({0,1,2,3});
        if (choice == 0) {
            std::cout << "Bye,bye";
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
        tasks_.clear();
    }
}
