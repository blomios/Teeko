#include "SoundManager.h"

/**
 * Default constructor
 * Loads every sounds in buffer to reduce latency when calling a PlaySound function
 */
SoundManager::SoundManager() {
    marker_sound_buffer_.loadFromFile(R"(..\resources\sounds\move.wav)");
    marker_sound_.setBuffer(marker_sound_buffer_);
    victory_music_buffer_.loadFromFile(R"(..\resources\sounds\victory.wav)");
    victory_music_.setBuffer(victory_music_buffer_);
    victory_sound_played_ = false;
    button_click_sound_buffer_.loadFromFile(R"(..\resources\sounds\menu_click.wav)");
    button_click_sound_.setBuffer(button_click_sound_buffer_);
}

/**
 * Plays the sound of a marker being placed on the board
 */
void SoundManager::PlayMarkerSound() {
    marker_sound_.play();
}

/**
 * Plays a victory tone
 */
void SoundManager::PlayVictoryMusic() {
    if(!victory_sound_played_) {
        victory_music_.play();
        victory_sound_played_ = true;
    }
}

/**
 * Plays the sound when selecting a button
 */
void SoundManager::PlayButtonClickSound() {
    button_click_sound_.play();
}

