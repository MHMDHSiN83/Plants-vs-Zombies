#pragma once
#include "require.hpp"
// #include "peashooter.hpp"

class Plant {
public:
    Plant(int type);
    ~Plant();
    void update(Vector2i position);
    void render(RenderWindow* window);
    virtual void build_animation();
    int handle_mouse_pressed(Vector2i mouse_position, bool (&tiles_status)[NUMBER_OF_TILE_HEIGHT][NUMBER_OF_TILE_WIDTH]);
    int get_card_index();
protected:
    Texture texture;
    Sprite sprite;
    IntRect rect;
    int type;
    int z;
    bool is_planted;
    int planting(Vector2i mouse_position, bool (&tiles_status)[NUMBER_OF_TILE_HEIGHT][NUMBER_OF_TILE_WIDTH]);
    bool is_mouse_on_playground(Vector2i mouse_position);
    pair<float, float> get_center_of_current_tile(int height_index, int width_index, float tile_width, float tile_height);
    int timer = 0;
};