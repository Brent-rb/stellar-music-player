#include <algorithm>
#include <cmath>
#define MINIAUDIO_IMPLEMENTATION
#include <fmt/format.h>
#include <stellar/stellar.h>

#include <iostream>

using namespace stellar;

Stellar::Stellar() : _engine(), _group(), _last_result() {}

Stellar::~Stellar() { ma_engine_uninit(&_engine); }

bool Stellar::init() {
    _last_result = ma_engine_init(nullptr, &_engine);
    if (_last_result != MA_SUCCESS) {
        std::cerr << "[Error][" << _last_result << "] Engine initialisation failed" << std::endl;
        return false;
    }

    _last_result = ma_sound_group_init(
        &_engine, MA_SOUND_FLAG_NO_PITCH | MA_SOUND_FLAG_NO_SPATIALIZATION, nullptr, &_group);
    if (_last_result != MA_SUCCESS) {
        std::cerr << "[Error][" << _last_result << "] Group initialisation failed" << std::endl;
        return false;
    }

    return true;
}

bool Stellar::playSong(std::string const& file_path) {
    _last_result
        = ma_sound_init_from_file(&_engine, file_path.c_str(), 0, &_group, nullptr, &_sound);
    if (_last_result != MA_SUCCESS) {
        std::cerr << "[Error][" << _last_result << "] Song initialisation failed" << std::endl;
        return false;
    }

    _last_result = ma_sound_start(&_sound);
    if (_last_result != MA_SUCCESS) {
        std::cerr << "[Error][" << _last_result << "] Sound start failed" << std::endl;
        return false;
    }

    ma_sound_get_length_in_pcm_frames(&_sound, &_sound_length_frames);
    ma_sound_get_length_in_seconds(&_sound, &_sound_length_seconds);
    _sound_fps = static_cast<float>(_sound_length_frames) / _sound_length_seconds;

    return true;
}

bool Stellar::start() {
    _last_result = ma_engine_start(&_engine);
    if (_last_result != MA_SUCCESS) {
        std::cerr << "[Error][" << _last_result << "] Failed to start player" << std::endl;
        return false;
    }

    return true;
}

bool Stellar::stop() {
    _last_result = ma_engine_stop(&_engine);
    if (_last_result != MA_SUCCESS) {
        std::cerr << "[Error][" << _last_result << "] Failed to start player" << std::endl;
        return false;
    }

    return true;
}

bool Stellar::seek(int seconds) {
    ma_uint64 current_index;
    ma_sound_get_cursor_in_pcm_frames(&_sound, &current_index);

    ma_uint64 new_index = current_index + (std::round(seconds * _sound_fps));
    new_index = std::clamp(new_index, 0ull, _sound_length_frames);

    return ma_sound_seek_to_pcm_frame(&_sound, new_index) == MA_SUCCESS;
}

float Stellar::getCursorSeconds() {
    float seconds;
    ma_sound_get_cursor_in_seconds(&_sound, &seconds);

    return seconds;
}

float Stellar::getDurationSeconds() { return _sound_length_seconds; }