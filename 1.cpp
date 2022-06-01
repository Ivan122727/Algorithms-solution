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
#include <cassert>

template<class T>
class HornerHash
{
public:
    static int Hash1(const T& data, const int& size)
    {
        int index = 0;
        for (auto elem : data)
        {
            index = (index * (size - 1) + elem) % size;
        }
        return index;
    }

    static int Hash2(const T& value, int& size)
    {
        int index = 0;
        for (auto elem : value)
        {
            index = (index * (size + 1) + elem) % size;
        }
        return (index * 2 + 1) % size;
    }
};

template <class T, class THash = HornerHash<T>>
struct HashTable : public HornerHash<T>
{
public:
    HashTable() : list(std::vector<T>(8)), capacity(8), size(0) {}
    bool Add(const T& data)
    {
        if (size >= capacity * overflow)
        {
            Rehash();
        }
        int h1 = THash::Hash1(data, capacity);
        int h2 = THash::Hash2(data, capacity);
        for (int i = 0; i <= size; i++)
        {
            if (list[h1] == data)
            {
                break;
            }
            if (list[h1] == "")
            {
                list[h1] = data;
                size++;
                return true;
            }
            h1 = (h1 + h2) % capacity;
        }
        return false;
    }
    bool Find(const T& data)
    {
        int h1 = THash::Hash1(data, capacity);
        int h2 = THash::Hash2(data, capacity);
        for (int i = 0; i <= size; i++)
        {
            if (list[h1] == "")
            {
                break;
            }
            if (list[h1] == data)
            {
                return true;
            }
            h1 = (h1 + h2) % capacity;
        }
        return false;
    }
    bool Delete(const T& data)
    {
        int h1 = THash::Hash1(data, capacity);
        int h2 = THash::Hash2(data, capacity);
        for (int i = 0; i <= size; i++)
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
            h1 = (h1 + h2) % capacity;
        }
        return false;
    }
private:
    std::vector<T> list;
    int capacity;
    int size;
    const float overflow = 0.75;
    void Rehash()
    {
        capacity *= 2;
        std::vector<std::string> temp(capacity);
        size = 0;
        std::swap(list, temp);
        for (int i = 0; i < capacity / 2; ++i)
        {
            if (temp[i] != "" && temp[i] != "deleted")
            {
                Add(temp[i]);
            }
        }
    }
};

int main()
{
    HashTable<std::string> array;
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
