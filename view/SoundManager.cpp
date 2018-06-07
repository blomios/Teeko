#include "SoundManager.h"

SoundManager::SoundManager() {
    marker_sound_buffer_.loadFromFile(R"(..\resources\sounds\move.wav)");
    marker_sound_.setBuffer(marker_sound_buffer_);
}

void SoundManager::PlayMarkerSound() {
    marker_sound_.play();
}
