
#ifndef EVENTCONTROLLER_H
#define EVENTCONTROLLER_H

#include <list>
#include<memory>
#include <filesystem>
#include<fstream>
#include"ControllerInterface.h"
#include "Date.h"
#include "Task.h"
#include"Validation.h"

class EventController:public ControllerInterface {
public:
    ~EventController() override;
    EventController();
    void Run() override;
private:
    std::list<std::unique_ptr<Task>> events_;
    std::unique_ptr<Date> date_;
    //CRUD operations
    void Add() override;
    void Edit() override;
    void Delete() override;
    void DeleteAll() override;
    void Reschedule() override;
    void Delay() override;
    //Working with file
    void ReadFromFile() override;
    void ReadFromFile(std::list<std::unique_ptr<Task>> &events,std::string date_name) override;
    void WriteToFile() override;
    void AppendToFile(Task *event) override;
    void AppendToFile(std::string date_name, Task *event) override;
    //Sort Methods
    void SortByName() override;
    void SortByPriority() override;
    void SortByTime() override;
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
    //Analyze conflicts
    void AnalyzeConflicts() override;
};



#endif //EVENTCONTROLLER_H
