#include "all.h"
#include <conio.h>
#include <Windows.h>

constexpr auto ESC = "\x1b";
constexpr auto CSI = "\x1b[";

igra::igra()
{
	int error;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hOut == INVALID_HANDLE_VALUE)
	{
		error = GetLastError();
	}

	DWORD dwMode = 0;
	if (!GetConsoleMode(hOut, &dwMode))
	{
		error = GetLastError();
	}

	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	if (!SetConsoleMode(hOut, dwMode))
	{
		error = GetLastError();
	}

	generate();

	std::queue<std::pair<short, short>> qtmp;
	qtmp = bfs(3, 3);
	if (!qtmp.empty())
		opera(qtmp);

	enter = 0;

	X = 3;
	Y = 3;

	printPole(X, Y);

	for (int i = 1; i < pole.size() - 1; i++)
	{
		for (int j = 1; j < pole[0].size() - 1; j++)
		{
			qtmp = bfs(j, i);
			if (!qtmp.empty())
				opera(qtmp);
		}
	}

	printPole(X, Y);
}