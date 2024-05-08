#include "../include/peashooter.hpp"


Peashooter::Peashooter(int _type) : Plant(_type) {
    
}

void Peashooter::build_animation() {
    if(!is_planted) return;
    timer++;
    int fream = timer/5;
    fream = (fream + 1) % freamsize1;
    fream++;
    string fream_in_string = to_string(fream);
    texture.loadFromFile("assets/peashooter/peashooters/" + fream_in_string + ".png");
    
    // texture.loadFromFile("assets/peashooter/peashooter-idle/1.png");
    //texture.loadFromFile("assets/peashooter/peashooter-idle/" + fream_in_string + ".png");
    sprite.setTexture(texture);
    sprite.setTextureRect(rect);
    // sprite.setScale(0.05, 0.05);
}
