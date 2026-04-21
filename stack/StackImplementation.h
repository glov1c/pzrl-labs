#pragma once

#include "Vector.h"
#include "dllist.h"

using ValueType = double;

// интерфейс для конкретных реализаций контейнера для стека
class IStackImplementation {
public:
    // добавление в хвост
    virtual void push(const ValueType& value) = 0;
    // удаление с хвоста
    virtual void pop() = 0;
    // посмотреть элемент в хвосте
    virtual const ValueType& top() const = 0;
    // проверка на пустоту
    virtual bool isEmpty() const = 0;
    // размер 
    virtual size_t size() const = 0;
    // виртуальный деструктор
    virtual ValueType& operator[](int k) = 0;
    virtual const ValueType& operator[](int k) const = 0;

    virtual ~IStackImplementation() = default;
};


class StackOnVector: public IStackImplementation {
	Vector vec;

	public:
		void push(const ValueType& value) override;
		void pop() override;
		const ValueType& top() const override;
		bool isEmpty() const override;
		size_t size() const override;
		ValueType& operator[](int k) override;
    		const ValueType& operator[](int k) const override;
};

class StackOnList: public IStackImplementation {
	DLList list;

	public:
		void push(const ValueType& value) override;
		void pop() override;
		const ValueType& top() const override;
		bool isEmpty() const override;
		size_t size() const override;
		ValueType& operator[](int k) override;
    		const ValueType& operator[](int k) const override;
};
