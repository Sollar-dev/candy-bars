#pragma once

#include <queue>

class igra
{
public:
	// обработка клавиш
	void move(bool enterIsActivated);

	// инициализация
	igra();

	// нажат ли enter
	bool enter;
private:

	void printScore();
	short combo = 1;
	int score = 0;

	// получение рандомного символа
	char getSymbol();

	// заполнение поля
	void generate();

	// выделение найденной последовательности
	void colorQueue(std::queue<std::pair<short, short>> task);

	// движение стрелками
	void RIGHT(bool& enterIsActivated);
	void LEFT(bool& enterIsActivated);
	void UP(bool& enterIsActivated);
	void DOWN(bool& enterIsActivated);

	// при печати
	short flagForPrint = 0;

	// текущие координаты на поле; выделенной точки
	short X, Y, prevX, prevY;

	// игровое поле
	std::vector<std::vector<char>> pole{ {0, 0, 0, 0, 0, 0, 0, 0},
								 {0, 0, 0, 0, 0, 0, 0, 0},
								 {0, 0, 0, 0, 0, 0, 0, 0},
								 {0, 0, 0, 0, 0, 0, 0, 0},
								 {0, 0, 0, 0, 0, 0, 0, 0},
								 {0, 0, 0, 0, 0, 0, 0, 0},
								 {0, 0, 0, 0, 0, 0, 0, 0},
								 {0, 0, 0, 0, 0, 0, 0, 0} };

	// поиск последовательностей
	std::queue<std::pair<short, short>> bfs(short x, short y);

	// замена, смещение, символов
	void opera(std::queue<std::pair<short, short>>& task);

	// вывод поля на консоль
	void printPole(short vx, short vy);

	// менять местами символы
	void swap();
};