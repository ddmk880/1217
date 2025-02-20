#ifndef _PAVIPCI_H_
#define _PAVIPCI_H_

#ifdef __cplusplus 
extern "C" {
#endif

#include "../include/visatype.h"
#include "../include/visa.h"

/*- Resource Manager Functions and Operations -------------------------------*/

ViStatus _VI_FUNC  PaviOpenDefaultRM(ViPSession vi);
ViStatus _VI_FUNC  PaviFindRsrc		(ViSession sesn, ViConstString expr, ViPFindList vi,
									 ViPUInt32 retCnt, ViChar _VI_FAR desc[]);
ViStatus _VI_FUNC  PaviFindNext		(ViFindList vi, ViChar _VI_FAR desc[]);
ViStatus _VI_FUNC  PaviParseRsrc	(ViSession rmSesn, ViConstRsrc rsrcName,
									 ViPUInt16 intfType, ViPUInt16 intfNum);
ViStatus _VI_FUNC  PaviParseRsrcEx	(ViSession rmSesn, ViConstRsrc rsrcName, ViPUInt16 intfType,
									 ViPUInt16 intfNum, ViChar _VI_FAR rsrcClass[],
									 ViChar _VI_FAR expandedUnaliasedName[],
									 ViChar _VI_FAR aliasIfExists[]);
ViStatus _VI_FUNC  PaviOpen			(ViSession sesn, ViConstRsrc name, ViAccessMode mode,
									 ViUInt32 timeout, ViPSession vi);

/*- Resource Template Operations --------------------------------------------*/

ViStatus _VI_FUNC  PaviClose		(ViObject vi);
ViStatus _VI_FUNC  PaviSetAttribute	(ViObject vi, ViAttr attrName, ViAttrState attrValue);
ViStatus _VI_FUNC  PaviGetAttribute	(ViObject vi, ViAttr attrName, void _VI_PTR attrValue);
ViStatus _VI_FUNC  PaviStatusDesc	(ViObject vi, ViStatus status, ViChar _VI_FAR desc[]);
ViStatus _VI_FUNC  PaviTerminate	(ViObject vi, ViUInt16 degree, ViJobId jobId);
ViStatus _VI_FUNC  PaviLock			(ViSession vi, ViAccessMode lockType, ViUInt32 timeout,
									 ViConstKeyId requestedKey, ViChar _VI_FAR accessKey[]);
ViStatus _VI_FUNC  PaviUnlock		(ViSession vi);
ViStatus _VI_FUNC  PaviEnableEvent	(ViSession vi, ViEventType eventType, ViUInt16 mechanism,
									 ViEventFilter context);
ViStatus _VI_FUNC  PaviDisableEvent	(ViSession vi, ViEventType eventType, ViUInt16 mechanism);
ViStatus _VI_FUNC  PaviDiscardEvents(ViSession vi, ViEventType eventType, ViUInt16 mechanism);
ViStatus _VI_FUNC  PaviWaitOnEvent	(ViSession vi, ViEventType inEventType, ViUInt32 timeout,
									 ViPEventType outEventType, ViPEvent outContext);
ViStatus _VI_FUNC  PaviInstallHandler(ViSession vi, ViEventType eventType, ViHndlr handler,
									  ViAddr userHandle);
ViStatus _VI_FUNC  PaviUninstallHandler(ViSession vi, ViEventType eventType, ViHndlr handler,
									    ViAddr userHandle);

/*- Basic I/O Operations ----------------------------------------------------*/

ViStatus _VI_FUNC  PaviRead			(ViSession vi, ViPBuf buf, ViUInt32 cnt, ViPUInt32 retCnt);
ViStatus _VI_FUNC  PaviReadAsync	(ViSession vi, ViPBuf buf, ViUInt32 cnt, ViPJobId  jobId);
ViStatus _VI_FUNC  PaviReadToFile	(ViSession vi, ViConstString filename, ViUInt32 cnt,
									 ViPUInt32 retCnt);
ViStatus _VI_FUNC  PaviWrite		(ViSession vi, ViConstBuf  buf, ViUInt32 cnt, ViPUInt32 retCnt);
ViStatus _VI_FUNC  PaviWriteAsync	(ViSession vi, ViConstBuf  buf, ViUInt32 cnt, ViPJobId  jobId);
ViStatus _VI_FUNC  PaviWriteFromFile(ViSession vi, ViConstString filename, ViUInt32 cnt,
									 ViPUInt32 retCnt);
ViStatus _VI_FUNC  PaviAssertTrigger(ViSession vi, ViUInt16 protocol);
ViStatus _VI_FUNC  PaviReadSTB		(ViSession vi, ViPUInt16 status);
ViStatus _VI_FUNC  PaviClear		(ViSession vi);

/*- Formatted and Buffered I/O Operations -----------------------------------*/

ViStatus _VI_FUNC  PaviSetBuf		(ViSession vi, ViUInt16 mask, ViUInt32 size);
ViStatus _VI_FUNC  PaviFlush		(ViSession vi, ViUInt16 mask);

ViStatus _VI_FUNC  PaviBufWrite		(ViSession vi, ViConstBuf  buf, ViUInt32 cnt, ViPUInt32 retCnt);
ViStatus _VI_FUNC  PaviBufRead		(ViSession vi, ViPBuf buf, ViUInt32 cnt, ViPUInt32 retCnt);

ViStatus _VI_FUNCC PaviPrintf		(ViSession vi, ViConstString writeFmt, ...);
ViStatus _VI_FUNC  PaviVPrintf		(ViSession vi, ViConstString writeFmt, ViVAList params);
ViStatus _VI_FUNCC PaviSPrintf		(ViSession vi, ViBuf buf, ViConstString writeFmt, ...);
ViStatus _VI_FUNC  PaviVSPrintf		(ViSession vi, ViBuf buf, ViConstString writeFmt,
									 ViVAList parms);

ViStatus _VI_FUNCC PaviScanf		(ViSession vi, ViConstString readFmt, ...);
ViStatus _VI_FUNC  PaviVScanf		(ViSession vi, ViConstString readFmt, ViVAList params);
ViStatus _VI_FUNCC PaviSScanf		(ViSession vi, ViConstBuf buf, ViConstString readFmt, ...);
ViStatus _VI_FUNC  PaviVSScanf		(ViSession vi, ViConstBuf buf, ViConstString readFmt,
									 ViVAList parms);

ViStatus _VI_FUNCC PaviQueryf		(ViSession vi, ViConstString writeFmt, ViConstString readFmt, ...);
ViStatus _VI_FUNC  PaviVQueryf		(ViSession vi, ViConstString writeFmt, ViConstString readFmt,
									 ViVAList params);

/*- Memory I/O Operations ---------------------------------------------------*/

ViStatus _VI_FUNC  PaviIn8			(ViSession vi, ViUInt16 space,
									ViBusAddress offset, ViPUInt8  val8);
ViStatus _VI_FUNC  PaviOut8			(ViSession vi, ViUInt16 space,
									ViBusAddress offset, ViUInt8   val8);
ViStatus _VI_FUNC  PaviIn16			(ViSession vi, ViUInt16 space,
									ViBusAddress offset, ViPUInt16 val16);
ViStatus _VI_FUNC  PaviOut16		(ViSession vi, ViUInt16 space,
									ViBusAddress offset, ViUInt16  val16);
ViStatus _VI_FUNC  PaviIn32			(ViSession vi, ViUInt16 space,
									ViBusAddress offset, ViPUInt32 val32);
ViStatus _VI_FUNC  PaviOut32		(ViSession vi, ViUInt16 space,
									ViBusAddress offset, ViUInt32  val32);

#if defined(_VI_INT64_UINT64_DEFINED)
ViStatus _VI_FUNC  PaviIn64			(ViSession vi, ViUInt16 space,
									 ViBusAddress offset, ViPUInt64 val64);
ViStatus _VI_FUNC  PaviOut64		(ViSession vi, ViUInt16 space,
									 ViBusAddress offset, ViUInt64  val64);

ViStatus _VI_FUNC  PaviIn8Ex		(ViSession vi, ViUInt16 space,
									 ViBusAddress64 offset, ViPUInt8  val8);
ViStatus _VI_FUNC  PaviOut8Ex		(ViSession vi, ViUInt16 space,
									 ViBusAddress64 offset, ViUInt8   val8);
ViStatus _VI_FUNC  PaviIn16Ex		(ViSession vi, ViUInt16 space,
									 ViBusAddress64 offset, ViPUInt16 val16);
ViStatus _VI_FUNC  PaviOut16Ex		(ViSession vi, ViUInt16 space,
									 ViBusAddress64 offset, ViUInt16  val16);
ViStatus _VI_FUNC  PaviIn32Ex		(ViSession vi, ViUInt16 space,
									 ViBusAddress64 offset, ViPUInt32 val32);
ViStatus _VI_FUNC  PaviOut32Ex		(ViSession vi, ViUInt16 space,
									 ViBusAddress64 offset, ViUInt32  val32);
ViStatus _VI_FUNC  PaviIn64Ex		(ViSession vi, ViUInt16 space,
									 ViBusAddress64 offset, ViPUInt64 val64);
ViStatus _VI_FUNC  PaviOut64Ex		(ViSession vi, ViUInt16 space,
									 ViBusAddress64 offset, ViUInt64  val64);
#endif

ViStatus _VI_FUNC  PaviMoveIn8		(ViSession vi, ViUInt16 space, ViBusAddress offset,
									ViBusSize length, ViAUInt8  buf8);
ViStatus _VI_FUNC  PaviMoveOut8		(ViSession vi, ViUInt16 space, ViBusAddress offset,
									ViBusSize length, ViAUInt8  buf8);
ViStatus _VI_FUNC  PaviMoveIn16		(ViSession vi, ViUInt16 space, ViBusAddress offset,
									ViBusSize length, ViAUInt16 buf16);
ViStatus _VI_FUNC  PaviMoveOut16	(ViSession vi, ViUInt16 space, ViBusAddress offset,
									ViBusSize length, ViAUInt16 buf16);
ViStatus _VI_FUNC  PaviMoveIn32		(ViSession vi, ViUInt16 space, ViBusAddress offset,
									ViBusSize length, ViAUInt32 buf32);
ViStatus _VI_FUNC  PaviMoveOut32	(ViSession vi, ViUInt16 space, ViBusAddress offset,
									ViBusSize length, ViAUInt32 buf32);

#if defined(_VI_INT64_UINT64_DEFINED)
ViStatus _VI_FUNC  PaviMoveIn64		(ViSession vi, ViUInt16 space, ViBusAddress offset,
									 ViBusSize length, ViAUInt64 buf64);
ViStatus _VI_FUNC  PaviMoveOut64	(ViSession vi, ViUInt16 space, ViBusAddress offset,
									 ViBusSize length, ViAUInt64 buf64);

ViStatus _VI_FUNC  PaviMoveIn8Ex	(ViSession vi, ViUInt16 space, ViBusAddress64 offset,
									 ViBusSize length, ViAUInt8  buf8);
ViStatus _VI_FUNC  PaviMoveOut8Ex	(ViSession vi, ViUInt16 space, ViBusAddress64 offset,
									 ViBusSize length, ViAUInt8  buf8);
ViStatus _VI_FUNC  PaviMoveIn16Ex	(ViSession vi, ViUInt16 space, ViBusAddress64 offset,
									 ViBusSize length, ViAUInt16 buf16);
ViStatus _VI_FUNC  PaviMoveOut16Ex	(ViSession vi, ViUInt16 space, ViBusAddress64 offset,
									 ViBusSize length, ViAUInt16 buf16);
ViStatus _VI_FUNC  PaviMoveIn32Ex	(ViSession vi, ViUInt16 space, ViBusAddress64 offset,
									 ViBusSize length, ViAUInt32 buf32);
ViStatus _VI_FUNC  PaviMoveOut32Ex	(ViSession vi, ViUInt16 space, ViBusAddress64 offset,
									 ViBusSize length, ViAUInt32 buf32);
ViStatus _VI_FUNC  PaviMoveIn64Ex	(ViSession vi, ViUInt16 space, ViBusAddress64 offset,
									 ViBusSize length, ViAUInt64 buf64);
ViStatus _VI_FUNC  PaviMoveOut64Ex	(ViSession vi, ViUInt16 space, ViBusAddress64 offset,
									 ViBusSize length, ViAUInt64 buf64);
#endif

ViStatus _VI_FUNC  PaviMove			(ViSession vi, ViUInt16 srcSpace, ViBusAddress srcOffset,
									 ViUInt16 srcWidth, ViUInt16 destSpace,
									 ViBusAddress destOffset, ViUInt16 destWidth,
									 ViBusSize srcLength);
ViStatus _VI_FUNC  PaviMoveAsync	(ViSession vi, ViUInt16 srcSpace, ViBusAddress srcOffset,
									 ViUInt16 srcWidth, ViUInt16 destSpace,
									 ViBusAddress destOffset, ViUInt16 destWidth,
									 ViBusSize srcLength, ViPJobId jobId);

#if defined(_VI_INT64_UINT64_DEFINED)
ViStatus _VI_FUNC  PaviMoveEx		(ViSession vi, ViUInt16 srcSpace, ViBusAddress64 srcOffset,
									 ViUInt16 srcWidth, ViUInt16 destSpace,
									 ViBusAddress64 destOffset, ViUInt16 destWidth,
									 ViBusSize srcLength);
ViStatus _VI_FUNC  PaviMoveAsyncEx	(ViSession vi, ViUInt16 srcSpace, ViBusAddress64 srcOffset,
									 ViUInt16 srcWidth, ViUInt16 destSpace,
									 ViBusAddress64 destOffset, ViUInt16 destWidth,
									 ViBusSize srcLength, ViPJobId jobId);
#endif

ViStatus _VI_FUNC  PaviMapAddress	(ViSession vi, ViUInt16 mapSpace, ViBusAddress mapOffset,
									 ViBusSize mapSize, ViBoolean access,
									 ViAddr suggested, ViPAddr address);
ViStatus _VI_FUNC  PaviUnmapAddress	(ViSession vi);

#if defined(_VI_INT64_UINT64_DEFINED)
ViStatus _VI_FUNC  PaviMapAddressEx	(ViSession vi, ViUInt16 mapSpace, ViBusAddress64 mapOffset,
									 ViBusSize mapSize, ViBoolean access,
									 ViAddr suggested, ViPAddr address);
#endif

void     _VI_FUNC  PaviPeek8		(ViSession vi, ViAddr address, ViPUInt8  val8);
void     _VI_FUNC  PaviPoke8		(ViSession vi, ViAddr address, ViUInt8   val8);
void     _VI_FUNC  PaviPeek16		(ViSession vi, ViAddr address, ViPUInt16 val16);
void     _VI_FUNC  PaviPoke16		(ViSession vi, ViAddr address, ViUInt16  val16);
void     _VI_FUNC  PaviPeek32		(ViSession vi, ViAddr address, ViPUInt32 val32);
void     _VI_FUNC  PaviPoke32		(ViSession vi, ViAddr address, ViUInt32  val32);

#if defined(_VI_INT64_UINT64_DEFINED)
void     _VI_FUNC  PaviPeek64		(ViSession vi, ViAddr address, ViPUInt64 val64);
void     _VI_FUNC  PaviPoke64		(ViSession vi, ViAddr address, ViUInt64  val64);
#endif

/*- Shared Memory Operations ------------------------------------------------*/

ViStatus _VI_FUNC  PaviMemAlloc		(ViSession vi, ViBusSize size, ViPBusAddress offset);
ViStatus _VI_FUNC  PaviMemFree		(ViSession vi, ViBusAddress offset);

#if defined(_VI_INT64_UINT64_DEFINED)
ViStatus _VI_FUNC  PaviMemAllocEx	(ViSession vi, ViBusSize size, ViPBusAddress64 offset);
ViStatus _VI_FUNC  PaviMemFreeEx	(ViSession vi, ViBusAddress64 offset);
#endif

#ifdef __cplusplus 
}
#endif

#endif	//_PAPCI_H_