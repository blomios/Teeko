#ifndef TEEKO_SOUNDMANAGER_H
#define TEEKO_SOUNDMANAGER_H

#include "SFML/Audio.hpp"

class SoundManager {
public:
    SoundManager();
    void PlayMarkerSound();
private:
    sf::SoundBuffer marker_sound_buffer_;
    sf::Sound marker_sound_;
};


#endif //TEEKO_SOUNDMANAGER_H
