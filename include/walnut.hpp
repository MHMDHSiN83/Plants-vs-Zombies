#pragma once
#include "require.hpp"
#include "plant.hpp"

class Walnut : public Plant {
public:
    Walnut(int type, vector<double> walnut_data);
    void build_animation();
private:
    void store_textures();
    vector<Texture> textures;
        int number_of_idle_frames = 25;
    double damage;
    double health;
    double cooldown;
    double hit_rate;
    double speed;
    double price;
    void set_data_of_walnut(vector<double> walnut_data);
};