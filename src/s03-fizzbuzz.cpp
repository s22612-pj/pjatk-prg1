#include <iostream>

auto main(int, char* argv[]) -> int
{

    auto const number = std::stoi(argv[1]);

	
    for(int n = 1; n <= number; n++){
    std::cout << n << " ";    

	if(n % 3 == 0 && n % 5 == 0){
		std::cout << "FizzBuzz\n";
	}
	else if(n % 3 == 0)
	{
	 std::cout << "Fizz\n";
	} 
	else if (n % 5 == 0)
	{
		std::cout << "Buzz\n";
	} 
	else{
	std::cout << n << "\n"; 
	}
    }
    return 0;
}
	

