#include "HashTable.h"

#include <iostream>

size_t HashTable::hash_function(const KeyType& key) const {
	size_t res = 0;
	for(size_t i = 0; i < key.size(); i++) {
	       res = (res * 23 + key[i]);
	}
	return res % _capacity;
}	

HashTable::HashTable(size_t size) noexcept: table(size), _capacity(size), _filled(0) {}

HashTable::~HashTable() {}

double HashTable::getLoadFactor() {
	return static_cast<double>( _filled) / _capacity;
}

bool HashTable::find(const KeyType& key, ValueType& value) const {
        size_t hash = hash_function(key);
        for(auto it = table[hash].begin(); it != table[hash].end(); it++) {
                if (it->first == key) {
                       value = it->second;
                       return true;
                }
        }
        return false;
}

void HashTable::remove(const KeyType& key) {
        size_t hash = hash_function(key);
        for(auto it = table[hash].begin(); it != table[hash].end(); it++) {
                if (it->first == key) {
                        table[hash].erase(it);
                        if (table[hash].size() == 0) --_filled;
                        return;
                }
        }
}

void HashTable::insert(const KeyType& key, const ValueType& value) {
        auto& list = table[hash_function(key)];
        for(auto& elem: list) {
                if (elem.first == key) {
                        elem.second = value;
                        return;
                }
        }

        list.push_back({key, value});
        if (list.size() == 1)
                ++_filled;

        if (getLoadFactor() > 0.75) {
                HashTable newHash(table.size() * 2);
                for(size_t i = 0; i < table.size(); i++) {
                        for(auto it = table[i].begin(); it != table[i].end(); it++) {
                                newHash.insert(it->first, it->second);
                        }
                }
                *this = std::move(newHash);
        }
}

ValueType& HashTable::operator[](const KeyType& key) {
	size_t hash = hash_function(key);
	for(auto it = table[hash].begin(); it != table[hash].end(); it++) {
		if (it->first == key) {
			return it->second;
		}	
	}
	throw std::runtime_error("no such element");
}
