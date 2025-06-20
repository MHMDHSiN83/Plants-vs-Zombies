#pragma once

#include "require.hpp"
#include "card.hpp"
#include "attackingPlant.hpp"
#include "sunflower.hpp"
#include "walnut.hpp"
#include "sunshine.hpp"
#include "scoreBox.hpp"
#include "zombie.hpp"
#include "bullet.hpp"

class System {
public:
    System(vector<vector<double>> zombies_data, vector<vector<double>> plants_data, vector<double> attack_data, vector<double> sun_data);
    ~System();
    void run();
private:
    RenderWindow window;
    Status status;
    vector<Plant*> plants;
    vector<Sunshine*> sunshines;
    vector<Zombie*> zombies;
    vector<Bullet*> bullets;
    vector<Card*> cards;
    Texture background_texture;
    Sprite background_sprite;
    Texture pause_menu_texture;
    Sprite pause_menu_sprite;
    Music music;
    bool tiles_status[NUMBER_OF_TILE_HEIGHT][NUMBER_OF_TILE_WIDTH];
    bool should_zombie_create = true;
    int sun = 0;
    Clock sunshine_clock;
    Clock wave_clock;
    Clock game_clock;
    Clock sleep;
    ScoreBox* score_box;
    Clock zombie_clock;
    Vector2u screen_size;
    int cards_number;
    vector<double> regular_zombie;
    vector<double> hair_metal_gargantuar_zombie;
    vector<double> peashooter_data;
    vector<double> icepeashooter_data;
    vector<double> kernelPult_data;
    vector<double> sunflower_data;
    vector<double> walnut_data;
    vector<double> sunshine_data;
    double win_timer;
    double each_wave_time;
    double zombie_number_each_wave;
    double extra_zombie_each_wave;

    void update();
    void render();
    void handle_events();
    void play_music(string path, bool loop);
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
    int generate_random_number_between(int start, int end);
    void create_zombie();
    void update_zombies();
    void render_zombies();
    void build_animation_of_plants();
    void build_animation_of_zombie();
    int calculate_height_position(int tile);
    void update_bullets();
    void render_bullets();
    void set_information(vector<vector<double>> zombies_data, vector<vector<double>> plants_data, vector<double> attack_data, vector<double> sun_data);
    void handle_collision();
    void handle_zombie_bullet_collision();
    void handle_zombie_plant_collision();
    bool is_on_same_height(Bullet* bullet, Zombie* zombie);
    bool is_on_same_height(Plant* plant, Zombie* zombie);
    bool is_there_zombie_in_front(Plant* plant);
    void render_main_menu();
    void handle_mouse_pressed_main_menu(Vector2i mouse_position);
    void set_background(string path);
    void key_pressed(Event event);
    void render_pause_menu();
    void handle_mouse_pressed_pause_menu(Vector2i mouse_position);
    void update_wave();
    void has_player_won();
    void render_victory_screen();
    Card* find_card_by_type(int type);
    void restart_clocks();
    void create_cards(vector<vector<double>> plants_data);
    void set_pause_menu();
    void free_memory();
};