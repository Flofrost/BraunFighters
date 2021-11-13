#include <avr/pgmspace.h>
#include "SynthX.h"

Voice::Voice(void (*updateFunction_source)(const uint8_t)){
    updateFunction = updateFunction_source;
    options = 0x80;
    current_note = 0;
}

void Voice::update(){
    if(options&0x80){
        if(!current_note){
            if(options&1){
                current_note = pgm_read_byte(song);
                timeout = pgm_read_byte(song + (current_note << 1) + 1);
                updateFunction(pgm_read_byte(song + (current_note<<1)));
            }else{
                options &= 0x7F;
                updateFunction(60);
            }
        }

        if(!timeout && current_note){
            current_note--;
            updateFunction(pgm_read_byte(song + (current_note<<1)));
            timeout = pgm_read_byte(song + (current_note<<1) + 1);
        }
        
        timeout--;
    }
}

void Voice::playSong(const uint8_t* song_source){
    song = song_source;
    current_note = pgm_read_byte(song);
    timeout = pgm_read_byte(song + (current_note<<1) + 1);
    updateFunction(pgm_read_byte(song + (current_note<<1)));
}

void Voice::loop(const bool new_loop){
    options = (options&0xFE) | new_loop;
}