#ifndef CRC_H
#define CRC_H




//按查表方法计算给定信息串的CRC码，返回：CRC码
unsigned short CRC16(unsigned short const *mes,unsigned int n);

//按位计算给定信息串的CRC码,速度较慢，返回：CRC码
unsigned short crcSlow(unsigned short const *mes,unsigned int n);

unsigned short CRC16_char(unsigned char const *ptr,unsigned int n);

unsigned short CRC16_(unsigned short const *ptr, unsigned int n);
void make_CRC_ITU_table(void);
#endif // CRC_H
