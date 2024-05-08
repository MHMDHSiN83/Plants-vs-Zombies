#pragma once

#include "require.hpp"


class Sunshine {
public:
    Sunshine();
    ~Sunshine();
    void update();
    void render(RenderWindow* Window);
    bool handle_mouse_pressed(Vector2i mouse_position);
private:
    Texture texture;
    Sprite sprite;
    IntRect rect;
    int speed = 1;
};