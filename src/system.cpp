#include "../include/require.hpp"
#include "../include/system.hpp"


System::System(vector<double> zombies_data, vector<double> plant_data, vector<double> attack_data, vector<double> sun_data) {
    window.create(VideoMode::getDesktopMode(), "PVZ", Style::Default);
    window.setFramerateLimit(120);

    status = MAIN_MENU;
    
    set_background("assets/main_menu.png");

    score_box = new ScoreBox;

    // play_music();
    
    set_information(zombies_data, plant_data, attack_data, sun_data);
    for(int i = 0; i < PLANTS_NUMBER; i++) {
        double cooldown;
        double price;
        switch (i)
        {
        case 0:
            cooldown = peashooter_data[2];
            price = peashooter_data[5];
            break;
        case 1:
            cooldown = sun_flower_data[2];
            price = sun_flower_data[5];
            break;
        case 2:
            cooldown = walnut_data[2];
            price = walnut_data[5];
            break;
        case 3:
            cooldown = icepeashooter_data[2];
            price = icepeashooter_data[5];
            break;
        }
        cards[i] = new Card(FIRST_CARD_POSITION, i, cooldown, price);
    }
    for (int i = 0; i < NUMBER_OF_TILE_HEIGHT; i++)
        for (int j = 0; j < NUMBER_OF_TILE_WIDTH; j++)
            tiles_status[i][j] = 0;
    if(!pause_menu_texture.loadFromFile("assets/pause_menu.png")) {
        exit(0);
    }
    // screen_size = window.getSize();
    // background_sprite.setScale(screen_size.x / (float)background_texture.getSize().x, screen_size.y / (float)background_texture.getSize().y);
    pause_menu_sprite.setTexture(pause_menu_texture);
    pause_menu_sprite.setPosition(screen_size.x / 2 - pause_menu_sprite.getGlobalBounds().width / 2, screen_size.y / 2 - pause_menu_sprite.getGlobalBounds().height / 2);
}

void System::set_information(vector<double> zombies_data, vector<double> plant_data, vector<double> attack_data, vector<double> sun_data){
    for(int i = 0; i < 8; i++)
        regular_zombie.push_back(zombies_data[i]);
    for(int i = 0; i < 6; i++)
        peashooter_data.push_back(plant_data[i]);
    for(int i = 6; i < 12; i++)
        icepeashooter_data.push_back(plant_data[i]);
    for(int i = 12; i < 18; i++)
        kernelPult_data.push_back(plant_data[i]);
    for(int i = 18; i < 24; i++)
        sun_flower_data.push_back(plant_data[i]);
    for(int i = 24; i < 30; i++)
        walnut_data.push_back(plant_data[i]);
    zombies_attacking_data = attack_data;
    sunshine_data = sun_data;
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
        update_bullets();
        handle_collision();
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
    window.draw(background_sprite);
    switch (status) {
    case (PLAYING):
        render_plants();
        render_zombies();
        render_cards();
        score_box->render(&window, sun);
        render_bullets();
        render_sunshines();
        break;
    case (PAUSE_MENU):
        render_plants();
        render_zombies();
        render_cards();
        score_box->render(&window, sun);
        render_bullets();
        render_sunshines();
        render_pause_menu();
        break;
    case (MAIN_MENU):
        render_main_menu();
        break;
    case (VICTORY_SCREEN):
        break;
    case (GAMEOVER_SCREEN):
        // render_game_over();
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
        case (Event::KeyPressed):
            key_pressed(event);
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
            handle_mouse_pressed_pause_menu(mouse_position);
            break;
        case (MAIN_MENU):
            handle_mouse_pressed_main_menu(mouse_position);
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
            sun -= cards[plants[i]->get_card_index()]->get_price();
        }
    }
}

