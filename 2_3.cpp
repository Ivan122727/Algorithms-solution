/*
ID: 58922021
Условие:
На числовой прямой окрасили N отрезков. Известны координаты левого и правого концов каждого отрезка [Li, Ri]. Найти длину окрашенной части числовой прямой.
Асимптотика: T(n) = O(n log n)
Память: M(n) = O(n)
*/
#include <iostream>
#include <vector>

template <class T>
void SiftDown(std::vector<T>& arr, int i, int end)
{
	int left = 0;
	int right = 0;
	int largest = 0;
	while (i < end)
	{
		left = 2 * i + 1;
		right = 2 * i + 2;
		largest = i;
		if (left < end && arr[largest] < arr[left])
		{
			largest = left;
		}
		if (right < end && arr[largest] < arr[right])
		{
			largest = right;
		}
		if (largest == i)
		{
			return;
		}
		std::swap(arr[i], arr[largest]);
		i = largest;
	}
}

template <class T>
void BuildHeap(std::vector<T>& arr)
{
	for (int i = (arr.size() / 2) - 1; i >= 0; --i)
	{
		SiftDown(arr, i, arr.size());
	}
}

template <class T>
void HeapSort(std::vector<T>& arr)
{
	BuildHeap(arr);
	for (int end = arr.size() - 1; end > 0; end--)
	{
		std::swap(arr[0], arr[end]);
		SiftDown(arr, 0, end);
	}
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

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);
	int n;
	std::cin >> n;
	std::vector<std::pair<int, int>> events;
	int start, finish;
	for (int i = 0; i < n; i++)
	{
		std::cin >> start >> finish;
		events.push_back({ start, 1 });
		events.push_back({ finish, -1 });
	}
	HeapSort(events);
	int amount = 0, answer = 0, last = 0;
	for (std::pair<int, int> event : events)
	{
		ProcessEvent(amount, answer, last, event);
	}
	std::cout << answer << "\n";
	return 0;
}
