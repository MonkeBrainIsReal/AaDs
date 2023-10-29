#include <iostream>
#include <windows.h>
#include <string>
#include <cctype>
#include <sstream>
#include <cmath>

using namespace std;
HANDLE Output = GetStdHandle(STD_OUTPUT_HANDLE);

template<typename T> class DArray {
private:
    int cap;
    int size;
    T* arr;

public:
    DArray(int size = 6) //базовый конструктор с каким то случайным размером
    {

        cap = size;
        arr = new T[size];
    }

    ~DArray()
    {
        delete[] arr;
    }

    void expand()
    {
        cap *= 2;
        T* tempArr = new T[cap];

        for (int i = 0; i < size; i++) {
            tempArr[i] = arr[i];
        }

        delete[] arr;

        arr = tempArr;//присваиваем указатель на новый массив
    }

    void push(const T& element)//добавляем малыша в конец массива 
    {
        if (size >= cap)
        {
            expand();
        }
        arr[size++] = element;
    }

    const int& getsize() const {
        return size;
    }

    void insert(const T& element, int position) {
        if (position < 0 || position > size) {
            cerr << "Неверная позиция" << "\n";
        }

        if (size >= cap) {
            expand();
        }

        for (int i = size; i > position; --i) //cдвигаем элементы вправо начиная с конца массива для освобождения места под новый элемент
        {
            arr[i] = arr[i - 1];
        }

        arr[position] = element;
        ++size;
    }

    void remove(int index)
    {
        if (index >= size) {
            cerr << "Ошибка: индекс преисполнился и ушел за границы" << "\n";
            return;
        }

        for (int i = index; i < size - 1; ++i)//cдвигаем элементы влево для заполнения пустого места
        {
            arr[i] = arr[i + 1];
        }
        --size;
    }

    T& operator[](const int index)
    {
        if (index < 0 || index >= size)
        {
            cerr << "Ошибка: индекс преисполнился и ушел за границы" << "\n";
        }
        return arr[index];
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////Список

template<typename T> class Node {
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

/////////////////////////////////////////////////////////////////////////////////////////////////////Стек и все что связано с инфиксной/постфиксной записью

template <typename T> class Stack {
private:
    LinkedList<T> list;

public:
    Stack() {}

    ~Stack() {}

    void add(T data) // добавляем в стек
    {
        list.add_first(data);
    }

    void delete_el() {
        list.delete_first();
    }

    T get() {//полчаем инфу 
        if (list.head != nullptr) {
            return list.head->data;
        }
        else {
            return T();
        }
    }

    bool empty() const {
        return list.head == nullptr;
    }

    int size() {
        return list.size();
    }
};

class Token {
public:
    enum Type
    {
        OPERATOR, OPERAND, FUNCTION, OPEN_PARENTHESIS, CLOSE_PARENTHESIS
    };

    Type type;
    string value;

    Token(Type type = OPERAND, const string& value = "") : type(type), value(value) {}//конструктор co значениями по умолчанию
};

bool Operator_check(const string& token) {
    return token == "+" || token == "-" || token == "*" || token == "/" || token == "^";
}

bool Func_check(const string& token) {
    return token == "sin" || token == "cos";
}

int OperatorPriority(const string& op) {
    if (op == "+" || op == "-")
        return 1;
    if (op == "*" || op == "/")
        return 2;
    if (op == "^")
        return 3;
    else
        return 0;
}

int FuncPriority(const string& op) {
    if (op == "cos" || op == "sin")
        return 4;
    else
        return 0;

}

string infixToPostfix(const string& infixExpression)
{
    stringstream ss(infixExpression);
    Stack<Token> operators;
    stringstream postfix;
    string token;
    int openParenthesisCount = 0;
    int closeParenthesisCount = 0;

    while (ss >> token) {
        if (std::isdigit(token[0]) || (token.size() > 1 && std::isdigit(token[1]))) {
            postfix << token << " ";
        }
        else if (Operator_check(token) || Func_check(token)) {
            if (Func_check(token)) {
                operators.add(Token(Token::FUNCTION, token));
            }
            else {
                while (!operators.empty() &&
                    (operators.get().type == Token::OPERATOR || operators.get().type == Token::FUNCTION) &&
                    OperatorPriority(operators.get().value) >= OperatorPriority(token) &&
                    FuncPriority(operators.get().value) == 0) {
                    postfix << operators.get().value << " ";
                    operators.delete_el();
                }
                operators.add(Token(Token::OPERATOR, token));
            }
        }
        else if (token == "(") {
            operators.add(Token(Token::OPEN_PARENTHESIS, token));
            openParenthesisCount++;
        }
        else if (token == ")") {
            closeParenthesisCount++;
            while (!operators.empty() && operators.get().type != Token::OPEN_PARENTHESIS) {
                postfix << operators.get().value << " ";
                operators.delete_el();
            }
            operators.delete_el(); // Убираем открывающую скобку

            //слишком тупой недочет
            if (!operators.empty() && operators.get().type == Token::FUNCTION) {
                postfix << operators.get().value << " ";
                operators.delete_el();
            }
        }
    }

    while (!operators.empty())
    {
        postfix << operators.get().value << " ";
        operators.delete_el();
    }

    if (openParenthesisCount != closeParenthesisCount || openParenthesisCount > 1 || closeParenthesisCount > 1) {
        cout << "Ошибка: недостающие скобки" << endl;
        return 0;  // или другое значение, указывающее на ошибку
    }

    return postfix.str();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////Функция подсчета

double magic(const string& Expression)
{
    stringstream ss(Expression);
    Stack<double> stack;
    string token;

    while (ss >> token) {
        if (isdigit(token[0]) || (token.size() > 1 && isdigit(token[1])))
        {
            stack.add(stod(token));
        }
        else if (Operator_check(token))
        {
            if (stack.size() < 2)
            {
                cerr << "Ошибка: Недостаточно операндов для оператора " << token << "\n";
                exit(EXIT_FAILURE);
            }
            double operand2 = stack.get();
            stack.delete_el();
            double operand1 = stack.get();
            stack.delete_el();

            switch (token[0])
            {
            case '+':
                stack.add(operand1 + operand2);
                break;
            case '-':
                stack.add(operand1 - operand2);
                break;
            case '*':
                stack.add(operand1 * operand2);
                break;
            case '/':
                if (operand2 != 0) {
                    stack.add(operand1 / operand2);
                }
                else
                {
                    cerr << "Ошибка: Деление на 0." << "\n";
                    exit(EXIT_FAILURE);
                }
                break;
            case '^':
                stack.add(pow(operand1, operand2));
                break;
            default:
                cerr << "Ошибка: Неизвестный оператор." << "\n";
                exit(EXIT_FAILURE);
            }
        }
        else if (Func_check(token))
        {
            if (stack.empty())
            {
                cerr << "Ошибка: Недостаточно операндов для функции " << token << "\n";
                exit(EXIT_FAILURE);
            }
            double operand = stack.get();
            stack.delete_el();

            if (token == "cos")
            {
                stack.add(cos(operand));
            }
            else if (token == "sin")
            {
                stack.add(sin(operand));
            }
        }
        else
        {
            cerr << "Ошибка: Неизвестный токен." << "\n";
            exit(EXIT_FAILURE);
        }
    }
    if (stack.size() != 1) {
        cerr << "Ошибка: Неверное количество операндов." << "\n";
        exit(EXIT_FAILURE);
    }

    return stack.get();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void testlist() {
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
    for (int i = 0;i < lst.size();i++)
        cout << lst[i]->data << " ";
    cout << "\n" << "размер списка  " << lst.size() << "\n";
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

}

void testarray() {
    DArray<int> d;
    d.push(666);
    d.push(777);
    d.push(888);
    d.push(999);
    d.push(000);
    d.push(111);
    d.push(222);
    d.insert(12345, 4);
    d.remove(6);
    d.insert(12345, 7);
    d.push(222);
    for (int i = 0;i < d.getsize();i++)
    {
        cout << d[i] << "\n";
    }
    cout << "размер масcива " << d.getsize() << "\n\n";
}

void teststack() 
{
    cout << "Введите выражение: ";

    string infixExpression;
    getline(cin, infixExpression);

    string postfixExpression = infixToPostfix(infixExpression);

    cout << "Постфиксное выражение: " << postfixExpression << "\n";
    double result = magic(postfixExpression);
    cout << "Результат: " << result << "\n";

    SetConsoleTextAttribute(Output, 12);
    cout << "Со смертью этого персонажа нить вашей судьбы обрывается. Загрузите сохранённую игру дабы восстановить течение судьбы, или живите дальше в проклятом мире, который сами и создали..." << "\n\n\n";
    SetConsoleTextAttribute(Output, 7);
    
}

int main()
{
    testlist();

    testarray();

    teststack();
    return 0;
    
}