#pragma once

#include "require.hpp"


class Zombie {
public:
    Zombie(Vector2f position);
    ~Zombie();
    void update();
    void render(RenderWindow* Window);
    bool handle_mouse_pressed(Vector2i mouse_position);
    void build_animation();
private:
    Texture texture;
    vector<Texture> textures;
    Sprite sprite;
    IntRect rect;
    int number_of_idle_frames = 31;
    float speed = 0.5;
    int timer = 1;
    void store_textures();
};