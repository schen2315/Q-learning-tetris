all:	driver 
		./driver
tester:	tetris.o tester.o
		g++ tetris.o tester.o -o tester
driver:	tetris.o algo_hashed.o driver.o
		g++ tetris.o algo_hashed.o driver.o -o driver
tester.o:	tester.cpp
		g++ tester.cpp -c
driver.o:	driver.cpp
		g++ driver.cpp -c
algo_hashed.o:	algo_hashed.cpp
		g++ algo_hashed.cpp -c
tetris.o:	tetris.cpp
		g++ tetris.cpp -c 
clean:
		rm -rf *.o driver tester