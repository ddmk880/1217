

#pragma once

typedef struct
{
	unsigned char	LocalIp[4]; // 本地ip地址
	unsigned short	LocalPort;  // 本地监听端口号
	unsigned char	LocalMac[6];  	// 物理地址
	unsigned char   RemoteIp[4];// 远程IP
	unsigned short  RemotePort; // 远程端口
	unsigned int	Baud;		// 速率
	unsigned char   Reserve1;	// 保留
}TPA_NETParam, *PTPA_NETParam;	// 以太网结构体

