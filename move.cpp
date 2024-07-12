#include "all.h"
#include <conio.h>

short n6 = 7;
short n5 = 6;

void igra::move(bool enterIsActivated)
{
	int choice = _getch();
	if (choice == 224)
		choice = _getch();

	switch (choice)
	{
		// вниз
	case(80):
		combo = 1;
		DOWN(enterIsActivated);
		break;

		// вверх
	case(72):
		combo = 1;
		UP(enterIsActivated);
		break;

		// вправо
	case(77):
		combo = 1;
		RIGHT(enterIsActivated);
		break;

		// влево
	case(75):
		combo = 1;
		LEFT(enterIsActivated);
		break;

		// enter
	case(13):
		if (enter)
		{
			swap();
			prevX = NULL;
			flagForPrint = 0;
			printPole(X, Y);
			enter = 0;
		}
		else
		{
			flagForPrint = 1;
			prevX = X;
			prevY = Y;
			printPole(X, Y);
			enter = 1;

		}
		break;

		// esc
	case(27):
		exit(0);
		break;

		// del
	case(83):
		// после выбранного символа
		printf("\x1b[4;8H");
		// удаление с начала до курсора
		printf("\x1b[1K");
		// установка в начало строки
		printf("\x1b[4;0H");
		break;

	default:
		break;
	}
}

void igra::UP(bool& enterIsActivated)
{
	if (enterIsActivated)
	{
		if (X == prevX)
		{
			if (prevY == pole.size() - 2 && Y == prevY - 1)
				++Y;
			else
				if ((Y - 1 < prevY - 1) || Y == 1)
					Y = prevY + 1;
				else
					--Y;
		}
	}
	else
	{
		if (!(Y = (Y - 1) % n6))
			(Y += n5);
	}

	printPole(X, Y);
}

void igra::DOWN(bool& enterIsActivated)
{
	if (enterIsActivated)
	{
		if (X == prevX)
		{
			if (prevY == 1 && Y == prevY + 1)
				--Y;
			else
				if ((Y + 1 > prevY + 1) || Y == pole.size() - 2)
					Y = prevY - 1;
				else
					++Y;
		}
	}
	else
	{
		if (!(Y = (Y + 1) % n6))
			++Y;
	}

	printPole(X, Y);
}

void igra::LEFT(bool& enterIsActivated)
{
	if (enterIsActivated)
	{
		if (Y == prevY)
		{
			if (prevX == pole.size() - 2 && X == prevX - 1)
				++X;
			else
				if ((X - 1 < prevX - 1) || X == 1)
					X = prevX + 1;
				else
					--X;
		}
	}
	else
	{
		if (!(X = (X - 1) % n6))
			X += n5;
	}

	printPole(X, Y);
}

void igra::RIGHT(bool& enterIsActivated)
{
	if (enterIsActivated)
	{
		if (Y == prevY)
		{
			if (prevX == 1 && X == prevX + 1)
				--X;
			else
				if (X + 1 > prevX + 1 || X == pole.size() - 2)
					X = prevX - 1;
				else
					++X;
		}
	}
	else
	{
		if (!(X = (X + 1) % n6))
			++X;
	}

	printPole(X, Y);
}