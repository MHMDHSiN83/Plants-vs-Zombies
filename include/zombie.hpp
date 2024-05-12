#pragma once

#include "require.hpp"


class Zombie {
public:
    Zombie(Vector2f position, int _height);
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
    int get_damage();
    bool is_eating();
    int get_hit_rate();
    Time get_elapsed();
    void restart_clock();
private:
    Texture texture;
    vector<Texture> textures;
    Sprite sprite;
    IntRect rect;
    int number_of_idle_frames = 31;
    float speed = 0.5;
    int timer = 1;
    void store_textures();
    int height;
    int health;
    bool eating = false;
    int damage;
    int hit_rate;
    Clock hit_clock;
};