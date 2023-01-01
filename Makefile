
DIRS := \
 daytime-iostreams \
 daytime-tcp \
 daytime-udp \
 dummy-work \
 read-udp \
 signals \
 timers


export STD=c++14

all clean :
	for dir in $(DIRS); do \
	    $(MAKE) -C $$dir $(MAKECMDGOALS); \
	done

