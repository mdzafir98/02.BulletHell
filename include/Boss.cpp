#include "Boss.h"

void Boss::initVariables(){
    health =100;
    healthMax =health;
    speed =0.75f;
}

void Boss::initSprite(){
    sprite.setTexture(texture);
    sprite.setScale(0.5f,0.5f);
    sprite.setOrigin(texture.getSize().x/2,texture.getSize().y/2);
}

void Boss::initTexture(){
    if (!texture.loadFromFile("Resources/Sprites/purple-boss-sprite.png")){
        std::cout << "Error::Boss.cpp::Cannot load texture!" << std::endl;
    }
}

void Boss::initHpBar(){

}

Boss::Boss(){
    initVariables();
    initTexture();
    initSprite();
}

Boss::~Boss(){
    std::cout << "Boss is destroyed!" << std::endl;
}

const sf::FloatRect Boss::getBounds() const{
    return sprite.getGlobalBounds();
}

const sf::Vector2f Boss::getPos() const{
    return sprite.getPosition();
}

//to reset the boss position
void Boss::setPos(float posx, float posy){
    sprite.setPosition(posx,posy);
}

void Boss::regainHp(){
    health +=20;
}

void Boss::setHp(const int value){
    health = value;
}

const int& Boss::getHp() const{
    return health;
}

const int& Boss::getHpMax() const{
    return healthMax;
}

void Boss::loseHp(const int value){
    health -=value;
    if (health<0){
        health =0;
    }
}

//follow the direction of the player
void Boss::update(float playerx){
    //move the boss down to y=100.f
    if (sprite.getPosition().y<100.f){
        sprite.move(0.f,speed);
    }
    if (sprite.getPosition().x<playerx){
        sprite.move(speed,0.f);
    }
    if (sprite.getPosition().x>playerx){
        sprite.move(-speed,0.f);
    }
}

void Boss::updateHp(){

}

void Boss::render(sf::RenderTarget* target){
    target->draw(sprite);
}