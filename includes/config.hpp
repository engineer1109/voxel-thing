#ifndef CONFIG_H
#define CONFIG_H

class Config {
  public:
    static Config* instance();

    float screenWidth = 1600;
    float screenHeight = 900;
  private:
    static Config* s_instance;
};

#endif
