#include "BST.h"
#include <limits>

#include <iostream>

BinarySearchTree::Node::Node(Key key, Value value, Node *parent, Node *left, Node *right): keyValuePair({key, value}), parent(parent), left(left), right(right) {}

BinarySearchTree::Node::Node(const Node& other): keyValuePair(other.keyValuePair), parent(nullptr), left(nullptr), right(nullptr) {
	if (left != nullptr) {
		left = new Node(*other.left);
		left->parent = this;
	}
	if (right != nullptr) {
		right = new Node(*other.right);
		right->parent = this;
	}
}

bool BinarySearchTree::Node::operator==(const Node& other) const {
	if (keyValuePair.first == other.keyValuePair.first && keyValuePair.second == other.keyValuePair.second) return true;
	return false;
}

void BinarySearchTree::Node::output_node_tree() const {
	const Node* elem = this;
	if (elem) {
		if (elem->left) elem->left->output_node_tree();
		std::cout << elem->keyValuePair.first << " " << elem->keyValuePair.second << std::endl;;		
		if (elem->right) elem->right->output_node_tree();
	}
}

void BinarySearchTree::Node::insert(const Key& key, const Value& value) {
		Node* elem = parent;
		if (key > keyValuePair.first) {
			if (right != nullptr) {
				right->insert(key, value);
				return;
			}
			right = new Node(key, value, this);
		}
		else if (key <= keyValuePair.first) {
			if (left != nullptr) {
				left->insert(key, value);
				return;
			}
			left = new Node(key, value, this);
		}
		//else if (key == keyValuePair.first) keyValuePair.second = value;
}


void BinarySearchTree::Node::erase(const Key& key) {
		Node* elem = this;
		if (elem == nullptr) return;
		else if (key > elem->keyValuePair.first) {
		    if (elem->right) elem->right->erase(key);
			return;
			//if (elem->right) elem->right->parent = elem;
		}
		else if (key < elem->keyValuePair.first) {
		    if (elem->left) elem->left->erase(key);
			return;
			//if (elem->left) elem->left->parent = elem;
		}
		else if (key == elem->keyValuePair.first) {
			if (elem->left == nullptr && elem->right == nullptr) {
				if (elem->parent) {
					if (elem->parent->left == elem) parent->left = nullptr;
					else parent->right = nullptr;
				}

				delete elem;
				elem = nullptr;
				return;
			}
			if (elem->left != nullptr && elem->right == nullptr) {
				Node* tmp = elem->left;
				if (elem->parent) {
					if (elem->parent->left == elem) parent->left = tmp;
					else parent->right = tmp;
				}

				tmp->parent = elem->parent;

				delete elem;
				elem = nullptr;
				return;
			}
			if (elem->left == nullptr && elem->right != nullptr) {
				Node* tmp = elem->right;
				if (elem->parent) {
					if (elem->parent->left == elem) parent->left = tmp;
					else parent->right = tmp;
				}

				tmp->parent = elem->parent;

				delete elem;
				elem = nullptr;
				return;
			}
			if (elem->left != nullptr && elem->right != nullptr) {
				Node* lelem = elem->right;
				while (lelem->left != nullptr) {
					lelem = lelem->left;
				}
				elem->keyValuePair = lelem->keyValuePair;
				lelem->erase(lelem->keyValuePair.first);
				return;
			}	
		}
		/*
		if (key == elem->left->keyValuePair.first) {
			if (elem->left->left == nullptr && elem->left->right == nullptr) {
				delete elem->left;
				elem->left = nullptr;
			}
			if (elem->left->left != nullptr && elem->left->right == nullptr) {
				elem->left = elem->left->left;
				delete elem->left->left;
			}
			if (elem->left->left == nullptr && elem->left->right != nullptr) {
				elem->left = elem->left->right;
				delete elem->left->right;
			}
			if (elem->left->left != nullptr && elem->left->right != nullptr) {
				if (elem->left->right->left == nullptr) {
					elem->left->keyValuePair = elem->left->right->keyValuePair;
					elem->left->right = elem->left->right->right;
				}
				else {
					Node* lelem = elem->left;
					while (lelem->left != nullptr) {
						lelem = lelem->left;
					}
					elem->left->keyValuePair = lelem->keyValuePair;
					delete lelem;
				}
			}
		} */
}

void BinarySearchTree::erase_all(const Node* node) {
	if (node != nullptr) {
		if (node->right) erase_all(node->right);
		if (node->left) erase_all(node->left);
		delete node;
	}
	return;
}

