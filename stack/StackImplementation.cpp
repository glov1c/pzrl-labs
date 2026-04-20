#include "StackImplementation.h"

void StackOnVector::push(const ValueType& value) {
       vec.pushBack(value);
}       

void StackOnVector::pop() {
	vec.popBack();
}

const ValueType& StackOnVector::top() const {
	return vec[size()];
}

bool StackOnVector::isEmpty() const {
	return !(vec.size() > 0);
}

size_t StackOnVector::size() const {
	return vec.size();
}

void StackOnList::push(const ValueType& value) {
       list.push_back(value);
}       

void StackOnList::pop() {
	list.pop_back();
}

const ValueType& StackOnList::top() const {
	return list[size()];
}

bool StackOnList::isEmpty() const {
	return !(list.size() > 0);
}

size_t StackOnList::size() const {
	return list.size();
}
