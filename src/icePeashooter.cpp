#include "../include/icePeashooter.hpp"


IcePeashooter::IcePeashooter(int _type) : Plant(_type) {
    if(!texture.loadFromFile("assets/Icepeoshooter/Icepeoshooter/1.png")) {
        exit(0);
    }
    store_textures();
}

void IcePeashooter::build_animation() {
    if(!is_planted) return;
    timer++;
    int counter = ((timer/5 + 1) % number_of_idle_frames )+ 1;
    sprite.setTexture(textures[counter - 1]);
    if(timer == 91) timer = 0;
}

void IcePeashooter::store_textures() {
    for (int i = 1; i <= number_of_idle_frames; i++)
    {
        Texture new_texture;
        new_texture.loadFromFile("assets/Icepeoshooter/Icepeoshooter/" + to_string(i) + ".png");
        textures.push_back(new_texture);
    }
}