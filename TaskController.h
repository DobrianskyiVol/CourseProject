#ifndef TASKCONTROLLER_H
#define TASKCONTROLLER_H
#include <list>
#include<memory>
#include <filesystem>
#include<fstream>
#include"ControllerInterface.h"
#include "Date.h"
#include "Task.h"
#include"Validation.h"
#include"FileManager.h"

class TaskController:public ControllerInterface {
public:
    ~TaskController() override = default;
    TaskController();
    void Run() override;
private:
    std::unique_ptr<Date> date_;
    std::list<std::unique_ptr<Task>> tasks_;
    std::unique_ptr<FileManager> file_manager_;
    //CRUD operations
    void Add() override;
    void Edit() override;
    void Delete() override;
    void DeleteAll() override;
    void Reschedule() override;
    void Delay() override;
    //Working with file
    void ReadFromFile() override;
    void ReadFromFile(std::list<std::unique_ptr<Task>> &tasks,const std::string& date_name);
    void WriteToFile() override;
    void AppendToFile(Task &task);
    //void AppendToFile(Task *task) override;
    void AppendToFile(const std::string& date_name, Task &task);
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
    void CheckName(std::string &date, std::string &task_name) override;
    //Analyze conflicts
    void AnalyzeConflicts() override;
};



#endif //TASKCONTROLLER_H
