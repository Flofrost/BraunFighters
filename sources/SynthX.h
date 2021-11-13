#ifndef SYNTHX_H
#define SYNTHX_H

#include "assets/music.h"

class Voice{
    private:
        void (*updateFunction)(const uint8_t);
        const uint8_t* song;
        uint8_t options; // 0bPXXXXXXL -> P = Play  L = Loop
        uint8_t current_note, timeout;
    public:
        Voice(void (*updateFunction_source)(const uint8_t));
        void update();

        void playSong(const uint8_t* song_source);
        void playNote();

        void loop(const bool new_loop);
};

#endif