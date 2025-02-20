/*********************************************************************
* 版权所有 (C)2023, 成都指南中为科技有限公司。
*
* 文件名称： pacom.h
* 内容摘要： 通用参数声明
* 其它说明： 无
* 当前版本： V1.00
* 作    者： Luohz
* 建立日期： 2023年06月23日
* 完成日期：
*
* 修改记录1：
* 修改日期：
*    版 本 号：V1.00
*    修 改 人：Luohz
*    修改内容：创建
**********************************************************************/

#pragma once

//#pragma region 函数导出参数//vs特有预处理语法
#define PA_DLLEXPORT				__declspec(dllexport)
#define PA_FUNC						__stdcall
//#pragma endregion

//#pragma region 函数返回参数
#define PA_SUCCESS					0		// 成功
#define PA_UNSUCCESS				-1		// 不成功
#define PA_ERROR_PARAMETER_ILLEGAL	-2		// 非法参数
#define PA_ERROR_UNKNOWN			-127	// 非法参数
//#pragma endregion

//#pragma region 使能参数
#define PA_ENABLE					0x01	// 使能
#define PA_DISABLE					0x00	// 失能
//#pragma endregion

//#pragma region 工作模式
#define PA_MODE_LEVEL				0x03	// 电平模式
#define PA_MODE_PULSE				0x04	// 脉冲模式
#define PA_MODE_UART				0x05	// 串口模式
//#pragma endregion

//#pragma region 电平模式
#define PA_LEVEL_LOW				0x00	// 低电平
#define PA_LEVEL_HIGH				0x01	// 高电平
//#pragma endregion

//#pragma region 脉冲模式
#define PA_PULSEMODE_SINGLE			0x00	// 单次发生模式
#define PA_PULSEMODE_PERIOD			0x01	// 周期发生模式
#define PA_PRECISION_US				0x00	// 脉冲精度：us
#define PA_PRECISION_MS				0x01	// 脉冲精度：ms
#define PA_PRECISION_S				0x02	// 脉冲精度：s
#define PA_PRECISION_X				0x03	// 脉冲精度：x
//#pragma endregion

//#pragma region 门控参数
#define PA_GATING_LOW				0x00	// 门控低有效
#define PA_GATING_HIGH				0x01	// 门控高有效
//#pragma endregion

//#pragma region 边沿参数
#define PA_EDGE_RISING				0x00	// 上升沿
#define PA_EDGE_FALING				0x01	// 下降沿
//#pragma endregion

//#pragma region 方向参数
#define PA_DIRECTION_IN				0x00	// 接收方向
#define PA_DIRECTION_OUT			0x01	// 输出方向
//#pragma endregion

//#pragma region 字节序参数
#define PA_BIG_ENDIAN				0x00	// 大端模式
#define PA_LITTLE_ENDIAN			0x01	// 小端模式
//#pragma endregion

//#pragma region TTL接口参数
#define PA_LEVELSTD_LVTTL			(0x20000000L)// LVTTL电平标准(3.3V), 低电平
#define PA_LEVELSTD_TTL				(0x20000001L)// TTL电平标准(5V), 高电平
//#pragma endregion

//#pragma region AD接口参数
#define PA_AD_RANGE_2Dot5V			(0x70000001L)// AD采样范围±2.5V
#define PA_AD_RANGE_5V				(0x70000002L)// AD采样范围±5V
#define PA_AD_RANGE_10V				(0x70000003L)// AD采样范围±10V
#define PA_AD_RATE_NULL				(0x71000000L)// AD过采样率 无
#define PA_AD_RATE_2X				(0x71000001L)// AD过采样率2x
#define PA_AD_RATE_4X				(0x71000002L)// AD过采样率4x
#define PA_AD_RATE_8X				(0x71000003L)// AD过采样率8x
#define PA_AD_RATE_16X				(0x71000004L)// AD过采样率16x
#define PA_AD_RATE_32X				(0x71000005L)// AD过采样率32x
#define PA_AD_RATE_64X				(0x71000006L)// AD过采样率64x
//#pragma endregion

//#pragma region RS232模式
#define PA_DUPLEXFLAG_HALF			0x00	// 半双工
#define PA_DUPLEXFLAG_FULL			0x01	// 全双工			
#define PA_STOPBIT_ONE				0x00	// 1位停止位
#define PA_STOPBIT_TWO				0x01	// 2位停止位
#define PA_PARITY_NONE				0x00	// 无校验
#define PA_PARITY_ODD				0x02	// 奇校验
#define PA_PARITY_EVEN				0x03	// 偶校验
//#pragma endregion

//#pragma region CAN接口参数
#define PA_CAN_BAUD_1000K			0x00	// CAN速率 1M
#define PA_CAN_BAUD_500K			0x01	// CAN速率 500K
#define PA_CAN_BAUD_200K			0x02	// CAN速率 200K
#define PA_CAN_BAUD_100K			0x03	// CAN速率 100K
#define PA_CAN_MATCHING_OPEN		0x00	// CAN总线匹配电阻 开路		
#define PA_CAN_MATCHING_60			0x01	// CAN总线匹配电阻 60欧姆
#define PA_CAN_MATCHING_120			0x02	// CAN总线匹配电阻 120欧姆
//#pragma endregion

//#pragma region NET接口参数
#define PA_NET_BAUD_10M				(0x60000000L)	// 10M速率
#define PA_NET_BAUD_100M			(0x60000001L)	// 100M速率
#define PA_NET_BAUD_1000M			(0x60000002L)	// 1000M速率
//#pragma endregion

//#pragma region 函数返回参数通用宏定义
#define PA_UNUSED(x) (void)(x)// 避免未使用的参数告警
//#pragma endregion

#define PA_DATABUF_MAX_LENGTH		1230//数据缓冲区最大深度定义

//#pragma region 函数返回参数通用宏定义
typedef  int(__stdcall *PA_UserHandle)(unsigned int device);
//#pragma endregion
