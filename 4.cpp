/*
Требуется отыскать самый короткий маршрут между городами.
Из города может выходить дорога, которая возвращается в этот же город.
Требуемое время работы O((N + M)log N),
Асимптотика: T(N, M) = O((N + M)log N)
Память: M(n) = O(n)
ID: 67974928
*/
#include <algorithm>
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

int GetMinWay(int from,  int to, int n, ListGraph& g)
{
    std::vector<int> distance(n, 1000000);
    distance[from] = 0;
    std::set<std::pair<int, int>> s;
    s.insert({ distance[from], from });
    while (!s.empty())
    {
        int v = s.begin()->second;
        s.erase(s.begin());
        std::vector<std::pair<int, int>> vertices;
        g.FindAllAdjacentIn(v, vertices);
        for (auto& x : vertices)
        {
            if (distance[v] + x.second < distance[x.first])
            {
                s.erase({ distance[x.first], x.first });
                distance[x.first] = distance[v] + x.second;
                s.insert({ distance[x.first], x.first });
            }
        }
    }
    return distance[to];
}

int main()
{
    int n, m;
    std::cin >> n >> m;
    ListGraph g(n);
    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        std::cin >> a >> b >> c;
        if (a == b) continue;
        bool isSecondRoad = false;
        std::vector<std::pair<int, int>> vertices;
        g.FindAllAdjacentIn(a, vertices);
        for (auto& x : vertices)
        {
            if (x.first == b)
            {
                isSecondRoad = true;
                if (x.second > c)
                {
                    std::cout << x.second << "\n";
                    g.ChangeLen(a, x.first, c);
                }
                break;
            }
        }
        vertices.clear();
        g.FindAllAdjacentIn(b, vertices);
        for (auto& x : vertices)
        {
            if (x.first == a)
            {
                if (x.second > c)
                {
                    g.ChangeLen(b, x.first, c);
                }
                break;
            }
        }
        if (!isSecondRoad)
        {
            g.AddEdge(a, b, c);
            g.AddEdge(b, a, c);
        }
    }
    int from, to;
    std::cin >> from >> to;
    std::cout << GetMinWay(from, to, n, g) << "\n";
    return 0;
}
