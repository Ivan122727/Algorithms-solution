/*
Дан невзвешенный неориентированный граф.
Определить, является ли он двудольным. Требуемая сложность O(V+E)
Асимптотика: T(V, E) = O(V + E)
Память: M(n) = O(n)
ID: 67964077
*/
#include <iostream>
#include <vector>

void DFS(int v, int curColor, std::vector<std::vector<int>>& g, std::vector<int>& color, bool& bipartiteGraph)
{
    if (!bipartiteGraph)
    {
        return;
    }
    color[v] = curColor;
    for (auto x : g[v])
    {
        if (!color[x])
        {
            if (curColor == 1)
            {
                DFS(x, 2, g, color, bipartiteGraph);
            }
            else if (curColor == 2)
            {
                DFS(x, 1, g, color, bipartiteGraph);
            }
        }
        else
        {
            if (color[v] == color[x])
            {
                bipartiteGraph = false;
                return;
            }
        }
    }
}

int main()
{
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> g(n);
    std::vector<int> color(n);
    int a, b;
    for (int i = 0; i < m; i++)
    {
        std::cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    bool bipartiteGraph = true;
    DFS(0, 1, g, color, bipartiteGraph);
    if (bipartiteGraph)
    {
        std::cout << "YES";
    }
    else
    {
        std::cout << "NO";
    }
    return 0;
}