STD ?= c++11
all :: read-udp

LIB=-lboost_system -lboost_thread -lpthread

read-udp: read-udp.cpp
	g++ $(LIB) -O2 -std=$(STD) read-udp.cpp -o read-udp

clean:
	rm -f read-udp
