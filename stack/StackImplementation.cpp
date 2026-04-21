#include "StackImplementation.h"

void StackOnVector::push(const ValueType& value) {
       vec.pushBack(value);
}       

void StackOnVector::pop() {
	vec.popBack();
}

const ValueType& StackOnVector::top() const {
	return vec[size()-1];
}

bool StackOnVector::isEmpty() const {
	return !(vec.size() > 0);
}

size_t StackOnVector::size() const {
	return vec.size();
}

const ValueType& StackOnVector::operator[](int k) const {
	return vec[k];
}

ValueType& StackOnVector::operator[](int k) {
	return vec[k];
}

void StackOnList::push(const ValueType& value) {
       list.push_back(value);
}       

void StackOnList::pop() {
	list.pop_back();
}

const ValueType& StackOnList::top() const {
	return list[size()-1];
}

bool StackOnList::isEmpty() const {
	return !(list.size() > 0);
}

size_t StackOnList::size() const {
	return list.size();
}

const ValueType& StackOnList::operator[](int k) const {
	return list[k];
}

ValueType& StackOnList::operator[](int k) {
	return list[k];
}
