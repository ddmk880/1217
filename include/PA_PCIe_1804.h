#ifndef PA_PCIE_1804_H
#define PA_PCIE_1804_H

#include <sal.h>
#include "../include/pacom.h"
#include "../include/pavipci.h"

/*板卡信息宏定义*/
#define PA_MANFID					0x5041
#define PA_PCIE_1804				0x1804

#define PA_ADDR_RESET				(0x00000 + 0x000 + 0x00)   // 复位寄存器

#define PA_RESET_IO					0x01    // IO复位
#define PA_RESET_OC					0x02	// OC复位
#define PA_RESET_AD					0x04	// AD复位

#define PA_1804_OC_MAX_CHANNEL		24	// OC最大支持通道数 // 三个芯片，每个芯片8通道，一共24通道
#define PA_1804_AD_MAX_CHANNEL		32	// AD最大支持通道数 // 四个芯片，每个芯片8通道，一共32通道
#define PA_1804_IO_MAX_CHANNEL		16	// IO最大支持通道数 // 两个芯片，每个芯片8通道，一共16通道

#ifdef __cplusplus
extern "C"
{
#endif

	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_Init(ViPSession vi);
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_Close(ViSession vi);

// IO
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_IO_Init(ViPSession _Out_ vi);	// 初始化IO
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_IO_Reset(ViSession _In_ vi);		// 复位
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_IO_Close(ViSession _In_ vi);		// 关闭

	// 模式+使能
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_IO_SetParam(ViSession _In_ vi, ViUInt8 _In_ channel, ViUInt8 _In_ mode, ViUInt8 _In_ dire, ViUInt8 _In_ lvStd); // 设置模式参数
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_IO_EnableSend(ViSession _In_ vi, ViUInt8 _In_ channel, ViUInt8 _In_ state);		// 启停通道发送使能	
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_IO_EnableReceive(ViSession _In_ vi, ViUInt8 _In_ channel, ViUInt8 _In_ state);	// 启停通道接收使能

	// 电平
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_IO_SetLevel(ViSession _In_ vi, ViUInt8 _In_ channel, ViUInt8 _In_ level);		// 设置电平
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_IO_GetLevel(ViSession _In_ vi, ViUInt8 _In_ channel, ViPUInt8 _Out_ level);	// 获取电平

	// 脉冲
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_IO_SetPulseMode(ViSession _In_ vi, ViUInt8 _In_ channel, ViUInt8 _In_ mode);// 设置脉冲输出模式
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_IO_SetPulseIn(ViSession _In_ vi, ViUInt8 _In_ channel, ViUInt8 _In_ polarity, ViUInt8 _In_ precision);// 设置脉冲输入参数
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_IO_SetPulseOut(ViSession _In_ vi, ViUInt8 _In_ channel, ViUInt8 _In_ polarity, ViUInt8 _In_ precision, ViUInt32 _In_ width, ViUInt32 _In_ period);// 设置脉冲输出参数
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_IO_GetPluseIn(ViSession _In_ vi, ViUInt8 _In_ channel, ViPUInt32 _Out_ width, ViPUInt32 _Out_ period);// 获取脉冲输入参数
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_IO_SendSinglePulse(ViSession _In_ vi, ViUInt8 _In_ channel);	// 发送单次脉冲
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_IO_StartPeriod(ViSession _In_ vi, ViUInt8 _In_ channel);		// 开启周期发送

// OC
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_OC_Init(ViPSession _Out_ vi);	// 初始化OC
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_OC_Reset(ViSession _In_ vi);		// 复位
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_OC_Close(ViSession _In_ vi);		// 关闭

	// 设置模式
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_OC_EnableSend(ViSession _In_ vi, ViUInt8 _In_ channel, ViUInt8 _In_ state); // 发送使能
	//ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_OC_EnableReceive(ViSession _In_ vi, ViUInt8 _In_ channel, ViUInt8 _In_ state); // 接收使能

	// 脉冲
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_OC_SetPulseMode(ViSession _In_ vi, ViUInt8 _In_ channel, ViUInt8 _In_ mode); // 脉冲模式
	//ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_OC_SetPulseIn(ViSession _In_ vi, ViUInt8 _In_ channel, ViUInt8 _In_ polarity, ViUInt8 _In_ precision); // 设置脉冲输入
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_OC_SetPulseOut(ViSession _In_ vi, ViUInt8 _In_ channel, ViUInt8 _In_ polarity, ViUInt8 _In_ precision, ViUInt32 _In_ width, ViUInt32 _In_ period); // 设置脉冲输出
	//ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_OC_GetPluseIn(ViSession _In_ vi, ViUInt8 _In_ channel, ViPUInt32 _Out_ width, ViPUInt32 _Out_ period); //获取脉冲输入参数
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_OC_SendSinglePulse(ViSession _In_ vi, ViUInt8 _In_ channel);  // 发送单脉冲
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_OC_StartPeriod(ViSession _In_ vi, ViUInt8 _In_ channel);  // 启用周期模式

// AD
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_AD_Init(ViPSession _Out_ vi);	// 初始化AD
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_AD_Reset(ViSession _In_ vi);		// 复位
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_AD_Close(ViSession _In_ vi);		// 关闭

	// 采集
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_AD_SetRange(ViSession _In_ vi, ViUInt32 _In_ channel, ViUInt32 _In_ range);  // 设置AD采样范围
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_AD_SetRate(ViSession _In_ vi, ViUInt32 _In_ channel, ViUInt8 _In_ rate);	// 设置过采样率
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1804_AD_GetValue(ViSession _In_ vi, ViUInt8 _In_ channel, ViPReal64 _Out_ value); // 获取采样值

#ifdef __cplusplus
}
#endif

#endif