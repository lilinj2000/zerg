// Copyright (c) 2010
// All rights reserved.

#ifndef ZERG_SERVER_HH
#define ZERG_SERVER_HH

#include <memory>
#include <string>

#include "Config.hh"
#include "zebra/Service.hh"
#include "zod/PubService.hh"

namespace zerg {

class Server : public zebra::ServiceCallback {
 public:
  Server(int argc, char *argv[]);

  ~Server();

  virtual void onReceiveMarketData(
      const ftdc::MarketDataField*,
      const struct timeval&,
      const u_char* sp,
      uint32_t len);

 private:
  std::unique_ptr<Config> config_;

  std::unique_ptr<zod::PubService> pub_service_;

  std::unique_ptr<zebra::Service> zebra_service_;
};

};  // namespace zerg

#endif
