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
        }
        return it;
    }

    iterator_set erase(iterator_set pos) {
        auto foundElement = Set.find(*pos);
        auto pointerToRemove = std::remove(Order.begin(), Order.end(), &(*foundElement));
        if (pointerToRemove != Order.end()) Order.erase(pointerToRemove);
        iterator_set it_erase = Set.erase(foundElement);
        return it_erase;

    }

    iterator_set erase(iterator_set first, iterator_set last) {

        iterator_set afterLastRemoved;
        while (first != last)
        {
            afterLastRemoved = erase(first++);
        }
        return afterLastRemoved;
    }
    size_t erase(const T& element) {
        auto foundElement = Set.find(element);
        if (foundElement != Set.end()) {
            erase(foundElement);
            return size_t{ 1 };
        }
        return size_t{ 0 };
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

    void print_set() {
        for (auto it = Set.begin(); it != Set.end(); it++)
        {
            std::cout << *it << " ";
        }
    }

    void print_vector() {
        for (auto iter = Order.begin(); iter != Order.end(); iter++) {
            std::cout << *(*iter) << " "; //*iter равен элементу из вектора order, который хранит адреса элементов из set
            //*(*iter) позволяет получить само значение элемента, хранящееся по этому адресу
        }
    }

    iterator_set begin() { return Set.begin(); }
    iterator_set end() { return Set.end(); }
};



int main()
{
    setlocale(LC_ALL, "rus");
    OrderedSet<int> orderedSet;
    orderedSet.insert(1);
    orderedSet.insert(11);
    orderedSet.insert(5);
    orderedSet.insert(18);
    orderedSet.insert(6);
    orderedSet.insert(0);
    orderedSet.insert(500);
    orderedSet.insert(200);
    std::cout << "OrderedSet до вставки новых элементов" << std::endl << "Set: ";
    orderedSet.print_set();
    std::cout << std::endl << "Вектор: ";
    orderedSet.print_vector();
    std::cout << std::endl << "" << std::endl;

    //Тест вставки
    std::cout << "Вставка элементов..." << std::endl;
    std::cout << "Вставляемый элемент: " << 5 << " Успешность вставки: " << std::boolalpha << (orderedSet.insert(5)).second << std::endl; //не вставится, уже есть такой элемент
    std::cout << "Вставляемый элемент: " << 4 << " Успешность вставки: " << std::boolalpha << (orderedSet.insert(4)).second << std::endl; //вставится
    std::cout << "Вставляемый элемент: " << 18 << " Успешность вставки: " << std::boolalpha << (orderedSet.insert(18)).second << std::endl; //не вставится, уже есть такой элемент
    std::cout << "Set после вставки: ";
    orderedSet.print_set();
    std::cout << std::endl << "Вектор после вставки: ";
    orderedSet.print_vector();
    std::cout << std::endl << "" << std::endl;

    //Тест удаления
    std::cout << "Удаление элементов..." << std::endl;
    orderedSet.erase(18);
    std::cout << "Удаляемый элемент (по значению): " << 4 << " Количество удалённых элементов: " << orderedSet.erase(4) << std::endl; //удалится
    std::cout << "Удаляемый элемент (по значению): " << 1 << " Количество удалённых элементов: " << orderedSet.erase(1) << std::endl; //удалится
    std::cout << "Удаляемый элемент (по значению): " << 115 << " Количество удалённых элементов: " << orderedSet.erase(115) << std::endl; //не удалится, нет такого элемента
    std::cout << "Set после удаления: ";

    orderedSet.print_set();
    std::cout << std::endl << "Вектор после удаления: ";
    orderedSet.print_vector();
    std::cout << std::endl << "" << std::endl;

    std::cout << "Удаляемый элемент (по итератору): 5" << std::endl;
    std::cout << "Удаляемый элемент (по итератору): 11" << std::endl;
    orderedSet.erase((orderedSet.get_set()).find(5));
    orderedSet.erase((orderedSet.get_set()).find(11));
    std::cout << "Set после удаления: ";
    orderedSet.print_set();
    std::cout << std::endl << "Вектор после удаления: ";
    orderedSet.print_vector();
    std::cout << std::endl << "" << std::endl;

    std::cout << "Начальный элемент из диапазона для удаления: 0" << std::endl;
    std::cout << "Конечный элемент из диапазона для удаления: 200" << std::endl;
    orderedSet.erase(orderedSet.begin(), std::next(orderedSet.begin(), 2));

    std::cout << "Set после удаления: ";
    orderedSet.print_set();
    std::cout << std::endl << "Вектор после удаления: ";
    orderedSet.print_vector();


    std::cout << std::endl;
}
