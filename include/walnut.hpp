#pragma once
#include "require.hpp"
#include "plant.hpp"

class Walnut : public Plant {
public:
    Walnut(int type);
private:
        int health;
        // Tir* tir;
};