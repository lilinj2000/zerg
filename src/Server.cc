// Copyright (c) 2010
// All rights reserved.

#include "Server.hh"
#include "Log.hh"
#include "json/json.hh"
#include "soil/DateTime.hh"

namespace zerg {

Server::Server(int argc, char* argv[]) {
  ZERG_TRACE <<"Server::Server()";

  config_.reset(new Config(argc, argv));

  pub_service_.reset(
      zod::PubService::create(
          config_->zergOptions()->xsub_addr));
      
  zebra_service_.reset(zebra::Service::createService(
      config_->zebraOptions(),
      config_->spyOptions(),
      this));
}

Server::~Server() {
  ZERG_TRACE <<"Server::~Server()";
}

void Server::onReceiveMarketData(
    const ftdc::MarketDataField* md,
    const struct timeval& ts,
    const u_char* sp,
    uint32_t len) {
  ZERG_TRACE <<"Server::onReceiveMarketData()";

  std::string timestamp = soil::DateTime::now().toString();

  json::Document doc;
  json::Value v_datas;
  json::Value m_datas;

  // updatetime field
  json::Value v_InstrumentID;
  json::Value v_UpdateTime;
  json::Value v_UpdateMillisec;
  json::Value v_ActionDay;

  v_InstrumentID.SetString(md->updatetime_field.InstrumentID,
                           strlen(md->updatetime_field.InstrumentID));
  v_UpdateTime.SetString(md->updatetime_field.UpdateTime,
                         strlen(md->updatetime_field.UpdateTime));
  v_UpdateMillisec.SetInt(md->updatetime_field.UpdateMillisec);
  v_ActionDay.SetString(md->updatetime_field.ActionDay,
                        strlen(md->updatetime_field.ActionDay));

  json::addMember<const json::Value&>(&v_datas,
                                      "InstrumentID",
                                      v_InstrumentID,
                                      &doc);

  json::addMember<const json::Value&>(&v_datas,
                                      "UpdateTime",
                                      v_UpdateTime,
                                      &doc);

  json::addMember<const json::Value&>(&v_datas,
                                      "UpdateMillisec",
                                      v_UpdateMillisec,
                                      &doc);

  json::addMember<const json::Value&>(&v_datas,
                                      "ActionDay",
                                      v_ActionDay,
                                      &doc);

  // base field
  json::Value v_TradingDay;
  json::Value v_PreSettlementPrice;
  json::Value v_PreClosePrice;
  json::Value v_PreOpenInterest;
  json::Value v_PreDelta;

  v_TradingDay.SetString(md->base_field.TradingDay,
                         strlen(md->base_field.TradingDay));
  v_PreSettlementPrice.SetDouble(md->base_field.PreSettlementPrice);
  v_PreClosePrice.SetDouble(md->base_field.PreClosePrice);
  v_PreOpenInterest.SetDouble(md->base_field.PreOpenInterest);
  v_PreDelta.SetDouble(md->base_field.PreDelta);

  json::addMember<const json::Value&>(&v_datas,
                                      "TradingDay",
                                      v_TradingDay,
                                      &doc);

  json::addMember<const json::Value&>(&v_datas,
                                      "PreSettlementPrice",
                                      v_PreSettlementPrice,
                                      &doc);

  json::addMember<const json::Value&>(&v_datas,
                                      "PreClosePrice",
                                      v_PreClosePrice,
                                      &doc);

  json::addMember<const json::Value&>(&v_datas,
                                      "PreOpenInterest",
                                      v_PreOpenInterest,
                                      &doc);

  json::addMember<const json::Value&>(&v_datas,
                                      "PreDelta",
                                      v_PreDelta,
                                      &doc);

  // static field
  json::Value v_OpenPrice;
  json::Value v_HighestPrice;
  json::Value v_LowestPrice;
  json::Value v_ClosePrice;
  json::Value v_UpperLimitPrice;
  json::Value v_LowerLimitPrice;
  json::Value v_SettlementPrice;
  json::Value v_CurrDelta;

  v_OpenPrice.SetDouble(md->static_field.OpenPrice);
  v_HighestPrice.SetDouble(md->static_field.HighestPrice);
  v_LowestPrice.SetDouble(md->static_field.LowestPrice);
  v_ClosePrice.SetDouble(md->static_field.ClosePrice);
  v_UpperLimitPrice.SetDouble(md->static_field.UpperLimitPrice);
  v_LowerLimitPrice.SetDouble(md->static_field.LowerLimitPrice);
  v_SettlementPrice.SetDouble(md->static_field.SettlementPrice);
  v_CurrDelta.SetDouble(md->static_field.CurrDelta);

  json::addMember<const json::Value&>(&v_datas,
                                      "OpenPrice",
                                      v_OpenPrice,
                                      &doc);

  json::addMember<const json::Value&>(&v_datas,
                                      "HighestPrice",
                                      v_HighestPrice,
                                      &doc);

  json::addMember<const json::Value&>(&v_datas,
                                      "LowestPrice",
                                      v_LowestPrice,
                                      &doc);

  json::addMember<const json::Value&>(&v_datas,
                                      "ClosePrice",
                                      v_ClosePrice,
                                      &doc);

  json::addMember<const json::Value&>(&v_datas,
                                      "UpperLimitPrice",
                                      v_UpperLimitPrice,
                                      &doc);

  json::addMember<const json::Value&>(&v_datas,
                                      "LowerLimitPrice",
                                      v_LowerLimitPrice,
                                      &doc);

  json::addMember<const json::Value&>(&v_datas,
                                      "SettlementPrice",
                                      v_SettlementPrice,
                                      &doc);

  json::addMember<const json::Value&>(&v_datas,
                                      "CurrDelta",
                                      v_CurrDelta,
                                      &doc);

  // lastmatch field
  json::Value v_LastPrice;
  json::Value v_Volume;
  json::Value v_Turnover;
  json::Value v_OpenInterest;

  v_LastPrice.SetDouble(md->lastmatch_field.LastPrice);
  v_Volume.SetInt(md->lastmatch_field.Volume);
  v_Turnover.SetDouble(md->lastmatch_field.Turnover);
  v_OpenInterest.SetDouble(md->lastmatch_field.OpenInterest);

  json::addMember<const json::Value&>(&v_datas,
                                      "LastPrice",
                                      v_LastPrice,
                                      &doc);

  json::addMember<const json::Value&>(&v_datas,
                                      "Volume",
                                      v_Volume,
                                      &doc);

  json::addMember<const json::Value&>(&v_datas,
                                      "Turnover",
                                      v_Turnover,
                                      &doc);

  json::addMember<const json::Value&>(&v_datas,
                                      "OpenInterest",
                                      v_OpenInterest,
                                      &doc);

  // bestprice field
  json::Value v_BidPrice1;
  json::Value v_BidVolume1;
  json::Value v_AskPrice1;
  json::Value v_AskVolume1;

  v_BidPrice1.SetDouble(md->bestprice_field.BidPrice1);
  v_BidVolume1.SetInt(md->bestprice_field.BidVolume1);
  v_AskPrice1.SetDouble(md->bestprice_field.AskPrice1);
  v_AskVolume1.SetInt(md->bestprice_field.AskVolume1);

  json::addMember<const json::Value&>(&v_datas,
                                      "BidPrice1",
                                      v_BidPrice1,
                                      &doc);

  json::addMember<const json::Value&>(&v_datas,
                                      "BidVolume1",
                                      v_BidVolume1,
                                      &doc);

  json::addMember<const json::Value&>(&v_datas,
                                      "AskPrice1",
                                      v_AskPrice1,
                                      &doc);

  json::addMember<const json::Value&>(&v_datas,
                                      "AskVolume1",
                                      v_AskVolume1,
                                      &doc);

  // bid23 field
  json::Value v_BidPrice2;
  json::Value v_BidVolume2;
  json::Value v_BidPrice3;
  json::Value v_BidVolume3;

  v_BidPrice2.SetDouble(md->bid23_field.BidPrice2);
  v_BidVolume2.SetInt(md->bid23_field.BidVolume2);
  v_BidPrice3.SetDouble(md->bid23_field.BidPrice3);
  v_BidVolume3.SetInt(md->bid23_field.BidVolume3);

  json::addMember<const json::Value&>(&v_datas,
                                      "BidPrice2",
                                      v_BidPrice2,
                                      &doc);

  json::addMember<const json::Value&>(&v_datas,
                                      "BidVolume2",
                                      v_BidVolume2,
                                      &doc);

  json::addMember<const json::Value&>(&v_datas,
                                      "BidPrice3",
                                      v_BidPrice3,
                                      &doc);

  json::addMember<const json::Value&>(&v_datas,
                                      "BidVolume3",
                                      v_BidVolume3,
                                      &doc);

  // bid45 field
  json::Value v_BidPrice4;
  json::Value v_BidVolume4;
  json::Value v_BidPrice5;
  json::Value v_BidVolume5;

  v_BidPrice4.SetDouble(md->bid45_field.BidPrice4);
  v_BidVolume4.SetInt(md->bid45_field.BidVolume4);
  v_BidPrice5.SetDouble(md->bid45_field.BidPrice5);
  v_BidVolume5.SetInt(md->bid45_field.BidVolume5);

  json::addMember<const json::Value&>(&v_datas,
                                      "BidPrice4",
                                      v_BidPrice4,
                                      &doc);

  json::addMember<const json::Value&>(&v_datas,
                                      "BidVolume4",
                                      v_BidVolume4,
                                      &doc);

  json::addMember<const json::Value&>(&v_datas,
                                      "BidPrice5",
                                      v_BidPrice5,
                                      &doc);

  json::addMember<const json::Value&>(&v_datas,
                                      "BidVolume5",
                                      v_BidVolume5,
                                      &doc);

  // ask23 field
  json::Value v_AskPrice2;
  json::Value v_AskVolume2;
  json::Value v_AskPrice3;
  json::Value v_AskVolume3;

  v_AskPrice2.SetDouble(md->ask23_field.AskPrice2);
  v_AskVolume2.SetInt(md->ask23_field.AskVolume2);
  v_AskPrice3.SetDouble(md->ask23_field.AskPrice3);
  v_AskVolume3.SetInt(md->ask23_field.AskVolume3);

  json::addMember<const json::Value&>(&v_datas,
                                      "AskPrice2",
                                      v_AskPrice2,
                                      &doc);

  json::addMember<const json::Value&>(&v_datas,
                                      "AskVolume2",
                                      v_AskVolume2,
                                      &doc);

  json::addMember<const json::Value&>(&v_datas,
                                      "AskPrice3",
                                      v_AskPrice3,
                                      &doc);

  json::addMember<const json::Value&>(&v_datas,
                                      "AskVolume3",
                                      v_AskVolume3,
                                      &doc);

  // ask45 field
  json::Value v_AskPrice4;
  json::Value v_AskVolume4;
  json::Value v_AskPrice5;
  json::Value v_AskVolume5;

  v_AskPrice4.SetDouble(md->ask45_field.AskPrice4);
  v_AskVolume4.SetInt(md->ask45_field.AskVolume4);
  v_AskPrice5.SetDouble(md->ask45_field.AskPrice5);
  v_AskVolume5.SetInt(md->ask45_field.AskVolume5);

  json::addMember<const json::Value&>(&v_datas,
                                      "AskPrice4",
                                      v_AskPrice4,
                                      &doc);

  json::addMember<const json::Value&>(&v_datas,
                                      "AskVolume4",
                                      v_AskVolume4,
                                      &doc);

  json::addMember<const json::Value&>(&v_datas,
                                      "AskPrice5",
                                      v_AskPrice5,
                                      &doc);

  json::addMember<const json::Value&>(&v_datas,
                                      "AskVolume5",
                                      v_AskVolume5,
                                      &doc);

  json::addMember<const json::Value&>(&m_datas,
                                      "MarketDataField",
                                      v_datas,
                                      &doc);

  json::Value v_timestamp;
  v_timestamp.SetString(json::StringRef(timestamp.data()), timestamp.length());

  json::addMember<const json::Value&>(&m_datas,
                                      "timestamp",
                                      v_timestamp,
                                      &doc);
  std::chrono::system_clock::time_point tp =
      std::chrono::system_clock::from_time_t(ts.tv_sec);
  tp += std::chrono::microseconds(ts.tv_usec);
  std::string ts_pcap = soil::DateTime(tp).toString();
  json::Value v_ts;
  v_ts.SetString(json::StringRef(ts_pcap.data()), ts_pcap.length());

  json::addMember<const json::Value&>(&m_datas,
                                      "ts",
                                      v_ts,
                                      &doc);

  json::addMember<const json::Value&>(&doc,
                                      "onReceiveMarketData",
                                      m_datas);

  std::string str_json = json::toString(doc);
  ZERG_DEBUG <<str_json;

  pub_service_->sendMsg(str_json);
}

};  // namespace zerg
