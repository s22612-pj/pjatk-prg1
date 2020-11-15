#include <iostream>
#include <string>


auto main(int argc, char* argv[]) -> int
{
    for (auto i = 1; i < argc; ++i) {
        std::cout << argv[i] << " ";
    }

    if (std::string{argv[1]} == "-n") {
        for (auto i = 0; i < argc; ++i) {
            std::cout << argv[i] << ", ";
        }
    }

    else if (std::string{argv[1]} == "-r") {
        for (auto i = argc - 1; i > 0; --i) {
            std::cout << argv[i] << ", ";
        }
    }

    else if (std::string{argv[1]} == "-l") {
        for (auto i = 0; i < argc; ++i) {
            std::cout << argv[i] << "\n";
        }
    }

    std::cout << "\n";

    return 0;
}
