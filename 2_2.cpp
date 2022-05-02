/*
Условия:
В большой IT-фирме есть только одна переговорная комната.
Желающие посовещаться заполняют заявки с желаемым временем начала и конца.
Ваша задача определить максимальное количество заявок, которое может быть удовлетворено.
Число заявок ≤ 100000.
Асимптотика: T(n) = O(n log n)
Память: M(n) = O(n)
ID: 65419918
*/
#include <iostream>
#include <algorithm>
#include <vector>

bool cmp(const std::pair<int, int>& a, const std::pair<int, int>& b)
{
	return a.second < b.second;
}

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);
	std::vector<std::pair<int, int>> events;
	int start, finish;
	while (std::cin >> start >> finish)
	{
		events.push_back({ start, finish });
	}
	std::sort(events.begin(), events.end(), cmp);
	int j = 0, ans = 1;
	for (int i = 1; i < events.size(); i++)
	{
		if (events[i].first >= events[j].second)
		{
			ans++;
			j = i;
		}
	}
	std::cout << ans << "\n";
	return 0;
}
