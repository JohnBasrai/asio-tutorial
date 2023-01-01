STD ?= c++11
PROGS := dummy-work
LIB=-lboost_system -lboost_thread -lpthread

all :: $(PROGS)

dummy-work: dummy-work.cpp
	g++ $(LIB) $(INC) -O0 -g -std=$(STD) dummy-work.cpp -o dummy-work

clean:
	rm -f $(PROGS)
