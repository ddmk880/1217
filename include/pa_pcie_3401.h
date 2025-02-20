#ifndef __PA_PCIE_3401_H
#define __PA_PCIE_3401_H

#ifdef __cplusplus 
extern "C" {
#endif

#include "../include/pacom.h"
#include "../include/pa_srio_com.h"
#include "../include/pavipci.h"
#include <sal.h>
/*板卡信息宏定义*/
#define PA_MANFID										0x5041
#define PA_PCIE_3401									0x3401
//模块通道号定义
#define CH_1X_0											0x0
#define CH_1X_1											0x1
#define CH_1X_2											0x2
#define CH_1X_3											0x3
//模块通道号定义
#define CH_2X_0											0x0
#define CH_2X_1											0x1
//模块通道号定义
#define CH_4X_0											0x0


	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_3401_SRIO_Init(ViPSession _Out_ vi);
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_3401_SRIO_Close(ViSession _In_ vi);
									
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_3401_SRIO_SetRxAffinity(ViSession _In_ vi, ViUInt8 _In_ channel, ViUInt8 _In_ readDataThreadAffinityBit);
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_3401_SRIO_PreAllocRxBuffer(ViSession _In_ vi, ViUInt8 _In_ channel, ViUInt32 _In_ bufferSizeInM);
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_3401_SRIO_FreeRxBuffer(ViSession _In_ vi, ViUInt8 _In_ channel);

	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_3401_SRIO_SetNwriteParam(ViSession _In_ vi, ViUInt8 _In_ channel, struct PA_SRIO_NWRITEPAMETER nwriteparameter);
	
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_3401_SRIO_EnableSend(ViSession _In_ vi, ViUInt8 _In_ channel, ViUInt8 _In_ state);
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_3401_SRIO_EnableReceive(ViSession _In_ vi, ViUInt8 _In_ channel, ViUInt8 _In_ state);

	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_3401_SRIO_Send(ViSession _In_ vi, ViUInt8 _In_ channel, ViPUInt8 data, ViUInt32 _In_ len);
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_3401_SRIO_Receive(ViSession _In_ vi, ViUInt8 _In_ channel, ViPUInt8 data, ViPUInt32 _Out_ len);

	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_3401_SRIO_SetTxAutoData(ViSession _In_ vi, ViUInt32 _In_ frameNum, ViUInt32 _In_ frameLength);
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_3401_SRIO_LoopEn(ViSession _In_ vi, ViUInt8 _In_ state);

#ifdef __cplusplus 
}
#endif

#endif
