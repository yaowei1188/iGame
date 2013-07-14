/******************************************************************************
文件名: socket.cpp
编写者: csdn_viva@foxmail.com ccnet1.0
编写日期: 2012-5-27
功能描述: 套接字功能封装类的定义，采用select无阻塞模型
******************************************************************************/
#include "socket.h"

///缺省构造函数
CSocket::CSocket()
{
	m_Socket = INVALID_SOCKET;
}

///析构函数
CSocket::~CSocket()
{
	if(m_Socket != INVALID_SOCKET)
	{
		Close();
	}
}

///创建IO对象
bool CSocket::Create()
{
//choose socket version of win32
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 0), &wsaData);
#endif

	m_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(m_Socket == INVALID_SOCKET)
	{
		//LOG_ERROR("创建套接字失败");
		return false;
	}

	//设置非阻塞模式
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	unsigned long ul = 1;
	int nRet = ioctlsocket(m_Socket, FIONBIO, (unsigned long*)&ul);
	if (nRet == SOCKET_ERROR)
	{
		Close();
		//LOG_ERROR("设置非阻塞模式失败");
		return false;
	}
#else
    int nFlags = fcntl(m_Socket, F_GETFL, 0);
    int nRet = fcntl(m_Socket, F_SETFL, nFlags | O_NONBLOCK);
	if (nRet == SOCKET_ERROR)
	{
		Close();
		//LOG_ERROR("设置非阻塞模式失败");
		return false;
	}
#endif
	//设置套接字无延时
	int nNoDelay = 1;
	if(setsockopt (m_Socket , IPPROTO_TCP , TCP_NODELAY , (char *)&nNoDelay , sizeof(nNoDelay)) == SOCKET_ERROR)
	{
		Close();
		//LOG_ERROR("设置套接字无延时失败");
		return false;
	}

	return true;
}

///请求连接一个地址，无阻塞
bool CSocket::Connect(const char* pIp, unsigned short uPort)
{
	if(pIp == NULL)
	{
		return false;
	}
	else
	{
		return Connect(inet_addr(pIp), uPort);
	}
}

///请求连接一个地址，无阻塞
bool CSocket::Connect(unsigned int uIp, unsigned short uPort)
{
	if(m_Socket == INVALID_SOCKET)
	{
		return false;
	}

	CInetAddress oAddr;
	oAddr.SetIP(uIp);
	oAddr.SetPorT(uPort);
    
	int nRet = connect(m_Socket, oAddr, oAddr.GetLength());
	if(nRet == 0)
	{
		return true;
	}
	else
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		int nError = WSAGetLastError();
		if(nError ==  WSAEWOULDBLOCK)
		{
			return true;
		}
		else
		{
			return false;
		}
#else
		if(nRet == SOCKET_ERROR && errno == EINPROGRESS)
		{
			return true;
		}
		else
		{
			return false;
		}
#endif
	}
}

///绑定本地一个端口
bool CSocket::Bind(const char* pIp, unsigned short uPort)
{
	return Bind(inet_addr(pIp), uPort);
}

///绑定本地一个端口
bool CSocket::Bind(unsigned int uIp, unsigned short uPort)
{
	if(m_Socket == INVALID_SOCKET)
	{
		return false;
	}

	CInetAddress oAddr;
	oAddr.SetIP(uIp);
	oAddr.SetPorT(uPort);

	return ::bind(m_Socket, oAddr, oAddr.GetLength()) == 0;
}

///开始监听（暂没有测试）
bool CSocket::Listen()
{
	if(m_Socket == INVALID_SOCKET)
	{
		return false;
	}

	return listen(m_Socket, 5) == 0;
}

///读取数据，无阻塞
int CSocket::Read(char* pBuffer, int nLen)
{
	if(m_Socket == INVALID_SOCKET)
	{
		return SOCKET_ERROR;
	}

	return recv(m_Socket, pBuffer, nLen, 0);
}

///写入数据，无阻塞
int CSocket::Write(char* pBuffer, int nLen)
{
	if(m_Socket == INVALID_SOCKET)
	{
		return SOCKET_ERROR;
	}
#if ( (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) )
	return send(m_Socket, pBuffer, nLen, 0);
#else
    return send(m_Socket, pBuffer, nLen, SO_NOSIGPIPE);
#endif
}

///主动断开连接
void CSocket::Disconnect()
{
	if(m_Socket != INVALID_SOCKET)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		shutdown(m_Socket, SD_BOTH);
#else
        shutdown(m_Socket, SHUT_RDWR);
#endif
	}
}

///关闭IO对象
void CSocket::Close()
{
	if(m_Socket != INVALID_SOCKET)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		closesocket(m_Socket);
#else
		close(m_Socket);
#endif
		m_Socket = INVALID_SOCKET;
	}
}

///检测是有数据可读
bool CSocket::IsReadable()
{
	fd_set	fd;
	struct timeval tv;

	FD_ZERO(&fd);
	FD_SET(m_Socket, &fd);

	tv.tv_sec = 0;
	tv.tv_usec = 0;

	if(select((int)(m_Socket + 1), &fd, NULL, NULL, &tv) > 0)
	{
		if(FD_ISSET(m_Socket, &fd))
		{
			return true;
		}
	}

	return false;
}

///检测是否可以写入数据
bool CSocket::IsWritable()
{
	fd_set	fd;
	struct timeval tv;

	FD_ZERO(&fd);
	FD_SET(m_Socket, &fd);

	tv.tv_sec = 0;
	tv.tv_usec = 0;

	if(select((int)(m_Socket + 1), NULL, &fd, NULL, &tv) >	0)
	{
		if(FD_ISSET(m_Socket, &fd))
		{
			return true;
		}
	}

	return false;
}

///检测是否已经建立连接
int CSocket::IsConnected()
{
	fd_set	fd;
	struct timeval tv;

	FD_ZERO(&fd);
	FD_SET(m_Socket, &fd);

	tv.tv_sec = 0;
	tv.tv_usec = 0;

	if(select((int)(m_Socket + 1), NULL, &fd, NULL, &tv) > 0)
	{
		if(FD_ISSET(m_Socket, &fd))
		{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
			return 1;
#else
			int error;
			socklen_t len = sizeof (error);
			if (getsockopt(m_Socket, SOL_SOCKET, SO_ERROR, &error, &len) < 0)
			{
				return -1;
			}
			//LINUX ECONNREFUSED 111
			//UNIX ECONNREFUSED 61
			if(error == ECONNREFUSED)
			{
				return -1;
			}
			return 1;
#endif
		}
	}
	return 0;
}

///检测是否接受到连接（暂没有测试）
bool CSocket::IsAcceptable()
{
	return IsReadable();
}
