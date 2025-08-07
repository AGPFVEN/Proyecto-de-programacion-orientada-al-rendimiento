#include "infoops.hpp"

#include <cstdlib>
#include <fstream>
#include <gsl/gsl>
#include <iostream>
#include <memory>
#include <string>

int read_meta_data(std::ifstream & input_file, std::ofstream & output_file) {
  // Allocate 1 byte, automatically freed via std::free when 'reader_string' goes out of scope
  auto reader_string =
      std::unique_ptr<char, decltype(&std::free)>{static_cast<char *>(std::malloc(1)), &std::free};

  if (!reader_string) {
    std::abort();  // allocation failure
  }

  std::cout << "Reading file...\n";
  input_file.read(reader_string, 1);
  output_file.write("test", 3);
  std::free(reader_string);
  return 1;
}