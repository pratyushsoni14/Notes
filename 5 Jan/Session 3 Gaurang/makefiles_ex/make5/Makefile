# Example # 5
#
# Creating SHARED LIBRARIES

CC = g++

SRCDIR = src
OBJDIR = obj
BINDIR = bin
LIBDIR = lib

SRCS = main.cpp fun1.cpp fun2.cpp fun3.cpp
OBJS = $(SRCS:%.cpp=$(OBJDIR)/%.o)

INCFLAGS = -I./include \
	   -I/opt/TinyXML/include -fPIC

LIBFLAGS = -L/usr/lib/ -lpthread \
	   -L/opt/TinyXML/lib/ -lticppd

TRGT = $(BINDIR)/exe

LIBRARY = $(LIBDIR)/mylib.so

$(TRGT) : 
	$(CC) $(LIBRARY) -o $@ $(LIBFLAGS)

MAKELIB : $(OBJS)
	g++ -shared $^ -o $(LIBRARY)
	@echo LIBRARY CREATED $(LIBRARY)

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CC) -c $< -o $@ $(INCFLAGS)

clean:
	rm -rf $(OBJS) $(TRGT)

distclean: clean
	rm -rf $(LIBRARY)