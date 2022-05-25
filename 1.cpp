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
#include <assert.h>

template<class THash, class T>
struct HashTable
{
public:
    HashTable() : list(THash(8)), size(8), buffer(0) {}
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
    int Horner1(T data, int size)
    {
        int index = 0;
        for (auto elem : data)
        {
            index = (index * (size - 1) + elem) % size;
        }
        return index;
    }

    int Horner2(T value, int size)
    {
        int index = 0;
        for (auto elem : value)
        {
            index = (index * (size + 1) + elem) % size;
        }
        return (index * 2 + 1) % size;
    }
    bool Add(const T& data)
    {
        if (buffer >= size * overflow)
        {
            Rehash();
        }
        int h1 = Horner1(data, size);
        int h2 = Horner2(data, size);
        for (int i = 0; i <= buffer; i++)
        {
            if (list[h1] == data)
            {
                break;
            }
            if (list[h1] == "")
            {
                list[h1] = data;
                buffer++;
                return true;
            }
            h1 = (h1 + h2) % size;
        }
        return false;
    }
    bool Find(const T& data)
    {
        int h1 = Horner1(data, size);
        int h2 = Horner2(data, size);
        for (int i = 0; i <= buffer; i++)
        {
            if (list[h1] == "")
            {
                break;
            }
            if (list[h1] == data)
            {
                return true;
            }
            h1 = (h1 + h2) % size;
        }
        return false;
    }
    bool Delete(const T& data)
    {
        int h1 = Horner1(data, size);
        int h2 = Horner2(data, size);
        for (int i = 0; i <= buffer; i++)
        {
            if (list[h1] == "")
            {
                break;
            }
            if (list[h1] == data)
            {
                list[h1] = "deleted";
                return true;
            }
            h1 = (h1 + h2) % size;
        }
        return false;
    }
private:
    THash list;
    int size;
    int buffer;
};

int main()
{
    HashTable<std::vector<std::string>, std::string> array;
    char command;
    std::string word;
    while (std::cin >> command >> word)
    {
        assert(command == '+' || command == '-' || command == '?');
        if (command == '?')
        {
            std::cout << (array.Find(word) ? "OK" : "FAIL") << "\n";
        }
        else if (command == '+') 
        {
            std::cout << (array.Add(word) ? "OK" : "FAIL") << "\n";
        }
        else
        {
            std::cout << (array.Delete(word) ? "OK" : "FAIL") << "\n";
        }
    }
    return 0;
}
