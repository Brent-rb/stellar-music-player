#pragma once

#include <miniaudio.h>

#include <string>

namespace stellar {
    /**
     * @brief The root of the project
     */
    class Stellar {
      private:
        ma_engine _engine;
        ma_sound _sound;
        ma_sound_group _group;
        ma_result _last_result;

        float _sound_fps;
        float _sound_length_seconds;
        ma_uint64 _sound_length_frames;

      public:
        Stellar();
        ~Stellar();

        bool init();
        bool playSong(std::string const& file_path);
        bool stop();
        bool start();
        bool seek(int seconds);
        float getCursorSeconds();
        float getDurationSeconds();
    };

}  // namespace stellar
