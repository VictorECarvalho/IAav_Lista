# My first makefile


all: main 
 
 
main: src/lista1.cpp src/Search.cpp src/util.cpp src/State.cpp src/State.h src/Search.h src/util.h
	g++ -O3 -o main src/lista1.cpp  src/Search.cpp  src/State.cpp src/util.cpp 

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
15astar:./main
	./main -astar 7 11 8 3 14 0 6 15 1 4 13 9 5 12 2 10, 12 9 0 6 8 3 5 14 2 4 11 7 10 1 15 13, 13 0 9 12 11 6 3 5 15 8 1 10 4 14 2 7
