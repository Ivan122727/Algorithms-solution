/*
ID: 54883135
Дана последовательность N прямоугольников различной ширины и высоты (wi, hi). 
Прямоугольники расположены, начиная с точки (0, 0), на оси ОХ вплотную друг за другом (вправо). Требуется найти M - площадь максимального прямоугольника (параллельного осям координат), 
который можно вырезать из этой фигуры
В первой строке задано число N (1 ≤ N ≤ 10000).
Далее идет N строк. В каждой строке содержится два числа width и height: ширина и высота i-го прямоугольника.
(0 < width ≤ 10000, 0 ≤ height ≤ 10000)
Асимптотика: O(n)
Память: T(n)
*/
#include <iostream>
#include <vector>

int Solve(std::vector<int> temp, std::vector<std::pair<int, int>> rectangles, std::vector<std::pair<int, int>> lens, int n)
{
	for (int i = 0; i < n; i++)
	{
		int step = 0;
		while (i != step && rectangles[i - step - 1].second >= rectangles[i].second)
		{
			step++;
		}
		lens[i].first = temp[i - step] - rectangles[i - step].first;
	}
	for (int i = n - 1; i >= 0; i--)
	{
		int step = 0;
		while (i + step != n - 1 && rectangles[i + step + 1].second >= rectangles[i].second)
		{
			step++;
		}
		lens[i].second = temp[i + step];
	}
	int  ans = 0;
	for (int i = 0; i < n; i++)
	{
		ans = std::max(ans, rectangles[i].second * (lens[i].second - lens[i].first));
	}
	return ans;
}

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);
	int n;
	std::cin >> n;
	std::vector<int> temp(n);  // Доп массив, чтобы можно было за 1 операцию найти сумму на определенном участке.
	std::vector<std::pair<int, int>> rectangles(n);
	std::vector<std::pair<int, int>> lens(n);  // Координаты участка где i - прямоугольник ниже остальных pair<начало, конец>
	std::cin >> rectangles[0].first >> rectangles[0].second;
	temp[0] = rectangles[0].first;
	for (int i = 1; i < n; i++)
	{
		std::cin >> rectangles[i].first >> rectangles[i].second;
		temp[i] = temp[i - 1] + rectangles[i].first;
	}
	std::cout << Solve(temp, rectangles, lens, n) << '\n';
	return 0;
}
