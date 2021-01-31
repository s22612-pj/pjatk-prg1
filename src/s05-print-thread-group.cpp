#include <iostream>
#include <string>
#include <thread>
#include <vector>

auto print_stuff(std::string x) -> void
{
    std::cout << (x + "\n");
}

auto main() -> int
{
    auto size_of_groups = int{6};
    auto groups         = int{7};

    for (auto i = 0; i < groups; i++) {
        auto v_threads = std::vector<std::thread>{};

        std::cout << "----" << i << "----"
                  << "\n";

        for (auto j = 0; j < size_of_groups; j++) {
            auto s = std::string{"Hello, "}
                     + std::to_string((j + 1) + (i * size_of_groups)) + "!";
            v_threads.push_back(std::thread(print_stuff, std::move(s)));
        }


        for (auto& each : v_threads) {
            each.join();
        }
    }
    return 0;
}
