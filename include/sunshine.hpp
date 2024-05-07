#pragma once

#include "require.hpp"


class Sunshine {
public:
    Sunshine();
    ~Sunshine();
    void update();
    void render(RenderWindow* Window);
    // void handle_mouse_pressed();
private:
    Texture texture;
    Sprite sprite;
    IntRect rect;
    int speed = 1;
};