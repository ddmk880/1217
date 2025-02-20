#ifndef GLOBEL_DEFINE_H
#define GLOBEL_DEFINE_H
#include <qendian.h>

#include <QDateTime>
#include <QDebug>
#include <QMainWindow>

#include "Crc.h"
/*************************************************
 <文件名称>    Globel_Define.h
 <概要说明>    结构体定义头文件
 <详细说明>    无
 <作    者>   zm
 <时    间>   2023-03-21
 <修    改>
**************************************************/
#define LL long long

// 1553协议字节序 高前低后
/*************************File********************
 <文件名称>    全部变量定义区
 <文件说明>    无
 <作    者>   zm
 <时    间>   2023-04-03
 <修    改>
**************************************************/
extern QMainWindow* P_MAIN_WIN;

//  规定字节对齐方式
#pragma pack(push, 1)
/*************************区域划分********************
                   任务指令格式
 <结构体名称>  Order_List_Object
 <详细说明>   主界面指令列表内元素的结构体
 【打*的为必填项,无*的可不填,但是函数对象必须初始化0】
**************************************************/
struct Order_List_Object {
    bool mode;           // 模式 FALSE-0-代表新增模式 TRUE-1-代表修改模式
    uchar obj_id;        // 目标单机,0开始（单机1）
    uint start_time;     // 发送时间
    uchar page_id;       // 页面序号
    uchar gap_time;      // 间隔时间
    QString order_name;  // 指令名称
    uchar order_kind;    // 指令类型：1：总线指令，2：总线注数
    quint16 order_len;   // 指令长度
    uchar* data_buf;     // 数据区
    // 深拷贝，重载=赋值
    bool operator=(const Order_List_Object rec_data) {
        mode = rec_data.mode;
        obj_id = rec_data.obj_id;
        start_time = rec_data.start_time;
        page_id = rec_data.page_id;
        gap_time = rec_data.gap_time;
        order_name = rec_data.order_name;
        order_kind = rec_data.order_kind;
        order_len = rec_data.order_len;
        uchar* data_buf = new uchar[rec_data.order_len];
        memcpy(data_buf, rec_data.data_buf, rec_data.order_len);
        return true;
    }
};
Q_DECLARE_METATYPE(Order_List_Object)

/************************Struct*******************
 <结构体名称>  Test_By_ZM_
 <结构体定义>  测试用样例任务指令结构体
 <作    者>   zm
 <时    间>   2023-04-03
 <修    改>   无
**************************************************/
struct Test_By_ZM_ {
    int t;
    char a;
    short b;
};

/*************************区域划分********************
                 总线数据格式
**************************************************/
typedef struct _CAN_MESS {
    qint32 MsgID;           // 帧ID
    qint8 Data[8];          // 数据域
    qint8 DLC;              // 数据域长度
    qint8 Reserved1;        // 保留 字节对齐 无实意
    qint16 Reserved2;       // 保留 字节对齐 无实意
} CAN_MESS, *P_CAN_MESS;  // CAN消息结构体声明
/*************************区域划分********************
                 数据库表格式
**************************************************/
/********软件日志表*********/
struct Software_Note {
    unsigned int id;
    QDateTime write_time;
    QString function_name;
    QString call_text;
    QString remark;
};
/********总线数据发送记录表*********/
struct Data_Bus_Send_Note {
    unsigned int id;
    QDateTime send_time;
    QString data_bus;
    QString send_name;
    unsigned int data_length;
    QString data_text;
    QString remark;
};
/********总线数据接收记录表*********/
struct Data_Bus_Accept_Note {
    unsigned int id;
    QDateTime accept_time;
    QString data_bus;
    QString accept_name;
    unsigned int data_length;
    QString data_text;
    QString remark;
};
/********总线数据监视记录表*********/
struct Data_Bus_Watchon_Note {
    unsigned int id;
    QString data_bus;
    QString data_direction;
    QString data_name;
    unsigned int data_length;
    QString data_text;
    QString remark;
};


//CAN总线数据帧(4+D_LEN)//每一帧前面的4个字节(yyh定义)
struct CAN_DATA
{
    uchar send_mark:1;      //发送标志。0：从管控机发送到下控单机,1：下控单机发送到管控机
    uchar priotity:1;       //动态优先级标志。0：高优先级（默认）1：低优先级
    uchar by:1;             //备用
    uchar re_addr;          //接收节点站地址
    uchar tr_addr;          //发送节点站地址
    uchar comtype:2;        //指令数据帧类型  //00：既是起始帧又是结束帧（即数据只有1帧）
    //01：起始帧（数据有多帧）
    //10：中间帧（数据有多帧）
    //11：结束帧（数据有多帧）
    uchar frameN;           //帧序号。从0开始计数，如果一条指令含有多帧数据，则帧号进行累加，最大值为255。

};

// RapidIO数据包格式（1408字节）
struct RapidIO_STR {
    // 同步头（4）
    uint head;  // 同步头0xeb905716
    // 主导头（36）

    uchar groupmark : 2;  // 2bit分组标志 （后）
    uchar packmark : 6;   // 6bit打包标志 (前)

    uchar standmark;   // 单机标志
    uchar channelnum;  // 通道编号
    uchar udmark;      // 上下行标志

    uint Tpartcode : 8;    // 源地址：部位代码 ^
    uint Tstartmark : 16;  // 源地址：卫星标志 |
    uint Taddrtyp : 8;     // 源地址：地址类型 |

    uint Rpartcode : 8;    // 目的地址：部位代码 ^
    uint Rstartmark : 16;  // 目的地址：卫星标志 |
    uint Raddrtyp : 8;     // 目的地址：地址类型 |

    uint seconds;     // 打包时间：整秒数
    uint nanosecond;  // 打包时间：纳秒数
    uint taskid;      // 任务ID

    ushort smallnum : 8;  // 数据类型：小类号   ^
    ushort bignum : 8;    // 数据类型：大类号   |

    ushort dataflowid;  // 数据流ID
    uint ordercount;    // 序列计数
    uchar bl2[4];       // 保留
    // 数据域（1360）
    ////副导头（10）
    uchar subheadtyp;   // 副导头类型,默认 0x12
    uchar subheadlen;   // 副导头长度,默认 10
    ushort effectlen;   // 有效数据长度，默认 1024
    uchar bl3[4];       // 保留4
    ushort subcontent;  // 副导头内容 0x1f01
    ////数据（1024）
    uchar datas[1024];  // 数据内容
    ////保留（1360-10-1024）326
    uchar bl4[326];
    // 包尾（8）
    ushort Tport;  // 源端口
    ushort Rport;  // 目的端口
    uchar bl5[2];  // 保留
    ushort crc;    // 校验码
};

// 上注软件数据包格式
struct UP_Sorft_pack {
    uint sum_len;     // 数据包总长度
    uchar sorft_num;  // 软件个数
    uchar bl;         // 保留
    //    uchar* files;       //软件数据n
    //    ushort crc;         //CRC校验码
};

// 单个软件数据包格式
struct One_pack {
    uint sorft_len;        // 软件总长度
    ushort sorft_mark;     // 软件代号
    ushort sorft_version;  // 软件版本号
    uint write_addr;       // 软件写入地址
};

//1553千兆网上注指令
struct upOrder_1553str {
    uchar sur_IP[4];        //源IP
    ushort sur_port;        //源端口
    uchar md_IP[4];         //目的IP
    ushort md_port;         //目的端口
    uint file_py;           //文件起始偏移量
    uint file_sendsize;     //文件发送大小*
    ushort only_masssize;   //单个消息块大小
    ushort send_cyc;        //发送周期
    uchar file_path[128];   //文件路径

};


// 千兆网口数据发送结构体 922字节
struct str_QZ {
//    char mac[14];  // MAC头（14字节）
//    char IP[20];   // IP头（20字节）
//    char UDP[8];   // UDP头（8字节）

    //PDU（8字节）
    uchar PDU4[4];    //PDU
    uchar soure_ID;   // 源实体ID
    ushort number;    // 包序号 0开始
    uchar goal_ID;    //目标实体ID

    //914字节
    ushort qzdata_head;     //数据头0x1731
    ushort list_mark;       //0xC000-0xFFFF
    ushort pack_len;       //包长N+1,907
    uchar buff[906];        // 数据
    ushort qz_crc;          //有效数据校验（最后一帧校验在前，填充在最后）
//    uint fcs;         // FCS(4字节)
};


// 千兆网口分段发送结构体(10字节)
struct str_FenDuan {

    uchar fd_mark;      //分段标志
    ushort d_number;    //段号
    uint d_Len;         //段长
    uchar bl[3];        //保留
    //上注数据n(最多110Mb)
    //ushort fd_crc;      //CRC校验

};

//1553上注结构体 1024字节
struct str_1553up{

    ushort pack_mark;       //包标志0x1731
    ushort pack_number;     //包顺序控制
    ushort pack_len;        //包长
    ushort fun_mode;        //功能识别0x0009

    uchar data922[922];        // 数据（封装好922上注文件）

    ushort addcrc;             //异或和校验（功能识别符开始）

    uchar tc[92];           //填充到1024
};

// 1553总线指令 数据包封装格式
struct STR_1553BusInstr {
    // ushort packmark;
    // //包标志（3bit版本号，1bit类型标志，1bit副导头标志，11bit应用过程识别符）
    // 2字节用位域表示
    ushort packmark_d1 : 3;  // 11bit应用过程识别符(高3位)
    // //^低，位序(每个字节的位反序)
    ushort packmark_c : 1;   // 1bit副导头标志                    //|
    ushort packmark_b : 1;   // 1bit类型标志                      //|
    ushort packmark_a : 3;   // 3bit版本号                        //|高
    ushort packmark_d2 : 8;  // 11bit应用过程识别符(低8位)

    // ushort packsequence;    //包顺序控制（2bit序列标志，14bit包名称或序列计数）
    // 2字节用位域表示
    ushort packsequence_b1 : 6;  // 14bit包名称或序列计数(高6位)  ^低
    ushort packsequence_a : 2;   // 2bit序列标志                |高
    ushort packsequence_b2 : 8;  // 14bit包名称或序列计数(低8位)

    ushort packLen;  // 包长

    ushort funrecog;     // 功能识别
    uchar applybuff[2];  // 应用数据
    ushort andcheck;     // 按字异或和校验(功能识别和异或数据)
};
// 1553总线注数指令 数据包封装格式
struct STR_1553OverInstr {
    // ushort packmark;
    // //包标志（3bit版本号，1bit类型标志，1bit副导头标志，11bit应用过程识别符）
    // 2字节用位域表示
    ushort packmark_d1 : 3;  // 11bit应用过程识别符(高3位)
    // //^低，位序(每个字节的位反序)
    ushort packmark_c : 1;   // 1bit副导头标志                    //|
    ushort packmark_b : 1;   // 1bit类型标志                      //|
    ushort packmark_a : 3;   // 3bit版本号                        //|高
    ushort packmark_d2 : 8;  // 11bit应用过程识别符(低8位)

    // ushort packsequence;    //包顺序控制（2bit序列标志，14bit包名称或序列计数）
    // 2字节用位域表示
    ushort packsequence_b1 : 6;  // 14bit包名称或序列计数(高6位)  ^低
    ushort packsequence_a : 2;   // 2bit序列标志                |高
    ushort packsequence_b2 : 8;  // 14bit包名称或序列计数(低8位)

    ushort packLen;  // 包长
    ushort funrecog;  // 功能识别(上注配置0080H,上注透传指令0081H高算力平台1,上注透传指令0082H高算力平台2，
    // 上注非透传指令0083H高算力平台1，上注非透传指令0084H高算力平台2，上注管控指令0085H,上注软件0086H，上注软件补丁0087H,上注任务0088H)
    uchar applybuff[246];  // 应用数据，包含（STR1553_SubPack结构体数据）
    ushort andcheck;  // 按字异或和校验(（功能识别和应用数据）按字异或和校验)
};

// 1553接口协议传输格式(多包进行分包)总线注数封装,一包最长246字节应用数据（2长度+2标志+2帧号+原始数据最长238字节。。+2校验）
struct STR1553_SubPack {
    ushort Len;  // 原始数据长度
    ushort framemark;  // 帧标志（0：只有一帧，1：起始帧，2：中间帧，3：结束帧）2023.8.25改成2字节
    uint frameNUM;  // 帧序号（0开始，高前低后）2023.11.15改成4字节

    uchar* priDataBuff;  // 原始数据
    // 不定长（偶数字节长度，不满偶数补0x2A），最长246-8=238字节
    //    ushort checksum;
    //    //校验和(从“帧标志”开始，到“指令原始数据”，所有数据字按字进行累加和取反)//2023.11.16去除
    // 填充0x2A,一包最长246字节，
};

// 任务基本信息+通用任务基本信息
struct General_Mess {
    // 任务基本信息
    uint task_massageLen;   // 任务基本信息长度
    uchar bl3[4];           // 保留
    // 通用任务基本信息
    uchar gsl_choose;       // 高算力平台选择
    uchar gsl_mainsub;      // 高算力主从选择
    uchar pd_choose;        // 频段选择
    uchar data_choose;      // 数传标志Bit7-Bit4：一 ，Bit3-Bit0：二
    ushort data_speed;      // 数传传输速率
    //uchar isxw_table;     // 是否使用天线阵相位补偿表
    uchar bl1;              // 7.2改为保留
    uchar inch_choose;      // 内校正输出通道
    uchar DA_dbm;           // DA输出幅度衰减值
    uchar bl[2];            // 保留3字节
    uchar zp_change;        // 中频切换开关状态
    ushort sf_fpga1;        // 收发FPGA_1(该字段填0xFFFF。该字段填0xEEEE表示卸载当前加载的软件)
    ushort sf_fpga2;        // 收发FPGA_2
    ushort dataA_fpga1;     // 数据处理板AFPGA_1
    ushort dataA_fpga2;     // 数据处理板AFPGA_2
    ushort dataA_dsp;       // 数据处理板Adsp
    ushort dataB_fpga1;     // 数据处理板BFPGA_1
    ushort dataB_fpga2;     // 数据处理板BFPGA_2
    ushort dataB_dsp;       // 数据处理板Bdsp
    // 不同类型基本信息(不定长)根据功能模式确定
};



//CAN结构体（CAN指令格式）
struct can_kindFz{
    ushort CanorderLen;     // 指令长度
    uchar Canmark;         // 指令标识
    //指令内容
    ushort crc_add;        // 校验和
};


//CAN 广播结构体
struct can_board{
    ushort CanorderLen;     // 指令长度
    uchar Canmark;         // 指令标识
    //指令内容
    uchar bl;               //保留
    ushort crc_add;        // 校验和
};

//CAN 任务下发 结构体--对应1553上注任务类
struct can_C90{
    ushort CanorderLen;     // 指令长度
    uchar Canmark;         // 指令标识
    uchar pack_sum;         //包总数
    uchar pack_number;      //包序号
    //指令内容 1-2041字节
    ushort crc_add;        // 校验和
};

//上注任务格式
struct OntaskFormat {
    uint sumLen;     // 任务包总长度
    ushort taskSum;  // 任务数量
    uchar bl[4];     // 保留
    // N字节数据
    // 2字节crc
};


// 任务N内容
struct TaskContent {
    // 任务内容引导头
    uint taskSumlen;        // 任务长度（包括从“任务长度”到“任务模式参数”的字节总数，有效值范围：0-1348）
    ushort taskflowid;      // 任务流水号(运维管控任务流水号范围,0-9999自主区域任务流水号范围1,0000-19999常规任务流水号范围：20000-65535,任务流水号循环计数)
    ushort main_id;         // 主任务id
    uchar sub_id;           // 子任务id
    ushort start_code;      // 卫星代码
    uchar mainsub_choose;   // 主从标志
    uchar start_sum;        // 协同卫星数量
    uchar fun_mode;         // 功能模式
    uchar work_mode;        // 工作模式
    uchar tasktype;         // 任务类型
    uchar tasksum;          // 任务个数
    uchar mb_mask;          // 模板标志
    uchar bl2[2];           // 保留
    uint task_starttime;    // 任务开始时刻
    uint task_holdtime;     // 任务持续时长

    General_Mess Gener_str;  // 任务基本信息+通用任务基本信息
};

// 电子侦察任务基本信息
struct Elec_Recon {
    ushort datastrim;        // 数据通道流向
    uchar limitspeed;        // 限速速率
    uchar bz_choose;         // 本振选择方式
    uchar aerial_ad;         // 天线与通道对应模式
    uchar bz1_mess;          // 1本振使用信息
    uchar sp_ad[2];          // 射频通道号
    uchar sp_addata[2];      // 射频通道参数设置
    uchar sp_adlow[2];       // 射频通道接收衰减
    uchar aerial_patameter;  // 天线子阵参数
    uchar aerial_time;       // 天线控制间隔时间
    uchar aerial_data;       // 天线指向算法数据源
    uchar aerial_low;        //天线射频发射衰减值,Bit7-Bit6：天线接收衰减值
    uchar switch_Choose;     //开关矩阵选择7.11
    uchar bs_hc;             //波束合成标志7.2
    ushort zz1_lz;           //数字波束1偏置离轴角
    ushort zz1_fw;           //数字波束1偏置方位角
    ushort zz2_lz;           //数字波束2偏置离轴角
    ushort zz2_fw;           //数字波束2偏置方位角
    ushort zz3_lz;           //数字波束3偏置离轴角
    ushort zz3_fw;           //数字波束3偏置方位角
    ushort zz4_lz;           //数字波束4偏置离轴角
    ushort zz4_fw;           //数字波束4偏置方位角


    //
    // 4个天线子阵参数，4种模式
};

// 任务基本信息+通用任务基本信息（拓展功能）
struct General_Mess_2 {
    // 任务基本信息
    uint task_massageLen;   // 任务基本信息长度
    uchar bl3[4];           // 保留???????
    // 通用任务基本信息
    uchar gsl_choose;       // 高算力平台选择
    uchar gsl_mainsub;      // 高算力主从选择
    uchar pd_choose;        // 频段选择
    uchar zp_change;        // 中频切换开关状态
    uchar data_choose;      // 数传标志Bit7-Bit4：一 ，Bit3-Bit0：二
    ushort data_speed;      // 数传传输速率
    uchar bl1[2];           // 7.2改为保留

    ushort sf_fpga1;        // 收发FPGA_1(该字段填0xFFFF。该字段填0xEEEE表示卸载当前加载的软件)
    ushort sf_fpga2;        // 收发FPGA_2
    ushort dataA_fpga1;     // 数据模块1FPGA_1
    ushort dataA_fpga2;     // 数据模块2FPGA_2
    ushort dataA_dsp;       // 数据模块1DSP
    ushort dataB_fpga1;     // 数据模块2FPGA_1
    ushort dataB_fpga2;     // 数据模块2FPGA_2
    ushort dataB_dsp;       // 数据模块2DSP
    ushort sf2_fpga1;       // （高算力2）收发FPGA_1(该字段填0xFFFF。该字段填0xEEEE表示卸载当前加载的软件)
    ushort sf2_fpga2;       // （高算力2）收发FPGA_2
    ushort dataA2_fpga1;    // （高算力2）数据模块1FPGA_1
    ushort dataA2_fpga2;    // （高算力2）数据模块2FPGA_2
    ushort dataA2_dsp;      // （高算力2）数据模块1DSP
    ushort dataB2_fpga1;    // （高算力2）数据模块2FPGA_1
    ushort dataB2_fpga2;    // （高算力2）数据模块2FPGA_2
    ushort dataB2_dsp;      // （高算力2）数据模块2DSP

    // 不同类型基本信息(不定长)根据功能模式确定
};

// 任务N内容--拓展模块
struct TaskContent_2 {
    // 任务内容引导头
    uint taskSumlen;        // 任务长度（包括从“任务长度”到“任务模式参数”的字节总数，有效值范围：0-1348）
    ushort taskflowid;      // 任务流水号(运维管控任务流水号范围,0-9999自主区域任务流水号范围1,0000-19999常规任务流水号范围：20000-65535,任务流水号循环计数)
    ushort main_id;         // 主任务id
    uchar sub_id;           // 子任务id
    ushort start_code;      // 卫星代码
    uchar mainsub_choose;   // 主从标志
    uchar start_sum;        // 保留（协同卫星数量）
    uchar fun_mode;         // 功能模式
    uchar work_mode;        // 工作内核（工作模式）
    uchar tasktype;         // 任务类型
    uchar tasksum;          // 任务个数
    uchar mb_mask;          // 模板标志
    uchar bl2[2];           // 保留
    uint task_starttime;    // 任务开始时刻
    uint task_holdtime;     // 任务持续时长

    General_Mess_2 Gener_str;  // 任务基本信息+通用任务基本信息（拓展功能）
};

// 拓展功能--任务基本信息
struct Tz_Mess {

    ushort datastrim;        // 数据通道流向
    uchar aerial_ad;         // 天线与通道对应模式

    uchar in_ad;             // 内校正输出通道
    uchar DA_out;            // DA输出幅度衰减值
    uchar bz_choose;         // 本振选择方式

    uchar bz1_mess[2];       // 1本振使用信息
    uchar sp_ad[4];          // 射频通道号
    uchar fd_sp[4];          // 放大器使能/射频衰减
    uchar sp_adfs[4];        // 射频通道发射衰减
    uchar sp_adlow[4];       // 射频通道接收衰减
    uchar bl[2];             // 保留
    uchar tx_mode;           // 天线工作模式


    uchar aerial_patameter;  // 天线子阵参数
    uchar aerial_time;       // 天线控制间隔时间
    uchar aerial_data;       // 天线指向算法数据源
    uchar aerial_low;        //天线接收衰减值

    uchar sp_fsd;            //射频发射衰减（L频段）
    uchar kgjzxz;            //开关矩阵选择（L频段）
    uchar rec_xw;            //接收相位/幅度加权码（SXKu频段）
    uchar con_yc;            //组件遥测数据类型（SXKu频段）
    uchar bl2[2];             // 保留


    //
    // 4个天线子阵参数，4种模式
};

// 指向驻留模式参数
struct aerial_ZCmode1_zxzl {
    uchar aerial_zznumber;  // 天线子阵号
    uchar aerial_mode;      // 天线子阵控制模式
    uchar bl[2];            // 保留

    uchar polarmand;    // 极化方式
    uchar bl2[3];       // 保留
    ushort bs_offaxis;  // 波束离轴角指向
    ushort bs_bearing;  // 波束方位角指向
};

struct Cyc_zxsm {
    ushort bs_offaxis;  // 波束离轴角指向
    ushort bs_bearing;  // 波束方位角指向
};

// 指向扫描模式参数
struct aerial_ZCmode2_zxsm {
    uchar aerial_zznumber;  // 天线子阵号
    uchar aerial_mode;      // 天线子阵控制模式
    uchar bl[2];            // 保留

    uchar polarmand;  // 极化方式

    uchar bl2[1];     // 保留
    uchar zx_ontime;  // 指向驻留时间
    uchar pointsum;   // 指向个数（。。。。1-8循环体）

    Cyc_zxsm cyc[255];  // 开辟8块，过长减去长度
};
// 指向扫描模式参数_2
struct aerial_ZCmode2_zxsm_2 {
    uchar aerial_zznumber;  // 天线子阵号
    uchar aerial_mode;      // 天线子阵控制模式
    uchar bl[2];            // 保留

    uchar polarmand;  // 极化方式

    uchar bl2[1];     // 保留
    uchar zx_ontime;  // 指向驻留时间
    uchar pointsum;   // 指向个数（。。。。1-8循环体）

};

// 区域凝视模式参数
struct aerial_ZCmode3_qyns {
    uchar aerial_zznumber;  // 天线子阵号
    uchar aerial_mode;      // 天线子阵控制模式
    uchar bl[2];            // 保留

    uchar polarmand;       // 极化方式
    uchar bl2[3];          // 保留
    uint target_orb;       // 目标经度
    uint target_latitude;  // 目标纬度
};

struct Cyc_qysm {
    uint region_orb;       // 区域点经度
    uint region_latitude;  // 区域点纬度
};

// 区域扫描模式参数
struct aerial_ZCmode4_qysm {
    uchar aerial_zznumber;  // 天线子阵号
    uchar aerial_mode;      // 天线子阵控制模式
    uchar bl[2];            // 保留

    uchar polarmand;       // 极化方式
    uchar region_onntime;  // 区域驻留时间
    ushort region_sum;     // 区域点个数。。。。1-5循环体）

    Cyc_qysm cyc[5];
};

// 电子干扰任务基本信息
struct Elec_Jamming {
    ushort datastrim;        // 数据通道流向
    uchar bz_choose;         // 本振选择方式

    uchar txytddyms;         // 天线与通道对应模式
    uchar bz1_mess;          // 1本振使用信息
    uchar bl1[2];             //保留
    uchar sp_addata[2];      // 射频通道参数设置

    uchar sp_adlow[2];       // 射频通道发射衰减
    uchar sp_jslow[2];       // 射频通道接收衰减

    uchar aerial_patameter;  // 天线子阵参数
    uchar aerial_mode;       // 天线子阵控制模式
    uchar aerial_time;       // 天线间隔时间
    uchar aerial_pointing;   // 天线指向算法数据源
    uchar aerial_low;       //天线射频发射衰减值,Bit7-Bit6：天线接收衰减值,Bit5-Bit0：L频段天线发射衰减值
    uchar bl[2];            //保留2

    // 天线子阵参数，当模式为3时有效
};


// SAR探测任务基本信息
struct SAR_Str {


    ushort sf_FPGA_1;   //收发FPGA_1
    ushort sf_FPGA_2;   //收发FPGA_2
    ushort A_FPGA_1;    //数据处理板A的FPGA_1
    ushort A_FPGA_2;    //数据处理板A的FPGA_2
    ushort A_dsp;       //数据处理板A的DSP
    ushort B_FPGA_1;    //数据处理板B的FPGA_1
    ushort B_FPGA_2;    //数据处理板B的FPGA_2
    ushort B_dsp;       //数据处理板B的DSP


    uchar is_yd;            //bit7-bit4:引导方式 bit3-bit0:侦察定位模式
    uchar is_cx;            //是否实时成像
    uchar aerial_ad;        // 天线与通道对应模式
    uchar sp_ad;            // 射频通道号
    uchar sp_addata;        // 射频通道参数设置
    uchar sp_fslow;         // 射频通道发射衰减
    uchar sp_jslow;         // 射频通道接收衰减
    uint yddz;              // 引导地址
    uchar bl[4];            // 保留
};

