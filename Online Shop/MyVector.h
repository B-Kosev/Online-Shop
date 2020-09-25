#pragma once
#include <iostream>

using namespace std;

template<typename T>
class Vector
{
	T* arr;
	int size;
public:
	Vector() { arr = nullptr; size = 0; };
	Vector(const Vector<T>&);
	Vector<T>& operator=(const Vector<T>&);
	~Vector();

	//modifiers
	void pushBack(T);
	void popBack();
	void clear();
	void remove(int);
	void sort();

	//capacity
	int getSize() const;
	bool empty() const;

	T& operator[](int);
	const T& operator[](int) const;
	T& at(int);
};

template<typename T>
inline Vector<T>::Vector(const Vector<T>& obj)
{
	arr = new T[obj.size];
	for (int i = 0;i < obj.size;i++)
	{
		arr[i] = obj.arr[i];
	}
	size = obj.size;
}

template<typename T>
inline Vector<T>& Vector<T>::operator=(const Vector<T>& obj)
{
	if (this != &obj)
	{
		delete[] arr;
		size = obj.size;
		arr = new T[obj.size];
		for (int i = 0;i < obj.size;i++)
		{
			arr[i] = obj.arr[i];
		}
	}
	return *this;
}

template<typename T>
inline Vector<T>::~Vector()
{
	delete[] arr;
}

template<typename T>
inline void Vector<T>::pushBack(T el)
{
	T* newArr = new T[size + 1];
	for (int i = 0;i < size;i++)
	{
		newArr[i] = arr[i];
	}
	newArr[size] = el;
	size++;
	delete[] arr;
	arr = newArr;
}

template<typename T>
inline void Vector<T>::popBack()
{
	T* newArr = new T[size - 1];
	for (int i = 0;i < size - 1;i++)
	{
		newArr[i] = arr[i];
	}
	size--;
	delete[] arr;
	arr = newArr;
}

template<typename T>
inline void Vector<T>::clear()
{
	delete[] arr;
	arr = nullptr;
	size = 0;
}

template<typename T>
inline void Vector<T>::remove(int pos)
{
	if (pos<0 || pos >size - 1)
	{
		cout << "Position out of bounds.\n";
		return;
	}

	T* newArr = new T[size - 1];
	for (int i = 0;i < size;i++)
	{
		if (i != pos) newArr[i] = arr[i];
		else continue;
	}
	size--;
	delete[] arr;
	arr = newArr;
}

template<typename T>
void Vector<T>::sort()
{
	T temp;
	for (int i = 0;i < size;i++)
	{
		for (int j = 0;j < size - i - 1;j++)
		{
			if (arr[j] > arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

template<typename T>
inline int Vector<T>::getSize() const
{
	return size;
}

template<typename T>
inline bool Vector<T>::empty() const
{
	if (size != 0) return true;
	return false;
}

template<typename T>
inline T& Vector<T>::operator[](int pos)
{
	if (pos>=0 || pos<size) return arr[pos];
}

template<typename T>
inline const T& Vector<T>::operator[](int pos) const
{
	if (pos>=0 || pos<size) return arr[pos];
}

template<typename T>
inline T& Vector<T>::at(int pos)
{
	if (pos>=0 || pos<size) cout << "Out of bounds\n";
	return arr[pos];
}