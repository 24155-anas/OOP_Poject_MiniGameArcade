#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H
#include<iostream>
using namespace std;


template <typename T>
class Dynamic_array {
private:
	T* arr;
	int len;
	int cap;

	void double_capacity();
public:
	Dynamic_array();
	Dynamic_array(int count, T value);

	Dynamic_array(const Dynamic_array<T>& other);
	~Dynamic_array();

	Dynamic_array& operator=(const Dynamic_array<T>& other);
	T& operator[](int index);
	const T& operator[](int index) const;
	bool operator==(const Dynamic_array<T>& other) const;
	bool operator!=(const Dynamic_array<T>& other) const;
	Dynamic_array operator+(const Dynamic_array<T>& other) const;
	Dynamic_array& operator+=(const Dynamic_array<T>& other);

	void push(T value);
	void pop();
	void insert_at(int idx, T value);
	void delete_at(int index);
	void reserve(int new_capacity);
	void clear();
	void swap(Dynamic_array<T>& other);
	void shrink_to_fit();
	void reverse();


	bool empty() const;
	int size() const;

	T& at(int index);
	const T& at(int index) const;

	T& front();
	const T& front() const;

	T& back();
	const T& back() const;

	int find(T value) const;



	//ye kuch extra funxtionalities maine add ki ha
	Dynamic_array(int size);
	void display();

	template <typename U>   //this tells the compiler k ye func friend ha current template instantiation ka 
	// u cannot make a freind under the same template here , we need to make another template 

	friend bool valid_index(const Dynamic_array<U>& d1, int idx); //=====ye maine add kia to check valid index for insert at funcs and others aswell===

};


template<typename T>
void Dynamic_array<T>::double_capacity() {
	this->cap = this->cap * 2;
}

