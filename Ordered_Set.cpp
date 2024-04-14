#include <iostream>
#include <set>
#include <vector>

template<typename T>
class OrderedSet {
    std::set<T> Set; //set из значений
    std::vector<const T*> Order; //вектор, хранящий адреса элементов в порядке их добавления

public:
    void insert(const T& element) { //вставка в OrderedSet
        auto it = Set.insert(element);
        if (it.second==true) Order.push_back(&(*it.first));   
    }

    void erase(const T& element) { //удаление из OrderedSet

        // удалить из вектора order
        typename std::vector<const T*>::iterator iter;
        for (iter = Order.begin(); iter != Order.end(); iter++)
        {
            if (*iter == &(*Set.find(element)))
            {
                Order.erase(iter);
                break;
            }

        }
        //удалить из set
        typename std::set<T>::iterator it = Set.find(element);
        if (it != Set.end()) { //если есть элементы

            Set.erase(it);
        }
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
    std::set<int>::iterator it;
    for (it = Set.begin(); it != Set.end(); it++)
    {
        std::cout <<*it<<" ";
    }
    
    std::cout << std::endl;

    std::cout << "Порядок вставки:";
    std::vector<const int*> order = orderedSet.get_order();
    std::vector<const int*>::iterator iter;

    for (iter = order.begin(); iter != order.end(); iter++) {
        std::cout << " " << *(*iter); //*iter равен элементу из вектора order, который хранит адреса элементов из set
        //*(*iter) позволяет получить само значение элемента, хранящееся по этому адресу
    } //вывод: 10 5

    std::cout << std::endl;
}

