all:	algo
		./algo
algo:	algo.o
		g++ algo.o -o algo
algo.o:	algo.cpp
		g++ algo.cpp -c 
clean:
		rm -rf *.o algo