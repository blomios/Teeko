#include "SoundManager.h"

SoundManager::SoundManager() {
    marker_sound_buffer_.loadFromFile(R"(..\resources\sounds\move.wav)");
    marker_sound_.setBuffer(marker_sound_buffer_);
    victory_music_buffer_.loadFromFile(R"(..\resources\sounds\victory.wav)");
    victory_music_.setBuffer(victory_music_buffer_);
    victory_sound_played_ = false;
}

void SoundManager::PlayMarkerSound() {
    marker_sound_.play();
}

void SoundManager::PlayVictoryMusic() {
    if(!victory_sound_played_) {
        victory_music_.play();
        victory_sound_played_ = true;
    }
}
