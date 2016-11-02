/************************************************************************
File: priqueue.cc
Author: Eseosa Asiruwa
Date: 4/24/16
Assignment: Lab 7 (Huffman)

Implementation for priority queue

************************************************************************/

#include "priqueue.h"
#include <cstdlib>
#include <iostream>

using namespace std;

priqueue::priqueue()
{
    _front =  NULL;
    _size = 0;
}

priqueue::~priqueue()
{
    while(_size !=0)
        remove();
}

hnode * priqueue::remove()
{
    if(_front == NULL)
        return NULL;
    listnode * p = _front;
    _front = p -> next;     
    hnode * q = p -> data; 
    _size--;
    delete p;
    return q;
}

size_t priqueue::size()
{
    return _size;
}

void priqueue::add(hnode* item)
{
    helpadd(item, _front);
}

void priqueue::helpadd(hnode* item, listnode* & q)
{
    // add if queue is empty or if item count  <= current node's count 
    if (q == NULL or item -> count <= q -> data -> count){
        q = new listnode(item, q);
        _size++; 
    }
    else
        helpadd(item, q -> next);
}