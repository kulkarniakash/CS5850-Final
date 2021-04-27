#include "SoundComponent.hpp"
#include <stdio.h>

SoundComponent::SoundComponent() {
    
}

SoundComponent::~SoundComponent() {
    std::cout << "SoundComponent destructor called" << std::endl;
    for (auto it: m_mapSoundEffect) {
        Mix_FreeChunk(it.second);
    }
    
    for (auto it: m_mapBackgroundMusic) {
        Mix_FreeMusic(it.second);
    }
     
}

void SoundComponent::addBackgroundMusic(std::string const & filePath) {
    
    for (auto it: m_mapBackgroundMusic) {
        if (it.first == filePath) {
            std::cout << "Music already added \n";
            return;
        }
    }
    Mix_Music * bgm = Mix_LoadMUS(filePath.c_str());
    if (!bgm) {
        std::cout << "Music failed to load \n";
    }
    else {
        m_mapBackgroundMusic[filePath] = bgm;
    }
}

void SoundComponent::addSoundEffect(std::string const & filePath) {
    for (auto it: m_mapSoundEffect) {
        if (it.first == filePath) {
            std::cout << "Sound effect already added \n";
            return;
        }
    }
    Mix_Chunk * sound = Mix_LoadWAV(filePath.c_str());
    if (!sound) {
        std::cout << "Sound effect failed to load \n";
    }
    else {
        m_mapSoundEffect[filePath] =  sound;
    }
}

void SoundComponent::playSoundEffect(std::string const & filePath, int volume) {
    for (auto it: m_mapSoundEffect) {
        if (it.first == filePath) {
            Mix_PlayChannel(-1,it.second, 0);
            Mix_VolumeChunk(it.second, volume);
            return;
        }
    }
    std::cout << "Sound effect not found \n";
}

void SoundComponent::playBackgroundMusic(std::string const & filePath, int volume) {
    for (auto it: m_mapBackgroundMusic) {
        if (it.first == filePath) {
            if (Mix_PlayingMusic() == 0) {
                //Play the music
                Mix_VolumeMusic(volume);
                Mix_PlayMusic(it.second, -1);
                return;
            }
        }
    }
    std::cout << "Music not found \n";
}
