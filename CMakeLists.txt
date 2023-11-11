cmake_minimum_required(VERSION 3.27)

project(CppSandbox)

add_compile_options(-Werror -Wall -Wextra -Wconversion -pedantic -pedantic-errors -Wconversion -Wsign-conversion)

enable_testing()

set(CXXOPTS_DIR /root/build/Debug/generators/)
if(NOT EXISTS ${CXXOPTS_DIR})
  message(FATAL_ERROR "conan did not install correctly in docker")
endif()
find_package(CXXOPTS CONFIG REQUIRED)

add_subdirectory(./src/palindrome-int)
