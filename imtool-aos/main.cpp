#include "progargs.hpp"

#include <iostream>
#include <span>

int main(int argc, char * argv[]) {
  // Construct arguments as a vector
  // it is done becuase of the clang-format and tidy does not allow pointer arithmetic,
  // so I need to use vectors of strings instead
  std::vector<std::string_view> const args(argv, argv + argc);

  // Validation for arguments
  int aux_result = check_arguments(args);

  if (aux_result != 1) { return aux_result; }

  aux_result = 1;

  return aux_result;
}