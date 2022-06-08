/*
Дан ориентированный граф.
Определите, какое минимальное число ребер необходимо добавить, чтобы граф стал сильносвязным.
В графе возможны петли
Асимптотика: T(n) = O(n)
Память: M(n) = O(n)
ID: 67964254
*/
#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>

class ListGraph
{
public:
    ListGraph(int size);
    virtual void AddEdge(int from, int to);
    virtual int VerticesCount() const;
    virtual int NeighboursCount(int vertex) const;
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

int ListGraph::NeighboursCount(int vertex) const
{
    return g[vertex].size();
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

void DFS1(int v, std::vector<bool>& used, std::vector<int>& order, ListGraph& g1)
{
    std::stack<int> stk;
    stk.push(v);
    int top;
    while (!stk.empty())
    {
        top = stk.top();
        stk.pop();
        used[top] = true;
        std::vector<int> vertices;
        g1.FindAllAdjacentIn(top, vertices);
        for (auto& x : vertices)
        {
            if (!used[x])
            {
                stk.push(x);
            }
        }
        order.push_back(top);
    }
}

void DFS2(int v, std::vector<bool>& used, std::vector<int>& component, ListGraph& g2)
{
    std::stack<int> stk;
    stk.push(v);
    int top;
    while (!stk.empty())
    {
        top = stk.top();
        stk.pop();
        used[top] = true;
        component.push_back(top);
        std::vector<int> vertices;
        g2.FindAllAdjacentIn(top, vertices);
        for (auto& x : vertices)
        {
            if (!used[x])
            {
                stk.push(x);
            }
        }
    }
}

int GetMinAdd(ListGraph& g1, ListGraph& g2, int n)
{
    std::vector<int> order;
    std::vector<int> component;
    std::vector<std::pair<int, int>> isST;
    std::vector<bool> used(n, false);
    for (int i = 0; i < n; i++)
    {
        if (!used[i])
        {
            DFS1(i, used, order, g1);
        }
    }
    used.assign(n, false);
    std::vector<int> dsu(n);
    int cursor = 0;
    for (int i = 0; i < n; i++)
    {
        int v = order[n - 1 - i];
        if (!used[v])
        {
            DFS2(v, used, component, g2);
            if (component.size() == n)
            {
                std::cout << 0;
                return 0;
            }
            for (auto x : component)
            {
                dsu[x] = cursor;
            }
            component.clear();
            cursor++;
        }
    }
    isST.resize(cursor, { 0, 0 });
    used.assign(n, false);
    for (int i = 0; i < n; i++)
    {
        std::vector<int> vertices;
        g1.FindAllAdjacentIn(i, vertices);
        for (auto& x : vertices)
        {
            if (dsu[i] != dsu[x])
            {
                isST[dsu[i]].first++;
                isST[dsu[x]].second++;
            }
        }
    }
    int s = 0, t = 0, q = 0;
    for (int i = 0; i < cursor; i++)
    {
        if (!isST[i].first && !isST[i].second)
        {
            q++;
        }
        else if ((isST[i].first || isST[i].second) && isST[i].first - isST[i].second != 0)
        {
            if (isST[i].first)
            {
                s++;
            }
            if (isST[i].second)
            {
                t++;
            }
        }
    }
    return std::max(s + q, t + q);
}

int main()
{

    int n, m;
    std::cin >> n >> m;
    if (n == 1)
    {
        std::cout << 0;
        return 0;
    }
    ListGraph g1(n), g2(n);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        std::cin >> a >> b;
        if (a == b)
        {
            continue;
        }
        a--;
        b--;
        bool isSecondRoad = false;
        std::vector<int> vertices;
        g1.FindAllAdjacentIn(a, vertices);
        for (auto& x : vertices)
        {
            if (x == b)
            {
                isSecondRoad = true;
                break;
            }
        }
        if (!isSecondRoad)
        {
            g1.AddEdge(a, b);
            g2.AddEdge(b, a);
        }
    }
    std::cout << GetMinAdd(g1, g2, n) << "\n";
    return 0;
}
