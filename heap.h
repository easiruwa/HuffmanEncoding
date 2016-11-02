/************************************************************************
File: heap.h
Author: Eseosa Asiruwa
Date: 5/7/16
Assignment: Lab 7 (Huffman)

Implementation of minheap
************************************************************************/
#ifndef HEAP_H
#define HEAP_H

template <typename T>

class priqueue {
	public:
		priqueue(int (*C)(const T &, const T &));
		void add(const T &);
		T remove();
		size_t left_child(size_t k);
		size_t right_child(size_t k);
		size_t parent(size_t k);
		void swap(T & p1, T & p2);
		size_t size();

	private:
		std::size_t _size; // current number of elements in the heap
		T _data[500]; // space to store the heap
		int(*_compare)(const T &, const T &); // comparison function
		void _reheap_up(size_t);
		void _reheap_down(size_t);
};

#endif
#include "heap.cc"