#include "../include/peashooter.hpp"


Peashooter::Peashooter(int _type) : Plant(_type) {
    
}

void Peashooter::build_animation() {
    if(!is_planted) return;
    timer++;
    int x = timer/7;
    x = (x + 1) % 8;
    x++;
   // if(x == 9){x = 1;}
    string x_in_string = to_string(x);
    texture.loadFromFile("assets/peashooter/peashooter-idle/" + x_in_string + ".png");
    //texture.loadFromFile("assets/AA.png");
    sprite.setTexture(texture);
    sprite.setTextureRect(rect);
}