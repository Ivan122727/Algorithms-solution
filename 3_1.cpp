/*
ID: 64501700
Условие:
В одной военной части решили построить в одну шеренгу по росту.
Т.к. часть была далеко не образцовая, то солдаты часто приходили не вовремя, а то их и вовсе приходилось выгонять из шеренги за плохо начищенные сапоги. 
Однако солдаты в процессе прихода и ухода должны были всегда быть выстроены по росту – сначала самые высокие, а в конце – самые низкие.
За расстановку солдат отвечал прапорщик, который заметил интересную особенность – все солдаты в части разного роста.
Ваша задача состоит в том, чтобы помочь прапорщику правильно расставлять солдат, а именно для каждого приходящего солдата указывать, перед каким солдатом в строе он должен становится.
Требуемая скорость выполнения команды - O(log n).
Асимптотика: T(n) = O(n log n)
Память: M(n) = O(n)
*/
#include <iostream>
#include <stack>
#include <vector>

template<class T>
struct Node
{
    T value;
    int height;
    int number;
    Node<T>* left = nullptr;
    Node<T>* right = nullptr;
    explicit Node(const T& value) : value(value), height(1), number(1) {};
};

template<class T>
class Tree
{
public:
    Tree() {};
    int Height(Node<T>* node)
    {
        return node ? node->height : 0;
    }
    int BalanceFactor(Node<T>* node)
    {
        return Height(node->right) - Height(node->left);
    }
    void FixHeightTree(Node<T>* node)
    {
        int hLeft = Height(node->left);
        int hRight = Height(node->right);
        node->height = (hLeft > hRight ? hLeft : hRight) + 1;
    }
    void FixNum(Node<T>* node)
    {
        node->number = ((node->right == 0) ? 0 : node->right->number) + ((node->left == 0) ? 0 : node->left->number) + 1;
    }
    Node<T>* RotateToLeft(Node<T>* tmp)
    {
        Node<T>* node = tmp->right;
        tmp->right = node->left;
        node->left = tmp;
        FixNum(tmp);
        FixNum(node);
        FixHeightTree(tmp);
        FixHeightTree(node);
        return node;
    }
    Node<T>* RotateToRight(Node<T>* tmp)
    {
        Node<T>* node = tmp->left;
        tmp->left = node->right;
        node->right = tmp;
        FixNum(tmp);
        FixNum(node);
        FixHeightTree(tmp);
        FixHeightTree(node);
        return node;
    }
    Node<T>* BalanceTree(Node<T>* node)
    {
        FixHeightTree(node);
        if (BalanceFactor(node) == 2)
        {
            if (BalanceFactor(node->right) < 0)
            {
                node->right = RotateToRight(node->right);
            }
            return RotateToLeft(node);
        }
        if (BalanceFactor(node) == -2)
        {
            if (BalanceFactor(node->left) > 0)
            {
                node->left = RotateToLeft(node->left);
            }
            return RotateToRight(node);
        }
        return node;
    }
    Node<T>* Insert(Node<T>* node, T elem, int& position)
    {
        if (!node)
        {
            return new Node<T>(elem);
        }
        (node->number)++;
        if (elem < node->value)
        {
            position += ((node->right == 0) ? 0 : node->right->number) + 1;
            node->left = Insert(node->left, elem, position);
        }
        else
        {
            node->right = Insert(node->right, elem, position);
        }
        return BalanceTree(node);
    }
    Node<T>* MinElem(Node<T>* node)
    {
        return node->left ? MinElem(node->left) : node;
    }
    Node<T>* RemoveMinElem(Node<T>* node)
    {
        if (node->left == 0)
        {
            return node->right;
        }
        node->left = RemoveMinElem(node->left);
        node->number--;
        return BalanceTree(node);
    }
    Node<T>* RemoveElem(Node<T>* node, const int& position)
    {
        if (!node)
        {
            return 0;
        }
        if (position >= node->number)
        {
            return node;
        }
        int sum = 0;
        std::stack<Node<T>*> nodesOfTree;
        while (true)
        {
            int numberFromRight = node->right ? node->right->number : 0;
            if (position - sum > numberFromRight)
            {
                nodesOfTree.push(node);
                node = node->left;
                sum += numberFromRight + 1;
            }
            else if (position - sum < numberFromRight)
            {
                if (node->right != 0)
                {
                    nodesOfTree.push(node);
                    node = node->right;
                }
                else
                {
                    break;
                }
            }
            else
            {
                Node<T>* left = node->left;
                Node<T>* right = node->right;
                int value = node->value;
                delete node;
                if (right == 0)
                {
                    if (left == 0)
                    {
                        if (!nodesOfTree.empty())
                        {
                            node = nodesOfTree.top();
                            nodesOfTree.pop();
                            if (node->value > value)
                            {
                                node->left = 0;
                            }
                            else
                            {
                                node->right = 0;
                            }
                            node->number--;
                        }
                        else
                        {
                            return 0;
                        }
                    }
                    else
                    {
                        node = left;
                    }
                }
                else
                {
                    Node<T>* min = MinElem(right);
                    min->right = RemoveMinElem(right);
                    min->left = left;
                    FixNum(min);
                    node = BalanceTree(min);
                }
                break;
            }
        }
        Node<T>* newNode;
        while (!nodesOfTree.empty())
        {
            newNode = nodesOfTree.top();
            nodesOfTree.pop();
            newNode->number--;
            if (newNode->value > node->value)
            {
                newNode->left = node;
            }
            else
            {
                newNode->right = node;
            }
            node = BalanceTree(newNode);
        }
        return node;
    }
};

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    int n;
    std::cin >> n;
    std::vector<int> order;
    int value, command, position;
    Node<int>* root = nullptr;
    Tree<int> tree;
    for (int i = 0; i < n; i++)
    {
        std::cin >> command;
        if (command == 1)
        {
            position = 0;
            std::cin >> value;
            root = tree.Insert(root, value, position);
            order.push_back(position);
        }
        else if (command == 2)
        {
            std::cin >> value;
            root = tree.RemoveElem(root, value);
        }
    }
    for (int i = 0; i < order.size(); ++i)
    {
        std::cout << order[i] << "\n";
    }
    return 0;
}
