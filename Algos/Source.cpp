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
            cerr<<"Неверная позиция"<< "\n";
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
            cerr<<"Ошибка: индекс преисполнился и ушел за границы"<<"\n";
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
    LinkedList() //êîíñòðóêòîð
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
        if (index > listSize / 2) //ïðîâåðêà íà ïîçèöèþ ýëåìåíòà
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
        while (current != nullptr && current->data != data)// èùåì óçåë ñ êîíêðåòíûì çíà÷åíèåì 
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

    void add(T data) // äîáàâëÿåì â ñòåê
    {
        list.add_first(data);
    }

    void delete_el() {
        list.delete_first();
    }

    T get()  {//ïîë÷àåì èíôó 
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

    Token(Type type = OPERAND, const string& value = "") : type(type), value(value) {}//êîíñòðóêòîð co çíà÷åíèÿìè ïî óìîë÷àíèþ
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

    while (ss >> token) //ïîêà åñòü ÷òî ñ÷èòûâàòü
    {
        if (isdigit(token[0]) || (token.size() > 1 && isdigit(token[1]))) {
            postfix << token << " ";
        }
        else if (Operator_check(token) || Func_check(token))// ïðîâåðêà íà ðàçëè÷íûå îïåðàòîðû 
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
            operators.delete_el(); // Óáèðàåì îòêðûâàþùóþ ñêîáêó
        }
    }

    while (!operators.empty())
    {
        postfix << operators.get().value << " ";
        operators.delete_el();
    }

    if (openParenthesisCount != closeParenthesisCount || openParenthesisCount > 1 || closeParenthesisCount > 1) {
        cout << "Îøèáêà: íåäîñòàþùèå ñêîáêè" << endl;
        return 0;  // èëè äðóãîå çíà÷åíèå, óêàçûâàþùåå íà îøèáêó
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
            cerr << "Ошибка: Неизвестный токен в обратной польской записи." << "\n";
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




int main()

{///////////////////////////////////////////////////////////////////////////////////////// ÒÅÑÒ ÑÏÈÑÊÀ
	LinkedList<string> lst;

    setlocale(LC_ALL, "Russian");
	//äîáàâëÿåì 4 ýëåìåíòà â íàø ñïèñîê 
	lst.add_first("îîîîî");
	lst.add_last("âåëèêèé");
	lst.add_last("ñóï");
	lst.add_last("íàâàðèëè");
	//âûâîäèì ÷àñòü èç íèõ ÷òîáû ïðîâåðèòü ôóíêöèþ äîáàâëåíèÿ
	cout << lst.get(0)->data << "\n";
	cout << lst.get(1)->data << "\n";
	cout << lst.get(2)->data << "\n";
    cout << lst.get(3)->data << "\n\n";
	//äîïîëíèì ñïèñîê 2 íîâûìè ýëåìåíòàìè è âûâåäåì âåñü ñïèñîê íà ýêðàí 
	lst.insert(5, "ØÈÊÀÐÍÛÉ");
	lst.insert(6, "Íàâàðèëè?");
	for (int i =0 ;i<lst.size();i++)
		cout << lst[i]->data << " ";
    cout <<"\n" << "ðàçìåð ñïèñêà  " << lst.size() << "\n";
	cout << "\n\n";
	//òåïåðü ïðîâåðèì ôóíêöèþ óäàëåíèÿ è âûâåäåì ñïèñîê ïîñëå óäàëåíèÿ íåñêîëüêèõ ýëåìåíòîâ
	lst.erase(0);
    lst.erase(3);
	lst.erase(5);
	lst.erase(7);//íè÷åãî íå óäàëèòñÿ òê ýòî íåñóùåñòâóþùèé ýëåìåíò

    lst.remove_current("Íàâàðèëè?");

	for (int i = 0;i < lst.size();i++)
		cout << lst[i]->data << " ";
	cout << "\n";
	cout << "ðàçìåð ñïèñêà  " << lst.size() << "\n\n\n";
   
   
	///////////////////////////////////////////////////////////////////////////////////////// ÒÅÑÒ ÌÀÑÑÈÂÀ
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
    for (int i = 0;i < d.getsize();i++) {
        cout << d[i] << "\n";
    }
    cout << "размер масcива "<<d.getsize() << "\n\n";


    ///////////////////////////////////////////////////////////////////////////////////////// TEST STACK
    cout << "Ââåäèòå âûðàæåíèå: ";

    string infixExpression;
    getline(cin, infixExpression);

    string postfixExpression = infixToPostfix(infixExpression);

    cout << "Постфиксное выражение: " << postfixExpression << "\n";
   double result = magic(postfixExpression);
   cout << "Результат: " << result << "\n";

    SetConsoleTextAttribute(Output, 12);
    cout << "Ñî ñìåðòüþ ýòîãî ïåðñîíàæà íèòü âàøåé ñóäüáû îáðûâàåòñÿ. Çàãðóçèòå ñîõðàí¸ííóþ èãðó äàáû âîññòàíîâèòü òå÷åíèå ñóäüáû, èëè æèâèòå äàëüøå â ïðîêëÿòîì ìèðå, êîòîðûé ñàìè è ñîçäàëè..." << "\n\n\n";
    SetConsoleTextAttribute(Output, 7);
    return 0;
}
