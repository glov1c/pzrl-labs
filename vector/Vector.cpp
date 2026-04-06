#include "Vector.h"

#include <iostream>

Vector::Vector(const ValueType* rawArray, const size_t size, float coef): _size(size), _capacity(size), _multiplicativeCoef(coef) {
	_data = new ValueType[_capacity];
	for(size_t i = 0; i < _size; i++) {
		_data[i] = rawArray[i];
	}
}

Vector::Vector(const Vector& other) {
	_size = other._size;
	_capacity = other._capacity;
	_multiplicativeCoef = other._multiplicativeCoef;
	_data = new ValueType[_capacity];
	for(int i = 0; i < _size; i++) {
		_data[i] = other._data[i];
	}
}

Vector& Vector::operator=(const Vector& other) {
	_size = other._size;
	_capacity = other._capacity;
	_multiplicativeCoef = other._multiplicativeCoef;
	_data = new ValueType[_capacity];
	for(int i = 0; i < _size; i++) {
		_data[i] = other._data[i];
	}
	delete[] other._data;
	return *this;
}

Vector::Vector(Vector&& other) noexcept {
	_data = other._data;
	_size = other._size;
	_capacity = other._capacity;
	_multiplicativeCoef = other._multiplicativeCoef;
	other._data = nullptr;
	other._size = 0;
	other._capacity = 0;
}

Vector& Vector::operator=(Vector&& other) noexcept {
	_data = other._data;
	_size = other._size;
	_capacity = other._capacity;
	_multiplicativeCoef = other._multiplicativeCoef;
	other._data = nullptr;
	other._size = 0;
	other._capacity = 0;
	return *this;
}

Vector::~Vector() {
	delete[] _data;
}

ValueType& Vector::operator[](size_t idx) {
	if (0 <= idx && idx < _size) return *(_data + idx);
	throw std::runtime_error("no such index");
}

const ValueType& Vector::operator[](size_t idx) const {
	if(0 <= idx && idx < _size)return *(_data + idx);
	throw std::runtime_error("no such index");
}

void Vector::pushBack(const ValueType& value) {
	if (_capacity == 0) {
		reserve(1);
	}
	if (_size + 1 > _capacity) {
		reserve(_capacity * _multiplicativeCoef);
	}
	_data[_size] = value;
	_size++;
}

void Vector::pushFront(const ValueType& value) {
	if (_capacity == 0) {
		reserve(1);
	}
	if (_size + 1 > _capacity) {
		reserve(_capacity * _multiplicativeCoef);
	}
	if (_size > 0) {
		for(size_t i = 0; i < _size + 1; i++) {
			_data[i+1] = _data[i];
		}
	}
	_data[0] = value;
	_size++;
}

void Vector::insert(const ValueType& value, size_t pos) {
	if (_size  > _capacity) {
		reserve(_capacity * _multiplicativeCoef);
	}

	for(size_t i = _size - 1; i > pos - 1; i--) {
		_data[i+1] = _data[i];
	}
	_data[pos] = value;
	_size++;
}

void Vector::insert(const ValueType* values, size_t size, size_t pos) {
	if (_size + size > _capacity * _multiplicativeCoef) {
		reserve(_size + size);
	}
	else if (_size + size > _capacity) {
		reserve(_capacity * _multiplicativeCoef);
	}

	for(size_t i = _size + size; i >= pos + size; i--) {
		_data[i] = _data[i - size];
	}
	for(size_t i = 0; i < size; i++) {
		_data[pos+i] = values[i];
	}
	_size += size;
}

void Vector::insert(const Vector& vector, size_t pos) {
	size_t size = vector._size;

	if (_size + size > _capacity * _multiplicativeCoef) {
		reserve(_size + size);
	}
	else if (_size + size > _capacity) {
		reserve(_capacity * _multiplicativeCoef);
	}

	for(size_t i = _size + size; i >= pos + size; i--) {
		_data[i] = _data[i - size];
	}
	for(size_t i = 0; i < size; i++) {
		_data[pos+i] = vector._data[i];
	}
	_size += size;
}

void Vector::popBack() {
	_size--;
}

void Vector::popFront() {
	for(size_t i = 0; i < _size; i++) {
		_data[i] = _data[i+1];
	}
	_size--;
}

void Vector::erase(size_t pos, size_t count) {
	if (pos < 0 && pos >= _size) throw std::runtime_error("can`t erase this elemenrs");
	if (pos == _size - 1) popBack();
	if (pos == 0) popFront();
	else {
		if (pos + count >= _size) {
			for(size_t i = pos; i < _size - pos; i++) {
				_data[i] = _data[i+count];
			}
			_size = pos + 1;
		}
		else {
			for(size_t i = pos; i < _size - pos; i++) {
				_data[i] = _data[i+count];
			}
			_size = _size - count;
		}
	}
}

void Vector::eraseBetween(size_t beginPos, size_t endPos) {
	if (beginPos < 0 || endPos > _size) throw std::runtime_error("wrong end or begin positions");
	for(size_t i = beginPos; i < _size; i++) {
		_data[i] = _data[i +endPos - beginPos];
	}
	_size -= (endPos - beginPos );	
}

long long Vector::find(const ValueType& value) const {
	for(long long i = 0; i < _size; i++) {
		if (_data[i] == value) {
			return i;
		}
	}
	throw std::runtime_error("no such element found");	
}


size_t Vector::size() const {
	return _size;
}

size_t Vector::capacity() const {
	return _capacity;
}

double Vector::loadFactor() const {
	return 1.0 * _size/_capacity;
}


void Vector::reserve(size_t capacity) {
	if (capacity >  _capacity) {
		ValueType* newdata = new ValueType[capacity];
		if (_size > 0) {
			for(int i = 0; i < _size; i++) {
				newdata[i] = _data[i];
			}
		}
		delete[] _data;
		_data = newdata;
		_capacity = capacity;
	}
}

void Vector::shrinkToFit() {
	ValueType* newdata = new ValueType[_size];
	for(int i = 0; i < _size; i++) {
		newdata[i] = _data[i];
	}
	delete[] _data;
	_data = newdata;
	_capacity = _size;
}

Vector::Iterator Vector::begin() {
	return Iterator(_data);
}

Vector::Iterator Vector::end() {
	return Iterator(_data + _size);
}

Vector::Iterator::Iterator(ValueType* ptr): _ptr(ptr) {}

ValueType& Vector::Iterator::operator*() {
	if (_ptr != nullptr) return *_ptr;
	throw std::runtime_error("nullptr object");
}	

const ValueType& Vector::Iterator::operator*() const {
	if (_ptr != nullptr) return *_ptr;
	throw std::runtime_error("nullptr object");
}	

ValueType* Vector::Iterator::operator->() {
	return _ptr;
}
const ValueType* Vector::Iterator::operator->() const {
	return _ptr;
}

Vector::Iterator Vector::Iterator::operator++() {
	_ptr++;
	return *this;
}

Vector::Iterator Vector::Iterator::operator++(int) {
	Iterator old = *this;
	operator++();
	return old;
}

bool Vector::Iterator::operator==(const Iterator& other) const { 
	if (_ptr == other._ptr) return true;
	else return false;
}

bool Vector::Iterator::operator!=(const Iterator& other) const {
	return !(*this == other);
}
