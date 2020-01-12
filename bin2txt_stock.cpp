#include <iostream>
#include <string>

#include <boost/filesystem.hpp>  // headers: /usr/local/include


#include "bin2txt_stock.h"


using namespace std;
namespace fs = boost::filesystem;

//global variable
string full_path;

void convert_file(string dat_file){
	ifstream f_in(dat_file.c_str(), ios_base::binary);
	if (!f_in) {
		cerr << dat_file << " open failed" << endl;
		return;
	}

	int pos1 = dat_file.rfind('/');
	int pos = dat_file.find(".dat");
	string outfile = full_path + dat_file.substr(pos1 + 1, pos-4) + ".csv"; //output in csv format
	ofstream f_out(outfile.c_str(), ios::out);
	if (!f_out) {
		cerr << outfile << " open failed" << endl;
		f_in.close();
		return;
	}

	SaveFileHeaderStruct f_header;
	memset(&f_header, 0, sizeof(SaveFileHeaderStruct));
	f_in.read((char *)&f_header, sizeof(f_header));

	switch (f_header.data_type) {
	case TDB_KLINE_QUOTE_TYPE:
		for (int i = 0; i < f_header.data_count; ++i) {
			tdb_kline_data data;
			f_in.read((char *)&data, sizeof(data));

			f_out << data.chCode << "|" << data.chWindCode << "|" << data.nDate << "|"
				<< data.nTime << "|" << data.nOpen << "|" << data.nHigh << "|" << data.nLow << "|"
				<< data.nClose << "|" << data.iVolume << "|" << data.iTurover << "|"
				<< data.nMatchItems << "|" << data.nInterest << endl;
		}
	break;

	case TDB_TICK_QUOTE_TYPE:
		//f_out << "交易所代码,万得代码,日期,时间,成交价,成交量,成交额,成交笔数,IOPV,成交标志,BS标志,当日累计成交量,当日成交额,最高,最低,开盘,前收盘,结算价,持仓量,虚实度,昨结算,昨持仓,加权平均叫卖价,加权平均叫买价,叫卖总量,叫买总量,档1,叫卖价1,叫卖量1,叫买价1,叫买量1,...,档n,叫卖价n,叫卖量n,叫买价n,叫买量n，不加权指数，品种总数，上涨品种数，下跌品种数，持平品种数" << endl;
		f_out << "Code,Date,Time,LastPrice,volume,turnover,NumOfTrade,High,Low,Open,PreClosePrice,AskWAvgPrice,BidWAvgPrice,TotalAskVol,TotalBidVol,SP1,SV1,BP1,BV1,SP2,SV2,BP2,BV2,SP3,SV3,BP3,BV3,SP4,SV4,BP4,BV4,SP5,SV5,BP5,BV5,SP6,SV6,BP6,BV6,SP7,SV7,BP7,BV7,SP8,SV8,BP8,BV8,SP9,SV9,BP9,BV9,SP10,SV10,BP10,BV10" << endl;
		for (int i = 0; i < f_header.data_count; ++i) {
			tdb_tick_data data;
			f_in.read((char *)&data, sizeof(data));
			if (data.nTime<92400000) continue;
			//f_out << data.chCode << "|" << data.chWindCode << "|" << data.nDate << "|" << data.nTime << "|"
			//	<< data.nPrice << "|" << data.iVolume << "|" << data.iTurover << "|" << data.nMatchItems << "|"
			//	<< data.nInterest << "|" << data.chTradeFlag << "|" << data.chBSFlag << "|"
			//	<< data.iAccVolume << "|" << data.iAccTurover << "|" << data.nHigh << "|" << data.nLow << "|"
			//	<< data.nOpen << "|" << data.nPreClose << "|" << data.nSettle << "|" << data.nPosition << "|"
			//	<< data.nCurDelta << "|" << data.nPreSettle << "|" << data.nPrePosition << endl;

			//f_out << data.chCode << "|" << data.nAskAvPrice << "|" << data.nBidAvPrice << "|" << data.iTotalAskVolume << "|" << data.iTotalBidVolume << endl;
			//for (int j = 0; j < 10; j++)
			//	f_out << j << ": " << data.nAskPrice[j] << "|" << data.nAskVolume[j] << "|" << data.nBidPrice[j] << "|" << data.nBidVolume[j] << endl;

			f_out << data.chCode << "," << data.nDate << "," << data.nTime << ","
				<< data.nPrice << "," << data.iVolume << "," << data.iTurover << "," << data.nMatchItems << ","
				<< data.nHigh << "," << data.nLow << "," << data.nOpen << "," << data.nPreClose << "," 
				<< data.nAskAvPrice << "," << data.nBidAvPrice << "," << data.iTotalAskVolume << "," << data.iTotalBidVolume << ",";

			for (int j = 0; j < 10; j++)
				f_out << data.nAskPrice[j] << "," << data.nAskVolume[j] << "," << data.nBidPrice[j] << "," << data.nBidVolume[j] << ",";

			f_out << endl;
		}
	break;

	case KMDS_ORDER_QUEUE_TYPE:
		for (int i = 0; i < f_header.data_count; ++i) {
			tdb_orderqueue data;
			f_in.read((char *)&data, sizeof(data));

			f_out << data.scr_code << "|" << data.market << "|" << data.time << "|"
				<< data.insr_txn_tp_code << "|" << data.ord_price << "|" << data.ord_qty << "|"
				<< data.ord_nbr << endl;

			for (int j = 0; j < data.ord_nbr; j++)
				f_out << j << ": " << data.ord_detail_vol[j] << endl;
		}
	break;

	case KMDS_PER_ENTRUST_TYPE:
		for (int i = 0; i < f_header.data_count; ++i) {
			tdb_order data;
			f_in.read((char *)&data, sizeof(data));

			f_out << data.scr_code << "|" << data.market << "|" << data.entrt_time << "|"
				<< data.entrt_price << "|" << data.entrt_id << "|" << data.entrt_vol << "|"
				<< data.insr_txn_tp_code << "|" << data.entrt_tp << endl;
		}
	break;

	case KMDS_PER_BARGAIN_TYPE:
		for (int i = 0; i < f_header.data_count; ++i) {
			tdb_transaction data;
			f_in.read((char *)&data, sizeof(data));

			f_out << data.scr_code << "|" << data.market << "|" << data.time << "|" << data.bgn_id << "|"
				<< data.bgn_price << "|" << data.bgn_qty << "|" << data.bgn_amt << "|" << data.bgn_flg << "|"
				<< data.nsr_txn_tp_code << endl;
		}
	break;
	}

	f_out.flush();
	f_out.close();
	f_in.close();
}


int main(int argc, char **argv){

	if (argc < 3) {
		cerr <<"Mising Argument[s]: " << argv[0] << " [path_to_dat_files] [path_to_save]" << endl;
		return -1;
	}

	//full_path = fs::initial_path<fs::path>().string() + new_dir;
	string save_dir = argv[2];
	if (save_dir[0] != '/'){ //if not absolute path
		if(save_dir[0] == '.'){
			save_dir = save_dir.substr(2);
		}
		if(save_dir[save_dir.size()-1] != '/'){
			save_dir += "/";
		}
		full_path = fs::initial_path<fs::path>().string() + "/" + save_dir ;
	}
	
	if (!fs::exists(full_path)) {
		(void)fs::create_directories(full_path);
	}


	fs::path dir_path(argv[1]);
	fs::directory_iterator end_iter;
	for (fs::directory_iterator iter(dir_path); iter != end_iter; ++iter) {
		if (fs::is_directory(*iter))
			continue;

		cout << "start convert " << iter->path().string() << endl;
		convert_file(iter->path().string());
	}




	return 0;
}

