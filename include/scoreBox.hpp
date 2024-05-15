#pragma once

#include "require.hpp"

class ScoreBox {
public:
    ScoreBox();
    // ~ScoreBox();
    void render(RenderWindow* window, int sun);
private:
    // void update();
    RectangleShape rectangle;
    Text text;
    Font font;
    Sprite sprite;
    Texture texture;
    IntRect rect;
};