#ifndef HASHTABLE_H
#define HASHTABLE_H
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
    vector<vector<pair<K,V>>> table;
    int size;
    int tableSize;
    hash<string> stringhash;
};

template <class K, class V>
Hashtable<K,V>::Hashtable() {
    tableSize = 5000;
    table.reserve(tableSize);
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
    pair<K,V> newNode = make_pair(key,value);
    int hashvalue = stringhash(key)%tableSize;
    table[hashvalue].push_back(newNode);
    return &(newNode.second);
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
    for(int i = 0; i < table[hashvalue].size(); i++) {
        if(table[hashvalue].at(i).second == value)
            return true;
    }
    return false;
}

template <class K, class V>
V* Hashtable<K,V>::search(K key, V value) {
    int hashvalue = stringhash(key)%tableSize;
    for(int i = 0; i < table[hashvalue].size(); i++) {
        if(table[hashvalue].at(i).second == value) {
            return &(table[hashvalue].at(i).second);
        }
    }
}

template <class K, class V>
void Hashtable<K,V>::print() {
    for(int i = 0; i < tableSize; i++) {
        for(int j = 0; j < table[i].size(); j++) {
            cout << table[i].at(j).second.getWordText() << " ";
            for(auto iter = table[i].at(j).second.getMap().begin(); iter != table[i].at(j).second.getMap().end(); iter++) {
                cout << iter->first << " " << iter->second << " ";
            }
        }
    }
}

template <class K, class V>
void Hashtable<K,V>::output(ofstream& outFS) {
    for(int i = 0; i < tableSize; i++) {
        for(int j = 0; j < table[i].size(); j++) {
            outFS << table[i].at(j).second.getWordText() << " ";
            for(auto iter = table[i].at(j).second.getMap().begin(); iter != table[i].at(j).second.getMap().end(); iter++) {
                outFS << iter->first << " " << iter->second << " ";
            }
        }
    }
}

#endif // HASHTABLE_H
