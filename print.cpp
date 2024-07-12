#include <iostream>
#include "all.h"
#include <conio.h>
#include <windows.h>

void igra::printScore()
{
	std::cout << "combo = " << combo;
	std::cout << "\nscore = " << score;
}

void igra::colorQueue(std::queue<std::pair<short, short>> task)
{
	// очистка экрана
	printf("\x1b[1;1H");
	printf("\x1b[2J");

	std::pair<short, short> v = task.front();
	task.pop();

	for (short i = 0; i < pole.size(); i++)
	{
		for (short j = 0; j < pole[0].size(); j++)
		{
			if (v.first == j && v.second == i)
			{
				std::cout << "\x1b[42m" << pole[i][j];
				if (!task.empty())
				{
					v = task.front();
					task.pop();
				}
				if (v.second == i && v.first != j)
					std::cout << " \x1b[0m";
				else 
					std::cout << "\x1b[0m ";
			}
			else
				std::cout << pole[i][j] << " ";
		}
		std::cout << std::endl;
	}

	printScore();
	Sleep(400);
}

void igra::printPole(short vx, short vy)
{
	// очистка экрана
	printf("\x1b[1;1H");
	printf("\x1b[2J"); 
	
	for (short i = 0; i < pole.size(); i++)
	{
		for (short j = 0; j < pole[0].size(); j++)
		{
			if (i == prevY && j == prevX && prevX != NULL && flagForPrint)
			{
				if (X == prevX && Y == prevY)
				{
					std::cout << "[\x1b[93m" << pole[i][j];
					std::cout << "\x1b[0m]";
				}
				else
				{
					std::cout << "[\x1b[95m" << pole[i][j];
					std::cout << "\x1b[0m]";
				}
				continue;
			}
			if (i == vy && j == vx)
			{

				std::cout << ((j != prevX + 1 || prevX == NULL) ? ">" : "") << "\x1b[93m" << pole[i][j];
				std::cout << "\x1b[0m" << (j != prevX - 1 ? "<" : "");
				continue;
			}
			else
			{
				std::cout << pole[i][j];
			}
			if (!(j == X - 1 && i == Y) && !(j == prevX - 1 && i == prevY))
				std::cout << " ";
		}
		std::cout << std::endl;
	}

	printScore();
}