// 备用导航任务
struct Elec_BYnavigation {
    ushort datastrim;        // 数据通道流向7.16更改（改0）
    uchar aerial_ad;         // 天线与通道对应模式
    uchar sp_ad;             // 射频通道号
    uchar sp_addata;         // 射频通道参数设置(改保留)
    uchar sp_fslow;          // 射频通道发射衰减
    uchar aerial_patameter;  // 天线子阵参数
    uchar aerial_time;       // 天线控制间隔时间
    uchar aerial_data;      // Bit0：天线指向算法数据源
    uchar aerial_low;       //天线射频发射衰减值,Bit7-Bit6：天线接收衰减值,Bit5-Bit0：L频段天线发射衰减值
    uchar bl[2];            //保留2
    //
    // 4个天线子阵参数，4种模式
};

struct TZZCS
{
    uchar TzzZh;        //天线子阵号
    uchar TzzctrlMode;  //天线子阵控制模式
    uchar keepValue[2]; //保留
    int area_X;         //区域点经度
    int area_Y;         //区域点纬度
};
// 类5G任务基本信息
struct Kind5G_Str {
    ushort datastrim;        // 数据通道流向
    uchar bz_choose;         // 本振选择方式
    uchar bz1_mess;          // 1本振使用信息
    uchar aerial_ad;         // 天线与通道对应模式
    uchar sp_ad;             // 射频通道号
    uchar sp_addata;         // 射频通道参数设置
    uchar sp_adlow;          // 射频通道接收衰减
    uchar sp_fslow;          // 射频通道发射衰减
    uchar aerial_patameter;  // 天线子阵参数
    uchar aerial_time;       // 天线控制间隔时间
    uchar aerial_data;       // 天线指向算法数据源
    uchar aerial_low;        //天线射频发射衰减值,Bit7-Bit6：天线接收衰减值,Bit5-Bit0：L频段天线发射衰减值
    uchar switch_Choose;     //开关矩阵选择
    uchar bl[1];             //保留1
    //
    // 4个天线子阵参数，4种模式
};

// 指向驻留模式参数
struct aerial_GRmode1_zxzl {
    uchar polarmand;    // 极化方式
    uchar qh_time;      // 极化切换时间
    uchar bl2[2];       // 保留
    ushort bs_offaxis;  // 波束离轴角指向
    ushort bs_bearing;  // 波束方位角指向
};
// 指向扫描模式参数
struct aerial_GRmode2_zxsm {
    uchar polarmand;  // 极化方式
    uchar qh_time;    // 极化切换时间
    uchar zx_ontime;  // 指向驻留时间

    uchar pointsum;   // 指向个数（。。。。1-255循环体）

    Cyc_zxsm cyc[255];  // 开辟8块，过长减去长度
};

// 指向扫描模式参数2
struct aerial_GRmode2_zxsm2 {
    uchar polarmand;  // 极化方式
    uchar qh_time;    // 极化切换时间
    uchar zx_ontime;  // 指向驻留时间

    uchar pointsum;   // 指向个数（。。。。1-255循环体）


};
// 区域凝视模式参数
struct aerial_GRmode3_qyns {
    uint target_orb;       // 目标经度
    uint target_latitude;  // 目标纬度
    uchar polarmand;       // 极化方式
    uchar qh_time;         // 极化切换时间
};


// SXKu天线定标任务
struct Elec_sxkuDB {
    ushort datastrim;    // 数据通道流向
    uchar bz_choose;     // 本振选择方式
    uchar bz1_mess;      // 1本振使用信息
    uchar tx_mode;       // 天线与通道对应模式（新增）
    uchar spAD;          // 射频通道号（新增）
    uchar sp_addata;     // 射频通道参数设置
    uchar sp_recvlow;    // 射频通道接收衰减
    uchar sp_sendlow;    // 射频通道发射衰减
    uint  fre;            // 接收机频率KHz
    uchar ZMHV;          // 阵面H/V极化选择
    uchar zdyx;          // 指定移相值
    uchar zdlow;         // 指定衰减值
    uchar zddelayed;     // 指定延时（小位）值
    uchar zdbigdelayed;  // 指定延时（大位/中位）值
};

// J链任务基本信息
struct J_chainSTR {
    ushort datastrim;    // 数据通道流向
    uchar txytddyms;         // 天线与通道对应模式

    uchar sp_ad;          //射频通道号
    uchar sp_addata2;    // 射频通道参数设置
    uchar sp_recvlow2;   // 射频通道接收衰减
    uchar sp_sendlow;    // 射频通道发射衰减

    uchar aerial_patameter;  // 天线子阵参数
    uchar aerial_time;       // 天线控制间隔时间
    uchar aerial_data;      // 天线指向算法数据源
    uchar aerial_low;       //天线射频发射衰减值,Bit7-Bit6：天线接收衰减值,Bit5-Bit0：L频段天线发射衰减值
    uchar bl[2];            //保留2
    //
    // 4个天线子阵参数，4种模式

};

struct J_TxZZCS
{
    uchar TzzZh;        //天线子阵号
    uchar TzzctrlMode;  //天线子阵控制模式
    uchar keepValue[2]; //保留
    int area_X;         //区域点经度
    int area_Y;         //区域点纬度
};

//引导卫星个数---N(不定长内容)
struct ModePart_yd{
    uchar yd_startMode;    //引导卫星工作模式(不定长)
    uint yd_startAddr;     //引导卫星目的地址(不定长)
};

// 任务模式参数。。。。N
struct Task_ModeParameter {
    uint taskmodeLen;        // 任务模式参数长度
    uchar task_fpgachoose;   // 任务执行fpga选择
    uchar dx_marsk;          // 定位标志
    uchar RH_AI_mask;        // bit7-bit4,融合标志  bit3-bit0,AI识别标志
    // 三星定位参数
    uchar third_site[4];     // 三星定位主星地址12.1.1.165
    ushort third_base_site;  // 三星定位主星基地址
    uchar start_mode;        // 多星定位工作模式
    uchar satelliteSum;      // 定位参数卫星个数
    //  uint md_addr;        // 协同引导卫星目的地址(不定长)
    //引导参数
    //uchar yd_startNum;     //引导参数卫星个数
    //uchar yd_startMode;    //引导卫星工作模式(不定长)
    //uint yd_startAddr;     //引导卫星目的地址(不定长)

    // 任务模式类型
    //  uchar task_modetype;  // 任务模式类型
};

// 全景工作模式
struct Str_QJmode {
    uchar bl1;      // 保留1
    uchar bl2;      // 保留2
    uchar AD_num;   // 单通道AD采样存储深度
    uchar cj_mand;  // 采集触发方式
    uchar cfmx;     // 触发门限
    uchar pd_sum;   // 频段个数
    // 多个可能
    //  uint start_fre;  // 起始频率(KHz)
    //  uint end_fre;    // 终止频率
    //  uint mid_fre;    // 瞬时频率
};

struct Str_QJmode_p2 {
    // 多个可能
    uint start_fre;  // 起始频率(协议里最小KHz)
    uint end_fre;    // 终止频率(协议里最小KHz)
    uint mid_fre;    // 瞬时频率(协议里最小Hz)
};

// 常规信号频点控守参数
struct gen_Sig_Ctr_HEAD {
    uchar investMode;      // 侦察模式
    uchar cscl_sum;        // 参数测量次数
    uchar bl[4];            //保留
    uint reciveFre;        // 接收机频率
    uchar iq_len;        // iq长度
    uchar CyChannelNum_N;  // 采样信道总数N
};

/*常规信号频点控守参数采样*/
struct cgxhpdks_cy {
    uchar bl;               // 保留
    int NCOFre_N;          // NCO频率Hz
    uint CyPer_N;           // 采样带宽KHz
    uchar examDoorLimit_N;  // 检测门限 Bit7：门限标志，恒为1；Bit6~0：门限值
};

// LINK16信号频点控守参数
struct Link16_Signal_Ctrl {
    uint FreError;         // 频偏Hz
    uchar examChannelSel;  // 检测通道选择
    uchar mckind;          // 脉冲类型
    uchar is_pdw;          // PDW数据是否下传标识
    uchar measureFlag;     // 是否测向
    uchar cx_pd;           // 测向频段
    uchar measureLine;     // 测向基线
    uchar corChannelSel;   // 校正谱通道选择
    uchar cx_oder;         // 测向门限
    uchar jx_mainer;         // 校正方式 5.31新加
    uchar ssqy;             // 搜索区域宽度 6.27新加
    uchar bl[2];           // 保留
};

// 塔康信号频点控守参数
struct Tk_Signal_Ctrl {
    uint examChannelSel;  // 检测通道选择
    uchar measureFlag;    // 是否测向
    uchar cxpd;           // 测向频段
    uchar measureLine;    // 测向基线
    uchar corChannelSel;  // 校正谱通道选择
    uchar cx_oder;        // 测向门限
    uchar tc_downmark;    // 塔康信号下传标志
    uchar jz_mand;        // 校正方式
    uchar sskd;           // 搜索区域宽度 6.27新加
    uchar bl[1];          // 保留
};

// 敌我识别信号频点控守
struct DW_Signal_Ctrl {

    uint examChannelSel;  // 检测通道选择

    uint pulseWidth_min;  // 脉冲最小截取宽度
    uint pulseWidth_max;  // 脉冲最大截取宽度
    uint IFF_mode;        // IFF信号工作模式
    uchar measureFlag;    // 是否测向

    uchar measureLine;    // 测向基线选择
    uint corChannelSel;   // 校正谱通道选择

    ushort pace;          // 步进
    uchar cx_oder;        // 测向门限
    uchar dw_downmark;    // 敌我识别下传标志
    uchar jz_mand;        // 校正方式
    uchar sskd;           // 搜索区域宽度 6.27新加
    uchar bl[1];          // 保留
};

// 铱星信号频点控守参数
struct YX_Signal_Ctrl {
    uint DeTEctionChannel;  // 检测通道选择

    uchar uptimeon;         //突发时长 目前固定8ms
    uchar jc_door;          //检测门限 单位dB
    uchar measureFlag;      // 是否测向
    uchar cxmx;             // 测向门限
    uchar jz_manner;        // 测向校正方式
    uchar relationData;     //相关系数
    uchar tzmode;           //特征模板选择
    uchar bitJudge;         //Bit判决标志

    uchar ch_shield[32];    //通道屏蔽,256个通道，bit值为0表示不屏蔽，为1表示屏蔽
};

// 海事信号频点控守参数
struct HS_Signal_Ctrl {};

// 雷达信号频点控守参数
struct Radar_Siganl_Ctrl {

    uint reFre;         //接收机频率 KHz
    int ncoFre;         //NCO频率 单位，Hz
    uchar fpgaDoor;     //FPGA检测门限
    uchar downchoose;   //下行数据选择
    int clb_NCO;        //处理板NCO频率Hz
    uint cl_wide;       //处理带宽KHz

    uchar csChoose;     //参数信息选择
    uchar bl[1];        //保留
    uchar groupMark;    //分选任务标志
    uchar jfxMark;      //精分析任务标志
    uchar zcChoose;     //侦察目标选择

};

// 星链信号频点控守参数
struct StarLink_Siganl_Ctrl {
    uint re_fre;         // 接收机频率KHz
    uchar hx_bz;        //互相关与自相关比值
    uchar twoMc;        //双窗门限
    uchar NCOs;         //NCO路数
    //...多个
    //int nco_fre;        //NCO频率

};

// 同步采样
struct Str_tbCy {
    uint re_fre;         // 接收机频率KHz
    int nco_fre;        // 收发板NCO频率 Hz

    uchar cy_cnt;        // 采样次数
    uchar cy_deep;      // 单次采样深度14-30（2的幂次方）
    uchar bl[2];        // 保留

};
// 上注软件解调
struct Str_upsorft {
    uint re_fre;            // 接收机频率KHz
    int nco_fre;            // 频偏Hz
    int cy_deep;           // 码速率Hz
    uint data_cnt;          //数据帧数
    uchar ys;               //样式

    uchar bl[3];            // 保留

};


// 雷达信号频点扫描参数
struct Radar_Siganl_Scan {

    uchar fpgaDoor;     //FPGA检测门限
    uchar downchoose;   //下行数据选择
    uchar groupMark;    //分选任务标志
    uchar groupMark2;   //精分析任务标志
    uchar zcChoose;     //侦察目标选择
    uchar smFrenum;     //扫描频点个数
    uchar smFreontime;  //扫描频点驻留时间

    //循环体----根据上面扫描频点个数
    //uint reFre;     //接收机中心频率单位：KHz

};


struct StarLink_Siganl_Scan_1 {
    uint recFre;       // 接收机频率
    ushort doorLimit;  // 门限
};

/**********电子干扰任务模式参数***********/
// 通信干扰快速多目标/扫频干扰任务格式
// 多频点快速干扰
struct TxSp_Interfere_Task_Head {
    int recFre;          // 接收机频率 KHz
    uchar interfereNum;  // 干扰频率数(频点数≤8个)
};
// 多频点快速干扰--循环体
struct TxSp_Interfere_Task {
    //    int recFre;                 //接收机频率
    //    uchar interfereNum;         //干扰频率数

    int digitFre;          // 数字频率
    uint modeSelect;       // 模式选择
    uint scanWidth;        // 扫频带宽
    uint scanInterval;     // 扫频间隔
    uint scanStandTime;    // 扫频驻留时间
    short interfereRange;  // 干扰幅度
    uchar interfereStyle;  // 干扰样式
    uint interfereParam1;  // 干扰参数1(带宽/码速率）
    uint interfereParam2;  // 干扰参数2(FSK频偏）
    uint interfereParam3;  // 干扰参数3(码流选择）
    uint interfereParam4;  // 干扰参数4(多项式参数）
    uint interfereParam5;  // 干扰参数5(多项式参数）
};

// 等间隔梳状谱干扰
struct pos_intervarComb_Head {
    uint recFre;           // 接收机频率khz
    short interfereRange;  // 干扰幅度
    uchar interfereStyle;  // 干扰样式
    uint interfereParam1;  // 干扰参数1(带宽/码速率）
    uint interfereParam2;  // 干扰参数2(FSK频偏）
    uint interfereParam3;  // 干扰参数3(码流选择）
    uint interfereParam4;  // 干扰参数4(多项式参数）
    uint interfereParam5;  // 干扰参数5(多项式参数）
    uchar combNum;         // 梳状谱段数
};

// 等间隔梳状谱干扰--循环体
struct pos_intervarComb_2 {
    short combRange;    // 梳状谱幅度0.1dB
    uint combFre;       // 梳状谱中心频率hz
    uint combWidth;     // 梳状谱干扰带宽hz
    uint combinterval;  // 梳状谱干扰间隔hz
};

// 非等间隔梳状谱干扰
struct nav_IntervarCombk_HEAD {
    uint recFre;            // 接收机频率khz
    short interfereRange;   // 干扰幅度0为最大，0.1dB为单位
    uchar interfereStyle;   // 干扰样式
    uint interfereParam1;   // 干扰参数1(带宽/码速率）
    uint interfereParam2;   // 干扰参数2(FSK频偏）hz
    uchar interfereParam3;  // 干扰参数3(码流选择）
    uint interfereParam4;   // 干扰参数4(多项式参数）
    uint interfereParam5;   // 干扰参数5(多项式参数）
    uint combFreNum;        // 梳状谱频率数(<100)
};

// 非等间隔梳状谱干扰--循环体
struct nav_IntervarComb_2 {
    short comInterfereRange;  // 梳状谱干扰幅度
    int comInterfereFre;      // 梳状谱干扰频率
};

// 多通道快速变极化协同干扰
struct target_interfere_Task {
    uint recFre;             // 接收机频率khz
    uchar bl[4];               //保留
    uchar L1_L2;               //L1，L2是否同步
    int zz1216grxhszpl;      // 子阵1、2第一级16个干扰信号数字频率
    int zz3416grxhszpl;      // 子阵3、4第一级16个干扰信号数字频率
    int zz12QPSKszpl;        // 子阵1、2 QPSK数字频率
    uchar zz12QPSKszxhkg;    // 子阵1、2 QPSK数字信号开关 0：关闭；1：开启
    int zz12QPSKszxhfhsl;    // 子阵1、2 QPSK数字信号符号速率
    short zz12QPSKszxhgrfd;  // 子阵1、2 QPSK数字信号干扰幅度 单位：0.1dB
    int zz34QPSKszpl;        // 子阵3  4 QPSK数字频率
    uchar zz34QPSKszxhkg;    // 子阵3、4 QPSK数字信号 开 关
    int zz34QPSKszxhfhsl;    // 子阵3、4 QPSK数字信号符号速率
    short zz34QPSKszxhgrfd;  // 子阵3、4 QPSK数字信号干扰幅度 单 位：0.1dB
    uchar zz1216grxhgs;      // 子阵1、2的16个干扰信号个数
    uchar zz3416grxhgs;      // 子阵3、4的16个干扰信号个数
};
// 多通道快速变极化协同干扰---循环体
struct target_interfere_Task_2 {
    int digitFre;           // 数字频率
    short interfereRange;   // 干扰幅度 单位：0.1dB
    uchar interfereStyle;   // 干扰样式
    uint interfereParam1;   // 干扰参数1(带宽/码速率）
    uint interfereParam2;   // 干扰参数2(FSK频偏）
    uchar interfereParam3;  // 干扰参数3(码流选择）
    uchar interfereParam4;  // 干扰参数4(多项式参数）
    uint interfereParam5;   // 干扰参数5(预留）
};
// 多通道多带宽协同干扰(星链目标干扰)
struct StarLink_Siganl_Task {
    int recFre;            // 接收机频率khz
    short interfereRange;  // 干扰幅度0.1dB
    uchar interfereStyle;  // 干扰样式
    uint interfereParam1;  // 干扰参数1(带宽/码速率）
    uint interfereParam2;  // 干扰参数2(FSK频偏）
    uint interfereParam3;  // 干扰参数3(码流选择）hz
    uint interfereParam4;  // 干扰参数4(多项式参数）
    uint interfereParam5;  // 干扰参数5(多项式参数）

    uchar bl;               // 保留
    uchar szp1spkg;        // 梳状谱1扫频开关
    uint szp1spzdk;        // 梳状谱1扫频总带宽
    uint szp1spsd;         // 梳状谱1扫频速度
    uchar szpds1;          // 梳状谱段数1

};

// 多通道多带宽协同干扰(星链目标干扰)---循环体
struct StarLink_Siganl_Task_1 {
    int combFre;        // 梳状谱中心频率hz
    uint combWidth;     // 梳状谱干扰带宽hz
    uint combinterval;  // 梳状谱干扰间隔
};

// 雷达强制干扰任务格式
struct Radar_force_Task {
    uint recFre;       //接收机调谐频率Khz
    uchar fSwitch1234; //1234通道频偏开启
    uint ad13fpre;     //13通道频偏
    uint ad24fpre;     //24通道频偏
    uchar grMode;       //干扰样式
    uint gr_data1;      //干扰参数1（带宽/码速率）
    uint gr_data2;      //干扰参数2
    uint bl1;           //保留字段1
    uint bl2;           //保留字段2
    uint bl3;           //保留字段3
    uint bl4;           //保留字段4
    ushort gr_frenum;   //干扰频点数
    ////循环体
    //谱线干扰幅度
    //谱线频率

};

struct CYC_force_Task {
    ushort px_grdB;     //谱线干扰幅度
    int px_fre;         //谱线基带频率
};

// 雷达自主侦察干扰任务格式
struct Radar_Interfer_Task {
    uint recFre;            //接收机调谐频率KHz
    uchar fSwitch1234;      //1234通道频偏开启
    uint ad13fpre;          //13通道频偏Hz为单位
    uint ad24fpre;          //24通道频偏Hz为单位


    //侦察参数
    uchar zc_maskchoose;    //侦察参数--侦察目标选择
    uint bl1;               //保留字段1
    uint bl2;               //保留字段2
    uint bl3;               //保留字段3
    uint bl4;               //保留字段4
    int clb_nco;            //处理板NCO频率
    uint clWide;            //处理带宽

    uchar gr_cl;            //干扰策略
    uchar zc_jcmx;          //侦察参数--检测门限

    int gr_protecU1;       //保护载频上限_1 hz
    int gr_protecD1;       //保护载频下限_1
    int gr_protecU2;       //保护载频上限_2
    int gr_protecD2;       //保护载频下限_2


};




//备用导航任务模式参数（T41.1）
struct SpareNavigat_Str {

    uchar pseudo_code;      //是否修改伪码
    ushort G1polynomial;    //G1多项式
    ushort G1initV;         //G1初相
    ushort G2polynomial;    //G2多项式
    ushort G2initV;         //G2初相
    uchar signal_mode;      //信号模式
    uchar work_mode;        //工作模式
    uint zerodata;          //零值参数


};
//类5G任务模式参数
struct L5G_Str {

    uint fre;           //接收机频率kHz
    ushort l5_mx;       //门限
    uchar codeIndex;    //调制编码索引
    uchar DA1;           //DA幅度校平衰减1
    uchar DA2;           //DA幅度校平衰减2
    uchar DA3;           //DA幅度校平衰减3
    uchar DA4;           //DA幅度校平衰减4
    uchar bl[13];       //保留

    uchar fileSum;      //数传文件数量


};

//类5G任务模式参数--文件名循环体
struct L5GStr_cycFile {

    uint time;       //时间
    ushort streamNum;//流水号
    uchar bl[2];      //保留


};


//J链任务模式参数
struct J_Str {

    ushort wx_mark;     //卫星平台编识号
    ushort net_ID;      //网络设计ID
    ushort tx_ID;       //通信规划ID
    uchar cent_rep;     //地面区域中心报告
    uchar cent_update;  //地面区域中心更新策略
    uchar bl1[2];       //保留
    uchar fg_mode;      //覆盖保障模式
    uchar zf_mode;      //转发模式
    ushort dp_data;     //点频参数
    uchar dp_kh;        //跳频库号
    uchar dp_xh;        //跳频序号
    uchar test_m1;      //测试模式1
    uchar test_m2;      //测试模式2
    uchar test_m3;      //测试模式3
    uchar test_m4;      //测试模式4
    uchar ZHS_IP[4];        //ZHS落地IP
    uchar ZX_IP[4];         //ZX落地IP
    ushort wx2PTbh;         //卫星2平台编识号
    uchar wx2PTip[4];       //卫星2平台IP
    uchar glChoose;     //过滤器选择
    uchar sour_NPG1;    //源NPG1
    uchar sour_NPG2;    //源NPG2
    uchar sour_NPG3;    //源NPG3
    uchar sour_NPG4;    //源NPG4
    uchar sour_NPG5;    //源NPG5
    ushort PT_mark1;    //源平台编识号1
    ushort PT_mark2;    //源平台编识号2
    ushort PT_mark3;    //源平台编识号3
    ushort PT_mark4;    //源平台编识号4
    ushort PT_mark5;    //源平台编识号5


};

/*************************************************
 <类   名>    1553总线指令 结构体
 <概要说明>    无
 <详细说明>    无

 <作    者>   yhh ybl
 <时    间>   2023-08-24
 <修    改>
**************************************************/
// 1553总线指令 关机准备
struct Sorder_shutdown {
    uchar ordermark;    // 指令标志
    uchar controlunit;  // 管控单元
};

// 1553总线指令 管理模式
struct Manage_mode {
    uchar ordermark;     // 指令标志
    uchar manage_style;  // 管理模式
};

// 1553总线指令 常规和区域任务选择
struct CommonAndArea_task {
    uchar ordermark;  // 指令标志
    uchar task_mode;  // 任务模式
};

// 1553总线指令 运维列表开关
struct OperAndMaintain_switch {
    uchar ordermark;     // 指令标志
    uchar sequence_num;  // 序号
};

// 1553总线指令 区域任务列表开关
struct Areatask_switch {
    uchar ordermark;     // 指令标志
    uchar sequence_num;  // 序号
};

// 1553总线指令 看门狗控制
struct WatchDog_control {
    uchar ordermark;        // 指令标志
    uchar magcontrol_mode;  // 管控软件看门狗（关闭/启动）
};

// 1553总线指令 管控软件加载选择
struct Software_load_choose {
    uchar ordermark;        // 指令标志
    uchar software_choose;  // 加载参数
};

// 1553总线指令 OC电压控制
struct OC_power_control {
    uchar ordermark;     // 指令标志
    uchar power_choose;  // 上下电选择
};

// 1553总线指令 Can电压控制
struct Can_power_control {
    uchar ordermark;     // 指令标志
    uchar power_choose;  // 操作参数
};

// 1553总线指令 Flash格式化
struct Flash_Format {
    uchar ordermark;        // 指令标志
    uchar capacity_choose;  // 容量选择
};

// 1553总线指令 综合管控单元SSD清空
struct SSD_clear {
    uchar ordermark;  // 指令标志
    uchar reserve;    //分区
};

// 1553总线指令 SSD重启
struct SSD_restart {
    uchar ordermark;  // 指令标志
    uchar reserve;    // 保留字节
};

// 1553总线指令 单机上下电控制方式
struct Standalone_updown_control {
    uchar ordermark;     // 指令标志
    uchar control_mode;  // 控制模式（计时/非计时）
};

// 1553总线指令 单机上电时间
struct Standalone_supplypower {
    uchar ordermark;              // 指令标志
    uchar supply_power_time = 1;  // 计时单位（分钟）
};

// 1553总线指令 单机复位
struct Standalone_reset {
    uchar ordermark;    // 指令标志
    uchar reset_style;  // 单机复位模式
};


/*************************************************
 <类   名>    1553总线注数指令 结构体
 <概要说明>    无
 <详细说明>    无

 <作    者>   ybl
 <时    间>   2023-08-24
 <修    改>
**************************************************/
// 1553总线注数指令 阵面2次电源控制指令
struct Sorder_secele {
    uchar ordermark;       // 指令标志
    uchar submatrix;       // 子阵
    uchar transceiver;     // 接收发射
    uchar switchelectric;  // 开关电
};

// 1553总线注数指令 射频收发电源控制
struct Radio_RAD_Power {
    uchar ordermark;       // 指令标志
    uchar transceiver;     // 接收发射
    uchar switchelectric;  // 开关电
};

// 1553总线注数指令 射频收发开关控制
struct Radio_RAD_Switch {
    uchar ordermark;      // 指令标志
    uchar switchcontrol;  // 开关控制
};

