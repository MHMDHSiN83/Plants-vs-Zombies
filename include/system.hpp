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
    RenderWindow window;
private:
    Status status;
    Texture background_texture;
    Sprite background_sprite;
    void update();
    void render();
    void handle_events();
    void mouse_pressed(Event event);

};