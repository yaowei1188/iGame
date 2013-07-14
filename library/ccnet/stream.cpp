/******************************************************************************
文件名: stream.cpp
编写者: csdn_viva@foxmail.com ccnet1.0
编写日期: 2012-5-27
功能描述: 封装了基本数据的数据流API
******************************************************************************/
#include <stdlib.h>
#include "stream.h"

//stream动态缓冲区的初始化大小
#define STREAM_BUFFER_SIZE 1024

///构造一个只写的流
CStream::CStream()
{
	this->m_pData = NULL;
	this->m_nReadIdx = 0;
	this->m_Buffer.reserve(STREAM_BUFFER_SIZE);
}

///构造一个只读的流
CStream::CStream(char* buffer, int len)
{
	this->m_pData = NULL;
	this->m_nReadIdx = 0;
	this->m_Buffer.reserve(STREAM_BUFFER_SIZE);
	for(int i = 0; i < len; i++)
	{
		this->m_Buffer.push_back(buffer[i]);
	}
}

///析构，释放所有资源
CStream::~CStream()
{
	if(m_pData != NULL)
	{
		delete m_pData;
	}

	if(!m_DeleteCharList.empty())
	{
		for(vector<char*>::iterator iter = m_DeleteCharList.begin(); iter != m_DeleteCharList.end(); iter++)
		{
			delete *iter;
		}
	}
}

///获取缓冲区长度
int	CStream::size()
{
	return (this->m_Buffer.size());
}

///组成一个数据包，返回缓冲区所有数据
char* CStream::flush()
{
	int nBufferSize = m_Buffer.size();
	if(nBufferSize != 0)
	{
		int nIdx = 0;
		this->m_pData = new char[nBufferSize];
		for(vector<char>::iterator iter = m_Buffer.begin(); iter != m_Buffer.end(); iter++, nIdx++)
		{
			this->m_pData[nIdx] = *iter;
		}
		return this->m_pData;
	}
	return NULL;
}

///写入一个Short型2字节
void CStream::writeShort(short num)
{
	this->m_Buffer.push_back( ((0xff00 & num) >> 8) );
	this->m_Buffer.push_back( (0xff & num) );
}

///写入一个int型4字节
void CStream::writeInt(int num)
{
	this->m_Buffer.push_back( ((0xff000000 & num) >> 24) );
	this->m_Buffer.push_back( ((0xff0000 & num) >> 16) );
	this->m_Buffer.push_back( ((0xff00 & num) >> 8) );
	this->m_Buffer.push_back( (0xff & num) );
}

///写入一个byte型char1字节
void CStream::writeByte(char ch)
{
	this->m_Buffer.push_back(ch);
}

///写入一个字符串，先写4字节长度，再写字符串
void CStream::writeUTF(const char* str)
{
	int size = strlen(str);
	this->writeInt(size);
	for(int i = 0; i < size; i++){
		this->m_Buffer.push_back(str[i]);
	}
}

///读一个4字节int
int	CStream::readInt()
{
	if( (m_nReadIdx + 3) < (int)m_Buffer.size())
	{
		int addr = m_Buffer[m_nReadIdx + 3] & 0xff;
		addr |= ((m_Buffer[m_nReadIdx + 2] << 8) & 0xff00);
		addr |= ((m_Buffer[m_nReadIdx + 1] << 16) & 0xff0000);
		addr |= ((m_Buffer[m_nReadIdx] << 24) & 0xff000000);

		m_nReadIdx += 4;
		return addr;
	}
	return 0;
}

///读一个2字节short
short CStream::readShort()
{
	if( (m_nReadIdx + 1) < (int)m_Buffer.size())
	{
		short addr = m_Buffer[m_nReadIdx + 1] & 0xff;
		addr |= ((m_Buffer[m_nReadIdx] << 8) & 0xff00);

		m_nReadIdx += 2;
		return addr;
	}
	return 0;
}

///读一个char
char CStream::readByte()
{
	if( (m_nReadIdx) < (int)m_Buffer.size())
	{
		char addr = m_Buffer[m_nReadIdx];
		m_nReadIdx += 1;
		return addr;
	}
	return 0;
}

///读一个字符串，先读4字节长度
char* CStream::readUTF()
{
	if( (m_nReadIdx + 3) < (int)m_Buffer.size())
	{
		int size = m_Buffer[m_nReadIdx + 3] & 0xff;
		size |= ((m_Buffer[m_nReadIdx + 2] << 8) & 0xff00);
		size |= ((m_Buffer[m_nReadIdx + 1] << 16) & 0xff0000);
		size |= ((m_Buffer[m_nReadIdx] << 24) & 0xff000000);

		if( ( (m_nReadIdx + 4) + (size - 1)) < (int)m_Buffer.size() )
		{
			m_nReadIdx += 4;
			char* pUTF = new char[size + 1];
			for(int i = 0; i < size; i++, m_nReadIdx++)
			{
				pUTF[i] = m_Buffer[m_nReadIdx];
			}
			pUTF[size] = '\0';
			m_DeleteCharList.push_back(pUTF);
			return pUTF;
		}
	}
	return NULL;
}
