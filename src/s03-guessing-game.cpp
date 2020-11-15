#include <iostream>
#include <random>
#include <string>

auto main() -> int
{
    std::random_device rd;
    std::uniform_int_distribution<int> random_number(1, 100);
    auto const number_to_guess = random_number(rd);

    auto entered_number = std::string{};
    auto number         = int{};

    do {
        std::cout << "guess: ";
        std::getline(std::cin, entered_number);
        number = std::stoi(entered_number);

        if (number > number_to_guess) {
            std::cout << "number too big!\n";
        } else if (number < number_to_guess) {
            std::cout << "number to small!\n";
        }
    } while (number != number_to_guess);

    std::cout << "just right!";

    return 0;
}
