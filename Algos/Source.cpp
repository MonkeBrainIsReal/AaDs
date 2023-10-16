#include <iostream>
#include <windows.h>
#include <string>
#include <cctype>
#include <sstream>
#include <cmath>

using namespace std;
HANDLE Output = GetStdHandle(STD_OUTPUT_HANDLE);


template<typename T> class DArray
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

    };

    ~DArray()
    {
        for (int i = 0; i < NumOfEl; i++)
        {
            delete this->arr[i];
        }
        delete[]this->arr;
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


template <typename T> class Stack {
private:
    LinkedList<T> list;

public:
    Stack() {}

    ~Stack() {}

    void add(T data) // ��������� � ����
    {
        list.add_first(data);
    }

    void delete_el() {
        list.delete_first();
    }

    T get()  {//������� ���� 
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

    int size()  {
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
    double toDouble();

    Token(Type type = OPERAND, const string& value = "") : type(type), value(value) {}//����������� co ���������� �� ���������
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

    while (ss >> token) //���� ���� ��� ���������
    {
        if (isdigit(token[0]) || (token.size() > 1 && isdigit(token[1]))) {
            postfix << token << " ";
        }
        else if (Operator_check(token) || Func_check(token))// �������� �� ��������� ��������� 
        {
            if (Func_check(token))
            {
                operators.add(Token(Token::FUNCTION, token));
            }
            else
            {
                while (!operators.empty() && (operators.get().type == Token::OPERATOR || operators.get().type == Token::FUNCTION) && OperatorPriority(operators.get().value) >= OperatorPriority(token) && FuncPriority(operators.get().value) == 0)
                {
                    postfix << operators.get().value << " ";
                    operators.delete_el();
                }
                operators.add(Token(Token::OPERATOR, token));
            }
        }
        else if (token == "(")
        {
            operators.add(Token(Token::OPEN_PARENTHESIS, token));
            openParenthesisCount++;
        }
        else if (token == ")")
        {
            closeParenthesisCount++;
            while (!operators.empty() && operators.get().type != Token::OPEN_PARENTHESIS)
            {
                postfix << operators.get().value << " ";
                operators.delete_el();
            }
            operators.delete_el(); // ������� ����������� ������
        }
    }

    while (!operators.empty())
    {
        postfix << operators.get().value << " ";
        operators.delete_el();
    }

    if (openParenthesisCount != closeParenthesisCount || openParenthesisCount > 1 || closeParenthesisCount > 1) {
        cout << "������: ����������� ������" << endl;
        return 0;  // ��� ������ ��������, ����������� �� ������
    }

    return postfix.str();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////

double Token::toDouble()
{
    if (type == OPERAND)
    {
        return stod(value);
    }
    else
    {
        // � ������ ������� �������������� ��������� ��� �������
        cout << "Error: Cannot convert operator or function to double." << endl;
        return 0;
    }
}

double applyOperator(double operand1, double operand2, const string& op) // ����� ��������� �������� ��� ����
{
    if (op == "+") 
    {
        return operand1 + operand2;
    }
    else if (op == "-") 
    {
        return operand1 - operand2;
    }
    else if (op == "*") 
    {
        return operand1 * operand2;
    }
    else if (op == "/") 
    {
        if (operand2 != 0) 
        {
            return operand1 / operand2;
        }
        else 
        {
            cout << "������: ������� �� 0." << endl;
            exit(EXIT_FAILURE);
        }
    }
    else if (op == "^") 
    {
        return pow(operand1, operand2);
    }
    else 
    {
        cout << "������: ����������� ��������." << endl;
        exit(EXIT_FAILURE);
    }
}

double applyFunction(double operand, const string& func) //�� ��������
{
    if (func == "sin") 
    {
        return sin(operand);
    }
    else if (func == "cos") 
    {
        return cos(operand);
    }
    else 
    {
        cout << "������: ����������� �������." << endl;
        exit(EXIT_FAILURE);
    }
}

double evaluatePostfix(const string& postfixExpression) // ������� ����� ���� �������

{
    stringstream ss(postfixExpression);
    Stack<Token> operands;
    string token;

    while (ss >> token) 
    {
        if (isdigit(token[0]) || (token.size() > 1 && isdigit(token[1]))) 
        {
            operands.add(Token(Token::OPERAND, token));
        }
        else if (Operator_check(token) || Func_check(token)) 
        {
            if (Func_check(token)) 
            {
                operands.add(Token(Token::FUNCTION, token));
            }
            else
            {
                Token operand2 = operands.get();
                operands.delete_el();
                Token operand1 = operands.get();
                operands.delete_el();
                double result = applyOperator(operand1.toDouble(), operand2.toDouble(), token);
                operands.add(Token(Token::OPERAND, to_string(result)));
            }
        }
        else if (token == "(") 
        {
            operands.add(Token(Token::OPEN_PARENTHESIS, token));
        }
        else if (token == ")") 
        {
            while (!operands.empty() && operands.get().type != Token::OPEN_PARENTHESIS) 
            {
                cout << "������: ����������� ������" << endl;
                exit(EXIT_FAILURE);
            }
            operands.delete_el(); 
        }
    }

    if (operands.size() == 1) 
    {
        return stod(operands.get().value);
    }
    else 
    {
        cout << "���.. ��� �� ������..." << endl;
        exit(EXIT_FAILURE);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////




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


    ///////////////////////////////////////////////////////////////////////////////////////// TEST STACK
    cout << "������� ���������: ";

    string infixExpression;
    getline(cin, infixExpression);

    string postfixExpression = infixToPostfix(infixExpression);

    cout << "����������� ���������: " << postfixExpression << "\n";
   double result = evaluatePostfix(postfixExpression);
   cout << "���������: " << result << "\n";

    SetConsoleTextAttribute(Output, 12);
    cout << "�� ������� ����� ��������� ���� ����� ������ ����������. ��������� ���������� ���� ���� ������������ ������� ������, ��� ������ ������ � ��������� ����, ������� ���� � �������..." << "\n\n\n";
    SetConsoleTextAttribute(Output, 7);
    return 0;
}