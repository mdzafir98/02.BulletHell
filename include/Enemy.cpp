#include "Enemy.h"

void Enemy::initVariables(){
    //min =3, max =10
    pointCount = rand()%8 + 3;
    speed = static_cast<float>(pointCount/2);
    healthMax =static_cast<int>(pointCount);
    health =pointCount;
    damage =pointCount;
    points =pointCount;
}

void Enemy::initShape(){
    //generate random shapes for enemies
    shape.setRadius(pointCount +10);
    shape.setPointCount(pointCount);
    shape.setFillColor(sf::Color(rand()%255+1, rand()%255+1, rand()%255+1));
}

void Enemy::initTexture(){
    //load monster textures from file
    if (!texture1.loadFromFile("Resources/Sprites/red-monster-sprite.png")){
        std::cout << "Error::Enemy.cpp::Cannot load texture1!" << "\n";
    }
    if (!texture2.loadFromFile("Resources/Sprites/green-monster-sprite.png")){
        std::cout << "Error::Enemy.cpp::Cannot load texture2!" << "\n";
    }
    if (!texture3.loadFromFile("Resources/Sprites/blue-monster-sprite.png")){
        std::cout << "Error::Enemy.cpp::Cannot load texture3!" << "\n";
    }
}

void Enemy::initSprite(){
    if (pointCount>=3 && pointCount<6){ //3,4,5
        sprite.setTexture(texture1);
        sprite.setScale(0.5f,0.5f);
    }
    if (pointCount>=6 && pointCount<9){ //6,7,8
        sprite.setTexture(texture2);
        sprite.setScale(0.5f,0.5f);
    }
    if (pointCount>=9){
        sprite.setTexture(texture3); //9,10
        sprite.setScale(0.5f,0.5f);
    }
}

void Enemy::initPoint(){
    if (!font.loadFromFile("Resources/Fonts/Pixel Sans Serif Condensed.ttf")){
        std::cout << "Error::Enemy.cpp::Cannot load font!" << "\n";
    }
    healthText.setFont(font);
    healthText.setCharacterSize(15.f);
    healthText.setFillColor(sf::Color::White);
    healthText.setOutlineColor(sf::Color::Black);
    healthText.setOutlineThickness(2.f);
    auto s = std::to_string(pointCount);
    healthText.setString(s);
}

Enemy::Enemy(float posx, float posy){
    initVariables();
    initTexture();
    initSprite();
    initPoint();
    sprite.setPosition(posx,posy);
    healthText.setPosition(posx+sprite.getGlobalBounds().width/3,posy-15.f);
}

Enemy::~Enemy(){

}

const sf::FloatRect Enemy::getBounds() const{
    return sprite.getGlobalBounds();
}

const int& Enemy::getPoints() const{
    return points;
}

const int& Enemy::getDamage() const{
    return damage;
}

const int& Enemy::getHp() const{
    return health;
}

void Enemy::loseHp(const int value){
    health -=value;
    if (health<0){
        health =0;
    }
}

void Enemy::updatePoint(){
    std::stringstream ss;
    ss << health;
    healthText.setString(ss.str());
}

void Enemy::update(){
    updatePoint();
    sprite.move(0.f,speed);
    healthText.move(0.f,speed);
}

void Enemy::render(sf::RenderTarget* target){
    target->draw(sprite);
    target->draw(healthText);
}