#include "EventController.h"

#include "Event.h"

EventController::EventController():date_(std::make_unique<Date>()) {
    date_->SetCurrentDate();
}

void EventController::ReadFromFile() {
    std::string folder = R"(D:\C++\Course_Project_Final_Final\Events\)";
    std::string nameoffile = (folder  +  date_->GetDate() + ".txt");
    std::ifstream of(nameoffile);
    if (!of) {
        //std::cout << "No events for current day\n";
        return;
    }

    while (!of.eof()) {
        std::unique_ptr<Task> event = std::make_unique<Event>();
        of >> *event;
        if (event->GetPriority() == 0)
            break;
        events_.emplace_back(std::move(event));
    }
    of.close();
}