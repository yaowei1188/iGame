/******************************************************************************
文件名: stream.h
编写者: csdn_viva@foxmail.com ccnet1.0
编写日期: 2012-5-27
功能描述: 封装了基本数据的数据流API
******************************************************************************/
#ifndef __CCNET_STREAM_H__
#define __CCNET_STREAM_H__

#include <vector>
using namespace std;

/******************************************************************************
类    名: CStream
功能描述: 封装了基本数据的数据流API
******************************************************************************/
class CStream
{
public:
	///构造一个只写的流
	CStream();
	///构造一个只读的流
	CStream(char* buffer, int len);
	///析构，释放所有资源
	~CStream();

public:
	///写入一个Short型2字节
	void writeShort(short num);
	///写入一个int型4字节
	void writeInt(int num);
	///写入一个byte型char1字节
	void writeByte(char ch);
	///写入一个字符串，先写4字节长度，再写字符串
	void writeUTF(const char* str);
	///组成一个数据包，返回缓冲区所有数据
	char* flush();

public:
	///读一个4字节int
	int	readInt();
	///读一个2字节short
	short readShort();
	///读一个char
	char readByte();
	///读一个字符串，先读4字节长度
	char* readUTF();

public:
	///获取缓冲区长度
	int	size();

protected:
	///构成的字符串
	char* m_pData;
	///读取数据的光标
	int	m_nReadIdx;

	///缓冲区
	vector<char> m_Buffer;
	///待释放的字符串
	vector<char*> m_DeleteCharList;
};


#endif