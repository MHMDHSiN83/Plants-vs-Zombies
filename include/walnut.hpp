#pragma once
#include "require.hpp"
#include "plant.hpp"

class Walnut : public Plant {
public:
    Walnut(int type, vector<double> walnut_data);
    void build_animation();
    void decrease_health(double zombie_damage);
    bool is_dead();
private:
    void store_textures();
    vector<Texture> textures;
    int number_of_idle_frames = 25;
    void set_data_of_walnut(vector<double> walnut_data);
};