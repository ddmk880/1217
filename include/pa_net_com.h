

#pragma once

typedef struct
{
	unsigned char	LocalIp[4]; // ����ip��ַ
	unsigned short	LocalPort;  // ���ؼ����˿ں�
	unsigned char	LocalMac[6];  	// �����ַ
	unsigned char   RemoteIp[4];// Զ��IP
	unsigned short  RemotePort; // Զ�̶˿�
	unsigned int	Baud;		// ����
	unsigned char   Reserve1;	// ����
}TPA_NETParam, *PTPA_NETParam;	// ��̫���ṹ��

