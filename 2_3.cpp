/*
ID: 58922021
Условие:
На числовой прямой окрасили N отрезков. Известны координаты левого и правого концов каждого отрезка [Li, Ri]. Найти длину окрашенной части числовой прямой.
Асимптотика: O(n log n)
Память: T(n)
*/
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