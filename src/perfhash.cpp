/*
    perfhash - perfect hash table generator
    Copyright (C) 2019 Shawn Wagner

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <exception>
#include <string>

#include "nlohmann/json.hpp"

#include "table.h"
#include "generator.h"
#include "cpp_gen.h"

using namespace nlohmann;

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " table_definition.json\n";
    return EXIT_FAILURE;
  }

  try {
    std::ifstream config_file{argv[1]};
    if (!config_file.good()) {
      std::cerr << "Unable to open file " << argv[1] << "!\n";
      return EXIT_FAILURE;
    }

    json config;
    config_file >> config;

    auto output = config.at("output");
    std::string lang = output.at("language");
    std::string type_s = config.at("type");
    map_type type;
    if (type_s == "map") {
      type = map_type::MAP;
    } else if (type_s == "set") {
      type = map_type::SET;
    } else {
      throw std::runtime_error{"Unknown table type"};
    }

    std::unique_ptr<generator> gen;
    if (lang == "c++17") {
      gen = make_cpp_gen(output, type, cpp_std::CPP_17);
      std::cout << "Using C++17\n";
    } else {
      std::cerr << "Unsupported language: " << lang << '\n';
      return EXIT_FAILURE;
    }
    gen->write(table_info());
  } catch (std::exception &e) {
    std::cerr << "Error: " << e.what() << '\n';
    return EXIT_FAILURE;
  }

  return 0;
}