// 1553总线注数指令 RS422线路控制选择
struct RS422_line {
    uchar ordermark;     // 指令标志
    uchar controlpower;  // 控制权
};


// 1553总线指令 GD编号
struct Software_GD {
    uchar ordermark;  // 指令标志
    uchar BH;         // 编号
};
struct SXtime{
    int time;
};

/*************************************************
 <类   名>    1553总线注数指令 FLASH编码写
 <概要说明>    无
 <详细说明>    无

 <作    者>   ybl
 <时    间>   2023-08-24
 <修    改>   2023-08-29
**************************************************/
struct Flash_codewrite {
    uchar ordermark;         // 指令标志
    uchar use_length;        // 有效长度
    uchar beginmark_high;    // FLASH起始地址（高字节）
    uchar beginmark_medium;  // FLASH起始地址（中字节）
    uchar beginmark_low;     // FLASH起始地址（低字节）
    uchar no_use;            // 保留字
    uchar content;           // FLASH内容
};

/*************************************************
 <类   名>    1553总线注数指令 FLASH编码读
 <概要说明>    无
 <详细说明>    无

 <作    者>   ybl
 <时    间>   2023-08-29
 <修    改>
**************************************************/
struct Flash_coderead {
    uchar ordermark;  // 指令标志
    uchar reserve;
};

/*************************************************
 <类   名>    1553总线注数指令 FLASH直接写
 <概要说明>    无
 <详细说明>    无

 <作    者>   ybl
 <时    间>   2023-08-24
 <修    改>   2023-08-29
**************************************************/
struct Flash_directwrite {
    uchar ordermark;         // 指令标志
    uchar use_length;        // 有效长度
    uchar beginmark_high;    // FLASH起始地址（高字节）
    uchar beginmark_medium;  // FLASH起始地址（中字节）
    uchar beginmark_low;     // FLASH起始地址（低字节）
    uchar no_use;            // 保留字
    uchar content;           // FLASH内容
};

/*************************************************
 <类   名>    1553总线注数指令 FLASH直接读
 <概要说明>    无
 <详细说明>    无

 <作    者>   ybl
 <时    间>   2023-08-29
 <修    改>
**************************************************/
struct Flash_directread {
    uchar ordermark;  // 指令标志
    uchar reserve;    // 保留
};

// 1553总线注数指令 FLASH擦除
struct Flash_eliminate {
    uchar ordermark;         // 指令标志
    uchar beginmark_high;    // FLASH起始地址（高字节）
    uchar beginmark_medium;  // FLASH起始地址（中字节）
    uchar beginmark_low;     // FLASH起始地址（低字节）
};

// 1553总线注数指令 工作时长设置
struct Work_time_set {
    uchar ordermark;  // 指令标志
    ushort worktime;  // 工作时长，单位：秒
};

// 1553总线注数指令 T/R开关控制
struct TandR_switch {
    uchar ordermark;         // 指令标志
    uchar submatrix_switch;  // 子阵开关
};

/*************************************************
 <类   名>    1553总线注数类CAN c综合管控
 <概要说明>    无
 <详细说明>    无

 <作    者>   ybl
 <时    间>   2023-08-31
 <修    改>
**************************************************/
 // 任务n UID
struct strtaskUID{
    ushort main_uid;
    ushort sub_uid;
};

// 预置模板任务删除(按任务ID)
struct Premodel_task_elibyid {
    uchar ordermark;    // 指令标识
    uchar tasknum;      // 任务个数，最大50个
    ushort task_UID[50];  // 任务n 流水ID
};

// 任务删除(按高频段)
struct Task_eli_byHighFrequency {
    uchar ordermark;          // 指令标识
    uchar task_type;          // 任务类型
    uchar frequencyband_num;  // 频段号
    uchar bl;                 // 保留
};


// 任务删除(按UID)
struct Task_eli_byUID {
    uchar ordermark;    // 指令标识
    uchar tasknum;      // 任务个数，最大50个
    strtaskUID task_UID[50];  // 任务n UID(主id,子id)
};

// 任务删除(按高算力平台)
struct Task_eli_byHighCalculate {
    uchar ordermark;        // 指令标识
    uchar startalone_mask;  // 单机标志
};

// 任务清除
struct Outdate_task_clear {
    uchar ordermark;    // 指令标识
    uchar task_type;    // 任务类型
    uchar clear_type;  // 清除类型
};

// 过时任务自动清除功能
struct Outdate_task_autoclear {
    uchar ordermark;       // 指令标识
    uchar autoclear_mask;  // 自动清除标志
};

// 停止当前执行的任务0x39
struct str_39 {
    uchar ordermark;            // 指令标识
    uchar stop_sum;             //停止任务数量
    ushort mask_stream;           //任务流水号
    ushort main_uid;             //任务主UID
    uchar bl[2];                //保留2


};
// 管控任务数据下传0x32
struct str_32 {
    uchar ordermark;      // 指令标识
    uchar task_kind;      //任务类型
    uchar data_ch;       //数传通道
    uchar bl;            //保留


};

// 上注配置0x3A
struct UP_set {
    uchar ordermark;          // 指令标识
    uchar bl;    // 保留
    ushort set_num;            //配置代号
    uint str_addr;            //起始地址
    uint set_size;            //配置大小
    uchar data[40960];        //配置内容最大40kb
    ushort crc;             //异或和校验(从指令标识至配置内容的校验)

};


// 模板校验 0x3C
struct str_3C {
    uchar ordermark;          // 指令标识
    ushort streamID;         //流水号
    uint sTime;            //起始时间
    uint eTime;            //结束时间
    uchar bl;              //保留


};

// 综合管控单元SSD文件删除  0x3E
struct Controlmachine_file_delete {
    uchar ordermark;       // 指令标识
    uchar file_name[8];      // 文件名
    uchar fq;               // 分区
};

// 管控机SSD文件回读下传0x3F
struct SSD_data_download {
    uchar ordermark;       // 指令标识
    uchar bl;              // 保留0xFF
    uchar file_name[8];   // 文件名
    long long py;           // 偏移量
    long long dataSum;      // 数据总量
};

// 管控机CAN复位
struct ControlMachine_CAN_reset {
    uchar ordermark;     // 指令标识
    uchar reset_choose;  // 复位选择
};

// 测试数传
struct Test_num_trans {
    uchar ordermark;          // 指令标识
    uchar startalone_mask;    // 单机标志
    ushort handlemodel_sign;  // 处理模块标识
    ushort data_trans_rate;   // 数据传输速率
    uint frame_num;           // 发送的帧数
    uchar sign;               // 标志（仅对高算力平台有效）
    ushort start_code;        //卫星代码
    uchar bl;                 // 保留
};

// 测试数传停止
struct Test_num_stop {
    uchar ordermark;        // 指令标识
    uchar startalone_mask;  // 单机标志
};

// 开始软件上载
struct Begin_software_upload {
    uchar ordermark;  // 指令标识
    uchar reserve;
};

// 结束软件上载
struct End_software_upload {
    uchar ordermark;  // 指令标识
    uchar reserve;
};

// 传输软件
struct Transmission_software {
    uchar ordermark;  // 指令标识
    //...
};

// 更新软件
struct Renew_software {
    uchar ordermark;  // 指令标识
    //...
};

//综合管控单元6Gb三维运维0x43
struct str_43 {
    uchar ordermark;          // 指令标识
    uchar objmark;              // 对象标识
    uchar contorl;            //控制
    uint startADDr;          //起始地址
    uint sorft_size;         //大小


};

// 定时刷新功能设置0x44
struct Time_refresh_set {
    uchar ordermark;          // 指令标识
    uchar startalone_mask;    // 单机标志
    uchar chip_num;           // 芯片代号
    uchar enablemark;         // 使能标识
    ushort FPGA_refresh_gap;  // FPGA刷新间隔，以秒为单位
};

//开始软件包上载0x4B
struct str_4B {
    uchar ordermark;          // 指令标识
    uchar up_mark;            // 上载方式
    uchar up_size;            // 上载大小
    uchar duan_num;           // 段号
};

//更新软件0x47
struct str_47 {
    uchar ordermark;          // 指令标识
    uchar pc_mark;            //单机标志
    ushort sorft_num;          //软件代号
    ushort sorft_size;         //软件大小
    uchar flash_num;          //FLASH编号
    uchar to_duan;            //数据源
    uint flash_s_addr;       //FLASH起始地址
    uchar sl_choose;          //算力通道选择
    //  uchar up_choose;          //上注通道选择

};

//更新配置0x4A
struct str_4A {
    uchar ordermark;          // 指令标识
    uchar pc_mark;            //单机标志
    ushort set_num;            //配置代号
    uint addr_str;             //起始地址
    uint set_size;             //配置大小

};


// 任务执行设置
struct Task_execute_set {
    uchar ordermark;        // 指令标识
    uchar task_type;        // 任务类型
    ushort time_len;        // 时间长度

    ushort task_number;     // 任务流水号
    uchar Mode_Fun_cnt;     //功能模式段数

    uint mode1_starts;      //功能模式1开始时间
    uint mode1_ends;        //功能模式1结束时间
    uchar mode1_choose;     //功能模式1
    uint mode2_starts;      //功能模式2开始时间
    uint mode2_ends;        //功能模式2结束时间
    uchar mode2_choose;     //功能模式2

   uchar bl[27];   //保留


};

// 功能模式设置
struct Function_model_set {
    uchar ordermark;      // 指令标识
    uchar task_choose;    // 数传通道
    uint memory_1;        // 内存起始地址
    uint memory_2;        // 内存结束地址
};


// Flash下传0x3B
struct Flash_down {
    uchar ordermark;         // 指令标识
    uchar type_num;           // 类型号
    uchar pc_number;          // 单机标志
    uchar flash_ch;          // Flash选择
    uint start_addr;          // 起始地址
    ushort sorft_size;        // 软件大小
    uchar data_ch;          // 数传通道
};

// 管控机SSD目录查询0x3C
struct Controlmachine_category_check {
    uchar ordermark;  // 指令标识
    uchar reserve;
};

// 管控机SSD目录删除0x3D
struct Controlmachine_category_delete {
    uchar ordermark;          // 指令标识
    uchar bl;                 // 保留
    char category_name[128];  // 目录名
};



/*************************************************
 <类   名>    1553总线注数类CAN L频段数字综合单元
 <概要说明>    无
 <详细说明>    无

 <作    者>   ybl
 <时    间>   2023-08-31
 <修    改>
**************************************************/
// 矢量字查询
struct Vector_word_check {
    uchar ordermark;  // 指令标识
};

// 总线复位
struct Total_line_reset {
    uchar ordermark;  // 指令标识
};

// 数据注入
struct Data_inject {
    uchar ordermark;  // 指令标识
    uint data;        // 数据,256字节
};

// 间接指令
struct Indirect_order {
    uchar ordermark;  // 指令标识
    ushort parament;  // 参数
};

// 恢复重要数据
struct Restore_importdata {
    uchar ordermark;  // 指令标识
    uchar* data;      // 数据，28字节
};

// 重要数据采集
struct ImportData_collect {
    uchar ordermark;  // 指令标识
};

// 任务交互数据采集
struct Task_interactive_datacollect {
    uchar ordermark;  // 指令标识
};

// 遥测轮询
struct L_Remote_test {
    uchar ordermark;  // 指令标识
};

// 打包遥测
struct Packing_remote_test {
    uchar ordermark;  // 指令标识
};

// 内存下陷
struct Memory_full {
    uchar ordermark;  // 指令标识
};

// 工作状态报告
struct Work_status_report {
    uchar ordermark;  // 指令标识
};

// 开始内存下卸模式
struct Begin_memory_downmode {
    uchar ordermark;        // 指令标识
    ushort begin_add_high;  // 起始地址高端
    ushort begin_add_low;   // 起始地址低端
    ushort length;          // 长度
};

// 停止内存下卸模式
struct End_meomry_downmode {
    uchar ordermark;  // 指令标识
};

// 计划任务成像参数表数据定义
struct Plan_task_image {
    ushort PRF;                      // PRF分频码，PRF = 25MHz/分频码
    ushort echo_sampling_begincode;  // 回波采样起始码，采样起始时刻 = 采样起始码
    // * 40
    uint PRF_pulsenum;                 // PRF脉冲个数
    ushort pulse_width;                // 调频源时延调整码及脉冲宽度
    uchar control_parament;            // 调频源及接收机控制参数
    uchar formwork_mode;               // 数据形成工作模式
    uchar formsample_control;          // 数据形成采样控制码；
    uchar MGC;                         // 接收通道MGC
    uchar frame_len;                   // 帧长度
    uchar delayed_pulse_num;           // 发射接收延时脉冲数
    uchar calibrate_mode;              // 定标模式
    uchar reserve1;                    // 保留
    uchar adjust_coefficient_A1;       // 调整系数A1
    uchar adjust_coefficient_A2;       // 调整系数A2
    uchar realtime_image_1;            // 实时成像参数1
    uchar realtime_image_2;            // 实时成像参数2
    uchar reserve2;                    // 保留
    uchar position_emitwave;           // 方位向发射波位号
    ushort distance_emitwave;          // 距离向发射波位号
    ushort distance_scan_angle;        // 距离向扫描角
    ushort position_scan_begin_angle;  // 方位向扫描起始角
};

// 程控任务成像参数表数据定义
struct Programmed_task_image {
    uchar calibrate_mode;          // 定标模式
    uchar image_type;              // 成像方式
    uchar position_width;          // 方位幅宽
    uchar reserve;                 // 保留
    ushort position_resolution;    // 方位分辨率
    ushort programmed_image_time;  // 程控成像时长
    ushort target_scatter;         // 目标散射系数
    ushort belowstar_altitude;     // 星下点海报相对高度
    ushort position_squint_angle;  // 方位斜视角
    uchar realtime_image_1;        // 实时成像参数1
    uchar realtime_image_2;        // 实时成像参数2
};

// 成像结构块定义
struct Image_block {
    ushort target_num;      // 目标编号
    uchar* absolute_time;   // 本次成像开始绝对时间, 6字节
    uchar* post_data;       // 本次成像目标位置数据, 10字节
    ushort paramark_Burst;  // 本次成像换参数标志及Burst循环次数

    // 本次成像参数（分计划任务和程控任务成像参数表）
    Plan_task_image pti;

    ushort center_time;  // 本次成像聚束相对中心时刻
    uchar work_mode;     // 本次成像工作模式
    uchar calculate_subnum;  // 本次成像聚束中心时刻星上计算控制码及子带个数
};

// SAR成像工作参数包数据定义
struct SAR_imaging {
    ushort packmark;      // 包标识
    ushort sequencymark;  // 顺序标识
    ushort packlen;       // 包长
    ushort funrecog;      // 功能识别

    /*
   * D15-D12：本包有效目标个数（1-4）
   * D11-D08：本包有效参数个数（1-4）
   * D7-D4：本包序号（1-15）
   * D3-D0：总包个数（1-15）
   */
    ushort content_control;  // 内容控制字

    /*
   * D15 包格式：0->其他成像模式；1->预定波位扫描模式（广域搜索）
   * D14-D13
   * 任务类型：0->程控任务(他星引导)；1->程控任务(地面上注)；2->计划任务(地面上注)
   * D12-D0：保留
   */
    ushort task_type;  // 任务类型

    /*
   * D31-D16 任务号
   * D15-D0 子任务号
   */
    uint task_message;  // 任务信息
    Image_block ib1;    // 成像结构块1，56字节
    Image_block ib2;    // 成像结构块2，56字节
    Image_block ib3;    // 成像结构块3，56字节
    Image_block ib4;    // 成像结构块4，56字节

    /*
   * D7-D4：发射开关矩阵选择（0-15）
   * D3-D0：接收开关矩阵选择（0-15）
   */
    uchar switch_rect;  // 开关矩阵选择

    uchar reserve;    // 保留，13字节，填0
    ushort checksum;  // 校验和
};

/*************************************************
 <类   名>    1553总线注数类CAN 可重构射频前端
 <概要说明>    无
 <详细说明>    无

 <作    者>   ybl
 <时    间>   2023-08-31
 <修    改>
**************************************************/
// 可重构射频前端通道、本振加电控制0x58
struct Channel_local_powercontrol {

    uchar ordermark;                 // 指令标识0x58
    uchar L_cSwitch;                 // L频段开关
    uchar SXKu_12receive_switch;     // SXKu频段1、2接收通道开关
    uchar SXKu_34receive_switch;     // SXKu频段3、4接收通道开关
    uchar SXKu_56receive_switch;     // SXKu频段5、6接收通道开关
    uchar SXKu_12emit_switch;        // SXKu频段1、2发射通道开关
    uchar SXKu_34emit_switch;        // SXKu频段3、4发射通道开关
    uchar SXKu_56emit_switch;        // SXKu频段5、6发射通道开关
    uchar broadband_onebook_switch;  // 宽带一本振开关
    uchar highnoise_switch;          // 高相噪本振开关
    uchar twoBooks_switch;           // 二本振开关

    uchar bl;
};

// 可重构射频前端通道、本振加电控制 c72
struct Channel_local_powercontrolC72 {

    ushort order_len;       // 指令长度

    uchar ordermark;                 // 指令标识0x72
    uchar L_cSwitch;                 // L频段开关
    uchar SXKu_12receive_switch;     // SXKu频段1、2接收通道开关
    uchar SXKu_34receive_switch;     // SXKu频段3、4接收通道开关
    uchar SXKu_56receive_switch;     // SXKu频段5、6接收通道开关
    uchar SXKu_12emit_switch;        // SXKu频段1、2发射通道开关
    uchar SXKu_34emit_switch;        // SXKu频段3、4发射通道开关
    uchar SXKu_56emit_switch;        // SXKu频段5、6发射通道开关
    uchar broadband_onebook_switch;  // 宽带一本振开关
    uchar highnoise_switch;          // 高相噪本振开关
    uchar twoBooks_switch;           // 二本振开关
    ushort crc;             // 校验和
};

// 可重构射频前端通道、本振加电控制 c73
struct str_C73 {

    ushort order_len;       // 指令长度

    uchar ordermark;        // 指令标识0x73
    uchar zp_qh;                //中频切换
    ushort crc;             // 校验和
};

// 可重构射频前端中频切换模块设置0x59
struct Mid_switch {

    uchar ordermark;            // 指令标识0x59
    uchar zp_qh;                //中频切换

};


// 可重构射频前端通道、本振控制选择0x5A
struct Channel_local_controlchoose {

    uchar ordermark;            // 指令标识
    uchar L_channel1;           // L频段通道1
    uchar L_channel2;           // L频段通道2
    uchar L_channel3;           // L频段通道3
    uchar L_channel4;           // L频段通道4
    uchar L_channel5;           // L频段通道5
    uchar L_channel6;           // L频段通道6

    uchar SXKu_channel_12;      // SXKu频段通道1和2
    uchar SXKu_channel_34;      // SXKu频段通道3和4
    uchar SXKu_channel_56;      // SXKu频段通道5和6
    uchar broadband_onebook_1;  // 宽带一本振1频率
    uchar broadband_onebook_2;  // 宽带一本振2频率
    uchar highnoise;            // 高相噪本振频率
    uchar bl;                   // 保留
};

// 可重构射频前端通道、本振控制选择0xc74
struct Channel_local_controlchooseC74 {

    ushort order_len;           // 指令长度
    uchar ordermark;            // 指令标识
    uchar L_channel1;           // L频段通道1
    uchar L_channel2;           // L频段通道2
    uchar L_channel3;           // L频段通道3
    uchar L_channel4;           // L频段通道4
    uchar L_channel5;           // L频段通道5
    uchar L_channel6;           // L频段通道6

    uchar SXKu_channel_12;      // SXKu频段通道1和2
    uchar SXKu_channel_34;      // SXKu频段通道3和4
    uchar SXKu_channel_56;      // SXKu频段通道5和6
    uchar broadband_onebook_1;  // 宽带一本振1频率
    uchar broadband_onebook_2;  // 宽带一本振2频率
    uchar highnoise;            // 高相噪本振频率
    ushort crc;                 // 校验和
};
// 射频收发开关控制C50
struct Str_spsf {
    // ushort order_len;
    uchar order_mark;  // 指令标识
    uchar switch_cotrl;
    // ushort crc_sum;
};

// RS422线路控制选择指令C51
struct Str_RS422oeder {
    // ushort order_len;
    uchar order_mark;  // 指令标识
    uchar cotrl;       // 控制权
    // ushort crc_sum;
};

// FLASH编码读C52
struct Str_flashRead {
    // ushort order_len;
    uchar order_mark;
    uchar flashaddr[3];  // flash起始地址
    // ushort crc_sum;
};

// SXKu频段FLASH编码写c53
struct Str_flashWrite {
    uchar ordermark;  // 指令标识
    // uchar datalen;       // 有效数据长度
    uchar flashaddr[3];  // flash起始地址
    uchar bl[2];         // 保留
    uchar flashin[240];  // flash内容（低前高后）
};



// L频段天线子阵TR开关选择
struct L_TRswitch {
    uchar ordermark;  // 指令标识
    uchar TRswitch;   // 子阵开关
};

// 内存下卸 0x61
struct SAR_shutdown {
    uchar ordermark;  // 指令标识
    uchar type;       // 启停标识
    uint s_addr;       // 起始地址
    ushort len;       // 长度
};


// 清空雷达指令包
struct Radar_clear {
    uchar ordermark;  // 指令标识
    uchar bl;         // 保留
};

// 删除单个雷达指令包
struct Radar_delsingal {
    uchar ordermark;  // 指令标识
    uchar bl;         // 保留
    ushort number;    // SAR工作参数包号
};

// 重要数据采集 0x65
struct Radar_modify {
    uchar ordermark;  // 指令标识
    uchar bl;         // 保留
};

// 重要数据恢复 0x66
struct Radar_backup {
    uchar ordermark;  // 指令标识
    uchar bl;         // 保留
};

// 清空所有上注的补丁包
struct servicePack_Clear {
    uchar ordermark;  // 指令标识
    uchar bl;         // 保留
};

// L频段阵面与通道对应关系
struct L_matchup {
    uchar ordermark;  // 指令标识
    uchar select;     // 对应关系选择
};

// 导航闭锁开关
struct Navi_lock {
    uchar ordermark;  // 指令标识
    uchar switchset;  // 开关设置
};


// 温度关断保护使能
struct T_protect {
    uchar ordermark;  // 指令标识
    uchar T_switch;   // 使能开关
};

// L频段数字综合单元CPU软件补丁注入0x6A
struct L_CPU6A {
    uchar ordermark;  // 指令标识
    uchar datas[256];   // 数据
};


// L频段数字综合单元CPU波控码0x6B
struct L_CPU6B {
    uchar ordermark;  // 指令标识
    uchar datas[256];   // 数据
};

// 设备主备启动设置0x72
struct str_0x72 {
    uchar orderID;      //指令ID
    uchar devchoose;    //设备选择
    uchar kcgspqd;      //可重构射频前端主备
    uchar L_data;       //L频段数字主控机主备
    uchar L_time;       //L频段定时波控机主备
    uchar sxku_bs;      //SXKu波束控制机主备

    uchar devchoose2;   //设备选择2
    uchar zb_ebz;       //可重构射频前端二本振主备
    uchar zb_gxz;       //可重构射频前端高相噪主备


};



// 通信工作模式切换
struct work_mode_switch {
    uchar ordermark;        // 指令标识
    uchar platform_choose;  // 平台选择
    uchar beam_number;      // 波束号
    uchar work_mode;        // 工作模式
    uint user_identity;     // 用户身份标识
};

// 高速数传
struct highspeed_datatrans {
    uchar ordermark;            // 指令标识
    uchar platform_choose;      // 平台选择
    uchar main_beam_num;        // 主波束号
    uchar retransmission_mark;  // 重传标识
};

// 数传开始
struct Data_translate_begin {
    uchar ordermark;        // 指令标识
    uchar platform_choose;  // 平台选择
};

// 数传结束
struct Data_translate_end {
    uchar ordermark;        // 指令标识
    uchar platform_choose;  // 平台选择
};

// 波位参数包
struct Beam_position {
    uchar reserve;                       // 保留填0
    uchar position_emit_num;             // 方位向发射波位号
    ushort distance_emit_num;            // 距离向发射波位号
    ushort distance_beam_angle;          // 距离向波束指向角
    ushort position_emit_beam_angle;     // 方位向发射波束起始角
    ushort position_receive_beam_angle;  // 方位向接收波束起始角
};

struct L_unit_beamcontrol {
    ushort frame_head;       // 帧头
    ushort data_len;         // 数据长度
    uchar ordermark;         // 指令标识
    uchar base_emit;         // 基态发射相位补偿码
    uchar base_receive;      // 基态接收相位补偿码
    uchar base_receamp;      // 基态接收幅度相位补偿码
    uchar reserve1;          // 保留
    uchar position_emit;     // 方位发射相位补偿码
    uchar position_receive;  // 方位接收相位补偿码

    uchar hour_emit;     // 小时延时发射相位补偿码
    uchar hour_receive;  // 小时延时接收相位补偿码
    uchar hour_receamp;  // 小时延时接收幅度相位补偿码

    uchar big_emit;     // 大位延时发射相位补偿码
    uchar big_receive;  // 大位延时接收相位补偿码
    uchar big_receamp;  // 大位延时接收幅度相位补偿码

    uchar reserve2;  // 保留
    uchar reserve3;  // 保留

    uchar receive_fade;        // 接收衰竭
    uchar switch_rect_choose;  // 开关矩阵选择
    uchar work_style;          // 工作模式

    uchar reserve4;                  // 保留，固定填0
    Beam_position beam_position[4];  // 波位参数
    ushort crc;                      // 校验和
    ushort frame_tail;               // 帧尾
};

/*************************************************
 <类   名>    1553 spi协议指令 SXKu频段波束控制单元
 <概要说明>    无
 <详细说明>    无

 <作    者>   ybl
 <时    间>   2023-10-09
 <修    改>
**************************************************/
// 波束指向参数定义
struct Beam_zx {
    uchar emit_beam_frequency;     // 发射波束频率
    uchar receive_beam_frequency;  // 接收波束频率
    ushort Theta_emit_beam;        // Theta发射波束指向角
    ushort Theta_receive_beam;     // Theta接收波束指向角
    ushort Phi_emit_beam;          // Phi发射波束指向角
    ushort Phi_receive_beam;       // Phi接收波束指向角
};

