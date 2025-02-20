
#ifndef __PA_RS422_H
#define __PA_RS422_H

#define PA_RS422_PULSE_IN_CH1 0
#define PA_RS422_PULSE_IN_CH2 1
#define PA_RS422_PULSE_IN_CH3 2
#define PA_RS422_PULSE_IN_CH4 3
#define PA_RS422_PULSE_IN_CH5 8
#define PA_RS422_PULSE_IN_CH6 9
#define PA_RS422_PULSE_IN_CH7 10
#define PA_RS422_PULSE_IN_CH8 11

#define PA_RS422_PULSE_OUT_CH1 4
#define PA_RS422_PULSE_OUT_CH2 5
#define PA_RS422_PULSE_OUT_CH3 6
#define PA_RS422_PULSE_OUT_CH4 7
#define PA_RS422_PULSE_OUT_CH5 12
#define PA_RS422_PULSE_OUT_CH6 13
#define PA_RS422_PULSE_OUT_CH7 14
#define PA_RS422_PULSE_OUT_CH8 15

#define PA_RS422_SYNCSOURCE_IN	0 //Pulse from the outside of the device,device check the pulse
#define PA_RS422_SYNCSOURCE_OUT	1 //Pulse from the inside of the device,device send the pulse

#ifdef __cplusplus 
extern "C" {
#endif

#include "../include/pavipci.h"
#include "../include/pacom.h"

	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_4202_RS422_Init(OUT ViPSession hDevice);
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_4202_RS422_Close(IN ViSession hDevice);
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_4202_RS422_CloseChannel(IN ViSession hDevice, IN ViUInt8 channel);
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_4202_RS422_Reset(IN ViSession hDevice);
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_4202_RS422_SetChronous(IN ViSession hDevice, IN ViUInt8 source);
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_4202_RS422_GetChronous(IN ViSession hDevice, OUT ViPUInt8 source);
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_4202_RS422_SetSyncPluseEnable(IN ViSession hDevice, IN ViUInt8 syncpluseenable);
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_4202_RS422_SetSyncPluseMode(IN ViSession hDevice, IN ViUInt8 channel);

	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_4202_RS422_SetLevel(IN ViSession hDevice, IN ViUInt8 channel, IN ViUInt8 level);
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_4202_RS422_SetSyncEdge(IN ViSession hDevice, IN ViUInt8 channel, IN ViUInt8 edge);
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_4202_RS422_SetPulseIn(IN ViSession hDevice, IN ViUInt8 channel, IN ViUInt8 polarity, IN ViUInt8 precision);
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_4202_RS422_SetPulseOut(IN ViSession hDevice, IN ViUInt8 channel, IN ViUInt8 polarity, IN ViUInt8 precision, IN ViUInt32 width, IN ViUInt32 period);
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_4202_RS422_SetPulseMode(IN ViSession hDevice, IN ViUInt8 channel, IN ViUInt8 mode);
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_4202_RS422_SendSinglePulse(IN ViSession hDevice, IN ViUInt8 channel);
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_4202_RS422_StartPeriod(IN ViSession hDevice, IN ViUInt8 channel);

	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_4202_RS422_EnableSend(IN ViSession hDevice, IN ViUInt8 channel, IN ViUInt8 state);
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_4202_RS422_EnableReceive(IN ViSession hDevice, IN ViUInt8 channel, IN ViUInt8 state);

	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_4202_RS422_ReadLevel(IN ViSession hDevice, IN ViUInt8 channel, OUT ViPUInt8 level);
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_4202_RS422_ReadPulseIn(IN ViSession hDevice, IN ViUInt8 channel, OUT ViPUInt32 width, OUT ViPUInt32 period);

	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_4202_RS422_PluseStatus(IN ViSession hDevice, IN ViUInt8 channel, OUT ViPUInt8 en);
	ViStatus PA_DLLEXPORT PA_FUNC PA_PCIe_4202_RS422_ClearStatus(IN ViSession hDevice, IN ViUInt8 channel);

#ifdef __cplusplus 
}
#endif

#endif