/*
ID: 58919113
Условие:
Задано 
N точек на плоскости. Указать (N−1) -звенную несамопересекающуюся незамкнутую ломаную, проходящую через все эти точки.
Асимптотика: O(n²)
Память: O(n)
*/
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
