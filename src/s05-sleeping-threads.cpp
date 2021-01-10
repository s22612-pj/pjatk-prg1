#include <chrono>
#include <iostream>
#include <mutex>
#include <queue>
#include <random>
#include <string>
#include <thread>


auto print_stuff(std::queue<std::string>& k, std::mutex& mtx, int const id)
    -> void
{
    std::random_device rd;
    std::uniform_int_distribution<int> random_int(10, 100);
    auto line = std::string{};

    while (true) {
        std::unique_lock<std::mutex> lck{mtx};


        if (k.empty()) {
            lck.unlock();
            std::this_thread::sleep_for(
                std::chrono::milliseconds(random_int(rd)));
            continue;
        }


        line = k.front();

        k.pop();

        if (line.empty()) {
            std::cout << "thread number " << id << " exiting\n";
            break;
        } else {
            std::cout << "from thread number " << id << " : " << line << "\n";
        }
    }
}

auto main() -> int
{
    auto queue = std::queue<std::string>{};
    std::mutex mtx;


    auto t0 = std::thread{print_stuff, std::ref(queue), std::ref(mtx), 0};
    auto t1 = std::thread{print_stuff, std::ref(queue), std::ref(mtx), 1};
    auto t2 = std::thread{print_stuff, std::ref(queue), std::ref(mtx), 2};
    auto t3 = std::thread{print_stuff, std::ref(queue), std::ref(mtx), 3};

    auto done = 0;
    ;

    while (true) {
        auto line = std::string{};
        std::getline(std::cin, line);

        if (line.empty()) {
            done++;
        }

        {
            std::unique_lock<std::mutex> lck{mtx};
            queue.push(std::move(line));
        }

        if (done == 4) {
            break;
        }
    }


    t0.join();
    t1.join();
    t2.join();
    t3.join();

    return 0;
}
