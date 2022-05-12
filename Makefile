SOURCES := $(wildcard src/*.cpp)
INCLUDES := $(wildcard src/*.h)
OBJ := $(patsubst src/%.cpp,bin/%.o, $(SOURCES))

CC_OPTIONS := -g -fsanitize=address

.PHONY: check diff


check:
	./main < ./data/input2 > ./data/output2

diff:
	diff ./data/output2 ../me/data/output2 | grep '^[1-9]' > diff.txt
	cat diff.txt

all: main

bin/%.o: src/%.cpp
	g++ -c -o $@ $^ $(CC_OPTIONS)

main: $(SOURCES) $(INCLUDES) $(OBJ)
	g++ -o $@ $(OBJ) $(CC_OPTIONS)
