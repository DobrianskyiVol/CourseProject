#ifndef TASK_H
#define TASK_H
#include<string>
#include<memory>
#include "tabulate/single_include/tabulate/tabulate.hpp"
#include "Time.h"



class Task {
private:
    std::string name;
    std::unique_ptr<Time> time;
    std::unique_ptr<int> duration;
    std::unique_ptr<int> priority;
public:
    //Constructors
    Task();
    Task(const std::string &name,Time &time,int duration, int priority);
    Task(std::string &&name,Time &&time,int duration, int priority);
    virtual ~Task() = default;
    //Copy and move constructors
    Task(const Task &task);
    Task(Task &&task) noexcept;
    //Getters
    std::string  GetName();
    [[nodiscard]] Time GetTime() const;
    [[nodiscard]] int GetDuration() const;
    [[nodiscard]] int GetPriority() const;
    //Setters
    void SetName(const std::string &_name);
    void SetTime(const Time &_time) const;
    void SetDuration(int _duration) const;
    void SetPriority(int _priority) const;

    virtual void ShowTask() const = 0;
    //Overloaded operators
    friend std::ostream& operator<<(std::ostream& os, Task& task);
    friend std::istream& operator>>(std::istream& is, Task& task);
    //Write method
    virtual std::istream &Write(std::istream &is);
    virtual std::ostream &Read(std::ostream &os);
};



#endif //TASK_H
