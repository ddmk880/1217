/*********************************************************************
* ��Ȩ���� (C)2023, �ɶ�ָ����Ϊ�Ƽ����޹�˾��
*
* �ļ����ƣ� pacom.h
* ����ժҪ�� ͨ�ò�������
* ����˵���� ��
* ��ǰ�汾�� V1.00
* ��    �ߣ� Luohz
* �������ڣ� 2023��06��23��
* ������ڣ�
*
* �޸ļ�¼1��
* �޸����ڣ�
*    �� �� �ţ�V1.00
*    �� �� �ˣ�Luohz
*    �޸����ݣ�����
**********************************************************************/

#pragma once

//#pragma region ������������//vs����Ԥ�����﷨
#define PA_DLLEXPORT				__declspec(dllexport)
#define PA_FUNC						__stdcall
//#pragma endregion

//#pragma region �������ز���
#define PA_SUCCESS					0		// �ɹ�
#define PA_UNSUCCESS				-1		// ���ɹ�
#define PA_ERROR_PARAMETER_ILLEGAL	-2		// �Ƿ�����
#define PA_ERROR_UNKNOWN			-127	// �Ƿ�����
//#pragma endregion

//#pragma region ʹ�ܲ���
#define PA_ENABLE					0x01	// ʹ��
#define PA_DISABLE					0x00	// ʧ��
//#pragma endregion

//#pragma region ����ģʽ
#define PA_MODE_LEVEL				0x03	// ��ƽģʽ
#define PA_MODE_PULSE				0x04	// ����ģʽ
#define PA_MODE_UART				0x05	// ����ģʽ
//#pragma endregion

//#pragma region ��ƽģʽ
#define PA_LEVEL_LOW				0x00	// �͵�ƽ
#define PA_LEVEL_HIGH				0x01	// �ߵ�ƽ
//#pragma endregion

//#pragma region ����ģʽ
#define PA_PULSEMODE_SINGLE			0x00	// ���η���ģʽ
#define PA_PULSEMODE_PERIOD			0x01	// ���ڷ���ģʽ
#define PA_PRECISION_US				0x00	// ���徫�ȣ�us
#define PA_PRECISION_MS				0x01	// ���徫�ȣ�ms
#define PA_PRECISION_S				0x02	// ���徫�ȣ�s
#define PA_PRECISION_X				0x03	// ���徫�ȣ�x
//#pragma endregion

//#pragma region �ſز���
#define PA_GATING_LOW				0x00	// �ſص���Ч
#define PA_GATING_HIGH				0x01	// �ſظ���Ч
//#pragma endregion

//#pragma region ���ز���
#define PA_EDGE_RISING				0x00	// ������
#define PA_EDGE_FALING				0x01	// �½���
//#pragma endregion

//#pragma region �������
#define PA_DIRECTION_IN				0x00	// ���շ���
#define PA_DIRECTION_OUT			0x01	// �������
//#pragma endregion

//#pragma region �ֽ������
#define PA_BIG_ENDIAN				0x00	// ���ģʽ
#define PA_LITTLE_ENDIAN			0x01	// С��ģʽ
//#pragma endregion

//#pragma region TTL�ӿڲ���
#define PA_LEVELSTD_LVTTL			(0x20000000L)// LVTTL��ƽ��׼(3.3V), �͵�ƽ
#define PA_LEVELSTD_TTL				(0x20000001L)// TTL��ƽ��׼(5V), �ߵ�ƽ
//#pragma endregion

//#pragma region AD�ӿڲ���
#define PA_AD_RANGE_2Dot5V			(0x70000001L)// AD������Χ��2.5V
#define PA_AD_RANGE_5V				(0x70000002L)// AD������Χ��5V
#define PA_AD_RANGE_10V				(0x70000003L)// AD������Χ��10V
#define PA_AD_RATE_NULL				(0x71000000L)// AD�������� ��
#define PA_AD_RATE_2X				(0x71000001L)// AD��������2x
#define PA_AD_RATE_4X				(0x71000002L)// AD��������4x
#define PA_AD_RATE_8X				(0x71000003L)// AD��������8x
#define PA_AD_RATE_16X				(0x71000004L)// AD��������16x
#define PA_AD_RATE_32X				(0x71000005L)// AD��������32x
#define PA_AD_RATE_64X				(0x71000006L)// AD��������64x
//#pragma endregion

//#pragma region RS232ģʽ
#define PA_DUPLEXFLAG_HALF			0x00	// ��˫��
#define PA_DUPLEXFLAG_FULL			0x01	// ȫ˫��			
#define PA_STOPBIT_ONE				0x00	// 1λֹͣλ
#define PA_STOPBIT_TWO				0x01	// 2λֹͣλ
#define PA_PARITY_NONE				0x00	// ��У��
#define PA_PARITY_ODD				0x02	// ��У��
#define PA_PARITY_EVEN				0x03	// żУ��
//#pragma endregion

//#pragma region CAN�ӿڲ���
#define PA_CAN_BAUD_1000K			0x00	// CAN���� 1M
#define PA_CAN_BAUD_500K			0x01	// CAN���� 500K
#define PA_CAN_BAUD_200K			0x02	// CAN���� 200K
#define PA_CAN_BAUD_100K			0x03	// CAN���� 100K
#define PA_CAN_MATCHING_OPEN		0x00	// CAN����ƥ����� ��·		
#define PA_CAN_MATCHING_60			0x01	// CAN����ƥ����� 60ŷķ
#define PA_CAN_MATCHING_120			0x02	// CAN����ƥ����� 120ŷķ
//#pragma endregion

//#pragma region NET�ӿڲ���
#define PA_NET_BAUD_10M				(0x60000000L)	// 10M����
#define PA_NET_BAUD_100M			(0x60000001L)	// 100M����
#define PA_NET_BAUD_1000M			(0x60000002L)	// 1000M����
//#pragma endregion

//#pragma region �������ز���ͨ�ú궨��
#define PA_UNUSED(x) (void)(x)// ����δʹ�õĲ����澯
//#pragma endregion

#define PA_DATABUF_MAX_LENGTH		1230//���ݻ����������ȶ���

//#pragma region �������ز���ͨ�ú궨��
typedef  int(__stdcall *PA_UserHandle)(unsigned int device);
//#pragma endregion
