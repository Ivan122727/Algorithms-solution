/*
Дано невзвешенное дерево.
Расстоянием между двумя вершинами будем называть количество ребер в пути, соединяющем эти две вершины.
Для каждой вершины определите расстояние до самой удаленной от нее вершины.
Время работы должно быть O(n)
Асимптотика: T(n) = O(n)
Память: M(n) = O(n)
ID: 66218436
*/
#include <iostream>
#include <vector>
typedef std::vector<std::vector<int>> CTree;
void Traverse(const CTree& tree, int node, std::vector<int>& heights)
{
    for (int child : tree[node])
    {
        Traverse(tree, child, heights);
    }
    heights[node] = 0;
    for (int child : tree[node])
    {
        if (heights[child] + 1 > heights[node])
        {
            heights[node] = heights[child] + 1;
        }
    }
}

std::ostream& operator<<(std::ostream& os, const std::vector<int>& data)
{
    for (int i = 0; i < data.size(); i++)
    {
        os << i << " " << data[i] << "\n";
    }
    return os;
}

void Traverse2(const CTree& tree, int node, const std::vector<int>& lengthsDown, std::vector<int>& lengthsUp)
{
    int maxLengthDown = -1;
    int secondMaxLengthDown = -1;
    for (int child : tree[node])
    {
        if (lengthsDown[child] >= maxLengthDown)
        {
            secondMaxLengthDown = maxLengthDown;
            maxLengthDown = lengthsDown[child];
        }
        else if (lengthsDown[child] > secondMaxLengthDown)
        {
            secondMaxLengthDown = lengthsDown[child];
        }
    }

    for (int child : tree[node])
    {
        lengthsUp[child] = lengthsUp[node] + 1;
        if (lengthsDown[child] == maxLengthDown)
        {
            lengthsUp[child] = std::max(lengthsUp[child], secondMaxLengthDown + 2);
        }
        else
        {
            lengthsUp[child] = std::max(lengthsUp[child], maxLengthDown + 2);
        }
        Traverse2(tree, child, lengthsDown, lengthsUp);
    }
}

std::vector<int> CalcMaxDistance(const CTree& tree)
{
    std::vector<int> lengthsDown(tree.size());
    Traverse(tree, 0, lengthsDown);
    std::vector<int> lengthsUp(tree.size());
    Traverse2(tree, 0, lengthsDown, lengthsUp);
    std::vector<int> result(tree.size());
    for (int i = 0; i < lengthsDown.size(); i++)
    {
        result[i] = std::max(lengthsDown[i], lengthsUp[i]);
    }
    return result;
}

int main()
{
    int n;
    std::cin >> n;
    CTree tree(n);
    for (int i = 0; i < n - 1; i++)
    {
        int parent, child;
        std::cin >> parent >> child;
        tree[parent].push_back(child);
    }
    std::vector<int> result = CalcMaxDistance(tree);
    for (int v : result)
    {
        std::cout << v << "\n";
    }
    return 0;
}