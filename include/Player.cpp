#include "Player.h"

void Player::initVariables(){
    movementSpeed = 7.5f;
    attackCooldownMax = 15.f;
    attackCooldown = attackCooldownMax;
    hpMax = 20.f;
    hp = hpMax;
}

void Player::initTexture(){
    //load a texture from file
    if (!texture.loadFromFile("Resources/Sprites/red-player.png")){
        std::cout << "ERROR::Player::initTexture::Could not load texture file!\n";
    }
}

void Player::initSprite(){
   sprite.setTexture(texture);
   sprite.setScale(0.1f,0.1f);
   sprite.setPosition(sf::Vector2f(400.f,400.f)); 
}

Player::Player(){
    initVariables();
    initTexture();
    initSprite();
}

Player::~Player(){
    std::cout << "Player is destroyed!" << std::endl;
}

const sf::FloatRect Player::getBounds() const{
    return sprite.getGlobalBounds();
}

const int& Player::getHp() const{
    return hp;
}

const int& Player::getHpMax() const{
    return hpMax;
}

void Player::setPosition(const float x, const float y){
    sprite.setPosition(x,y);
}

void Player::setHp(const int hp){
    this->hp = hp;
}

void Player::loseHp(const int value){
    this->hp -= value;
    if (hp<0){
        hp = 0;
    }
    //show player hp
    std::cout << "Player: " << hp << "\n";
}

void Player::addHp(const int value){
    hp += value;
    if (hp>hpMax){
        hp = hpMax;
    }
}

void Player::move(const float dirX, const float dirY){
    sprite.move(movementSpeed*dirX, movementSpeed*dirY);
}

const sf::Vector2f& Player::getPos() const{
    return sprite.getPosition();
}

const bool Player::canAttack(float attackCooldownModifier){
    attackCooldownMax = attackCooldownModifier;
    if (attackCooldown >= attackCooldownMax){
        attackCooldown = 0;
        return true;
    }
    return false;
}

void Player::updateAttack(){
    if (attackCooldown < attackCooldownMax){
        attackCooldown += 0.5f;
    }
}

void Player::update(){
    updateAttack();
}

void Player::render(sf::RenderTarget& target){
    target.draw(sprite);
}