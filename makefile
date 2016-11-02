all: hencode hdecode

hencode: hencode.o 
	g++ -o hencode hencode.o 

hdecode: hdecode.o 
	g++ -o hdecode hdecode.o 
