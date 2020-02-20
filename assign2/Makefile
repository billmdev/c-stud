CXXFLAGS=-Wall -g
  
all: rsshell

tcp-utils.o: triv_client/tcp-utils.h triv_client/tcp-utils.cc
        $(CXX) $(CXXFLAGS) -c -o tcp-utils.o triv_client/tcp-utils.cc

tokenize.o: tokenize.h tokenize.cc
        $(CXX) $(CXXFLAGS) -c -o tokenize.o tokenize.cc

rsshell.o: triv_client/tcp-utils.h rsshell.cc tokenize.h
        $(CXX) $(CXXFLAGS) -c -o rsshell.o rsshell.cc

rsshell: rsshell.o tcp-utils.o tokenize.o
        $(CXX) $(CXXFLAGS) -o rsshell rsshell.o tcp-utils.o tokenize.o

clean:
        rm -f rsshell *~ *.o *.bak core \#*

