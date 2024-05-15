#pragma once

#include "require.hpp"


class Zombie {
public:
    Zombie(int _type, Vector2f position, vector<double> zombie_data, int _height);
    ~Zombie();
    void update();
    void render(RenderWindow* Window);
    bool handle_mouse_pressed(Vector2i mouse_position);
    void build_animation_of_normal_zombie();
    void build_animation_of_giant_zombie();
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
    bool is_out();
    void speed_effect(double speed_effect);
private:
    double damage;
    Vector2f position;
    double health;
    double hit_rate;
    double starting_speed;
    double current_speed;

    void set_data_of_normal_zombie(Vector2f position);
    void set_data_of_giant_zombie(Vector2f position);
    Texture texture;
    vector<Texture> textures;
    vector<Texture> textures2;
    Sprite sprite;
    IntRect rect;
    int timer_normal_zombie = 1;
    int timer_eating_normal_zombie = 1;
    int timer_giant_zombie = 1;
    int timer_eating_giant_zombie = 1;
    void store_textures_of_normal_zombie();
    void store_textures_of_giant_zombie();
    int height;
    bool eating = false;
    Clock hit_clock;
    Clock freeze_clock;
    int type;
    vector<Texture> textures_of_giant;
    vector<Texture> textures_of_eating_giant;

};