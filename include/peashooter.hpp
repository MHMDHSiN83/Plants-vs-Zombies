#pragma once
#include "require.hpp"
#include "plant.hpp"

class Peashooter : public Plant {
public:
    Peashooter(int type);
private:
        int health;
        // Tir* tir;
};