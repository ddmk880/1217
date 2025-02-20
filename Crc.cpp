﻿#include "Crc.h"
#include<QDebug>
//CRC码采用CRC-X25标准，生成多项式为（0，5，12，16）
#define CRC_POLYNOMIAL 0x1021  //x^16+x^5+x^12+1 多项式

#define CRC_INTTIAL 0x1021 //初值



// CRC余式表
static unsigned short CRC_ITU_table[256] ={               // CRC余式表
    0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5, 0x60c6, 0x70e7,
    0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad, 0xe1ce, 0xf1ef,
    0x1231, 0x0210, 0x3273, 0x2252, 0x52b5, 0x4294, 0x72f7, 0x62d6,
    0x9339, 0x8318, 0xb37b, 0xa35a, 0xd3bd, 0xc39c, 0xf3ff, 0xe3de,
    0x2462, 0x3443, 0x0420, 0x1401, 0x64e6, 0x74c7, 0x44a4, 0x5485,
    0xa56a, 0xb54b, 0x8528, 0x9509, 0xe5ee, 0xf5cf, 0xc5ac, 0xd58d,
    0x3653, 0x2672, 0x1611, 0x0630, 0x76d7, 0x66f6, 0x5695, 0x46b4,
    0xb75b, 0xa77a, 0x9719, 0x8738, 0xf7df, 0xe7fe, 0xd79d, 0xc7bc,
    0x48c4, 0x58e5, 0x6886, 0x78a7, 0x0840, 0x1861, 0x2802, 0x3823,
    0xc9cc, 0xd9ed, 0xe98e, 0xf9af, 0x8948, 0x9969, 0xa90a, 0xb92b,
    0x5af5, 0x4ad4, 0x7ab7, 0x6a96, 0x1a71, 0x0a50, 0x3a33, 0x2a12,
    0xdbfd, 0xcbdc, 0xfbbf, 0xeb9e, 0x9b79, 0x8b58, 0xbb3b, 0xab1a,
    0x6ca6, 0x7c87, 0x4ce4, 0x5cc5, 0x2c22, 0x3c03, 0x0c60, 0x1c41,
    0xedae, 0xfd8f, 0xcdec, 0xddcd, 0xad2a, 0xbd0b, 0x8d68, 0x9d49,
    0x7e97, 0x6eb6, 0x5ed5, 0x4ef4, 0x3e13, 0x2e32, 0x1e51, 0x0e70,
    0xff9f, 0xefbe, 0xdfdd, 0xcffc, 0xbf1b, 0xaf3a, 0x9f59, 0x8f78,
    0x9188, 0x81a9, 0xb1ca, 0xa1eb, 0xd10c, 0xc12d, 0xf14e, 0xe16f,
    0x1080, 0x00a1, 0x30c2, 0x20e3, 0x5004, 0x4025, 0x7046, 0x6067,
    0x83b9, 0x9398, 0xa3fb, 0xb3da, 0xc33d, 0xd31c, 0xe37f, 0xf35e,
    0x02b1, 0x1290, 0x22f3, 0x32d2, 0x4235, 0x5214, 0x6277, 0x7256,
    0xb5ea, 0xa5cb, 0x95a8, 0x8589, 0xf56e, 0xe54f, 0xd52c, 0xc50d,
    0x34e2, 0x24c3, 0x14a0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
    0xa7db, 0xb7fa, 0x8799, 0x97b8, 0xe75f, 0xf77e, 0xc71d, 0xd73c,
    0x26d3, 0x36f2, 0x0691, 0x16b0, 0x6657, 0x7676, 0x4615, 0x5634,
    0xd94c, 0xc96d, 0xf90e, 0xe92f, 0x99c8, 0x89e9, 0xb98a, 0xa9ab,
    0x5844, 0x4865, 0x7806, 0x6827, 0x18c0, 0x08e1, 0x3882, 0x28a3,
    0xcb7d, 0xdb5c, 0xeb3f, 0xfb1e, 0x8bf9, 0x9bd8, 0xabbb, 0xbb9a,
    0x4a75, 0x5a54, 0x6a37, 0x7a16, 0x0af1, 0x1ad0, 0x2ab3, 0x3a92,
    0xfd2e, 0xed0f, 0xdd6c, 0xcd4d, 0xbdaa, 0xad8b, 0x9de8, 0x8dc9,
    0x7c26, 0x6c07, 0x5c64, 0x4c45, 0x3ca2, 0x2c83, 0x1ce0, 0x0cc1,
    0xef1f, 0xff3e, 0xcf5d, 0xdf7c, 0xaf9b, 0xbfba, 0x8fd9, 0x9ff8,
    0x6e17, 0x7e36, 0x4e55, 0x5e74, 0x2e93, 0x3eb2, 0x0ed1, 0x1ef0
  };

