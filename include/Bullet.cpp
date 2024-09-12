#include "Bullet.h"

//superclass
Bullet::Bullet(sf::Texture* texture, float posx, float posy, 
    float dirx, float diry, float speed, float scale){
    shape.setTexture(*texture);
    shape.setScale(scale,scale);
    shape.setPosition(posx,posy);
    direction.x =dirx;
    direction.y =diry;
    m_speed =speed;
}

Bullet::~Bullet(){

}

sf::FloatRect Bullet::getBounds() const{
    return shape.getGlobalBounds();
}

void Bullet::update(){
    shape.move(m_speed*direction);
}

void Bullet::render(sf::RenderTarget* target){
    target->draw(shape);
}

//fireclass
Fire::Fire(sf::Texture* texture, float posx, float posy, 
        float speed, float scale, float px, float py){
    shape.setTexture(*texture);
    shape.setScale(scale,scale);
    shape.setPosition(posx,posy);
    m_angle = atan2(px-posx,py-posy);
    direction.x =sin(m_angle);
    direction.y =cos(m_angle);
    m_speed =speed;
}

Fire::~Fire(){

}

sf::FloatRect Fire::getBounds() const{
    return shape.getGlobalBounds();
}

//function overload
void Fire::update(){
    shape.move(m_speed*direction);
    // std::cout << m_angle << ": " << cos(m_angle) << " and " 
    //     << sin(m_angle) << std::endl;
}

void Fire::render(sf::RenderTarget* target){
    target->draw(shape);
}