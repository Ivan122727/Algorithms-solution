/*
Дана строка длины n. Найти количество ее различных подстрок. Используйте суффиксный массив.
Построение суффиксного массива выполняйте за O(n log n). Вычисление количества различных подстрок выполняйте за O(n).
Время: T(n) = O(n log n)
Память: M(n) = O(n)
ID: 68797284
*/

#include <iostream>
#include <vector>
#include <algorithm>

const int N = 20000; 
std::vector<int> order(N);
int n, nowSuffAdd;

int GetOrder(const int& pos) 
{
    return (pos < n) ? order[pos] : -1;
}

bool cmp(std::pair<int, int>& a, std::pair<int, int>& b)
{
    return (a.first != b.first) ? a.first < b.first : GetOrder(a.second + nowSuffAdd) < GetOrder(b.second + nowSuffAdd);
}

std::vector<int> BuildSufArr(const std::string& s)
{
    n = (int)s.length();
    int cnt[26];
    for (int i = 0; i < 26; i++) 
    {
        cnt[i] = 0;
    }
    for (int i = 0; i < n; i++)
    {
        cnt[s[i] - 'a']++;
    }
    for (int i = 1; i < 26; i++)
    {
        cnt[i] += cnt[i - 1];
    }
    std::vector<std::pair<int, int>> suf;
    for (int i = 0; i < n; i++) 
    {
        order[i] = cnt[s[i] - 'a'] - 1;
        suf.push_back({ order[i], i });
    }
    sort(suf.begin(), suf.end(), cmp);
    nowSuffAdd = 1;
    while (nowSuffAdd <= n)
    {
        sort(suf.begin(), suf.end(), cmp);
        for(int i = (int)suf.size() - 2; i >= 0; i--)
        {
            if (order[suf[i].second + nowSuffAdd] < order[suf[i + 1].second + nowSuffAdd])
            {
                suf[i].first = i;
            }
            else 
            {
                suf[i].first = std::min(suf[i + 1].first, suf[i].first);
            }
        }
        for (auto& num : suf) 
        {
            order[num.second] = num.first;
        }
        nowSuffAdd += nowSuffAdd;
    }
    std::vector<int> answer;
    for (auto& num  : suf) 
    {
        answer.push_back(num.second);
    }
    nowSuffAdd = 0;
    return answer;
}

std::vector<int> BuildLCP(const std::string& s, const std::vector<int>& sa) 
{
    int n = (int)s.size(), k = 0;
    std::vector<int> lcp(n, 0);
    std::vector<int> rank(n, 0);
    for (int i = 0; i < n; i++) 
    {
        rank[sa[i]] = i;
    }
    for(int i = 0; i < n; i++, k ? k-- : 0) 
    {
        if (rank[i] == n - 1) 
        {
            k = 0;
            continue;
        }
        int j = sa[rank[i] + 1];
        while (i + k < n && j + k < n && s[i + k] == s[j + k])
        {
            k++;
        }
        lcp[rank[i]] = k;
    }
    lcp.pop_back();
    return lcp;
}

int GetCount(const std::string& s)
{
    std::vector<int> suf_ar = BuildSufArr(s);
    std::vector<int> lcp = BuildLCP(s, suf_ar);
    int n = (int)s.length();
    int c = 0;
    for (auto& x : lcp)
    {
        c += x;
    }
    return n * (n + 1) / 2 - c;
}

int main()
{
    std::string s;
    std::cin >> s;
    std::cout << GetCount(s) << "\n";
    return 0;
}