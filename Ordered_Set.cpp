#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <initializer_list> 

template<typename T>
class OrderedSet {
    using iterator_set = typename std::set<T>::iterator;
    using iterator_set_reverse = typename std::set<T>::reverse_iterator;
    using const_iterator_set = typename std::set<T>::const_iterator;
    using const_iterator_set_reverse = typename std::set<T>::const_reverse_iterator;
    using iterator_vector = typename std::vector<const T*>::iterator;
    using iterator_vector_reverse = typename std::vector<const T*>::reverse_iterator;
    using const_iterator_vector = typename std::vector<const T*>::const_iterator;
    using const_iterator_vector_reverse = typename std::vector<const T*>::const_reverse_iterator;
    std::set<T> Set; //set из значений
    std::vector<const T*> Order; //вектор, хранящий адреса элементов в порядке их добавления

public:
    OrderedSet(std::initializer_list<T> l) 
    {   
        for (auto it = l.begin(); it!=l.end(); it++)
        {
            insert(*it);
        }
    }
    
    auto insert(const T& element) //вставка в OrderedSet
    {
        auto it = Set.insert(element);
        if (it.second == true) 
        {
            Order.push_back(&(*it.first));
        }
        return it;
    }

    iterator_set erase(iterator_set pos) 
    {
        auto pointerToRemove = std::find(Order.begin(), Order.end(), &(*pos));
        if (pointerToRemove != Order.end()) Order.erase(pointerToRemove);
        return Set.erase(pos);
    }

    iterator_set erase(iterator_set first, iterator_set last) 
    {
        iterator_set afterLastRemoved;
        while (first != last)
        {
            afterLastRemoved = erase(first++);
        }
        return afterLastRemoved;
    }

    size_t erase(const T& element) 
    {
        auto foundElement = Set.find(element);
        if (foundElement == Set.end()) { return { 0 }; }
        erase(foundElement);
        return { 1 };
    }

    template <typename... Args>
    auto emplace(Args... args)
    {
        auto it = Set.emplace(args...);
        if(it.second==true) {Order.push_back(&(*it.first));}
        return it;
    }

    const std::vector<const T*>& get_order() const //функция, возвращающая вектор order
    { 
        return Order;
    }

    const std::set<T>& get_set() const 
    {
        return Set;
    }

    bool contains(const T& element) //проверка на наличие элемента в orderedset
    {
        return Set.find(element) != Set.end();
    }

    iterator_set begin() { return Set.begin(); }
    iterator_set end() { return Set.end(); }

    const_iterator_set begin() const { return Set.begin(); }
    const_iterator_set end() const { return Set.end(); }

    const_iterator_set cbegin() const {return Set.cbegin();}
    const_iterator_set cend() const {return Set.cend();}

    iterator_set_reverse rbegin() { return Set.rbegin(); }
    iterator_set_reverse rend()  { return Set.rend(); }
    
    const_iterator_set_reverse rbegin() const { return Set.rbegin(); }
    const_iterator_set_reverse rend() const  { return Set.rend(); }

    const_iterator_set_reverse crbegin() const {return Set.crbegin();}
    const_iterator_set_reverse crend() const {return Set.crend();}

    iterator_vector order_begin() {return Order.begin();}
    iterator_vector order_end() { return Order.end();}

    const_iterator_vector order_begin() const { return Order.begin();}
    const_iterator_vector order_end() const { return Order.end();}

    const_iterator_vector order_cbegin() const { return Order.cbegin();}
    const_iterator_vector order_cend() const { return Order.cend();}

    iterator_vector_reverse order_rbegin() {return Order.rbegin();}
    iterator_vector_reverse order_rend() { return Order.rend();}

    const_iterator_vector_reverse order_rbegin() const { return Order.rbegin();}
    const_iterator_vector_reverse order_rend() const { return Order.rend();}

    const_iterator_vector order_crbegin() const { return Order.crbegin();}
    const_iterator_vector order_crend() const { return Order.crend();}
};

class Book 
{
    public:
    std::string author;
    std::string name;
    int year_of_publication;
    Book(std::string Author, std::string Name, int Year):
    author{Author}, name{Name}, year_of_publication{Year} {}

    bool operator<(const Book &another_book) const  
    {
        return year_of_publication < another_book.year_of_publication;
    }

    friend std::ostream& operator<<(std::ostream& out, const Book& book) 
    {
        out << "Автор: " << book.author << ", Название: " << book.name << ", Год публикации: " << book.year_of_publication;
        return out;
    }
};

