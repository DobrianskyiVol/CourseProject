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
void Event::SetPlace(std::string &_place) {
    place = _place;
}

void Event::SetPeopleToMeet(std::string &_people) {
    people_to_meet = _people;
}

void Event::ShowTask() {
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

//Write and Read method
std::ostream &Event::Read(std::ostream &os) {
    Task::Read(os);
    os << place;
    os << people_to_meet;
    return os;
}
std::istream &Event::Write(std::istream &is) {
    Task::Write(is);
    is >> place;
    is >> people_to_meet;
    return is;
}