BinarySearchTree::Node* BinarySearchTree::copy_all(const Node* other) {
	if (other == nullptr) return nullptr;
	Node* elem = new Node(*other);
	elem->left = copy_all(other->left);
	if (elem->left) {
		elem->left->parent = elem;
	}
	elem->right = copy_all(other->right);
    	if (elem->right) {
	       	elem->right->parent = elem;
	}
	return elem;
}

BinarySearchTree::BinarySearchTree(const BinarySearchTree& other): _size(other._size) {
	if (other._root == nullptr) _root = nullptr;
	_root = copy_all(other._root);
}

BinarySearchTree& BinarySearchTree::operator=(const BinarySearchTree& other) {
	if (this == &other) return *this;
	erase_all(_root);
	_root = copy_all(other._root);
	_size = other._size;
	return *this;
}
	
BinarySearchTree::BinarySearchTree(BinarySearchTree&& other) noexcept: _root(other._root), _size(other._size) {
	other._size = 0;
	other._root = nullptr;
}

BinarySearchTree& BinarySearchTree::operator=(BinarySearchTree&& other) noexcept {
	if (this == &other) return *this;
	//*this = BinarySearchTree(std::move(other));
	std::swap(_root, other._root);
	std::swap(_size, other._size);
	return *this;
}

BinarySearchTree::~BinarySearchTree() {
	erase_all(_root);
}

BinarySearchTree::Iterator::Iterator(BinarySearchTree::Node* node): _node(node) {}


std::pair<Key, Value>& BinarySearchTree::Iterator::operator*() {
	if (_node == nullptr) throw std::runtime_error("empty node");
	return _node->keyValuePair;
}


const std::pair<Key, Value>& BinarySearchTree::Iterator::operator*() const {
	if (_node == nullptr) throw std::runtime_error("empty node");
	return _node->keyValuePair;
}

std::pair<Key, Value>* BinarySearchTree::Iterator::operator->() {
	return &_node->keyValuePair;
}


const std::pair<Key, Value>* BinarySearchTree::Iterator::operator->() const {
	return &_node->keyValuePair;
}

BinarySearchTree::Iterator BinarySearchTree::Iterator::operator++() {
	if (_node == nullptr) throw std::runtime_error("empty node");
	if (_node->right != nullptr) {
		_node = _node->right;
		while (_node->left != nullptr) {
			_node = _node->left;
		}
		return *this;
	}
	
	while (_node->parent != nullptr) {
		if (_node == _node->parent->left) {
			_node = _node->parent;
			return *this;
		}
		_node = _node->parent;
	}
	return *this;
}

BinarySearchTree::Iterator BinarySearchTree::Iterator::operator++(int) {
	BinarySearchTree::Iterator tmp = *this;
	++(*this);
	return tmp;
}


BinarySearchTree::Iterator BinarySearchTree::Iterator::operator--() {
	if (_node == nullptr) throw std::runtime_error("empty node");
	if (_node->left != nullptr) {
		_node = _node->left;
		while (_node->right != nullptr) {
			_node = _node->right;
		}
		return *this;
	}
	
	while (_node->parent != nullptr) {
		if (_node == _node->parent->right) {
			_node = _node->parent;
			return *this;
		}
		_node = _node->parent;
	}
	throw std::runtime_error("begin()--");
}

BinarySearchTree::Iterator BinarySearchTree::Iterator::operator--(int) {
	BinarySearchTree::Iterator tmp = *this;
	--(*this);
	return tmp;
}

bool BinarySearchTree::Iterator::operator==(const Iterator& other) const {
	return _node == other._node;
}

bool BinarySearchTree::Iterator::operator!=(const Iterator& other) const {
	return !(*this == other);
}



BinarySearchTree::ConstIterator::ConstIterator(const BinarySearchTree::Node* node): _node(node) {}


const std::pair<Key, Value>& BinarySearchTree::ConstIterator::operator*() const {
	if (_node == nullptr) throw std::runtime_error("empty node");
	return _node->keyValuePair;
}



const std::pair<Key, Value>* BinarySearchTree::ConstIterator::operator->() const {
	if (_node == nullptr) throw std::runtime_error("empty node");
	return &_node->keyValuePair;
}

BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator++() {
	if (_node == nullptr) throw std::runtime_error("empty node");
	if (_node->right != nullptr) {
		_node = _node->right;
		while (_node->left != nullptr) {
			_node = _node->left;
		}
		return *this;
	}
	
	while (_node->parent != nullptr) {
		if (_node == _node->parent->left) {
			_node = _node->parent;
			return *this;
		}
		_node = _node->parent;
	}
	return *this;
}

BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator++(int) {
	BinarySearchTree::ConstIterator tmp = *this;
	++(*this);
	return tmp;
}


BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator--() {
	if (_node == nullptr) throw std::runtime_error("empty node");
	if (_node->left != nullptr) {
		_node = _node->left;
		while (_node->right != nullptr) {
			_node = _node->right;
		}
		return *this;
	}
	
	while (_node->parent != nullptr) {
		if (_node == _node->parent->right) {
			_node = _node->parent;
			return *this;
		}
		_node = _node->parent;
	}
	return *this;
}

BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator--(int) {
	BinarySearchTree::ConstIterator tmp = *this;
	--(*this);
	return tmp;
}

bool BinarySearchTree::ConstIterator::operator==(const ConstIterator& other) const {
	return _node == other._node;
}

bool BinarySearchTree::ConstIterator::operator!=(const ConstIterator& other) const {
	return !(*this == other);
}

void BinarySearchTree::insert(const Key& key, const Value& value) {
	if (_root == nullptr) {
		_root = new BinarySearchTree::Node(key, value);
		_root->right = new Node(std::numeric_limits<Key>::max(), value, _root);
		_size++;
	}
	else {
		_root->insert(key, value);
		_size++;
	}
}

void BinarySearchTree::erase(const Key& key) {
	if (_root == nullptr) return;
	Iterator it(_root);
	it = find(key);
	while(it != end()) {
		it._node->erase(key);
		_size--;
		it = find(key);
	}
}

BinarySearchTree::Iterator BinarySearchTree::find(const Key& key) {
	auto elem = begin();
	while (elem != end() && elem->first != key) {
		++elem;
	}
	return elem;
}

BinarySearchTree::ConstIterator BinarySearchTree::find(const Key& key) const {
	auto elem = cbegin();
	while (elem != cend() && elem->first != key) {
		++elem;
	}
	return elem;
}

BinarySearchTree::Iterator BinarySearchTree::begin() {
	Node* elem = _root;
	while (elem->left != nullptr) elem = elem->left;
	return Iterator(elem);
}

BinarySearchTree::ConstIterator BinarySearchTree::cbegin() const{
	Node* elem = _root;
	while (elem->left != nullptr) elem = elem->left;
	return ConstIterator(elem);
}
	       

BinarySearchTree::Iterator BinarySearchTree::end() {
	Node* elem = _root;
	while (elem->right != nullptr) elem = elem->right;
	return Iterator(elem);
}

BinarySearchTree::ConstIterator BinarySearchTree::cend() const{
	Node* elem = _root;
	while (elem->right != nullptr) elem = elem->right;
	return ConstIterator(elem);
}

size_t BinarySearchTree::size() const {
	return _size;
}

void BinarySearchTree::output_tree() const {
       if (_root != nullptr) _root->output_node_tree();
}       

std::pair<BinarySearchTree::Iterator, BinarySearchTree::Iterator> BinarySearchTree::equalRange(const Key &key) {
	auto first = find(key);
	if (first == end()) return {end(), end()};

	auto last = first;
	while(last != end() && last->first == key) ++last;
	return {first, last};
}

std::pair<BinarySearchTree::ConstIterator, BinarySearchTree::ConstIterator> BinarySearchTree::equalRange(const Key &key) const {
	ConstIterator first = find(key);
	if (first == cend()) return {cend(), cend()};
	auto last = first;
	while(last != cend() && last->first == key) last++;
	return {first, last};
}
BinarySearchTree::ConstIterator BinarySearchTree::min() const {
	return cbegin();
}

BinarySearchTree::ConstIterator BinarySearchTree::max() const {
	return --cend();
}

BinarySearchTree::ConstIterator BinarySearchTree::min(const Key& key) const {
	auto p = equalRange(key);
	auto min = p.first;
	for(auto i = p.first; i != p.second; i++) {
		if (i->second < min->second) min = i;
	}
	//_root->output_node_tree();
	std::cout << min->first << " " << min->second << std::endl;
	return min;
}

BinarySearchTree::ConstIterator BinarySearchTree::max(const Key& key) const {
	auto p = equalRange(key);
	auto max = p.first;
	for(auto i = p.first; i != p.second; i++) {
		if (i->second > max->second) max = i;
	}
	std::cout << max->first << " " << max->second << std::endl;
	return max;
}
