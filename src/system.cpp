#include "../include/require.hpp"
#include "../include/system.hpp"


System::System() {
    window.create(VideoMode::getDesktopMode(), "PVZ", Style::Default);
    window.setFramerateLimit(120);
    status = PLAYING;
    if(!background_texture.loadFromFile("assets/background1.png")) {
        exit(0);
    }
    screen_size = window.getSize();
    background_sprite.setScale(screen_size.x / (float)background_texture.getSize().x, screen_size.y / (float)background_texture.getSize().y);
    background_sprite.setTexture(background_texture);
    score_box = new ScoreBox;

    // play_music();
    
    for(int i = 0; i < PLANTS_NUMBER; i++)
        cards[i] = new Card(FIRST_CARD_POSITION, i);
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
        update_cards();
        build_animation();
        update_sunshines();
        create_sunshine();
        update_zombies();
        create_zombie();
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
        render_cards();
        render_sunshines();
        render_zombies();
        score_box->render(&window, sun);
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
        }
    }
    window.display();
}

void System::play_music() {
    if(!music.openFromFile("assets/music/intro.ogg")){
        exit(0);
    }
    music.setLoop(true);
    music.play();
}

void System::mouse_pressed(Event event) {
    if (event.mouseButton.button == Mouse::Right)
        return;
    Vector2i mouse_position = {event.mouseButton.x, event.mouseButton.y};
    switch (status) {
        case (PLAYING):
            handle_mouse_pressed_plants(mouse_position);
            handle_mouse_pressed_cards(mouse_position);
            handle_mouse_pressed_sunshines(mouse_position);
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
        int result = plants[i]->handle_mouse_pressed(mouse_position, tiles_status);
        if(result == 0) {
            cards[plants[i]->get_card_index()]->reset_card();
            plants.pop_back();
        } else if(result == 1) {
            cards[plants[i]->get_card_index()]->start_timer();
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

void System::create_plant(int i){
    switch (i)
    {
        case 0:
            plants.push_back(new Peashooter(i));
            break;
        case 1:
            plants.push_back(new Sunflower(i));
            break;
        case 2:
            plants.push_back(new Walnut(i));
            break;
        case 3:
            plants.push_back(new IcePeashooter(i));
            break;
    }
}

void System::handle_mouse_pressed_cards(Vector2i mouse_position) {
    for (int i = 0; i < PLANTS_NUMBER; i++)
    {
        if(cards[i]->handle_mouse_pressed(mouse_position)) {
            create_plant(i);
        }
    }
    
}

void System::update_cards() {
    for (int i = 0; i < PLANTS_NUMBER; i++)
    {
        cards[i]->update();
    }
}

void System::build_animation(){
    for (Plant* plant : plants)
    {
        plant->build_animation();
    }
    
}


void System::render_sunshines() {
    for (Sunshine* sunshine: sunshines) {
        sunshine->render(&window);
    }
    
}

void System::update_sunshines() {
    for (int i = 0; i < sunshines.size(); i++) {
        sunshines[i]->update();
        if(sunshines[i]->is_out(screen_size.y)) {
            sunshines.erase(sunshines.begin() + i);
            i--;
        }
    }
}

void System::handle_mouse_pressed_sunshines(Vector2i mouse_position) {
    for (int i = 0; i < sunshines.size(); i++) {
        if(sunshines[i]->handle_mouse_pressed(mouse_position)) {
            sun += 25;
            sunshines.erase(sunshines.begin() + i);
            i--;
        }
    }    
}

void System::create_sunshine() {
    system_clock::time_point now = system_clock::now();
    duration<double> distance = now - last_sunshine_time;
    if(distance.count() > SUNSHINE_TIMER) {
        last_sunshine_time = now;
        Vector2f sunshine_position(generate_random_number_between(MIN_WIDTH, MAX_WIDTH), 0);
        sunshines.push_back(new Sunshine(sunshine_position));
    }
}
int System::generate_random_number_between(int start, int end) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(start, end);
    int random_number = dis(gen);
    return random_number;
}


void System::create_zombie() {
    system_clock::time_point now = system_clock::now();
    duration<double> distance = now - last_zombie_time;
    if(distance.count() > ZOMBIE_TIMER) {
        last_zombie_time = now;
        Vector2f zombie_position(1920, calculate_height_position(generate_random_number_between(1,5)));
        zombies.push_back(new Zombie(zombie_position));
    }
}

void System::render_zombies() {
    for (Zombie* zombie: zombies) {
        zombie->render(&window);
    }
    
}

void System::update_zombies() {
    for (Zombie* zombie: zombies) {
        zombie->update();
    }
}

int System::calculate_height_position(int tile) {
    return (MIN_HEIGHT + (tile - 0.5) * TILE_HEIGHT);
}