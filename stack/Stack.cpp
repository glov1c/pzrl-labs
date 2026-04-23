#include <iostream>

#include "Stack.h"
#include "StackImplementation.h"

Stack::Stack(StackContainer container): _containerType(container) {
	if (container == StackContainer::Vector) _pimpl = new StackOnVector(); 
	else if (container == StackContainer::List) _pimpl = new StackOnList(); 
	else throw std::runtime_error("no such container type");
}


Stack::Stack(const ValueType* valueArray, const size_t arraySize, StackContainer container): _containerType(container) {
	if (container == StackContainer::Vector) _pimpl = new StackOnVector(); 
	else if (container == StackContainer::List) _pimpl = new StackOnList(); 
	else throw std::runtime_error("no such container type");

	for(size_t i = 0; i < arraySize; i++) {
		_pimpl->push(valueArray[i]);
	}
}

Stack::Stack(const IStackImplementation* impl, const size_t arraySize, StackContainer container) : _containerType(container){
	if (container == StackContainer::Vector) _pimpl = new StackOnVector(); 
	else if (container == StackContainer::List) _pimpl = new StackOnList(); 
	else throw std::runtime_error("no such container type");

	for(size_t i = 0; i < arraySize; i++) {
		_pimpl->push((*impl)[i]);
	}
}

Stack::Stack(const Stack& copyStack): _containerType(copyStack._containerType) {
	if (copyStack._pimpl == nullptr) return;
	if (copyStack._containerType == StackContainer::Vector) {
		*this = Stack(copyStack._pimpl, copyStack._pimpl->size(), StackContainer::Vector);
	}
	else if (copyStack._containerType == StackContainer::List) {
		*this = Stack(copyStack._pimpl, copyStack._pimpl->size(), StackContainer::List);
	}
}

Stack& Stack::operator=(const Stack& copyStack) {
	if (this == &copyStack) return *this;
	delete _pimpl;
	_pimpl = nullptr;
	*this = Stack(copyStack);
	return *this;
}

Stack::Stack(Stack&& moveStack) noexcept: _pimpl(moveStack._pimpl), _containerType(moveStack._containerType) {	
	moveStack._pimpl = nullptr;
}

Stack& Stack::operator=(Stack&& moveStack) noexcept {
	if (this == &moveStack) return *this;
	delete _pimpl;
	_pimpl = moveStack._pimpl;
	_containerType = moveStack._containerType;
	moveStack._pimpl = nullptr;
	return *this;
}

Stack::~Stack() {
	delete _pimpl;
}	


void Stack::push(const ValueType& value) {
	_pimpl->push(value);
}

void Stack::pop() {
	if (_pimpl == nullptr) throw std::runtime_error("empty stack");
	_pimpl->pop();
}

const ValueType& Stack::top() const {
	if (_pimpl == nullptr) throw std::runtime_error("empty stack");
	return _pimpl->top();
}

bool Stack::isEmpty() const {
	if (_pimpl == nullptr) return true; 
	return _pimpl->isEmpty();
}

size_t Stack::size() const {
	if (_pimpl == nullptr) return 0;
	return _pimpl->size();
}
	
