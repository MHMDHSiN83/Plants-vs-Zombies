

#include "../include/require.hpp"
#include "../include/system.hpp"


System::System(int width, int height) {
    window.create(VideoMode(width, height), "PVZ", Style::Default);
    window.setFramerateLimit(120);
    status = PLAYING;
    if(!background_texture.loadFromFile("assets/background1.png")) {
        exit(0);
    }
    background_sprite.setTexture(background_texture);
    for(int i = 0; i < PLANTS_NUMBER; i++)
        cards[i] = new Card(FIRST_CARD_POSITION, i);
    // plant = new Plant();
    // plants.push_back(new Plant);
    // planting_area.first = make_pair(248, 993);
    // planting_area.second = make_pair(78, 573);
    // float tile_width = (993 - 248) / 9;
    // float tile_height = (573 - 78) / 5;
    for (int i = 0; i < NUMBER_OF_TILE_HEIGHT; i++)
        for (int j = 0; j < NUMBER_OF_TILE_WIDTH; j++)
            tiles_status[i][j] = 0;
    
}

System:: ~System() {}

void System::run() {
    while (window.isOpen() and status != EXIT) {
        update();
        render();
        handle_events();
    }
    exit(0);
}




void System::update() {
    Vector2i position = Mouse::getPosition(window);
    switch (status) {
    case (PLAYING):
        update_plants(position);
        // plant->update(position);
        update_cards();
        break;
    case (PAUSE_MENU):
        break;
    case (MAIN_MENU):
        break;
    case (VICTORY_SCREEN):
        break;
    case (GAMEOVER_SCREEN):
        break;
    case (EXIT):
        break;
    }
}

void System::render() {
    window.clear();
    switch (status) {
    case (PLAYING):
        window.draw(background_sprite);
        render_plants();
        // plant->render(&window);
        render_cards();
        break;
    case (PAUSE_MENU):
        break;
    case (MAIN_MENU):
        break;
    case (VICTORY_SCREEN):
        break;
    case (GAMEOVER_SCREEN):
        break;
    case (EXIT):
        break;
    }
    window.display();
}

void System::handle_events() {
    Event event;
    while (window.pollEvent(event)) {
    switch (event.type) {
        case (Event::Closed):
            window.close();
            status = EXIT;
            break;
        case (Event::MouseButtonPressed):
            mouse_pressed(event);
            break;
        case (Event::Resized):
        

            break;
        }
    }
    window.display();
}


void System::mouse_pressed(Event event) {
    if (event.mouseButton.button == Mouse::Right)
        return;
    Vector2i mouse_position = {event.mouseButton.x, event.mouseButton.y};
    switch (status) {
        case (PLAYING):
            // plant->handle_mouse_pressed(mouse_position, tiles_status);
            handle_mouse_pressed_plants(mouse_position);
            handle_mouse_pressed_cards(mouse_position);
            break;
        case (PAUSE_MENU):
            break;
        case (MAIN_MENU):
            break;
        case (VICTORY_SCREEN):
            break;
        case (GAMEOVER_SCREEN):
            break;
  }
}






void System::render_plants() {
    for (Plant* plant : plants)
    {
        plant->render(&window);
    }
    
}

void System::handle_mouse_pressed_plants(Vector2i mouse_position) {
    for (int i = 0; i < plants.size(); i++)
    {
        if(!(plants[i]->handle_mouse_pressed(mouse_position, tiles_status))) {
            plants.erase(plants.begin() + i);
            cards[plants[i]->get_card_index()]->reset_timer();
        }
    }
    
}

void System::update_plants(Vector2i position) {
    for (Plant* plant : plants)
    {
        plant->update(position);
    }
}


void System::render_cards() {
    for (int i = 0; i < PLANTS_NUMBER; i++)
    {
        cards[i]->render(&window);
    }
    
}

void System::handle_mouse_pressed_cards(Vector2i mouse_position) {
    for (int i = 0; i < PLANTS_NUMBER; i++)
    {
        if(cards[i]->handle_mouse_pressed(mouse_position)) {
            plants.push_back(new Plant(i));
        }
    }
    
}

void System::update_cards() {
    for (int i = 0; i < PLANTS_NUMBER; i++)
    {
        cards[i]->update();
    }
}