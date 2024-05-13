#pragma once
#include "require.hpp"

class Card {
public:
    Card(Vector2i first_card_position, int type, double _cooldown, double _price);
    ~Card();
    void render(RenderWindow* window);
    void update(int sun);
    bool handle_mouse_pressed(Vector2i mouse_position);
    void reset_card();
    void start_timer(); 
    void set_texture();
    double get_price();
    void disable();
private:
    int type;
    bool is_clicked;
    Texture texture;
    Texture pressed_texture;
    Sprite sprite;
    IntRect rect;
    int timer;
    Clock clock;
    double cooldown;
    double price;
};