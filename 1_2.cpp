/*
ID: 58919113
Задано N точек на плоскости. Указать (N-1)-звенную несамопересекающуюся незамкнутую ломаную, проходящую через все эти точки.
Указание: стройте ломаную в порядке возрастания x-координаты.
Если имеются две точки с одинаковой x-координатой, то расположите раньше ту точку, у которой y-координата меньше.
Асимптотика: T(n) = O(n^2)
Память: M(n) = O(n)
*/
#include <iostream>
#include <vector>

template<class T>
void InsertionSort(std::vector<T>& arr, int n)
{
	T temp;
	int j;
	for (int i = 1; i < n; i++)
	{
		temp = arr[i];
		j = i - 1;
		for (; j >= 0 && temp < arr[j]; j--)
		{
			arr[j + 1] = arr[j];
		}
		arr[j + 1] = temp;
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
	InsertionSort(arr, n);
	for (int i = 0; i < n; i++)
	{
		std::cout << arr[i].first << " " << arr[i].second << "\n";
	}
	return 0;
}


