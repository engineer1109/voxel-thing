#ifndef CONFIG_H
#define CONFIG_H

#include <string>

namespace E {
  class Config {
    public:
      static Config* instance();

      float screenWidth = 1600;
      float screenHeight = 900;

      std::string worldFilePath = "data/world.json";
      std::string blockDatabaseFilePath = "data/block.db";
    private:
      static Config* s_instance;
  };
}

#endif
