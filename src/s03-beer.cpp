#include <iostream>
#include <string>

auto main(int argc, char* argv []) -> int
{
	auto bottles = 99;
	if(argc != 1) {
		bottles = std::stoi(argv[1]);
	}

	for(int bottles1 = bottles; bottles1 >= 0; --bottles1) {
		if(bottles1 == 0) {
			std::cout << "No more bottles of beer on the wall, no more bottles of beer.\n";
			std::cout << "Go to the store and buy some more, " << bottles1 << " bottles of beer on the wall...\n";
		} else {
			std::cout << bottles1 << " bottles of beer on the wall, " << bottles1 << " bottles of beer.\n";
			std::cout << "Take one down, pass it around, " << bottles1 - 1 << " bottles of beer on the wall...\n";
	}
    }
return 0;
}
