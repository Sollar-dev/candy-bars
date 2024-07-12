#include "all.h"
#include <ctime>

void igra::generate()
{
	srand(time(NULL));

	for (int i = 1; i < pole.size() - 1; i++)
	{
		for (int j = 1; j < pole[0].size() - 1; j++)
		{
			pole[i][j] = getSymbol();
		}
	}
}

char igra::getSymbol()
{

	short symbolsSize = 5;
	char symbols[5]{ '%', '#', '@', '&', '+' };

	return symbols[rand() % symbolsSize];
}