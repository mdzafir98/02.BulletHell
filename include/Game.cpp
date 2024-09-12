#include "Game.h"

void Game::initWindow(){
    window = new sf::RenderWindow(sf::VideoMode(512,512), "Game", sf::Style::Close | sf::Style::Titlebar);
    window->setFramerateLimit(75.f);
    window->setVerticalSyncEnabled(false);
}

void Game::initTextures(){
    textures["BULLET"] = new sf::Texture;
    textures["BULLET"]->loadFromFile("Resources/Sprites/green-laser.png");
    textures["FIRE"] = new sf::Texture;
    textures["FIRE"]->loadFromFile("Resources/Sprites/boss-bullet-sprite.png");
}

void Game::initSound(){
    buffer1.loadFromFile("Audio/laserShoot.wav");
    laserSound.setBuffer(buffer1);
    laserSound.setVolume(20.f);

    buffer2.loadFromFile("Audio/enemyDeath.wav");
    deathSound.setBuffer(buffer2);
    deathSound.setVolume(20.f);

    buffer3.loadFromFile("Audio/damaged.mp3");
    damageSound.setBuffer(buffer3);
    damageSound.setVolume(60.f);

    buffer4.loadFromFile("Audio/fireballAttack.wav");
    fireSound.setBuffer(buffer4);
    fireSound.setVolume(20.f);
}

void Game::initMusic(){
    musics["MAINMUSIC"] = new AudioManager("Audio/Orbital Colossus.mp3",30.f);
    musics["BOSSMUSIC"] = new AudioManager("Audio/boss-music.mp3",30.f);
    //updateMusic();
}

void Game::initSystems(){
    gameState =false;
    points = 0;
    bulletDamage =2;
}

void Game::initGUI(){
    //load font from file
    if (!font.loadFromFile("Resources/Fonts/Pixel Sans Serif Condensed.ttf")){
        std::cout << "GAME::INITGUI::Failed to load font!" << "\n";
    }

    //start text
    startText.setFont(font);
    startText.setCharacterSize(15.f);
    startText.setFillColor(sf::Color::White);
    startText.setOutlineColor(sf::Color::Black);
    startText.setOutlineThickness(2.f);
    startText.setString("SKY SHOOTER!\nEnter: Start\nWASD: Control\nLeft-click: Shoot");
    startText.setPosition(window->getSize().x/2.f - gameoverText.getGlobalBounds().width/2.f, 
                            window->getSize().y/2.f - gameoverText.getGlobalBounds().height/2.f);

    //init point text
    pointText.setFont(font);
    pointText.setCharacterSize(15);
    pointText.setFillColor(sf::Color::White);
    pointText.setOutlineColor(sf::Color::Black);
    pointText.setOutlineThickness(2.f);
    pointText.setString("this is a test");
    pointText.setPosition(40.f, 450.f);

    //victory text
    victoryText.setFont(font);
    victoryText.setCharacterSize(15.f);
    victoryText.setFillColor(sf::Color::White);
    victoryText.setOutlineColor(sf::Color::Black);
    victoryText.setOutlineThickness(2.f);
    victoryText.setString("VICTORY!");
    victoryText.setPosition(window->getSize().x/2-victoryText.getGlobalBounds().width/2.f,
                            window->getSize().y/2.f-victoryText.getGlobalBounds().height/2.f);

    //game over screen
    gameoverText.setFont(font);
    gameoverText.setCharacterSize(15.f);
    gameoverText.setFillColor(sf::Color::Red);
    gameoverText.setOutlineColor(sf::Color::Black);
    gameoverText.setOutlineThickness(2.f);
    gameoverText.setString("GAME OVER!\nR: Restart\nESC: Exit game");
    gameoverText.setPosition(window->getSize().x/2.f - gameoverText.getGlobalBounds().width/2.f, 
                            window->getSize().y/2.f - gameoverText.getGlobalBounds().height/2.f);

    //init player hp bar gui
    playerHpBar.setSize(sf::Vector2f(100.f, 10.f));
    playerHpBar.setFillColor(sf::Color(0,200,0));
    playerHpBar.setOutlineColor(sf::Color::Black);
    playerHpBar.setOutlineThickness(2.f);
    playerHpBar.setPosition(40.f,480.f);
    playerHpBarBack =playerHpBar;
    playerHpBarBack.setFillColor(sf::Color(25,25,25,200));

    //init boss hp bar gui
    bossHpBar.setSize(sf::Vector2f(400.f,10.f));
    bossHpBar.setFillColor(sf::Color(0,200,0));
    bossHpBar.setOutlineColor(sf::Color::Black);
    bossHpBar.setOutlineThickness(2.f);
    bossHpBarBack =bossHpBar;
    bossHpBarBack.setFillColor(sf::Color(25,25,25,200));
    bossHpBar.setPosition(40.f,20.f);
}

void Game::initEnemies(){
    spawnTimerMax =50.f;
    spawnTimer =spawnTimerMax;
    boss =new Boss();
    boss->setPos(rand()%500+50.f,-60.f);
}

