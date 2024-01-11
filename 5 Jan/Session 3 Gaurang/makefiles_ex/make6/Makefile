# Example # 5
#
# Introducing conditions

CC = g++

LIBRARY_SHARED=0

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

LIBRARY = $(LIBDIR)/mylib.a
ifeq ($(LIBRARY_SHARED), 1)
	LIBRARY = $(LIBDIR)/mylib.so
endif

$(TRGT) : 
	$(CC) $(LIBRARY) -o $@ $(LIBFLAGS)

ifeq ($(LIBRARY_SHARED), 1)
MAKELIB : $(OBJS)
	g++ -shared $^ -o $(LIBRARY)
	@echo LIBRARY CREATED $(LIBRARY)
else
MAKELIB : $(OBJS)
	ar -rs $(LIBRARY) $^
	@echo LIBRARY CREATED $(LIBRARY)
endif

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CC) -c $< -o $@ $(INCFLAGS)

clean:
	rm -rf $(OBJS) $(TRGT)

distclean: clean
	rm -rf $(LIBRARY) 
