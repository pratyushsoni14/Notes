# Example # 3
#
# Splitting dependencies
#
# TARGET : DEPENDENCY...
# 	<COMMAND>
# 	...
#
# Introducing variable, automatic variable and subtitution
#
# VARIABLE = VALUES
#
# Automatic Variables
# 1. $@ : The name of the target of the rule. 
# 2. $< : The name of the first prerequisite(dependency)
# 3. $^ : The names of all the prerequisites, with spaces between them.

SRCS = main.cpp fun1.cpp

OBJS = main.o fun1.o

Execute: $(OBJS)
	g++ $(OBJS) -o binary

# substitute .o with .cpp
./%.o: ./%.cpp
	g++ -c $< -I./ -o $@
clean:
	rm *.o binary
