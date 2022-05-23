SOURCES := $(wildcard src/*.cpp)
INCLUDES := $(wildcard src/*.h)
OBJ := $(patsubst src/%.cpp,bin/%.o, $(SOURCES))

CC_OPTIONS := -g -fsanitize=address -Wall

.PHONY: check diff clean

number := 3

all: main

checkmy%: main
	./main < ./data.backup/input$(subst checkmy,,$@) > ./data.backup/output$(subst checkmy,,$@)
	diff ./data.backup/output$(subst checkmy,,$@) ../me/data/output$(subst checkmy,,$@) | grep '^[1-9]' > diff$(subst checkmy,,$@).txt
	cat diff$(subst checkmy,,$@).txt

check%: main
	./main < ./data/input$(subst check,,$@) > ./data/output$(subst check,,$@)
	diff ./data/output$(subst check,,$@) ../me/data/output$(subst check,,$@) | grep '^[1-9]' > diff$(subst check,,$@).txt
	cat diff$(subst check,,$@).txt

bin/%.o: src/%.cpp src/%.h src/common.h
	g++ -c -o $@ $< $(CC_OPTIONS)

bin/main.o: src/main.cpp
	g++ -c -o $@ $< $(CC_OPTIONS)

main: $(SOURCES) $(INCLUDES) $(OBJ)
	g++ -o $@ $(OBJ) $(CC_OPTIONS)

clean:
	rm -f bin/* main
