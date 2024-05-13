#pragma once
#include "require.hpp"
#include "plant.hpp"
// #include "bullet.hpp"

class AttackingPlant : public Plant {
public:
    AttackingPlant(int type, vector<double> peashooter_data, vector<double> icepeashooter_data);
    void build_animation();
    Bullet* shoot();
private:
    void store_textures();
    vector<Texture> textures;
    int number_of_idle_frames;
    float speed_effect;
    double damage;
    double health;
    double cooldown;
    double hit_rate;
    double speed;
    double price;
    void set_data_of_peashooter(vector<double> peashooter_data);
    void set_data_of_icepeashooter(vector<double> icepeashooter_data);
};