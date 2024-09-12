#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

class Player{
private:
    sf::Sprite sprite;
    sf::Texture texture;

    float movementSpeed;

    float attackCooldown;
    float attackCooldownMax;

    int hp;
    int hpMax;

    //private functions
    void initVariables();
    void initTexture();
    void initSprite();

protected:


public:
    Player();
    virtual ~Player();

    //accessors
    const sf::FloatRect getBounds() const;
    const int& getHp() const;
    const int& getHpMax() const;

    //modifiers
    void setPosition(const float x, const float y);
    void setHp(const int hp);
    void loseHp(const int value);
    void addHp(const int value);

    //functions
    void move(const float dirX, const float dirY);
    const sf::Vector2f& getPos() const;
    const bool canAttack(float attackCooldownModifier);
    void updateAttack();
    void update();
    void render(sf::RenderTarget& target);
};