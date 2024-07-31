#ifndef CONTROLLERINTERFACE_H
#define CONTROLLERINTERFACE_H
#include "Task.h"
#include <memory>

class ControllerInterface {
public:
    virtual ~ControllerInterface() = default;
    virtual void Run() = 0;
private:
    //CRUD operations
    virtual void Add() = 0;
    virtual void Edit() = 0;
    virtual void Delete() = 0;
    virtual void DeleteAll() = 0;
    virtual void Reschedule() = 0;
    virtual void Delay() = 0;
    //Basic sort method
    virtual void SortByTime() = 0;
    virtual void SortByName() = 0;
    virtual void SortByPriority() = 0;
    //Working with file
    virtual void WriteToFile() = 0;
    virtual void ReadFromFile() = 0;
    //Show
    virtual void Show() = 0;
    virtual void PrintMenu() = 0;
    //Handle tasks(events)
    virtual void HandleTodaysEvents() = 0;
    virtual void HandleFutureEvents() = 0;
    virtual void HandleYesterdaysEvents() = 0;
    //Execution method
    virtual void ExecuteChoice(int choice) = 0;
    virtual void Execution() = 0;
    //Name checking for its uniquness
    virtual void CheckName(std::string &date,std::string &name) = 0;
    //Analzing tasks or events that has time collapsed
    virtual void AnalyzeConflicts() = 0;
};



#endif //CONTROLLERINTERFACE_H
