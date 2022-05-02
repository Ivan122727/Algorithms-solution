/*
Дано N кубиков.
Требуется определить каким количеством способов можно выстроить из этих кубиков пирамиду.
Каждый вышележащий слой пирамиды должен быть строго меньше нижележащего.
Асимптотика: T(n) = O(n)
Память: M(n) = O(n)
ID: 65816905
*/
#include <iostream>
#include <vector>

long long CountPers(int n, int k, std::vector<std::vector<long long>>& v)
{
	if (n < 0 || k < 0)
	{
		return 0;
	}
	if (k == 1)
	{
		if (n == 1)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else if (n < 3)
	{
		return 1;
	}
	if (!(v[n][k] < 0))
	{
		return v[n][k];
	}
	v[n][k] = CountPers(n, k - 1, v) + CountPers(n - k, k - 1, v);
	return v[n][k];

}

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);
	int n;
	std::cin >> n;
	std::vector<std::vector<long long>> v(n + 1);
	for (int i = 0; i < n + 1; i++)
	{
		for (int j = 0; j < n + 1; j++)
		{
			v[i].push_back(-1);
		}
	}
	std::cout << CountPers(n, n, v) << "\n";
	return 0;
}
