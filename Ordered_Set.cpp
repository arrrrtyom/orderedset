#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

template<typename T>
class OrderedSet {
    std::set<T> Set; //set из значений
    std::vector<const T*> Order; //вектор, хранящий адреса элементов в порядке их добавления

public:
    void insert(const T& element) { //вставка в OrderedSet
        auto it = Set.insert(element);
        if (it.second == true) Order.push_back(&(*it.first));
    }

    std::pair<typename std::set<T>::iterator, typename std::vector<const T*>::iterator> erase(const T& element) { //удаление из OrderedSet
        auto iter1 = Set.find(element);

        //удалить из вектора Order
        auto iter2 = std::find(Order.begin(), Order.end(), &(*iter1));
        if (iter2 != Order.end()) iter2 = Order.erase(iter2);

        //удалить из Set
        iter1 = Set.erase(iter1);
        
        //возвращает пару (итератор на элемент из Set,следующий за удалённым, и итератор на элемент из Order, следующий за удалённым)
        return std::make_pair(iter1, iter2);
    }

    std::vector<const T*> get_order() { //функция, возвращающая вектор order

        return Order;
    }

    std::set<T> get_set() {
        return Set;
    }

    bool contains(const T& element) //проверка на наличие элемента в orderedset
    {
        bool flag = Set.find(element) != Set.end();
        return flag;
    }
};

int main()
{
    setlocale(LC_ALL, "rus");
    OrderedSet<int> orderedSet;
    int x = 5, y = 10, z = 2;
    orderedSet.insert(z);
    orderedSet.insert(y);
    orderedSet.insert(x);
    orderedSet.erase(z);

    std::cout << "Элементы в set: ";
    std::set<int> Set = orderedSet.get_set();

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
    } //вывод: 10 5

    std::cout << std::endl;
}
