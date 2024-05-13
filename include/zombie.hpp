#pragma once

#include "require.hpp"


class Zombie {
public:
    Zombie(Vector2f position, vector<double> regular_zombie, vector<double> zombies_attacking_data, int _height);
    ~Zombie();
    void update();
    void render(RenderWindow* Window);
    bool handle_mouse_pressed(Vector2i mouse_position);
    void build_animation();
    FloatRect get_rect();
    int get_height();
    void decrease_health(int bullet_damage);
    bool is_dead();
    void change_eating_situation();
    double get_damage();
    bool is_eating();
    double get_hit_rate();
    Time get_elapsed();
    void restart_clock();
private:
    double damage;
    double health;
    double hit_rate;
    double speed;
    void set_data(vector<double> regular_zombie, vector<double> zombies_attacking_data, int _height);
    Texture texture;
    vector<Texture> textures;
    Sprite sprite;
    IntRect rect;
    int number_of_idle_frames = 31;
    int timer = 1;
    double time_to_finish;
    double new_mode;
    double number_of_zombie;
    double number_of_add_zombie;
    void store_textures();
    int height;
    bool eating = false;
    Clock hit_clock;
};