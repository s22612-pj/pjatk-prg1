#include <iostream>
#include <string>

auto main(int, char* argv[]) -> int
{
    auto const odliczanie = std::stoi(argv[1]);
    if (odliczanie > 0) {
        for (auto i = odliczanie; i >= 0; --i) {
            std::cout << i << "..."
                      << "\n";
        }
    } else {
        for (auto i = odliczanie; i <= 0; ++i) {
            std::cout << i << "..."
                      << "\n";
        }
    }
    return 0;
}
