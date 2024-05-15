#include "../include/require.hpp"
#include "../include/system.hpp"

System::System(vector<vector<double>> zombies_data, vector<vector<double>> plants_data, vector<double> attack_data, vector<double> sun_data) {
    window.create(VideoMode::getDesktopMode(), "PVZ", Style::Default);
    window.setFramerateLimit(120);

    status = MAIN_MENU;
    
    set_background("assets/main_menu.png");

    score_box = new ScoreBox;

    play_music("assets/music/intro.ogg", true);

    set_information(zombies_data, plants_data, attack_data, sun_data);

    create_cards(plants_data);
    
    set_pause_menu();
    
    for (int i = 0; i < NUMBER_OF_TILE_HEIGHT; i++)
        for (int j = 0; j < NUMBER_OF_TILE_WIDTH; j++)
            tiles_status[i][j] = 0;    
}

void System::set_information(vector<vector<double>> zombies_data, vector<vector<double>> plants_data, vector<double> attack_data, vector<double> sun_data){
    for (int i = 0; i < zombies_data.size(); i++)
    {
        for (int j = 1; j < zombies_data[i].size(); j++)
        {
            if(zombies_data[i][0] == 0)
                regular_zombie.push_back(zombies_data[i][j]);
            else
                hair_metal_gargantuar_zombie.push_back(zombies_data[i][j]);
        }   
    }

    for (int i = 0; i < plants_data.size(); i++)
    {
        for (int j = 1; j < plants_data[i].size(); j++)
        {
            if(plants_data[i][0] == 0) {
                peashooter_data.push_back(plants_data[i][j]);
            } else if(plants_data[i][0] == 1) {
                sunflower_data.push_back(plants_data[i][j]);
            } else if(plants_data[i][0] == 2) {
                walnut_data.push_back(plants_data[i][j]);
            } else if(plants_data[i][0] == 3) {
                icepeashooter_data.push_back(plants_data[i][j]);
            }
        }   
    }
    
    sunshine_data = sun_data;
    win_timer = attack_data[0];
    each_wave_time = attack_data[1];
    zombie_number_each_wave = attack_data[2];
    extra_zombie_each_wave = attack_data[3];
    cards_number = plants_data.size();
}

System:: ~System() {}

void System::run() {
    while (window.isOpen() and status != EXIT) {
        update();
        render();
        handle_events();
    }
    free_memory();
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
        update_wave();
        has_player_won();
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
        case (Event::KeyPressed):
            key_pressed(event);
        }
    }
    window.display();
}

void System::play_music(string path, bool loop) {
    if(!music.openFromFile(path)){
        exit(0);
    }
    music.setLoop(loop);
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
        plant->render(&window);
}

void System::handle_mouse_pressed_plants(Vector2i mouse_position) {

    for (int i = 0; i < plants.size(); i++)
    {
        int result = plants[i]->handle_mouse_pressed(mouse_position, tiles_status);
        Card* card = find_card_by_type(plants[i]->get_card_index());
        if(result == 0) {
            card->reset_card();
            plants.pop_back();
        } else if(result == 1) {
            card->start_timer();
            sun -= card->get_price();
        }
    }
}

