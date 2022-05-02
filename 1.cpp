/*
Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией.
Хранимые строки непустые и состоят из строчных латинских букв.
Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.
Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает 3/4.
Структура данных должна поддерживать операции добавления строки в множество, удаления строки из множества и проверки принадлежности данной строки множеству.
Вариант 2. Для разрешения коллизий используйте двойное хеширование.
Асимптотика: T(n) = O(n)
Память: M(n) = O(n)
ID: 66218757
*/
#include <iostream>
#include <string>
#include <vector>

struct HashTable
{
    std::vector<std::string> list;
    int size;
    int buffer;
    HashTable() : list(std::vector<std::string>(8)), size(8), buffer(0) {}
    void Rehash()
    {
        size *= 2;
        std::vector<std::string> temp(size);
        buffer = 0;
        std::swap(list, temp);
        for (int i = 0; i < size / 2; ++i)
        {
            if (temp[i] != "" && temp[i] != "deleted")
            {
                Add(temp[i]);
            }
        }
    }
    const float overflow = 0.75;
    int Horner1(std::string data, int size)
    {
        int index = 0;
        for (auto elem : data)
        {
            index = (index * (size - 1) + elem) % size;
        }
        return index;
    }
    int Horner2(std::string value, int size)
    {
        int index = 0;
        for (auto elem : value)
        {
            index = (index * (size + 1) + elem) % size;
        }
        return (index * 2 + 1) % size;
    }
    bool Add(std::string data)
    {
        if (buffer >= size * overflow)
        {
            Rehash();
        }
        int h1 = Horner1(data, size);
        int h2 = Horner2(data, size);
        int i = 0;
        while (i <= buffer && list[h1] != data)
        {
            if (list[h1] == "")
            {
                list[h1] = data;
                buffer++;
                return true;
            }
            h1 = (h1 + h2) % size;
            i++;
        }
        return false;
    }
    bool Find(std::string data)
    {
        int h1 = Horner1(data, size);
        int h2 = Horner2(data, size);
        int i = 0;
        while (i <= buffer && list[h1] != "")
        {
            if (list[h1] == data)
            {
                return true;
            }
            h1 = (h1 + h2) % size;
        }
        return false;
    }
    bool Delete(std::string data)
    {
        int h1 = Horner1(data, size);
        int h2 = Horner2(data, size);
        int i = 0;
        while (i <= buffer && list[h1] != "")
        {
            if (list[h1] == data)
            {
                list[h1] = "deleted";
                return true;
            }
            h1 = (h1 + h2) % size;
            i++;
        }
        return false;
    }
};

int main()
{
    HashTable array;
    char command;
    std::string word;
    while (std::cin >> command >> word)
    {
        if (command == '?')
        {
            std::cout << (array.Find(word) ? "OK" : "FAIL") << "\n";
        }
        if (command == '+') {
            std::cout << (array.Add(word) ? "OK" : "FAIL") << "\n";
        }
        if (command == '-') {
            std::cout << (array.Delete(word) ? "OK" : "FAIL") << "\n";
        }
    }
    return 0;
}
