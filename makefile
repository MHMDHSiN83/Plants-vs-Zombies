CXX = g++ -g -std=c++20

FILES = build/main.o build/system.o build/peashooter.o build/card.o build/plant.o
EXE = program.out
LFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
clean: all
	rm -f $(FILES)

all: $(EXE)

$(EXE): $(FILES)
	$(CXX) $^ -o $@ $(LFLAGS)
build/main.o: src/main.cpp include/system.hpp 
	$(CXX) -c $< -o $@
build/system.o: src/system.cpp include/peashooter.hpp include/card.hpp 
	$(CXX) -c $< -o $@
build/peashooter.o: src/peashooter.cpp
	$(CXX) -c $< -o $@
build/card.o: src/card.cpp
	$(CXX) -c $< -o $@
build/plant.o: src/plant.cpp
	$(CXX) -c $< -o $@

.PHONY: all clean
