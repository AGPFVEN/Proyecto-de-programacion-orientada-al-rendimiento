#include "progargs.hpp"

#include <iostream>
#include <span>

int main(int argc, char * argv[]) {
  // Construct arguments as a vector
  // it is done becuase of the clang-format and tidy does not allow pointer arithmetic,
  // so I need to use vectors of strings instead
  std::vector<std::string_view> const args(argv, argv + argc);

  // Validation for arguments
  check_arguments(args);

  return 0;
}