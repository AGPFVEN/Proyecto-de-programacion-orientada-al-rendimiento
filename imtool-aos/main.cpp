#include "progargs.hpp"

#include <iostream>
#include <span>

int main(int argc, char * argv[]) {
  // check_arguments(argc, argv);
  // std::cout << "arg num: " << argc << "\n";
  // for (auto * arg : std::span(argv, static_cast<std::size_t>(argc))) { std::cout << arg << "\n";
  // }
  check_arguments(argc, &argv);
  return 0;
}