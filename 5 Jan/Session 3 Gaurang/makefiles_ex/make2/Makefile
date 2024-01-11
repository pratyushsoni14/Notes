# Example # 2
#
# Splitting dependencies
#
# TARGET : DEPENDENCY...
# 	<COMMAND>
# 	...
#

Execute: main.o fun1.o
	g++ main.o fun1.o -o binary

main.o:
	g++ -c main.cpp -I./ -o main.o

fun1.o:
	g++ -c fun1.cpp -I./ -o fun1.o

clean:
	rm *.o binary
