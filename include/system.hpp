#pragma once

#include "require.hpp"
#include "card.hpp"
#include "peashooter.hpp"
#include "sunflower.hpp"
#include "walnut.hpp"
#include "sunshine.hpp"
#include "icePeashooter.hpp"


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
    System();
    ~System();
    void run();
private:
    RenderWindow window;
    Status status;
    Plant* plant;
    vector<Plant*> plants;
    vector<Sunshine*> sunshines;
    Card* cards[PLANTS_NUMBER];
    Texture background_texture;
    Sprite background_sprite;
    pair<pair<float, float>, pair<float, float>> planting_area;
    Music music;
    bool tiles_status[NUMBER_OF_TILE_HEIGHT][NUMBER_OF_TILE_WIDTH];
    void update();
    void render();
    void handle_events();
    void mouse_pressed(Event event);
    void render_cards();
    void update_cards();
    void handle_mouse_pressed_cards(Vector2i mouse_position);
    void render_plants();
    void update_plants(Vector2i position);
    void handle_mouse_pressed_plants(Vector2i mouse_position);
    void build_animation();
    void update_sunshines();
    void render_sunshines();
    void handle_mouse_pressed_sunshines(Vector2i position);
    void create_sunshine();
    void creat_plant(int i);
    int sun = 0;
    int sunshine_timer = SUNSHINE_TIMER;

    system_clock::time_point last_sunshine_time = system_clock::now();
    
};