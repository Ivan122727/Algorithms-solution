/*
Найти в связном графе остовное дерево минимального веса.
Асимптотика: T(n) = O(n)
Память: M(n) = O(n)
ID:	68007987
*/
#include <iostream>
#include <set>
#include <vector>

int main()
{
	const int N = 100000;
	int n, m;
	std::cin >> n >> m;
	std::vector<std::pair<int, int>> g[N];
	for (int i = 0; i < m; i++)
	{
		int a, b, c;
		std::cin >> a >> b >> c;
		a--;
		b--;
		g[a].push_back({ b, c });
		g[b].push_back({ a, c });
	}
	std::vector<int> dist(n), was(n);
	for (int i = 0; i < n; i++)
	{
		dist[i] = 1e9;
		was[i] = 0;
	}
	dist[0] = 0;
	std::set<std::pair<int, int>> s;
	s.insert({ 0, 0 });
	int costMst = 0;
	while (!s.empty())
	{
		auto [distanse, v] = *s.begin();
		costMst += distanse;
		s.erase(s.begin());
		was[v] = 1;
		for (auto [u, cost] : g[v])
		{
			if (dist[u] > cost && was[u] == 0)
			{
				s.erase({ dist[u], u });
				dist[u] = cost;
				s.insert({ dist[u], u });
			}
		}
	}
	std::cout << costMst << "\n";
}