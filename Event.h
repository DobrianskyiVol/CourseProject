
#ifndef EVENT_H
#define EVENT_H
#include "Task.h"


class Event:public Task {
private:
    std::string place;
    std::string people_to_meet;
public:
    Event() = default;
    Event(const std::string &name,Time &time,int duration, int priority, const std::string &place, const std::string &people_to_meet);
    Event(std::string &&name,Time &&time,int duration, int priority,std::string &&place,std::string &&people_to_meet);
    ~Event() override = default;

    Event(Event &event) = default;
    Event(Event &&event) noexcept = default;

    std::string GetPlace();
    std::string GetPeopleToMeet();

    void SetPlace(std::string &_place);
    void SetPeopleToMeet(std::string &_people);

    void ShowTask() override;

    //
    std::istream &Write(std::istream &is) override;
    std::ostream &Read(std::ostream &os) override;

    friend std::ostream &operator <<(std::ostream &os,Event &event);
    friend std::istream &operator >>(std::istream &is,Event &event);
};



#endif //EVENT_H
