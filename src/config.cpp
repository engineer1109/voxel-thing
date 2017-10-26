#include <config.hpp>

Config* Config::instance() {
  if (!s_instance) {
    s_instance = new Config();
  }

  return s_instance;
}

Config* Config::s_instance;
