#pragma once
#include "require.hpp"
#include "plant.hpp"
// #include "bullet.hpp"

class AttackingPlant : public Plant {
public:
    AttackingPlant(int type, vector<double> peashooter_data, vector<double> icepeashooter_data);
    void build_animation();
    Bullet* shoot();
    void decrease_health(double zombie_damage);
    bool is_dead();
private:
    void store_textures();
    vector<Texture> textures;
    int number_of_idle_frames;
    float speed_effect;
    void set_data_of_peashooter(vector<double> peashooter_data);
    void set_data_of_icepeashooter(vector<double> icepeashooter_data);
};