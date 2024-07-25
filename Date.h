#ifndef DATE_H
#define DATE_H
#include<chrono>
#include<memory>
#include<iostream>
#include<sstream>

class Date {
private:
    std::unique_ptr<int> year;
    std::unique_ptr<int> month;
    std::unique_ptr<int> day;

    static bool IsValidDate(int y, int m, int d);
public:
    Date();
    Date(int y, int m, int d);
    ~Date();

    Date(const Date &date);
    Date(Date &&date) noexcept ;

    void SetCurrentDate();
    void SetYesterdayDay();
    void SetDate();

    [[nodiscard]] std::string GetDate() const;

    bool operator <(const Date &rhs) const;
    bool operator ==(const Date &rhs) const;

    friend bool IsFuture(const Date &lhs,const Date &rhs);
    friend bool IsNow(const Date &lhs, Date &rhs);
    static Date getCurrentDate();
};



#endif //DATE_H
