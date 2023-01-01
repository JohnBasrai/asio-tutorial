STD ?= c++11
all :: client server

LIB=-lboost_system -lboost_thread -lpthread

client: client.cpp
	g++ $(LIB) -O2 -std=$(STD) client.cpp -o client

INC=-I../../include

server: server.cpp
	g++ $(LIB) $(INC) -O2 -std=$(STD) server.cpp -o server

clean:
	rm -f client server
