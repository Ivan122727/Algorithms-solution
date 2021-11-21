/*
Реализовать очередь с динамическим зацикленным буфером. Обрабатывать команды push back и pop front.
Каждая команда задаётся как 2 целых числа: a b.
a = 2 - pop front
a = 3 - push back
Если дана команда pop front, то число b - ожидаемое значение.
Если команда pop front вызвана для пустой структуры данных, то ожидается “-1”.
ID: 55366866
Асимптотика: O(n)
Память: T(n)
*/
#include <iostream>
#include <string>
#include <assert.h>

class Queue {
public:
    Queue(int size = 1) : bufferSize(size * 2), head(size), tail(size), countElem(0), buffer(new int[bufferSize]) {};

    ~Queue()
    {
        delete[] buffer;
    }

    bool empty() const
    {
        return head == tail;
    }

    int pop_front()
    {
        int result = buffer[head];
        if (--countElem << 2 == bufferSize)
        {
            ChangeBuffer(false);
        }
        head = (head + 1) % bufferSize;
        return result;
    }

    void push_back(int a)
    {
        buffer[tail] = a;
        if (++countElem == bufferSize)
        {
            ChangeBuffer(true);
        }
        tail = (tail + 1) % bufferSize;

    }

private:
    int* buffer;
    int bufferSize = 1;
    int head = 0;
    int tail = 0;
    int countElem = 0;

    void ChangeBuffer(bool increase)
    {
        if (increase)
        {
            bufferSize <<= 1;
        }
        else
        {
            bufferSize >>= 1;
        }
        int* temp = new int[bufferSize];
        for (int i = 0; i < countElem; i++)
        {
            temp[i] = buffer[head + i];
        }
        buffer = temp;
        head = 0;
        tail = countElem;
    }

};

bool NotPossibleOperation(Queue& arr, std::pair<int, int> input)
{
    return (arr.empty() && input.second != -1) || (!arr.empty() && arr.pop_front() != input.second);
}

void ProcessInput(std::string& answer, std::pair<int, int> input, Queue& arr)
{
    if (answer != "NO")
    {
        if (input.first == 3)
        {
            arr.push_back(input.second);
        }
        else
        {
            if (NotPossibleOperation(arr, input))
            {
                answer = "NO";
            }
        }
    }
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    int countOper;
    std::cin >> countOper;
    Queue arr(countOper);
    std::pair<int, int> input;
    std::string answer = "YES";
    for (int i = 0; i < countOper; i++)
    {
        std::cin >> input.first >> input.second;
        assert(input.first >= 2 && input.first <= 3);
        ProcessInput(answer, input, arr);
    }
    std::cout << answer << '\n';
    return 0;
}
