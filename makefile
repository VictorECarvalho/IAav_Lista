# My first makefile


all: main 
 
 
main: src/lista1.cpp src/Search.cpp src/util.cpp
	g++ -o main src/lista1.cpp  src/Search.cpp  src/Estate.cpp src/util.cpp 

clean: 
	rm main 

run:./main
	./main -gbfs 0 6 1 7 4 2 3 8 5, 5 0 2 6 4 8 1 7 3, 2 4 7 0 3 6 8 1 5
