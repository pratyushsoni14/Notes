all: ex1 ex2 ex3

ex1: clean
	g++ ex1.cpp -o ex1 -lpthread;

ex2: clean
	g++ ex2.cpp -o ex2 -lpthread

ex3: clean
	g++ ex3.cpp -o ex3 -lpthread

clean:
	rm -f ex1 ex2 ex3

run_all: all 
	./ex1 
	./ex2 
	./ex3