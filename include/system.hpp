#pragma once

#include "require.hpp"
#include "plant.hpp"


enum Status {
    PLAYING,
    PAUSE_MENU,
    MAIN_MENU,
    VICTORY_SCREEN,
    GAMEOVER_SCREEN,
    EXIT,
};

class System {
public:
    System(int width, int height);
    ~System();
    void run();
private:
    RenderWindow window;
    Status status;
    Plant* plant;
    Texture background_texture;
    Sprite background_sprite;
    pair<pair<float, float>, pair<float, float>> planting_area;
    bool tiles_status[5][9];
    void update();
    void render();
    void handle_events();
    void mouse_pressed(Event event);

};