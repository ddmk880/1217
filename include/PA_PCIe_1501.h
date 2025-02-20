#ifndef PA_PCIE_1501_H
#define PA_PCIE_1501_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <sal.h>
#include "../include/pacom.h"
#include "../include/pa_net_com.h"
#include "../include/pavipci.h"

/*板卡信息宏定义*/
#define PA_MANFID	0x5041
#define PA_PCIE_1501	0x1501

	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1501_NET_Init(ViPSession _Out_ vi);  // 初始化板卡
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1501_NET_Reset(ViSession _In_ vi);   // 复位板卡
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1501_NET_Close(ViSession _In_ vi);	// 关闭板卡

	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1501_NET_SetParam(ViSession _In_ vi, ViUInt8 _In_ channel, TPA_NETParam _In_ param);   // 设置参数
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1501_NET_EnableSend(ViSession _In_ vi, ViUInt8 _In_ channel, ViUInt8 _In_ state);	  // 发送使能
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1501_NET_EnableReceive(ViSession _In_ vi, ViUInt8 _In_ channel, ViUInt8 _In_ state);	  // 接收使能
	
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1501_NET_Send(ViSession _In_ vi, ViUInt8 _In_ channel, _In_ ViPUInt8 data, ViUInt32 _In_ len);  // 发送数据
        ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1501_NET_Receive(ViSession _In_ vi, ViUInt8 _In_ channel, _Out_ ViPUInt8 data, ViUInt32 _In_ maxLen, ViPUInt32 _Out_ len);// 接收数据

	// 发送相关
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1501_NET_SetSendFrameLength(ViSession _In_ vi, ViUInt8 _In_ channel, ViUInt32 _In_ length);			// 设置帧长
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1501_NET_SetSendFrameInterval(ViSession _In_ vi, ViUInt8 _In_ channel, ViUInt32 _In_ interval);		// 设置帧间隔  单位8ns
	
	// 接收相关
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1501_NET_SetReceiveTimeout(ViSession _In_ vi, ViUInt8 _In_ channel, ViUInt32 _In_ time);				// 设置接收超时

	// 自造数相关
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1501_NET_SetTxAutoData(ViSession _In_ vi, ViUInt32 _In_ frameNum, ViUInt32 _In_ frameLength);
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_1501_NET_LoopEn(ViSession _In_ vi, ViUInt8 _In_ state);

#ifdef __cplusplus
}
#endif

#endif
