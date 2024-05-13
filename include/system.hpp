#pragma once

#include "require.hpp"
#include "card.hpp"
#include "attackingPlant.hpp"
#include "peashooter.hpp"
#include "sunflower.hpp"
#include "walnut.hpp"
#include "sunshine.hpp"
#include "scoreBox.hpp"
#include "icePeashooter.hpp"
#include "zombie.hpp"
#include "bullet.hpp"


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
    System(vector<double> zombies_data, vector<double> plant_data, vector<double> attack_data, vector<double> sun_data);
    ~System();
    void run();
private:
    RenderWindow window;
    Status status;
    vector<Plant*> plants;
    vector<Sunshine*> sunshines;
    vector<Zombie*> zombies;
    vector<Bullet*> bullets;
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
    Clock sunshine_clock;
    int sunshine_timer = SUNSHINE_TIMER;
    int generate_random_number_between(int start, int end);
    ScoreBox* score_box;
    void create_zombie();
    void update_zombies();
    void render_zombies();
    void build_animation_of_plants();
    void build_animation_of_zombie();
    Clock zombie_clock;
    Clock zombie_hit_clock;
    Vector2u screen_size;
    int calculate_height_position(int tile);
    void update_bullets();
    void render_bullets();
    /////////////////
    void set_information(vector<double> zombies_data, vector<double> plant_data, vector<double> attack_data, vector<double> sun_data);
    vector<double> regular_zombie;
    // hairMetalGargantuar zombie
    vector<double> peashooter_data;
    vector<double> icepeashooter_data;
    vector<double> kernelPult_data;
    vector<double> sun_flower_data;
    vector<double> walnut_data;
    /////////////////////
    vector<double> zombies_attacking_data;
    /////////////////////
    vector<double> sunshine_data;
    void handle_collision();
    void handle_zombie_bullet_collision();
    void handle_zombie_plant_collision();
    bool is_on_same_height(Bullet* bullet, Zombie* zombie);
    bool is_on_same_height(Plant* plant, Zombie* zombie);
    bool is_there_zombie_in_front(Plant* plant);
    void render_main_menu();
    void handle_mouse_pressed_main_menu(Vector2i mouse_position);
    void set_background(string path);
};