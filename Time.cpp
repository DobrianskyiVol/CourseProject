#include "Time.h"

Time::~Time() {
   // std::cout << "Time destructor was called\n";
}

Time::Time():hour(std::make_unique<int>(0)),min(std::make_unique<int>(0)) {}

Time::Time(int h, int m) : hour(std::make_unique<int>(h)), min(std::make_unique<int>(m)) {
    if (!ValidTime(h, m)) {
        throw std::invalid_argument("Invalid time");
    }
}

Time::Time(const Time &time) : hour(std::make_unique<int>(*time.hour)), min(std::make_unique<int>(*time.min)) {}

Time::Time(Time &&time) noexcept : hour(std::move(time.hour)), min(std::move(time.min)) {}

bool Time::ValidTime(int h, int min) {
    if (h < 0 || h > 23 || min < 0 || min > 59) {
        return false;
    }
    return true;
}

void Time::SetCurrentTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    tm localTime = *std::localtime(&t);

    *hour = localTime.tm_hour;
    *min = localTime.tm_min;
}

void Time::SetTime() {
    while(true) {
        std::cout << "(HH:MM): ";
        std::string input;
        std::getline(std::cin >> std::ws, input);  // Use getline to read the entire line

        std::stringstream ss(input);
        char timeDelimiter;

        if(ss >>  *hour >> timeDelimiter >> *min && timeDelimiter == ':') {
            if ( !ValidTime(*hour, *min)) {
                std::cerr << "Invalid time entered.\n" << std::endl;
                *hour = *min = 0;
            } else {
                std::cout << "Time entered successfully.\n" << std::endl;
                break;
            }
        }else
            std::cerr << "Incorrect input.Please try again\n";
    }
}

void Time::PrintTime() const {
    std::cout << "Time: "
                  << std::setw(2) << std::setfill('0') << *hour << ":"
                  << std::setw(2) << std::setfill('0') << *min
                  << std::endl;
}

bool Time::operator==(const Time &rhs) const{
    return  (hour == rhs.hour &&
               *min == *rhs.min);
}

bool Time::operator>(const Time &rhs) const {
    if (*hour > *rhs.hour)
        return true;
    if (*hour < *rhs.hour)
        return false;
    if (*min > *rhs.min)
        return true;
    if (*min < *rhs.min)
        return false;

    return false;
}

bool Time::operator<(const Time &rhs) const {
    if (*hour > *rhs.hour)
        return false;
    if (*hour < *rhs.hour)
        return true;
    if (*min > *rhs.min)
        return false;
    if (*min < *rhs.min)
        return true;

    return false;
}

Time &Time::operator=(const Time &time) {
    if (this == &time) {
        return *this;
    }
    hour = std::make_unique<int>(*time.hour);
    min = std::make_unique<int>(*time.min);
    return *this;
}

Time &Time::operator=(Time &&time) noexcept {
    if (this == &time) {
        return *this;
    }
    hour = std::move(time.hour);
    min = std::move(time.min);
    return *this;
}

std::ostream &operator <<(std::ostream &os, Time &time) {
    os << *time.hour << "\n";
    os << *time.min << "\n";
    return os;
};

std::istream &operator >>(std::istream &is, Time &time) {
    is >> *time.hour;
    is >> *time.min;
    return is;
};

std::string Time::GetTime() const {
    std::string hour_str = std::to_string(*hour);
    std::string minute_str = std::to_string(*min);
    if (*hour < 10) {
        hour_str = '0' + hour_str;
    }
    if (*min < 10) {
        minute_str = '0' + minute_str;
    }

    return (hour_str + ':' + minute_str);

}

Time Time::addMinutes(int minutes) {
    int total_minutes = *hour * 60 + *min + minutes;
    int h,m;
    h = (total_minutes / 60) % 24;
    m = total_minutes % 60;
    return {h,m};
}

Time Time::getCurrentTime() {
    Time time;
    time.SetCurrentTime();
    return time;
}
