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

class Queue {
public:
    Queue(int size = 1) : bufferSize(size * 2), head(size), tail(size), countElem(0), buffer(new int[bufferSize]) {};

    ~Queue()
    {
        delete[] buffer;
    }

    const bool empty()
    {
        return head == tail;
    }

    int pop_front()
    {
        countElem--;
        int result = buffer[head];
        if (countElem << 2 == bufferSize)
        {
            ChangeBuffer(false);
        }
        head = (head + 1) % bufferSize;
        return result;
    }

    void push_back(int a)
    {
        countElem++;
        buffer[tail] = a;
        if (countElem == bufferSize)
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

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    int countOper, oper, num;
    std::string answer = "YES";
    std::cin >> countOper;
    Queue arr(countOper);
    for (int i = 0; i < countOper; i++)
    {
        std::cin >> oper >> num;
        if (oper == 3)
        {
            arr.push_back(num);
        }
        else
        {
            if ((arr.empty() && num != -1) || (!arr.empty() && arr.pop_front() != num))
            {
                answer = "NO";
            }
        }
    }
    std::cout << answer << '\n';
    return 0;
}


