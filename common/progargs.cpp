#include "progargs.hpp"

#include <iostream>
#include <span>
#include <vector>

// Check if arguments are valid for the program
int check_arguments(int argcc, std::vector<std::string> const & argvv) {
  if (argcc < 3) {
    std::cout << "Error: Invalid number of arguments: " << argcc << "\n";
    return -1;
  }
  for (std::basic_string<char> & arg : argvv) { std::cout << arg << "\n"; }

  return 0;
}