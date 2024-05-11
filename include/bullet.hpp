#pragma once

#include "require.hpp"


class Bullet {
public:
    Bullet(Vector2f position, int type);
    ~Bullet();
    void update();
    void render(RenderWindow* Window);
    bool handle_mouse_pressed(Vector2i mouse_position);
    bool is_out(unsigned screen_height);
private:
    void set_texture(int type);
    Texture texture;
    Sprite sprite;
    IntRect rect;
    int speed = 5;
};