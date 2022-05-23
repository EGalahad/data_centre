SOURCES := $(wildcard src/*.cpp)
INCLUDES := $(wildcard src/*.h)
OBJ := $(patsubst src/%.cpp,bin/%.o, $(SOURCES))

CC_OPTIONS := -g -fsanitize=address

.PHONY: check diff

number := 3

check%:
	./main < ./data/input$(subst check,,$@) > ./data/output$(subst check,,$@)
	diff ./data/output$(subst check,,$@) ../me/data/output$(subst check,,$@) | grep '^[1-9]' > diff$(subst check,,$@).txt
	cat diff$(subst check,,$@).txt

all: main

bin/%.o: src/%.cpp
	g++ -c -o $@ $^ $(CC_OPTIONS)

main: $(SOURCES) $(INCLUDES) $(OBJ)
	g++ -o $@ $(OBJ) $(CC_OPTIONS)
