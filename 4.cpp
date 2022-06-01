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

void DFS1(int v, std::vector<bool>& used, std::vector<int>& order, std::vector<std::vector<int>>& g1)
{
    used[v] = true;
    for (int i = 0; i < g1[v].size(); i++)
    {
        if (!used[g1[v][i]])
        {
            DFS1(g1[v][i], used, order, g1);
        }
    }
    order.push_back(v);
}

void DFS2(int v, std::vector<bool>& used, std::vector<int>& component, std::vector<std::vector<int>>& g2)
{
    used[v] = true;
    component.push_back(v);
    for (int i = 0; i < g2[v].size(); i++)
    {
        if (!used[g2[v][i]])
        {
            DFS2(g2[v][i], used, component, g2);
        }
    }
}

int main()
{
    std::vector<int> order;
    std::vector<int> component;
    std::vector<std::pair<int, int>> isST;
    int n, m;
    std::cin >> n >> m;
    if (n == 1)
    {
        std::cout << 0;
        return 0;
    }
    std::vector<std::vector<int>> g1(n), g2(n);
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
        for (int j = 0; j < g1[a].size(); j++)
        {
            if (g1[a][j] == b)
            {
                isSecondRoad = true;
                break;
            }
        }
        if (!isSecondRoad)
        {
            g1[a].push_back(b);
            g2[b].push_back(a);
        }
    }
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
        for (int j = 0; j < g1[i].size(); j++)
        {
            if (dsu[i] != dsu[g1[i][j]])
            {
                isST[dsu[i]].first++;
                isST[dsu[g1[i][j]]].second++;
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
    std::cout << std::max(s + q, t + q) << "\n";
    return 0;
}