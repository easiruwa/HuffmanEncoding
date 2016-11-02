/************************************************************************
File: heap.cc
Author: Eseosa Asiruwa
Date: 5/7/16
Assignment: Lab 7 (Huffman)

Implementation for min heap. A min heap is a binary tree such that
1) the data contained in each node is less than or equal to the data in
    that node's children
2) binary tree is complete

************************************************************************/

#include <cstdlib>
#include <iostream>

using namespace std;

// Constructor
template <typename T>
priqueue<T>::priqueue(int (*C)(const T &, const T &))
{
    _compare = C;
    _size = 0;
}

template <typename T>
size_t priqueue<T>::size()
{
    return _size;
}

// Using a temp pointer, move the first and second item pointers
template <typename T>
void priqueue<T>::swap(T & p1, T & p2)
{
    T temp = p1;
    p1 = p2;
    p2 = temp;
}

template <typename T>
size_t priqueue<T>::left_child(size_t k)
{
    return k * 2 + 1;
}

template <typename T>
size_t priqueue<T>::right_child(size_t k)
{
    return k * 2 + 2;
}

template <typename T>
size_t priqueue<T>::parent(size_t k)
{
    return (k-1) / 2;
}

// Add item to the last spot in array then reheap up
template <typename T>
void priqueue<T>::add(const T & item)
{
    _data[_size++] = item;
    _reheap_up(_size - 1);
}

// Get the item in the first position, reheap down, and return the item
//  Set the first position in array to the last element
template <typename T>
T priqueue<T>::remove()
{
    T result = _data[0];
    _data[0] = _data[--_size];
    _reheap_down(0);
    return result;
}

/* After a new element is placed in the next available position (done in ADD):
    -Compare the new element in the given postiion with its parent
    -If the new element is smaller, then swap with its parent
    - Continue swapping until the new element's parent is smaller than or 
        equal to the new element OR the new element reaches the root */
template <typename T>
void priqueue<T>::_reheap_up(size_t pos)
{   if (pos == 0)
        return;
    size_t par = parent(pos);
    if (_compare(_data[pos],_data[par]) >= 0)
        return;
    swap(_data[pos], _data[par]);
    _reheap_up(par);
}

/* After the root is removed and the last element is moved to that position
    (done in REMOVE):
    If the new element at the root has a value greater than at least one of
    its children, swap with the smaller-valued child */
template <typename T>
void priqueue<T>::_reheap_down(size_t pos)
{
    if (pos < _size){
        size_t child = left_child(pos);
        if (child < _size){
            size_t right = right_child(pos);
            if (right < _size && _compare(_data[right],_data[child]) < 0)
                child = right;
            if (_compare(_data[child], _data[pos]) < 0){
                swap(_data[pos], _data[child]);
                _reheap_down(child);
            }
        }
    }
}