STD ?= c++14
all :: client server-sync server-async

LIB=-lboost_system -lboost_thread -lpthread

client: client.cpp
	g++ $(LIB) -O2 -std=$(STD) client.cpp -o client

server-sync: server-sync.cpp
	g++ $(LIB) -O2 -std=$(STD) server-sync.cpp -o server-sync

INC=-I.

server-async: server-async.cpp
	g++ $(LIB) $(INC) -O2 -std=$(STD) server-async.cpp -o server-async

clean:
	rm -f client server-sync server-async
