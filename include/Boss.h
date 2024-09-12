#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Boss{
private:
    sf::Sprite sprite;
    sf::Texture texture;
    int health;
    int healthMax;
    float speed;
    sf::RectangleShape bossHpBar;
    sf::RectangleShape bossHpBarBack;
protected:
    void initVariables();
    void initTexture();
    void initSprite();
    void initHpBar();
public:
    Boss();
    virtual ~Boss();

    //accessors
    const sf::FloatRect getBounds() const;
    const sf::Vector2f getPos() const;

    void setPos(float posx, float posy);

    //abilities
    void regainHp();
    void setHp(const int value);
    const int& getHp() const;
    const int& getHpMax() const;
    void loseHp(const int value);

    //functions
    void update(float playerx);
    void updateHp();
    void render(sf::RenderTarget* target);
};