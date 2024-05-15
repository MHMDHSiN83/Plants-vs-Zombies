#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <chrono>
#include <random>
#include <fstream>
#include <iomanip>




using namespace std;
using namespace sf;
using namespace chrono;

// const int MIN_WIDTH = 248; 1014
// const int MAX_WIDTH = 993;
// const int MIN_HEIGHT = 78; 600
// const int MAX_HEIGHT = 573;

// const int MIN_WIDTH = 452;
// const int MAX_WIDTH = 1811;
// const int MIN_HEIGHT = 132;
// const int MAX_HEIGHT = 970;

const int MIN_WIDTH = 452; // 452
const int MAX_WIDTH = 1790; // 1811
const int MIN_HEIGHT = 125; // 132
const int MAX_HEIGHT = 960; // 970

const int NUMBER_OF_TILE_WIDTH = 9;
const int NUMBER_OF_TILE_HEIGHT = 5;


const float TILE_WIDTH = (MAX_WIDTH - MIN_WIDTH) / NUMBER_OF_TILE_WIDTH;
const float TILE_HEIGHT = (MAX_HEIGHT - MIN_HEIGHT) / NUMBER_OF_TILE_HEIGHT;

const int PLANTS_NUMBER = 4;

const Vector2i FIRST_CARD_POSITION = {75,250};
const int SUNSHINE_TIMER = 1;

const string INPUT_FILE_ADDRESS = "input.csv";

const int NUMBER_OF_IDLE_FRAMES_NORMAL_ZOMBIE = 31;
const int NUMBER_OF_EATING_FRAMES_NORMAL_ZOMBIE = 12;
const int NUMBER_OF_IDLE_FRAMES_GIANT_ZOMBIE = 58;
const int NUMBER_OF_EATING_FRAMES_GIANT_ZOMBIE = 29;

const int FREEZE_TIME = 5;

enum Status {
    PLAYING,
    PAUSE_MENU,
    MAIN_MENU,
    VICTORY_SCREEN,
    GAMEOVER_SCREEN,
    EXIT,
};

