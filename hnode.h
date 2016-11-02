/************************************************************************
File: hnode.h
Author: Eseosa Asiruwa
Date: 4/25/16
Assignment: Lab 7 (Huffman Encoding)

Hnode declarations:
	1) Declaration with only letter and count 
	2) '' with letter, count and pointers
	3) '' with count and pointers

************************************************************************/

#include <iostream>
#include <fstream>

using namespace std;

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