#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

template<typename T>
class OrderedSet {
    using iterator_set = typename std::set<T>::iterator;
    std::set<T> Set; //set из значений
    std::vector<const T*> Order; //вектор, хранящий адреса элементов в порядке их добавления

public:
    auto insert(const T& element) { //вставка в OrderedSet
        auto it = Set.insert(element);
        if (it.second == true) {
            Order.push_back(&(*it.first));
            return std::make_pair(it.first, true);
        }
    }

    iterator_set erase(iterator_set pos) {
        auto foundElement = Set.find(*pos);
        if (foundElement == Set.end()) { return Set.end(); };

        auto pointerToRemove = std::remove(Order.begin(), Order.end(), &(*foundElement));
        if (pointerToRemove != Order.end()) Order.erase(pointerToRemove);

        iterator_set it_erase = Set.erase(foundElement);
        return it_erase;
    }

    iterator_set erase(iterator_set first, iterator_set last) {

        iterator_set it = erase(first);
        while (it != last) {
            it = erase(it);
        }
        return it;
    }
    size_t erase(const T& element) { //удаление из OrderedSet
        auto foundElement = Set.find(element);
        erase(foundElement);
        return size_t{ 1 };
    }

    std::vector<const T*> get_order() { //функция, возвращающая вектор order

        return Order;
    }

    std::set<T> get_set() {
        return Set;
    }

    bool contains(const T& element) //проверка на наличие элемента в orderedset
    {
        return Set.find(element) != Set.end();
    }

};

int main()
{
    setlocale(LC_ALL, "rus");
    OrderedSet<int> orderedSet;
    int x = 5, y = 10, z = 2, v = 100, c = 1;
    orderedSet.insert(z);
    orderedSet.insert(y);
    orderedSet.insert(x);
    auto first = orderedSet.insert(c).first;
    auto last = orderedSet.insert(v).first;
    //orderedSet.erase(first);
    //orderedSet.erase(z);
    orderedSet.erase(first, last);
    std::set<int> Set = orderedSet.get_set();

    std::cout << "Элементы в set: ";


    for (auto it = Set.begin(); it != Set.end(); it++)
    {
        std::cout << *it << " ";
    }

    std::cout << std::endl;

    std::cout << "Порядок вставки:";
    std::vector<const int*> order = orderedSet.get_order();

    for (auto iter = order.begin(); iter != order.end(); iter++) {
        std::cout << " " << *(*iter); //*iter равен элементу из вектора order, который хранит адреса элементов из set
                        //*(*iter) позволяет получить само значение элемента, хранящееся по этому адресу
    }

    std::cout << std::endl;
}
