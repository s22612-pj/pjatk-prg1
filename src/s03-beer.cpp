#include <iostream>
#include <string>

auto main(int argc, char* argv[]) -> int
{
    auto bottles_of_beer = 99;
    if (argc != 1) {
        bottles_of_beer = std::stoi(argv[1]);
    }

    for (auto remaining_beers = bottles_of_beer; remaining_beers > 0;
         --remaining_beers) {
        std::cout << remaining_beers << " bottles of beer on the wall, "
                  << remaining_beers << " bottles of beer.\n";
        std::cout << "Take one down, pass it around, " << remaining_beers - 1
                  << " bottles of beer on the wall...\n";
    }
    std::cout
        << "No more bottles of beer on the wall, no more bottles of beer.\n";
    std::cout << "Go to the store and buy some more, " << bottles_of_beer
              << " bottles of beer on the wall...\n";

    return 0;
}
