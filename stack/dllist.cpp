#include <iostream>
#include <cstdlib>

#include "dllist.h"

DLList::DLList() :
	head(nullptr), end(nullptr) 
{}

DLList::DLList(const DLList& other) {
	Node* elem = other.head;
	while (elem != nullptr) {
		this->push_back(elem->val);
		elem = elem->next;
	}
}

DLList& DLList::operator=(const DLList& other) {
	Node* elem = other.head;
	while (elem != nullptr) {
		this->push_back(elem->val);
		elem = elem->next;
	}
	return *this;
}

ValueType& DLList::operator[](int k) {
	if (k >= size()) throw std::runtime_error("invalid index");
	Node* elem = head;
	int pos = 0;
	while (pos != k) {
		elem = elem->next;
	}
	return elem->val;
}
	
const ValueType& DLList::operator[](int k) const {
	if (k >= size()) throw std::runtime_error("invalid index");
	Node* elem = head;
	int pos = 0;
	while (pos != k) {
		elem = elem->next;
	}
	return elem->val;
}

DLList::~DLList() {
	Node* elem = head;
	while (elem != nullptr) {
		Node* tmp = elem;	
		elem = elem->next;
		delete tmp;
	}
}

void DLList::push_front(ValueType newval) {
	Node* first = new Node;
	first->val = newval;
	first->prev = nullptr;
	first->next = head;
	if (empty() == true) {
		end = first;
	}
	else if (first->next != nullptr){
		first->next->prev = first;
	}
	head = first;
}


void DLList::push_back(ValueType newval) {
	Node* last = new Node;
	last->val = newval;
	last->prev = end;
	last->next = nullptr;
	if (empty() == true) {
		head = last;
	}
	else if (last->prev != nullptr) {
		last->prev->next = last;
	}
	end = last;
}

void DLList::pop_front() {
	if (head != nullptr) { 
		if (head != nullptr) {
			Node* tmp = head;					
			head = head->next;
			head->prev = nullptr;
			delete tmp;
		}
		else {
			delete head;
			head = nullptr;
			end = nullptr;
		}
	}
}

void DLList::pop_back() {
	if (head != nullptr && end != nullptr) {
		Node* tmp = end;
		end = end->prev;
		end->next = nullptr;
		delete tmp;
	}
}

DLList::Node& DLList::front() {
	if (head != nullptr) return *head;
	throw std::runtime_error("empty list");
}

DLList::Node& DLList::back() {
	if (end != nullptr) return *end;
	throw std::runtime_error("empty list");
}

int DLList::size() const {
	int count = 0;
	Node* elem = head;
	while (elem != nullptr) {
		count++;
		elem = elem->next;
	}
	return count;
}

bool DLList::empty() const {
	if (head == nullptr && end == nullptr) return true;
	return false;
}

void DLList::display() const {
	Node* elem = head;
	while (elem != nullptr) {
		std::cout << elem->val << " ";
		elem = elem->next;
	}
	std::cout << std::endl;
}

void DLList::insert(double newval, int k) {
	if (k < 0 || k > size()) return;
	if (k == 0) {
	       	push_front(newval);
		return;
	}
	if (k == size()) {
	       	push_back(newval);
		return;
	}
	else {
		int i = 0;
		Node* elem = head;
		while (elem != nullptr) {
			if (i == k) {
				Node* tmp = new Node;
				tmp->val = newval;
				tmp->prev = elem->prev;
				elem->prev->next = tmp;
				tmp->next = elem;
				elem->prev = tmp;
				return;
			}
			else {
				elem = elem->next;
				i++;
			}
		}
	}
}

void DLList::erase(double val1) {
	if (head == nullptr && end == nullptr) return ;

	Node* elem = head->next;
	while (elem != nullptr) {
		if (elem->val == val1) {
			if (elem->next != nullptr) {
				Node* tmp = elem->prev;
				tmp->next = elem->next;
				elem->next->prev = tmp;
				delete elem;
				elem = tmp->next;	
			}
			else pop_back();
		}

		else {
			elem = elem->next;
		}
	}
	if (head->val == val1) {
		head = head->next;
	}
}

void DLList::clear() {
	Node* elem = head;
	while (elem != nullptr) {
		Node* tmp = elem;	
		elem = elem->next;
		delete tmp;
	}
	head = nullptr;
}
