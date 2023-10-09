#include "Darray.h"
#include <iostream>
using namespace std;

template<typename T>
DArray<T>::DArray(int size)
{
	this->cap = size;
	this->NumOfEl = 0;
	this->arr = new T * [this->cap];

	initialize(this->NumOfEl);

};

template<typename T>
DArray<T>::~DArray()
{
	for (int i = 0; i < NumOfEl; i++)
	{
		delete this->arr[i];
	}
	delete[]this->arr;
};

template<typename T>
void DArray<T>::initialize(int from)
{
	for (int i = from; i < cap; i++)
	{
		this->arr[i] = nullptr;
	}
};

template<typename T>
void DArray<T>::expand()
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

template<typename T>
T& DArray<T>::operator[](const int index)
{
	if (index < 0 || index >= this->NumOfEl) 
	{
		throw("trying to access unallocated memory");
	}
	return *this->arr[index];
};

template<typename T>
void DArray<T>::push(const T& element)
{
	if (this->NumOfEl >= this->cap)
	{
		this->expand();
	}

	this->arr[this->NumOfEl++] = new T(element);
};