template<typename T>
void Dynamic_array<T>::display() {
	for (int i = 0; i < this->len; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

template<typename T>
Dynamic_array<T>::Dynamic_array() {
	this->arr = nullptr;
	this->len = 0;
	this->cap = 0;
}

template<typename T>
Dynamic_array<T>::Dynamic_array(int size) {
	this->cap = size;
	this->len = size;
	this->arr = new T[this->len];
}

template<typename T>
Dynamic_array<T>::Dynamic_array(int count, T value) {
	this->len = count;
	this->cap = len;
	this->arr = new T[this->len];
	for (int i = 0; i < this->len; i++) {
		this->arr[i] = value;
	}
}

template<typename T>
Dynamic_array<T>::Dynamic_array(const Dynamic_array<T>& other) {
	this->len = other.len;
	this->cap = other.cap;
	this->arr = new T[this->len];

	for (int i = 0; i < this->len; i++) {
		this->arr[i] = other.arr[i];
	}
}

template<typename T>
Dynamic_array<T>::~Dynamic_array() {
	delete[]this->arr;
}

template<typename T>
Dynamic_array<T>& Dynamic_array<T>::operator=(const Dynamic_array<T>& other) {
	this->len = other.len;
	this->cap = other.cap;
	this->arr = new T[this->len];

	for (int i = 0; i < this->len; i++) {
		this->arr[i] = other.arr[i];
	}

	return *this;
}


template<typename T>
T& Dynamic_array<T>:: operator[](int index) {
	return this->arr[index];
}

template<typename T>
const T& Dynamic_array<T>::operator[](int index) const {
	return this->arr[index];
}

template<typename T>
bool Dynamic_array<T>::operator==(const Dynamic_array<T>& other) const {
	if (this->len != other.len) {
		return false;
	}
	for (int i = 0; i < other.len; i++) {
		if (this->arr[i] != other.arr[i]) {
			return false;
		}
	}

	return true;
}

template<typename T>
bool Dynamic_array<T>::operator!=(const Dynamic_array<T>& other) const {
	if (this->len != other.len) {
		return true;
	}
	for (int i = 0; i < other.len; i++) {
		if (this->arr[i] != other.arr[i]) {
			return true;
		}
	}

	return false;
}

template<typename T>
Dynamic_array<T> Dynamic_array<T>:: operator+(const Dynamic_array<T>& other) const {
	Dynamic_array<T> temp(this->len + other.len);
	for (int i = 0; i < this->len; i++) {
		temp.arr[i] = this->arr[i];
	}
	for (int i = 0; i < other.len; i++) {
		temp.arr[this->len + i] = other.arr[i];
	}
	temp.len = this->len + other.len;
	return temp;
}


template<typename T>
Dynamic_array<T>& Dynamic_array<T>::operator+=(const Dynamic_array<T>& other) {
	T* temp = new T[(this->len + other.len)];
	for (int i = 0; i < this->len; i++) {
		temp[i] = this->arr[i];
	}
	for (int i = 0; i < other.len; i++) {
		temp[this->len + i] = other.arr[i];
	}

	delete[]this->arr;
	this->arr = new T[this->len + other.len];
	for (int i = 0; i < this->len + other.len; i++) {
		this->arr[i] = temp[i];
	}
	this->len = this->len + other.len;
	delete[]temp;
	return*this;
}

template<typename T>
void Dynamic_array<T>::push(T value) { //end pe add
	if (this->len == this->cap) {
		if (this->cap == 0) {
			this->cap = 1;
		}
		else {
			cap = cap * 2;
		}
		T* temp = new T[this->cap];
		for (int i = 0; i < this->len; i++) {
			temp[i] = this->arr[i];
		}
		delete[] this->arr;
		this->arr = temp;
	}
	this->arr[this->len++] = value;

}

template<typename T>
void Dynamic_array<T>::pop() { //akhri elmnt rmv
	T* temp = new T[this->len];
	for (int i = 0; i < this->len; i++) {
		temp[i] = this->arr[i];
	}
	delete[]this->arr;
	this->len--;

	this->arr = new T[this->len];
	for (int i = 0; i < this->len; i++) {
		this->arr[i] = temp[i];
	}
	delete[]temp;
}

template<typename T>
void Dynamic_array<T>::insert_at(int idx, T value) {
	if (this->cap == this->len) {
		//regrow
		this->cap = this->cap * 2;
		T* temp = new T[this->cap];

		//copy
		for (int i = 0; i < this->len; i++) {

			temp[i] = this->arr[i];

		}
		for (int i = this->len; i >= idx; i--) {
			temp[i + 1] = temp[i];
		}

		temp[idx] = value;
		this->len++;

		delete[]arr;
		this->arr = new T[this->cap];

		for (int i = 0; i < this->len; i++) {
			this->arr[i] = temp[i];
		}
	}
	else {
		//right shift
		for (int i = this->len; i >= idx; i--) {
			arr[i + 1] = arr[i];
		}
		arr[idx] = value;
		this->len++;
	}

}

template<typename T>
void Dynamic_array<T>::delete_at(int index) {
	//us index tk left shift
	for (int i = index; i < this->len - 1; i++) {
		this->arr[i] = this->arr[i + 1];
	}
	this->len--;
}

template<typename T>
void Dynamic_array<T>::reserve(int new_capacity) { //capacity reserve(sirf capacity barhegi aur size same rahega)
	T* temp_arr = new T[new_capacity];
	for (int i = 0; i < this->len; i++) {
		temp_arr[i] = this->arr[i];
	}
	delete[] this->arr;
	this->arr = new T[new_capacity];
	for (int i = 0; i < this->len; i++) {
		this->arr[i] = temp_arr[i];
	}
	this->cap = new_capacity;
	delete[]temp_arr;
}


template<typename T>
void Dynamic_array<T>::clear() {//clear all elmnts
	delete[]this->arr;
	this->arr = new T[1];
	this->cap = 1;
	this->len = 0;
}


template<typename T>
void Dynamic_array<T>::swap(Dynamic_array<T>& other) {//swaps
	//temp me other copy hogaya
	Dynamic_array<T> temp(other);

	//other me this copy krna
	other = *this;

	//ab this me temp copy krna
	*this = temp;
}


template<typename T>
void Dynamic_array<T>::shrink_to_fit() {
	if (this->len != this->cap) {
		//capacity hi bari hogi
		this->cap = this->cap - this->len;
	}
}


template<typename T>
void Dynamic_array<T>::reverse() {
	for (int i = 0; i < this->len / 2; i++) {
		T temp = arr[i];
		arr[i] = arr[len - i - 1];
		arr[len - i - 1] = temp;
	}
}


template<typename T>
bool Dynamic_array<T>::empty() const { //check if array is empty
	//empty hone k loye len zero hogi
	if (this->len == 0) {
		return true;
	}
	return false;
}


template<typename T>
int Dynamic_array<T>::size() const {//returns siize
	return this->len;
}


template<typename T>
T& Dynamic_array<T>::at(int index) {
	if (index >= 0 && index < this->len) {
		return this->arr[index];
	}
}

template<typename T>
const T& Dynamic_array<T>::at(int index) const {
	if (index >= 0 && index < this->len) {
		return this->arr[index];
	}
}


template<typename T>
T& Dynamic_array<T>::front() {

	return this->arr[0];
}

template<typename T>
const T& Dynamic_array<T>::front() const {
	return this->arr[0];
}


template<typename T>
T& Dynamic_array<T>::back() {

	return this->arr[this->len - 1];
}

template<typename T>
const T& Dynamic_array<T>::back() const {
	return this->arr[this->len - 1];

}


template<typename T>
int Dynamic_array<T>::find(T value) const {
	for (int i = 0; i < this->len; i++) {
		if (this->arr[i] == value) {
			return i;
		}
	}
	return -1;
}


template<typename T>
bool valid_index(const Dynamic_array<T>& d1, int idx) {
	if (idx >= 0 && idx < d1.len) {
		return true;
	}
	return false;

}


#endif 
#pragma once