unsigned short crcSlow(unsigned short const *mes,unsigned int n)
{
    unsigned int byte;
    unsigned short bit;
    unsigned short remainder=CRC_INTTIAL;

    for(byte=0;byte<n;byte++,mes++)
    {
        for(bit=0x8000;bit>0;bit>>=1)
        {
            if(remainder&0x8000)
            {
                remainder=(remainder<<1)^CRC_POLYNOMIAL;
            }
            else
            {
                remainder=(remainder<<1);
            }
            if(*mes &bit)
                remainder^=CRC_POLYNOMIAL;
        }
    }
    return remainder;
}

void make_CRC_ITU_table(void)//生成CRC16的查询表格
{
    unsigned short rem;
    int div;
    unsigned char bit;

    for(div=0;div<256;div++)
    {
        rem=div<<8;
        for(bit=8;bit>0;--bit)
        {
            if(rem&0x8000)
            {
                rem=(rem<<1)^CRC_POLYNOMIAL;

            }
            else
            {
                rem=(rem<<1);
            }
        }
        CRC_ITU_table[div]=rem;
    }
}


//计算给定信息串的CRC码
//注意必须首先调用CRC16_Init()生成表
//返回CRC码
unsigned short CRC16(unsigned short const *ptr,unsigned int n)
{
    unsigned short crc=CRC_INTTIAL;
    for(unsigned int i=0;i<n;i++)
    {
        crc=crc^(ptr[i]&0xff00);
        for(int j=0;j<8;j++)
        {
            if((crc&0x8000)==0x8000)
                crc=(crc<<1)^CRC_POLYNOMIAL;
            else
            {
                crc=crc<<1;
            }
        }

        crc=crc^(ptr[i]<<8);

        for(int j=0;j<8;j++)
        {
            if((crc&0x8000)==0x8000)
                crc=(crc<<1)^CRC_POLYNOMIAL;
            else
            {
                crc=crc<<1;
            }
        }
    }

    return (crc);
}

unsigned short CRC16_char(unsigned char const *ptr, unsigned int n)
{
//    //static int start = 1;
//    unsigned short crc;
//    unsigned char da;
///*
//    if(start) {
//        start = 0;

//        memset(CRC_ITU_table,0,256);
//        make_CRC_ITU_table();
//    }*/


//    crc = CRC_INTTIAL;
////    while(n--)
////    {
////        da = (unsigned char) (crc >> 8);		// 暂存CRC高8bit
////        crc <<= 8;								// CRC右移8位，相当于取CRC低8位
////        crc ^= CRC_ITU_table[da ^ (*ptr)];	// CRC高8位和数据高8位相加后查表，加上次CRC余数

////        ptr++;
////    }
//    while(n--) {
//            da = (unsigned char) (crc >> 8);		// 暂存CRC高8bit
//            crc <<= 8;								// CRC右移8位，相当于取CRC低8位
//            crc ^= CRC_ITU_table[da ^ (*ptr >> 8)];	// CRC高8位和数据高8位相加后查表，加上次CRC余数
//            da = (unsigned char) (crc >> 8);		// 暂存CRC高8位
//            crc <<= 8;								// CRC右移8位， 相当于取CRC低8位
//            crc ^= CRC_ITU_table[da^(*ptr & 0xff)];	// CRC高8位和数据低8位相加后查表，加上次CRC余数
//            ptr++;
//        }
//    return (crc);

    //static int start = 1;
    unsigned short crc;
    unsigned char da;
/*
    if(start) {
        start = 0;

        memset(CRC_ITU_table,0,256);
        make_CRC_ITU_table();
    }*/


    crc = CRC_INTTIAL;
    while(n--)
    {
        da = (unsigned char) (crc >> 8);		// 暂存CRC高8bit
        crc <<= 8;								// CRC右移8位，相当于取CRC低8位
        crc ^= CRC_ITU_table[da ^ (*ptr)];	    // CRC高8位和数据高8位相加后查表，加上次CRC余数

        ptr++;
    }
    return (crc);
}


// 计算给定信息串的CRC码
// 注意必须首先调用CRC16_Init() 生成表
// 返回: CRC 码
unsigned short CRC16_(unsigned short const *ptr, unsigned int n)
{
//	static int start = 1;
    unsigned short crc;
    unsigned char da;

//	if(start) {
//		start = 0;
//		make_CRC_ITU_table();
//	}

    crc = CRC_INTTIAL;
    while(n--) {
        da = (unsigned char) (crc >> 8);		// 暂存CRC高8bit
        crc <<= 8;								// CRC右移8位，相当于取CRC低8位
        crc ^= CRC_ITU_table[da ^ (*ptr >> 8)];	// CRC高8位和数据高8位相加后查表，加上次CRC余数
        da = (unsigned char) (crc >> 8);		// 暂存CRC高8位
        crc <<= 8;								// CRC右移8位， 相当于取CRC低8位
        crc ^= CRC_ITU_table[da^(*ptr & 0xff)];	// CRC高8位和数据低8位相加后查表，加上次CRC余数
        ptr++;
    }
    return (crc);
}








