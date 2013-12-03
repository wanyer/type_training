#include <conio.h>
#include <windows.h>
#include <winnt.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

#include <iostream>
#include <string>

static int mode = 0; // 0 for normal, 1 for random

struct Stat
{
	Stat() :
		total_time(0),
		hi_speed(999999),
		lo_speed(0),
		num(0) {}
	std::string training_str;
	double total_time;
	double hi_speed;
	double lo_speed;
	int num;
};

void PrintStat(const Stat& stat)
{
	HANDLE consolehwnd;
	consolehwnd = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(consolehwnd, FOREGROUND_GREEN);

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

	SetConsoleTextAttribute(consolehwnd, FOREGROUND_INTENSITY);
}

char GenRandomChar()
{
	static bool is_init = false;
	if (!is_init)
	{
		srand((unsigned int)time(NULL));
		is_init = true;
	}
	// characters between [32, 126]([0x20, 0x7e]) are displayable, 95 chars totally
	int r = rand() % 95;
	return (char)(32 + r);
}

Stat Train(std::string& training_str) 
{
	Stat ret_stat;
	
	std::cout << "start!" << std::endl;

	while (1) 
	{
		if (mode == 1) {
			int len = 73;
			char *buf = new char[len + 1];
			for (int i = 0; i < len; ++i) {
				buf[i] = GenRandomChar();
			}
			buf[len] = 0;
			training_str.assign(buf);
			std::cout << training_str << std::endl;
		}
		ret_stat.training_str = training_str;

		char c;
		clock_t s_time;
		for (unsigned int i = 0; i < training_str.length(); ++i) {
			while (c = _getch())
			{
				if (c == training_str[i])
					break;
				else if (c == 27) // ESC
					return ret_stat;
			}
			if (i == 0)
				s_time = clock();
			std::cout << c;
		}
		double time = (double)(clock() - s_time) / CLOCKS_PER_SEC;
		ret_stat.total_time += time;
		ret_stat.num++;
		if (time > ret_stat.lo_speed)
			ret_stat.lo_speed = time;
		if (time < ret_stat.hi_speed)
			ret_stat.hi_speed = time;
		printf("\ncost: %6.3f s\n", time);
	}
}

int main() {
	while (1) {
		mode = 0;
		std::string training_str;
		std::cout << "training string (\"quit\" to exit, \"random\" for random string):" << std::endl;
		std::cin >> training_str;
		if (training_str == "quit")
		{
			std::cout << "training finish!" << std::endl;
			break;
		}
		else if (training_str == "random") {
			mode = 1;
			std::cout << "random string mode, string len:" << std::endl;
		}
		
		Stat stat = Train(training_str);
		PrintStat(stat);
	}
	return 0;
}