#include "Background.h"

void Background::initTexture(){
    if (!texture.loadFromFile("Resources/Background/Cloudy Sky/Cloudy_Sky-Sunset_04-1024x512.png")){
        std::cout << "Error::Background.cpp::Cannot load texture!" << "\n";
    }
};

void Background::initSprite(){

}

Background::Background(unsigned int s_width, unsigned int s_height){
    initTexture();
    sf::Vector2u texture_size =texture.getSize();
    sf::Vector2f factor;
    width = s_width;
    height = s_height;
    factor.x =(float)s_width/texture_size.x;
    factor.y =(float)s_height/texture_size.y;

    for (sf::Sprite& frame:frames){
        frame.setTexture(texture);
        frame.setScale(factor);
    }

    frames.at(1).setPosition(0, 0-height);
}

void Background::update(float speed){
    sf::Vector2f pos;

    //move the background sprites down
    for (sf::Sprite& frame:frames){
        frame.move(0,speed);
        pos =frame.getPosition();

        if (pos.y > height){
            frame.setPosition(0,0-height+10.f);
        }
    }
}

void Background::render(sf::RenderTarget* target){
    for (sf::Sprite frame:frames){
        target->draw(frame);
    }
}