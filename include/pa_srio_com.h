/*********************************************************************
* 版权所有 (C)2023, 成都指南中为科技有限公司。
*
* 文件名称： pa_srio_com.h
* 内容摘要： 通用参数声明
* 其它说明： 无
* 当前版本： V1.00
* 作    者： LHZ
* 建立日期： 2023年03月11日
* 完成日期：
*
* 修改记录1：
* 修改日期：
*    版 本 号：V1.00
*    修 改 人：LHZ
*    修改内容：创建
**********************************************************************/

#pragma once

enum LOOPMODE
{
	LOOP_OFF = 0,
	LOOP_ON
};

struct PA_SRIO_NWRITEPAMETER
{
	unsigned int NwriteDestAddr;	// 从端器件地址
	unsigned int NwriteType;		// NWR类型
	unsigned int NwriteSourceAddr_L;  // NWR首地址低32位
	unsigned int NwriteSourceAddr_H;  // NWR首地址高2位
	unsigned int NwritePackageLen;	// NWR包长度
};

struct PA_SRIO_NREADPAMETER
{
	unsigned int FrameLen;  // 发送帧长(单位为字节)
	unsigned int FrameGap;  // 发送帧间隔(单位为us)
	unsigned int SyncHead_L;
	unsigned int SyncHead_H;
};