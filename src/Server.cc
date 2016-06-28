// Copyright (c) 2010
// All rights reserved.

#include "Server.hh"
#include "Log.hh"

namespace zerg {

Server::Server(int argc, char* argv[]) {
  ZERG_TRACE <<"Server::Server()";

  config_.reset(new Config(argc, argv));

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
}

};  // namespace zerg
