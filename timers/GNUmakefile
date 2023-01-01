STD ?= c++11
PROGS := bin/timer1 bin/timer2 bin/timer3 bin/timer4 bin/timer5
LIB=-lboost_system -lboost_thread -lpthread

all :: $(PROGS)

bin/timer1: timer1.cpp
	g++ $(LIB) $(INC) -O2 -std=$(STD) timer1.cpp -o bin/timer1

bin/timer2: timer2.cpp
	g++ $(LIB) $(INC) -O2 -std=$(STD) timer2.cpp -o bin/timer2

bin/timer3: timer3.cpp
	g++ $(LIB) $(INC) -O2 -std=$(STD) timer3.cpp -o bin/timer3

bin/timer4: timer4.cpp
	g++ $(LIB) $(INC) -O2 -std=$(STD) timer4.cpp -o bin/timer4

bin/timer5: timer5.cpp
	g++ $(LIB) $(INC) -O2 -std=$(STD) timer5.cpp -o bin/timer5

clean:
	rm -f $(PROGS)
