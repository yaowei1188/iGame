//
//  MDMessageCenter.cpp
//  mengdou
//
//  Created by ivan on 6/3/13.
//
//

#include "MDMessageCenter.h"

MDMessageCenter* MDMessageCenter::_instance = NULL;

MDMessageCenter::MDMessageCenter()
{
	gloox::JID jid( "bot@server/resource" );
	_client = new gloox::Client( jid, "password" );

	_client->disco()->setVersion( "messageTest", gloox::GLOOX_VERSION, "Linux" );              
	_client->disco()->setIdentity( "client", "bot" );

	gloox::StringList ca;
	ca.push_back( "/path/to/cacert.crt" );
	_client->setCACerts( ca );

	_client->registerMessageHandler(this);
	_client->registerConnectionListener(this);
	_client->registerPresenceHandler(this);
	_client->connect(false);
}

MDMessageCenter* MDMessageCenter::sharedInstance()
{
	if (_instance==NULL)
	{
		_instance = new MDMessageCenter();
	}
	return _instance;
}

void MDMessageCenter::handleMessage( const gloox::Message& msg,gloox::MessageSession* session)
{
	//    stanza.subject();
	//    CCLOG("%s",stanza.suboptarg);
	//    const gloox::JID from(stanza.from());
	//    gloox::Message msg(stanza.from(), "hello world","test" );
	//    j->send( msg );

	CCLOG( "type: %d, subject: %s, message: %s, thread id: %s\n", msg.subtype(),
		msg.subject().c_str(), msg.body().c_str(), msg.thread().c_str() );
}

void MDMessageCenter::onConnect()
{
	CCLOG( "connected!!!" );
}
void MDMessageCenter::onDisconnect(gloox::ConnectionError e )
{
	CCLOG( "message_test: disconnected: %d", e );
	delete(_client);
}
bool MDMessageCenter::onTLSConnect(const gloox::CertInfo& info)
{
	time_t from( info.date_from );
	time_t to( info.date_to );

	CCLOG( "status: %d\nissuer: %s\npeer: %s\nprotocol: %s\nmac: %s\ncipher: %s\ncompression: %s\n"
		"from: %s\nto: %s\n",
		info.status, info.issuer.c_str(), info.server.c_str(),
		info.protocol.c_str(), info.mac.c_str(), info.cipher.c_str(),
		info.compression.c_str(), ctime( &from ), ctime( &to ) );
	return true;

	return true;
}
void MDMessageCenter::handlePresence( const gloox::Presence& presence)
{

}