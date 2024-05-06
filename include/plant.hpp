#pragma once
#include "require.hpp"

class Plant {
public:
    Plant();
    ~Plant();
    void update(Vector2i position);
    void render(RenderWindow* window);
    void handle_mouse_pressed(Vector2i mouse_position, bool (&tiles_status)[NUMBER_OF_TILE_HEIGHT][NUMBER_OF_TILE_WIDTH]);
private:
    Texture texture;
    Sprite sprite;
    IntRect rect;
    bool is_clicked;
    bool is_planted;
    void planting(Vector2i mouse_position, bool (&tiles_status)[NUMBER_OF_TILE_HEIGHT][NUMBER_OF_TILE_WIDTH]);
    bool is_mouse_on_playground(Vector2i mouse_position);
    pair<float, float> get_center_of_current_tile(int height_index, int width_index, float tile_width, float tile_height);
    // Vector2f position;
};