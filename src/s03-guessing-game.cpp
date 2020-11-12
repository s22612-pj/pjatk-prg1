#include <iostream>
#include <string>
#include <random>

auto main() -> int
{
	std::random_device rd;
	std::uniform_int_distribution<int> random_number(1, 100);
	auto const guessed_number = random_number(rd);

	auto entered_number = std::string{};
	auto number = int{};

	do {
		std::cout << "guess: ";
		std::getline(std::cin, entered_number);
		number = std::stoi(entered_number);

		if (number > guessed_number) {
		std::cout << "number too big!\n";
		} else if (number < guessed_number) {
			std::cout << "number to small!\n";
		}
	} while (number != guessed_number);
	
	std::cout << "just right!";

	return 0;


}
