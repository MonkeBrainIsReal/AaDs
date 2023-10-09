#include <iostream>
#include <windows.h>
using namespace std;
HANDLE Output = GetStdHandle(STD_OUTPUT_HANDLE);

template<typename T>
class DArray
{
private:
    int cap;
    int NumOfEl;
    T** arr;
public:

    DArray(int size = 6)
    {
        this->cap = size;
        this->NumOfEl = 0;
        this->arr = new T * [this->cap];

        initialize(this->NumOfEl);

    };

    ~DArray()
    {
        for (int i = 0; i < NumOfEl; i++)
        {
            delete this->arr[i];
        }
        delete[]this->arr;
    };

    void initialize(int from)
    {
        for (int i = from; i < cap; i++)
        {
            this->arr[i] = nullptr;
        }
    };

   void expand()
    {
        this->cap *= 2;
        T** tempArr = new T * [this->cap];

        for (int i = 0;i < this->NumOfEl;i++)
        {
            tempArr[i] = new T(*this->arr[i]);
        }

        for (int i = 0; i < NumOfEl; i++)
        {
            delete this->arr[i];
        }
        delete[]this->arr;

        this->arr = tempArr;
        initialize(this->NumOfEl);


    };

   void push(const T& element)
    {

        if (this->NumOfEl >= this->cap)
        {
            this->expand();
        }

        this->arr[this->NumOfEl++] = new T(element);
    };

    const int& size()const
    {
        return this->NumOfEl;
    }

    T& operator [](const int index)
    {
        if (index < 0 || index >= this->NumOfEl)
        {
            throw("trying to access unallocated memory");
        }
        return *this->arr[index];
    };//вместо функции get, будет оператор который возвращает значение по индексу 
};

template<typename T>
class Node {
public:
    Node* prev;
    T data;
    Node* next;

public:
    Node(T data) {
        this->data = data;
        this->prev = this->next = nullptr;
    }
};

template <typename T> class LinkedList {
public:
    Node<T>* head, * tail;

public:
    LinkedList() //конструктор
    {
        head = tail = NULL;
    }

    ~LinkedList() 
    {
        while (head != nullptr)
            delete_first();
    }

    int size() {
        Node<T>* ptr = tail;
        int length = 0;
        while (ptr != nullptr) {
            ptr = ptr->prev;
            length++;
        }
        return length;
    }

    Node<T>* add_first(T data) {
        Node<T>* ptr = new Node<T>(data);
        ptr->next = head;
        if (head != nullptr)
            head->prev = ptr;
        if (tail == nullptr)
            tail = ptr;
        head = ptr;
        return ptr;
    }

    Node<T>* add_last(T data) {
        Node<T>* ptr = new Node<T>(data);
        ptr->prev = tail;
        if (tail != nullptr)
            tail->next = ptr;
        if (head == nullptr)
            head = ptr;
        tail = ptr;
        return ptr;
    }

    void delete_first() {
        if (head == nullptr)
            return;

        Node<T>* ptr = head->next;
        if (ptr != nullptr)
            ptr->prev = nullptr;
        else
            tail = nullptr;

        delete head;
        head = ptr;
    }

    void delete_last() {
        if (tail == nullptr)
            return;

        Node<T>* ptr = tail->prev;
        if (ptr != nullptr)
            ptr->next = nullptr;
        else
            head = nullptr;

        delete tail;
        tail = ptr;
    }

    Node<T>* get(int index) {
        if (index < 0)
            return nullptr;
        int listSize = size();
        if (index > listSize / 2) //проверка на позицию элемента
        {
            Node<T>* ptr = tail;
            int count = listSize - 1;
            while (count != index) {
                if (ptr == nullptr)
                    return ptr;
                ptr = ptr->prev;
                count--;
            }
            return ptr;
        }
        else {  
            Node<T>* ptr = head;
            int count = 0;
            while (count != index) {
                if (ptr == nullptr)
                    return ptr;
                ptr = ptr->next;
                count++;
            }
            return ptr;
        }
    }

    Node<T>* insert(int index, T data) {
        Node<T>* right = get(index);
        if (right == nullptr)
            return add_last(data);

        Node<T>* left = right->prev;
        if (left == nullptr)
            return add_first(data);

        Node<T>* ptr = new Node<T>(data);

        ptr->prev = left;
        ptr->next = right;
        left->next = ptr;
        right->prev = ptr;

        return ptr;
    }

    void erase(int index) {
        Node<T>* ptr = get(index);
        if (ptr == nullptr)
            return;
        if (ptr->prev == nullptr) {
            delete_first();
            return;
        }
        if (ptr->next == nullptr) {
            delete_last();
            return;
        }

        Node<T>* left = ptr->prev;
        Node<T>* right = ptr->next;
        left->next = right;
        right->prev = left;

        delete ptr;
    }

    void remove_current(const T& data)
    {
        Node<T>* current = head;
        while (current != nullptr && current->data != data)// ищем узел с конкретным значением 
        {
            current = current->next;
        }

        if (current == nullptr)
        {
            return;
        }

        Node<T>* left = current->prev;
        Node<T>* right = current->next;

        if (left != nullptr)
            left->next = right;
        else
            head = right;

        if (right != nullptr)
            right->prev = left;
        else
            tail = left;

        delete current;
    }

    Node<T>* operator [] (int index) {
        return get(index);
    }
};

int main()
{///////////////////////////////////////////////////////////////////////////////////////// ТЕСТ СПИСКА
	LinkedList<string> lst;
    setlocale(LC_ALL, "Russian");
	//добавляем 4 элемента в наш список 
	lst.add_first("ооооо");
	lst.add_last("великий");
	lst.add_last("суп");
	lst.add_last("наварили");
	//выводим часть из них чтобы проверить функцию добавления
	cout << lst.get(0)->data << "\n";
	cout << lst.get(1)->data << "\n";
	cout << lst.get(2)->data << "\n";
    cout << lst.get(3)->data << "\n\n";
	//дополним список 2 новыми элементами и выведем весь список на экран 
	lst.insert(5, "ШИКАРНЫЙ");
	lst.insert(6, "Наварили?");
	for (int i =0 ;i<lst.size();i++)
		cout << lst[i]->data << " ";
    cout <<"\n" << "размер списка  " << lst.size() << "\n";
	cout << "\n\n";
	//теперь проверим функцию удаления и выведем список после удаления нескольких элементов
	lst.erase(0);
    lst.erase(3);
	lst.erase(5);
	lst.erase(7);//ничего не удалится тк это несуществующий элемент

    lst.remove_current("Наварили?");

	for (int i = 0;i < lst.size();i++)
		cout << lst[i]->data << " ";
	cout << "\n";
	cout << "размер списка  " << lst.size() << "\n\n\n";
   
   
	///////////////////////////////////////////////////////////////////////////////////////// ТЕСТ МАССИВА
    DArray<int> d;
    d.push(666);
    d.push(777);
    d.push(888);
    d.push(999);
    d.push(000);
    d.push(111);
    d.push(222);
    for (int i = 0;i < d.size();i++) {
        cout << d[i] << "\n";
    }
    SetConsoleTextAttribute(Output, 12);
    cout << "Со смертью этого персонажа нить вашей судьбы обрывается. Загрузите сохранённую игру дабы восстановить течение судьбы, или живите дальше в проклятом мире, который сами и создали..." << "\n\n\n";
    SetConsoleTextAttribute(Output, 7);
    return 0;
}