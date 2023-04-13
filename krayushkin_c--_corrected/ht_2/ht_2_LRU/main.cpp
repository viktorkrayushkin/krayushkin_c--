#include <iostream>
#include <list>
#include <exception>

//using namespace std;

template <typename K, typename V>
class LRU {
    using List = std::list<std::pair<K, V>>; //вместо map так как не будем использовать большой массив данных;
    List list;
    int size;
public:
    LRU(int capacity) : size(capacity) {}

    const V get(const K& key) {
        typename List::iterator it = list.begin();
        for (int i = 0; i < list.size(); i++, ++it) {
            if (it->first == key) {
                std::pair<K, V> elem = *it;
                list.erase(it);
                list.push_front(std::move(elem));
                return elem.second;
            }
        }
        throw std::runtime_error("Element not found");
    }

    void put(K& key, V& value) {
        if (list.size() == size)
            list.pop_back();

        list.push_front(std::make_pair<K, V>(key, value));
    }

    void Put(K&& key, V&& value) {
        if (list.size() == size)
            list.pop_back();

        list.push_front(std::make_pair<K, V>(std::move(key), std::move(value)));
    }
};

int main() {
    LRU<char, int> cache(2);

    cache.Put('v', 1);
    cache.Put('p', 2);
    std::cout << cache.get('v') << std::endl;
    cache.Put('k', 5);
    cache.Put('t', 12);
    try {
        std::cout << cache.get('k') << std::endl;
    }
    catch (std::runtime_error exc) {
        std::cout << exc.what() << std::endl;
    }
}
/*
Доступ к элементам list по итератору -> получения элемента за o(1), + перемещение в начало списка за O(1)
поиск за O(n)
*/