struct SXKu_beam_control {
    ushort frame_head;               // 帧头
    ushort data_len;                 // 数据长度
    uchar ordermark;                 // 指令标识
    uchar work_style;                // 工作模式
    uchar polari_calculate_mode;     // 极化及计算模式
    uchar compensate;                // 补偿组别
    uchar power_load_rect;           // 功率及负载态矩阵
    uchar assembly_remote_high4;     // 组件遥测数据类型（高4位）
    uchar assembly_remotedata_low8;  // 组件遥测数据类型（低8位）
    uchar receive_fade;              // 接收衰减控制
    uchar reserve1;                  // 备用
    uchar reserve2;                  // 备用
    uchar X_emit;                    // X向发射相位加权码
    uchar X_receive;                 // X向接收相位加权码
    uchar Y_emit;                    // Y向发射相位加权码
    uchar Y_receive;                 // Y向接收相位加权码
    uchar appoint_move;              // 指定移向值（D5-D0,固定填0）
    uchar appoint_fade;              // 指定衰减值（D5-D0,固定填0）
    uchar appoint_delayed;           // 指定延时值（D5-D0,固定填0）
    Beam_zx bszx[4];
    uchar reserve3;     // 备用，填0
    ushort crc;         // 校验和
    ushort frame_tail;  // 帧尾
};

/*************************************************
 <类   名>    1553 spi协议指令 可重构射频前端
 <概要说明>    无
 <详细说明>    无

 <作    者>   ybl
 <时    间>   2023-10-09
 <修    改>
**************************************************/
// 可重构射频前端 L频段发射通道设置
struct recoemit_L_emit {
    ushort frame_head;     // 帧头
    ushort data_len;       // 数据长度
    uchar ordermark;       // 指令标识
    uchar channel_choose;  // 通道选择
    uchar emit_fade;       // 发射衰减
    uchar reserve[9];      // 保留填0
    ushort crc;
    ushort frame_tail;  // 帧尾
};

// SXKu频段接收通道设置
struct recoemit_sxku_receive {
    ushort frame_head;      // 帧头
    ushort data_len;        // 数据长度
    uchar ordermark;        // 指令标识
    uchar channel_choose;   // 通道选择
    uchar sxku_first;       // SXKu频段第一级放大器使能
    uchar sxku_emit_fade;   // SXKu频段射频衰减
    uchar receive_fade;     // 接收衰减
    uchar broad_onebook_1;  // 宽带一本振1频率
    uchar broad_onebool_2;  // 宽带一本振2频率
    uchar high_frequency;   // 高相噪本振频率
    ushort reserve;         // 保留填0
    ushort crc;
    ushort frame_tail;  // 帧尾
};

// SXKu频段发射通道设置
struct recoemit_sxku_emit {
    ushort frame_head;      // 帧头
    ushort data_len;        // 数据长度
    uchar ordermark;        // 指令标识
    uchar channel_choose;   // 通道选择
    uchar emit_fade;        // 发射衰减
    uchar broad_onebook_1;  // 宽带一本振1频率
    uchar broad_onebool_2;  // 宽带一本振2频率
    uchar high_frequency;   // 高相噪本振频率
    ushort reserve;         // 保留填0
    ushort crc;
    ushort frame_tail;  // 帧尾
};

// 射频校正开关状态设置
struct Frequencyband_check_switch {
    ushort frame_head;           // 帧头
    ushort data_len;             // 数据长度
    uchar ordermark;             // 指令标识
    uchar frequencyband_choose;  // 频段选择
    uchar check_work;            // 校正方式
    ushort reserve;              // 保留填0
    ushort crc;
    ushort frame_tail;  // 帧尾
};

// SXKu频段一本振选择设置
struct SXKu_Frequencyband_onebook {
    ushort frame_head;      // 帧头
    ushort data_len;        // 数据长度
    uchar ordermark;        // 指令标识
    uchar channel_choose;   // 通道选择
    uchar onebook_useinfo;  // 一本振使用信息
    ushort reserve;         // 保留填0
    ushort crc;
    ushort frame_tail;  // 帧尾
};

// L频段接收通道设置
struct L_frequencyband_receive {
    ushort frame_head;     // 帧头
    ushort data_len;       // 数据长度
    uchar ordermark;       // 指令标识
    uchar channel_choose;  // 通道选择
    uchar L_GSM_enable;    // L频段GSM陷波器使能
    uchar L_first;         // L频段第一级放大器使能
    uchar L_second;
    uchar L_third;
    uchar receive_fade;  // 接收衰减
    ushort reserve;      // 保留填0
    ushort crc;
    ushort frame_tail;  // 帧尾
};


//星时和能源状态广播
struct Star_Power_broad {
    ushort checktime_mode;          // 校正方式,0x5555H；GNSS校时,0xAAAAH；地面校时
    ushort time_code[3];           // 时间码 0.1ms计数
    ushort status;                // 卫星能源状态;0x1111:能源良好，0x2222:能源一级，0x3333:能源二级
};

//GNSS时间码
struct GNSS_Time {
    ushort code1;          // 数据有效标记高字节，数据有效标志低字节
    ushort code2;          // 北京时间累计秒最高字节，次高字节
    ushort code3;         // 北京时间累计秒次低字节，最低字节
};

/*************************************************
 <类   名>    GNSS定位数据
 <概要说明>    无
 <详细说明>    无

 <作    者>   ybl
 <时    间>   2023-10-13
 <修    改>
**************************************************/
struct GNSS_position_data {
    ushort page_reco;           // 包识别
    ushort page_order_control;  // 包顺序控制
    ushort page_len;            // 包长
    uchar position_sign;        // 定位标志
    uchar star_use;             // 可用星数
    uint time_second;           // 时间整秒
    uint X_position;            // X位置
    uint Y_position;            // Y位置
    uint Z_position;            // Z位置
    uint X_speed;               // X速度
    uint Y_speed;               // Y速度
    uint Z_speed;               // Z速度
    uchar orbit_sign;           // 定轨标志
    uchar reserve1[3];          // 保留

    uint X_position_2;  // X位置,15分钟后
    uint Y_position_2;  // Y位置,15分钟后
    uint Z_position_2;  // Z位置,15分钟后
    uint X_speed_2;     // X速度,15分钟后
    uint Y_speed_2;     // Y速度,15分钟后
    uint Z_speed_2;     // Z速度,15分钟后
};

/*************************************************
 <类   名>    GNSS定轨数据
 <概要说明>    无
 <详细说明>    无

 <作    者>   ybl
 <时    间>   2023-10-13
 <修    改>
**************************************************/
struct Orbit_Determination_data {
    ushort page_reco;           // 包识别
    ushort page_order_control;  // 包顺序控制
    ushort page_len;            // 包长
    uchar position_sign;        // 定位标志
    uchar star_use;             // 可用星数
    uint Bejing_time;           // 北京时间整秒
    uint orbit_half;            // 轨道半长轴
    uint orbit_eccentricity;    // 轨道偏心率
    uint orbit_angle;           // 轨道倾角
    uint node;                  // 升交点赤经
    uint perigee;               // 近地点角距
    uint flat_spot;             // 平近点角
    ushort out_put_time;        // 外推时间
    ushort reserve;             // 保留

    uint orbit_half_2;          // 轨道半长轴,15分钟后
    uint orbit_eccentricity_2;  // 轨道偏心率,15分钟后
    uint orbit_angle_2;         // 轨道倾角,15分钟后
    uint node_2;                // 升交点赤经,15分钟后
    uint perigee_2;             // 近地点角距,15分钟后
    uint flat_spot_2;           // 平近点角,15分钟后
};

// 轨道姿态广播数据CAN
struct Orbitalstance_Data_CAN {
    ushort pack_len;       // 指令长度0x0026
    uchar order_mark;      //指令标识0xF0

    uchar satsllite_mark;  // 卫星标志
    uchar bl[1];            //保留

    uchar thistime[6];     // 姿态计算时间
    int rolling_angle;       // 滚动角
    int pitch_angle;         // 俯仰角
    int yawing_angle;        // 偏航角
    int rolling_anglespeed;  // 滚动角速度
    int pitch_anglespeed;    // 俯仰角速度
    int yawing_anglespeed;   // 偏航角速度

    uchar bl2[1];            //保留
    ushort crc_add;       // 校验和
};

// 轨道姿态广播数据
struct Orbitalstance_Data {
    ushort pack_mark;      // 包识别0x1230
    ushort pack_sequence;  // 包顺序0xC000-0xFFFF
    ushort pack_len;       // 包长0x00B9

    ushort fun_mark;        //功能标志（5.11新增）0xBBBB
    uchar satsllite_mark;  // 卫星标志0x01:软件星1，0x02:软件星2,0x03:软件星3,0x04:软件星4
    uchar softstart_I;     // 软件星I轨道有效标志 0:有效，1：无效
    uchar softstart_II;    // 软件星II轨道有效标志0:有效，1：无效
    uchar softstart_III;   // 软件星III轨道有效标志0:有效，1：无效
    uchar softstart_IV;    // 软件星IV轨道有效标志0:有效，1：无效

    uchar thistime[6];     // 本星计算姿态时间
    int rolling_angle;       // 滚动角 0.0001度
    int pitch_angle;         // 俯仰角
    int yawing_angle;        // 偏航角
    int rolling_anglespeed;  // 滚动角速度 0.0001度/s
    int pitch_anglespeed;    // 俯仰角速度
    int yawing_anglespeed;   // 偏航角速度
    int sun_x;               // 太阳矢量Sx_o
    int sun_y;               // 太阳矢量Sy_o
    int sun_z;               // 太阳矢量Sz_o

    uchar sorfttime_I[6];  // 软件星I计算轨道时间  UTC时间
    int sorft_Iside_x;     // 软件星I姿轨控计算位置x 0.1m
    int sorft_Iside_y;     // 软件星I姿轨控计算位置y
    int sorft_Iside_z;     // 软件星I姿轨控计算位置z
    int sorft_Ispeed_x;    // 软件星I姿轨控计算速度x 0.01cm/s
    int sorft_Ispeed_y;    // 软件星I姿轨控计算速度y
    int sorft_Ispeed_z;    // 软件星I姿轨控计算速度z

    uchar sorfttime_II[6];  // 软件星II计算轨道时间
    int sorft_IIside_x;     // 软件星II姿轨控计算位置x
    int sorft_IIside_y;     // 软件星II姿轨控计算位置y
    int sorft_IIside_z;     // 软件星II姿轨控计算位置z
    int sorft_IIspeed_x;    // 软件星II姿轨控计算速度x
    int sorft_IIspeed_y;    // 软件星II姿轨控计算速度y
    int sorft_IIspeed_z;    // 软件星II姿轨控计算速度z

    uchar sorfttime_III[6];  // 软件星III计算轨道时间
    int sorft_IIIside_x;     // 软件星III姿轨控计算位置x
    int sorft_IIIside_y;     // 软件星III姿轨控计算位置y
    int sorft_IIIside_z;     // 软件星III姿轨控计算位置z
    int sorft_IIIspeed_x;    // 软件星III姿轨控计算速度x
    int sorft_IIIspeed_y;    // 软件星III姿轨控计算速度y
    int sorft_IIIspeed_z;    // 软件星III姿轨控计算速度z

    uchar sorfttime_IV[6];  // 软件星IV计算轨道时间
    int sorft_IVside_x;     // 软件星IV姿轨控计算位置x
    int sorft_IVside_y;     // 软件星IV姿轨控计算位置y
    int sorft_IVside_z;     // 软件星IV姿轨控计算位置z
    int sorft_IVspeed_x;    // 软件星IV姿轨控计算速度x
    int sorft_IVspeed_y;    // 软件星IV姿轨控计算速度y
    int sorft_IVspeed_z;    // 软件星IV姿轨控计算速度z

    uchar by[15];  // 备用
    ushort add_crc; //和校验
};

// 轨道姿态广播数据xlsx
struct Orbitalstance_Data_xlsx {
    uint thistime;
    int rolling_angle[4];  // 滚动角,1553用4个，can默认第一个
    int pitch_angle[4];    // 俯仰角
    int yawing_angle[4];   // 偏航角
};

// GNSS定位数据CAN
struct GNSS_Positioning_CAN{
    ushort order_len;       // 指令长度
    uchar order_mark;       //指令标识
    ushort pack_mark;      // 包识别
    ushort pack_sequence;  // 包顺序控制
    ushort pack_len;       // 包长

    uchar posit_mark;    // 定位标志
    uchar use_startsum;  // 可用星数标志
    uint time_s;         // 时间整秒
    int position_x;      // x位置
    int position_y;      // y位置
    int position_z;      // z位置
    int speed_x;         // x速度
    int speed_y;         // y速度
    int speed_z;         // z速度

    uchar track_mark;  // 定轨标志
    uchar bl[3];       // 保留
    int position15_x;  // 预报15分钟后x位置
    int position15_y;  // 预报15分钟后y位置
    int position15_z;  // 预报15分钟后z位置
    int speed15_x;     // 预报15分钟后x速度
    int speed15_y;     // 预报15分钟后y速度
    int speed15_z;     // 预报15分钟后z速度
    uchar bl2[1];            //保留
    ushort crc_add;       // 校验和
};

// GNSS定位数据
struct GNSS_Positioning {
    ushort pack_mark;      // 包识别0x0672H
    ushort pack_sequence;  // 包顺序b0-b2:序列标志，b3-b15:包名称或序列
    ushort pack_len;       // 包长0x0039

    uchar posit_mark;    // 定位标志...
    uchar use_startsum;  // 可用星数标志b0-b3:GPS可可用星数，b4-b7:BDS可用星数
    uint time_s;         // 时间整秒
    int position_x;      // x位置单位0.01m
    int position_y;      // y位置
    int position_z;      // z位置
    int speed_x;         // x速度0.01cm/s
    int speed_y;         // y速度
    int speed_z;         // z速度

    uchar track_mark;  // 定轨标志...
    uchar bl[3];       // 保留
    int position15_x;  // 预报15分钟后x位置
    int position15_y;  // 预报15分钟后y位置
    int position15_z;  // 预报15分钟后z位置
    int speed15_x;     // 预报15分钟后x速度
    int speed15_y;     // 预报15分钟后y速度
    int speed15_z;     // 预报15分钟后z速度
};

// GNSS定位数据表格容器
struct GNSS_Positioning_xlsx {
    uint time_s;     // 时间整秒

    int position_x[4];  // x位置 ,1553用4个，can默认第一个
    int position_y[4];  // y位置
    int position_z[4];  // z位置
    int speed_x[4];     // x速度
    int speed_y[4];     // y速度
    int speed_z[4];     // z速度
};

// GNSS定轨数据表格容器
struct GNSS_Orbit_xlsx {
    uint time_s;           // 时间整秒

    uint track_halflenth[4];  // 轨道半长轴（km）,1553用4个，can默认第一个
    uint track_offcenter[4];  // 轨道偏心率
    uint track_angle[4];      // 轨道倾角
    uint up_point[4];         // 升交点赤经
    uint near_angle[4];       // 近地点角距
    uint flat_angle[4];       // 平近点角距
};

// GNSS定轨数据CAN
struct GNSS_Track_CAN {
    ushort order_len;       // 指令长度
    uchar order_mark;       //指令标识
    ushort pack_mark;      // 包识别
    ushort pack_sequence;  // 包顺序控制
    ushort pack_len;       // 包长

    uchar track_mark;      // 定轨标志
    uchar use_startsum;    // 可用星数
    uint time_s;           // 时间整秒
    uint track_halflenth;  // 轨道半长轴（km）
    uint track_offcenter;  // 轨道偏心率
    uint track_angle;      // 轨道倾角
    uint up_point;         // 升交点赤经
    uint near_angle;       // 近地点角距
    uint flat_angle;       // 平近点角距
    ushort outpush_time;   // 外推时间
    uchar bl[2];           // 保留

    uint track_15halflenth;  // 15分钟后轨道半长轴
    uint track_15offcenter;  // 15分钟后轨道偏心率
    uint track_15angle;      // 15分钟后轨道倾角
    uint up_15point;         // 15分钟后升交点赤经
    uint near_15angle;       // 15分钟后近地点角距
    uint flat_15angle;       // 15分钟后平近点角距
    uchar bl2[1];            //保留
    ushort crc_add;       // 校验和

};
// GNSS定轨数据
struct GNSS_Track {
    ushort pack_mark;      // 包识别0x0673
    ushort pack_sequence;  // 包顺序bit0-bit2:序列标志，b3-b15包名称或序列
    ushort pack_len;       // 包长0x0039

    uchar track_mark;      // 定轨标志...
    uchar use_startsum;    // 可用星数bit0-bit3:GPS可用星数,bit4-bit7:BDS可用星数
    uint time_s;           // 时间整秒
    uint track_halflenth;  // 轨道半长轴单位0.1米（无效填AA）
    uint track_offcenter;  // 轨道偏心率
    uint track_angle;      // 轨道倾角
    uint up_point;         // 升交点赤经
    uint near_angle;       // 近地点角距
    uint flat_angle;       // 平近点角距
    ushort outpush_time;   // 外推时间b0:外推分，b1：外推秒
    uchar bl[2];           // 保留

    uint track_15halflenth;  // 15分钟后轨道半长轴（无效填AA）
    uint track_15offcenter;  // 15分钟后轨道偏心率
    uint track_15angle;      // 15分钟后轨道倾角
    uint up_15point;         // 15分钟后升交点赤经
    uint near_15angle;       // 15分钟后近地点角距
    uint flat_15angle;       // 15分钟后平近点角距
};

// 透传指令,开始软件上注C82
struct Str_startUp {
    ushort slen;           // 指令长度
    uchar zlmark;          // 指令标志
    uchar uomand;          // 上注方式
    uchar flash_mark;      // FLASH编号
    ushort sorftnumber;    // 软件代号
    ushort sorftsize;      // 软件大小
    uint flash_startaddr;  // FLASH起始地址
    uchar bl[1];
    ushort crc;  // 校验和crc
};

// 透传指令,FLASH 擦除C83
struct flashcc {
    ushort zlcd;   // 指令长度
    uchar zlbs;    // 指令标识
    ushort qskdz;  // 起始块地址
    uchar bl[1];   // 保留
    ushort jyh;    // 校验和
};

// 透传指令,FLASH 擦除状态查询C84
struct flashccztcx {
    ushort zlcd;  // 指令长度
    uchar zlbs;   // 指令标识
    uchar bl[1];  // 保留
    ushort jyh;   // 校验和
};

// 软件上注C85（多条后期，暂时）
struct Str_sorftupC85 {
    ushort order_len;   // 指令长度
    uchar order_mark;   // 指令标识
    uint page_addr;     // 页地址
    uchar number;       // 序号
    uchar datas[1024];  // （读取文件，多条）
    ushort crc;         // 校验和
};

// 软件上注完成C86
struct Str_sorftfinash {
    ushort order_len;  // 指令长度
    uchar order_mark;  // 指令标识
    ushort pack_num;   // 包数
    uchar bl[1];       // 保留
    ushort crc;        // 校验和
};

// 软件写入状态查询C87
struct Str_sorftWriteC87 {
    ushort order_len;  // 指令长度
    uchar order_mark;  // 指令标识
    uchar bl[1];       // 保留
    ushort crc;        // 校验和
};
// 接口控制板FPGAV7维护c88
struct FPGAV7whC88 {
    ushort order_len;  // 指令长度
    uchar order_mark;  // 指令标识
    uchar bl[1];       // 保留
    ushort crc;        // 校验和
};

//CAN解析及重构调度软件切换到更新区C89
struct Str_C89 {
    ushort order_len;  // 指令长度
    uchar order_mark;  // 指令标识
    uchar bl[1];       // 保留
    ushort crc;        // 校验和
};


// DSP6678加载测试A0
struct Str_A0 {
    ushort order_len;  // 指令长度
    uchar order_mark;  // 指令标识
    ushort crc;        // 校验和
};

// 透传指令,软件重构C8A
struct rjcg {
    ushort zlcd;   // 指令长度
    uchar zlbs;    // 指令标识
    ushort xpdh1;  // 芯片代号1
    ushort rjdh1;  // 软件代号1
    uchar czfs1;   // 操作方式1
    ushort xpdh2;  // 芯片代号2
    ushort rjdh2;  // 软件代号2
    uchar czfs2;   // 操作方式2；
    ushort xpdh3;  // 芯片代号3
    ushort rjdh3;  // 软件代号3
    uchar czfs3;   // 操作方式3
    ushort xpdh4;  // 芯片代号4
    ushort rjdh4;  // 软件代号4
    uchar czfs4;   // 操作方式4
    ushort xpdh5;  // 芯片代号5
    ushort rjdh5;  // 软件代号5
    uchar czfs5;   // 操作方式5
    ushort xpdh6;  // 芯片代号6
    ushort rjdh6;  // 软件代号6
    uchar czfs6;   // 操作方式6
    ushort xpdh7;  // 芯片代号7
    ushort rjdh7;  // 软件代号7
    uchar czfs7;   // 操作方式7
    ushort xpdh8;  // 芯片代号8
    ushort rjdh8;  // 软件代号8
    uchar czfs8;   // 操作方式8
    uchar bl;      // 保留
    ushort jyh;    // 校验和
};

// 软件下传C8B
struct Str_sorftDownC8B {
    ushort order_len;       // 指令长度
    uchar order_mark;       // 指令标识
    uchar flash_num;        // Flash编号
    uint flash_addr;        // Flashd地址
    ushort Sorftware_size;  // 软件大小
    uchar data_Ad;        // 数传通道
    uchar bl;             // 保留
    ushort crc;             // 校验和
};

//9.4.13 系统参数初始化C8C
struct Str_sysC8C {
    ushort order_len;       // 指令长度
    uchar order_mark;       // 指令标识

    ushort s_mark;         // 卫星标志
    uchar main_sub;        // 管控单元主备标识  D1：表示当前运行的交换机是主还是备  D0：表示当前运行的管控机是主还是备


    ushort crc;             // 校验和
};


//9.4.14 模块上下电C8D
struct Str_powC8D {
    ushort order_len;       // 指令长度
    uchar order_mark;       // 指令标识

    uchar AD_DA1;//AD/DA1
    uchar AD_DA2;//AD/DA2
    uchar AD_DA3;//AD/DA3

    ushort crc;             // 校验和
};

//9.4.15 NAND FALSH清除C8E
struct Str_C8E {
    ushort order_len;       // 指令长度
    uchar order_mark;       // 指令标识
    uchar flash_mark;      //FLASH标识
    ushort ccMark;          //擦除标识

    ushort crc;             // 校验和
};
//9.4.16 重构状态查询C8F
struct Str_C8F {
    ushort order_len;       // 指令长度
    uchar order_mark;       // 指令标识
    uchar bl;//保留

    ushort crc;             // 校验和
};
//10.4.17 任务下发C90
struct Str_C90 {
    ushort order_len;       // 指令长度
    uchar order_mark;       // 指令标识
    uchar packSum;          //总包数
    uchar packNum;          //包序号
    uchar data[2041];       //任务内容N(变长)

    ushort crc;             // 校验和
};

//9.4.18 开始任务C91 9.4.19 停止任务C92
struct Str_c91_c92 {
    ushort order_len;       // 指令长度
    uchar order_mark;       // 指令标识
    uchar task[3];            //任务号

    ushort crc;             // 校验和
};


//9.4.20 干扰引导信息C93
struct Str_C93 {
    ushort order_len;       // 指令长度
    uchar order_mark;       // 指令标识

    uchar signal_kind;      //信号类型
    ushort mask_sum;        //目标数量

    //  //循环体////
    //  uint fre;             //频率
    //  int jd;               //经度
    //  int wd;               //纬度
    //  int gd;               //高度
    //  ushort mode_type;     //模式（指侦察到类型）
    //////

    //  uchar gr_choose;      //干扰策略选择
    //  uchar bl;             //保留
    //  ushort crc;           // 校验和
};

//9.4.20 干扰引导信息C93内循环体
struct Str_C93_cyc {
    //循环体////
    uint fre;             //频率
    int jd;               //经度
    int wd;               //纬度
    int gd;               //高度
    ushort mode_type;     //模式（指侦察到类型）
};

//9.4.20 干扰引导信息C93尾部
struct Str_C93_end {
    uchar bl[2];             //保留
    ushort crc;           // 校验和
};


//10.4.21 测试数传C94
struct Str_C94 {
    ushort order_len;       // 指令长度
    uchar order_mark;       // 指令标识
    ushort cl_mark;         //处理模块标识
    ushort speed;           //数据传输速率
    uint sendFrame;         //发送的帧数

    uchar datamark;         //输传标志
    ushort startCode;       //卫星代码
    ushort crc;             // 校验和
};


//10.4.22 测试数传停止C95
struct Str_C95 {
    ushort order_len;       // 指令长度
    uchar order_mark;       // 指令标识
    uchar bl;             //保留1
    ushort crc;             // 校验和
};

//10.4.23 射频前端自动增益开关C96
struct Str_C96 {
    ushort order_len;       // 指令长度
    uchar order_mark;       // 指令标识
    uchar switch_kg;       // 开关使能

    ushort crc;             // 校验和
};

//9.4.24 数传完成C97
struct Str_C97 {
    ushort order_len;       // 指令长度
    uchar order_mark;       // 指令标识
    uchar dataAD;           //数传通道	1
    uint memSaddr;           //内存开始地址	4
    uint memEaddr;           //内存结束地址	4

    ushort crc;             // 校验和
};

// 矢量字查询C01
struct VectorC01  {
    ushort order_len;       // 指令长度
    uchar order_mark;       // 指令标识
    ushort crc;             // 校验和
};

//总线复位C02
struct busrespC02  {
    ushort order_len;       // 指令长度
    uchar order_mark;       // 指令标识
    ushort crc;             // 校验和
};
//数据注入C03
struct DatainC03  {
    ushort order_len;       // 指令长度
    uchar order_mark;       // 指令标识

    uchar data[256];        //数据

    ushort crc;             // 校验和
};

//间接指令C04
struct Str_indirectC04 {
    ushort order_len;       // 指令长度
    uchar order_mark;       // 指令标识
    ushort pack_mark;        // 包标识
    ushort sequence_mark;    // 顺序标识
    ushort packLen;          // 包长
    ushort fun_mark;         // 功能标识
    ushort indirect_made;    // 间接指令码
    ushort add_crc;         // 和校验
    ushort crc;         // 校验和

};

//重要数据采集C06
struct importdataC06  {
    ushort order_len;       // 指令长度
    uchar order_mark;       // 指令标识
    ushort crc;             // 校验和
};

