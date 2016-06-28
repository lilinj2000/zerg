// Copyright (c) 2010
// All rights reserved.

#ifndef ZERG_CONFIG_HH
#define ZERG_CONFIG_HH

#include <string>
#include <memory>

#include "soil/Config.hh"

namespace zerg {

namespace po = boost::program_options;

class Options : public soil::Options {
 public:
  Options();

  virtual ~Options();

  virtual po::options_description* configOptions();

  std::string log_cfg;

 private:
  boost::program_options::options_description config_options_;
};

class Config {
 public:
  explicit Config(int argc = 0, char* argv[] = nullptr);
  ~Config();

  Options* zergOptions() {
    return zerg_options_.get();
  }

  soil::Options* zebraOptions() {
    return zebra_options_.get();
  }

  soil::Options* spyOptions() {
    return spy_options_.get();
  }

 private:
  std::unique_ptr<Options> zerg_options_;
  std::unique_ptr<soil::Options> zebra_options_;
  std::unique_ptr<soil::Options> spy_options_;
};

};  // namespace zerg

#endif
