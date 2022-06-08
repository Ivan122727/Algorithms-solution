/*
Необходимо написать торгового советника для поиска арбитража.
Арбитраж - это торговля по цепочке различных валют в надежде заработать на небольших различиях в коэффициентах. Например, есть следующие курсы валют:
GBP/USD: 0.67
RUB/GBP: 78.66
USD/RUB: 0.02
Имея 1$ и совершив цикл USD->GBP->RUB->USD, получим 1.054$. Таким образом заработав
Асимптотика: T(n) = O(n)
Память: M(n) = O(n)
ID: 67975008
*/
#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>

class ListGraph
{
public:
    ListGraph(int size);
    virtual void AddEdge(int from, int to, double weight);
    virtual int VerticesCount() const;
    virtual void FindAllAdjacentIn(int vertex, std::vector<std::pair<int, double>>& vertices) const;
    virtual void FindAllAdjacentOut(int vertex, std::vector<std::pair<int, double>>& vertices) const;
    virtual double GetCost(int from, int to) const;
private:
    int size;
    std::vector<std::vector<std::pair<int, double>>> g;
    std::vector<std::vector<std::pair<int, double>>> reversedG;
};

ListGraph::ListGraph(int size) : size(size), g(std::vector<std::vector<std::pair<int, double>>>(size, std::vector<std::pair<int, double>>())), reversedG(std::vector<std::vector<std::pair<int, double>>>(size, std::vector<std::pair<int, double>>())) {}

void ListGraph::AddEdge(int from, int to, double weight)
{
    g[from].push_back({ to, weight });
    reversedG[to].push_back({ from, weight });
}

int ListGraph::VerticesCount() const
{
    return size;
}

void ListGraph::FindAllAdjacentIn(int vertex, std::vector<std::pair<int, double>>& vertices) const
{
    for (auto x : reversedG[vertex])
    {
        vertices.push_back(x);
    }
}

double ListGraph::GetCost(int from, int to) const
{
    for (int i = 0; i < g[from].size(); i++)
    {
        if (g[from][i].first == to)
        {
            return g[from][i].second;
        }
    }
}

void ListGraph::FindAllAdjacentOut(int vertex, std::vector<std::pair<int, double>>& vertices) const
{
    for (auto i : g[vertex])
    {
        vertices.push_back(i);
    }
}

void DFS(int v, double w, std::vector<int> u, bool& flag, int& n, ListGraph& g)
{
    std::stack<std::pair<std::pair<int, double>, std::vector<int>>> stk;
    stk.push({ { v, w }, u });
    std::pair<std::pair<int, double>, std::vector<int>> top;
    while (!stk.empty())
    {
        top = stk.top();
        stk.pop();
        if (u[top.first.first] == 2)
        {
            if (top.first.second > 1)
            {
                flag = true;
                return;
            }
        }
        for (int i = 0; i < n; i++)
        {
            if (top.first.first == i || g.GetCost(top.first.first, i) == -1)
            {
                continue;
            }
            if (u[i] != 1)
            {
                std::vector<int> u2(n);
                u2.assign(u.begin(), u.end());
                if (u2[i] != 2)
                {
                    u2[i] = 1;
                }
                stk.push({ {i, top.first.first * g.GetCost(top.first.first, i) }, u2 });
            }
        }
    }
    
}

void MainDFS(int x, int& n, bool& flag, ListGraph& g)
{
    std::vector<int> u(n, 0);
    u[x] = 2;
    for (int i = 0; i < n; i++)
    {
        if (x == i)
        {
            continue;
        }
        std::vector<int> u2(n);
        u2.assign(u.begin(), u.end());
        if (u2[i] != 2)
        {
            u2[i] = 1;
        }
        DFS(i, g.GetCost(x, i), u2, flag, n, g);
        break;
    }
}

int main()
{
    int n;
    std::cin >> n;
    ListGraph g(n);
    double cost;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                g.AddEdge(i, j, 0);
                continue;
            }
            std::cin >> cost;
            g.AddEdge(i, j, cost);
        }
    }
    bool hasProfite = false;
    for (int i = 0; i < n; i++)
    {
        if (!hasProfite)
        {
            MainDFS(i, n, hasProfite, g);
        }
    }
    std::cout << ((hasProfite) ? "YES\n" : "NO\n");
    return 0;
}