//任务交互数据采集C07
struct taskdataC07  {
    ushort order_len;       // 指令长度
    uchar order_mark;       // 指令标识
    ushort crc;             // 校验和
};

//遥测轮询C08
struct ycpolingC08  {
    ushort order_len;       // 指令长度
    uchar order_mark;       // 指令标识
    ushort crc;             // 校验和
};
// 打包遥测C09
struct packycC09  {
    ushort order_len;       // 指令长度
    uchar order_mark;       // 指令标识
    ushort crc;             // 校验和
};
// 打包遥测C0A
struct MemoryC0A  {
    ushort order_len;       // 指令长度
    uchar order_mark;       // 指令标识
    ushort crc;             // 校验和
};
//工作状态报告C0B
struct workststus  {
    ushort order_len;       // 指令长度
    uchar order_mark;       // 指令标识
    ushort crc;             // 校验和
};

//开始内存下卸模式C0C
struct startMemory  {
    ushort order_len;       // 指令长度
    uchar order_mark;       // 指令标识
    ushort addr1;           // 起始地址高端
    ushort addr2;           // 起始地址低端
    ushort len;             // 长度

    ushort crc;             // 校验和
};

//停止内存下卸模式C0D
struct stopMemory  {
    ushort order_len;       // 指令长度
    uchar order_mark;       // 指令标识
    ushort crc;             // 校验和
};


//9.2.1 遥测轮询C51
struct YccycleC51  {
    ushort order_len;       // 指令长度
    uchar order_mark;       // 指令标识
    ushort crc;             // 校验和
};
//阵面二次电源控制C52
struct second_power  {
    ushort order_len;       // 指令长度
    uchar order_mark;       // 指令标识

    uchar zz;               //子阵
    uchar recive_send;      //接收发射
    uchar switch_power;     //开关电

    ushort crc;             // 校验和
};

//9.2.2 射频收发电源控制（优先于阵面电源加电）C53
struct sppowerC53  {
    ushort order_len;       // 指令长度
    uchar order_mark;       // 指令标识

    uchar recive_send;      //接收发射
    uchar switch_power;     //开关电

    ushort crc;             // 校验和
};

//9.2.2 射频收发开关控制C54
struct spswitchC54  {
    ushort order_len;       // 指令长度
    uchar order_mark;       // 指令标识

    uchar switch_contrl;     //开关控制

    ushort crc;             // 校验和
};

//9.2.3 RS422线路控制选择指令C55
struct Rs422chooseC55  {
    ushort order_len;       // 指令长度
    uchar order_mark;       // 指令标识

    uchar contrlPower;     //控制权

    ushort crc;             // 校验和
};

//9.2.4 FLASH编码读C56
struct flashReadC56  {
    ushort order_len;       // 指令长度
    uchar order_mark;       // 指令标识

    uchar addr_1;           //FLASH起始地址(高字节）
    uchar addr_2;           //FLASH起始地址(中字节）
    uchar addr_3;           //FLASH起始地址(低字节）

    ushort crc;             // 校验和
};
//9.2.4 FLASH编码写C57
struct flashWriteC57  {
    ushort order_len;       // 指令长度
    uchar order_mark;       // 指令标识

    uchar addr_1;           //FLASH起始地址(高字节）
    uchar addr_2;           //FLASH起始地址(中字节）
    uchar addr_3;           //FLASH起始地址(低字节）
    uchar bl[2];            //保留
    uchar buff[240];        //FLASH内容

    ushort crc;             // 校验和
};


//9.2.6 FLASH擦除C5A
struct flashClearC5A  {
    ushort order_len;       // 指令长度
    uchar order_mark;       // 指令标识

    uchar addr_1;           //FLASH起始地址(高字节）
    uchar addr_2;           //FLASH起始地址(中字节）
    uchar addr_3;           //FLASH起始地址(低字节）

    ushort crc;             // 校验和
};

//9.2.7 工作时长设置C5B
struct worktimeC5B  {
    ushort order_len;       // 指令长度
    uchar order_mark;       // 指令标识

    ushort worktime;           //工作时长

    ushort crc;             // 校验和
};
//9.2.7 子阵选择控制C5C
struct zzC5C  {
    ushort order_len;       // 指令长度
    uchar order_mark;       // 指令标识

    uchar zzchoose;           //子阵选择

    ushort crc;             // 校验和
};
//天线工作模式设置指令C5D
struct txworkC5D  {
    ushort order_len;       // 指令长度
    uchar order_mark;       // 指令标识

    uchar txwork;           //天线工作模式

    ushort crc;             // 校验和
};
//9.2.10 阵面解锁指令C5E
struct zlunlockC5E  {
    ushort order_len;       // 指令长度
    uchar order_mark;       // 指令标识

    uchar unlock;           //解锁标识

    ushort crc;             // 校验和
};


//9.4.2 遥测轮询C81
struct yccyc_C81{
    ushort order_len;       // 指令长度
    uchar order_mark;       // 指令标识

    uchar bl;           // 保留

    ushort crc;             // 校验和
};

// 可重构射频前端L频段接收通道设置
struct Str_L_recvSet {
    ushort frame_head;    // 帧头
    ushort data_len;      // 数据长度
    uchar order_mark;     // 指令标识
    uchar ad_choose;      // 通道选择
    uchar L_GSmEnable;    // L频段GSM陷波器使能
    uchar L_oneEnable;    // L频段第一级放大器使能
    uchar L_twoEnable;    // L频段第二级放大器使能
    uchar L_threeEnable;  // L频段第三级放大器使能
    uchar recv_down;      // 接收衰减
    uchar bl[1];          // 保留
    ushort crc;           // 校验和
    ushort frame_end;     // 帧尾
};

// 可重构射频前端L频段发射通道设置
struct Str_L_SendSet {
    ushort frame_head;  // 帧头
    ushort data_len;    // 数据长度
    uchar order_mark;   // 指令标识
    uchar ad_choose;    // 通道选择
    uchar send_down;    // 发射衰减
    uchar bl[5];        // 保留
    ushort crc;         // 校验和
    ushort frame_end;   // 帧尾
};

// L频段数字综合单元波束控制指令
struct L_PDnumber {
    ushort frame_head;       // 帧头
    ushort data_len;         // 数据长度
    uchar order_mark;        // 指令标识
    uchar jt_sendBC;          // bit4-bit7基态接收相位补偿码
    // bit0-bit3基态发射相位补偿码

    uchar jt_rangerecv;      // bit4-bit7保留
    //bit0-bit3基态接收幅度补偿码

    uchar fx_sendBC;         // bit4-bit7方位向接收相位补偿码
    //  bit0-bit3方位向发射相位补偿码

    uchar small_rangerecv;   //  bit4-bit7小位延时接收补偿码
    //  bit0-bit3小位延时发射补偿码

    uchar small_YSBC;        // bit4-bit7保留
    //bit0-bit3小位延时接收幅度补偿码

    uchar big_sendBC;        //  bit4-bit7大位延时接收相位补偿码
    //   bit0-bit3大位延时发射相位补偿码

    uchar big_rangerecv;   // bit4-bit7保留
    //  bit0-bit3大位延时接收幅度补偿码

    uchar SPsend;            //射频综合单元发射通道控制 bit7-bit6保留，bit5-bit0：发射数控衰减码


    uchar SPDY_connect;    //射频综合单元发接收道控制 bit7-bit6保留，bit5-bit0：接收数控衰减码

    uchar QZ_low;          //全阵统一衰减量
    uchar kgjzxz;            // 开关矩阵选择

    uchar KJworke_mode;        // 孔径工作模式
    uchar  controy_code;       //收发组件发射/接收控制码 bit4-bit7发射控制码
    //                      bit0-bit3接收控制码

    uchar L_DBsend;          //内定标发射控制码
    uchar L_Drecv;           //内定标接收控制码
    uchar bl[12];            //保留
    uchar b_CS[40];          // 波位参数
    ushort crc;              // 校验和
    ushort frame_end;        // 帧尾
};
//波位参数
struct BWcs{
    uchar bl1[1];               //子阵——保留
    uchar position_send1;       //子阵——方位向发射波位号0-255
    ushort distance_send1;      //子阵——距离向发射波位号 bit15-13保留，bit12-bit0维波号
    ushort distance_B1;         //子阵——距离向波束指向角 bit15-14保留
    ushort position_sendBS1;    //子阵——方位向发射波束起始角 bit15-14保留
    ushort position_recvBS1;    //子阵——方位向接收波束起始角 bit15-14保留
};

// SXKu频段波束控制单元波束指向控制
struct sxkuPd {
    ushort frame_head;       // 帧头
    ushort data_len;         // 数据长度
    uchar order_mark;        // 指令标识
    uchar work_mode;         // 工作模式
    uchar jhj_mode;          // 极化及计算模式
    uchar Comoen_Group;      // 补偿组别
    uchar power;             // 功率及负载态矩阵
    uchar componet_high;     // 组件遥测数据类型（高4位）
    uchar componet_low;      // 组件遥测数据类型（低8位）
    uchar recv_attenuation;  // 接收衰减控制
    uchar bl[1];             // 备用
    uchar bl2[1];            // 备用
    uchar x_send;            // X向发射相位加权码（128组）
    uchar x_recvfd;          // X向接收相位/幅度加权码（128组）
    uchar y_send;            // Y向发射相位加权码（128组）
    uchar y_recvfd;          // y向接收相位/幅度加权码（128组）
    uchar specifies_yx;      // 指定移相值
    uchar specifies_sj;      // 指定衰减值
    uchar specifies_ys;      // 指定延时值
    uchar b_CS[40];          // 波位指向参数
    uchar bl3[1];            // 备用
    ushort crc;              // 校验和
    ushort frame_end;        // 帧尾
};

// 可重构射频前端射频校正开关状态设置
struct Str_Switch {
    ushort frame_head;      // 帧头
    ushort data_len;        // 数据长度
    uchar order_mark;       // 指令标识
    uchar frequency;        // 频段选择
    uchar correction_mode;  // 校正方式
    uchar bl[5];            // 保留
    ushort crc;             // 校验和
    ushort frame_end;       // 帧尾
};

// 可重构射频前端SXKu频段一本振选择设置
struct sxku_ankyloko {
    ushort frame_head;  // 帧头
    ushort data_len;    // 数据长度
    uchar order_mark;   // 指令标识
    uchar CHannel_xz;   // 通道选择
    uchar one_use;      // 一本振使用信息
    uchar bl[5];        // 保留
    ushort crc;         // 校验和
    ushort frame_end;   // 帧尾
};

// 可重构射频前端SXKu频段 接收/发射 通道设置
struct Str_SxkuReSetjs {
    ushort frame_head;   // 帧头
    ushort data_len;     // 数据长度
    uchar order_mark;    // 指令标识
    uchar ad_choose;     // 通道选择
    uchar first_enable;  // SXKu频段第一级放大器使能
    uchar sp_down;       // SXKu频段射频衰减
    uchar recive_down;   // 接收衰减
    uchar wide_fre1;     // 宽带一本振1频率
    uchar wide_fre2;     // 宽带一本振2频率
    uchar gx_fre;        // 高相噪本振频率
    ushort crc;          // 校验和
    ushort frame_end;    // 帧尾
};

// 可重构射频前端SXKu频段 接收/发射 通道设置
struct Str_SxkuReSetfs {
    ushort frame_head;  // 帧头
    ushort data_len;    // 数据长度
    uchar order_mark;   // 指令标识
    uchar ad_choose;    // 通道选择
    uchar recive_down;  // 发射衰减
    uchar wide_fre1;    // 宽带一本振1频率
    uchar wide_fre2;    // 宽带一本振2频率
    uchar gx_fre;       // 高相噪本振频率
    uchar bl[2];        // 保留
    ushort crc;         // 校验和
    ushort frame_end;   // 帧尾
};

// 内存下卸结构体
struct Memory_down {
    ushort pack_mark;    // 包标志0x0731
    ushort pack_number;  // 包顺序0xc000
    ushort pack_Len;     // 包长0x000d
    ushort fun_code;     // 功能识别码0x0003
    ushort data_1;       // 数据字1，0xd01d
    ushort data_2;       // 数据字2，
    ushort addr_high;    // 起始地址高端
    ushort addr_low;     // 起始地址低端
    ushort leng;         // 长度
    ushort addcrc;       // 按字异或和校验(功能识别码--应用数据)
};

//透传spi_can指令还有封装一层
struct packSpi_can{
    ushort can_data_len;    // CAN数据长度
    uchar can_order_mark;   // can指令标识
    //uchar* buff;      //内容
    uchar can_bl;     //保留
    ushort can_crc;   //can校验和
};

// 高算力平台调试指令1553b
struct gsl_test {
    ushort frame_head;  // 帧头
    ushort data_len;    // 数据长度
    uchar order_mark;   // 指令标识
    uchar pd_xz;        // 频段选择
    uchar cs1;          // 参数1
    uchar cs2;          // 参数2
    uchar cs3;          // 参数3
    uchar cs4;          // 参数4
    uchar cs5;          // 参数5
    uchar cs6;          // 参数6

    ushort crc;         // 校验和
    ushort frame_end;   // 帧尾
};
// 高算力平台调试指令CAN
struct gsl_test_CAN {

    ushort can_data_len;    // CAN数据长度
    uchar can_order_mark;   // can指令标识

    ushort frame_head;  // 帧头
    ushort data_len;    // 数据长度
    uchar order_mark;   // 指令标识
    uchar pd_xz;        // 频段选择
    uchar cs1;          // 参数1
    uchar cs2;          // 参数2
    uchar cs3;          // 参数3
    uchar cs4;          // 参数4
    uchar cs5;          // 参数5
    uchar cs6;          // 参数6

    ushort crc;         // 校验和
    ushort frame_end;   // 帧尾

    uchar can_bl;     //保留
    ushort can_crc;   //can校验和

};
/*************************************************
 <类   名>
 <概要说明>    用于目的地址和通道号测试的结构体
 <详细说明>    无

 <作    者>   ybl
 <时    间>   2023-10-13
 <修    改>
**************************************************/
struct DC_test {
    uchar channelnum;   // 通道编号
    uchar Raddrtyp;     // 目的地址：地址类型
    ushort Rstartmark;  // 目的地址：卫星标志
    uchar Rpartcode;    // 目的地址：部位代码
};

// 慢速遥测结构体--载荷电压模拟量-整机、单机关键状态量(2s)
struct slow_Group_1 {
    // 第一组遥测(128字节)
    ushort pack_head_1;    // 第一组版本号，包标志0x0732;
    ushort pack_number_1;  // 第一组包顺序控制
    ushort pack_Len_1;     // 第一组包长度

    uchar zh_ccststus;//bit7-6,综合管控单元-重构进行状态(5.22新加5字节)
    //bit5综合管控单元-重传标志
    //bit4综合管控单元-重传前进通道
    //bit3-0综合管控单元-保留
    uchar cc_number;  //综合管控单元-重传包个数
    uchar cc_cnt[3];  //综合管控单元-重传包位序号计数


    uchar L_PRFmon;         // L频段-触发PRF监测遥测(14bytes)
    uchar L_computermon;    // L频段-计算机状态监测遥测
    uchar L_busmon;         // L频段-总线状态监测遥测
    uchar L_ZJnumbermon;    // L频段-数字综合单元主机电源监测遥测
    uchar L_BJnumbermon;    // L频段-数字综合单元备机电源监测遥测
    uchar L_Powermon;       // L频段-组合定标功放电源监测
    uchar L_otherpowermon;  // L频段-其他电源监测
    uchar L_12output;       // L频段-射频收发模块1-2输出监测
    uchar L_36output;       // L频段-射频收发模块3-6输出监测
    uchar L_outputmon;      // L频段-组合定标模块输出监测
    uchar L_33Vmon;         // L频段-定时波控3.3V监测
    uchar L_Z5Vmon;         // L频段-定时波控主5V监测
    uchar L_B5Vmon;         // L频段-定时波控备5V监测
    uchar L_zFace;          //L频段-阵面1-4天线接收/发射电源开关状态(4.19添加1字节)


    uchar Sxku_XLswitch;     // SXKu频段-消浪涌开关遥测(15bytes)
    uchar Sxku_FDswitch;     // SXKu频段-放电开关遥测
    uchar Sxku_Zbeamswitch;  // SXKu频段-波束控制器主机开关遥测
    uchar Sxku_Bbeamswitch;  // SXKu频段-波束控制器备机开关遥测
    uchar Sxku_BK_main5v;    // SXKu频段-波控机主5V电压遥测
    uchar Sxku_BK_sub5v;     // SXKu频段-波控机备5V电压遥测

    uchar Sxkum1_jsswitch;  // SxKu频段模块1二次电源接收开关遥测
    uchar Sxkum1_fsswitch;  // SxKu频段模块1二次电源发射开关遥测
    uchar Sxkum2_jsswitch;  // SxKu频段模块2二次电源接收开关遥测
    uchar Sxkum2_fsswitch;  // SxKu频段模块2二次电源发射开关遥测
    uchar Sxkum3_jsswitch;  // SxKu频段模块3二次电源接收开关遥测
    uchar Sxkum3_fsswitch;  // SxKu频段模块3二次电源发射开关遥测
    uchar Sxkum4_jsswitch;  // SxKu频段模块4二次电源接收开关遥测
    uchar Sxkum4_fsswitch;  // SxKu频段模块4二次电源发射开关遥测

    uchar Sxku_sf_comunit;  //SXKu频段相控阵天线-射频收发单元-二次电源状态1-6(4.19，新加1字节)
    //SXKu频段相控阵天线-射频收发单元-接收电,发射电


    uchar ZH_Aswitch;    // 载荷-A组消浪涌开关状态遥测(8bytes)
    uchar ZH_Bswitch;    // 载荷-B组消浪涌开关状态遥测
    uchar ZH_Cswitch;    // 载荷-C组消浪涌开关状态遥测
    uchar ZH_Dswitch;    // 载荷-D组消浪涌开关状态遥测
    uchar A_Voltagemon;  // 载荷-A组母线电压遥测
    uchar B_Voltagemon;  // 载荷-B组母线电压遥测
    uchar C_Voltagemon;  // 载荷-C组母线电压遥测
    uchar D_Voltagemon;  // 载荷-D组母线电压遥测

    uchar z_up6VA;    // 可重构射频前端主份+6VA供电(20bytes)
    uchar z_down6VA;  // 可重构射频前端主份-6VA供电
    uchar z_up15VA;   // 可重构射频前端主份+15VA供电
    uchar z_up5VD;    // 可重构射频前端主份+5VD供电
    uchar z_up6V2A;   // 可重构射频前端主份+6V2A供电
    uchar b_up6VA;    // 可重构射频前端备份+6VA供电
    uchar b_down6VA;  // 可重构射频前端备份-6VA供电
    uchar b_up15VA;   // 可重构射频前端备份+15VA供电
    uchar b_up5VD;    // 可重构射频前端备份+5VD供电
    uchar b_up6V2A;   // 可重构射频前端备份+6V2A供电

    uchar gsl1_6Vpowemon;    // 可重构高算力平台1-(+6VA)供电模拟量遥测
    uchar gsl1_5Vl1powemon;  // 可重构高算力平台1-(+5VD)路1供电模拟量遥测
    uchar gsl1_5Vl2powemon;  // 可重构高算力平台1-(+5VD)路2供电模拟量遥测
    uchar gsl1_5Vl3powemon;  // 可重构高算力平台1-(+5VD)路3供电模拟量遥测(4.19新加1字节)
    uchar gsl1_5Vl4powemon;  // 可重构高算力平台1-(+5VD)路4供电模拟量遥测(4.19新加1字节)
    uchar gsl2_6Vpowemon;    // 可重构高算力平台2-(+6VA)供电模拟量遥测
    uchar gsl2_5Vl1powemon;  // 可重构高算力平台2-(+5VD)路1供电模拟量遥测
    uchar gsl2_5Vl2powemon;  // 可重构高算力平台2-(+5VD)路2供电模拟量遥测
    uchar gsl2_5Vl3powemon;  // 可重构高算力平台2-(+5VD)路3供电模拟量遥测(4.19新加1字节)
    uchar gsl2_5Vl4powemon;  // 可重构高算力平台2-(+5VD)路4供电模拟量遥测(4.19新加1字节)


    uchar L_sendrecv;     // bit7-bit2:保留，bit1-bit0:L频段-天线收发状态
    uchar Sxku_sendrecv;  // bit7-bit2:保留，bit1-bit0:SXKu频段-天线收发状态

    uchar gsl1_interDSP6701;// bit7:保留,
    // bit6,可重构高算力平台1-接口控制模块-接口控制模块DSP6678心跳(4.19添加1bit)
    // bit5,高算力1-接口控制模块-接口控制模块DSP6701加载状态;
    // bit4,DSP6678加载状态,
    // bit3,接口控制模块V7加载状态
    // bit2,收发处理模块K7加载状态
    // bit1,数据处理模块A的K7加载状态
    // bit0,数据处理模块B的K7加载状态

    uchar gsl1_V71;           // bit7-bit2:保留,
    // bit1,可重构高算力平台1-收发处理模块-V7_1加载状态
    // bit0,可重构高算力平台1-收发处理模块-V7_2加载状态

    uchar gsl1_SJA_DSP6678;  // bit7-bit4:保留
    //bit3,可重构高算力平台1-数据处理模块A-DSP6678心跳(4.19加1bit)
    // bit2，可重构高算力平台1-数据处理模块A-DSP6678加载状态
    // bit1，可重构高算力平台1-数据处理模块A-V7_1加载状态
    // bit0，可重构高算力平台1-数据处理模块A-V7_2加载状态

    uchar gsl1_SJB_DSP6678;  // bit7-bit4:保留
    //bit3，可重构高算力平台1-数据处理模块B-DSP6678心跳(4.19加1bit)
    // bit2，可重构高算力平台1-数据处理模块B-DSP6678加载状态
    // bit1，可重构高算力平台1-数据处理模块B-V7_1加载状态
    // bit0，可重构高算力平台1-数据处理模块B-V7_2加载状态

    uchar gsl2_interDSP6701;  // bit7:保留
    //bit6可重构高算力平台2-接口控制模块-接口控制模块DSP6678心跳(4.19加1bit)
    // bit5可重构高算力平台2-接口控制模块-接口控制模块DSP6701加载状态
    // bit4可重构高算力平台2-接口控制模块-接口控制模块DSP6778加载状态
    // bit3可重构高算力平台2-接口控制模块-接口控制模块V7加载状态
    // bit2可重构高算力平台2-接口控制模块-收发处理模块K7加载状态
    // bit1可重构高算力平台2-接口控制模块-数据处理模块A的K7加载状态
    // bit0可重构高算力平台2-接口控制模块-数据处理模块B的K7加载状态

    uchar gsl2_V71;  // bit7-bit2:保留
    // bit1可重构高算力平台2-收发处理模块-V7_1加载状态
    // bit0可重构高算力平台2-收发处理模块-V7_2加载状态

    uchar gsl2_SJA_DSP6678;  // bit7-bit4:保留
    // bit3,可重构高算力平台2-数据处理模块A-DSP6678心跳(4.19加1bit)
    // bit2可重构高算力平台2-数据处理模块A-DSP6678加载状态
    // bit1可重构高算力平台2-数据处理模块A-V7_1加载状态
    // bit0可重构高算力平台2-数据处理模块A-V7_2加载状态

    uchar gsl2_SJB_DSP6678;  // bit7-bit4:保留
    // bit3,可重构高算力平台2-数据处理模块B-DSP6678心跳(4.19加1bit)
    // bit2可重构高算力平台2-数据处理模块B-DSP6678加载状态
    // bit1可重构高算力平台2-数据处理模块B-V7_1加载状态
    // bit0可重构高算力平台2-数据处理模块B-V7_2加载状态

    uchar comper_work;  // 综合管控单元-工作状态(47bytes)
    uchar comper_canA;  // 综合管控单元-CAN通道A复位次数
    uchar comper_canB;  // 综合管控单元-CAN通道B复位次数

    uchar L_canexception;  // 综合管控单元-L频段相控阵天线-CAN接收异常帧次数
    uchar Sxku_canexception;  // 综合管控单元-SXKu频段相控阵天线-CAN接收异常帧次数
    uchar kcg_canexception;   // 综合管控单元-可重构射频前端-CAN接收异常帧次数
    uchar gsl1_canexption;    // 综合管控单元-可重构高算力平台1-CAN接收异常帧次数
    uchar gsl2_canexption;    // 综合管控单元-可重构高算力平台2-CAN接收异常帧次数

    uchar L_recount;          // 综合管控单元-L频段相控阵天线-接收计数(4.19加1字节）
    uchar SXKu_recount;       // 综合管控单元-SXKu频段相控阵天线-接收计数(4.19加1字节）
    uchar kcgspqd_recount;    // 综合管控单元-可重构射频前端-接收计数(4.19加1字节）
    uchar gsl1_recount;       // 综合管控单元-可重构高算力平台1-接收计数(4.19加1字节）
    uchar gsl2_recount;       //综合管控单元-可重构高算力平台2-接收计数(4.19加1字节）

    uchar ZL_1553number;  // 综合管控单元-1553B总线指令接收帧计数
    uchar ZS_1553number;  // 综合管控单元-1553B总线注数接收帧计数(4.19加1字节）

    uchar Z_1553number;   // 综合管控单元-1553B总线帧接收异常次数
    uchar FW_1553number;  // 综合管控单元-1553B总线复位次数


    ushort K_recvnumber;    // 综合管控单元-千兆网口软件接收帧计数
    ushort K_sendnumber;    // 综合管控单元-千兆网口软件发送帧计数

    uchar front_frame;      // 1553B指令执行结果-上一帧
    uchar now_frame;        // 1553B指令执行结果-当前帧

    uchar Effective;        // 综合管控单元-有效任务总数
    uchar YCnumber;         // 综合管控单元-已存任务总数

    ushort Currently_number;  // 综合管控单元-当前执行任务的流水号
    ushort gsl1_miss1;  // 综合管控单元-可重构高算力平台1-当前处理FPGA1执行的主任务ID
    ushort gsl1_miss2;  // 综合管控单元-可重构高算力平台1-当前处理FPGA2执行的主任务ID
    ushort gsl1_miss3;  // 综合管控单元-可重构高算力平台1-当前处理FPGA3执行的主任务ID
    ushort gsl1_miss4;  // 综合管控单元-可重构高算力平台1-当前处理FPGA4执行的主任务ID
    ushort gsl2_miss1;  // 综合管控单元-可重构高算力平台2-当前处理FPGA1执行的主任务ID
    ushort gsl2_miss2;  // 综合管控单元-可重构高算力平台2-当前处理FPGA2执行的主任务ID
    ushort gsl2_miss3;  // 综合管控单元-可重构高算力平台2-当前处理FPGA3执行的主任务ID
    ushort gsl2_miss4;  // 综合管控单元-可重构高算力平台2-当前处理FPGA4执行的主任务ID
    uint gk_time;       // 综合管控单元-管控机星时

