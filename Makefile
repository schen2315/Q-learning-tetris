all:	driver 
		./driver
driver:	algo.o driver.o
		g++ algo.o driver.o -o driver
driver.o:	driver.cpp
		g++ driver.cpp -c
algo.o:	algo.cpp
		g++ algo.cpp -c 
clean:
		rm -rf *.o algo