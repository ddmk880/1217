#ifndef PA_PCIE_1804_H
#define PA_PCIE_1804_H

#include <sal.h>
#include "../include/pacom.h"
#include "../include/pavipci.h"

/*�忨��Ϣ�궨��*/
#define PA_MANFID					0x5041
#define PA_PCIE_1804				0x1804

#define PA_ADDR_RESET				(0x00000 + 0x000 + 0x00)   // ��λ�Ĵ���

#define PA_RESET_IO					0x01    // IO��λ
#define PA_RESET_OC					0x02	// OC��λ
#define PA_RESET_AD					0x04	// AD��λ

#define PA_1804_OC_MAX_CHANNEL		24	// OC���֧��ͨ���� // ����оƬ��ÿ��оƬ8ͨ����һ��24ͨ��
#define PA_1804_AD_MAX_CHANNEL		32	// AD���֧��ͨ���� // �ĸ�оƬ��ÿ��оƬ8ͨ����һ��32ͨ��
#define PA_1804_IO_MAX_CHANNEL		16	// IO���֧��ͨ���� // ����оƬ��ÿ��оƬ8ͨ����һ��16ͨ��

#ifdef __cplusplus
extern "C"
{
#endif

	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_Init(ViPSession vi);
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_Close(ViSession vi);

// IO
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_IO_Init(ViPSession _Out_ vi);	// ��ʼ��IO
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_IO_Reset(ViSession _In_ vi);		// ��λ
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_IO_Close(ViSession _In_ vi);		// �ر�

	// ģʽ+ʹ��
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_IO_SetParam(ViSession _In_ vi, ViUInt8 _In_ channel, ViUInt8 _In_ mode, ViUInt8 _In_ dire, ViUInt8 _In_ lvStd); // ����ģʽ����
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_IO_EnableSend(ViSession _In_ vi, ViUInt8 _In_ channel, ViUInt8 _In_ state);		// ��ͣͨ������ʹ��	
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_IO_EnableReceive(ViSession _In_ vi, ViUInt8 _In_ channel, ViUInt8 _In_ state);	// ��ͣͨ������ʹ��

	// ��ƽ
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_IO_SetLevel(ViSession _In_ vi, ViUInt8 _In_ channel, ViUInt8 _In_ level);		// ���õ�ƽ
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_IO_GetLevel(ViSession _In_ vi, ViUInt8 _In_ channel, ViPUInt8 _Out_ level);	// ��ȡ��ƽ

	// ����
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_IO_SetPulseMode(ViSession _In_ vi, ViUInt8 _In_ channel, ViUInt8 _In_ mode);// �����������ģʽ
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_IO_SetPulseIn(ViSession _In_ vi, ViUInt8 _In_ channel, ViUInt8 _In_ polarity, ViUInt8 _In_ precision);// ���������������
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_IO_SetPulseOut(ViSession _In_ vi, ViUInt8 _In_ channel, ViUInt8 _In_ polarity, ViUInt8 _In_ precision, ViUInt32 _In_ width, ViUInt32 _In_ period);// ���������������
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_IO_GetPluseIn(ViSession _In_ vi, ViUInt8 _In_ channel, ViPUInt32 _Out_ width, ViPUInt32 _Out_ period);// ��ȡ�����������
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_IO_SendSinglePulse(ViSession _In_ vi, ViUInt8 _In_ channel);	// ���͵�������
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_IO_StartPeriod(ViSession _In_ vi, ViUInt8 _In_ channel);		// �������ڷ���

// OC
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_OC_Init(ViPSession _Out_ vi);	// ��ʼ��OC
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_OC_Reset(ViSession _In_ vi);		// ��λ
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_OC_Close(ViSession _In_ vi);		// �ر�

	// ����ģʽ
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_OC_EnableSend(ViSession _In_ vi, ViUInt8 _In_ channel, ViUInt8 _In_ state); // ����ʹ��
	//ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_OC_EnableReceive(ViSession _In_ vi, ViUInt8 _In_ channel, ViUInt8 _In_ state); // ����ʹ��

	// ����
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_OC_SetPulseMode(ViSession _In_ vi, ViUInt8 _In_ channel, ViUInt8 _In_ mode); // ����ģʽ
	//ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_OC_SetPulseIn(ViSession _In_ vi, ViUInt8 _In_ channel, ViUInt8 _In_ polarity, ViUInt8 _In_ precision); // ������������
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_OC_SetPulseOut(ViSession _In_ vi, ViUInt8 _In_ channel, ViUInt8 _In_ polarity, ViUInt8 _In_ precision, ViUInt32 _In_ width, ViUInt32 _In_ period); // �����������
	//ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_OC_GetPluseIn(ViSession _In_ vi, ViUInt8 _In_ channel, ViPUInt32 _Out_ width, ViPUInt32 _Out_ period); //��ȡ�����������
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_OC_SendSinglePulse(ViSession _In_ vi, ViUInt8 _In_ channel);  // ���͵�����
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_OC_StartPeriod(ViSession _In_ vi, ViUInt8 _In_ channel);  // ��������ģʽ

// AD
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_AD_Init(ViPSession _Out_ vi);	// ��ʼ��AD
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_AD_Reset(ViSession _In_ vi);		// ��λ
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_AD_Close(ViSession _In_ vi);		// �ر�

	// �ɼ�
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_AD_SetRange(ViSession _In_ vi, ViUInt32 _In_ channel, ViUInt32 _In_ range);  // ����AD������Χ
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_AD_SetRate(ViSession _In_ vi, ViUInt32 _In_ channel, ViUInt8 _In_ rate);	// ���ù�������
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_AD_GetValue(ViSession _In_ vi, ViUInt8 _In_ channel, ViPReal64 _Out_ value); // ��ȡ����ֵ

#ifdef __cplusplus
}
#endif

#endif