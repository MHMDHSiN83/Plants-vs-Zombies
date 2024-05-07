#pragma once
#include "require.hpp"
#include "plant.hpp"

class Sunflower : public Plant {
public:
    Sunflower(int type);
private:
        int health;
        // Tir* tir;
};