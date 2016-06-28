// Copyright (c) 2010
// All rights reserved.

#include <memory>

#include "Server.hh"
#include "soil/Pause.hh"

int main(int argc, char* argv[]) {
  std::unique_ptr<zerg::Server> server;

  server.reset(new zerg::Server(argc, argv));

  std::unique_ptr<soil::Pause> pause(soil::Pause::create());

  return 0;
}
