cflags := -std=gnu++0x -I. -I./src/lib -DUDPSERV -c
lflags := -std=gnu++0x
input := $(wildcard *.cpp)
objects := $(patsubst %.cpp, bin/%.o,$(wildcard *.cpp))
out := WarGames

all: $(objects)
	make -C packets/
	make -C lib/
	make -C test/
	g++ $(lflags) bin/*.o -o ../WarGames -lrt -lmysqlclient

bin/%.o : %.cpp 
	g++ $(cflags) -o $@ $<

clean : 
	rm bin/*
