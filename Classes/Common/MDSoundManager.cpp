//
//  MDSoundManager.cpp
//  mengdou
//
//  Created by ivan on 6/3/13.
//
//

#include "MDSoundManager.h"

using namespace cocos2d;
using namespace CocosDenshion;

void MDSoundManager::preLoadSound()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	// preload background music and effect
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic( MUSIC_FILE );
	SimpleAudioEngine::sharedEngine()->preloadEffect( MENU1_EFFECT );
	SimpleAudioEngine::sharedEngine()->preloadEffect( ATTACK_EFFECT );

	// set default volume
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.5);
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.5);
#endif
}

void MDSoundManager::end()
{
	 SimpleAudioEngine::end();
}

void MDSoundManager::pauseBackgroundMusic()
{
	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

void MDSoundManager::resumeBackgroundMusic()
{
	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

void MDSoundManager::playBackgroundMusic(std::string name, bool isLoop)
{
	bool _blnSound = CCUserDefault::sharedUserDefault()->getBoolForKey("IsSound",true);
	if (!_blnSound)
	{
		return;
	}

	SimpleAudioEngine::sharedEngine()->playBackgroundMusic(name.c_str(),isLoop);
}

void MDSoundManager::stopBackgroundMusic()
{
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}

void MDSoundManager::playEffect(std::string name)
{
	bool _blnEffect = CCUserDefault::sharedUserDefault()->getBoolForKey("IsEffect",true);
	if (!_blnEffect)
	{
		return;
	}
	SimpleAudioEngine::sharedEngine()->playEffect(name.c_str());
}
