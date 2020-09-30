cmake_minimum_required(VERSION 3.16)

project(RootDictExample LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(ROOT CONFIG REQUIRED)

root_generate_dictionary(G__myParticle myParticle.hpp LINKDEF LinkDef.h)

add_library(myParticle SHARED myParticle.hpp G__myParticle.cxx)
target_include_directories(myParticle PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
# target_link_libraries(myParticle PUBLIC ROOT::Core)

add_executable(myVector myVector.cpp)
target_link_libraries(myVector PUBLIC ROOT::Physics ROOT::Tree myParticle)
