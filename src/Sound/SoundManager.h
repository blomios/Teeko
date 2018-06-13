#ifndef TEEKO_SOUNDMANAGER_H
#define TEEKO_SOUNDMANAGER_H

#include "SFML/Audio.hpp"

/**
 * Class to manage sounds in the game
 */
class SoundManager {
public:
    // Default constructor
    SoundManager();
    // Plays the sound of a marker being placed
    void PlayMarkerSound();
    // Plays the victory music when game is over
    void PlayVictoryMusic();
    // Plays the sound on button mouseover
    void PlayButtonClickSound();
private:
    // Buffers and sounds
    sf::SoundBuffer marker_sound_buffer_;
    sf::Sound marker_sound_;
    sf::SoundBuffer button_click_sound_buffer_;
    sf::Sound button_click_sound_;
    sf::Sound victory_music_;
    sf::SoundBuffer victory_music_buffer_;
    // Boolean value used to block victory music to play twice
    bool victory_sound_played_;
};


#endif //TEEKO_SOUNDMANAGER_H
