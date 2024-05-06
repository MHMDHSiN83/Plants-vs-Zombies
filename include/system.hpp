#pragma once

#include "require.hpp"
#include "plant.hpp"
#include "card.hpp"

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
    Card* cards[PLANTS_NUMBER];
    Texture background_texture;
    Sprite background_sprite;
    pair<pair<float, float>, pair<float, float>> planting_area;
    bool tiles_status[NUMBER_OF_TILE_HEIGHT][NUMBER_OF_TILE_WIDTH];
    void update();
    void render();
    void handle_events();
    void mouse_pressed(Event event);
    void render_cards();
    void update_cards();
    void handle_mouse_pressed_cards(Vector2i mouse_position);

};