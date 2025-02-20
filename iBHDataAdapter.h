#pragma once
/************************************************************************/
/*
Copyright(c) 2017
All rights reserved.
�ļ�:iBHDataAdapter.h
˵������̬��ӿ��ļ���ʵ�����ӷ��񣬷����룬״̬��ѯ�ȹ���
���ߣ���� 13013787596
���ڣ�2018.8.9
*/
/************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
//#define   CODE_LEN  144  ֧�� 48  144����

//��������붨��
#define ERR_NOERR         0
#define ERR_CLOSE         1    //�����ر�
#define ERR_REMOTE_CLOSE  2    //����ر�
#define ERR_TIMEOUT       3    //��ʱ
#define ERR_SENDFAIL      4    //���ʹ���
#define ERR_REMOTE_REFUSE 5   //Զ�ܾ̾�, ������ʱ
#define ERR_INIT_ERROR    6    //û����ȷ��ʼ��

#ifdef BHDATAADAPTER_EXPORTS
#define DATAADPATER_API _declspec(dllexport)
#else
#define DATAADPATER_API _declspec(dllimport)
#endif
	
	class DATAADPATER_API IDataAdapterNotify
	{
	public:
		//�����¼�֪ͨ��nError==0��ʾ�޴�������ֵ������궨��
		virtual void OnConnect(long UserID,int nError) = 0;
		virtual void OnDisconnect(long UserID,int nError) = 0;

		//��������豸����֪ͨ��nError==0��ʾ������==1��ʾ�쳣
		virtual void OnRecvCode(long UserID,int nError) = 0;
		//����IP�ķ���
		virtual void OnSetIpPort(long UserID,LPCTSTR lpszIP, USHORT usPort) = 0;
		/************************************************************************/
		/*
		������OnSearchStatus
		������
		nError��0��ʾ�ɹ���1��ʾʧ��
		pfU pfI pnTemp���ֱ�Ϊ��ѹ���������¶����顣Ԫ�ظ���Ϊ4��ģ����
		nModuleNum:  4��ģ��
		˵���� ��ѹ���������¶ȷ���ֵ
		*/
		/************************************************************************/
		virtual void OnSearchStatus(long UserID,int nError, float *pfU, float *pfI, int *pnTemp, int nModuleNum = 4) {};
		/************************************************************************/
		/*
		������OnSearchCurPha
		������
		nError��0��ʾ�ɹ���1��ʾʧ��
		bytCurPha:  32�ֽڵ�ǰ����ֵ����1-8�ֽ�Ϊ��ģ��1��8ͨ��...
		˵���� ��ǰ����ֵ
		*/
		/************************************************************************/
		virtual void OnSearchCurPha(long UserID,int nError, BYTE *bytCurPha, int nPhaNum = 32) {};

		//��������������ݻص�
		virtual void OnSendData(long UserID,BYTE *pBuff, int nLen) {};

		virtual ~IDataAdapterNotify() { };
	};
	/************************************************************************/
	/*
	������BH_InitModule
	������
	pNotify��class IDataAdapterNotify��֪ͨ�࣬�û�ʵ�ֻص�
	����ֵ������0���ɹ��� С��0��ʧ�ܡ�
	˵�����û���ʼ�������ȵ��ã����ܵ��������ӿ�
	*/
	/************************************************************************/
	long DATAADPATER_API BH_InitModule(IDataAdapterNotify *pNotify);
	/************************************************************************/
	/*
	������BH_UninitModule
	����ֵ������0���ɹ��� С��0��ʧ�ܡ�
	˵�����û�ʹ��������
	*/
	/************************************************************************/
	void DATAADPATER_API BH_UninitModule();

	/************************************************************************/
	/*
	������BH_StartConnect
	����ֵ������0Ϊ�û���ʾ  UserID�� С��0��ʧ�ܡ�
	�������ֱ�Ϊ��IP��ַ���˿ڣ��Ͽ�����ʱ�䣨���룩Ϊ0ʱ���Ͽ���������Ĭ��3�롣
	˵���������豸
	*/
	/************************************************************************/
	long DATAADPATER_API BH_StartConnect(LPCTSTR lpszIP, USHORT usPort, int nReconnectTime=3000);
	//�Ͽ�����
	void DATAADPATER_API BH_Disconnect(long UserID);

	//���ò�����������Ϊ1,2,4����1M��2M��4M��Ĭ��Ϊ4
	//����ֵ������0���ɹ��� С��0��ʧ�ܡ�
	long DATAADPATER_API BH_SetFreqCheckInterval(long UserID,int nM = 4);
	//����ֱͨ���Ƶ , ntype  0:ֱͨ 1:��Ƶ
	long DATAADPATER_API BH_SetStrightorChangeRate(long UserID,int ntype);
	//����ip�˿�
	long DATAADPATER_API BH_SetIPPort(long UserID,LPCTSTR lpszIP,USHORT usPort);
	/************************************************************************/
	/*
	������BH_SendCode
	����ֵ������0���ɹ��� С��0��ʧ�ܡ�
	������
	fFreq1��fFreq2��fFreq3��fFreq4��Ϊģ��1��2��3��4��Ƶ��
	pbytCode��  ���ַ������ͷ
	nCodeLen�� ��ĳ��ȣ�֧�� 48 �� 144����
	˵����������
	*/
	/************************************************************************/
	long DATAADPATER_API BH_SendCode(long UserID,float fFreq1,float fFreq2,float fFreq3, float fFreq4,BYTE *pbytCode,int nCodeLen);
	//��ѯ��ǰ�ĵ�ѹ���������¶�
	long DATAADPATER_API BH_SearchStatus(long UserID);
	//��ѯ��ǰ������ֵ
	long DATAADPATER_API BH_SearchCurPha(long UserID);
	//͸��ͨ��������ԭʼ����
	long DATAADPATER_API BH_SendData(long UserID,BYTE *pData, int nDataLen);

#ifdef __cplusplus
}
#endif