#include "include/Game.h"

int main(){

    // sf::Music music;
    // if (!music.openFromFile("Audio/Orbital Colossus.mp3")){
    //     std::cout << "Error::main.cpp::Music not loaded!" << "\n";
    // }
    // //background music settings
    // music.setVolume(25.f);
    // music.setLoop(true);
    // music.play();

    Game game;
    game.run();
    return 0;
}