void System::update_plants(Vector2i position) {
    for (Plant* plant : plants)
    {
        plant->update(position);
        if(plant->is_time_to_create_sunshine()) {
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
    for (int i = 0; i < cards_number; i++)
        cards[i]->render(&window);
}

void System::create_plant(int i){
    switch (i)
    {
        case 0:
            plants.push_back(new AttackingPlant(i, peashooter_data, icepeashooter_data));
            break;
        case 1:
            plants.push_back(new Sunflower(i, sunflower_data));
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
    for (int i = 0; i < cards_number; i++)
        if(cards[i]->handle_mouse_pressed(mouse_position))
            create_plant(cards[i]->get_type());
}

void System::update_cards() {
    for (int i = 0; i < cards_number; i++)
        cards[i]->update(sun);
}


void System::render_sunshines() {
    for (Sunshine* sunshine: sunshines)
        sunshine->render(&window);
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
    if(elapsed.asSeconds() > each_wave_time / zombie_number_each_wave) {
        int rand = generate_random_number_between(1,5);
        int type = generate_random_number_between(0,1);
        Vector2f zombie_position(MAX_WIDTH, calculate_height_position(rand));
        if(type)
            zombies.push_back(new Zombie(type, zombie_position, hair_metal_gargantuar_zombie, rand));
        else
            zombies.push_back(new Zombie(type, zombie_position, regular_zombie, rand));
        zombie_clock.restart();
    }
}

void System::render_zombies() {
    for (Zombie* zombie: zombies)
        zombie->render(&window);
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
        plant->build_animation();
}

void System::build_animation_of_zombie(){
    for (Zombie* zombie : zombies)
        zombie->build_animation();
}


int System::calculate_height_position(int tile) {
    return (MIN_HEIGHT + (tile - 0.5) * TILE_HEIGHT);
}

void System::render_bullets() {
    for (Bullet* bullet: bullets)
        bullet->render(&window);
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
                zombies[j]->speed_effect(bullets[i]->get_speed_effect());
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


void System::handle_mouse_pressed_main_menu(Vector2i mouse_position) {
    if(mouse_position.x > screen_size.x/4 && mouse_position.x < 3 * screen_size.x/4 && mouse_position.y > 6 * screen_size.y/7) {
        status = PLAYING;
        set_background("assets/background.png");
        restart_clocks();
        play_music("assets/music/ingame.ogg", true);
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
    if(event.key.code = Keyboard::Escape)
        status = PAUSE_MENU;
}

void System::render_pause_menu() {
    window.draw(pause_menu_sprite);
}
void System::handle_mouse_pressed_pause_menu(Vector2i mouse_position) {
    status = PLAYING;
}

void System::update_wave() {
    Time elapsed = wave_clock.getElapsedTime();
    if(elapsed.asSeconds() > each_wave_time) {
        zombie_number_each_wave += extra_zombie_each_wave;
        wave_clock.restart();
    }
}

void System::has_player_won() {
    Time elapsed = game_clock.getElapsedTime();
    if(elapsed.asSeconds() > win_timer) {
        status = VICTORY_SCREEN;
        set_background("assets/main_menu.png");
    }
}

Card* System::find_card_by_type(int type) {
    for (Card* card : cards)
        if(card->get_type() == type)
            return card;
    return NULL;
}

void System::restart_clocks() {
    game_clock.restart();
    wave_clock.restart();
    zombie_clock.restart();
    sunshine_clock.restart();
    for (Card* card : cards)
        card->start_timer();   
}

void System::create_cards(vector<vector<double>> plants_data) {
    for(int i = 0; i < cards_number; i++) {
        double cooldown;
        double price;
        int card_type = plants_data[i][0];
        switch (card_type)
        {
        case 0:
            cooldown = peashooter_data[2];
            price = peashooter_data[5];
            cards.push_back(new Card(FIRST_CARD_POSITION, card_type, cooldown, price, i));
            break;
        case 1:
            cooldown = sunflower_data[2];
            price = sunflower_data[5];
            cards.push_back(new Card(FIRST_CARD_POSITION, card_type, cooldown, price, i));
            break;
        case 2:
            cooldown = walnut_data[2];
            price = walnut_data[5];
            cards.push_back(new Card(FIRST_CARD_POSITION, card_type, cooldown, price, i));
            break;
        case 3:
            cooldown = icepeashooter_data[2];
            price = icepeashooter_data[5];
            cards.push_back(new Card(FIRST_CARD_POSITION, card_type, cooldown, price, i));
            break;
        }
    }
}

void System::set_pause_menu() {
    if(!pause_menu_texture.loadFromFile("assets/pause_menu.png"))
        exit(0);
    pause_menu_sprite.setTexture(pause_menu_texture);
    pause_menu_sprite.setPosition(screen_size.x / 2 - pause_menu_sprite.getGlobalBounds().width / 2, screen_size.y / 2 - pause_menu_sprite.getGlobalBounds().height / 2);
}

void System::free_memory() {
    delete score_box;
    for (auto p : plants)
        delete p;
    plants.clear();
    for (auto s : sunshines)
        delete s;
    sunshines.clear();
    for (auto z : zombies)
        delete z;
    zombies.clear();
    for (auto b : bullets)
        delete b;
    bullets.clear();
    for (auto c : cards)
        delete c;
    cards.clear();
}