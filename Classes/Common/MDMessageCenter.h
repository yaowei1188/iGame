//
//  MDMessageCenter.h
//  mengdou
//
//  Created by ivan on 6/3/13.
//
//

#ifndef __mengdou__MessageCenter__
#define __mengdou__MessageCenter__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

#include "gloox.h"
#include "client.h"
#include "messagehandler.h"
#include "connectionlistener.h"
#include "messagesessionhandler.h"
#include "messageeventhandler.h"
#include "messageeventfilter.h"
#include "presencehandler.h"
#include "clientbase.h"
#include "disco.h"
#include "message.h"

using namespace std;
using namespace cocos2d;
using namespace cocos2d::extension;

class MDMessageCenter : 
	public gloox::MessageHandler,
	public gloox::ConnectionListener,
	public gloox::PresenceHandler
{
public:
	static MDMessageCenter *sharedInstance();

private:
	MDMessageCenter();
	virtual void handleMessage(const gloox::Message& stanza,gloox::MessageSession* session = 0 );
	virtual void onConnect();
	virtual void onDisconnect(gloox::ConnectionError e );
	virtual bool onTLSConnect(const gloox::CertInfo& info);
	virtual void handlePresence( const gloox::Presence& presence);

	static MDMessageCenter* _instance;

	gloox::Client* _client;
};

#endif
