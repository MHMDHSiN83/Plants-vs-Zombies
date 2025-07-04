#include "../include/bullet.hpp"

Bullet::Bullet(Vector2f position, int _type, int _width, int _height, double _speed, double _damage) {
    set_texture(_type);
    rect.top = 0;
    rect.left = 0;
    rect.width = 152;
    rect.height = 138;
    sprite.setTexture(texture);
    sprite.setTextureRect(rect);
    sprite.setPosition(position);
    sprite.setScale(0.2, 0.2);
    width = _width;
    height = _height;
    damage = _damage;
    speed = _speed;
    type = _type;
}


void Bullet::update() {
    sprite.setPosition(sprite.getPosition().x + speed, sprite.getPosition().y);
}

void Bullet::render(RenderWindow* window) {
    window->draw(sprite);
}

bool Bullet::handle_mouse_pressed(Vector2i mouse_position) {
    Vector2f position = sprite.getPosition();
    Vector2f sprite_size = {sprite.getGlobalBounds().width, sprite.getGlobalBounds().height};
    if (mouse_position.x >= position.x && mouse_position.x <= position.x + sprite_size.x &&
        mouse_position.y >= position.y && mouse_position.y <= position.y + sprite_size.y) {
        return true;
    }
    return false;    
}

bool Bullet::is_out(unsigned screen_width) {
    if(sprite.getPosition().x >= screen_width)
        return true;
    return false;
}

void Bullet::set_texture(int type) {
    switch (type)
    {
    case 0:
        if(!texture.loadFromFile(PEA_BULLET_PATH)) {
            exit(0);
        }
        break;
    case 3:
        if(!texture.loadFromFile(SNOW_PEA_BULLET_PATH)) {
            exit(0);
        }
        break;
    }
}

FloatRect Bullet::get_rect() { return sprite.getGlobalBounds(); }

int Bullet::get_height() { return height; }

int Bullet::get_damage() { return damage; }

double Bullet::get_speed_effect() {
    if(type == 0)
        return 1;
    else
        return 0.5;
}

Bullet::~Bullet() {}