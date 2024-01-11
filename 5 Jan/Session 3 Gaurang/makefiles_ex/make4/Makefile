# Example # 4
# 
# Sample makefile
# Introducing directory structure.

CC = g++

SRCDIR = src
OBJDIR = obj
BINDIR = bin

SRCS = main.cpp fun1.cpp fun2.cpp fun3.cpp
OBJS = $(SRCS:%.cpp=$(OBJDIR)/%.o)

TRGT = $(BINDIR)/exe

$(TRGT) : $(OBJS)
	$(CC) $^ -o $@

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CC) -c $< -Iinclude -o $@

clean:
	rm -rf $(OBJS) $(TRGT)
