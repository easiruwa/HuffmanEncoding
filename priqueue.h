/************************************************************************
File: priqueue.h
Author: Eseosa Asiruwa
Date: 4/24/16
Assignment: Lab 7 (Huffman)

Declaration for priority queue class with hnode and listnode struct 
defintions
************************************************************************/

#include <cstdlib>

struct hnode {
    unsigned char data;
    size_t count;
    hnode *left, *right;
    hnode(int letter, size_t count) : data(letter), count(count),
                                      left(NULL), right(NULL) {} 

    hnode(int letter, size_t count, hnode * left, hnode * right) : 
    data(letter), count(count), left(left), right(right) {}

    hnode(size_t count, hnode * left, hnode * right) : 
    count(count), left(left), right(right) {}

};

struct listnode {
    hnode* data;
    listnode* next;
    listnode(hnode * data, listnode * next) : data(data), next(next) {}
};


class priqueue
{
 public:
  priqueue();

  ~priqueue();

  hnode* remove();

  void add(hnode* item);

  void helpadd(hnode* item, listnode* & q);

  size_t size();

 private:
  size_t _size;

  listnode* _front;
};