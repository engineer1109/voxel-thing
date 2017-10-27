#ifndef CONFIG_H
#define CONFIG_H

#include <string>

class Config {
  public:
    static Config* instance();

    float screenWidth = 1600;
    float screenHeight = 900;

    std::string worldFilePath = "world.json";
  private:
    static Config* s_instance;
};

#endif
