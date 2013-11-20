#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

#include <iostream>
#include <string>

struct Stat
{
	Stat() : valid(false),
		total_time(0),
		hi_speed(999999),
		lo_speed(0),
		num(0) {}
	std::string training_str;
	bool valid;
	double total_time;
	double hi_speed;
	double lo_speed;
	int num;
};

void PrintStat(const Stat& stat)
{
	if (!stat.valid)
		return;
	printf("\nresult :\n");
	printf("\ttraining string: %s\n", stat.training_str.c_str());
	printf("\ttrain num:  %6d\n", stat.num);
	printf("\ttotal time: %6.3f s\n", stat.total_time);
	printf("\tavg speed:  %6.3f s, %6.3f ch/s\n", 
		stat.total_time / stat.num, stat.training_str.length() * stat.num / stat.total_time);
	printf("\thigh speed: %6.3f s, %6.3f ch/s\n", 
		stat.hi_speed, stat.training_str.length() / stat.hi_speed);
	printf("\tlow speed:  %6.3f s, %6.3f ch/s\n\n", 
		stat.lo_speed, stat.training_str.length() / stat.lo_speed);
}

Stat Train() 
{
	Stat ret_stat;
	std::string training_str;
	std::cout << "training string (\"quit\" to exit):" << std::endl;
	std::cin >> training_str;
	if (training_str == "quit") 
	{
		std::cout << "training finish!" << std::endl;
		return ret_stat;
	} 
	ret_stat.training_str = training_str;
	std::cout << "start!" << std::endl;

	while (1) 
	{
		char c;
		while (c = _getch()) 
		{
			if (c == training_str[0])
			{
				std::cout << c;
				break;
			}
			else if (c == 27) // ESC
			{
				return ret_stat;
			}
		}

		clock_t s_time = clock();
		for (unsigned int i = 1; i < training_str.length(); ++i) {
			while (1) 
			{
				c = _getch();
				if (c == training_str[i])
				{
					break;
				}
				else if (c == 27) // ESC
				{
					return ret_stat;
				}
			}
			std::cout << c;
		}
		double time = (double)(clock() - s_time) / CLOCKS_PER_SEC;
		ret_stat.total_time += time;
		ret_stat.num++;
		if (time > ret_stat.lo_speed)
			ret_stat.lo_speed = time;
		if (time < ret_stat.hi_speed)
			ret_stat.hi_speed = time;
		ret_stat.valid = true;
		printf("\ncost: %6.3f s\n", time);
	}
}

int main() {
	while (1) {
		Stat stat = Train();
		if (!stat.valid)
			break;
		PrintStat(stat);
	}
	return 0;
}