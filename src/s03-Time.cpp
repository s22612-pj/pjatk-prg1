#include <Time.h>

#include <iomanip>
#include <iostream>
#include <sstream>

s22612::Time::Time(int hour, int minute, int second)
        : hour{hour}, minute{minute}, second{second}
{}


auto timeFormatter(unsigned i) -> std::string
{
    auto out = std::ostringstream{};
    out << std::setw(2) << std::setfill('0') << i;
    return out.str();
}


auto s22612::Time::to_string() const -> std::string
{
    auto out = std::ostringstream{};
    out << std::setw(2) << timeFormatter(hour) << ":" << timeFormatter(minute)
        << ":" << timeFormatter(second);
    return out.str();
}


auto s22612::Time::to_string(const s22612::Time::Time_of_day time_of_day)
    -> std::string
{
    switch (time_of_day) {
    case Time_of_day::MORNING:
        return "Rano!";
    case Time_of_day::AFTERNOON:
        return "Popoludnie!";
    case Time_of_day::EVENING:
        return "Wieczor!";
    default:
        return "Noc!";
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
    ++hour;
    if (hour > 23) {
        hour = 0;
    }
}

auto s22612::Time::next_minute() -> void
{
    ++minute;
    if (minute > 59) {
        minute = 0;
        next_hour();
    }
}

auto s22612::Time::next_second() -> void
{
    ++second;
    if (second > 59) {
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
    auto result = Time{hour, minute, second};
    return result - Time{0, 0, 2};
}


auto s22612::Time::operator+(Time const& time) -> Time
{
    auto result = Time{hour, minute, second};
    for (auto i = 0; i < time.hour; ++i) {
        result.next_hour();
    }
    for (auto i = 0; i < time.minute; ++i) {
        result.next_minute();
    }
    for (auto i = 0; i < time.second; ++i) {
        result.next_second();
    }
    return result;
}

auto s22612::Time::operator-(Time const& time) -> Time
{
    auto result = Time{hour, minute, second};
    for (auto i = 24; i > time.hour; --i) {
        result.next_hour();
    }
    for (auto i = 0; i < time.minute; ++i) {
        result.next_minute();
    }
    for (auto i = 0; i < time.second; ++i) {
        result.next_second();
    }
    return result;
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
    std::cout << s22612::Time::to_string(s22612::Time::Time_of_day::NIGHT)
              << "\n";


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
