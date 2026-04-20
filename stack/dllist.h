#pragma once
#include <iostream>

using ValueType = double;

class DLList {
	struct Node {
		ValueType val;
		Node* prev = nullptr;
		Node* next = nullptr;
	};
	Node* head = nullptr;
	Node* end = nullptr;
	
	public:
		DLList();
		DLList(const DLList& other);
		DLList& operator=(const DLList& other);
		DLList(DLList&& other);
		DLList& operator=(DLList&& other);
		~DLList();

		ValueType& operator[](int k);
		const ValueType& operator[](int k) const;
		DLList& operator+(DLList& L);

		void push_front(ValueType newval);
		void push_back(ValueType newval);
		void pop_front();
		void pop_back();
		void insert(ValueType newval, int k);
		Node& front();
		Node& back();
		int size() const;
		bool empty() const;
		void display() const;
		void erase(double val);
		void clear();

		friend std::ostream& operator<<(std::ostream& out, const DLList& L);
};

std::ostream& operator<<(std::ostream& out, const DLList& L);
