#ifndef binaryio
#define binaryio

#include <string_view>

int open_files(std::string_view const & input_filename_to_open, std::ifstream & input_file,
               std::string_view const & output_filename_to_open, std::ofstream & output_file);

void close_files(std::string_view const & input_filename_to_close, std::ifstream & input_file,
                 std::string_view const & output_filename_to_close, std::ofstream & output_file);

#endif  // binaryio.hpp