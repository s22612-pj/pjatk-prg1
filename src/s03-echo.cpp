#include <iostream>
#include <string>

auto main(int argc, char* argv[]) -> int
{
	for(int i = 1; i < argc; ++i) {
		std::cout << argv[i] << " ";
	}

}
