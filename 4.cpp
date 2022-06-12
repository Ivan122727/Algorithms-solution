/*
Шаблон поиска задан строкой длины m, в которой кроме обычных символов могут встречаться символы “?”.
Найти позиции всех вхождений шаблона в тексте длины n. Каждое вхождение шаблона предполагает, что все обычные символы совпадают с соответствующими из текста, а вместо символа “?” в тексте встречается произвольный символ.
Гарантируется, что сам “?” в тексте не встречается.
Время работы - O(n + m + Z), где Z - общее число вхождений подстрок шаблона “между вопросиками” в исходном тексте.
Время: T(n, m, Z) = O(n + m + Z)
Память: M(n, m) = O(n + m)
ID: 68782454
*/
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

struct Node
{
    std::unordered_map<char, int> next;  // next[i] - вершина в которую переходим по букве i в обычном Боре
    bool isTerminal;  // является ли вершина терминальной
    int parent;  // номер вершины-родителя
    char parentCh;  // символ, по которому попадаем из родителя в нашу вершину
    int link;  // суффиксная ссылка
    std::unordered_map<char, int> go;  // переходы по каждому из символов (в модифицированном Боре)
    std::vector<int> answers;  // все терминальные вершины, в которые можно попасть по суфф. ссылкам
    std::vector<int> patternNumbers;  // номера шаблонов, которым соответствует вершина
    Node() : next({}), isTerminal(true), parent(-1), parentCh(-1), link(-1), go({}), answers({}), patternNumbers({}) {}
    Node(const int& parent, const char& parentCh) : next({}), isTerminal(true), parent(parent), parentCh(parentCh), link(-1), go({}), answers({}), patternNumbers({}) {}
};

class Automata
{
public:
    Automata();
    void AddString(const std::string& s, const int& patternNumber);
    int Go(const int& vertex, const char& ch);
    int SuffLink(const int& vertex);
    std::vector<int> FindingTerminalVertices(const int& vertex);
    std::vector<int> GetPattern(const int& vertex);
private:
    std::vector<Node> trie;
};

Automata::Automata()
{
    Node root;
    root.link = -1;
    trie.push_back(root);
}

void Automata::AddString(const std::string& s, const int& patternNumber)
{
    int currentVertex = 0;
    for (auto& ch : s)
    {
        if (!trie[currentVertex].next[ch])
        {
            size_t trieSize = trie.size();
            Node newVertex(currentVertex, ch);
            trie.push_back(newVertex);
            trie[currentVertex].next[ch] = trie.size() - 1;
        }
        currentVertex = trie[currentVertex].next[ch];
    }
    trie[currentVertex].patternNumbers.push_back(patternNumber);
}

int Automata::Go(const int& vertex, const char& ch)
{
    if (!trie[vertex].go[ch])
    {
        if (trie[vertex].next[ch])
        {
            trie[vertex].go[ch] = trie[vertex].next[ch];
        }
        else
        {
            if (vertex == 0)
            {
                trie[vertex].go[ch] = 0;
            }
            else
            {
                trie[vertex].go[ch] = Go(SuffLink(vertex), ch);
            }
        }
    }
    return trie[vertex].go[ch];
}

int Automata::SuffLink(const int& vertex)
{
    if (trie[vertex].link == -1)
    {
        if (vertex == 0 || trie[vertex].parent == 0)
        {
            trie[vertex].link = 0;
        }
        else
        {
            trie[vertex].link = Go(SuffLink(trie[vertex].parent), trie[vertex].parentCh);
        }
    }
    return trie[vertex].link;
}

std::vector<int> Automata::FindingTerminalVertices(const int& vertex)
{
    if (trie[vertex].answers.size() > 0)
    {
        return trie[vertex].answers;
    }
    int currentVertex = vertex;
    while (currentVertex != 0)
    {
        if (trie[currentVertex].isTerminal)
        {
            trie[vertex].answers.push_back(currentVertex);
        }
        currentVertex = SuffLink(currentVertex);
    }
    return trie[vertex].answers;
}

std::vector<int> Automata::GetPattern(const int& vertex)
{
    if (trie[vertex].isTerminal)
    {
        return trie[vertex].patternNumbers;
    }
    else
    {
        return std::vector<int>(0);
    }
}

std::vector<int> GetOccurrences(const std::string& sample, const std::string& s)
{
    Automata automata;
    std::string currentStr = "";
    std::vector<int> sampleIndex(0);  // вхождения шаблонов без '?' в исходном шаблоне
    std::vector<int> sampleLength(0);  // длины шаблонов без '?'
    bool flag = true;  // последний прочитанный символ - '?' ?
    for (int i = 0; i < sample.length(); i++)
    {
        char ch = sample[i];
        if (ch != '?')
        {
            currentStr += ch;
            if (flag)
            {
                sampleIndex.push_back(i);
            }
            flag = false;
        }
        else
        {
            if (currentStr != "")
            {
                automata.AddString(currentStr, sampleIndex.size() - 1);
                sampleLength.push_back(currentStr.length());
                currentStr = "";
            }
            flag = true;
        }
    }
    automata.AddString(currentStr, sampleIndex.size() - 1);
    sampleLength.push_back(currentStr.length());
    std::vector<int> countOccurrences(s.length(), 0);  // c[i] - количество возможных вхождений на i символе
    int currentVertex = 0;
    for (int i = 0; i < s.length(); i++)
    {
        char ch = s[i];
        currentVertex = automata.Go(currentVertex, ch);
        std::vector <int> terminalVertices = automata.FindingTerminalVertices(currentVertex);
        // для каждой вершины из terminalVertices найдем, какому шаблону она соответствует, а затем по номеру шаблона
        // определим, на какой позиции она находится в исходном шаблоне с "?"
        for (auto& vertex : terminalVertices)
        {
            std::vector<int> patternNumbers = automata.GetPattern(vertex);
            for (auto& patternNumber : patternNumbers)
            {
                if (i - sampleLength[patternNumber] - sampleIndex[patternNumber] + 1 >= 0)
                {
                    countOccurrences[i - sampleLength[patternNumber] - sampleIndex[patternNumber] + 1]++;
                }
            }
        }
    }
    std::vector<int> occurrences;
    for (int i = 0; i < countOccurrences.size(); i++)
    {
        if (countOccurrences[i] == sampleIndex.size() && i + sample.length() <= s.length())
        {
            occurrences.push_back(i);
        }
    }
    return occurrences;
}

int main()
{
    std::string sample, s;
    std::cin >> sample >> s;
    std::vector<int> occurrences = GetOccurrences(sample, s);
    for (auto& occurrence : occurrences)
    {
        std::cout << occurrence << " ";
    }
    std::cout << "\n";
    return 0;
}
