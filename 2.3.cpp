/*
Дан невзвешенный неориентированный граф.
Определить, является ли он двудольным. Требуемая сложность O(V+E)
Асимптотика: T(V, E) = O(V + E)
Память: M(n) = O(n)
ID: 67964077
*/
#include <iostream>
#include <vector>

class ListGraph
{
public:
    ListGraph(int size);
    virtual void AddEdge(int from, int to);
    virtual int VerticesCount() const;
    virtual void FindAllAdjacentIn(int vertex, std::vector<int>& vertices) const;
    virtual void FindAllAdjacentOut(int vertex, std::vector<int>& vertices) const;
private:
    int size;
    std::vector<std::vector<int>> g;
    std::vector<std::vector<int>> reversedG;
};

ListGraph::ListGraph(int size) : size(size), g(std::vector<std::vector<int>>(size, std::vector<int>())), reversedG(std::vector<std::vector<int>>(size, std::vector<int>())) {}

void ListGraph::AddEdge(int from, int to)
{
    g[from].push_back(to);
    reversedG[to].push_back(from);
}

int ListGraph::VerticesCount() const
{
    return size;
}

void ListGraph::FindAllAdjacentIn(int vertex, std::vector<int>& vertices) const
{
    for (int x : reversedG[vertex])
    {
        vertices.push_back(x);
    }
}

void ListGraph::FindAllAdjacentOut(int vertex, std::vector<int>& vertices) const 
{
    for (int i : g[vertex])
    {
        vertices.push_back(i);
    }
}

void DFS(int v, int curColor, ListGraph& g, std::vector<int>& color, bool& bipartiteGraph)
{
    if (!bipartiteGraph)
    {
        return;
    }
    color[v] = curColor;
    std::vector<int> vertices;
    g.FindAllAdjacentIn(v, vertices);
    for (auto& x : vertices)
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
    ListGraph g(n);
    std::vector<int> color(n);
    int a, b;
    for (int i = 0; i < m; i++)
    {
        std::cin >> a >> b;
        g.AddEdge(a, b);
        g.AddEdge(b, a);
    }
    bool bipartiteGraph = true;
    DFS(0, 1, g, color, bipartiteGraph);
    if (bipartiteGraph)
    {
        std::cout << "YES\n";
    }
    else
    {
        std::cout << "NO\n";
    }
    return 0;
}
