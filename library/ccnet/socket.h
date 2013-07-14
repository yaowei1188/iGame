/******************************************************************************
文件名: socket.h
编写者: csdn_viva@foxmail.com ccnet1.0
编写日期: 2012-5-27
功能描述: 套接字功能封装类的定义，采用select无阻塞模型
******************************************************************************/
#ifndef __CCNET_SOCKET_H__
#define __CCNET_SOCKET_H__

#include "inetaddress.h"

/******************************************************************************
类    名: CSocket
功能描述: 套接字功能封装类的定义，采用select无阻塞模型
******************************************************************************/
class CSocket
{
public:
	///构造函数，初始化SOCK
	CSocket();
	///析构时释放
	virtual ~CSocket();

public:
	///开始监听（暂没有测试）
	bool Listen();
	///创建IO对象
	bool Create();
	///关闭IO对象
	void Close();
	///主动断开连接
	void Disconnect();

	///请求连接一个地址，无阻塞
	bool Connect(const char* pIp, unsigned short uPort);
	///请求连接一个地址，无阻塞
	bool Connect(unsigned int uIp, unsigned short uPort);
	///绑定本地一个端口（暂没有测试）
	bool Bind(const char* pIp, unsigned short uPort);
	///绑定本地一个端口（暂没有测试）
	bool Bind(unsigned int uIp, unsigned short uPort);

	///读取数据，无阻塞
	int	Read(char* pBuffer, int nLen);
	///写入数据，无阻塞
	int	Write(char* pBuffer, int nLen);

public:
	///检测是有数据可读
	bool IsReadable();
	///检测是否可以写入数据
	bool IsWritable();
	///检测是否已经建立连接
	int	IsConnected();
	///检测是否接受到连接（暂没有测试）
	bool IsAcceptable();

protected:
	///IO对象
	SOCKET	m_Socket;
};

#endif // _SOCKET_INCLUDE_