Description
------------
This program can convert stock tick files from dat format to csv format. A stock tick file has headers as following: 

`"Code,Date,Time,LastPrice,volume,turnover,NumOfTrade,High,Low,Open,PreClosePrice,AskWAvgPrice,BidWAvgPrice,TotalAskVol,TotalBidVol,SP1,SV1,BP1,BV1,SP2,SV2,BP2,BV2,SP3,SV3,BP3,BV3,SP4,SV4,BP4,BV4,SP5,SV5,BP5,BV5,SP6,SV6,BP6,BV6,SP7,SV7,BP7,BV7,SP8,SV8,BP8,BV8,SP9,SV9,BP9,BV9,SP10,SV10,BP10,BV10"`

The Boost C++ Libraries are used. Make sure to have the libraries installed.

To execute the program, execute `./bin2csv [path_to_dat_files] [path_to_save]`.
