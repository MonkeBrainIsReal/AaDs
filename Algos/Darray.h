#pragma once
#include<iostream>
#ifndef DArray_H
#define DArray_H
using namespace std;
template<typename T>
class DArray
{
private:
	int cap;
	int NumOfEl;
	T** arr;
public:
	DArray(int size = 5);
	~DArray();

	void initialize(int from = 0);
	void expand();
	void push(const T &element);
	const int& size()const 
	{
		return this->NumOfEl;
	}

	T& operator[](const int index);//вместо функции get, будет оператор который возвращает значение по индексу 

};
#endif // !DArray_H

