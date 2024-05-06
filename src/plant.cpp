#include "../include/plant.hpp"

Plant::Plant(int _type) {

    if(!texture.loadFromFile("assets/peashooter.png")) {
        exit(0);
    }
    rect.top = 0;
    rect.left = 0;
    rect.width = 39;
    rect.height = 38;
    sprite.setTexture(texture);
    sprite.setTextureRect(rect);
    Vector2f pos(FIRST_CARD_POSITION.x, FIRST_CARD_POSITION.y + _type * 70);
    sprite.setPosition(pos);
    sprite.setScale(2,2);
    is_clicked = true;
    is_planted = false;
    type = _type;
}

Plant::~Plant() {

}

void Plant::update(Vector2i position){
    if(is_clicked){
        Vector2f target(position.x - sprite.getTextureRect().width, position.y - sprite.getTextureRect().height);
        sprite.setPosition(target);
    }
}


void Plant::render(RenderWindow* window) {
    window->draw(sprite);
}


bool Plant::handle_mouse_pressed(Vector2i mouse_position, bool (&tiles_status)[NUMBER_OF_TILE_HEIGHT][NUMBER_OF_TILE_WIDTH]) {
    Vector2f position = sprite.getPosition();
    Vector2f sprite_size = {sprite.getGlobalBounds().width, sprite.getGlobalBounds().height};
    if(is_clicked) {
        is_clicked = false;
        return (planting(mouse_position, tiles_status));
    }
    return true;
}

bool Plant::is_mouse_on_playground(Vector2i mouse_position){
    if(mouse_position.x < MIN_WIDTH || mouse_position.x > MAX_WIDTH)
        return false;
    if(mouse_position.y < MIN_HEIGHT || mouse_position.y > MAX_HEIGHT)
        return false;
    return true;
}

pair<float, float> Plant::get_center_of_current_tile(int height_index, int width_index, float tile_width, float tile_height){
        return make_pair((width_index - 0.5) * tile_width, (height_index - 0.5) * tile_height);
}

bool Plant::planting(Vector2i mouse_position, bool (&tiles_status)[NUMBER_OF_TILE_HEIGHT][NUMBER_OF_TILE_WIDTH]) {
    if(!is_mouse_on_playground(mouse_position)) {
        return false;
    }

    float tile_width = (MAX_WIDTH - MIN_WIDTH) / NUMBER_OF_TILE_WIDTH;
    float tile_height = (MAX_HEIGHT - MIN_HEIGHT) / NUMBER_OF_TILE_HEIGHT;

    int width_index = 0, height_index = 0;
    for (float i = MIN_WIDTH; i < MAX_WIDTH; i += tile_width)
    {
        if(mouse_position.x < i) {
            break;
        }
        width_index++;
        
    }
    for (float i = MIN_HEIGHT; i < MAX_HEIGHT; i += tile_height)
    {
        if(mouse_position.y < i) {
            break;
        }
        height_index++;
    }
    if(!tiles_status[width_index][height_index]) {
        tiles_status[width_index][height_index] = true;
        pair<float, float> center_of_tile = get_center_of_current_tile(height_index, width_index, tile_width, tile_height); 
        sprite.setPosition(MIN_WIDTH + center_of_tile.first - sprite.getTextureRect().width, MIN_HEIGHT + center_of_tile.second - sprite.getTextureRect().height);
    } else {
        is_clicked = true;
    }
    
    return true;
}


int Plant::get_card_index() { return type; }