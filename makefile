CXX = g++ -g -std=c++20

FILES = build/main.o build/system.o build/card.o build/plant.o build/sunflower.o build/walnut.o build/sunshine.o build/scoreBox.o build/zombie.o build/attackingPlant.o build/bullet.o
EXE = pvz.out
LFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
# clean: all
# 	rm -f $(FILES)

all: $(EXE)

$(EXE): $(FILES)
	$(CXX) $^ -o $@ $(LFLAGS)
build/main.o: src/main.cpp include/system.hpp 
	$(CXX) -c $< -o $@
build/system.o: src/system.cpp include/card.hpp include/sunflower.hpp include/walnut.hpp include/sunshine.hpp include/scoreBox.hpp include/zombie.hpp include/attackingPlant.hpp include/bullet.hpp
	$(CXX) -c $< -o $@
build/plant.o: src/plant.cpp
	$(CXX) -c $< -o $@
build/card.o: src/card.cpp
	$(CXX) -c $< -o $@
build/sunflower.o: src/sunflower.cpp
	$(CXX) -c $< -o $@
build/walnut.o: src/walnut.cpp
	$(CXX) -c $< -o $@
build/sunshine.o: src/sunshine.cpp
	$(CXX) -c $< -o $@
build/scoreBox.o: src/scoreBox.cpp
	$(CXX) -c $< -o $@
build/zombie.o: src/zombie.cpp
	$(CXX) -c $< -o $@
build/attackingPlant.o: src/attackingPlant.cpp
	$(CXX) -c $< -o $@
build/bullet.o: src/bullet.cpp
	$(CXX) -c $< -o $@
.PHONY: all clean