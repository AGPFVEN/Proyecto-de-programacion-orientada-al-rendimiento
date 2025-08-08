#include "infoops.hpp"

#include <cstdlib>
#include <fstream>
#include <gsl/gsl>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

int read_meta_data(std::ifstream & input_file, std::ofstream & output_file) {
  std::vector<char> reader_buffer(1);
  char * ptr = reader_buffer.data();

  std::cout << "Reading file...\n";
  input_file.read(ptr, 1);
  output_file.write("test", 3);
  return 1;
}