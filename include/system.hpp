#pragma once

#include "require.hpp"
#include "card.hpp"
#include "peashooter.hpp"
#include "sunflower.hpp"
#include "walnut.hpp"
#include "sunshine.hpp"
#include "scoreBox.hpp"
#include "icePeashooter.hpp"
#include "zombie.hpp"


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
    vector<Plant*> plants;
    vector<Sunshine*> sunshines;
    vector<Zombie*> zombies;
    Card* cards[PLANTS_NUMBER];
    Texture background_texture;
    Sprite background_sprite;
    // pair<pair<float, float>, pair<float, float>> planting_area;
    Music music;
    bool tiles_status[NUMBER_OF_TILE_HEIGHT][NUMBER_OF_TILE_WIDTH];
    void update();
    void render();
    void handle_events();
    void play_music();
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
    void create_plant(int i);
    int sun = 0;
    int sunshine_timer = SUNSHINE_TIMER;
    int generate_random_number_between(int start, int end);
    system_clock::time_point last_sunshine_time = system_clock::now();
    ScoreBox* score_box;
    void create_zombie();
    void update_zombies();
    void render_zombies();
    void build_animation_of_plants();
    void build_animation_of_zombie();
    system_clock::time_point last_zombie_time = system_clock::now();
    Vector2u screen_size;
    int calculate_height_position(int tile);
    
};