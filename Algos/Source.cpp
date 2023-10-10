#include <iostream>
#include <windows.h>
#include <string>
#include <cctype>
#include <sstream>
#include <cmath>

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

    DArray(int size = 6)//������� ����������� � ����� �� ��������� ��������
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
            this->arr[i] = nullptr;//��������� �������� 0
        }
    };

   void expand()//�������� ��� ���������� ������ �������
    {
        this->cap *= 2;
        T** tempArr = new T * [this->cap];

        for (int i = 0;i < this->NumOfEl;i++)
        {
            tempArr[i] = new T(*this->arr[i]);
        }

        for (int i = 0; i < NumOfEl; i++)
        {
            delete this->arr[i];//��������� ��� �������� �������
        }
        delete[]this->arr;

        this->arr = tempArr;
        initialize(this->NumOfEl);


    };

   void push(const T& element)//���������� �������� � ������ �������
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

    T& operator [](const int index)//������ ������� get, ����� �������� ������� ���������� �������� �� ������� 
    {
        if (index < 0 || index >= this->NumOfEl)
        {
            throw("trying to access unallocated memory");
        }
        return *this->arr[index];
    };
    void insert(const T& element, int position)
    {
        if (position < 0 || position > this->NumOfEl)
        {
            throw("Invalid position");
        }

        if (this->NumOfEl >= this->cap)
        {
            this->expand();
        }

        // �������� �������� ������ ��� ������������ ����� ��� ����� �������
        for (int i = this->NumOfEl; i > position; --i)
        {
            this->arr[i] = this->arr[i - 1];
        }

        // ��������� ����� �������
        this->arr[position] = new T(element);
        ++this->NumOfEl;
    }
    void remove(int index)
    {
        if (index < 0 || index >= this->NumOfEl)
        {
            throw("Invalid index");
        }

        // ����������� ������, ���������� ��� �������, ������� �� �������
        delete this->arr[index];

        // �������� �������� ����� ��� ���������� ������� �����
        for (int i = index; i < this->NumOfEl - 1; ++i)
        {
            this->arr[i] = this->arr[i + 1];
        }

        // ��������� ���������� ��������� � �������
        --this->NumOfEl;
    }
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
    LinkedList() //�����������
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
        if (index > listSize / 2) //�������� �� ������� ��������
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
        while (current != nullptr && current->data != data)// ���� ���� � ���������� ��������� 
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


template <typename T>
class Stack {
private:
    LinkedList<T> list;

public:
    Stack() {}

    // ����������� �����������
    Stack(const Stack& other) : list(other.list) {}

    // ����������� �����������
    Stack(Stack&& other) noexcept : list(std::move(other.list)) {}

    ~Stack() {}

    void push(T data) {
        list.add_first(data);
    }

    void pop() {
        list.delete_first();
    }

    T top() const {//������� ���� 
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

    int size() const {
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

    Token(Type type = OPERAND, const string& value = "") : type(type), value(value) {}
};

bool isOperatorOrPower(const string& token) {
    return token == "+" || token == "-" || token == "*" || token == "/" || token == "^";
}

bool isFunction(const string& token) {
    return token == "sin" || token == "cos";
}

int getOperatorOrPowerPriority(const string& op) {
    if (op == "+" || op == "-")
        return 1;
    else if (op == "*" || op == "/")
        return 2;
    else if (op == "^")
        return 3;
    else
        return 0;
}

string infixToPostfix(const string& infixExpression) {
    stringstream ss(infixExpression);
    Stack<Token> operators;
    stringstream postfix;

    string token;
    while (ss >> token) //���� ���� ��� ���������
    {
        if (std::isdigit(token[0]) || (token.size() > 1 && std::isdigit(token[1]))) {
            postfix << token << " ";
        }
        else if (isOperatorOrPower(token) || isFunction(token))// �������� �� ��������� ��������� 
        {
            while (!operators.empty() && (operators.top().type == Token::OPERATOR || operators.top().type == Token::FUNCTION) && getOperatorOrPowerPriority(operators.top().value) >= getOperatorOrPowerPriority(token)) 
            {
                postfix << operators.top().value << " ";
                operators.pop();
            }
            operators.push(Token(Token::OPERATOR, token));
        }
        else if (token == "(") 
        {
            operators.push(Token(Token::OPEN_PARENTHESIS, token));
        }
        else if (token == ")") 
        {
            while (!operators.empty() && operators.top().type != Token::OPEN_PARENTHESIS) 
            {
                postfix << operators.top().value << " ";
                operators.pop();
            }
            operators.pop(); // ������� ����������� ������
        }
    }

    while (!operators.empty()) 
    {
        postfix << operators.top().value << " ";
        operators.pop();
    }

    return postfix.str();
}

int main()

{///////////////////////////////////////////////////////////////////////////////////////// ���� ������
	LinkedList<string> lst;

    

    setlocale(LC_ALL, "Russian");
	//��������� 4 �������� � ��� ������ 
	lst.add_first("�����");
	lst.add_last("�������");
	lst.add_last("���");
	lst.add_last("��������");
	//������� ����� �� ��� ����� ��������� ������� ����������
	cout << lst.get(0)->data << "\n";
	cout << lst.get(1)->data << "\n";
	cout << lst.get(2)->data << "\n";
    cout << lst.get(3)->data << "\n\n";
	//�������� ������ 2 ������ ���������� � ������� ���� ������ �� ����� 
	lst.insert(5, "��������");
	lst.insert(6, "��������?");
	for (int i =0 ;i<lst.size();i++)
		cout << lst[i]->data << " ";
    cout <<"\n" << "������ ������  " << lst.size() << "\n";
	cout << "\n\n";
	//������ �������� ������� �������� � ������� ������ ����� �������� ���������� ���������
	lst.erase(0);
    lst.erase(3);
	lst.erase(5);
	lst.erase(7);//������ �� �������� �� ��� �������������� �������

    lst.remove_current("��������?");

	for (int i = 0;i < lst.size();i++)
		cout << lst[i]->data << " ";
	cout << "\n";
	cout << "������ ������  " << lst.size() << "\n\n\n";
   
   
	///////////////////////////////////////////////////////////////////////////////////////// ���� �������
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
    for (int i = 0;i < d.size();i++) {
        cout << d[i] << "\n";
    }
    cout << "������ ���c��� "<<d.size() << "\n\n";
    cout << "������� ��������� ���������: ";

    string infixExpression;
    getline(cin, infixExpression);

    string postfixExpression = infixToPostfix(infixExpression);

    cout << "����������� ���������: " << postfixExpression << "\n";

    SetConsoleTextAttribute(Output, 12);
    cout << "�� ������� ����� ��������� ���� ����� ������ ����������. ��������� ���������� ���� ���� ������������ ������� ������, ��� ������ ������ � ��������� ����, ������� ���� � �������..." << "\n\n\n";
    SetConsoleTextAttribute(Output, 7);
    return 0;
}