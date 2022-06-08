/*
Найдите все вхождения шаблона в строку. Длина шаблона – p, длина строки – n. С помощью z-функции. 
Время O(n + p), доп. память – O(p).
p ≤ 30000, n ≤ 300000.
Время: T(n, p) = O(n + p)
Память: M(n) = O(n)
ID: 68779043
*/
#include <iostream>
#include <vector>
#include <string>

std::vector<int> GetZ(const std::string & s, int n)
{
    std::vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; i++) 
    {
        if (i <= r)
        {
            z[i] = std::min(r - i + 1, z[i - l]);
        }
        while(i + z[i] < n && s[z[i]] == s[i + z[i]])
        {
            z[i]++;
        }
        if (i + z[i] - 1 > r)
        {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

std::vector<int> GetOccurrences(const std::string& s, const std::string& sample)
{
    std::vector<int> occurrences;
    std::string c = sample + "#" + s;
    std::vector<int> z = GetZ(c, c.length());
    for (int i = sample.length() + 1; i < c.length(); i++)
    {
        if (z[i] == sample.length())
        {
            occurrences.push_back(i - sample.length() - 1);
        }
    }
    return occurrences;
}

int main()
{
    std::string sample, s;
    std::cin >> sample >> s;
    std::vector<int> occurrences = GetOccurrences(s, sample);
    for (auto& occurrence : occurrences)
    {
        std::cout << occurrence << " ";
    }
    std::cout << "\n";
    return 0;
}