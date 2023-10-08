#include <iostream>
using namespace std;
template <typename T>
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

    int size() {
        Node<T>* ptr = tail;
        int length = 0;
        while (ptr != nullptr) {
            ptr = ptr->prev;
            length++;
        }
        return length;
    }

    Node<T>* operator [] (int index) {
        return get(index);
    }
};

int main()
{
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
	cout<<"������ ������  " << lst.size() << "\n\n";
	for (int i =0 ;i<lst.size();i++)
		cout << lst[i]->data << " ";
	cout << "\n\n";
	//������ �������� ������� �������� � ������� ������ ����� �������� ���������� ���������
	lst.erase(0);
    lst.erase(3);
	lst.erase(5);
	lst.erase(7);//������ �� �������� �� ��� �������������� �������

	for (int i = 0;i < lst.size();i++)
		cout << lst[i]->data << " ";
	cout << "\n";
	cout << "������ ������  " << lst.size() << "\n";
	return 0;

}