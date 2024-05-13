#pragma once
#include "require.hpp"
#include "bullet.hpp"

class Plant {
public:
    Plant(int type);
    ~Plant();
    void update(Vector2i position);
    void render(RenderWindow* window);
    virtual void build_animation();
    int handle_mouse_pressed(Vector2i mouse_position, bool (&tiles_status)[NUMBER_OF_TILE_HEIGHT][NUMBER_OF_TILE_WIDTH]);
    int get_card_index();
    virtual Bullet* shoot();
    int get_height();
    int get_width();
    FloatRect get_rect();
    virtual void decrease_health(double zombie_damage);
    virtual bool is_dead();
protected:
    Texture texture;
    Sprite sprite;
    IntRect rect;
    int width = 0;
    int height = 0;
    int type;
    bool is_planted;
    int planting(Vector2i mouse_position, bool (&tiles_status)[NUMBER_OF_TILE_HEIGHT][NUMBER_OF_TILE_WIDTH]);
    bool is_mouse_on_playground(int width_index, int height_index);
    pair<float, float> get_center_of_current_tile(int height_index, int width_index, float tile_width, float tile_height);
    int timer = 0;
    Clock action_clock;
    void set_size(int type);
    double damage;
    double health;
    double cooldown;
    double hit_rate;
    double speed;
    double price;
};