#pragma once
/************************************************************************/
/*
Copyright(c) 2017
All rights reserved.
文件:iBHDataAdapter.h
说明：动态库接口文件，实现连接服务，发送码，状态查询等功能
作者：吴金华 13013787596
日期：2018.8.9
*/
/************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
//#define   CODE_LEN  144  支持 48  144两种

//网络错误码定义
#define ERR_NOERR         0
#define ERR_CLOSE         1    //主动关闭
#define ERR_REMOTE_CLOSE  2    //服务关闭
#define ERR_TIMEOUT       3    //超时
#define ERR_SENDFAIL      4    //发送错误
#define ERR_REMOTE_REFUSE 5   //远程拒绝, 心跳超时
#define ERR_INIT_ERROR    6    //没有正确初始化

#ifdef BHDATAADAPTER_EXPORTS
#define DATAADPATER_API _declspec(dllexport)
#else
#define DATAADPATER_API _declspec(dllimport)
#endif
	
	class DATAADPATER_API IDataAdapterNotify
	{
	public:
		//连接事件通知，nError==0表示无错误，其他值看上面宏定义
		virtual void OnConnect(long UserID,int nError) = 0;
		virtual void OnDisconnect(long UserID,int nError) = 0;

		//发送码后，设备返回通知，nError==0表示正常，==1表示异常
		virtual void OnRecvCode(long UserID,int nError) = 0;
		//设置IP的返回
		virtual void OnSetIpPort(long UserID,LPCTSTR lpszIP, USHORT usPort) = 0;
		/************************************************************************/
		/*
		函数：OnSearchStatus
		参数：
		nError：0表示成功，1表示失败
		pfU pfI pnTemp：分别为电压，电流，温度数组。元素个数为4即模块数
		nModuleNum:  4个模块
		说明： 电压，电流，温度返回值
		*/
		/************************************************************************/
		virtual void OnSearchStatus(long UserID,int nError, float *pfU, float *pfI, int *pnTemp, int nModuleNum = 4) {};
		/************************************************************************/
		/*
		函数：OnSearchCurPha
		参数：
		nError：0表示成功，1表示失败
		bytCurPha:  32字节当前移相值，如1-8字节为，模块1的8通道...
		说明： 当前移相值
		*/
		/************************************************************************/
		virtual void OnSearchCurPha(long UserID,int nError, BYTE *bytCurPha, int nPhaNum = 32) {};

		//发送码二进制数据回调
		virtual void OnSendData(long UserID,BYTE *pBuff, int nLen) {};

		virtual ~IDataAdapterNotify() { };
	};
	/************************************************************************/
	/*
	函数：BH_InitModule
	参数：
	pNotify：class IDataAdapterNotify的通知类，用户实现回调
	返回值：等于0：成功， 小于0：失败。
	说明：用户初始化必须先调用，才能调用其他接口
	*/
	/************************************************************************/
	long DATAADPATER_API BH_InitModule(IDataAdapterNotify *pNotify);
	/************************************************************************/
	/*
	函数：BH_UninitModule
	返回值：等于0：成功， 小于0：失败。
	说明：用户使用完后调用
	*/
	/************************************************************************/
	void DATAADPATER_API BH_UninitModule();

	/************************************************************************/
	/*
	函数：BH_StartConnect
	返回值：大于0为用户标示  UserID， 小于0：失败。
	参数：分别为：IP地址，端口，断开重连时间（毫秒）为0时，断开不重连，默认3秒。
	说明：连接设备
	*/
	/************************************************************************/
	long DATAADPATER_API BH_StartConnect(LPCTSTR lpszIP, USHORT usPort, int nReconnectTime=3000);
	//断开连接
	void DATAADPATER_API BH_Disconnect(long UserID);

	//设置查表点间隔，参数为1,2,4代表1M，2M，4M。默认为4
	//返回值：等于0：成功， 小于0：失败。
	long DATAADPATER_API BH_SetFreqCheckInterval(long UserID,int nM = 4);
	//设置直通或变频 , ntype  0:直通 1:变频
	long DATAADPATER_API BH_SetStrightorChangeRate(long UserID,int ntype);
	//设置ip端口
	long DATAADPATER_API BH_SetIPPort(long UserID,LPCTSTR lpszIP,USHORT usPort);
	/************************************************************************/
	/*
	函数：BH_SendCode
	返回值：等于0：成功， 小于0：失败。
	参数：
	fFreq1，fFreq2，fFreq3，fFreq4：为模块1，2，3，4的频点
	pbytCode：  码地址，包含头
	nCodeLen： 码的长度，支持 48 ， 144两种
	说明：发送码
	*/
	/************************************************************************/
	long DATAADPATER_API BH_SendCode(long UserID,float fFreq1,float fFreq2,float fFreq3, float fFreq4,BYTE *pbytCode,int nCodeLen);
	//查询当前的电压，电流，温度
	long DATAADPATER_API BH_SearchStatus(long UserID);
	//查询当前的移相值
	long DATAADPATER_API BH_SearchCurPha(long UserID);
	//透明通道，发送原始数据
	long DATAADPATER_API BH_SendData(long UserID,BYTE *pData, int nDataLen);

#ifdef __cplusplus
}
#endif