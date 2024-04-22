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
        
        auto pointerToRemove = std::find(Order.begin(), Order.end(), &(*pos));
       if (pointerToRemove != Order.end()) Order.erase(pointerToRemove);
     return Set.erase(pos);
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
        if (foundElement == Set.end()) { return { 0 }; }
        erase(foundElement);
        return { 1 };
    }
template <typename... Args>
    auto emplace(Args... args){
        auto it = Set.emplace(args...);
        if(it.second==true) {Order.push_back(&(*it.first));}
        return it;
    }

    std::vector<const T*>& get_order() { //функция, возвращающая вектор order

        return Order;
    }

    std::set<T>& get_set() {
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

class Book {
    public:
    std::string name;
    std::string author;
    int year_of_publication;
    Book(std::string _name, std::string _author, int _year):
        name{_name}, author{_author}, year_of_publication{_year} {}

     bool operator<(const Book &other) const  {
        return year_of_publication < other.year_of_publication;
    }

    
friend std::ostream& operator<<(std::ostream& os, const Book& book) {
        os << "Название: " << book.name << ", Автор: " << book.author << ", Год публикации: " << book.year_of_publication;
        return os;
    }
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
    std::cout << "Удаляемый элемент (по значению): " << 4 << " Количество удалённых элементов: " << orderedSet.erase(4) << std::endl; //удалится
    std::cout << "Удаляемый элемент (по значению): " << 1 << " Количество удалённых элементов: " << orderedSet.erase(1) << std::endl; //удалится
    std::cout << "Удаляемый элемент (по значению): " << 115 << " Количество удалённых элементов: " << orderedSet.erase(115) << std::endl; //не удалится, нет такого элемента
    std::cout << "Set после удаления: ";

    orderedSet.print_set();
    std::cout << std::endl << "Вектор после удаления: ";
    orderedSet.print_vector();
    std::cout << std::endl << "" << std::endl;

    std::cout << "Удаляемый элемент (по итератору): 0" << std::endl;
    std::cout << "Удаляемый элемент (по итератору): 6" << std::endl;
    orderedSet.erase(orderedSet.begin());
    orderedSet.erase(std::next(orderedSet.begin(),1));
    std::cout << "Set после удаления: ";
    orderedSet.print_set();
    std::cout << std::endl << "Вектор после удаления: ";
    orderedSet.print_vector();
    std::cout << std::endl << "" << std::endl;

    std::cout << "Начальный элемент из диапазона для удаления: 5" << std::endl;
    std::cout << "Конечный элемент из диапазона для удаления: 18" << std::endl;
    orderedSet.erase(orderedSet.begin(), std::next(orderedSet.begin(), 2));

    std::cout << "Set после удаления: ";
    orderedSet.print_set();
    std::cout << std::endl << "Вектор после удаления: ";
    orderedSet.print_vector();

    //Тест emplace
    std::cout<<"Элемент для вставки:"<<35<<std::endl;
    orderedSet.emplace(35);
    std::cout<<"Set после вставки:";
    orderedSet.print_set();
    std::cout<<std::endl<<"Вектор после вставки: ";
    orderedSet.print_vector();
    OrderedSet <Book> Books;
    std::cout << std::endl;
    Books.emplace("М. А. Булгаков", "Мастер и Маргарита", 1967);
    Books.emplace("Н. В. Гоголь", "Ревизор",1835);
    Books.emplace("Ф. М. Достоевский", "Преступление и наказание", 1866);
    std::cout<<"Книги, отсортированные по году публикации:"<<std::endl;
    for (auto it = Books.begin(); it!=Books.end(); it++){
    std::cout<<(*it)<<std::endl;
    }
    std::cout<<""<<std::endl;
    std::cout<<"Книги в порядке добавления:"<<std::endl;
    for (auto it = Books.get_order().begin(); it != Books.get_order().end(); it++) {
        std::cout << (*(*it)) << std::endl;
    }
}
