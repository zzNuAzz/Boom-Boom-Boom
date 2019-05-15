#include "Sound.h"
Mix_Music* Music_Background = NULL;
Mix_Music* Music_SoundGame = NULL;
Mix_Music* Music_Goodbye = NULL;
Mix_Music* Music_Start = NULL;
Mix_Music* Music_Die = NULL;
Mix_Music* Music_Win = NULL;

Mix_Chunk* Chunk_Touch = NULL;
Mix_Chunk* Chunk_Bang = NULL;
Mix_Chunk* Chunk_Item = NULL;
Mix_Chunk* Chunk_SetBoom = NULL;

void LoadSound()
{
	//SoundMusic;
	Music_Background = Mix_LoadMUS("Bin/Sound/background.wav");
	Music_Goodbye = Mix_LoadMUS("Bin/Sound/byebye.wav");
	Music_Start = Mix_LoadMUS("Bin/Sound/start.wav");
	Music_SoundGame = Mix_LoadMUS("Bin/Sound/soundGame.wav");
	Music_Die = Mix_LoadMUS("Bin/Sound/die.wav");
	Music_Win = Mix_LoadMUS("Bin/Sound/win.wav");
	//Sound 
	Chunk_Touch = Mix_LoadWAV("Bin/Sound/Touch.wav");
	Chunk_Bang = Mix_LoadWAV("Bin/Sound/bang.wav");
	Chunk_Item = Mix_LoadWAV("Bin/Sound/item.wav");
	Chunk_SetBoom = Mix_LoadWAV("Bin/Sound/set_boom.wav");
}
