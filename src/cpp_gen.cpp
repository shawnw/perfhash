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

#include <ctime>
#include <exception>
#include <fstream>
#include <memory>
#include <string>
#include "nlohmann/json.hpp"

#include "table.h"
#include "generator.h"
#include "cpp_gen.h"

using namespace nlohmann;

void cpp_generator::write(const table_info &tab) {
  std::ofstream output_file{config.at("header file")};
  output_file.exceptions(std::ofstream::failbit);
  write_header(output_file, tab);
#if 0
  output_file.close();
  output_file.open(config.at("source file"));
  write_source(output_file, tab);
#endif
}

static void write_timestamp(std::ostream &out) {
  auto now = std::time(nullptr);
  out << "// Created at " << std::ctime(&now);
}

class cpp17_generator : public cpp_generator {
 protected:
  void write_header(std::ostream &, const table_info &) override;
  //  void write_source(std::ostream &, const table_info &) override;

 public:
  cpp17_generator(map_type t_, const json &config_)
      : cpp_generator(t_, config_) {}
  ~cpp17_generator() override {}
};

void cpp17_generator::write_header(std::ostream &out, const table_info &table) {
  bool is_set = type == map_type::SET;

  write_timestamp(out);
  out << "#pragma once\n"
      << "#include <array>\n"
      << "#include <cstdlib>\n"
      << "#include <optional>\n"
      << "#include <string_view>\n"
      << "#include <tuple>\n"
      << '\n';

  std::string nmspc;
  if (config.find("namespace") != config.end()) {
    nmspc = config.at("namespace");
    out << "namespace " << nmspc << " {\n";
  }

  std::string name = config.at("class");

  out << "class " << name << " {\n"
      << "public:\n"
      << "\t" << name << "() {}\n"
      << "\t~" << name << "() {}\n"
      << "\tbool exists(std::string_view) const { return false }\n"
      << "private:\n"
      << "\tstd::array<std::size_t, " << table.size() << "> lengths;\n";
  if (is_set) {
    out << "\tstd::array<const char *, " << table.size() << ">\n";
  } else {
    out << "\tstd::array<std::tuple<const char *, std::optional<"
        << static_cast<std::string>(config.at("value type")) << ">>, "
        << table.size() << ">\n";
  }

  out << "};\n";
  if (!nmspc.empty()) {
    out << "};\n";
  }
}

#if 0
void cpp17_generator::write_source(std::ostream &out, const table_info &table) {
  bool is_set = type == map_type::SET;

  write_timestamp(out);
  out << "#include " << config.at("header file") << "\n";

  std::string nmspc;
  if (config.find("namespace") != config.end()) {
    nmspc = config.at("namespace");
    out << "namespace " << nmspc << " {\n";
  }

  std::string name = config.at("class");

  out << name << "::" << name << "() {}\n";
  out << "bool " << name << "::"
      << "exists(std::string_view key) { return false; }\n";

  if (!nmspc.empty()) {
    out << "};\n";
  }
}
#endif

std::unique_ptr<cpp_generator> make_cpp_gen(const json &config, map_type type,
                                            cpp_std vers) {
  switch (vers) {
    case cpp_std::CPP_17:
      return std::make_unique<cpp17_generator>(type, config);
  }
  throw std::runtime_error{"Unknown C++ version"};
}