    uchar gsl1_workpd;    // bit7-bit4，保留，bit3综合管控单元-可重构高算力平台1-工作频段（5.22更改）
    // bit2综合管控单元-可重构高算力平台2-工作频段
    // bit1综合管控单元-可重构高算力平台1-主从（控射频前端）状态
    // bit0综合管控单元-可重构高算力平台2-主从（控射频前端）状态

    uchar sorft_status;         //bit7    综合管控单元-软件上注块存储快状态（5.22更改）
                                //bit6-bit0综合管控单元-Can软件更新进度或6G刷新进度
    uchar up_status;          //综合管控单元-管控机软件上注更新状态(4.19加1字节）

};

// 电压、开关状态-单机内部、温度(4s)
struct slow_Group_2 {
    // 第二组遥测

    ushort pack_head_2;    // 第一组版本号，包标志0x0732;
    ushort pack_number_2;  // 第一组包顺序控制
    ushort pack_Len_2;     // 第一组包长度

    uchar L_sendPRF;    // L频段相控阵天线-波控发射PRF监测
    uchar L_recvPRF;    // L频段相控阵天线-波控接收PRF监测
    uchar L_Z1Access1;  // L频段相控阵天线-天线子阵1通道1
    uchar L_Z1Access2;  // L频段相控阵天线-天线子阵1通道2
    uchar L_Z3Access2;  // L频段相控阵天线-天线子阵3通道2
    uchar L_Z3Access3;  // L频段相控阵天线-天线子阵3通道3
    uchar L_Z2Access4;  // L频段相控阵天线-天线子阵2通道4
    uchar L_Z2Access5;  // L频段相控阵天线-天线子阵2通道5
    uchar L_Z4Access5;  // L频段相控阵天线-天线子阵4通道5
    uchar L_Z4Access6;  // L频段相控阵天线-天线子阵4通道6

    uchar SAR_WorkMode;  // SAR成像-系统工作状态(4.19添加1字节)
    uchar SAR_Status;     // bit7-bit4SAR成像-SAR分系统状态、bit3-bit0SAR成像-指令接收/处理状态(4.19添加1字节)
    uchar SAR_EDAC;       //SAR成像-EDAC错误计数(4.19添加1字节)
    uchar SAR_CPU;        //SAR成像-CPU复位计数(4.19添加1字节)
    uchar SAR_CAN;        //SAR成像-CAN总线复位计数(4.19添加1字节)
    uchar SAR_reCount;    //SAR成像-收指令计数(4.19添加1字节)


    uchar Sxku_RFswitch;  //SXKu频段相控阵天线-射频收发单元-开关状态
                            //1234路开:[85,85]/1256路开[153,153]/3456路开[170,170]


    uchar gsl1_JKpower;  // bit7-
    //bit6 可重构高算力平台1-接口控制模块-光模块参数更新状态
    // bit5-可重构高算力平台1-接口控制模块-光模块供电指示(FIBER_3V3_PG)
    // bit4-可重构高算力平台1-接口控制模块-DSP供电指示(PG_DSPVTT)
    // bit3-可重构高算力平台1-接口控制模块-DSP供电指示(PG_DSP1V8)
    // bit2-可重构高算力平台1-接口控制模块-DSP供电指示(PG_DSP1V5)
    // bit1-可重构高算力平台1-接口控制模块-DSP供电指示(PG_DSP1V0_SMART)
    // bit0-可重构高算力平台1-接口控制模块-DSP供电指示(PG_DSP1V0)

    uchar gsl1_SFFPGApower;  // bit7-bit4保留
    // bit3-可重构高算力平台1-收发处理模块-FPGA1的1DDRVTT电源PG指示
    // bit2-可重构高算力平台1-收发处理模块-FPGA1的2DDRVTT电源PG指示
    // bit1-可重构高算力平台1-收发处理模块-FPGA2的1DDRVTT电源PG指示
    // bit0-可重构高算力平台1-收发处理模块-FPGA2的2DDRVTT电源PG指示

    uchar gsl1_SFAD1power;  // bit7-bit5保留
    // bit4-可重构高算力平台1-收发处理模块-AD1电源1V电源PG指示
    // bit3-可重构高算力平台1-收发处理模块-AD1电源1_1V电源PG指示
    // bit2-可重构高算力平台1-收发处理模块-AD1电源1_2V电源PG指示
    // bit1-可重构高算力平台1-收发处理模块-AD1电源1.3VA电源PG指示
    //// bit1-可重构高算力平台1-收发处理模块-AD1电源1.3VB电源PG指示//(4.22去除1bit)
    // bit0-可重构高算力平台1-收发处理模块-AD1电源2V电源PG指示

    uchar gsl1_SFAD2power;  // bit7-bit5保留
    // bit4-可重构高算力平台1-收发处理模块-AD2电源1V电源PG指示
    // bit3-可重构高算力平台1-收发处理模块-AD2电源1_1V电源PG指示
    // bit2-可重构高算力平台1-收发处理模块-AD2电源1_2V电源PG指示
    //// bit2-可重构高算力平台1-收发处理模块-AD2电源1.3VA电源PG指示//(4.22去除1bit)
    // bit1-可重构高算力平台1-收发处理模块-AD2电源1.3VB电源PG指示
    // bit0-可重构高算力平台1-收发处理模块-AD2电源2V电源PG指示

    uchar gsl1_SFAD3power;  // bit7-bit4保留
    // bit3-可重构高算力平台1-收发处理模块-AD3电源1V电源PG指示
    // bit2-可重构高算力平台1-收发处理模块-AD3电源1_1V电源PG指示
    // bit1-可重构高算力平台1-收发处理模块-AD3电源1_2V电源PG指示
    //// bit2-可重构高算力平台1-收发处理模块-AD3电源1.3VA电源PG指示//(4.22去除1bit)
    //// bit1-可重构高算力平台1-收发处理模块-AD3电源1.3VB电源PG指示//(4.22去除1bit)
    // bit0-可重构高算力平台1-收发处理模块-AD3电源2V电源PG指示

    uchar gsl1_SFpower;  // bit7-bit6保留
    // bit5-可重构高算力平台1-收发处理模块-1.5V电源PG指示
    // bit4-可重构高算力平台1-收发处理模块-2_1.5V电源PG指示
    // bit3-可重构高算力平台1-收发处理模块-AD1电源1.8V电源PG指示
    // bit2-可重构高算力平台1-收发处理模块-2.8V电源PG指示
    // bit1-可重构高算力平台1-收发处理模块-模拟3.3V电源PG指示
    // bit0-可重构高算力平台1-收发处理模块-模拟3.3_2电源PG指示

    uchar gsl1_SJAlightpower;  // bit7-
    //bit6可重构高算力平台1-数据处理模块A-光模块参数更新状态
    // bit5-可重构高算力平台1-数据处理模块A-光模块(PG_FIB3V3)
    // bit4-可重构高算力平台1-数据处理模块A-DSP电源(PG_DSPVTT)
    // bit3-可重构高算力平台1-数据处理模块A-DSP电源(PG_DSP1V8)
    // bit2-可重构高算力平台1-数据处理模块A-DSP电源(PG_DSP1V5)
    // bit1-可重构高算力平台1-数据处理模块A-DSP电源(PG_DSP1V0_SMART)
    // bit0-可重构高算力平台1-数据处理模块A-DSP电源(PG_DSP1V0)

    uchar gsl1_SJBlightpower;  // bit7
    //bit6可重构高算力平台1-数据处理模块B-光模块参数更新状态
    // bit5-可重构高算力平台1-数据处理模块B-光模块(PG_FIB3V3)
    // bit4-可重构高算力平台1-数据处理模块B-DSP电源(PG_DSPVTT)
    // bit3-可重构高算力平台1-数据处理模块B-DSP电源(PG_DSP1V8)
    // bit2-可重构高算力平台1-数据处理模块B-DSP电源(PG_DSP1V5)
    // bit1-可重构高算力平台1-数据处理模块B-DSP电源(PG_DSP1V0_SMART)
    // bit0-可重构高算力平台1-数据处理模块B-DSP电源(PG_DSP1V0)

    //  uchar gsl2_5Vl3YC;  // 可重构高算力平台2-（+5VD）路3供电模拟量遥测(4.22去除2字节)
    //  uchar gsl2_5Vl4YC;  // 可重构高算力平台2-（+5VD）路3供电模拟量遥测

    uchar gsl2_JKlightpower;  // bit7
    //bit6 可重构高算力平台1-接口控制模块-光模块参数更新状态
    // bit5-可重构高算力平台2-接口控制模块-光模块供电指示(FIBER_3V3_PG)
    // bit4-可重构高算力平台2-接口控制模块-DSP供电指示(PG_DSPVTT)
    // bit3-可重构高算力平台2-接口控制模块-DSP供电指示(PG_DSP1V8)
    // bit2-可重构高算力平台2-接口控制模块-DSP供电指示(PG_DSP1V5)
    // bit1-可重构高算力平台2-接口控制模块-DSP供电指示(PG_DSP1V0_SMART)
    // bit0-可重构高算力平台2-接口控制模块-DSP供电指示(PG_DSP1V0)

    uchar gsl2_SFFPGA;  // bit7-bit4保留
    // bit3-可重构高算力平台2-收发处理模块-FPGA1的1DDRVTT电源PG指示
    // bit2-可重构高算力平台2-收发处理模块-FPGA1的2DDRVTT电源PG指示
    // bit1-可重构高算力平台2-收发处理模块-FPGA2的1DDRVTT电源PG指示
    // bit0-可重构高算力平台2-收发处理模块-FPGA2的2DDRVTT电源PG指示

    uchar gsl2_SFAD1power;  // bit7-bit5保留
    // bit4-可重构高算力平台2-收发处理模块-AD1电源1V电源PG指示
    // bit3-可重构高算力平台2-收发处理模块-AD1电源1_1V电源PG指示
    // bit2-可重构高算力平台2-收发处理模块-AD1电源1_2V电源PG指示
    // bit1-可重构高算力平台2-收发处理模块-AD1电源1.3VA电源PG指示
    //// bit1-可重构高算力平台2-收发处理模块-AD1电源1.3VB电源PG指示//(4.22去除1bit)
    // bit0-可重构高算力平台2-收发处理模块-AD1电源2V电源PG指示

    uchar gsl2_SFAD2power;  // bit7-bit6保留
    // bit4-可重构高算力平台2-收发处理模块-AD2电源1V电源PG指示
    // bit3-可重构高算力平台2-收发处理模块-AD2电源1_1V电源PG指示
    // bit2-可重构高算力平台2-收发处理模块-AD2电源1_2V电源PG指示
    //// bit2-可重构高算力平台2-收发处理模块-AD2电源1.3VA电源PG指示//(4.22去除1bit)
    // bit1-可重构高算力平台2-收发处理模块-AD2电源1.3VB电源PG指示
    // bit0-可重构高算力平台2-收发处理模块-AD2电源2V电源PG指示

    uchar gsl2_SFAD3power;  // bit7-bit4保留
    // bit3-可重构高算力平台2-收发处理模块-AD3电源1V电源PG指示
    // bit2-可重构高算力平台2-收发处理模块-AD3电源1_1V电源PG指示
    // bit1-可重构高算力平台2-收发处理模块-AD3电源1_2V电源PG指示
    //// bit2-可重构高算力平台2-收发处理模块-AD3电源1.3VA电源PG指示//(4.22去除1bit)
    //// bit1-可重构高算力平台2-收发处理模块-AD3电源1.3VB电源PG指示//(4.22去除1bit)
    // bit0-可重构高算力平台2-收发处理模块-AD3电源2V电源PG指示

    uchar gsl2_SFpower;  // bit7-bit6保留
    // bit5-可重构高算力平台2-收发处理模块-1.5V电源PG指示
    // bit4-可重构高算力平台2-收发处理模块-2_1.5V电源PG指示
    // bit3-可重构高算力平台2-收发处理模块-AD1电源1.8V电源PG指示
    // bit2-可重构高算力平台2-收发处理模块-2.8V电源PG指示
    // bit1-可重构高算力平台2-收发处理模块-模拟3.3V电源PG指示
    // bit0-可重构高算力平台2-收发处理模块-模拟3.3_2电源PG指示

    uchar gsl2_SJAlightpower;  // bit7-
    // bit6 可重构高算力平台2-数据处理模块A-光模块参数更新状态
    // bit5-可重构高算力平台2-数据处理模块A-光模块(PG_FIB3V3)
    // bit4-可重构高算力平台2-数据处理模块A-DSP电源(PG_DSPVTT)
    // bit3-可重构高算力平台2-数据处理模块A-DSP电源(PG_DSP1V8)
    // bit2-可重构高算力平台2-数据处理模块A-DSP电源(PG_DSP1V5)
    // bit1-可重构高算力平台2-数据处理模块A-DSP电源(PG_DSP1V0_SMART)
    // bit0-可重构高算力平台2-数据处理模块A-DSP电源(PG_DSP1V0)

    uchar gsl2_SJBlightpower;  // bit7
    // bit6 可重构高算力平台2-数据处理模块B-光模块参数更新状态
    // bit5-可重构高算力平台2-数据处理模块B-光模块(PG_FIB3V3)
    // bit4-可重构高算力平台2-数据处理模块B-DSP电源(PG_DSPVTT)
    // bit3-可重构高算力平台2-数据处理模块B-DSP电源(PG_DSP1V8)
    // bit2-可重构高算力平台2-数据处理模块B-DSP电源(PG_DSP1V5)
    // bit1-可重构高算力平台2-数据处理模块B-DSP电源(PG_DSP1V0_SMART)
    // bit0-可重构高算力平台2-数据处理模块B-DSP电源(PG_DSP1V0)

    uchar ZH_OCCANstatus;  // bit7-bit2保留
    // bit1-综合管控单元-OC开关状态-L频段相控阵天线消浪涌
    // bit0-综合管控单元-OC开关状态-L频段相控阵天线31V总电源
    //// bit2-综合管控单元-OC开关状态-SXKu频段相控阵天线放电开关//(4.22去除1bit)
    //// bit1-综合管控单元-OC开关状态-综合处理模块//(4.22去除1bit)
    //// bit0-综合管控单元-CAN开关状态-L频段射频综合单元//(4.22去除1bit)

    //(4.22去除1字节)
    //uchar ZH_CANsxku;  // bit7-综合管控单元-CAN开关状态-SXKu频段阵面4天线发射
    // bit6-综合管控单元-CAN开关状态-SXKu频段阵面3天线发射
    // bit5-综合管控单元-CAN开关状态-SXKu频段阵面2天线发射
    // bit4-综合管控单元-CAN开关状态-SXKu频段阵面1天线发射
    // bit3-综合管控单元-CAN开关状态-SXKu频段阵面4天线接收
    // bit2-综合管控单元-CAN开关状态-SXKu频段阵面3天线接收
    // bit1-综合管控单元-CAN开关状态-SXKu频段阵面2天线接收
    // bit0-综合管控单元-CAN开关状态-SXKu频段阵面1天线接收

    uchar ZH_aivoltage;  // 综合管控单元-综合处理模块-AI电压
    uchar ZH_DSp6678;  // 综合管控单元-综合处理模块-3个DSP6678总电压
    //uchar ZH_V7voltage;  // 综合管控单元-综合处理模块-V7电压（24.5.7删除）

    uchar L_RFswitch;  // bit7-bit6保留
    // bit5-可重构射频前端-SXKu频段射频通道56
    // bit4-可重构射频前端-SXKu频段射频通道34
    // bit3-可重构射频前端-SXKu频段射频通道12
    // bit2-可重构射频前端-L波段射频切换调理模块遥测量
    // bit1-可重构射频前端-中频切换模块1遥测量
    // bit0-可重构射频前端-中频切换模块2遥测量

    uchar RF_SxkuPH35;  // bit7-可重构射频前端-宽带一本振2主环锁定指示
                        // bit6-可重构射频前端-宽带一本振2副环锁定指示
                        // bit5-可重构射频前端-备份高相噪一本振锁定指示
                        // bit4-可重构射频前端-备份二本振锁定指示
                        // bit3-可重构射频前端-宽带一本振1主环锁定指示
                        // bit2-可重构射频前端-宽带一本振1副环锁定指示
                        // bit1-可重构射频前端-主份高相噪一本振锁定指示
                        // bit0-可重构射频前端-主份二本振锁定指示


    //
    uchar gsl1_JKlock;  // bit7-保留
    // bit6-可重构高算力平台1-接口控制模块-模块栓锁
    // bit5-可重构高算力平台1-接口控制模块-收发处理模块栓锁(收发LRM_PG1)
    // bit4-可重构高算力平台1-接口控制模块-数据处理1模块栓锁(数据1LRM_PG2)
    // bit3-可重构高算力平台1-接口控制模块-数据处理2模块栓锁(数据2LRM_PG3)
    // bit2-可重构高算力平台1-接口控制模块-锁相环(V2_LD1)
    // bit1-可重构高算力平台1-接口控制模块-锁相环(V2_LD2)
    // bit0-可重构高算力平台1-接口控制模块-锁相环(V2_LD3)


    //(4.19新加1字节)
    uchar gsl1_jk_v7; //bit5-7,保留
    //bit4,可重构高算力平台1-接口控制模块-V7与综合管控单元RapidIO主备
    //bit3,可重构高算力平台1-接口控制模块-V7与高速交换机光纤主备
    //bit2,可重构高算力平台1-接口DSP6678与接口控制 V7建链指示
    //bit1,可重构高算力平台1-接口DSP6678与数据处理1 DSP6678建链指示
    //bit0,可重构高算力平台1-接口DSP6678与数据处理2 DSP6678建链指示


    uint gsl1_JKV7recv;  // 可重构高算力平台1-接口板V7接收数据计数
    uint gsl1_JKV7send;  // 可重构高算力平台1-接口板V7发送数据计数
    uint gsl1_DSP_time;  // 可重构高算力平台1-接口板DSP6678星时

    //(4.22新增1字节)
    uchar gsl1_ADC_DAC;   //bit7-6
    //bit5,可重构高算力平台1-收发处理模块-ADC1建链指示
    //bit4,可重构高算力平台1-收发处理模块-ADC2建链指示
    //bit3,可重构高算力平台1-收发处理模块-ADC3建链指示
    //bit2,可重构高算力平台1-收发处理模块-DAC1建链指示
    //bit1,可重构高算力平台1-收发处理模块-DAC2建链指示
    //bit0,可重构高算力平台1-收发处理模块-DAC3建链指示


    uchar gsl2_JKlock;    // bit7-保留
    // bit6-可重构高算力平台2-接口控制模块-模块栓锁
    // bit5-可重构高算力平台2-接口控制模块-收发处理模块栓锁(收发LRM_PG1)
    // bit4-可重构高算力平台2-接口控制模块-数据处理1模块栓锁(数据1LRM_PG2)
    // bit3-可重构高算力平台2-接口控制模块-数据处理2模块栓锁(数据2LRM_PG3)
    // bit2-可重构高算力平台2-接口控制模块-锁相环(V2_LD1)
    // bit1-可重构高算力平台2-接口控制模块-锁相环(V2_LD2)
    // bit0-可重构高算力平台2-接口控制模块-锁相环(V2_LD3)

    //(4.19新加1字节)
    uchar gsl2_jk_v7;  //bit5-7,保留
    //bit4,可重构高算力平台2-接口控制模块-V7与综合管控单元RapidIO主备
    //bit3,可重构高算力平台2-接口控制模块-V7与高速交换机光纤主备
    //bit2,可重构高算力平台2-接口DSP6678与接口控制 V7建链指示
    //bit1,可重构高算力平台2-接口DSP6678与数据处理1 DSP6678建链指示
    //bit0,可重构高算力平台2-接口DSP6678与数据处理2 DSP6678建链指示



    uint gsl2_JKV7recv;   // 可重构高算力平台2-接口板V7接收数据计数
    uint gsl2_JKV7send;   // 可重构高算力平台2-接口板V7发送数据计数
    uint gsl2_DSP_time;   // 可重构高算力平台2-接口板DSP6678星时

    //(4.22新增1字节)
    uchar gsl2_ADC_DAC;     //bit7-6
    //bit5,可重构高算力平台2-收发处理模块-ADC1建链指示
    //bit4,可重构高算力平台2-收发处理模块-ADC2建链指示
    //bit3,可重构高算力平台2-收发处理模块-ADC3建链指示
    //bit2,可重构高算力平台2-收发处理模块-DAC1建链指示
    //bit1,可重构高算力平台2-收发处理模块-DAC2建链指示
    //bit0,可重构高算力平台2-收发处理模块-DAC3建链指示

    uchar L_RFWD;          // L频段相控阵天线-射频综合单元温度
    uchar L_numberWD;      // L频段相控阵天线-数字综合单机温度
    ushort gsl1_JKV7WD;    // 可重构高算力平台1-接口控制模块-V7温度
    ushort gsl1_JKADC1WD;  // 可重构高算力平台1-收发处理模块-ADC1温度
    ushort gsl1_JKADC2WD;  // 可重构高算力平台1-收发处理模块-ADC2温度
    ushort gsl1_JKADC3WD;  // 可重构高算力平台1-收发处理模块-ADC3温度
    ushort gsl1_SFV71WD;   // 可重构高算力平台1-收发处理模块-V7_1温度
    ushort gsl1_SFV72WD;   // 可重构高算力平台1-收发处理模块-V7_2温度
    ushort gsl1_SJAV71WD;  // 可重构高算力平台1-数据处理模块A-V 7_1温度
    ushort gsl1_SJAV72WD;  // 可重构高算力平台1-数据处理模块A-V 7_2温度
    ushort gsl1_SJBV71WD;  // 可重构高算力平台1-数据处理模块B-V 7_1温度
    ushort gsl1_SJBV72WD;  // 可重构高算力平台1-数据处理模块B-V 7_2温度
    ushort gsl2_JKV7WD;    // 可重构高算力平台2-接口控制模块-V7温度
    ushort gsl2_JKADC1WD;  // 可重构高算力平台2-收发处理模块-ADC1温度
    ushort gsl2_JKADC2WD;  // 可重构高算力平台2-收发处理模块-ADC2温度
    ushort gsl2_JKADC3WD;  // 可重构高算力平台2-收发处理模块-ADC3温度
    ushort gsl2_SFV71WD;   // 可重构高算力平台2-收发处理模块-V7_1温度
    ushort gsl2_SFV72WD;   // 可重构高算力平台2-收发处理模块-V7_2温度
    ushort gsl2_SJAV71WD;  // 可重构高算力平台2-数据处理模块A-V 7_1温度
    ushort gsl2_SJAV72WD;  // 可重构高算力平台2-数据处理模块A-V 7_2温度
    ushort gsl2_SJBV71WD;  // 可重构高算力平台2-数据处理模块B-V 7_1温度
    ushort gsl2_SJBV72WD;  // 可重构高算力平台2-数据处理模块B-V 7_2温度
    ushort ZH_V7WD;        // 综合管控单元-管控模块-V7温度
    ushort GK_clV7WD;      //综合管控单元-综合处理模块-V7温度
    ushort GK_AIWD;        //综合管控单元-综合处理模块-AI温度
    uchar GK_TaskSum;        //综合管控单元-任务模板数量（保留）

    uchar GSL_jianLian;        //bit7:可重构高算力平台1-接口控制模块-V7与交换A光纤建链指示
                               //bit6:可重构高算力平台1-接口控制模块-V7与交换B光纤建链指示
                               //bit5:可重构高算力平台1-接口控制模块-V7与管控主Rapid IO建链指示
                               //bit4:可重构高算力平台1-接口控制模块-V7与管控备Rapid IO建链指示
                               //bit3:可重构高算力平台2-接口控制模块-V7与交换A光纤建链指示
                               //bit2:可重构高算力平台2-接口控制模块-V7与交换B光纤建链指示
                               //bit1:可重构高算力平台2-接口控制模块-V7与管控主Rapid IO建链指示
                               //bit0:可重构高算力平台2-接口控制模块-V7与管控备Rapid IO建链指示

    uchar L_reseSwitch;        //L频段相控阵天线-射频收发单元-开关状态

    uchar Tprotect_gsl1;      //综合管控单元-温度保护关断温度阈值-高算力1
    uchar Tprotect_gsl2;      //综合管控单元-温度保护关断温度阈值-高算力2


    uchar Mess_gsl1_2;         //bit7:可重构高算力平台1-数据处理模块A-与高算力2数据处理模块A V7-1时钟锁定
                               //bit6:可重构高算力平台1-数据处理模块A-与高算力2数据处理模块A V7-1建链
                               //bit5:可重构高算力平台1-数据处理模块B-与高算力2数据处理模块B V7-1时钟锁定
                               //bit4:可重构高算力平台1-数据处理模块B-与高算力2数据处理模块B V7-1建链
                               //bit3:可重构高算力平台2-数据处理模块A-与高算力1数据处理模块A V7-1时钟锁定
                               //bit2:可重构高算力平台2-数据处理模块A-与高算力1数据处理模块A V7-1建链
                               //bit1:可重构高算力平台2-数据处理模块B-与高算力1数据处理模块B V7-1时钟锁定
                               //bit0:可重构高算力平台2-数据处理模块B-与高算力1数据处理模块B V7-1建链

};

// 版本-代号、普通状态量(4s)
struct slow_Group_3 {
    // 第三组遥测

    ushort pack_head_3;    // 第三组版本号，包标志0x0732;
    ushort pack_number_3;  // 第三组包顺序控制
    ushort pack_Len_3;     // 第三组包长度

    uchar gsl1_JKV2;  // bit7-bit5可重构高算力平台1-接口控制模块-V2大版本号
    // bit4-bit0可重构高算力平台1-接口控制模块-V2小版本号

    uchar gsl1_JKV7;  // bit7-bit5可重构高算力平台1-接口控制模块-V7大版本号
    // bit4-bit0可重构高算力平台1-接口控制模块-V7小版本号

