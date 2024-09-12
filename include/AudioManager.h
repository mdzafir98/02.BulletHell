#pragma once
#include <string>
#include <iostream>
#include <SFML/Audio.hpp>

class AudioManager{
private:
    sf::Music m_audio;
    std::string m_path;
protected:
    float m_volume{25.f};
    float getVolume();
public:
    AudioManager(std::string path, float volume);
    ~AudioManager();
    const std::string getName() const;
    void playAudio(bool loop);
    void stopAudio();
    void adjustVolume(float val);
};

class BufferManager:public AudioManager{

};