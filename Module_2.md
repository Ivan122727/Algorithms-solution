# Algorithms-solution: Module 2
___
# Задача 1
## В первой задачи у меня вариант 2.
### ID: 58919113
## Условие:
Задано 
N точек на плоскости. Указать (N−1)-звенную несамопересекающуюся незамкнутую ломаную, проходящую через все эти точки.
#### Другими словами, здесь нужно написать сортировку, которая сначала сравнивает х, если они равны, y.
# Вот код:
```C++
#include <iostream>
#include <vector>

void Swap(std::pair<int, int>& a, std::pair<int, int>& b)
{
	std::pair<int, int> temp = a;
	a = b;
	b = temp;
}

bool Comp(std::pair<int, int> a, std::pair<int, int> b)
{
	if (b.first == a.first)
	{
		return a.second < b.second;
	}
	else
	{
		return a.first < b.first;
	}
}

void SelectionSort(std::vector<std::pair<int, int>>& arr, int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		int minIndex = i;
		for (int j = i + 1; j < n; j++)
		{
			if (Comp(arr[j], arr[minIndex]))
			{
				minIndex = j;
			}
		}
		Swap(arr[i], arr[minIndex]);
	}
}

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);
	int n;
	std::cin >> n;
	std::vector<std::pair<int, int>> arr(n);
	for (int i = 0; i < n; i++)
	{
		std::cin >> arr[i].first >> arr[i].second;
	}
	SelectionSort(arr, n);
	for (int i = 0; i < n; i++)
	{
		std::cout << arr[i].first << " " << arr[i].second << "\n";
	}
	return 0;
}
```
## Асимптотика: O(n²) 
## Память: T(n)
___
# Задача 2
## В первой задачи у меня вариант 3
### ID: 58922021
## Условие:
На числовой прямой окрасили N отрезков. Известны координаты левого и правого концов каждого отрезка [Li, Ri]. Найти длину окрашенной части числовой прямой.
#### Для решения я ввожу события: '1' - отрезок начался, '-1' - отрезок закончился. Далее сортирую и складываю нужные отрезки
# Вот код:
```C++
#include <iostream>
#include <vector>
#include <algorithm>

bool comp(std::pair<int, int> a, std::pair<int, int> b) 
{
	if (a.first == b.first) 
	{
		return a.second > b.second;
	}
	return a.first < b.first;
}

void ProcessEvent(int& amount, int& answer, int& last, std::pair<int, int> event)
{
	if (amount > 0)
	{
		answer += (event.first - last);
	}
	amount += event.second;
	last = event.first;
}

int main() {
	int n;
	std::cin >> n;
	std::vector<std::pair<int, int>> events;
	for (int i = 0; i < n; i++) {
		int start, finish;
		std::cin >> start >> finish;
		events.push_back({ start, 1 });
		events.push_back({ finish, -1 });
	}
	sort(begin(events), end(events), comp);
	int amount = 0, answer = 0, last = 0;
	for (std::pair<int, int> event : events) 
	{
		ProcessEvent(amount, answer, last, event);
	}
	std::cout << answer << "\n";
	return 0;
}
```
## Асимптотика: O(n log n) 
## Память: T(n)
