#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include "nlohmann/json.hpp"

using namespace nlohmann;

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " table_definition.json\n";
    return EXIT_FAILURE;
  }

  std::ifstream config_file{argv[1]};
  if (!config_file.good()) {
    std::cerr << "Unable to open file " << argv[1] << "!\n";
    return EXIT_FAILURE;
  }

  json config;
  if (!(config_file >> config)) {
    std::cerr << "Unable to parse " << argv[1] << "!\n";
    return EXIT_FAILURE;
  }

  return 0;
}
