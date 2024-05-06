#pragma once
#include "require.hpp"

class Card {
public:
    Card(Vector2i first_card_position, int distance);
    ~Card();
    void render(RenderWindow* window);
    void update();
    void handle_mouse_pressed(Vector2i mouse_position);
private:
    // Vector2i position;
    bool is_clicked;
    Texture texture;
    Texture pressed_texture;
    Sprite sprite;
    IntRect rect;
};