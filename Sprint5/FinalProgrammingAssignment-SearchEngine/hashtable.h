#ifndef HASHTABLE_H
#define HASHTABLE_H
#define MAX_CHAIN_SIZE 10
#include <vector>
#include <utility>
#include <iostream>
#include <fstream>
#include <map>
using namespace std;

template <class K, class V>
class Hashtable {
public:
    Hashtable();
    ~Hashtable();
    int& getSize();
    V* insert(const K&, const V&);
    void makeEmpty();
    bool isEmpty() const;
    bool contains(K,V);
    V* search(K,V);
    void print();
    void output(ofstream&);
private:
    void rehash();
    vector<pair<K,V>>* table;
    int size;
    int tableSize;
    hash<string> stringhash;
};

template <class K, class V>
void Hashtable<K,V>::rehash() {
    vector<pair<K,V>>* newTable = new vector<pair<K,V>>[tableSize * 2];
    for(int i = 0; i < tableSize; i++) {
        for(int j = 0; j < table[i].size(); j++) {
            int newHashValue = stringhash(table[i].at(j).first)%(tableSize * 2);
            newTable[newHashValue].push_back(table[i].at(j));
        }
    }
    delete[] table;
    table = newTable;
    tableSize = tableSize * 2;
}

template <class K, class V>
Hashtable<K,V>::Hashtable() {
    tableSize = 200;
    table = new vector<pair<K,V>>[tableSize];
    size = 0;
}

template <class K, class V>
Hashtable<K,V>::~Hashtable() {
}

template<class K, class V>
int& Hashtable<K,V>::getSize() {
    return size;
}

template <class K, class V>
V* Hashtable<K,V>::insert(const K& key, const V& value) {
    pair<K,V>* newNode = new pair<K,V>(key,value);
    int hashvalue = stringhash(key)%tableSize;
    table[hashvalue].push_back(*newNode);
    size++;
//    if(table[hashvalue].size() >= MAX_CHAIN_SIZE)
//        rehash();
    return &(newNode->second);
}

template <class K, class V>
void Hashtable<K,V>::makeEmpty() {
    for(int i = 0; i < tableSize; i++) {
        table[i].clear();
    }
}

template <class K, class V>
bool Hashtable<K,V>::isEmpty() const {
    for(int i = 0; i < tableSize; i++) {
        if(table[i].size() != 0)
            return false;
    }
    return true;
}

template <class K, class V>
bool Hashtable<K,V>::contains(K key, V value) {
    int hashvalue = stringhash(key)%tableSize;
    for(unsigned int i = 0; i < table[hashvalue].size(); i++) {
        if(table[hashvalue].at(i).second == value)
            return true;
    }
    return false;
}

template <class K, class V>
V* Hashtable<K,V>::search(K key, V value) {
    int hashvalue = stringhash(key)%tableSize;
    for(unsigned int i = 0; i < table[hashvalue].size(); i++) {
        if(table[hashvalue].at(i).second == value) {
            return &(table[hashvalue].at(i).second);
        }
    }
    return nullptr;
}

template <class K, class V>
void Hashtable<K,V>::print() {
    for(int i = 0; i < tableSize; i++) {
        for(unsigned int j = 0; j < table[i].size(); j++) {
            cout << table[i].at(j).second << endl;
        }
    }
}

template <class K, class V>
void Hashtable<K,V>::output(ofstream& outFS) {
    for(int i = 0; i < tableSize; i++) {
        for(unsigned int j = 0; j < table[i].size(); j++) {
            outFS << table[i].at(j).second << endl;
        }
    }
}

#endif // HASHTABLE_H
