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

const int MIN_WIDTH = 452;
const int MAX_WIDTH = 1790;
const int MIN_HEIGHT = 125;
const int MAX_HEIGHT = 960;
const int NUMBER_OF_TILE_WIDTH = 9;
const int NUMBER_OF_TILE_HEIGHT = 5;
const float TILE_WIDTH = (MAX_WIDTH - MIN_WIDTH) / NUMBER_OF_TILE_WIDTH;
const float TILE_HEIGHT = (MAX_HEIGHT - MIN_HEIGHT) / NUMBER_OF_TILE_HEIGHT;
const int PLANTS_NUMBER = 4;
const Vector2i FIRST_CARD_POSITION = {75,250};
const string INPUT_FILE_ADDRESS = "input.csv";
const int NUMBER_OF_IDLE_FRAMES_NORMAL_ZOMBIE = 31;
const int NUMBER_OF_EATING_FRAMES_NORMAL_ZOMBIE = 12;
const int NUMBER_OF_IDLE_FRAMES_GIANT_ZOMBIE = 58;
const int NUMBER_OF_EATING_FRAMES_GIANT_ZOMBIE = 29;
const int FREEZE_TIME = 5;

const string FONT_PATH = "assets/fonts/ARIAL.TTF";
const string IN_GAME_MUSIC_PATH = "assets/musics/ingame.ogg";
const string INTRO_MUSIC_PATH = "assets/musics/intro.ogg";
const string VICTORY_MUSIC_PATH = "assets/musics/victory.ogg";
const string PAUSE_MENU_PATH = "assets/images/backgrounds/pause_menu.png";
const string MAIN_MENU_PATH = "assets/images/backgrounds/main_menu.png";
const string VICTORY_SCREEN_PATH = "assets/images/backgrounds/victory_screen.png";
const string BACKGROUND_PATH = "assets/images/backgrounds/background.png";
const string GAMEOVER_BACKGROUND_PATH = "assets/images/backgrounds/game_over.png";
const string PEASHOOTER_PATH = "assets/images/plants/peashooter/";
const string ICEPEASHOOTER_PATH = "assets/images/plants/icepeashooter/";
const string PEA_BULLET_PATH = "assets/images/bullets/pea.png";
const string SNOW_PEA_BULLET_PATH = "assets/images/bullets/snow_pea.png";
const string ON_PEASHOOTER_CARD_PATH = "assets/images/cards/on_peashooter.png";
const string OFF_PEASHOOTER_CARD_PATH = "assets/images/cards/off_peashooter.png";
const string ON_ICEPEASHOOTER_CARD_PATH = "assets/images/cards/on_snow_peashooter.png";
const string OFF_ICEPEASHOOTER_CARD_PATH = "assets/images/cards/off_snow_peashooter.png";
const string ON_WALNUT_CARD_PATH = "assets/images/cards/on_walnut.png";
const string OFF_WALNUT_CARD_PATH = "assets/images/cards/off_walnut.png";
const string ON_SUNFLOWER_CARD_PATH = "assets/images/cards/on_sunflower.png";
const string OFF_SUNFLOWER_CARD_PATH = "assets/images/cards/off_sunflower.png";
const string SUNSHINE_PATH = "assets/images/sun.png";
const string SUNFLOWER_PATH = "assets/images/plants/sunflower/";
const string WALNUT_PATH = "assets/images/plants/walnut/";
const string REGULAR_WALKING_ZOMBIE_PATH = "assets/images/zombies/regular/walking/";
const string REGULAR_EATING_ZOMBIE_PATH = "assets/images/zombies/regular/eating/";
const string GIANT_WALKING_ZOMBIE_PATH = "assets/images/zombies/giant/walking/";
const string GIANT_EATING_ZOMBIE_PATH = "assets/images/zombies/giant/eating/";



const int DISTANCE_BETWEEN_SUN_AND_SUNWHINE = 60;
const int SUNSHINE_VALUE = 25;
enum PlantType {
    PEASHOOTER,
    SUNFLOWER,
    WALNUT,
    ICEPEASHOOTER,
};

enum Status {
    PLAYING,
    PAUSE_MENU,
    MAIN_MENU,
    VICTORY_SCREEN,
    GAMEOVER_SCREEN,
    EXIT,
};