#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>


auto print_stuff(std::queue<int>& queue, std::mutex& mtx, int const id) -> void
{
    while (true) {
        auto number = 0;
        {
            std::lock_guard<std::mutex> lck{mtx};

            if (queue.empty()) {
                std::cout << " thread " << id << " : "
                          << " closed "
                          << "\n";
                break;
            }

            number = queue.front();
            queue.pop();
        }

        std::cout << " thread " << id << " : " << number << "\n";
    }
}


auto main() -> int
{
    auto queue = std::queue<int>{};
    std::mutex mtx;


    for (auto i = 0; i < 16; ++i) {
        queue.push(i);
    }

    auto t0 = std::thread{print_stuff, std::ref(queue), std::ref(mtx), 0};
    auto t1 = std::thread{print_stuff, std::ref(queue), std::ref(mtx), 1};
    auto t2 = std::thread{print_stuff, std::ref(queue), std::ref(mtx), 2};
    auto t3 = std::thread{print_stuff, std::ref(queue), std::ref(mtx), 3};

    t0.join();
    t1.join();
    t2.join();
    t3.join();

    return 0;
}
