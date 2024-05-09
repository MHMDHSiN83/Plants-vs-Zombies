#include "../include/sunflower.hpp"


Sunflower::Sunflower(int _type) : Plant(_type) {
    if(!texture.loadFromFile("assets/sunflower/1.png")) {
        exit(0);
    }
    store_textures();
}

void Sunflower::build_animation() {
    if(!is_planted) return;
    timer++;
    int counter = ((timer/5 + 1) % number_of_idle_frames )+ 1;
    sprite.setTexture(textures[counter - 1]);
    if(timer == 156) timer = 0;
}

void Sunflower::store_textures() {
    for (int i = 1; i <= number_of_idle_frames; i++)
    {
        Texture new_texture;
        new_texture.loadFromFile("assets/sunflower/" + to_string(i) + ".png");
        textures.push_back(new_texture);
    }
}