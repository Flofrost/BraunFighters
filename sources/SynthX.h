#ifndef SYNTHX_H
#define SYNTHX_H

#include "assets/music.h"

class Voice{
    private:
        void (*updateFunction)(const unsigned char);
        const unsigned char* song;
        unsigned char options; // 0bPXXXXXXL -> P = Play  L = Loop
        unsigned char current_note, timeout;
    public:
        Voice(void (*updateFunction_source)(const unsigned char));
        void update();

        void playSong(const unsigned char* song_source);
        void playNote();

        void loop(const bool new_loop);
};

#endif