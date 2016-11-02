/************************************************************************
File: hdecode.cc
Author: Eseosa Asiruwa
Date: 4/25/16
Assignment: Lab 7 (Huffman Encoding)

This part of the program reads the overhead from the given .huf file.
Starting at the root of the tree, it reads 8 bits at a time, using each
bit to move from an internal node toward a leaf (0-left, 1-right). When
it reaches a leaf, if outputs a character. The program stops when the 
number of orginal characters have been output.

************************************************************************/
#include <iostream>
#include <fstream>
#include <ctype.h>
#include <string>

#include "heap.h"
#include "hnode.h"

using namespace std;

// Input checks
void check_args(int argc){ 
    if (argc != 2){ 
        cout << "Not enough arguements given. " 
        << "Program has terminated." << endl;
        exit(1);
    }
}

void check_infile(ifstream & in){
    if (!in.is_open()){
        cout << "Infile cannot be opened. " 
        << "Program has terminated." << endl;
        exit(1);
    }
}

/* Traverese through tree using the given path, either ofstreaming data or 
    moving through the tree while substracting from the path. */
string decodepath(hnode* tree, string path, ofstream & ostr)
{
    if (!tree -> left && !tree -> right){
        ostr << tree -> data;
        return path;
    }
    else if (path[0] == '0')
        return decodepath(tree -> left, path.substr(1, path.length()-1), ostr);
    else
        return decodepath(tree -> right, path.substr(1, path.length()-1), ostr);
}

// Read the overhead from the file and build a tree 
hnode* read_tree(ifstream & in)
{
    unsigned char which = in.get(); 
    if (which == 'L'){  // lead node
    	return new hnode(in.get(),0, NULL, NULL);
    }
    // build left and right subtrees
    hnode* left = read_tree(in); 
    hnode* right = read_tree(in);
    return new hnode(0,left, right);
}

// Convert the byte character to a bitstring 
string byte_to_bitstring(unsigned char byte)
{
    string bits; unsigned char power;
    for (power = 128; power > 0; power /= 2){
        if (byte >= power){
            byte -= power;
            bits += '1';
        }
        else
            bits += '0';
    }
    return bits;
}

int main(int argc, char **argv)
{  
    check_args(argc);
    string filename = argv[1];
    ifstream in(filename.c_str());
    check_infile(in);
    ofstream ostr(filename.substr(0,filename.size()-4).c_str()); // rm .huf

    // Store the orginal file length
    size_t filesize;
    in >> filesize;

    hnode* root = read_tree(in);

    // Get each char byte from file and convert to bitstring
    int byte;
    string path;
    while ((byte = in.get()) != EOF){
        path += byte_to_bitstring(byte);
    }

    int file_length = filesize;
    int path_length = path.size();

    // Decode the path until the original file length is reached
    while (file_length != 0){
        path = decodepath(root, path, ostr);
        path_length = path.length(); // reset path length
        file_length--;
    }
    remove(argv[1]);
}