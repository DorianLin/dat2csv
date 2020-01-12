#ifndef BIN2TXT_STOCK_H_
#define BIN2TXT_STOCK_H_

#include <string>

#pragma pack(push)
#pragma pack(8)

typedef unsigned char UCHAR8;
typedef unsigned short UINT16;
typedef long long INT64;
typedef char CHAR8;
typedef short INT16;
typedef int INT32;
typedef unsigned int UINT32;
typedef double REAL8;
typedef int BOOL;


#define TDB_TICK_QUOTE_TYPE         27
#define TDB_KLINE_QUOTE_TYPE        28
#define KMDS_ORDER_QUEUE_TYPE       0xc4
#define KMDS_PER_ENTRUST_TYPE       0xc5
#define KMDS_PER_BARGAIN_TYPE       0xc6


// 二进制存储的文件头信息
struct SaveFileHeaderStruct
{
    int data_count;     // number of quote data items
    short data_type;    // 行情类型标识
    short data_length;  // length of one item (byte)
};


//历史K线数据
struct tdb_kline_data
{
    CHAR8 chWindCode[32];             //万得代码(ag1312.SHF)
    CHAR8 chCode[32];                 //交易所代码(ag1312)
    INT32 nDate;                      //日期（自然日）格式：YYMMDD，例如20130101表示2013年1月1日，0表示今天
    INT32 nTime;                      //时间（HHMMSSmmm）例如94500000 表示 9点45分00秒000毫秒
    INT32 nOpen;                      //开盘((a double number + 0.00005) *10000)
    INT32 nHigh;                      //最高((a double number + 0.00005) *10000)
    INT32 nLow;                       //最低((a double number + 0.00005) *10000)
    INT32 nClose;                     //收盘((a double number + 0.00005) *10000)
    INT64 iVolume;                    //成交量
    INT64 iTurover;                   //成交额(元)
    INT32 nMatchItems;                //成交笔数
    INT32 nInterest;                  //持仓量(期货)、IOPV(基金)、利息(债券)

    // HH:MM:SS.mmm
    std::string GetQuoteTime() const
    {
        CHAR8 buf[64];
        INT32 t = nTime;
        sprintf(buf, "%02d:%02d:%02d.%03d", t / 10000000, (t / 100000) % 100, (t / 1000) % 100, t % 1000);

        return std::string(buf);
    }
};


//历史Tick数据
struct tdb_tick_data
{
    CHAR8 chWindCode[32];               //万得代码(ag1312.SHF)
    CHAR8 chCode[32];                   //交易所代码(ag1312)
    INT32 nDate;                        //日期（自然日）
    INT32 nTime;                        //时间（HHMMSSmmm）例如94500000 表示 9点45分00秒000毫秒
    INT32 nPrice;                       //成交价((a double number + 0.00005) *10000)
    INT64 iVolume;                      //成交量
    INT64 iTurover;                     //成交额(元)
    INT32 nMatchItems;                  //成交笔数
    INT32 nInterest;                    //IOPV(基金)、利息(债券)
    CHAR8 chTradeFlag;                  //成交标志
    CHAR8 chBSFlag;                     //BS标志
    INT64 iAccVolume;                   //当日累计成交量
    INT64 iAccTurover;                  //当日成交额(元)
    INT32 nHigh;                        //最高((a double number + 0.00005) *10000)
    INT32 nLow;                         //最低((a double number + 0.00005) *10000)
    INT32 nOpen;                        //开盘((a double number + 0.00005) *10000)
    INT32 nPreClose;                    //前收盘((a double number + 0.00005) *10000)

    //期货字段
    INT32 nSettle;                      //结算价((a double number + 0.00005) *10000)
    INT32 nPosition;                    //持仓量
    INT32 nCurDelta;                    //虚实度
    INT32 nPreSettle;                   //昨结算((a double number + 0.00005) *10000)
    INT32 nPrePosition;                 //昨持仓

    //买卖盘字段
    INT32 nAskPrice[10];                //叫卖价((a double number + 0.00005) *10000)
    UINT32 nAskVolume[10];              //叫卖量
    INT32 nBidPrice[10];                //叫买价((a double number + 0.00005) *10000)
    UINT32 nBidVolume[10];              //叫买量
    INT32 nAskAvPrice;                  //加权平均叫卖价(上海L2)((a double number + 0.00005) *10000)
    INT32 nBidAvPrice;                  //加权平均叫买价(上海L2)((a double number + 0.00005) *10000)
    INT64 iTotalAskVolume;              //叫卖总量(上海L2)
    INT64 iTotalBidVolume;              //叫买总量(上海L2)

    //下面的字段指数使用
    INT32 nIndex;                       //不加权指数
    INT32 nStocks;                      //品种总数
    INT32 nUps;                         //上涨品种数
    INT32 nDowns;                       //下跌品种数
    INT32 nHoldLines;                   //持平品种数

    // HH:MM:SS.mmm
    std::string GetQuoteTime() const
    {
        CHAR8 buf[64];
        INT32 t = nTime;
        sprintf(buf, "%02d:%02d:%02d.%03d", t / 10000000, (t / 100000) % 100, (t / 1000) % 100, t % 1000);

        return std::string(buf);
    }
};


//历史逐笔委托
struct tdb_order
{
    INT32 market;
    CHAR8 scr_code[32];         //交易所代码
    INT32 entrt_time;           //委托时间
    INT32 entrt_price;          //委托价格
    INT64 entrt_id;             //委托编号
    INT64 entrt_vol;            //委托数量
    CHAR8 insr_txn_tp_code[4];  //指令交易类型 'B','S','C'
    CHAR8 entrt_tp[4];          //委托类别

    // HH:MM:SS.mmm
    std::string GetQuoteTime() const
    {
        CHAR8 buf[64];
        INT32 t = entrt_time;
        sprintf(buf, "%02d:%02d:%02d.%03d", t / 10000000, (t / 100000) % 100, (t / 1000) % 100, t % 1000);

        return std::string(buf);
    }
};


//历史逐笔成交
struct tdb_transaction
{
    INT32 time;                     //成交时间
    INT32 market;
    CHAR8 scr_code[32];             //交易所代码
    INT64 bgn_id;                   //成交编号
    INT32 bgn_price;                //成交价格
    INT64 bgn_qty;                  //成交数量
    INT64 bgn_amt;                  //成交金额
    CHAR8 bgn_flg[4];               //成交类别
    CHAR8 nsr_txn_tp_code[4];       //指令交易类型

    // HH:MM:SS.mmm
    std::string GetQuoteTime() const
    {
        CHAR8 buf[64];
        INT32 t = time;
        sprintf(buf, "%02d:%02d:%02d.%03d", t / 10000000, (t / 100000) % 100, (t / 1000) % 100, t % 1000);

        return std::string(buf);
    }
};


//历史委托队列
struct tdb_orderqueue
{
    INT32 time;
    INT32 market;
    CHAR8 scr_code[32];
    CHAR8 insr_txn_tp_code[4];      //指令交易类型 'B','S'
    INT32 ord_price;                //订单价格
    INT32 ord_qty;                  //订单数量
    INT32 ord_nbr;                  //明细个数
    INT32 ord_detail_vol[50];       //订单明细数量

    // HH:MM:SS.mmm
    std::string GetQuoteTime() const
    {
        CHAR8 buf[64];
        INT32 t = time;                  //时间(HHMMSSmmm)
        sprintf(buf, "%02d:%02d:%02d.%03d", t / 10000000, (t / 100000) % 100, (t / 1000) % 100, t % 1000);

        return std::string(buf);
    }
};



#pragma pack(pop)

#endif
