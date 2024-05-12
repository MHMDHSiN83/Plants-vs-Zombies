#pragma once

#include "require.hpp"


class Bullet {
public:
    Bullet(Vector2f position, int type, int _width, int _height);
    ~Bullet();
    void update();
    void render(RenderWindow* Window);
    bool handle_mouse_pressed(Vector2i mouse_position);
    bool is_out(unsigned screen_height);
    FloatRect get_rect();
    int get_height();
    int get_damage();

private:
    void set_texture(int type);
    Texture texture;
    Sprite sprite;
    IntRect rect;
    int speed = 5;
    int width;
    int height;
    int damage;
};