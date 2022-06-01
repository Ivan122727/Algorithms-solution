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

void DFS(int v, double w, std::vector<int> u, bool& flag, int& n, std::vector<std::vector<double>>& g)
{
    if (u[v] == 2)
    {
        if (w > 1)
        {
            flag = true;
            return;
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (v == i || g[v][i] == -1)
        {
            continue;
        }
        if (u[i] != 1)
        {
            std::vector<int> u2(n);
            u2.assign(u.begin(), u.end());
            if (u2[i] != 2) u2[i] = 1;
            DFS(i, w * g[v][i], u2, flag, n, g);
        }
    }
}

void MainDFS(int x, int& n, bool& flag, std::vector<std::vector<double>>& g)
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
        DFS(i, g[x][i], u2, flag, n, g);
        break;
    }
}

int main()
{
    int n;
    std::cin >> n;
    std::vector<std::vector<double>> g(n, std::vector<double>(n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                g[i][j] = 0;
                continue;
            }
            std::cin >> g[i][j];
        }
    }
    bool flag = false;
    for (int i = 0; i < n; i++)
    {
        if (!flag)
        {
            MainDFS(i, n, flag, g);
        }
    }
    if (flag)
    {
        std::cout << "YES";
    }
    else
    {
        std::cout << "NO";
    }
    return 0;
}