# CXX Make variable for compiler
CXX=g++
# Make variable for compiler options
#	-std=c++11  C/C++ variant to use, e.g. C++ 2011
#	-g          include information for symbolic debugger e.g. gdb 
CXXFLAGS=-std=c++11 -g

CXXTHREADS=-pthread

CFLAGS = -c -Wall -Iinclude


# Rules format:
# target : dependency1 dependency2 ... dependencyN
#     Command to make target, uses default rules if not specified

# First target is the one executed if you just type make
# make target specifies a specific target
# $^ is an example of a special variable.  It substitutes all dependencies
countwords : dicttree.o inserting.o searching.o threadargs.h arguments.o countwords.o
	$(CXX) $(CXXFLAGS) $(CXXTHREADS) $^ 
	
# -o countwords

dicttree.o : dicttree.h dicttree.cpp

inserting.o : inserting.h inserting.cpp

searching.o : searching.h searching.cpp

arguments.o : arguments.h arguments.cpp

countwords.o : dicttree.h countwords.cpp

clean :
	rm *.o

