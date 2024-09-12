#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>

class Background{
private:
    int width, height;
    std::array<sf::Sprite, 2> frames;
    sf::Texture texture;
    void initTexture();
    void initSprite();
public:
    Background(unsigned int s_width, unsigned int s_height);
    void update(float speed);
    void render(sf::RenderTarget* target);
};