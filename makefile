CXX = g++ -g -std=c++20

FILES = build/main.o build/system.o build/plant.o
EXE = program.out
LFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
all: $(EXE)

$(EXE): $(FILES)
	$(CXX) $^ -o $@ $(LFLAGS)
build/main.o: src/main.cpp include/system.hpp 
	$(CXX) -c $< -o $@
build/system.o: src/system.cpp include/plant.hpp
	$(CXX) -c $< -o $@
build/plant.o: src/plant.cpp
	$(CXX) -c $< -o $@

.PHONY: all clean

clean:
	rm -f $(FILES) $(EXE)