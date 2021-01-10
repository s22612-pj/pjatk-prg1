#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>

auto print_stuff(std::queue<std::string>& k,
                 std::mutex& mtx,
                 std::condition_variable& cv,
                 int const id) -> void
{
    auto line = std::string{};


    while (true) {
        std::unique_lock<std::mutex> lck{mtx};
        cv.wait(lck);


        if (k.empty()) {
            lck.unlock();
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
    std::condition_variable cv;


    auto t0 = std::thread{
        print_stuff, std::ref(queue), std::ref(mtx), std::ref(cv), 0};
    auto t1 = std::thread{
        print_stuff, std::ref(queue), std::ref(mtx), std::ref(cv), 1};
    auto t2 = std::thread{
        print_stuff, std::ref(queue), std::ref(mtx), std::ref(cv), 2};
    auto t3 = std::thread{
        print_stuff, std::ref(queue), std::ref(mtx), std::ref(cv), 3};

    auto done = 0;

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
        cv.notify_one();
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
