#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

#include <string>
#include <sstream>

class Enemy{
private:
    unsigned pointCount;
    sf::CircleShape shape;
    sf::Sprite sprite;
    sf::Texture texture1, texture2, texture3;

    sf::Font font;
    sf::Text healthText;

    int type;
    float speed;
    int health;
    int healthMax;
    int damage;
    int points;

    void initVariables();
    void initShape();
    void initTexture();
    void initSprite();
    void initPoint();
public:
    Enemy(float posx, float posy);
    virtual ~Enemy();

    //accessors
    const sf::FloatRect getBounds() const;
    const int& getPoints() const;
    const int& getDamage() const;
    const int& getHp() const;

    //functions
    void loseHp(const int value);
    void updatePoint();
    void update();
    void render(sf::RenderTarget* target);
};