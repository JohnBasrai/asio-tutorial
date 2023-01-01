STD ?= c++11
all :: signal

LIB=-lboost_system -lboost_thread -lpthread

signal: signal.cpp
	g++ $(LIB) -O2 -std=$(STD) signal.cpp -o signal

clean:
	rm -f signal
