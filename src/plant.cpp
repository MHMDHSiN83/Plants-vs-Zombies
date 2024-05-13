#include "../include/plant.hpp"

Plant::Plant(int _type){
    type = _type;
    rect.top = 0;
    rect.left = 0;
    rect.width = 465;
    rect.height = 537;
    sprite.setTexture(texture);
    sprite.setTextureRect(rect);
    Vector2f pos(FIRST_CARD_POSITION.x, FIRST_CARD_POSITION.y + _type * 140);
    set_size(type);
    sprite.setPosition(pos);
    is_planted = false;
    health = 5;
}

Plant::~Plant() {

}

void Plant::set_size(int type){
    switch (type)
    {
    case 0:
        sprite.setScale(0.28,0.28);
        break;
    case 1:
        sprite.setScale(0.25,0.25);
        break;
    case 2:
        sprite.setScale(0.35,0.35);
        break;
    case 3:
        sprite.setScale(0.38,0.38);
        break;
    default:
        break;
    }
}

void Plant::build_animation() {}

void Plant::update(Vector2i position){
    if(!is_planted){
        Vector2f target(position.x - sprite.getGlobalBounds().width/2, position.y - sprite.getGlobalBounds().height/2);
        sprite.setPosition(target);
    }
}


void Plant::render(RenderWindow* window) {
    window->draw(sprite);
}


int Plant::handle_mouse_pressed(Vector2i mouse_position, bool (&tiles_status)[NUMBER_OF_TILE_HEIGHT][NUMBER_OF_TILE_WIDTH]) {
    Vector2f position = sprite.getPosition();
    Vector2f sprite_size = {sprite.getGlobalBounds().width, sprite.getGlobalBounds().height};
    if(!is_planted) {
        is_planted = true;
        return (planting(mouse_position, tiles_status));
    }
    return 2;
}

bool Plant::is_mouse_on_playground(int width_index, int height_index){
    if(width_index > NUMBER_OF_TILE_WIDTH || width_index < 1)
        return false;
    if(height_index > NUMBER_OF_TILE_HEIGHT || height_index < 1)
        return false;
    return true;
}


pair<float, float> Plant::get_center_of_current_tile(int height_index, int width_index, float tile_width, float tile_height){
        return make_pair((width_index - 0.5) * tile_width, (height_index - 0.5) * tile_height);
}

int Plant::planting(Vector2i mouse_position, bool (&tiles_status)[NUMBER_OF_TILE_HEIGHT][NUMBER_OF_TILE_WIDTH]) {

    int width_index = 0, height_index = 0;
    for (float i = MIN_WIDTH; i < MAX_WIDTH; i += TILE_WIDTH)
    {
        if(mouse_position.x < i)
            break;
        width_index++;
    }
    for (float i = MIN_HEIGHT; i < MAX_HEIGHT; i += TILE_HEIGHT)
    {
        if(mouse_position.y < i)
            break;
        height_index++;
    }
    if(!is_mouse_on_playground(width_index, height_index))
        return 0;
    
    if(!tiles_status[height_index - 1][width_index - 1]) {
        tiles_status[height_index - 1][width_index - 1] = 1;
        width = width_index;
        height = height_index;
        pair<float, float> center_of_tile = get_center_of_current_tile(height_index, width_index, TILE_WIDTH, TILE_HEIGHT); 
        sprite.setPosition(MIN_WIDTH + center_of_tile.first - sprite.getGlobalBounds().width/2, MIN_HEIGHT + center_of_tile.second - sprite.getGlobalBounds().height/2);
        return 1;
    }
    is_planted = false;
    return 2;
}


int Plant::get_card_index() { return type; }

Bullet* Plant::shoot() { return NULL; }

int Plant::get_height() { return height; }

FloatRect Plant::get_rect() { return sprite.getGlobalBounds(); }


void Plant::decrease_health(int zombie_damage) { health -= zombie_damage; }

bool Plant::is_dead() {
    if(health <= 0)
        return true;
    return false;
}