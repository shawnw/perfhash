cmake_minimum_required(VERSION 3.10)
project(perfhash)

set(JSON_BuildTests OFF CACHE INTERNAL "")
set(JSON_Install OFF CACHE INTERNAL "")
add_subdirectory(nlohmann_json)


add_executable(perfhash perfhash.cpp cpp_gen.cpp)
set_target_properties(perfhash PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED 1)
target_link_libraries(perfhash PRIVATE nlohmann_json::nlohmann_json)