void System::update_plants(Vector2i position) {
    for (Plant* plant : plants)
    {
        plant->update(position);
        if(plant->is_time_to_create_sunshine()) {
            cout << "test" << endl;
            Vector2f plant_position = plant->get_position();
            sunshines.push_back(new Sunshine({plant_position.x + 60, plant_position.y + 60}, sunshine_data, 0));
        }
        if(!is_there_zombie_in_front(plant))  {
            continue;
        }
        Bullet* bullet = plant->shoot();
        if(bullet != NULL)
            bullets.push_back(bullet);
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
            plants.push_back(new AttackingPlant(i, peashooter_data, icepeashooter_data));
            break;
        case 1:
            plants.push_back(new Sunflower(i, sun_flower_data));
            break;
        case 2:
            plants.push_back(new Walnut(i, walnut_data));
            break;
        case 3:
            plants.push_back(new AttackingPlant(i, peashooter_data, icepeashooter_data));
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
        cards[i]->update(sun);
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
    Time elapsed = sunshine_clock.getElapsedTime();
    if(elapsed.asSeconds() > sunshine_data[1]) {
        Vector2f sunshine_position(generate_random_number_between(MIN_WIDTH, MAX_WIDTH), 0);
        sunshines.push_back(new Sunshine(sunshine_position, sunshine_data, 1));
        sunshine_clock.restart();
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
    Time elapsed = zombie_clock.getElapsedTime();
    if(elapsed.asSeconds() > ZOMBIE_TIMER) {
        int rand = generate_random_number_between(1,5);
        int type = generate_random_number_between(0,1);
        Vector2f zombie_position(MAX_WIDTH, calculate_height_position(rand));
        zombies.push_back(new Zombie(type, zombie_position, regular_zombie, zombies_attacking_data, rand));
        zombie_clock.restart();
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
        if(zombie->is_out()) {
            status = GAMEOVER_SCREEN;
            set_background("assets/game_over.png");
        }
    }
}

void System::build_animation(){
    build_animation_of_plants();
    build_animation_of_zombie();
}
void System::build_animation_of_plants(){
    for (Plant* plant : plants)
    {
        plant->build_animation();
    }
}

void System::build_animation_of_zombie(){
    for (Zombie* zombie : zombies)
    {
        zombie->build_animation();
    }
}


int System::calculate_height_position(int tile) {
    return (MIN_HEIGHT + (tile - 0.5) * TILE_HEIGHT);
}

void System::render_bullets() {
    for (Bullet* bullet: bullets) {
        bullet->render(&window);
    }
}

void System::update_bullets() {
    for (int i = 0; i < bullets.size(); i++) {
        bullets[i]->update();
        if(bullets[i]->is_out(screen_size.x)) {
            bullets.erase(bullets.begin() + i);
            i--;
        }
    }
}

void System::handle_collision() {
    handle_zombie_plant_collision();
    handle_zombie_bullet_collision();
}

void System::handle_zombie_bullet_collision() {
    for (int i = 0; i < bullets.size(); i++)
    {
        FloatRect bullet_rect = bullets[i]->get_rect();
        for (int j = 0; j < zombies.size(); j++)
        {
            FloatRect zombie_rect = zombies[j]->get_rect();
            if(zombie_rect.intersects(bullet_rect) and is_on_same_height(bullets[i], zombies[j])) {
                zombies[j]->decrease_health(bullets[i]->get_damage());
                if(zombies[j]->is_dead()) {
                    zombies.erase(zombies.begin() + j);
                    j--;
                }
                bullets.erase(bullets.begin() + i);
                i--;
                break;
            }
        }
    }
}

void System::handle_zombie_plant_collision() {
    for (int i = 0; i < plants.size(); i++)
    {
        FloatRect plant_rect = plants[i]->get_rect();
        for (int j = 0; j < zombies.size(); j++)
        {
            FloatRect zombie_rect = zombies[j]->get_rect();
            if(zombie_rect.intersects(plant_rect) and is_on_same_height(plants[i], zombies[j])) {
                if(zombies[j]->is_eating()) {
                    Time elapsed = zombies[j]->get_elapsed();
                    if(elapsed.asSeconds() > zombies[j]->get_hit_rate()) {
                        plants[i]->decrease_health(zombies[j]->get_damage());
                        zombies[j]->restart_clock();
                    }
                } else {
                    zombies[j]->change_eating_situation();
                    zombies[j]->restart_clock();
                }
            }
        }
        if(plants[i]->is_dead()) {
            for (Zombie* zombie : zombies)
            {
                FloatRect zombie_rect = zombie->get_rect();
                if(zombie_rect.intersects(plant_rect) and is_on_same_height(plants[i], zombie)) {
                    zombie->change_eating_situation();
                }
            }
            tiles_status[plants[i]->get_height() - 1][plants[i]->get_width() - 1] = false;
            plants.erase(plants.begin() + i);
            i--;
        }
    }
}


bool System::is_on_same_height(Bullet* bullet, Zombie* zombie) {
    if(bullet->get_height() == zombie->get_height())
        return true;
    return false;
}

bool System::is_on_same_height(Plant* plant, Zombie* zombie) {
    if(plant->get_height() == zombie->get_height())
        return true;
    return false;
}

bool System::is_there_zombie_in_front(Plant* plant) {
    for (Zombie* zombie : zombies) {
        if(zombie->get_height() == plant->get_height())
            if(zombie->get_rect().left > plant->get_rect().left )
                return true;
    }
    return false;
}


void System::render_main_menu() {

}

void System::handle_mouse_pressed_main_menu(Vector2i mouse_position) {
    if(mouse_position.x > screen_size.x/4 && mouse_position.x < 3 * screen_size.x/4 && mouse_position.y > 6 * screen_size.y/7) {
        status = PLAYING;
        set_background("assets/background.png");
    }
}

void System::set_background(string path) {
    if(!background_texture.loadFromFile(path)) {
        exit(0);
    }
    screen_size = window.getSize();
    background_sprite.setScale(screen_size.x / (float)background_texture.getSize().x, screen_size.y / (float)background_texture.getSize().y);
    background_sprite.setTexture(background_texture);
}

void System::key_pressed(Event event) {
    if(event.key.code = Keyboard::Escape) {
        status = PAUSE_MENU;
    }
}

void System::render_pause_menu() {
    window.draw(pause_menu_sprite);
}
void System::handle_mouse_pressed_pause_menu(Vector2i mouse_position) {
    status = PLAYING;
}