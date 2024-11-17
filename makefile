# My first makefile


all: main 
 
 
main: src/lista1.cpp src/Search.cpp src/util.cpp src/State.cpp src/State.h src/Search.h src/util.h
	g++ -o main src/lista1.cpp  src/Search.cpp  src/State.cpp src/util.cpp 

clean: 
	rm main 

run:./main
	./main -bfs 0 6 1 7 4 2 3 8 5, 5 0 2 6 4 8 1 7 3, 2 4 7 0 3 6 8 1 5

bfs:./main
	./main -bfs 0 6 1 7 4 2 3 8 5, 5 0 2 6 4 8 1 7 3, 2 4 7 0 3 6 8 1 5
astar:./main
	./main -astar 0 6 1 7 4 2 3 8 5, 5 0 2 6 4 8 1 7 3, 2 4 7 0 3 6 8 1 5
idfs:./main
	./main -idfs 0 6 1 7 4 2 3 8 5, 5 0 2 6 4 8 1 7 3, 2 4 7 0 3 6 8 1 5
idastar:./main
	./main -idastar 0 6 1 7 4 2 3 8 5, 5 0 2 6 4 8 1 7 3, 2 4 7 0 3 6 8 1 5
gbfs:./main
	./main -gbfs 0 6 1 7 4 2 3 8 5, 5 0 2 6 4 8 1 7 3, 2 4 7 0 3 6 8 1 5