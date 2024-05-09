#include "../include/peashooter.hpp"


Peashooter::Peashooter(int _type) : Plant(_type) {
    z = 0;
    if(!texture.loadFromFile("assets/peashooter/peashooters/1.png")) {
        exit(0);
    }
    store_textures();
}

void Peashooter::build_animation() {
    if(!is_planted) return;
    timer++;
    int counter = ((timer/5 + 1) % number_of_idle_frames )+ 1;
    sprite.setTexture(textures[counter - 1]);
    if(timer == 101) timer = 0;
}

void Peashooter::store_textures() {
    for (int i = 1; i <= number_of_idle_frames; i++)
    {
        Texture new_texture;
        new_texture.loadFromFile("assets/peashooter/peashooters/" + to_string(i) + ".png");
        textures.push_back(new_texture);
    }
}