#include <conio.h>
#include <stdio.h>
#include <time.h>

#include <iostream>
#include <string>

void main() {
	clock_t s_time, e_time;
	std::string training_str;

restart:	
	std::cout << "training string:" << std::endl;
	std::cin >> training_str;
	if (training_str == "quit") {
		std::cout << "training finish!" << std::endl;
		return;
	}
    printf("start!\n");

	while (1) {
		char c;
		while (c = getch()) {
			if (c == 27) { // ESC
				goto restart;
			} else if (c == training_str[0]) {
				break;
			}
		}
		std::cout << c;
		s_time = clock();
		int i = 1;
		while (1) {
			while ((c = getch()) != training_str[i]);
			std::cout << c;
			i++;
			if (i == training_str.length())
				break;
		}
		e_time = clock();
		std::cout << std::endl << "cost: " << 
			(double)(e_time - s_time) / 1000 << "s" << std::endl;
	}
}
