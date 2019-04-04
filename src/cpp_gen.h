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

#pragma once

class cpp_generator : public generator {
 protected:
  const nlohmann::json &config;
  virtual void write_header(std::ostream &, const table_info &) = 0;
  // virtual void write_source(std::ostream &, const table_info &) = 0;

 public:
  cpp_generator(map_type t_, const nlohmann::json &config_)
      : generator(t_), config(config_) {}
  ~cpp_generator() override {}
  void write(const table_info &) override;
};

enum class cpp_std { CPP_17 };

std::unique_ptr<cpp_generator> make_cpp_gen(const nlohmann::json &, map_type,
                                            cpp_std);
