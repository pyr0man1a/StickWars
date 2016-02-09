flags := -std=gnu++0x -I. -I./src/lib -DUDPSERV -c
input := $(wildcard *.cpp)
objects := $(patsubst %.cpp, ../bin/%.o,$(wildcard *.cpp))
out := WarGames

all: $(objects)

../bin/%.o : %.cpp
	g++ $(flags) -o $@ $<
