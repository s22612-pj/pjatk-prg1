#ifndef S22612_TIME_H
#define S22612_TIME_H
#include <iostream>

namespace s22612 {
struct Time {
    int hour, minute, second;
    Time(int, int, int);
    enum class Time_of_day { MORNING, AFTERNOON, EVENING, NIGHT };


    auto to_string() const -> std::string;
    auto to_string(enum Time_of_day) const -> std::string;
    auto time_of_day() const -> Time_of_day;
    auto next_hour() -> void;
    auto next_minute() -> void;
    auto next_second() -> void;
    auto count_seconds() const -> uint64_t;
    auto count_minutes() const -> uint64_t;
    auto time_to_midnight() -> Time;
    auto operator+(Time const&) -> Time;
    auto operator-(Time const&) -> Time;
    auto operator<(Time const&) -> bool;
    auto operator>(Time const&) -> bool;
    auto operator==(Time const&) -> bool;
    auto operator!=(Time const&) -> bool;
};

}  // namespace s22612

#endif
