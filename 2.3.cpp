/*
Дан невзвешенный неориентированный граф.
Определить, является ли он двудольным. Требуемая сложность O(V+E)
Асимптотика: T(V, E) = O(V + E)
Память: M(n) = O(n)
ID: 67964077
*/
#include <iostream>
#include <vector>
#include <stack>

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

bool IsBipartiteGraph(int v, int curColor, ListGraph& g, std::vector<int>& color)
{
    std::stack<std::pair<int, int>> stk;
    stk.push({ v, curColor });
    std::pair<int, int> top;
    while (!stk.empty())
    {
        top = stk.top();
        stk.pop();
        color[top.first] = top.second;
        std::vector<int> vertices;
        g.FindAllAdjacentIn(top.first, vertices);
        for (auto& x : vertices)
        {
            if (!color[x])
            {
                curColor = (top.second == 1) ? 2 : 1;
                stk.push({ x, curColor });
            }
            else if (color[top.first] == color[x])
            {
                    return false;
            }
        }
    }
    return true;
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
    std::cout << ((IsBipartiteGraph(0, 1, g, color)) ? "YES\n" : "NO\n");
    return 0;
}
