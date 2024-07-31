#include "Event.h"
//Constructors
Event::Event(const std::string &name, Time &time, int duration, int priority, const std::string &place, const std::string &people_to_meet):
    Task(name,time,duration,priority),place(place),people_to_meet(people_to_meet){}

Event::Event(std::string &&name, Time &&time, int duration, int priority, std::string &&place, std::string &&people_to_meet):
Task(name,time,duration,priority),place(place),people_to_meet(people_to_meet){}
//Getters
std::string Event::GetPlace() {
    return place;
}

std::string Event::GetPeopleToMeet() {
    return people_to_meet;
}
//Setters
void Event::SetPlace(const std::string &_place) {
    place = _place;
}

void Event::SetPeopleToMeet(const std::string &_people) {
    people_to_meet = _people;
}

void Event::ShowTask()const {
    tabulate::Table table;
    table.add_row(
        {"Name","Place","People to meet","Time","Duration","Priority"});
    for (int i = 0; i < 6;i++) {
        table[0][i].format().font_color(tabulate::Color::blue);
    }
    table.add_row(
        {
            GetName(),
            place,
            people_to_meet,
            GetTime().GetTime(),
            std::to_string(GetDuration()),
            std::to_string(GetPriority())
        }
        );
    std::cout << table << "\n";
}

tabulate::Table Event::GetEventTable() {
    tabulate::Table table;
    table.add_row(
        {"Name","Place","People to meet","Time","Duration","Priority"});
    for (int i = 0; i < 6;i++) {
        table[0][i].format().font_color(tabulate::Color::blue);
    }
    table.add_row(
        {
            GetName(),
            place,
            people_to_meet,
            GetTime().GetTime(),
            std::to_string(GetDuration()),
            std::to_string(GetPriority())
        }
        );
    return table;
}

//Write and Read method
std::ostream &Event::Write(std::ostream &os) {
    Task::Write(os);
    os << place << "\n";
    os << people_to_meet << "\n";
    return os;
}
std::istream &Event::Read(std::istream &is) {
    Task::Read(is);
    is >> place;
    is >> people_to_meet;
    return is;

}

std::ostream &operator <<(std::ostream &os,Event &event) {
    return event.Write(os);;
};
std::istream &operator >>(std::istream &is,Event &event) {
    return event.Read(is);;
};