#pragma once

#include "require.hpp"


class Zombie {
public:
    Zombie(Vector2f position);
    ~Zombie();
    void update();
    void render(RenderWindow* Window);
    bool handle_mouse_pressed(Vector2i mouse_position);
private:
    Texture texture;
    Sprite sprite;
    IntRect rect;
    int speed = 1;
};