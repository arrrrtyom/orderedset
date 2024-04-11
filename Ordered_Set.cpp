// ConsoleApplication61.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <set>
#include <vector>
using namespace std;

template<typename T>
class OrderedSet {
    set<T> _set; //set из значений
    vector<T> _order; //вектор, хранящий элементы в порядке их добавления

public:
    void insert(T element) { //вставка в OrderedSet
        if (_set.find(element) == _set.end()) {
            _set.insert(element);
            _order.push_back(element);
        }
    }

    void erase(T element) { //удаление из OrderedSet
        typename set<T>::iterator it = _set.find(element);
        if (it != _set.end()) { //если есть элементы
            
            _set.erase(it); //удалить из set

            // удалить из вектора order
            typename vector<T>::iterator iter;
            for (iter = _order.begin(); iter != _order.end(); iter++)
            {
                if (*iter == element)
                {
                    _order.erase(iter);
                    break;
                }
                
            }
        }
    }

        vector<T> get_order() { //функция, возвращающая вектор order
            return _order;
        }

        bool contains(T element) //проверка на наличие элемента в orderedset
        {
            bool flag = _set.find(element) != _set.end();
            return flag;
        }
    }
    ;



    int main()
    {
        setlocale(LC_ALL, "rus");
        OrderedSet<int> orderedSet;
        orderedSet.insert(25);
        orderedSet.insert(3);
        orderedSet.insert(15); 
        orderedSet.erase(15);

        cout << "Проверка наличия элементов:" << endl; 
        cout << "Ordered Set coдержит 3: " << boolalpha << orderedSet.contains(3) << endl; //true
        cout << "Ordered Set содержит 15: " << boolalpha << orderedSet.contains(15) << endl; //false
        cout << "Ordered Set содержит 25: " << boolalpha << orderedSet.contains(25) << endl; //true

        cout << "Порядок вставки:";
        vector<int> order = orderedSet.get_order();
        vector<int>::iterator iter;
        
        for (iter = order.begin(); iter!=order.end(); iter++) {
            cout << " " << *iter; 
        } //25 3

        cout <<endl;
    }

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
