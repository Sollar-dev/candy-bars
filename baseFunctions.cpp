#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <vector>
#include <ctime>
#include "all.h"

// замена, смещение, проверка
void igra::opera(std::queue<std::pair<short, short>>& task)
{
	std::srand(std::time(NULL));

	// для проверки по bfs
	std::set<std::pair<short, short>> moved;

	// замена символов в последовательностях
	std::queue<std::pair<short, short>> forChange = task;

	auto comp = [](std::pair<short, short> a, std::pair<short, short> b)
	{
		if (a.second > b.second)
			return true;
		else if (a.second == b.second && a.first > b.first)
			return true;
		else
			return false;
	};
	std::priority_queue<std::pair<short, short>, std::vector<std::pair<short, short>>, decltype(comp)> stask(comp);

	// первый проход сортирует по второму элементу
	// второй проход по первому элементу при равных вторых
	// заполнение с сортировкой
	while (!task.empty())
	{
		stask.push(task.front());
		task.pop();
	}

	while (!stask.empty())
	{
		task.push(stask.top());
		stask.pop();
	}

	while (!task.empty())
	{
		stask.push(task.front());
		task.pop();
	}

	while (!stask.empty())
	{
		task.push(stask.top());
		stask.pop();
	}

	score += task.size() * combo;
	combo++;;
	colorQueue(task);

	// замена символов в последовательности
	while (!forChange.empty())
	{
		std::pair<short, short> v = forChange.front();
		pole[v.second][v.first] = getSymbol();
		forChange.pop();
	}

	// смещение 
	while (!task.empty())
	{
		std::pair<short, short> v = task.front();
		task.pop();

		for (short i = v.second; i > 1; i--)
		{

			moved.insert({ i, v.first });
			moved.insert({ i - 1, v.first });

			short tmp = pole[i][v.first];
			pole[i][v.first] = pole[i - 1][v.first];
			pole[i - 1][v.first] = tmp;
		}
	}

	// проверка на возможно созданные последовательности
	for (auto& i : moved)
	{
		std::queue<std::pair<short, short>> tmp = bfs(i.first, i.second);
		if (!tmp.empty())
			opera(tmp);
	}
	moved.clear();
}

// волновой алгоритм поиска последовательностей
std::queue<std::pair<short, short>> igra::bfs(short x, short y)
{
	// использованные вершины в этом проходе
	std::vector<std::vector<char>> used(pole.size(), std::vector<char>(pole[0].size(), 0));

	// временная очередь, очередь с координатами элементов (из последовательности >= 3)
	std::queue<std::pair<short, short>> q, p;

	std::unordered_map<short, std::pair<short, short>> xmap, ymap;

	// количество в последовательности по строкам, столбцам
	std::vector<short> size_x(pole[0].size(), 0), size_y(pole.size(), 0);

	// старт вершина в очереди, использована
	q.push({ x, y });
	p.push({ x, y });
	used[x][y] = 1;

	while (!q.empty())
	{
		// координаты из вершины
		std::pair<short, short> v = q.front();
		short vy = v.first;
		short vx = v.second;
		q.pop();

		// если вершина в округе равна установке, не использована, идем на нее
		if (pole[vy][vx] == pole[vy + 1][vx] && !used[vy + 1][vx])
		{
			q.push({ (vy + 1), vx });
			p.push({ (vy + 1), vx });
			used[vy + 1][vx] = 1;
		}
		if (pole[vy][vx] == pole[vy][vx + 1] && !used[vy][vx + 1])
		{
			q.push({ vy, (vx + 1) });
			p.push({ vy, (vx + 1) });
			used[vy][vx + 1] = 1;
		}
		if (pole[vy][vx] == pole[vy - 1][vx] && !used[vy - 1][vx])
		{
			q.push({ (vy - 1), vx });
			p.push({ (vy - 1), vx });
			used[vy - 1][vx] = 1;
		}
		if (pole[vy][vx] == pole[vy][vx - 1] && !used[vy][vx - 1])
		{
			q.push({ vy, (vx - 1) });
			p.push({ vy, (vx - 1) });
			used[vy][vx - 1] = 1;
		}
	}

	// проверка хранятся ли 3 символа в одной плоскости без пробелов, исключает (4, 1, 4, 4), оставляет(1, 4, 4, 4)
	if (p.size() >= 3)
	{
		short size = p.size();
		for (short i = 0; i < size; i++)
		{
			std::pair<short, short>& u = p.front();

			std::pair<short, short>& x_map_first = xmap[u.first];
			if (x_map_first.first == NULL)
				x_map_first.first = 0;
			if (x_map_first.first < u.second)
				x_map_first.first = u.second;

			if (x_map_first.second == NULL)
				x_map_first.second = 255;
			if (x_map_first.second > u.second)
				x_map_first.second = u.second;
			size_x[u.first]++;

			std::pair<short, short>& y_map_first = ymap[u.second];
			if (y_map_first.first == NULL)
				y_map_first.first = 0;
			if (y_map_first.first < u.first)
				y_map_first.first = u.first;

			if (y_map_first.second == NULL)
				y_map_first.second = 255;
			if (y_map_first.second > u.first)
				y_map_first.second = u.first;
			size_y[u.second]++;

			p.pop();
		}
		// для проверки на повтор
		std::vector<std::pair<short, short>> tmp;

		for (auto& u : xmap)
		{
			std::pair<short, short> x = u.second;
			if ((size_x[u.first] >= 3) && (x.first - x.second + 1 == size_x[u.first]))
			{
				for (short i = x.second; i <= x.first; i++)
				{
					tmp.push_back({ i, u.first });
					p.push({ i, u.first });
				}
			}
		}
		for (auto& u : ymap)
		{
			std::pair<short, short> y = u.second;
			if ((size_y[u.first] >= 3) && (y.first - y.second + 1 == size_y[u.first]))
			{
				for (short i = y.second; i <= y.first; i++)
				{
					// проверка на повтор
					bool f = 0;
					std::pair<short, short> tmp_pair = { u.first, i };
					for (short j = 0; j < tmp.size(); j++)
					{
						if (tmp[j] == tmp_pair)
						{
							f = 1;
							break;
						}
					}

					if (!f)
						p.push({ u.first, i });
				}
			}
		}
		tmp.clear();
	}

	if (p.size() < 3 && p.size() != 0)
		p.pop();
	if (p.size() == 1)
		p.pop();

	return p;
}

void igra::swap()
{
	char tmp = pole[Y][X];
	pole[Y][X] = pole[prevY][prevX];
	pole[prevY][prevX] = tmp;

	std::queue<std::pair<short, short>> qtmp;
	qtmp = bfs(Y, X);
	if (!qtmp.empty())
		opera(qtmp);
	qtmp = bfs(prevY, prevX);
	if (!qtmp.empty())
		opera(qtmp);
}