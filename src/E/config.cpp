#include <E/config.hpp>

E::Config* E::Config::instance() {
  if (!s_instance) {
    s_instance = new E::Config();
  }

  return s_instance;
}

E::Config* E::Config::s_instance;
