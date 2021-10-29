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

class Queue {
public:

    Queue() : bufferSize(1), head(0), tail(0), countElem(0)
    {
        buffer = new int[bufferSize];
    }

    Queue(int& size) : bufferSize(size << 1), head(size), tail(size), countElem(0)
    {
        buffer = new int[bufferSize];
    }

    ~Queue()
    {
        delete[] buffer;
    }

    bool empty()
    {
        return head == tail;
    }

    void IncreaseBuffer()
    {
        bufferSize <<= 1;
        int* temp = new int[bufferSize];
        for (int i = 0; i < countElem; i++)
        {
            temp[i] = buffer[head + i];
        }
        delete[] buffer;
        buffer = temp;
        head = 0;
        tail = countElem + 1;
    }

    void ReduceBuffer()
    {
        bufferSize >>= 1;
        int* temp = new int[bufferSize];
        for (int i = 0; i < countElem; i++)
        {
            temp[i] = buffer[head + i];
        }
        delete[] buffer;
        buffer = temp;
        head = 0;
        tail = countElem + 1;
    }

    void push_back(int& a)
    {
        countElem++;
        if (countElem == bufferSize)
        {
            IncreaseBuffer();
        }
        buffer[tail] = a;
        tail = (tail + 1) % bufferSize;

    }

    int pop_front()
    {
        if (countElem << 2 == bufferSize)
        {
            ReduceBuffer();
        }
        int result = buffer[head];
        head = (head + 1) % bufferSize;
        return result;
    }

private:
    int* buffer;
    int bufferSize;
    int head;
    int tail;
    int countElem;
};

std::string Solve()
{
    int countOper, oper, num;
    std::cin >> countOper;
    Queue arr(countOper);
    for (int i = 0; i < countOper; i++)
    {
        std::cin >> oper >> num;
        switch (oper)
        {
        case 3:
            arr.push_back(num);
            break;
        default:
            if ((arr.empty() && num != -1) || (!arr.empty() && arr.pop_front() != num))
            {
                return "NO";
            }
            break;
        }
    }
    return "YES";
}
int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cout << Solve();
}


