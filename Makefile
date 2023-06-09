OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-uninitialized -Wno-sign-compare -std=c++11

#In a rule, the thing left tot he colon is the thing you wanna "make"
# the things at the right side of the colon are the requisites
# in the lines below the rule, u have what u gonna do to make the thing
program.exe : program.o Cpu.o Cluster.o Process.o Waiting_Area.o
	g++ -o program.exe $(OPCIONS) program.o Cpu.o Cluster.o Process.o Waiting_Area.o 

# This rule says: "for any x.o file you need the x.cc file
# $< means "the thing in the right side of the rule" i. e. the source file
# in this case (right to the colon)
%.o : %.cc
	g++ -c $(OPCIONS) $<

# This rule says the same with cpp, make will look for the first one that matches
%.o : %.cpp
	g++ -c $(OPCIONS) $< 

# The same with clean, but we'll delete the files.
clean :
	rm *.o *.exe
