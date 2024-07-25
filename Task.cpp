#include "Task.h"
//Constructors
Task::Task():Task("",Time(0,0),0,0) {}

Task::Task(const std::string &name, Time &time, int duration, int priority):
    name(name),time(std::make_unique<Time>(time)),duration(std::make_unique<int>(duration)),
    priority(std::make_unique<int>(priority)){}

Task::Task(std::string &&name, Time &&time, int duration, int priority):
name(name),time(std::make_unique<Time>(time)),duration(std::make_unique<int>(duration)),
priority(std::make_unique<int>(priority)){}
//Copy and move constructors
Task::Task(const Task &task) {
    name = task.name;
    time =  std::make_unique<Time>(*task.time);
    duration = std::make_unique<int>(*task.duration);
    priority = std::make_unique<int>(*task.priority);
}

Task::Task(Task &&task) noexcept {
    name = std::move(task.name);
    time = std::move(task.time);
    duration = std::move(task.duration);
    priority = std::move(task.priority);
}
//Getters
std::string Task::GetName() {
    return name;
}

Time Task::GetTime() const {
    return *time;
}

int Task::GetDuration() const {
    return *duration;
}

int Task::GetPriority() const {
    return *priority;
}
//Setters
void Task::SetName(const std::string &_name) {
    name = _name;
}

void Task::SetDuration(const int _duration) const {
    *duration = _duration;
}

void Task::SetTime(const Time &_time) const {
    *time = _time;
}

void Task::SetPriority(const int _priority) const {
    *priority = _priority;
}
//Show method
void Task::ShowTask() {
    tabulate::Table table;
    table.add_row({"Name","Time","Duration","Priority"});
    table.add_row(
        {name,time->GetTime(),std::to_string(*duration),std::to_string(*priority)});
    std::cout << table << "\n";
}

//Read and Write method for streming
std::ostream &Task::Read(std::ostream &os) {
    os << name << "\n";
    os << *time;
    os << *duration << "\n";
    os << *priority << "\n";
    return os;
}

std::istream &Task::Write(std::istream &is) {
    if (!std::getline(is >> std::ws, name)) {
        return is; // Return if reading failed
    }
    if (!(is >> *time)) {
        return is; // Return if reading failed
    }
    if (!(is >> *duration)) {
        return is; // Return if reading failed
    }
    if (!(is >> *priority)) {
        return is; // Return if reading failed
    }
    return is;
}

//Overloaded operators
std::ostream& operator<<(std::ostream& os,Task& task) {
    return task.Read(os);
};
std::istream& operator>>(std::istream& is, Task& task) {
    return task.Write(is);
}


