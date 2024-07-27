
#ifndef EVENTCONTROLLER_H
#define EVENTCONTROLLER_H

#include <list>
#include<memory>
#include <filesystem>
#include <thread>
#include<algorithm>
#include<mutex>
#include"ControllerInterface.h"
#include "Date.h"
#include "Event.h"
#include "Task.h"
#include"Validation.h"
#include"FileManager.h"

class EventController:public ControllerInterface {
public:
    ~EventController() override = default;
    EventController();
    void Run() override;
    void EventReminder();
private:
    std::list<std::unique_ptr<Event>> events_;
    std::unique_ptr<Date> date_;
    std::unique_ptr<FileManager> file_manager_;
    //std::thread reminder_thread_;
    std::mutex mutex_;
    //CRUD operations
    void Add() override;
    void Edit() override;
    void Delete() override;
    void DeleteAll() override;
    void Reschedule() override;
    void Delay() override;
    void DeletePassedEvents();
    //Working with file
    void ReadFromFile() override;
    void ReadFromFile(std::list<std::unique_ptr<Event>> &events,const std::string& date_name);
    void WriteToFile() override;
    //void AppendToFile(Task *event) override;
    void AppendToFile(const std::string& date_name, Event &event);
    void AppendToFile(Event &event);
    //Sort Methods
    void SortByName() override;
    void SortByPriority() override;
    void SortByTime() override;
    void SortByPeopleToMeet();
    //Show
    void Show() override;
    void PrintMenu() override;
    //Handle tasks
    void HandleTodaysEvents() override;
    void HandleFutureEvents() override;
    void HandleYesterdaysEvents() override;
    //Execution method
    void ExecuteChoice(int choice) override;
    void Execution() override;
    //Check name
    void CheckName(std::string &date, std::string &event_name) override;
    void CheckHour();
    //Analyze conflicts
    void AnalyzeConflicts() override;
};



#endif //EVENTCONTROLLER_H
