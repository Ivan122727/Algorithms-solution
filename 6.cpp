/*
Найти в связном графе остовное дерево минимального веса.
Асимптотика: T(n) = O(n)
Память: M(n) = O(n)
ID:	68007987
*/
#include <iostream>
#include <set>
#include <vector>

class ListGraph
{
public:
	ListGraph(int size);
	virtual void AddEdge(int from, int to, int weight);
	virtual int VerticesCount() const;
	virtual void FindAllAdjacentIn(int vertex, std::vector<std::pair<int, int>>& vertices) const;
	virtual void FindAllAdjacentOut(int vertex, std::vector<std::pair<int, int>>& vertices) const;
	virtual void ChangeLen(int from, int to, int len);
private:
	int size;
	std::vector<std::vector<std::pair<int, int>>> g;
	std::vector<std::vector<std::pair<int, int>>> reversedG;
};

ListGraph::ListGraph(int size) : size(size), g(std::vector<std::vector<std::pair<int, int>>>(size, std::vector<std::pair<int, int>>())), reversedG(std::vector<std::vector<std::pair<int, int>>>(size, std::vector<std::pair<int, int>>())) {}

void ListGraph::AddEdge(int from, int to, int weight)
{
	g[from].push_back({ to, weight });
	reversedG[to].push_back({ from, weight });
}

int ListGraph::VerticesCount() const
{
	return size;
}

void ListGraph::FindAllAdjacentIn(int vertex, std::vector<std::pair<int, int>>& vertices) const
{
	for (auto x : reversedG[vertex])
	{
		vertices.push_back(x);
	}
}

void ListGraph::FindAllAdjacentOut(int vertex, std::vector<std::pair<int, int>>& vertices) const
{
	for (auto x : g[vertex])
	{
		vertices.push_back(x);
	}
}

void ListGraph::ChangeLen(int from, int to, int len)
{
	for (int i = 0; i < g[from].size(); i++)
	{
		if (g[from][i].first == to)
		{
			g[from][i].second = len;
		}
	}
}

int GetMinWay(ListGraph& g, int n)
{
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
		std::vector<std::pair<int, int>> vertices;
		g.FindAllAdjacentIn(v, vertices);
		for (auto [u, cost] : vertices)
		{
			if (dist[u] > cost && was[u] == 0)
			{
				s.erase({ dist[u], u });
				dist[u] = cost;
				s.insert({ dist[u], u });
			}
		}
	}
	return costMst;
}

int main()
{
	const int N = 100000;
	int n, m;
	std::cin >> n >> m;
	ListGraph g(N);
	int a, b, c;
	for (int i = 0; i < m; i++)
	{
		std::cin >> a >> b >> c;
		a--;
		b--;
		g.AddEdge(a, b, c);
		g.AddEdge(b, a, c);
	}
	std::cout << GetMinWay(g, n) << "\n";
	return 0;
}
