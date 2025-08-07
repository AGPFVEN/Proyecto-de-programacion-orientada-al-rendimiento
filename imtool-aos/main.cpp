#include "binaryio.hpp"
#include "infoops.hpp"
#include "progargs.hpp"

#include <fstream>
#include <iostream>
#include <span>

int main(int argc, char * argv[]) {
  // Construct arguments as a vector
  //  it is done becuase of the clang-format and tidy does not allow pointer arithmetic,
  //  so I need to use vectors of strings instead
  std::vector<std::string_view> const args(argv, argv + argc);

  // Validation for arguments
  int aux_result = check_arguments(args);
  if (aux_result != 1) { return aux_result; }

  // Open files
  std::ifstream input;
  std::ofstream output;
  aux_result = open_files(args[1], input, args[2], output);
  if (aux_result != 1) { return aux_result; }

  // Check if command is info
  aux_result = read_meta_data(input, output);
  if (aux_result != 1) { return aux_result; }

  // Close files
  close_files(args[1], input, args[2], output);

  aux_result = 1;

  return aux_result;
}