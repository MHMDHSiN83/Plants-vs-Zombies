#pragma once

#include "require.hpp"


class Sunshine {
public:
    Sunshine(Vector2f position, vector<double> sunshine_data, bool _type);
    ~Sunshine();
    void update();
    void render(RenderWindow* Window);
    bool handle_mouse_pressed(Vector2i mouse_position);
    bool is_out(unsigned screen_height);
private:
    Texture texture;
    Sprite sprite;
    IntRect rect;
    double speed;
    double interval;
    bool type;
    void set_data(vector<double> sunshine_data);
};