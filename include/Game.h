#pragma once

#include <string>
#include <sstream>
#include <fstream>

#include <SFML/Audio.hpp>

#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Background.h"
#include "Boss.h"
#include "AudioManager.h"

class Game{
private:
    sf::RenderWindow* window;
    std::map<std::string, sf::Texture*> textures;

    //audio
    sf::SoundBuffer buffer1, buffer2, buffer3, buffer4;
    sf::Sound laserSound, deathSound, damageSound, fireSound;
    std::map<std::string, AudioManager*> musics;
    bool g =true;
    bool b =false;

    //player variables
    Player* player;
    sf::RectangleShape playerHpBar;
    sf::RectangleShape playerHpBarBack;

    //boss variables
    sf::RectangleShape bossHpBar;
    sf::RectangleShape bossHpBarBack;

    //vector store attacks
    std::vector<Bullet*> bullets;
    std::vector<Fire*> fires;

    //GUI
    sf::Font font;
    sf::Text startText;
    sf::Text pointText;
    sf::Text gameoverText;
    sf::Text victoryText;
    sf::RectangleShape gameOverOverly;

    //systems
    unsigned points;
    int bulletDamage;
    Background* bg;
    bool gameState;

    //time module
    sf::Clock clock;
    sf::Time timePerFrame =sf::seconds(1.f/60.f);
    sf::Time delta =sf::seconds(0.5f);
    sf::Time elapsed;
    float eSeconds = elapsed.asSeconds();

    //enemies
    Boss* boss;
    std::vector<Enemy*> enemies;
    float spawnTimer;
    float spawnTimerMax;

protected:
    //functions
    void initWindow();
    void initTextures();
    void initSound();
    void initMusic();
    void initSystems();
    void initGUI();
    void initEnemies();
    void initPlayer();
    void initWorld();
    
    void resetMusic();

public:
    Game();
    ~Game();

    //functions
    void run();

    //update
    void updatePollevents();
    void updateInput();
    void updateGUI();
    void updateMusic();
    void updateWorld();
    void updateBullet();
    void updateEnemies();
    void updateBoss();
    void updateBossBullet();
    void updateCollision();
    void updateCombat();
    void update();
    void saveScore(float score);

    //render
    void renderGUI();
    void render();
};