#ifndef TIME_H
#define TIME_H
#include<iostream>
#include<chrono>
#include<iomanip>
#include <list>
#include<memory>


class Time {
private:
    std::unique_ptr<int> hour;
    std::unique_ptr<int> min;

    static bool ValidTime(int h, int min);
public:
    ~Time();
    Time();
    Time(int h, int m);
    Time(const Time &time);
    Time(Time &&time) noexcept;

    Time &operator=(const Time &time);
    Time &operator=(Time &&time) noexcept;
    bool operator ==(const Time &rhs) const;
    bool operator <(const Time &rhs) const;
    bool operator >(const Time &rhs) const;
    friend std::ostream &operator <<(std::ostream &os, Time &time);
    friend std::istream &operator >>(std::istream &is, Time &time);

    void SetCurrentTime();
    static Time getCurrentTime();
    void SetTime();
    Time addMinutes(int minutes);

    [[nodiscard]] std::string GetTime() const;

    void PrintTime() const;
};



#endif
