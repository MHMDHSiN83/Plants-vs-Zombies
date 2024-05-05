#pragma once
#include "require.hpp"

class Plant {
public:
    Plant();
    ~Plant();
    void update();
    void render(RenderWindow* window);
    // void event();
private:
    Texture texture;
    Sprite sprite;
    IntRect rect;
    Vector2f position;
};