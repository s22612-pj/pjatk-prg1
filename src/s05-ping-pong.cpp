#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <random>
#include <string>
#include <thread>


auto print_stuff(int& number,
                 std::mutex& mtx,
                 std::condition_variable& cv,
                 std::random_device& rd,
                 std::uniform_int_distribution<int>& random_number,
                 std::string const id) -> void
{
    for (number = 0; number <= 1024; ++number) {
        {
            std::unique_lock<std::mutex> lck{mtx};
            cv.wait(lck);
            number = number + random_number(rd);
            std::cout << (id + " " + std::to_string(number) + "\n");
        }
        cv.notify_all();
        if (number > 1024) {
            break;
        }
    }
}


auto main() -> int
{
    std::mutex mtx;
    std::condition_variable cv;

    std::random_device rd;
    std::uniform_int_distribution<int> random_number(1, 42);
    auto number         = int{random_number(rd)};
    auto entered_number = std::string{};


    auto ping = std::thread(print_stuff,
                            std::ref(number),
                            std::ref(mtx),
                            std::ref(cv),
                            std::ref(rd),
                            std::ref(random_number),
                            "ping");

    auto pong = std::thread(print_stuff,
                            std::ref(number),
                            std::ref(mtx),
                            std::ref(cv),
                            std::ref(rd),
                            std::ref(random_number),
                            "pong");

    std::cout << "ping ";
    std::getline(std::cin, entered_number);
    number = std::stoi(entered_number);
    cv.notify_all();

    ping.join();
    pong.join();

    return 0;
}
