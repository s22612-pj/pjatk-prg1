#include <Time.h>

#include <iomanip>
#include <iostream>
#include <sstream>

s22612::Time::Time(int h, int m, int s)
{
    hour   = h;
    minute = m;
    second = s;
}


auto timeFormatter(unsigned i) -> std::string
{
    return i < 10 ? "0" + std::to_string(i) : std::to_string(i);
}


auto s22612::Time::to_string() const -> std::string
{
    auto out = std::ostringstream{};
    out << std::setw(2) << timeFormatter(hour) << ":" << timeFormatter(minute)
        << ":" << timeFormatter(second);
    return out.str();
}


auto s22612::Time::to_string(Time_of_day time_of_day) const -> std::string
{
    switch (time_of_day) {
    case Time_of_day::MORNING:
        return "Rano!";
    case Time_of_day::AFTERNOON:
        return "Popoludnie!";
    case Time_of_day::EVENING:
        return "Wieczor!";
    case Time_of_day::NIGHT:
        return "Noc!";
    default:
        return "";
    }
}


auto s22612::Time::time_of_day() const -> Time_of_day
{
    if (hour < 6) {
        return Time_of_day::NIGHT;
    } else if (hour >= 6 && hour < 12) {
        return Time_of_day::MORNING;
    } else if (hour >= 12 && hour < 18) {
        return Time_of_day::AFTERNOON;
    } else if (hour >= 18 && hour < 21) {
        return Time_of_day::EVENING;
    } else {
        return Time_of_day::NIGHT;
    }
}

auto s22612::Time::next_hour() -> void
{
    if (hour == 23) {
        hour = 0;
    } else {
        ++hour;
    }
}

auto s22612::Time::next_minute() -> void
{
    if (minute == 59) {
        minute = 0;
        next_hour();
    }
}

auto s22612::Time::next_second() -> void
{
    if (second == 59) {
        second = 0;
        next_minute();
    }
}

auto s22612::Time::count_seconds() const -> uint64_t
{
    return second + minute * 60 + hour * 3600;
}

auto s22612::Time::count_minutes() const -> uint64_t
{
    return second / 60 + minute + hour * 60;
}

auto s22612::Time::time_to_midnight() -> Time
{
    return Time{0, 0, 0} - *this;
}


auto s22612::Time::operator+(Time const& time) -> Time
{
    for (int i = 0; i < time.hour; ++i) {
        next_hour();
    };
    for (int i = 0; i < time.minute; ++i) {
        next_minute();
    };
    for (int i = 0; i < time.second; ++i) {
        next_second();
    };
    return *this;
}

auto s22612::Time::operator-(Time const& time) -> Time
{
    auto second_for_operator = second - time.second;
    auto minute_for_operator = minute - time.minute;
    auto hour_for_operator   = hour - time.hour;
    if (second_for_operator < 0) {
        --minute_for_operator;
        second = 60 + second_for_operator;
    } else if (minute_for_operator < 0) {
        --hour_for_operator;
        minute = 60 + minute_for_operator;
    } else if (hour_for_operator < 0) {
        hour = 24 + hour_for_operator;
    }
    return *this;
}

auto s22612::Time::operator<(Time const& time) -> bool
{
    if (hour == time.hour && minute == time.minute) {
        return second < time.second;
    } else if (hour == time.hour) {
        return minute < time.hour;
    }
    return second < time.second;
}

auto s22612::Time::operator>(Time const& time) -> bool
{
    if (hour == time.hour and minute == time.minute) {
        return second > time.second;
    } else if (hour == time.hour) {
        return minute > time.hour;
    }
    return second > time.second;
}
auto s22612::Time::operator==(Time const& time) -> bool
{
    return (hour == time.hour && minute == time.minute
            && second == time.second);
}


auto main() -> int
{
    std::cout << "to_string()\n";
    auto time = s22612::Time{23, 59, 59};
    std::cout << time.to_string() << "\n";

    std::cout << "next_hour()\n";
    time = s22612::Time{23, 59, 59};
    time.next_hour();
    std::cout << time.to_string() << "\n";

    std::cout << "next_minute()\n";
    time = s22612::Time{23, 59, 59};
    time.next_minute();
    std::cout << time.to_string() << "\n";

    std::cout << "next_second()\n";
    time = s22612::Time{23, 59, 59};
    time.next_second();
    std::cout << time.to_string() << "\n";


    std::cout << "time_of_day()\n";
    time = s22612::Time{23, 59, 59};
    std::cout << time.to_string(time.time_of_day()) << "\n";


    std::cout << "operator+\n";
    auto a = s22612::Time{23, 59, 59};
    auto b = s22612::Time{0, 0, 1};
    std::cout << (a + b).to_string() << "\n";

    std::cout << "operator-\n";
    a = s22612::Time{3, 59, 59};
    b = s22612::Time{4, 0, 0};
    std::cout << (a - b).to_string() << "\n";

    std::cout << "operator<\n";
    a = s22612::Time{23, 59, 59};
    b = s22612::Time{0, 0, 1};
    if (a > b) {
        std::cout << a.to_string() << " > " << b.to_string() << "\n";
    } else {
        std::cout << a.to_string() << " ? " << b.to_string() << "\n";
    }

    std::cout << "operator==\n";
    a = s22612::Time{23, 59, 59};
    b = s22612::Time{0, 0, 1};
    if (a == b) {
        std::cout << a.to_string() << " == " << b.to_string() << "\n";
    } else {
        std::cout << a.to_string() << " != " << b.to_string() << "\n";
    }

    std::cout << "count_seconds()\n";
    time = s22612::Time{23, 59, 59};
    std::cout << time.count_seconds() << "\n";

    std::cout << "count_minutes()\n";
    time = s22612::Time{23, 59, 59};
    std::cout << time.count_minutes() << "\n";

    std::cout << "time_to_midnight()\n";
    time = s22612::Time{23, 59, 59};
    std::cout << time.time_to_midnight().to_string() << "\n";

    return 0;
}
