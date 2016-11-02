/******************************************************************************
File: hencode.cc
Author: Eseosa Asiruwa
Date: 4/24/16
Assignment: Lab 7 (Huffman Encoding)

This is a program for Huffman encoding, where files are compressed in order 
to save space on a device. The program builds a full binary tree whose
leaves represent the unique characters of the file and whose branches 
represent the bits of the code. The program then reopens the file to generate 
bits for each source character. Then, encodes the bits, by 8, into a character,
lastly writing those characters to a .huf file. If there are any leftover bits,
they are padded to a multiple of 8 bits, converted and then written to the file.

******************************************************************************/
#include <iostream>
#include <fstream>
#include "heap.h"
#include "hnode.h"

using namespace std;

/* negative when item 1 comes before item 2
     postiive when item 2 comes before iten 1
       0 when the same  */
int hnode_compare(hnode * const & p1, hnode * const & p2)
{
    return p1 -> count - p2 -> count;
}

priqueue<hnode*> priq(hnode_compare);

size_t COUNTS[256] = {0};  // Initializes all cells to 0
string CODES[256];    // Default strings are empty

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

// Traverse the tree and, depending on whether it is a leaf or
    // an internal node, print L or I and then the tree data
void outputtree(hnode* tree, ofstream & ostr)
{
    if (!tree -> left)
        ostr << 'L' << tree -> data;
    else {
        ostr << 'I';
        outputtree(tree -> left, ostr);
        outputtree(tree -> right, ostr);
    }
}

// Traverse tree, depending on branch add 0 (left) or 1 (right) to 
    // the char data index in CODES 
void addCodes(hnode* tree, string bits)
{
    if (!tree -> right and !tree -> left){
        CODES[tree -> data] = bits;
    }
    else {
        if (tree -> left)
            addCodes(tree -> left, bits+'0');
        if (tree -> right)
            addCodes(tree -> right, bits+'1');
    }
}

// convert bits to bytes
unsigned char bits_to_byte(string bits)
{
    unsigned char result = 0;
    for (size_t i = 0; i < 8; i++)
        result = result * 2 + bits[i] - '0'; 
    return result;
}

// Get length of the characters in the file
size_t length(size_t COUNTS[])
{
    size_t length = 0;
    for (int i = 0; i < 256; i++){
        if (COUNTS[i])
            length += COUNTS[i];
    }
    return length;
}

// Pad string with '0' until it, evenly, divides by 8
void padding(string & bits)
{
  while (bits.length() % 8 != 0)
    bits += '0';
}

// Encode the 8 piece subparts of the string of codes 
void encode(string codes, ofstream & ostr)
{
    if (codes.length() == 0)
        return;
    else
        ostr << bits_to_byte(codes.substr(0,8));
    encode(codes.erase(0,8), ostr);
}

// Add character distribution to heap
void add_charhnodes()
{
    for (size_t i=0;i<256;i++)
        if (COUNTS[i]) {
            hnode* item = new hnode(i, COUNTS[i]);
            priq.add(item); 
        }
}

// Continuously take out two hnodes from the heap, combining them and then 
//  putting the resulting node back into the heap
void make_tree()
{
    while (priq.size() != 1){
        hnode* left = priq.remove();
        hnode* right = priq.remove();
        priq.add(new hnode(0, left -> count + right -> count, left, right));
    }
}

int main(int argc, char **argv)
{   
    check_args(argc);
    string filename = argv[1];
    ifstream in(filename.c_str());
    check_infile(in);
    ofstream ostr((filename + ".huf").c_str()); // convert file format

    // Get characters from file and add them to COUNTS
    int letter;
    while ((letter = in.get()) != EOF) {
        COUNTS[letter]++;
    }
    add_charhnodes();
    make_tree();

    hnode* htree = priq.remove(); // Root of the tree
    string bits = "";
    addCodes(htree, bits); // Place corresponding codes into array
    ostr << length(COUNTS);
    outputtree(htree, ostr);
    bits = "";

    // Read orginal file again and generate bits for each source character
    ifstream in2(filename.c_str());
    check_infile(in2);
    while ((letter = in2.get()) != EOF){
        bits += CODES[letter];
    }
    padding(bits);
    encode(bits, ostr);
    remove(argv[1]);
}