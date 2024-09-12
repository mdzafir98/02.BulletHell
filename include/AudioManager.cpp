#include "AudioManager.h"

float AudioManager::getVolume(){
    return m_volume;
}

AudioManager::AudioManager(std::string path, float volume){
    m_path =path;
    if (!m_audio.openFromFile(m_path)){
        std::cout << "Error::AudioManager::Cannot load audio file!" 
            << std::endl;
    } else{
        std::cout << "Sucessfully load audio!" << std::endl;
    }
    m_volume = volume;
    m_audio.setVolume(m_volume);
}

AudioManager::~AudioManager(){
    std::cout << "AudioManager: " << m_path << " destroyed!" 
        << std::endl;
}

const std::string AudioManager::getName() const{
    return m_path;
}

void AudioManager::playAudio(bool loop){
    m_audio.setLoop(loop);
    m_audio.play();
}

void AudioManager::stopAudio(){
    m_audio.stop();
}

void AudioManager::adjustVolume(float val){
    m_volume +=val;
}