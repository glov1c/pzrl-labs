#include <iostream>

#include "Stack.h"
#include "StackImplementation.h"

Stack::Stack(StackContainer container): _containerType(container) {
	if (container == StackContainer::Vector) _pimpl = new StackOnVector(); 
	else if (container == StackContainer::List) _pimpl = new StackOnList(); 
	else throw std::runtime_error("no such container type");
}


Stack::Stack(const ValueType* valueArray, const size_t arraySize, StackContainer container) {
	if (container == StackContainer::Vector) _pimpl = new StackOnVector(); 
	else if (container == StackContainer::List) _pimpl = new StackOnList(); 
	else throw std::runtime_error("no such container type");

	for(size_t i = 0; i < arraySize; i++) {
		push(valueArray[i]);
	}
}

Stack::Stack(const Stack& copyStack) {
	if (copyStack._containerType == StackContainer::Vector) {
		*this = Stack((ValueType*)copyStack._pimpl, copyStack._pimpl->size(), StackContainer::Vector);
	}
	else if (copyStack._containerType == StackContainer::List) {
		*this = Stack((ValueType*)copyStack._pimpl, copyStack._pimpl->size(), StackContainer::List);
	}
	else throw std::runtime_error("no such container type");
}

Stack& Stack::operator=(const Stack& copyStack) {
	if (this == &copyStack) return *this;
	*this = Stack(copyStack);
	delete copyStack._pimpl;
	return *this;
}

Stack::Stack(Stack&& moveStack) noexcept: _pimpl(moveStack._pimpl), _containerType(moveStack._containerType) {	
	moveStack._pimpl = nullptr;
}

Stack& Stack::operator=(Stack&& moveStack) noexcept {
	if (this == &moveStack) return *this;
	*this = Stack(moveStack);
	return *this;
}

Stack::~Stack() {
	delete _pimpl;
}	


void Stack::push(const ValueType& value) {
	_pimpl->push(value);
}

void Stack::pop() {
	_pimpl->pop();
}

const ValueType& Stack::top() const {
	return _pimpl->top();
}

bool Stack::isEmpty() const {
	return _pimpl->isEmpty();
}

size_t Stack::size() const {
	return _pimpl->size();
}
	
