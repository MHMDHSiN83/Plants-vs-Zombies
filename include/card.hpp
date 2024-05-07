#pragma once
#include "require.hpp"

class Card {
public:
    Card(Vector2i first_card_position, int type);
    ~Card();
    void render(RenderWindow* window);
    void update();
    bool handle_mouse_pressed(Vector2i mouse_position);
    void reset_timer();
private:

    int type;
    bool is_clicked;
    Texture texture;
    Texture pressed_texture;
    Sprite sprite;
    IntRect rect;
    int timer;
    void set_texture(int type);
};