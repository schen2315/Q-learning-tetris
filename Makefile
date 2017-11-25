all:	driver 
		./driver
driver:	algo_hashed.o driver.o
		g++ algo_hashed.o driver.o -o driver
driver.o:	driver.cpp
		g++ driver.cpp -c
algo_hashed.o:	algo_hashed.cpp
		g++ algo_hashed.cpp -c 
clean:
		rm -rf *.o driver