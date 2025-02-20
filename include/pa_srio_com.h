/*********************************************************************
* ��Ȩ���� (C)2023, �ɶ�ָ����Ϊ�Ƽ����޹�˾��
*
* �ļ����ƣ� pa_srio_com.h
* ����ժҪ�� ͨ�ò�������
* ����˵���� ��
* ��ǰ�汾�� V1.00
* ��    �ߣ� LHZ
* �������ڣ� 2023��03��11��
* ������ڣ�
*
* �޸ļ�¼1��
* �޸����ڣ�
*    �� �� �ţ�V1.00
*    �� �� �ˣ�LHZ
*    �޸����ݣ�����
**********************************************************************/

#pragma once

enum LOOPMODE
{
	LOOP_OFF = 0,
	LOOP_ON
};

struct PA_SRIO_NWRITEPAMETER
{
	unsigned int NwriteDestAddr;	// �Ӷ�������ַ
	unsigned int NwriteType;		// NWR����
	unsigned int NwriteSourceAddr_L;  // NWR�׵�ַ��32λ
	unsigned int NwriteSourceAddr_H;  // NWR�׵�ַ��2λ
	unsigned int NwritePackageLen;	// NWR������
};

struct PA_SRIO_NREADPAMETER
{
	unsigned int FrameLen;  // ����֡��(��λΪ�ֽ�)
	unsigned int FrameGap;  // ����֡���(��λΪus)
	unsigned int SyncHead_L;
	unsigned int SyncHead_H;
};