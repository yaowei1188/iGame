/******************************************************************************
文件名: CNetBean.cpp
编写者: csdn_viva@foxmail.com ccnet1.0
编写日期: 2012-5-27
功能描述: 客户端网络对象，一个网络对象对应一个SOCKET
******************************************************************************/
#include "netbean.h"

///构造函数，初始化默认值
CNetBean::CNetBean():
m_nnPort(0),
m_nConnectStatus(ENULL)
{
#if CLIP_PACKET
	m_nRecvPackLength = 0;
#endif
}

///析构函数，释放所有资源
CNetBean::~CNetBean(){}


///设置于服务器连接的地址与端口
void CNetBean::setAddress(const char* ip, unsigned short port)
{
	this->m_nnPort = port;
	this->m_nnAddress = ip;
}

///开始无阻塞方式连接
bool CNetBean::connect()
{
	//there is connected or connecting 
	if(this->m_nConnectStatus == EConnected || this->m_nConnectStatus == EConnecting){
		return false;
	}
	//validate value
	if(this->m_nnAddress == "" || this->m_nnPort == 0) {
		return false;
	}
	if(!m_Sock.Create()) {
		return false;
	}
	if(!m_Sock.Connect(this->m_nnAddress.c_str(), this->m_nnPort)) {
		return false;
	}
	//set the connecting status
	this->m_nConnectStatus = EConnecting;
	//get the connect time of started.
	CCTime::gettimeofdayCocos2d(&m_ccConnectTime, NULL);
	//call back to virtual function 
	this->onCreate();

	return true;
}

///是否处于连接状态
bool CNetBean::isConnected()
{
	if(this->m_nConnectStatus == EConnected)
	{
		return true;
	}
	return false;
}

///关闭连接
void CNetBean::close()
{
	this->m_Sock.Close();
	this->m_nConnectStatus = EDisconnected;
}

///释放本网络对象
void CNetBean::release()
{
	this->close();
	delete this;
}

///往服务端写数据，无阻塞
void CNetBean::write(STREAM stream)
{
	//check status
	if( this->m_nConnectStatus != EConnected ) {
		return;
	}
	//check io is alive
	if( m_Sock.IsWritable() ) {
		//pack length
		int length = stream.size();
#if CLIP_PACKET
		char* data = stream.flush();
		char* buff = new char[ length + 4 ];
		if( length == 0 )
			return;
		//write length of pack to pack header
		buff[0] = ((0xff000000 & length) >> 24);
		buff[1] = ((0xff0000 & length) >> 16);
		buff[2] = ((0xff00 & length) >> 8);
		buff[3] = ((0xff & length));
		//write data
		for(int idx = 0; idx < length; idx++) {
			buff[idx+4] = data[idx];
		}
		length += 4;
#else
		char* buff = stream.flush();
#endif
		if( length != 0 ) {
			int nLen = m_Sock.Write( buff, length );
			if( nLen == SOCKET_ERROR ) {
				//set the connecting status
				this->m_nConnectStatus = EDisconnected;
				//call back to virtual function
				this->onDisconnected();
				//release socket
				this->close();
				//log
				CCLOG("## [DEBUG] Write Disconnected if(nLen == SOCKET_ERROR)");
			}
		}
#if CLIP_PACKET
		delete buff;
#endif
	} else {
		//log
		CCLOG("## [DEBUG] Write Disconnected if( m_Sock.IsWritable() )");
	}
}

///读数据
void CNetBean::read(char* buff, int len)
{
#if CLIP_PACKET
	//add data to buffer
	for(int idx = 0; idx < len; idx++ ) {
		this->m_vFrameDecodeBuffer.push_back(m_RecvBuffer[idx]);
	}
	//check pack recv
	if(this->m_nRecvPackLength == 0) {
		//read length of pack head
		if(this->m_vFrameDecodeBuffer.size() >= 4) {
			//read 4 char to int
			this->m_nRecvPackLength = 0;
			for(int i = 0; i < 4; i++) {
				this->m_nRecvPackLength <<= 8;
				this->m_nRecvPackLength |= (this->m_vFrameDecodeBuffer[i] & 0xff);
			}
		} else {
			//there is no 4 bytes in buffer
			return;
		}
	}
	int readable_size = this->m_vFrameDecodeBuffer.size() - 4;
	//if readable
	if(readable_size >= this->m_nRecvPackLength) {
		//to stream buffer
		char* buffer = new char[this->m_nRecvPackLength];
		//to delelte 4 char of pack length
		this->m_vFrameDecodeBuffer.pop_front();
		this->m_vFrameDecodeBuffer.pop_front();
		this->m_vFrameDecodeBuffer.pop_front();
		this->m_vFrameDecodeBuffer.pop_front();
		//read data from buffer
		for(int idx = 0; idx < m_nRecvPackLength; idx++) {
			buffer[idx] = this->m_vFrameDecodeBuffer.front();
			this->m_vFrameDecodeBuffer.pop_front();
		}
		//make stream to logic
		CStream stream(buffer, this->m_nRecvPackLength);
		//release temp buffer;
		delete buffer;
		//pack read successed.
		this->m_nRecvPackLength = 0;
		//call back to virtual function 
		this->onMessage(stream);
	}
#else
	//make stream to logic
	CStream stream(buff, len);
	//call back to virtual function 
	this->onMessage(stream);
#endif

}

///帧循环，读写数据
void CNetBean::drive()
{
	//connect successed
	if(this->m_nConnectStatus == EConnected){
		//Read Buffer
		while(m_Sock.IsReadable())
		{
			int nLen = m_Sock.Read(m_RecvBuffer, SOCK_RECVBUFFERSIZE);
			//check error
			if (nLen == 0 || nLen  == SOCKET_ERROR) {
				//change connecting status
				this->m_nConnectStatus = EDisconnected;
				//call back to virtual function
				this->onDisconnected();
				//release socket
				this->close();
				//stop while and loop;
				break;
			} else {
				//read data
				this->read(m_RecvBuffer, nLen);
			}
		}
	}
	//sock was keeping connecting status
	else if (this->m_nConnectStatus == EConnecting) {
		//check connected status of unblock socket
		int nRet = this->m_Sock.IsConnected();	
		if (nRet == 1) {
			//set the connecting status
			this->m_nConnectStatus = EConnected;
			//call back to virtual function
			this->onConnected();
		} else if (nRet < 0) {	//error
			//set the connecting status
			this->m_nConnectStatus = EConnectError;
			//call back to virtual function
			this->onConnectError();
			//close socket
			this->close();
		} else {
			//if it didn't finish the work at time
			struct cc_timeval ccTimeNow;
			CCTime::gettimeofdayCocos2d(&ccTimeNow, NULL);
			if(ccTimeNow.tv_sec - m_ccConnectTime.tv_sec >= SOCK_CONNECT_TIMEOUT){
				//set the connecting status
				this->m_nConnectStatus = EConnectTimeout;
				//call back to virtual function
				this->onConnectTimeout();
				//release socket
				this->close();
			}
		}
	}
}
