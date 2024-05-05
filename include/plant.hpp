#pragma once


class Plant {
public:
    Plant();
    ~Plant();
    void update();
    void render();
    // void event();
private:
    Texture texture;
    Sprite sprite;
    

};