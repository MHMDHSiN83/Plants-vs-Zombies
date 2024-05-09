#pragma once
#include "require.hpp"
#include "plant.hpp"

class Walnut : public Plant {
public:
    Walnut(int type);
    void build_animation();
private:
    void store_textures();
    vector<Texture> textures;
        int number_of_idle_frames = 25;
        int health;
};