template <typename T>
void test_insert(OrderedSet<T> &orderedSet)
{   
    std::cout << "OrderedSet до вставки новых элементов" << std::endl;
    print_orderedSet(orderedSet);
    std::cout<<""<<std::endl;
    std::cout << "Вставляемый элемент: " << 5 << " Успешность вставки: " << std::boolalpha << (orderedSet.insert(5)).second << std::endl; //не вставится, уже есть такой элемент
    std::cout << "Вставляемый элемент: " << 4 << " Успешность вставки: " << std::boolalpha << (orderedSet.insert(4)).second << std::endl; //вставится
    std::cout << "Вставляемый элемент: " << 18 << " Успешность вставки: " << std::boolalpha << (orderedSet.insert(18)).second << std::endl; //не вставится, уже есть такой элемент
    std::cout << "OrderedSet после вставки: ";
    std::cout<<""<<std::endl;
    print_orderedSet(orderedSet);
}

template <typename T>
void test_erase(OrderedSet<T>& orderedSet) 
{
    std::cout << "Удаляемый элемент (по значению): " << 4 << " Количество удалённых элементов: " << orderedSet.erase(4) << std::endl; //удалится
    std::cout << "Удаляемый элемент (по значению): " << 1 << " Количество удалённых элементов: " << orderedSet.erase(1) << std::endl; //удалится
    std::cout << "Удаляемый элемент (по значению): " << 115 << " Количество удалённых элементов: " << orderedSet.erase(115) << std::endl; //не удалится, нет такого элемента
    std::cout << "OrderedSet после удаления: "<<std::endl;
    print_orderedSet(orderedSet);
    std::cout << std::endl << "" << std::endl;

    std::cout << "Удаляемый элемент (по итератору): 0" << std::endl;
    std::cout << "Удаляемый элемент (по итератору): 6" << std::endl;
    orderedSet.erase(orderedSet.begin());
    orderedSet.erase(std::next(orderedSet.begin(),1));
    std::cout << "OrderedSet после удаления: "<<std::endl;
    print_orderedSet(orderedSet);
    std::cout << std::endl << "" << std::endl;

    std::cout << "Начальный элемент из диапазона для удаления: 5" << std::endl;
    std::cout << "Конечный элемент из диапазона для удаления: 18" << std::endl;
    orderedSet.erase(orderedSet.get_set().find(5), orderedSet.get_set().find(18));
    
    std::cout<<"OrderedSet после удаления: ";
    std::cout<<""<<std::endl;
    print_orderedSet(orderedSet);
}

template <typename T>
void test_emplace(OrderedSet<T>& orderedSet)
{   
    std::cout<<"Вставка элементов с помощью emplace для базового типа..."<<std::endl;
    std::cout<<"Элемент для вставки:"<<35<<std::endl;
    orderedSet.emplace(35);
    std::cout << "OrderedSet после вставки: "<<std::endl;
    print_orderedSet(orderedSet);
    std::cout << std::endl << "" << std::endl;

    OrderedSet <Book> Books={};
    Books.emplace("М. А. Булгаков", "Мастер и Маргарита", 1967);
    Books.emplace("Н. В. Гоголь", "Ревизор",1835);
    Books.emplace("Ф. М. Достоевский", "Преступление и наказание", 1866);
    std::cout<<"Вставка элементов с помощью emplace для пользовательного класса..."<<std::endl;
    std::cout<<"Книги, отсортированные по году публикации:"<<std::endl;
    for (auto it = Books.begin(); it!=Books.end(); it++)
    {
        std::cout<<(*it)<<std::endl;
    }
    std::cout<<""<<std::endl;
    std::cout<<"Книги в порядке добавления:"<<std::endl;
    for (auto it = Books.get_order().begin(); it != Books.get_order().end(); it++) 
    {
        std::cout << (*(*it)) << std::endl;
    }
}

template <typename T>
void print_orderedSet(OrderedSet<T>& orderedSet)
{  std::cout<<"Set: ";
    for(auto it = orderedSet.begin(); it != orderedSet.end(); ++it)
    {
        std::cout<<*it<<" ";
    }
    std::cout<<std::endl;
    std::cout<<"Вектор: ";
    for(auto it = orderedSet.order_begin(); it != orderedSet.order_end(); ++it)
    {
        std::cout<<*(*it)<<" ";
    }
}

template <typename T>
void print_orderedSet_reverse(OrderedSet<T>& orderedSet)
{   
    std::cout<<"Set: ";
    for(auto it = orderedSet.rbegin(); it != orderedSet.rend(); ++it)
    {
        std::cout<<*it<<" ";
    }
    std::cout<<std::endl;
    std::cout<<"Вектор: ";
    for(auto it = orderedSet.order_rbegin(); it != orderedSet.order_rend(); ++it)
    {
        std::cout<<*(*it)<<" ";
    }
}

