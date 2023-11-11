#include <cxxopts.hpp>
#include <iostream>
#include <source_location>

int main(int argc, char **argv) {
  cxxopts::Options options(std::source_location::current().file_name());
  options.add_options()("i", "Int to check for palindrome",
                        cxxopts::value<int>())("h,help", "Print usage");
  options.parse_positional({"i"});
  auto result = options.parse(argc, argv);
  if (result.count("help") || !result.count("i")) {
    std::cout << options.help() << '\n';
    return 0;
  }

  auto i = result["i"].as<int>();
  auto str = std::to_string(i);
  std::cout << "i = " << i << "; as str = " << str << '\n';
  return 0;
}
