#pragma once

#include <queue>

class igra
{
public:
	// ��������� ������
	void move(bool enterIsActivated);

	// �������������
	igra();

	// ����� �� enter
	bool enter;
private:

	void printScore();
	short combo = 1;
	int score = 0;

	// ��������� ���������� �������
	char getSymbol();

	// ���������� ����
	void generate();

	// ��������� ��������� ������������������
	void colorQueue(std::queue<std::pair<short, short>> task);

	// �������� ���������
	void RIGHT(bool& enterIsActivated);
	void LEFT(bool& enterIsActivated);
	void UP(bool& enterIsActivated);
	void DOWN(bool& enterIsActivated);

	// ��� ������
	short flagForPrint = 0;

	// ������� ���������� �� ����; ���������� �����
	short X, Y, prevX, prevY;

	// ������� ����
	std::vector<std::vector<char>> pole{ {0, 0, 0, 0, 0, 0, 0, 0},
								 {0, 0, 0, 0, 0, 0, 0, 0},
								 {0, 0, 0, 0, 0, 0, 0, 0},
								 {0, 0, 0, 0, 0, 0, 0, 0},
								 {0, 0, 0, 0, 0, 0, 0, 0},
								 {0, 0, 0, 0, 0, 0, 0, 0},
								 {0, 0, 0, 0, 0, 0, 0, 0},
								 {0, 0, 0, 0, 0, 0, 0, 0} };

	// ����� �������������������
	std::queue<std::pair<short, short>> bfs(short x, short y);

	// ������, ��������, ��������
	void opera(std::queue<std::pair<short, short>>& task);

	// ����� ���� �� �������
	void printPole(short vx, short vy);

	// ������ ������� �������
	void swap();
};