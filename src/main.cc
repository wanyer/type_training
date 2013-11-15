#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

#include <iostream>
#include <string>

void main() {
restart:	
	std::string training_str;
	std::cout << "training string:" << std::endl;
	std::cin >> training_str;
	if (training_str == "quit") {
		std::cout << "training finish!" << std::endl;
		return;
	} 
	std::cout << "start!" << std::endl;

	while (1) {
		char c;
		while (c = _getch()) {
			if (c == 27) // ESC
				goto restart;
			else if (c == training_str[0])
				break;
		}
		std::cout << c;
		clock_t s_time = clock();
		for (unsigned int i = 1; i < training_str.length(); ++i) {
			while ((c = _getch()) != training_str[i]);
			std::cout << c;
		}
		std::cout << std::endl << "cost: " << 
			(double)(clock() - s_time) / 1000 << "s" << std::endl;
	}
}