    uchar gsl1_JKDSP6701;  // bit7-bit5可重构高算力平台1-接口控制模块-DSP6701大版本号
    // bit4-bit0可重构高算力平台1-接口控制模块-DSP6701小版本号

    uchar gsl1_JKDSP6678;  // bit7-bit5可重构高算力平台1-接口控制模块-DSP6678大版本号
    // bit4-bit0可重构高算力平台1-接口控制模块-DSP6678小版本号

    uchar gsl1_SFK7;  // bit7-bit5可重构高算力平台1-收发处理模块-K7大版本号
    // bit4-bit0可重构高算力平台1-收发处理模块-K7小版本号

    uchar gsl1_SFV7_1;  // bit7-bit5可重构高算力平台1-收发处理模块-V7-1大版本号
    // bit4-bit0可重构高算力平台1-收发处理模块-V7-1小版本号

    ushort gsl1_SFV7_1soft;  // 可重构高算力平台1-收发处理模块-V7-1软件代号

    uchar gsl1_SFV7_2;  // bit7-bit5可重构高算力平台1-收发处理模块-V7-2大版本号
    // bit4-bit0可重构高算力平台1-收发处理模块-V7-2小版本号

    ushort gsl1_SFV7_2soft;  // 可重构高算力平台1-收发处理模块-V7-2软件代号


    uchar gsl1_SFK7_sum;  // 可重构高算力平台1-收发处理模块-K7预加载软件数量(4.22新增1字节)

    uchar gsl1_SJAK7;  // bit7-bit5可重构高算力平台1-数据处理模块A-K7大版本号
                        // bit4-bit0可重构高算力平台1-数据处理模块A-K7大版本号

    uchar gsl1_SJAV7_1;  // bit7-bit5可重构高算力平台1-数据处理模块A-V7-1大版本号
    // bit4-bit0可重构高算力平台1-数据处理模块A-V7-1大版本号

    ushort gsl1_SJAV7_1soft;  // 可重构高算力平台1-数据处理模块A-V7-1软件代号

    uchar gsl1_SJAV7_2;  // bit7-bit5可重构高算力平台1-数据处理模块A-V7-2大版本号
    // bit4-bit0可重构高算力平台1-数据处理模块A-V7-2大版本号

    ushort gsl1_SJAV7_2soft;  // 可重构高算力平台1-数据处理模块A-V7-2软件代号

    uchar gsl1_SJADSP6678;  // bit7-bit5可重构高算力平台1-数据处理模块A-DSP6678大版本号
    // bit4-bit0可重构高算力平台1-数据处理模块A-DSP6678大版本号

    ushort gsl1_SJADSP6678soft;  // 可重构高算力平台1-数据处理模块A-DSP6678软件代号

    uchar gsl1_CLAK7_sum;  //可重构高算力平台1-数据处理模块A-K7预加载软件数量(4.22新增1字节)

    uchar gsl1_SJBK7;  // bit7-bit5可重构高算力平台1-数据处理模块B-K7大版本号
    // bit4-bit0可重构高算力平台1-数据处理模块B-K7大版本号

    uchar gsl1_SJBV7_1;  // bit7-bit5可重构高算力平台1-数据处理模块B-V7-1大版本号
    // bit4-bit0可重构高算力平台1-数据处理模块B-V7-1大版本号

    ushort gsl1_SJBV7_1soft;  // 可重构高算力平台1-数据处理模块B-V7-1软件代号

    uchar gsl1_SJBV7_2;  // bit7-bit5可重构高算力平台1-数据处理模块B-V7-2大版本号
    // bit4-bit0可重构高算力平台1-数据处理模块B-V7-2大版本号

    ushort gsl1_SJBV7_2soft;  // 可重构高算力平台1-数据处理模块B-V7-2软件代号

    uchar gsl1_SJBDSP6678;  // bit7-bit5可重构高算力平台1-数据处理模块B-DSP6678大版本号
    // bit4-bit0可重构高算力平台1-数据处理模块B-DSP6678大版本号

    ushort gsl1_SJBDSP6678soft;  // 可重构高算力平台1-数据处理模块B-DSP6678软件代号

    uchar gsl1_CLBK7_sum;  //可重构高算力平台1-数据处理模块B-K7预加载软件数量(4.22新增1字节)


    uchar sorft1_guiding;  //bit7
    //bit6 可重构高算力平台1-接口V7三模运维状态
    //bit5,可重构高算力平台1-软件引导方式-接口控制模块Can解析与重构调度软件
    //bit4,可重构高算力平台1-软件引导方式-接口控制模块综合调度软件
    //bit3,可重构高算力平台1-软件引导方式-数据处理模块A接口控制软件
    //bit2,可重构高算力平台1-软件引导方式-数据处理模块B接口控制软件
    //bit1,可重构高算力平台1-软件引导方式-收发处理模块接口控制软件
    //bit0,可重构高算力平台1-软件引导方式-接口控制模块数据传输软件



    uchar gsl2_JKV2;  // bit7-bit5可重构高算力平台2-接口控制模块-V2大版本号
    // bit4-bit0可重构高算力平台2-接口控制模块-V2小版本号

    uchar gsl2_JKV7;  // bit7-bit5可重构高算力平台2-接口控制模块-V7大版本号
    // bit4-bit0可重构高算力平台2-接口控制模块-V7小版本号

    uchar gsl2_JKDSP6701;  // bit7-bit5可重构高算力平台2-接口控制模块-DSP6701大版本号
    // bit4-bit0可重构高算力平台2-接口控制模块-DSP6701小版本号

    uchar gsl2_JKDSP6678;  // bit7-bit5可重构高算力平台2-接口控制模块-DSP6678大版本号
    // bit4-bit0可重构高算力平台2-接口控制模块-DSP6678小版本号

    uchar gsl2_SFK7;  // bit7-bit5可重构高算力平台2-收发处理模块-K7大版本号
    // bit4-bit0可重构高算力平台2-收发处理模块-K7小版本号

    uchar gsl2_SFV7_1;  // bit7-bit5可重构高算力平台2-收发处理模块-V7-1大版本号
    // bit4-bit0可重构高算力平台2-收发处理模块-V7-1小版本号

    ushort gsl2_SFV7_1soft;  // 可重构高算力平台2-收发处理模块-V7-1软件代号

    uchar gsl2_SFV7_2;  // bit7-bit5可重构高算力平台2-收发处理模块-V7-2大版本号
    // bit4-bit0可重构高算力平台2-收发处理模块-V7-2小版本号

    ushort gsl2_SFV7_2soft;  // 可重构高算力平台2-收发处理模块-V7-2软件代号

    uchar gsl2_SFK7_sum;  //可重构高算力平台2-收发处理模块-K7预加载软件数量(4.22新增1字节)

    uchar gsl2_SJAK7;  // bit7-bit5可重构高算力平台2-数据处理模块A-K7大版本号
    // bit4-bit0可重构高算力平台2-数据处理模块A-K7大版本号

    uchar gsl2_SJAV7_1;  // bit7-bit5可重构高算力平台2-数据处理模块A-V7-1大版本号
    // bit4-bit0可重构高算力平台2-数据处理模块A-V7-1大版本号

    ushort gsl2_SJAV7_1soft;  // 可重构高算力平台2-数据处理模块A-V7-1软件代号

    uchar gsl2_SJAV7_2;  // bit7-bit5可重构高算力平台2-数据处理模块A-V7-2大版本号
    // bit4-bit0可重构高算力平台2-数据处理模块A-V7-2大版本号

    ushort gsl2_SJAV7_2soft;  // 可重构高算力平台2-数据处理模块A-V7-2软件代号

    uchar gsl2_SJADSP6678;  // bit7-bit5可重构高算力平台2-数据处理模块A-DSP6678大版本号
    // bit4-bit0可重构高算力平台2-数据处理模块A-DSP6678大版本号

    ushort gsl2_SJADSP6678soft;  // 可重构高算力平台2-数据处理模块A-DSP6678软件代号

    uchar gsl2_CLAK7_sum;  //可重构高算力平台2-数据处理模块A-K7预加载软件数量(4.22新增1字节)

    uchar gsl2_SJBK7;  // bit7-bit5可重构高算力平台2-数据处理模块B-K7大版本号
    // bit4-bit0可重构高算力平台2-数据处理模块B-K7大版本号

    uchar gsl2_SJBV7_1;  // bit7-bit5可重构高算力平台2-数据处理模块B-V7-1大版本号
    // bit4-bit0可重构高算力平台2-数据处理模块B-V7-1大版本号

    ushort gsl2_SJBV7_1soft;  // 可重构高算力平台2-数据处理模块B-V7-1软件代号

    uchar gsl2_SJBV7_2;  // bit7-bit5可重构高算力平台2-数据处理模块B-V7-2大版本号
    // bit4-bit0可重构高算力平台2-数据处理模块B-V7-2大版本号

    ushort gsl2_SJBV7_2soft;  // 可重构高算力平台2-数据处理模块B-V7-2软件代号

    uchar gsl2_SJBDSP6678;  // bit7-bit5可重构高算力平台2-数据处理模块B-DSP6678大版本号
    // bit4-bit0可重构高算力平台2-数据处理模块B-DSP6678大版本号

    ushort gsl2_SJBDSP6678soft;  // 可重构高算力平台2-数据处理模块B-DSP6678软件代号

    uchar gsl2_CLBK7_sum;  //可重构高算力平台2-数据处理模块B-K7预加载软件数量(4.22新增1字节)


    uchar sorft2_guiding;//bit7
    //bit6 可重构高算力平台2-接口V7三模运维状态
    //bit5,可重构高算力平台2-软件引导方式-接口控制模块Can解析与重构调度软件
    //bit4,可重构高算力平台2-软件引导方式-接口控制模块综合调度软件
    //bit3,可重构高算力平台2-软件引导方式-数据处理模块A接口控制软件
    //bit2,可重构高算力平台2-软件引导方式-数据处理模块B接口控制软件
    //bit1,可重构高算力平台2-软件引导方式-收发处理模块接口控制软件
    //bit0,可重构高算力平台2-软件引导方式-接口控制模块数据传输软件

    uchar ZH_GKP2020;  // bit7-bit5综合管控单元-管控模块-P2020大版本号
    // bit4-bit0综合管控单元-管控模块-P2020小版本号

    uchar ZH_GKV7;  // bit7-bit5综合管控单元-管控模块-V7大版本号
    // bit4-bit0综合管控单元-管控模块-V7小版本号

    uchar ZH_ZHV7;  // bit7-bit5综合管控单元-综合处理模块-V7大版本号
    // bit4-bit0综合管控单元-综合处理模块-V7小版本号

    uchar ZH_ZHDSP6678_1;  // bit7-bit5综合管控单元-综合处理模块-DSP6678_1大版本号
    // bit4-bit0综合管控单元-综合处理模块-DSP6678_1小版本号

    uchar ZH_ZHDSP6678_2;  // bit7-bit5综合管控单元-综合处理模块-DSP6678_2大版本号
    // bit4-bit0综合管控单元-综合处理模块-DSP6678_2小版本号

    uchar ZH_ZHDSP6678_3;  // bit7-bit5综合管控单元-综合处理模块-DSP6678_3大版本号
    // bit4-bit0综合管控单元-综合处理模块-DSP6678_3小版本号

    uchar ZH_ZHai;  // bit7-bit5综合管控单元-综合处理模块-AI大版本号
    // bit4-bit0综合管控单元-综合处理模块-AI小版本号

    uchar ZH_GKsatetrack;  // bit7-bit4综合管控单元-卫星编号
    // bit3-bit0综合管控单元-轨道编号

    uchar ZH_GKV2;  // bit7-bit6综合管控单元-管控模块-V2看门狗使能
    // bit5-bit4综合管控单元-主副卫星
    // bit3-bit2综合管控单元-CAN应用通道
    // bit1-bit0综合管控单元-千兆网应用通道

    uchar ZH_AreaClear;  // bit7-bit4保留
    // bit3-bit2综合管控单元-任务自动清除使能
    // bit1-bit0综合管控单元-区域或常规任务状态选择

    uchar ZH_templates_number;      // 综合管控单元-模板数量
    ushort ZH_SSD;                  // 综合管控单元-SSD存储余量

    //后面都改动
    uchar ZH_gsl12_receiverup;  // bit7 保留
                                //bit6--综合管控单元-管控Flash软刷周期使能
                                //bit5-综合管控单元-可重构高算力平台1-接收机自动增益控制状态
                                // bit4-综合管控单元-可重构高算力平台2-接收机自动增益控制状态
                                // bit3-综合管控单元-可重构高算力平台1-接口板V7软件维护状态
                                // bit2-综合管控单元-可重构高算力平台2-接口板V7软件维护状态
                                // bit1-综合管控单元-V7刷新芯片控制标志
                                // bit0-综合管控单元-温度保护关断功能使能标志

    //  uchar ZH_WDenable;  // bit7-bit1保留(5.22去除)
    //                      // bit0综合管控单元-温度保护关断功能使能标志

    uchar ZH_antennatime;       // (保留)综合管控单元-天线控制时间间隔
    uint ZH_GKptsendnumber;  // 综合管控单元-管控模块向平台发送数据计数
    ushort ZH_GKlyrecvnumber;  // 综合管控单元-管控模块接收路由数据计数
    ushort ZH_GKlysendnumber;  // 综合管控单元-管控模块向路由发送数据计数

    uchar ZH_1553cbh_cnt;    //综合管控单元-1553B长抱环计数(4.22新增1字节)
    uchar ZH_1553sys_cnt;    //综合管控单元-1553B系统同步计数(4.22新增1字节)

    uchar ZH_GKoffnumber;    // 综合管控单元-管控机关机准备次数
    uchar XKoffnumber;       // 综合管控单元-下控单机关机准备次数

    //5.22新增4字节
    uchar signal_1; //bit7-bit6:万兆网路由连接状态主/备，各1个Bit，1连接，0未连接
                    //bit5综合管控单元-管控模块V7与P2020互联的SRIOx1链接初始化信号
                    //bit4综合管控单元-管控模块V7与P2020互联的SRIOx1端口初始化信号
                    //bit3综合管控单元-管控模块V7与高算力备份互联的SRIOx2链接初始化信号
                    //bit2综合管控单元-管控模块V7与高算力备份互联的SRIOx2端口初始化信号
                    //bit1综合管控单元-管控模块V7与高算力主份互联的SRIOx2链接初始化信号
                    //bit0综合管控单元-管控模块V7与高算力主份互联的SRIOx2端口初始化信号
    uchar signal_2;//bit7综合管控单元-处理模块V7与810A互联SRIOx4链接初始化信号
    //bit6综合管控单元-处理模块V7与810A互联SRIOx4端口初始化信号
    //bit5综合管控单元-处理模块V7与DSP0互联SRIOx4链接初始化信号
    //bit4综合管控单元-处理模块V7与DSP0互联SRIOx4端口初始化信号
    //bit3综合管控单元-处理模块V7与DSP1互联SRIOx4链接初始化信号
    //bit2综合管控单元-处理模块V7与DSP1互联SRIOx4端口初始化信号
    //bit1综合管控单元-处理模块V7与DSP2互联SRIOx4链接初始化信号
    //bit0综合管控单元-处理模块V7与DSP2互联SRIOx4端口初始化信号
    uchar signal_3;//bit7综合管控单元-管控模块V7与处理模块V7互联第0路SRIOx4链接初始化信号
    //bit6综合管控单元-管控模块V7与处理模块V7互联第0路SRIOx4端口初始化信号
    //bit5综合管控单元-综合管控模块V7与综合处理模块V7互联第1路SRIOx4链接初始化信号
    //bit4综合管控单元-综合管控模块V7与综合处理模块V7互联第1路SRIOx4端口初始化信号
    //bit3综合管控单元-综合处理模块V7与综合管控模块V7互联第0路SRIOx4链接初始化信号
    //bit2综合管控单元-综合处理模块V7与综合管控模块V7互联第0路SRIOx4端口初始化信号
    //bit1综合管控单元-综合处理模块V7与综合管控模块V7互联第1路SRIOx4链接初始化信号
    //bit0综合管控单元-综合处理模块V7与综合管控模块V7互联第1路SRIOx4端口初始化信号

    uchar guiding_main1;    //bit7-V7万兆网与存储连接状态 主/备
                            //bit6保留
                            //bit5-4综合管控单元-P2020软件引导方式
                            //bit3-2综合管控单元-综合管控模块-V7软件引导方式
                            //bit1-0综合管控单元-综合处理模块-V7软件引导方式

    uchar guiding_main2;  //bit7-6综合管控单元-综合处理模块-DSP6678_1软件引导方式
                        //bit5-4综合管控单元-综合处理模块-DSP6678_2软件引导方式
                        //bit3-2综合管控单元-综合处理模块-DSP6678_3软件引导方式
                        //bit1-0综合管控单元-综合处理模块-AI软件引导方式

    uchar guiding_main3;//bit7-4保留
    //bit3综合管控单元-综合处理模块-DSP6678_1启动状态
    //bit2综合管控单元-综合处理模块-DSP6678_2启动状态
    //bit1综合管控单元-综合处理模块-DSP6678_3启动状态
    //bit0综合管控单元-综合处理模块-AI启动状态

    uchar SRIO_number;      // 综合管控单元-SRIO接收异常帧次数
    uchar ALLnumber;        // 综合管控单元-累计已运行任务总数
    uint zhMake_time;       // 综合管控单元-即将执行的任务时间

    //新加
    uchar SAR_code;         //SAR成像-串注间接指令码特征码
    uchar SAR_mode;         //bit7-bit6:保留
                            //bit5-bit4:SAR成像-导航闭锁信号
                            //bit3-bit0:SAR-任务模式

    uchar SAR_LManer;        //bit6:SAR-L频段天线波控加载方式-子阵1-子板1
                            //bit6:SAR-L频段天线波控加载方式-子阵1-子板2
                            //bit5:SAR-L频段天线波控加载方式-子阵2-子板1
                            //bit4:SAR-L频段天线波控加载方式-子阵2-子板2
                            //bit3:SAR-L频段天线波控加载方式-子阵3-子板1
                            //bit2:SAR-L频段天线波控加载方式-子阵3-子板2
                            //bit1:SAR-L频段天线波控加载方式-子阵4-子板1
                            //bit0:SAR-L频段天线波控加载方式-子阵4-子板2

    uchar gsl1_Av7;     //bit7-bit4:可重构高算力平台1-数据处理模块A-FPGAV7-1任务状态
                        //bit3-bt0:可重构高算力平台1-数据处理模块A-FPGAV7-2任务状态
    uchar gsl1_Bv7;     //bit7-bit4可重构高算力平台1-数据处理模块B-FPGAV7-1任务状态
                        //bit3-bt0:可重构高算力平台1-数据处理模块B-FPGAV7-2任务状态
    uchar gsl2_Av7;     //bit7-bit4可重构高算力平台2-数据处理模块A-FPGAV7-1任务状态
                        //bit3-bt0:可重构高算力平台2-数据处理模块A-FPGAV7-2任务状态
    uchar gsl2_Bv7;     //bit7-bit4可重构高算力平台2-数据处理模块B-FPGAV7-1任务状态
                        //bit3-bt0:可重构高算力平台2-数据处理模块B-FPGAV7-2任务状态


    uchar bl[6];             //保留6字节
};

// 不同类型遥测量 公共头，相同部分(27字节)
struct slow_Group_4_Head {
    // 第四组遥测

    ushort last_number;     //综合管控单元-上次执行任务的流水号
    ushort gsl1_lastID1;    //综合管控单元-可重构高算力平台1-上次处理FPGA1执行的主任务I
    ushort gsl1_lastID2;    //综合管控单元-可重构高算力平台1-上次处理FPGA2执行的主任务I
    ushort gsl1_lastID3;    //综合管控单元-可重构高算力平台1-上次处理FPGA3执行的主任务I
    ushort gsl1_lastID4;    //综合管控单元-可重构高算力平台1-上次处理FPGA4执行的主任务I
    ushort gsl2_lastID1;    //综合管控单元-可重构高算力平台2-上次处理FPGA1执行的主任务I
    ushort gsl2_lastID2;    //综合管控单元-可重构高算力平台2-上次处理FPGA2执行的主任务I
    ushort gsl2_lastID3;    //综合管控单元-可重构高算力平台2-上次处理FPGA3执行的主任务I
    ushort gsl2_lastID4;    //综合管控单元-可重构高算力平台2-上次处理FPGA4执行的主任务I
    uint start_time;        //综合管控单元-上次执行任务的实际起始时间
    uint end_time;          //综合管控单元-上次执行任务的实际终止时间
    uchar gk_lastMask;       //bit7-bit2,综合管控单元-保留
                            //bit1,综合管控单元-上一个任务任务强制终止标志
                            //bit0,综合管控单元-上个任务异常结束标志


};

// 慢速遥测结构体（512字节）
struct slow_YCdata {
    // 主头（6字节）
    ushort Pack_Head;    // 主头版本号，包标志0x0731;
    ushort Pack_Number;  // 主头包顺序控制
    ushort Pack_Len;     // 主头包长度

    slow_Group_1 group1;  // 第一组遥测（128字节）

    slow_Group_2 group2;  // 第二组遥测（128字节）

    slow_Group_3 group3;  // 第三组遥测（128字节）


    ushort pack_head_4;    // 第四组版本号，包标志0x0735;
    ushort pack_number_4;  // 第四组包顺序控制
    ushort pack_Len_4;     // 第四组包长度
    uchar group4[116];  // 第四组遥测（122字节）

};

// 不同类型遥测量 电子侦察任务包(2s)包标志0x0735;
struct slow_Group_4_ElecZZ {

    slow_Group_4_Head g4_Head;  //公共头，相同部分(27字节)


    uchar gsl1_AV71Mode;        //可重构高算力平台1-数据处理模块A-V7-1运行模式
    uchar gsl1_AV71Stas;        //可重构高算力平台1-数据处理模块A-V7-1运行状态
    uchar gsl1_AV72Mode;        //可重构高算力平台1-数据处理模块A-V7-2运行模式
    uchar gsl1_AV72Stas;        //可重构高算力平台1-数据处理模块A-V7-2运行状态
    uchar gsl1_BV71Mode;        //可重构高算力平台1-数据处理模块B-V7-1运行模式
    uchar gsl1_BV71Stas;        //可重构高算力平台1-数据处理模块B-V7-1运行状态
    uchar gsl1_BV72Mode;        //可重构高算力平台1-数据处理模块B-V7-2运行模式
    uchar gsl1_BV72Stas;        //可重构高算力平台1-数据处理模块B-V7-2运行状态
    uchar gsl2_AV71Mode;        //可重构高算力平台2-数据处理模块A-V7-1运行模式
    uchar gsl2_AV71Stas;        //可重构高算力平台2-数据处理模块A-V7-1运行状态
    uchar gsl2_AV72Mode;        //可重构高算力平台2-数据处理模块A-V7-2运行模式
    uchar gsl2_AV72Stas;        //可重构高算力平台2-数据处理模块A-V7-2运行状态
    uchar gsl2_BV71Mode;        //可重构高算力平台2-数据处理模块B-V7-1运行模式
    uchar gsl2_BV71Stas;        //可重构高算力平台2-数据处理模块B-V7-1运行状态
    uchar gsl2_BV72Mode;        //可重构高算力平台2-数据处理模块B-V7-2运行模式
    uchar gsl2_BV72Stas;        //可重构高算力平台2-数据处理模块B-V7-2运行状态


};


// 不同类型遥测量 电子干扰任务包(2s)包标志0x0736;
struct slow_Group_4_ElecGR {

    slow_Group_4_Head g4_Head;  //公共头，相同部分(27字节)

};

// 不同类型遥测量 SAR成像任务包(2s)包标志0x0737;
struct slow_Group_4_SAR {

    slow_Group_4_Head g4_Head;  //公共头，相同部分(27字节)


    uchar imaging_mode;         //bit7,SAR成像-成像模式字-极化方式
                                //bit6-5,SAR成像-通道模式
                                //bit4,SAR成像-保留
                                //bit3-0,SAR成像-成像模式
    ushort order_len;           //SAR成像-指令队列长度
    ushort open_time;           //SAR成像-SAR开机时间

    uchar curr_timeT5;          //SAR成像-本地时间码T5
    uchar curr_timeT4;          //SAR成像-本地时间码T4
    uchar curr_timeT3;          //SAR成像-本地时间码T3
    uchar curr_timeT2;          //SAR成像-本地时间码T2
    uchar sar_pack;             //bit7-bit3,保留
                                //bit2,SAR成像-包格式
                                //bit1-0,SAR成像-任务类型

    ushort stream_number;       //SAR成像-流水号
    ushort task_mainnumber;     //SAR成像-任务号 高字节
                                //SAR成像-任务号 低字节
    ushort task_subnumber;      //SAR成像-子任务号 高字节
                                //SAR成像-子任务号 低字节
    uchar sar_amendment;        //bit7,SAR成像-聚束中心时刻星上修正控制
                                //bit6,保留
                                //bit5-0,SAR成像-子带个数
    uchar start_err1;           //SAR成像-星上参数计算结果错误状态1
    uchar start_err2;           //SAR成像-星上参数计算结果错误状态2
    uchar sar_taskSum;          //SAR成像-当前待执行成像任务数


    //24.10.12新增
    uchar V7_1inSignal;     //bit7-4保留
                            //bit3可重构高算力平台1-收发处理模块-V7-1数据形成-采集输入输出信号遥测-采集回波数据标志
                            //bit2可重构高算力平台1-收发处理模块-V7-1数据形成-采集输入输出信号遥测-辅助数据接收标志
                            //bit1可重构高算力平台1-收发处理模块-V7-1数据形成-采集输入输出信号遥测-数传数据输出标志
                            //bit0可重构高算力平台1-收发处理模块-V7-1数据形成-采集输入输出信号遥测-PRF接收标志

    uchar V7_1inJz;         //bit7-2可重构高算力平台1-收发处理模块-V7-1数据形成-校正流程遥测-AD数据选择
                            //bit1可重构高算力平台1-收发处理模块-V7-1数据形成-校正流程遥测-校正流程开始标志
                            //bit0可重构高算力平台1-收发处理模块-V7-1数据形成-校正流程遥测-校正流程完成标志

    uchar V7_1inJzAD;       //bit7-1保留
                            //bit0可重构高算力平台1-收发处理模块-V7-1数据形成-校正完成遥测-AD同步流程