void Game::initPlayer(){
    player = new Player();
}

void Game::initWorld(){
    bg =new Background(window->getSize().x, window->getSize().y);
    gameOverOverly.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    gameOverOverly.setFillColor(sf::Color(25,25,25,200));
}

void Game::resetMusic(){
    //reset audio flags
    g =true;
    b =false;
    musics["BOSSMUSIC"]->stopAudio();
}

void Game::saveScore(float score){
    std::ifstream stream("scores.txt");
    std::string line;
    std::getline(stream,line);
    float x;
    stream >> x;
    stream.close();
    if (score>x){
        std::ofstream filescore;
        filescore.open("scores.txt",std::ios::out);
        filescore << "Highscore:\n" << score << std::endl;
        filescore.close();
    }
}

Game::Game(){
    initWindow();
    initTextures();
    initSound();
    initMusic();
    initPlayer();
    initWorld();
    initSystems();
    initGUI();
    initEnemies();
}

Game::~Game(){
    //free up memory after game ends
    delete window;
    delete player;
    delete bg;
    delete boss;

    for (auto& i:musics){
        delete i.second;
    }
    for (auto& i:textures){
        delete i.second;
    }
    for (auto* i:bullets){
        delete i;
    }
    for (auto* i:enemies){
        delete i;
    }
    for (auto* i:fires){
        delete i;
    }
}

//functions
void Game::run(){
    while (window->isOpen()){
        updatePollevents();
        if (player->getHp() > 0){
            update();
        }
        render();
    }
}

void Game::updatePollevents(){
    sf::Event e;
    while (window->pollEvent(e)){
        if (e.type == sf::Event::Closed){
            window->close();
        }
        if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape){
            window->close();
        }
        //restart the game
        if (gameState == false && e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::R){
            player->setHp(player->getHpMax());
            points =0;
            player->setPosition(400.f,400.f);
            boss->setPos(50.f,-60.f);
            resetMusic();
        }
        if (gameState == false && e.type ==sf::Event::KeyPressed && e.key.code ==sf::Keyboard::Enter){
            gameState =true;
            // resetMusic();
        }
    }
}

