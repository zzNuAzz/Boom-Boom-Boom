#ifndef SOUND_H
#define SOUND_H

#include <SDL_mixer.h>
//sound 
extern Mix_Music* Music_Background;
extern Mix_Music* Music_Goodbye;
extern Mix_Music* Music_Start;
extern Mix_Music* Music_SoundGame;
extern Mix_Music* Music_Die;
extern Mix_Music* Music_Win;

extern Mix_Chunk* Chunk_Touch;
extern Mix_Chunk* Chunk_Bang;
extern Mix_Chunk* Chunk_Item;
extern Mix_Chunk* Chunk_SetBoom;

void LoadSound();

#endif // !SOUND_H