template <typename T>
void print_orderedSet(const OrderedSet<T>& orderedSet) 
{
    std::cout<<"Set: ";
    for(auto it = orderedSet.begin(); it != orderedSet.end(); ++it)
    {
        std::cout<<*it<<" ";
    }
    std::cout<<std::endl;
    std::cout<<"Вектор: ";
    for(auto it = orderedSet.order_begin(); it != orderedSet.order_end(); ++it)
    {
        std::cout<<*(*it)<<" ";
    }
}

template <typename T>
void print_orderedSet_reverse(const OrderedSet<T>& orderedSet)
{  
    std::cout<<"Set: ";
    for(auto it = orderedSet.rbegin(); it != orderedSet.rend(); ++it)
    {
        std::cout<<*it<<" ";
    }
    std::cout<<std::endl;
    std::cout<<"Вектор: ";
    for(auto it = orderedSet.order_rbegin(); it != orderedSet.order_rend(); ++it)
    {
        std::cout<<*(*it)<<" ";
    }
}

template <typename T> 
void test_iterators( OrderedSet<T>& orderedSet)
{  
    std::cout<<"Элементы в прямом порядке: "<<std::endl;
    print_orderedSet(orderedSet);
    std::cout<<std::endl;
    std::cout<<"Элементы в обратном порядке: "<<std::endl;
    print_orderedSet_reverse(orderedSet);
    std::cout<<std::endl;
}

template <typename T> 
void test_iterators(const OrderedSet<T>& orderedSet)
{  
    std::cout<<"Элементы в прямом порядке: "<<std::endl;
    print_orderedSet(orderedSet);
    std::cout<<std::endl;
    std::cout<<"Элементы в обратном порядке: "<<std::endl;
    print_orderedSet_reverse(orderedSet);
}

template <typename T>
void test_algorithms(OrderedSet<T>& orderedSet)
{   
    std::cout<<"Содержание OrderedSet: "<<std::endl;
    print_orderedSet(orderedSet);
    std::cout << std::endl;
    std::cout<<"Бинарный поиск:"<<std::endl 
    << "Наличие элемента 22 в orderedSet: "<<std::binary_search(orderedSet.begin(), orderedSet.end(), 22)
    <<std::endl<<"Наличие элемента 1 в orderedSet: "<<std::binary_search(orderedSet.begin(), orderedSet.end(), 1)<<std::endl;
    std::cout<<"Количество вхождений элемента 5: "<<std::count(orderedSet.begin(), orderedSet.end(), 5)<<std::endl;
    std::cout<<"Количество вхождений элемента 35: "<<std::count(orderedSet.begin(), orderedSet.end(), 35);
}

template <typename T>
void test_algorithms(const OrderedSet<T>& orderedSet)
{   
    std::cout<<"Содержание OrderedSet: "<<std::endl;
    print_orderedSet(orderedSet);
    std::cout << std::endl;
    std::cout<<"Бинарный поиск:"<<std::endl 
    << "Наличие элемента 2 в orderedSet: "<<std::binary_search(orderedSet.begin(), orderedSet.end(), 2)
    <<std::endl<<"Наличие элемента 1 в orderedSet: "<<std::binary_search(orderedSet.begin(), orderedSet.end(), 1)<<std::endl;
    std::cout<<"Количество вхождений элемента 5: "<<std::count(orderedSet.begin(), orderedSet.end(), 5)<<std::endl;
    std::cout<<"Количество вхождений элемента 8: "<<std::count(orderedSet.begin(), orderedSet.end(), 8);
}

int main()
{
    setlocale(LC_ALL, "rus");
    OrderedSet<int> orderedSet={22,33, 1, 11, 5, 18, 6, 0, 500, 200};

    //Тест insert
    std::cout << "Вставка элементов c помощью insert..." << std::endl;
    test_insert(orderedSet);
    std::cout << std::endl << "" << std::endl;

    //Тест erase
    std::cout << "Удаление элементов..." << std::endl;
    test_erase(orderedSet);
    std::cout<<std::endl<<""<<std::endl;

    //Тест emplace
    test_emplace(orderedSet);
    std::cout << std::endl;

    //Тест перебора с помощью итераторов
    std::cout<<"Перебор неконстантного контейнера с помощью итераторов: "<<std::endl;
    test_iterators(orderedSet);
    std::cout << std::endl;
    
    std::cout<<"Перебор константного контейнера с помощью итераторов: "<<std::endl;
    const OrderedSet<int> order_const = {5,2,7};
    test_iterators(order_const);
    std::cout<<std::endl<<""<<std::endl;

    //Тест совместимости со стандартными алгоритмами
    std::cout<<"Совместимость неконстантного контейнера со стандратными алгоритмами:"<<std::endl;
    test_algorithms(orderedSet);
    std::cout << std::endl << "" << std::endl;
    std::cout<<"Совместимость константного контейнера со стандратными алгоритмами:"<<std::endl;
    test_algorithms(order_const);
}
