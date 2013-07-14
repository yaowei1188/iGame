/******************************************************************************
文件名: inetaddress.cpp
编写者: csdn_viva@foxmail.com ccnet1.0
编写日期: 2012-5-27
功能描述: 地址封装
******************************************************************************/
#include "inetaddress.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	#pragma comment(lib, "Ws2_32.lib")
#endif

// Constructions
CInetAddress::CInetAddress()
{
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS )
    sin_len = sizeof(struct sockaddr_in);
#endif
	sin_family = AF_INET;
	sin_addr.s_addr = INADDR_ANY;
	sin_port = 0;
	memset(sin_zero, 0, 8);
}

// Constructions from ip and port
CInetAddress::CInetAddress(const char* ip, unsigned short port)
{
	sin_family = AF_INET;
	sin_addr.s_addr = inet_addr(ip);
	sin_port = htons(port);
	memset(sin_zero, 0, 8);
}

// Constructions from struct sockaddr
CInetAddress::CInetAddress(const struct sockaddr * addr)
{
	memcpy(&this->sin_family, addr, sizeof(struct sockaddr));
}

// Deconstructions
CInetAddress::~CInetAddress(void)
{
}

//Returns the raw IP address of this CInetAddress object. 
CInetAddress::operator struct sockaddr*()
{
#if ( CC_TARGET_PLATFORM != CC_PLATFORM_IOS )
	return (struct sockaddr *)(&this->sin_family);
#else
	return (struct sockaddr *)(&this->sin_len);
#endif
}

//Returns the raw IP address of this CInetAddress object. 
CInetAddress::operator const struct sockaddr*() const
{
#if ( CC_TARGET_PLATFORM != CC_PLATFORM_IOS )
	return (const struct sockaddr *)(&this->sin_family);
#else
	return (const struct sockaddr *)(&this->sin_len);
#endif
}

//Returns the IP address string in textual presentation form. 
const char* CInetAddress::GetHostAddress() const
{
	static char addr[64];
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	sprintf_s(addr, 64, "%s:%u", inet_ntoa(sin_addr), GetPort());
#else
	snprintf(addr, 64, "%s:%u", inet_ntoa(sin_addr), GetPort());
#endif
	return addr;
}

const char* CInetAddress::GetIP() const
{
	return inet_ntoa(sin_addr);
}

//Returns the port
unsigned short CInetAddress::GetPort() const
{
	return ntohs(sin_port);
}

//Set IP
void CInetAddress::SetIP(const char* ip)
{
	sin_addr.s_addr = inet_addr(ip);
}

//Set IP
void CInetAddress::SetIP(unsigned int ip)
{
	sin_addr.s_addr = ip;
}

//Set port
void CInetAddress::SetPorT(unsigned short port)
{
	sin_port = htons(port);
}

//Set domain
void CInetAddress::SetHost(const char* name)
{
	hostent* h = gethostbyname(name);
	if(h != NULL)
	{
		sin_addr.s_addr = *((u_long *)h->h_addr_list[0]);
	}
}

//Get length of address
int CInetAddress::GetLength() 
{ 
	return sizeof(sockaddr_in); 
}

