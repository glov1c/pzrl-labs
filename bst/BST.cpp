#include "BST.h"

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
	Node* elem = parent;
	if (elem) {
		if (elem->left) elem->left->output_node_tree();
		std::cout << elem->keyValuePair.first << " ";		
		if (elem->right) elem->right->output_node_tree();
	}
}

void BinarySearchTree::Node::insert(const Key& key, const Value& value) {
	if (parent == nullptr) *this = Node(key, value);
	else {
		Node* elem = parent;
		if (key > elem->keyValuePair.first) elem->right->insert(key, value);
		if (key < elem->keyValuePair.first) elem->left->insert(key, value);
		if (key == elem->keyValuePair.first) elem->keyValuePair.second = value;
	}
}


void BinarySearchTree::Node::erase(const Key& key) {
	if (parent == nullptr) return;	
	else {
		Node* elem = this;
		if (key > elem->keyValuePair.first) elem->right->erase(key);
		if (key < elem->keyValuePair.first) elem->left->erase(key);
		if (elem->left == nullptr && elem->right == nullptr) {
			delete elem;
			if (elem->parent->left == elem) parent->left = nullptr;
			if (elem->parent->right == elem) parent->right = nullptr;
		}
		if (elem->left != nullptr && elem->right == nullptr) {
			elem->keyValuePair = elem->left->keyValuePair;
			elem->left = elem->left->left;
			elem->right = elem->left->right;
			delete elem->left;
		}
		if (elem->left == nullptr && elem->right != nullptr) {
			elem->keyValuePair = elem->right->keyValuePair;
			elem->left = elem->right->left;
			elem->right = elem->right->right;
			delete elem->right;
		}
		if (elem->left != nullptr && elem->right != nullptr) {
			if (elem->right->left == nullptr) {
				elem->keyValuePair = elem->right->keyValuePair;
				elem->right = elem->right->right;
			}
			else {
				Node* lelem = elem;
				while (lelem->left != nullptr) {
					lelem = lelem->left;
				}
				elem->keyValuePair = lelem->keyValuePair;
				delete lelem;
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
}

void BinarySearchTree::Node::erase_all() {
	Node* node = this;
	if (!node) return;
	node->right->erase_all();
	node->left->erase_all();
	delete node;
}



BinarySearchTree::BinarySearchTree(const BinarySearchTree& other): _size(other._size) {
	if (other._root == nullptr) _root = nullptr;
	_root = new Node(*other._root);
}

BinarySearchTree& BinarySearchTree::operator=(const BinarySearchTree& other) {
	if (this == &other) return *this;
	_root->erase_all();
	*this = BinarySearchTree(other);
	return *this;
}
	
BinarySearchTree::BinarySearchTree(BinarySearchTree&& other) noexcept: _root(other._root), _size(other._size) {
	_size = 0;
	_root = nullptr;
}

BinarySearchTree& BinarySearchTree::operator=(BinarySearchTree&& other) noexcept {
	if (this == &other) return *this;
	*this = BinarySearchTree(other);
	return *this;
}

BinarySearchTree::~BinarySearchTree() {
	_root->erase_all();
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
	Node* elem = _node;
	if (elem->right != nullptr) {
		elem = elem->right;
		while (elem->left != nullptr) {
			elem = elem->left;
		}
		return Iterator(elem);
	}
	elem = elem->parent;
	while (elem->parent != nullptr && elem == elem->parent->right) {
		elem = elem->parent;
	}
	return Iterator(elem->parent);
}

BinarySearchTree::Iterator BinarySearchTree::Iterator::operator++(int) {
	BinarySearchTree::Iterator tmp = *this;
	++(*this);
	return tmp;
}


BinarySearchTree::Iterator BinarySearchTree::Iterator::operator--() {
	if (_node == nullptr) throw std::runtime_error("empty node");
	Node* elem = _node;
	if (elem->left != nullptr) {
		elem = elem->left;
		while (elem->right != nullptr) {
			elem = elem->right;
		}
		return Iterator(elem);
	}
	elem = elem->parent;
	while (elem->parent != nullptr && elem == elem->parent->left) {
		elem = elem->parent;
	}
	return Iterator(elem->parent);
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
	return &_node->keyValuePair;
}

BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator++() {
	if (_node == nullptr) throw std::runtime_error("empty node");
	const Node* elem = _node;
	if (elem->right != nullptr) {
		elem = elem->right;
		while (elem->left != nullptr) {
			elem = elem->left;
		}
		return ConstIterator(elem);
	}
	elem = elem->parent;
	while (elem->parent != nullptr && elem == elem->parent->right) {
		elem = elem->parent;
	}
	return ConstIterator(elem->parent);
}

BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator++(int) {
	BinarySearchTree::ConstIterator tmp = *this;
	++(*this);
	return tmp;
}


BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator--() {
	if (_node == nullptr) throw std::runtime_error("empty node");
	const Node* elem = _node;
	if (elem->left != nullptr) {
		elem = elem->left;
		while (elem->right != nullptr) {
			elem = elem->right;
		}
		return ConstIterator(elem);
	}
	elem = elem->parent;
	while (elem->parent != nullptr && elem == elem->parent->left) {
		elem = elem->parent;
	}
	return ConstIterator(elem->parent);
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
		_size++;
	}
	else {
		_root->insert(key, value);
		_size++;
	}
}

void BinarySearchTree::erase(const Key& key) {
	_root->erase(key);
	_size--;
}

BinarySearchTree::Iterator BinarySearchTree::find(const Key& key) {
	Node* elem = _root;
	while (elem != nullptr) {
		if (elem->keyValuePair.first < key) elem = elem->right;
		else if (elem->keyValuePair.first > key) elem = elem->left;
		else return Iterator(elem);
	}
	return Iterator(nullptr);
}

BinarySearchTree::ConstIterator BinarySearchTree::find(const Key& key) const {
	const Node* elem = _root;
	while (elem != nullptr) {
		if (elem->keyValuePair.first < key) elem = elem->right;
		else if (elem->keyValuePair.first > key) elem = elem->left;
		else return ConstIterator(elem);
	}
	return ConstIterator(nullptr);
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

void BinarySearchTree::output_tree() {
       if (_root != nullptr) _root->output_node_tree();
}       

std::pair<BinarySearchTree::Iterator, BinarySearchTree::Iterator> BinarySearchTree::equalRange(const Key &key) {
	auto first = find(key);
	if (first == Iterator(nullptr)) return {Iterator(nullptr), Iterator(nullptr)};

	auto last = first;
	while(last != end() && last->first == key) last++;
	return {first, last};
}

std::pair<BinarySearchTree::ConstIterator, BinarySearchTree::ConstIterator> BinarySearchTree::equalRange(const Key &key) const {
	ConstIterator first = find(key);
	if (first == ConstIterator(nullptr)) return {ConstIterator(nullptr), ConstIterator(nullptr)};
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
	return min;
}

BinarySearchTree::ConstIterator BinarySearchTree::max(const Key& key) const {
	auto p = equalRange(key);
	auto max = p.first;
	for(auto i = p.first; i != p.second; i++) {
		if (i->second > max->second) max = i;
	}
	return max;
}
