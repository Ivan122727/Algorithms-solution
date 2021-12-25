/*
Дано число N < 10^6 и последовательность целых чисел из [-231..231] длиной N.
Требуется построить бинарное дерево поиска, заданное наивным порядком вставки. Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
Выведите элементы в порядке level-order (по слоям, “в ширину”).
Асипмтотика: 0(n)
Память: T(n)
ID: 62900635	
*/

#include <iostream>
#include <cassert>
#include <queue>
#include <string>

struct BinnaryNode
{
    int value;
    BinnaryNode* Left;
    BinnaryNode* Right;
    BinnaryNode* Parent;
    explicit BinnaryNode(int value = 0) : value(value), Parent(nullptr), Left(nullptr), Right(nullptr) {}
};

std::string BFS(BinnaryNode* root)
{
    std::string answer = "";
    std::queue<BinnaryNode*> q;
    if (root != nullptr)
    {
        q.push(root);
    }
    while (!q.empty())
    {
        BinnaryNode* node = q.front();
        q.pop();
        answer += std::to_string(node->value) + " ";
        if(node->Left != nullptr)
        {
            q.push(node->Left);
        }
        if (node->Right != nullptr)
        {
            q.push(node->Right);
        }
    }
    return answer;
}

void AddElem(BinnaryNode* root, BinnaryNode* newNode)
{
    assert(root != nullptr);
    assert(newNode != nullptr);
    //Left:
    if (newNode->value < root->value)
    {
        if (root->Left != nullptr)
        {
            AddElem(root->Left, newNode);
        }
        else
        {
            root->Left = newNode;
            newNode->Parent = root;
        }
    }
    //Right:
    else
    {
        if (root->Right != nullptr)
        {
            AddElem(root->Right, newNode);
        }
        else
        {
            root->Right = newNode;
            newNode->Parent = root;
        }
    }

}

void CleanTree(BinnaryNode* node)
{
    if (node == nullptr)
    {
        return;
    }
    CleanTree(node->Left);
    CleanTree(node->Right);
    delete node;
}

int main()
{
    int n, value;
    std::cin >> n >> value;
    BinnaryNode* root = new BinnaryNode(value);
    for (int i = 1; i < n; i++)
    {
        std::cin >> value;
        AddElem(root, new BinnaryNode(value));
    }
    std::cout << BFS(root);
    CleanTree(root);
    std::cout << "\n";
    return 0;
}