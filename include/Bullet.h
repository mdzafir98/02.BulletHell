#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <math.h>

class Bullet{
protected:
    sf::Sprite shape;
    sf::Vector2f direction;
    float m_speed;

public:
    Bullet(sf::Texture* texture, float posx, float posy, 
            float dirx, float diry, float speed, float scale);
    virtual ~Bullet();

    //accessor
    sf::FloatRect getBounds() const;

    void update();
    void render(sf::RenderTarget* target);
};

class Fire{
protected:
    sf::Sprite shape;
    sf::Vector2f direction;
    float m_angle;
    float m_speed;
public:
    Fire(sf::Texture* texture, float posx, float posy, 
            float speed, float scale, float px, float py);
    virtual ~Fire();
    sf::FloatRect getBounds() const;
    void update();
    void render(sf::RenderTarget* target);
};