void Game::updateInput(){
    //move player using wasd
    bool p =false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        player->move(-1.f,0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        player->move(1.f,0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        player->move(0.f,-1.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        player->move(0.f,1.f);
    }
    //vector to store the bullets
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && player->canAttack(10.f)){
        bullets.push_back(new Bullet(textures["BULLET"], player->getPos().x + player->getBounds().width/2, 
                            player->getPos().y, 0.f, -1.f, 10.f, 0.05f));
        laserSound.play();
    }
}

void Game::updateGUI(){
    std::stringstream ss;
    ss << "POINTS: " << points;
    pointText.setString(ss.str());

    //player hp
    float hpPercent =static_cast<float>(player->getHp())/player->getHpMax();
    playerHpBar.setSize(sf::Vector2f(100.f*hpPercent, playerHpBar.getSize().y));

    //boss hp
    float bossHpPercent =static_cast<float>(boss->getHp())/boss->getHpMax();
    bossHpBar.setSize(sf::Vector2f(400.f*bossHpPercent, bossHpBar.getSize().y));
}

void Game::updateMusic(){
    //normal gameplay music
    if (points<=30){
        musics["MAINMUSIC"]->playAudio(true);
    }
    //boss gameplay music
    if (points>30){
        musics["MAINMUSIC"]->stopAudio();
        musics["BOSSMUSIC"]->playAudio(true);
        std::cout << "boss time!" 
            << std::endl;
    }
}

void Game::updateWorld(){
    bg->update(7.5f);
}

void Game::updateBullet(){
    unsigned bulletCounter =0;
    for (auto* bullet:bullets){
        bullet->update();

        //delete the bullet which goes offscreen
        if (bullet->getBounds().top + bullet->getBounds().height <0.f){
            delete bullets.at(bulletCounter);
            bullets.erase(bullets.begin() + bulletCounter);
            --bulletCounter;
        }
        ++bulletCounter;
    }
}

void Game::updateEnemies(){
    //spawning enemies in the screen
    spawnTimer +=0.5f;
    if (spawnTimer >= spawnTimerMax){
        enemies.push_back(new Enemy(rand()%window->getSize().x-20.f, -100.f));
        spawnTimer =0.f;
    }

    unsigned enemyCounter =0;
    for (auto* enemy:enemies){
        enemy->update();

        //remove the enemies that hit the bottom of the window
        if (enemy->getBounds().top > window->getSize().y){
            delete enemies.at(enemyCounter);
            enemies.erase(enemies.begin() + enemyCounter);
            --enemyCounter;
        }

        //remove the enemies that hit the player also
        if (enemy->getBounds().intersects(player->getBounds())){
            //player lose hp
            damageSound.play();
            player->loseHp(enemies.at(enemyCounter)->getDamage());
            delete enemies.at(enemyCounter);
            enemies.erase(enemies.begin() + enemyCounter);
            --enemyCounter;
        }
        ++enemyCounter;
    }
}

void Game::updateBoss(){
    //moving the boss
    boss->update(player->getPos().x);

    //if player hits the boss, instant death
    if (boss->getBounds().intersects(player->getBounds())){
        deathSound.play();
        player->setHp(0.f);
    }
    //function occurs every delta seconds ->for shooting behaviour
    elapsed +=clock.restart();
    while (elapsed>=delta){
        fires.push_back(new Fire(textures["FIRE"], boss->getPos().x, boss->getPos().y, 5.f, 0.5f, 
                player->getPos().x, player->getPos().y));
        fireSound.play();
        elapsed -=delta;
    }
}

void Game::updateBossBullet(){
    unsigned fireCounter =0;
    for (auto* fire:fires){
        //move the bullet
        fire->update();

        //delete the bullet that exits the window
        if (fire->getBounds().top>window->getSize().y){
            delete fires.at(fireCounter);
            fires.erase(fires.begin() + fireCounter);
            --fireCounter;
            std::cout << "FireCounter: " << fires.size() << "\n";
        }
        ++fireCounter;
    }
}

void Game::updateCollision(){
    if (player->getBounds().left < 0.f){
        player->setPosition(0.f,player->getBounds().top);
    }
    if (player->getBounds().left + player->getBounds().width > window->getSize().x){
        player->setPosition(window->getSize().x - player->getBounds().width, player->getBounds().top);
    }
    if (player->getBounds().top + player->getBounds().height > window->getSize().y){
        player->setPosition(player->getBounds().left, window->getSize().y - player->getBounds().height);
    }
    if (player->getBounds().top < 0.f){
        player->setPosition(player->getBounds().left,0.f);
    }
}

void Game::updateCombat(){
    for (int i =0; i <enemies.size(); ++i){
        bool enemy_deleted =false;

        //killing enemies with bullet attack
        for (int k = 0; (k < bullets.size()) && (enemy_deleted ==false); k++){
            if (enemies[i]->getBounds().intersects(bullets[k]->getBounds())){
                damageSound.play();
                enemies[i]->loseHp(bulletDamage);
                delete bullets.at(k);
                bullets.erase(bullets.begin() +k);

                if (enemies[i]->getHp()<=0){
                    delete enemies.at(i);
                    enemies.erase(enemies.begin()+i);
                    points += enemies[i]->getPoints();
                    deathSound.play();
                    enemy_deleted =true;
                }
            }
        }
    }
    //check collision with boss bullet and player
    for (int i =0; i<fires.size(); ++i){
        if (fires[i]->getBounds().intersects(player->getBounds())){
            deathSound.play();
            delete fires.at(i);
            fires.erase(fires.begin()+i);
            player->loseHp(2.f);
        }
    }

    //damaging and killing the boss
    for (int i=0; i<bullets.size(); i++){
        if (boss->getBounds().intersects(bullets[i]->getBounds())){
            damageSound.play();
            boss->loseHp(bulletDamage);
            delete bullets.at(i);
            bullets.erase(bullets.begin()+i);
            if (boss->getHp()<=0){
                points += boss->getHpMax();
                deathSound.play();
            }
        }
    }
}

void Game::update(){
    updateWorld();
    if (gameState){
        updateInput();
        player->update();
        updateCollision();
        updateBullet();
        updateGUI();
        updateCombat();

        if (g){
            g =false;
            musics["MAINMUSIC"]->playAudio(true);
        }
        //normal gameplay
        if (points<30){
            updateEnemies();
            updateBossBullet();
        }
        //boss fight
        if (points>=30 && boss->getHp()>0){
            updateBoss();
            updateBossBullet();
            if (!b){
                musics["MAINMUSIC"]->stopAudio();
                b=true;
                musics["BOSSMUSIC"]->playAudio(true);
            }
        }
    }
}

void Game::renderGUI(){
    window->draw(pointText);
    window->draw(playerHpBarBack);
    window->draw(playerHpBar);
    if (points>=30){
        window->draw(bossHpBar);
    }
}

void Game::render(){
    window->clear(sf::Color::Black);
    bg->render(window);

    //intro screen
    if (!gameState){
        window->draw(startText);
    }

    //gameplay session
    if (gameState){
        player->render(*window);
        //render bullet in the window
        for (auto* bullet:bullets){
            bullet->render(window);
        }
        //render the enemies in the window
        for (auto* enemy:enemies){
            enemy->render(window);
        }
        for (auto* fire:fires){
            fire->render(window);
        }
        //summon the boss
        if (points>=30){
            boss->render(window);
        }
        renderGUI();
    }
    //victory screen
    if (boss->getHp()<=0){
        gameState =false;
        window->draw(gameOverOverly);
        window->draw(victoryText);
        saveScore(points);
    }

    //game over screen
    if (player->getHp()<=0){
        gameState =false;
        window->draw(gameOverOverly);
        window->draw(gameoverText);
        saveScore(points);
    }
    window->display();
}