
#include <iostream>
#include <string>

auto main(int, char* argv[]) -> int
{
    auto const odliczanie = std::stoi(argv[1]);

    for (auto i = odliczanie; i != 0; (i < 0) ? ++i : --i) {
        std::cout << i << "..."
                  << "\n";
    }
    return 0;
}
