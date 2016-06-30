// Copyright (c) 2010
// All rights reserved.

#include <boost/program_options.hpp>
#include <fstream>
#include <iostream>

#include "Config.hh"
#include "Log.hh"
#include "zebra/Service.hh"
#include "spy/Service.hh"

namespace zerg {

Options::Options():
    config_options_("zergConfigOptions") {
  namespace po = boost::program_options;

  config_options_.add_options()
      ("zerg.xsub_addr", po::value<std::string>(&xsub_addr),
       "xsub address")
      ("zerg.log_cfg", po::value<std::string>(&log_cfg),
         "log config file");
  return;
}

Options::~Options() {
}

po::options_description* Options::configOptions() {
  return &config_options_;
}

Config::Config(int argc, char* argv[]) {
  zerg_options_.reset(new Options());
  zebra_options_.reset(zebra::Service::createOptions());
  spy_options_.reset(spy::Service::createOptions());

  std::unique_ptr<soil::Config> config(soil::Config::create());
  config->registerOptions(zerg_options_.get());
  config->registerOptions(zebra_options_.get());
  config->registerOptions(spy_options_.get());

  config->configFile() = "zerg.cfg";
  config->loadConfig(argc, argv);

  // init the log
  ZERG_LOG_INIT(zerg_options_->log_cfg);

  return;
}

Config::~Config() {
}

};  // namespace zerg
