#include <iostream>
#include <string>
using namespace std;

auto main(int, char* argv[]) -> int
{
	auto const odliczanie = std::stoi(argv[1]);
	if(odliczanie > 0) {
		for(int i = odliczanie; i >= 0; --i) {
			std::cout << i << "..." << "\n";
		}
	} else {
		for(int i = odliczanie; i <= 0; ++i) {
			std::cout << i << "..." << "\n";
		}
	}
	return 0; 
}
