#pragma once
#include "require.hpp"
#include "plant.hpp"

class IcePeashooter : public Plant {
public:
    IcePeashooter(int type);
    void build_animation();
private:
    void store_textures();
    vector<Texture> textures;
        int number_of_idle_frames = 18;
        int health;
};