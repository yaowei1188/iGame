//
//  MDSoundManager.h
//  mengdou
//
//  Created by ivan on 6/3/13.
//
//

#ifndef __MD_SOUND_MANAGER__
#define __MD_SOUND_MANAGER__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "common.h"

class MDSoundManager
{
public:
    static void preLoadSound();

	static void end();

	static void pauseBackgroundMusic();

	static void resumeBackgroundMusic();

	static void stopBackgroundMusic();
    
    static void playBackgroundMusic(std::string name = MUSIC_FILE,bool isLoop=true);

    static void playEffect(std::string name = MENU1_EFFECT);
};

#endif //__MD_SOUND_MANAGER__
