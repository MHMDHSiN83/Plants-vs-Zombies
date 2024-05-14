#include "../include/card.hpp"
// #include "../include/plant.hpp"
Card::Card(Vector2i first_card_position, int _type, double _cooldown, double _price) {
    type = _type;
    set_texture();
    rect.top = 0;
    rect.left = 0;
    rect.width = 188;//280
    rect.height = 112;//174
    sprite.setTexture(texture);
    sprite.setTextureRect(rect);
    first_card_position.y += _type * 140;
    Vector2f pos(first_card_position.x, first_card_position.y);
    sprite.setPosition(pos);
    sprite.setScale(1,1);
    is_clicked = true;
    timer = 0;
    cooldown = _cooldown;
    price = _price;
    if (!font.loadFromFile("assets/ARIAL.TTF")) {
        exit(0);
    }
    time_text.setFont(font);
    time_text.setCharacterSize(30);
    time_text.setFillColor(Color::Red);
    time_text.setStyle(Text::Bold);
    time_text.setPosition(sprite.getPosition().x + 10, sprite.getPosition().y + 10);


    price_text.setFont(font);
    price_text.setCharacterSize(30);
    price_text.setFillColor(Color::Black);
    price_text.setStyle(Text::Bold);
    price_text.setString(to_string((int)price));
    cout << price_text.getGlobalBounds().width << endl;
    price_text.setPosition(sprite.getPosition().x + sprite.getGlobalBounds().width -  price_text.getGlobalBounds().width - 30, 
                            sprite.getPosition().y + sprite.getGlobalBounds().height -  price_text.getGlobalBounds().height - 20);
}

void Card::set_texture() {
    switch (type)
    {
    case 0:
        if(!texture.loadFromFile("assets/cards/on_peashooter.png"))
            exit(0);
        if(!pressed_texture.loadFromFile("assets/cards/off_peashooter.png"))
            exit(0);
        break;
    case 1:
        if(!texture.loadFromFile("assets/cards/on_sunflower.png"))
            exit(0);
        if(!pressed_texture.loadFromFile("assets/cards/off_sunflower.png"))
            exit(0);
        break;
    case 2:
        if(!texture.loadFromFile("assets/cards/on_wallnut.png"))
            exit(0);
        if(!pressed_texture.loadFromFile("assets/cards/off_wallnut.png"))
            exit(0);
        break;
    case 3:
        if(!texture.loadFromFile("assets/cards/on_snow_peashooter.png"))
            exit(0);
        if(!pressed_texture.loadFromFile("assets/cards/off_snow_peashooter.png"))
            exit(0);
        break;
    }
}

Card::~Card() {

}

string doubleToStringWithOneDecimal(double number) {
    ostringstream stream;
    stream << fixed << setprecision(1) << number;
    return stream.str();
}

void Card::set_able_to_plant(int sun) {
    if(price > sun)
        able_to_plant = false;
    else
        able_to_plant = true;
}

void Card::set_background() {
    if(!is_clicked and able_to_plant)
        sprite.setTexture(texture);
    else
        sprite.setTexture(pressed_texture);
}

void Card::update(int sun) {
    set_able_to_plant(sun);
    Time elapsed = clock.getElapsedTime();
    if(is_clicked) {
        if(cooldown > elapsed.asSeconds())
            time_text.setString(doubleToStringWithOneDecimal(cooldown - elapsed.asSeconds()));
        else {
            time_text.setString("");
            is_clicked = false;
            clock.restart();
        }
    }
    set_background();
}

void Card::render(RenderWindow* window) {
    window->draw(sprite);
    window->draw(time_text);
    window->draw(price_text);
}

bool Card::handle_mouse_pressed(Vector2i mouse_position) {
    Vector2f position = sprite.getPosition();
    Vector2f sprite_size = {sprite.getGlobalBounds().width, sprite.getGlobalBounds().height};
    if(!is_clicked and able_to_plant) {
        if (mouse_position.x >= position.x && mouse_position.x <= position.x + sprite_size.x &&
            mouse_position.y >= position.y && mouse_position.y <= position.y + sprite_size.y) {
            sprite.setTexture(pressed_texture);
            return true;
        }
    }
    return false;
}

void Card::reset_card() { 
    is_clicked = false;
    sprite.setTexture(texture);
}

void Card::start_timer() { 
    clock.restart();
    is_clicked = true;
}

double Card::get_price() {
    return price;
}

void Card::disable() {
    is_clicked = true;
}