    uchar V7_2inJzSignal;   //bit7-bit3保留
                            //bit2可重构高算力平台1-收发处理模块-V7-2调频源-采集输入输出信号遥测-控制码接收标志
                            //bit1可重构高算力平台1-收发处理模块-V7-2调频源-采集输入输出信号遥测-DAC数据输出标志
                            //bit0可重构高算力平台1-收发处理模块-V7-2调频源-采集输入输出信号遥测-PRF接收标志

    uchar V7_2inJz;         //bit7-bit5保留
                            //bit4-1可重构高算力平台1-收发处理模块-V7-2调频源-校正流程遥测-射频选择
                            //bit0可重构高算力平台1-收发处理模块-V7-2调频源-校正流程遥测-数据可以开始输出标志

    uchar V7_2jz;           //保留
                            //bit5-3可重构高算力平台1-收发处理模块-V7-2调频源-校正完成遥测-校准数据源选择
                            //bit2-0可重构高算力平台1-收发处理模块-V7-2调频源-校正完成遥测-数据输出选择控制码

    uchar A_V71mark;        //bit7 可重构高算力平台1-数据处理模块A-V7-1探测成像预处理-探测成像节点完成标志1-当前程序处理节点8完成标志
                            //bit6 可重构高算力平台1-数据处理模块A-V7-1探测成像预处理-探测成像节点完成标志1-当前程序处理节点7完成标志
                            //bit5 可重构高算力平台1-数据处理模块A-V7-1探测成像预处理-探测成像节点完成标志1-当前程序处理节点6完成标志
                            //bit4 可重构高算力平台1-数据处理模块A-V7-1探测成像预处理-探测成像节点完成标志1-当前程序处理节点5完成标志
                            //bit3 可重构高算力平台1-数据处理模块A-V7-1探测成像预处理-探测成像节点完成标志1-当前程序处理节点4完成标志
                            //bit2 可重构高算力平台1-数据处理模块A-V7-1探测成像预处理-探测成像节点完成标志1-当前程序处理节点3完成标志
                            //bit1 可重构高算力平台1-数据处理模块A-V7-1探测成像预处理-探测成像节点完成标志1-当前程序处理节点2完成标志
                            //bit0 可重构高算力平台1-数据处理模块A-V7-1探测成像预处理-探测成像节点完成标志1-当前程序处理节点1完成标志

    uchar A_V72mark;        //bit7 可重构高算力平台1-数据处理模块A-V7-2探测成像方位向处理-探测成像节点完成标志2-当前程序处理节点8完成标志
                            //bit6 可重构高算力平台1-数据处理模块A-V7-2探测成像方位向处理-探测成像节点完成标志2-当前程序处理节点7完成标志
                            //bit5 可重构高算力平台1-数据处理模块A-V7-2探测成像方位向处理-探测成像节点完成标志2-当前程序处理节点6完成标志
                            //bit4 可重构高算力平台1-数据处理模块A-V7-2探测成像方位向处理-探测成像节点完成标志2-当前程序处理节点5完成标志
                            //bit3 可重构高算力平台1-数据处理模块A-V7-2探测成像方位向处理-探测成像节点完成标志2-当前程序处理节点4完成标志
                            //bit2 可重构高算力平台1-数据处理模块A-V7-2探测成像方位向处理-探测成像节点完成标志2-当前程序处理节点3完成标志
                            //bit1 可重构高算力平台1-数据处理模块A-V7-2探测成像方位向处理-探测成像节点完成标志2-当前程序处理节点2完成标志
                            //bit0 可重构高算力平台1-数据处理模块A-V7-2探测成像方位向处理-探测成像节点完成标志2-当前程序处理节点1完成标志

    ushort B_V72gyssWide;   //可重构高算力平台1-数据处理模块B-V7-2广域搜索模式舰船检测-灰度图宽度
    ushort B_V72gysshigh;   //可重构高算力平台1-数据处理模块B-V7-2广域搜索模式舰船检测-灰度图高度

    uchar B_V7cllc;         //bit7-4 保留
                            //bit3 可重构高算力平台1-数据处理模块B-V7-2广域搜索模式舰船检测-处理流程开始标志-接收数据开始标志
                            //bit2 可重构高算力平台1-数据处理模块B-V7-2广域搜索模式舰船检测-处理流程开始标志-接收数据结束标志
                            //bit1 可重构高算力平台1-数据处理模块B-V7-2广域搜索模式舰船检测-处理流程开始标志-发送数据开始标志
                            //bit0 可重构高算力平台1-数据处理模块B-V7-2广域搜索模式舰船检测-处理流程开始标志-发送数据结束标志

    uint B_V72Re_cnt;       //可重构高算力平台1-数据处理模块B-V7-2广域搜索模式舰船检测-接收数据时钟数计数
    uint B_V72Se_cnt;       //可重构高算力平台1-数据处理模块B-V7-2广域搜索模式舰船检测-发送数据时钟数计数

    uchar B_V72_CFAR;       //可重构高算力平台1-数据处理模块B-V7-2广域搜索模式舰船检测-CFAR处理步骤
    ushort B_V72_jcmb;      //可重构高算力平台1-数据处理模块B-V7-2广域搜索模式舰船检测-检测目标数


    uchar B_V71_net;        //可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-网络运行层数

    uchar B_V71_clbz1;      //bit7 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志1-目标处理开始标志
                            //bit6 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志1-切片写入开始标志
                            //bit5 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志1-图像插值开始标志
                            //bit4 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志1-参数写入开始标志
                            //bit3 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志1-参数读取开始标志
                            //bit2 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志1-发送数据开始标志
                            //bit1 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志1-接收数据开始标志
                            //bit0 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志1-网络运行开始标志

    uchar B_V71_clbz2;      //bit7 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志2-网络参数载入开始标志
                            //bit6 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志2-参数包导入开始标志
                            //bit5 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志2-网络计算最大值开始标志
                            //bit4 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志2-网络归一化开始标志
                            //bit3 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志2-全连接层开始标志
                            //bit2 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志2-经纬度计算开始标志
                            //bit1 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志2-经纬度计算参数有效标志
                            //bit0 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志2-参数包导入开始标志

    uchar B_V71_clbz3;      //bit7 保留
                            //bit6 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志3-读取权重结束标志
                            //bit5 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志3-读取权重开始标志
                            //bit4 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志3-网络运行结束响应标志
                            //bit3 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志3-AXI总线复位标志
                            //bit2 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志3-网络计算流程复位标志
                            //bit1 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志3-检测流程复位标志
                            //bit0 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志3-处理全局复位标志

    uchar B_V71_clbz4;      //bit7 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志4-网络参数载入结束标志
                            //bit6 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志4-海陆分割数据发送结束标志
                            //bit5 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志4-图像插值结束标志
                            //bit4 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志4-参数写入结束标志
                            //bit3 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志4-参数读取结束标志
                            //bit2 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志4-发送数据结束标志
                            //bit1 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志4-接收数据结束标志
                            //bit0 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志4-网络运行结束标志

    uchar B_V71_clbz5;      //bit7 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志5-网络参数载入结束标志
                            //bit6 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志5-参数包导入结束标志
                            //bit5 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志5-网络计算最大值结束标志
                            //bit4 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志5-网络归一化结束标志
                            //bit3 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志5-全连接层结束标志
                            //bit2 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志5-经纬度计算结束标志
                            //bit1 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志5-网络数据写入结束标志
                            //bit0 可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理流程标志5-参数包导入结束标志

    ushort B_V71xgcs1;      //可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理相关参数1-检测目标个数
    ushort B_V71xgcs2;      //可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理相关参数2-当前处理检测目标位置
    uchar  B_V71xgcs3;      //可重构高算力平台1-数据处理模块B-V7-1广域搜索模式舰船鉴别-处理状态参数3-舰船处理数据量


    uchar B2_V71_net;       //可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-网络运行层数

    uchar B2_V7_1clbz1;     //bit7 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志1-目标处理开始标志
                            //bit6 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志1-目标判据标志2
                            //bit5 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志1-目标判据标志1
                            //bit4 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志1-参数写入开始标志
                            //bit3 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志1-参数读取开始标志
                            //bit2 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志1-发送数据开始标志
                            //bit1 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志1-接收数据开始标志
                            //bit0 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志1-网络运行开始标志

    uchar B2_V7_1clbz2;     //bit7-6 保留
                            //bit5 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志2-网络参数载入开始标志
                            //bit4 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志2-参数包导入开始标志
                            //bit3 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志2-网络计算最大值开始标志
                            //bit2 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志2-网络归一化开始标志
                            //bit1 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志2-全连接层开始标志
                            //bit0 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志2-参数包导入开始标志

    uchar B2_V7_1clbz3;     //bit7 保留
                            //bit6 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志3-读取权重结束标志
                            //bit5 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志3-读取权重开始标志
                            //bit4 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志3-网络运行结束响应标志
                            //bit3 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志3-AXI总线复位标志
                            //bit2 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志3-网络计算流程复位标志
                            //bit1 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志3-检测流程复位标志
                            //bit0 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志3-处理全局复位标志

    uchar B2_V7_1clbz4;     //bit7-6保留
                            //bit5 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志4-网络参数载入结束标志
                            //bit4 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志4-参数写入结束标志
                            //bit3 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志4-参数读取结束标志
                            //bit2 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志4-发送数据结束标志
                            //bit1 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志4-接收数据结束标志
                            //bit0 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志4-网络运行结束标志

     uchar B2_V7_1clbz5;    //bit7 保留
                            //bit6 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志5-网络参数载入结束标志
                            //bit5 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志5-参数包导入结束标志
                            //bit4 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志5-网络计算最大值结束标志
                            //bit3 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志5-网络归一化结束标志
                            //bit2 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志5-全连接层结束标志
                            //bit1 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志5-网络数据写入结束标志
                            //bit0 可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理流程标志5-参数包导入结束标志

    ushort B2_V71xgcs1;     //可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理相关参数1-检测目标个数
    ushort B2_V71xgcs2;     //可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理相关参数2-当前处理检测目标位置
    uchar  B2_V71xgcs3;     //可重构高算力平台2-数据处理模块B-V7-1广域搜索模式舰船二分类-处理状态参数3-舰船处理状态


};

// 不同类型遥测量 备用导航任务包(2s)包标志0x0738;
struct slow_Group_4_BY {

    slow_Group_4_Head g4_Head;  //公共头，相同部分(27字节)

    uchar sorft_status;     //bit7,DSP  UTC时间状态
                            //bit6,FPGA PPS状态
                            //bit5-4,FPGA DDS信号生成状态
                            //bit3-2,轨道数据接收状态
                            //bit1-0,轨道数据连续性

    uchar sorft_status2;    //bit7-6综合管控单元-保留
                            //bit5-4伪码参数状态
                            //bit3-2星历拟合状态
                            //bit1-0,历书拟合状态
    uchar dsp_errcnt;       //DSP  三模冗余错误计数
    uchar gd_reccnt;        //轨道数据接收成功计数
    ushort xl_err;          //星历拟合误差
    uchar data_down;        //数字功率衰减值
    uint by_time;           //备用导航信号导航时间
};

// 不同类型遥测量 类5G通信任务包(2s)包标志0x0739;
struct slow_Group_4_kind5G {

    slow_Group_4_Head g4_Head;  //公共头，相同部分(27字节)

    int position_orb;            //综合管控单元-5G关口站位置-经度
    int latitude_latitude;       //综合管控单元-5G关口站位置-纬度
    uchar workMode_5G;           //bit7-2,保留
                                //bit1-0,5G工作模式
    uchar register_user;         //注册用户数
    uchar err_rate;              //误块率
    uchar code_maind;            //编码调制样式
    uchar code_rate;             //编码码率

};

// 打包遥测结构体（256字节）
struct Pack_YCdata {
    // 主头
    ushort Pack_Head;    // 主头版本号，包标志0x073E;
    ushort Pack_Number;  // 主头包顺序控制
    ushort Pack_Len;     // 主头包长度

    //内部协议

    //  ushort order_len; //指令长度
    //  uchar answer_mark;//指令应答标识
    //  ushort pack_head; //包头
    //  ushort number_mark;//顺序标识
    //  ushort pack_len;//包长

    uint curr_time;       //本地时间码
    ushort open_time;     //SAR开机时间
    uchar sys_status;     //系统工作状态
    uchar order_cnt;      //收指令计数
    uchar sys_work;       //分系统状态及指令执行情况
    uchar jz_zlcode;      //串注间接指令码
    ushort zl_teamLen;    //指令队列长度

    uchar cx_mode;            //成像模式字
    ushort mask_kind;         //任务类型
    ushort mask_number;       //任务号
    ushort sub_masknum;       //子任务号

    uchar starts_cnt;         //本次成像聚束中心时刻星上计算控制码及子带个数
    uchar ss1;                //实时成像参数1
    uchar ss2;                //实时成像参数2
    uchar EDAC_cnt;           //EDAC错误计数
    uchar CPU_cnt;            //CPU复位计数
    uchar bl[98];             //保留
    uchar pc32_yc[32];        //32路雷达计算机遥测
    uchar bk_yc[96];          //波控遥测
    //ushort crc;             //校验和


};
//c81的CAN遥测多次用到
struct FPGAV7
{
    uchar version;          //    版本号
    //    大版本号
    //    小版本号

    ushort software;        //    软件代号
    ushort Tem;             //    温度
    //    D15-D12	保留
    //    D11-D0	V7温度


    uchar GTX_CL;           //    GTX时钟锁定
    //    D7-D6	保留
    //    D5	收发K7时钟锁定指示
    //    D4	收发V7-2时钟锁定指示
    //    D3	数据处理1 V7-1时钟锁定指示
    //    D2	数据处理1 V7-2时钟锁定指示
    //    D1	数据处理2 V7-1时钟锁定指示
    //    D0	数据处理2 V7-2时钟锁定指示

    uchar GTX_JL;           //    GTX建链
    //    D7-D6	保留
    //    D5	收发K7建链指示
    //    D4	收发V7-2建链指示
    //    D3	数据处理1 V7-1建链指示
    //    D2	数据处理1 V7-2建链指示
    //    D1	数据处理2 V7-1建链指示
    //    D0	数据处理2 V7-2建链指示

    ushort SRIO_CL;         //    保留


    ushort SRIO_JL;        //    	保留



};


struct dataDeal_MK
{
    uchar version_FPGAK7;   //    K7版本号
    //    D7-D5	大版本号
    //    D4-D0	小版本号


    uchar softwareLoad_;    //    软件加载状态
    //    D7-D4	保留
    //    D3	DSP6678心跳
    //    D2	DSP6678加载状态
    //    D1	FPGAV7-1加载状态
    //    D0	FPGAV7-2加载状态


    uchar GTX_CL;           //    GTX时钟锁定
    //    D7-D4 软件预加载数量高4位
    //    D3	保留
    //    D2	数据处理1 V7-1时钟锁定
    //    D1	数据处理1 V7-2时钟锁定
    //    D0	接口控制 V7时钟锁定

    uchar GTX_JL;           //    GTX建链
    //    D7-D4 软件预加载数量低4位
    //    D3	保留
    //    D2	数据处理1 V7-1建链
    //    D1	数据处理1 V7-2建链
    //    D0	接口控制 V7建链

    uchar DSP_Source;       //    DSP、光模块电源
    //    D7-D6	保留
    //    D5	光模块(PG_FIB3V3)
    //    D4	DSP电源(PG_DSPVTT)
    //    D3	DSP电源(PG_DSP1V8)
    //    D2	DSP电源(PG_DSP1V5)
    //    D1	DSP电源(PG_DSP1V0_SMART)
    //    D0	DSP电源(PG_DSP1V0)
    FPGAV7 Fpgav7[2];       //FPGAV7-1、2

    uchar versionDSP6678;   //版本号
    //    D7-D5	大版本号
    //    D4-D0	小版本号
    ushort softwareNumber;  //软件代号

};


//CAN轮询遥测C81------292字节结构体
struct  YCLX_C81
{

    uchar softwareVersion;      //    软件版本号
    //D7-D5	大版本号
    //D4-D0	小版本号


    uchar MKlightpower;         //模块供电指示
    /*bit7-bit6保留
                                 bit5-可重构高算力平台2-接口控制模块-光模块供电指示(FIBER_3V3_PG)
                                 bit4-可重构高算力平台2-接口控制模块-DSP供电指示(PG_DSPVTT)
                                 bit3-可重构高算力平台2-接口控制模块-DSP供电指示(PG_DSP1V8)
                                 bit2-可重构高算力平台2-接口控制模块-DSP供电指示(PG_DSP1V5)
                                 bit1-可重构高算力平台2-接口控制模块-DSP供电指示(PG_DSP1V0_SMART)
                                 bit0-可重构高算力平台2-接口控制模块-DSP供电指示(PG_DSP1V0)*/
    uchar   JKlock;             //栓锁、锁相环锁指示
    /*// bit7-保留
                                // bit6-可重构高算力平台2-接口控制模块-模块栓锁
                                // bit5-可重构高算力平台2-接口控制模块-收发处理模块栓锁(收发LRM_PG1)
                                // bit4-可重构高算力平台2-接口控制模块-数据处理1模块栓锁(数据1LRM_PG2)
                                // bit3-可重构高算力平台2-接口控制模块-数据处理2模块栓锁(数据2LRM_PG3)
                                // bit2-可重构高算力平台2-接口控制模块-锁相环(V2_LD1)
                                // bit1-可重构高算力平台2-接口控制模块-锁相环(V2_LD2)
                                // bit0-可重构高算力平台2-接口控制模块-锁相环(V2_LD3)*/

    uchar  appLoadDone;         //    程序加载DONE指令
    //D7-D6	保留
    //D5	接口控制 DSP6701加载状态
    //D4	接口控制 DSP6678加载状态
    //D3	接口控制 V7加载状态
    //D2	收发处理 K7加载状态
    //D1	数据处理1 K7加载状态
    //D0	数据处理2 K7加载状态*/


    uchar Version_FPGAV7;        //    版本号

    ushort softwareNumber;      //    软件代号
    ushort  Temperature;        //    温度
    //    D15	DSP6678心跳
    //    D14-D12	保留
    //    D11-D0	V7温度

    uchar GTX_UDP_ClockLock;    //    GTX/UDP时钟锁定
    //    D7	主份udp时钟锁定指示
    //    D6	备份udp时钟锁定指示
    //    D5-D3	保留
    //    D2	收发处理  K7时钟锁定指示
    //    D1	数据处理1 K7时钟锁定指示
    //    D0	数据处理2 K7时钟锁定指示

    uchar JLZS_GTX_UDP ;        //    GTX/UDP建链指示
    //    D7	主份udp建链指示
    //    D6	备份udp建链指示
    //    D5-D3	保留
    //    D2	收发处理  K7建链指示
    //    D1	数据处理1 K7建链指示
    //    D0	数据处理2 K7建链指示

    ushort SRIO_ClockLockFlag;   //    SRIO时钟锁定指示
    //    D7	管控模块 V7备份时钟锁定指示
    //    D6	接口控制 DSP6678时钟锁定指示
    //    D5	数据处理1 V7-1时钟锁定指示
    //    D4	数据处理1 V7-2时钟锁定指示
    //    D3	数据处理1 DSP6678时钟锁定指示
    //    D2	数据处理2 V7-1时钟锁定指示
    //    D1	数据处理2 V7-2时钟锁定指示
    //    D0	数据处理2 DSP6678时钟锁定指示
    //    D7-D1	保留
    //    D0	管控模块 V7主份时钟锁定指示


    ushort JLZS_SRIO;            //    SRIO建链指示

    //    D7	管控模块 V7备份建链指示
    //    D6	接口控制 DSP6678建链指示
    //    D5	数据处理1 V7-1建链指示
    //    D4	数据处理1 V7-2建链指示
    //    D3	数据处理1 DSP6678建链指示
    //    D2	数据处理2 V7-1建链指示
    //    D1	数据处理2 V7-2建链指示
    //    D0	数据处理2 DSP6678建链指示

    //    D7	管控机主备
    //    D6	交换机主备
    //    D5-D1	保留
    //    D0	管控模块 V7主份建链指示

    uchar bl[4];                            //保留	4
    uint re_cnt;                            //接收计数	4
    uint send_cnt;                          //发送计算	4


    uchar Version_DSP6701;      //版本号
    //    D7-D5	大版本号
    //    D4-D0	小版本号


    uchar Version_DSP6678;      //    版本号
    //    D7-D5	大版本号
    //    D4-D0	小版本号
    uchar JLZS_DSP6678;         //    建链指示
    //    D7-D3	保留
    //    D2	与接口控制 V7建链指示
    //    D1	与数据处理1 DSP6678建链指示
    //    D0	与数据处理2 DSP6678建链指示


    /*********************收发处理模块********************/

    uchar Version_FPGAK7;       //版本号
    //    D7-D5	大版本号
    //    D4-D0	小版本号

    uchar  softwareLoad_FPGAK7; //    软件加载状态
    //    D7-D2	保留
    //    D1	FPGAV7-1加载状态
    //    D0	FPGAV7-2加载状态
    uchar GTX_ClockLock_FPGAK7; //    GTX时钟锁定
    //    D7-D4	软件预加载数量高4位
    //D3	保留
    //    D2	收发处理 V7-1时钟锁定指示
    //    D1	收发处理 V7-2时钟锁定指示
    //    D0	接口控制 V7时钟锁定指示
    uchar GTX_JL_FPGAK7;        //    GTX建链
    //    D7-D4	软件预加载数量高4位
    //D3	保留
    //    D2	收发处理 V7-1建链指示
    //    D1	收发处理 V7-2建链指示
    //    D0	接口控制 V7建链指示

    uchar DSP_Gmk_;             //    DSP、光模块电源(保留)


    uchar DDR_source_FPGAK7;    //    DDR电源
    //    D7-D4	保留
    //    D3	FPGA1的1DDRVTT电源PG指示
    //    D2	FPGA1的2DDRVTT电源PG指示
    //    D1	FPGA2的1DDRVTT电源PG指示
    //    D0	FPGA2的2DDRVTT电源PG指示

    uchar sourceFlag1_FPAGK7;    //    电源指示1
    //    D7-D6	保留
    //    D4	AD1电源1V电源PG指示(DVDD1PG)
    //    D3	AD1电源1_1V电源PG指示(AVDD1_1PG)
    //    D2	AD1电源1_2V电源PG指示(AVDD1_2PG)
    //    D1	AD1电源1.3VA电源PG指示(VCC1.3APG)
    //    D0	AD1电源2V电源PG指示(AVDD2PG)

    uchar sourceFlag2_FPAGK7;    //    电源指示2
    //    D7-D5	保留
    //    D4	AD2电源1V电源PG指示(2DVDD1PG)
    //    D3	AD2电源1_1V电源PG指示(2AVDD1_1PG)
    //    D2	AD2电源1V_2电源PG指示(2AVDD1_2PG)
    //    D1	AD2电源1.3VB电源PG指示(2VCC1.3BPG)
    //    D0	AD2电源2V电源PG指示(2AVDD2PG)

    uchar sourceFlag3_FPAGK7;    //    电源指示3
    //    D7-D4	保留
    //    D3	AD3电源1V电源PG指示(3DVDD1PG)
    //    D2	AD3电源1_1V电源PG指示(3AVDD1_1PG)
    //    D1	AD3电源1V_2电源PG指示(3AVDD1_2PG)
    //    D0	AD3电源2V电源PG指示(3AVDD2PG)

    uchar sourceFlag4_FPAGK7;    //    电源指示4
    //    D7-D6	保留
    //    D5	1.5V电源PG指示(VCC1.5PG)
    //    D4	2_1.5V电源PG指示(2VCC1.5PG)
    //    D3	AD1电源1.8V电源PG指示(DVDD1P8PG)
    //    D2	2.8V电源PG指示(VCC2.8PG)
    //    D1	模拟3.3V电源PG指示(VCC3.3CLKPG)
    //    D0	模拟3.3_2电源PG指示(VCC3.3CLK2PG)
    short ADC1_T_FPGAK7;        //    ADC1温度(bit8是正负标志，移动到bit15)
    //    D15-D9保留
    //    D8-D0 ADC1温度


    short ADC2_T_FPGAK7;        //    ADC2温度(bit8是正负标志，移动到bit15)
    //    D15-D9保留
    //    D8-D0 ADC2温度

    short ADC3_T_FPGAK7;        //    ADC3温度(bit8是正负标志，移动到bit15)
    //    D15-D9保留
    //    D8-D0 ADC2温度

    FPGAV7 Fpgav7_1;            //FPGAV7-1

    uchar ADC_DAC_CL_1;       //    ADC/DAC时钟锁定
    //    D7-D6	保留
    //    D5	ADC1时钟锁定指示
    //    D4	ADC2时钟锁定指示
    //    D3	ADC3时钟锁定指示
    //    D2-D0	保留
    uchar ADC_DAC_JL_1;       //    ADC/DAC建链


    //    D7-D6	保留
    //    D5	ADC1建链指示
    //    D4	ADC2建链指示
    //    D3	ADC3建链指示
    //    D2-D0	保留
    FPGAV7 Fpgav7_2;            //FPGAV7-2
    uchar ADC_DAC_CL_2;       //    ADC/DAC时钟锁定
    //    D7-D6	保留
    //    D5	ADC1时钟锁定指示
    //    D4	ADC2时钟锁定指示
    //    D3	ADC3时钟锁定指示
    //    D2-D0	保留
    uchar ADC_DAC_JL_2;       //    ADC/DAC建链
    //    D7-D6	保留
    //    D5	ADC1建链指示
    //    D4	ADC2建链指示
    //    D3	ADC3建链指示
    //    D2-D0	保留

    dataDeal_MK DataDealmk[2];  //数据处理模块

    uchar Dsp6701_S_I[16];      //    接口DSP6701
    uchar DSP6678_S_I[16];      //    接口DSP6678
    uchar V7_1_S_I[16];         //    收发V7-1
    uchar V7_2_S_I[16];         //    收发V7-2
    uchar D1V7_1_S_I[16];       //    数据1V7-1
    uchar D1V7_2_S_I[16];       //    数据1V7-2
    uchar D1DSP6678_S_I[16];    //    数据1DSP6678
    uchar D2V7_1_S_I[16];       //    数据2V7-1
    uchar D2V7_2_S_I[16];       //    数据2V7-1
    uchar D2DSP6678_S_I[16];    //    数据1DSP6678


};

Q_DECLARE_METATYPE(DC_test)

#pragma pack(pop)
#endif  // GLOBEL_DEFINE_H
