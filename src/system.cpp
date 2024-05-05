

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
    switch (status) {
    case (PLAYING):
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


void System::mouse_pressed(Event event) {

}



