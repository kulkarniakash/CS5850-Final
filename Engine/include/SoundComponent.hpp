#ifndef SoundComponent_h
#define SoundComponent_h
#include <unordered_map>
#include <SDL_Headers.hpp>
#include <string>
#include <fstream>
#include <iostream>

/*!
 * @brief class that Represents a SoundComponent
 * Handles adding and playing sounds for that GameObject
 */
class SoundComponent {
public:
    
    //! @brief constructs our SoundComponent
    SoundComponent();
    
    //! @brief destructs our SoundComponent
    ~SoundComponent();
    
    /*!
     * @brief adds music in our background music map
     * @param filepath: string that represents the file path of our sound
     */
    void addBackgroundMusic(std::string const & filePath);
    
    /*!
     * @brief adds sounds in our sound effect map
     * @param filepath: string that represents the file path of our sound
     */
    void addSoundEffect(std::string const & filePath);
    
    /*!
     * @brief plays a sound effect from ou sound effectr map
     * @param filepath: string that represents the file path of our sound
     */
    void playSoundEffect(std::string const & filePath, int volume);
    
    /*!
     * @brief plays music in our background music map
     * @param filepath: string that represents the file path of our sound
     */
    void playBackgroundMusic(std::string const & filePath, int volume);
    
    
private:
    std::unordered_map<std::string, Mix_Chunk*> m_mapSoundEffect;
    std::unordered_map<std::string, Mix_Music*> m_mapBackgroundMusic;

};

#endif /* SoundComponent_h */
