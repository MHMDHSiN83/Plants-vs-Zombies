#pragma once
#include "require.hpp"
#include "plant.hpp"

class Peashooter : public Plant {
public:
    Peashooter(int type);
    void build_animation();
private:
        int freamsize1 = 20;
        int health;
};