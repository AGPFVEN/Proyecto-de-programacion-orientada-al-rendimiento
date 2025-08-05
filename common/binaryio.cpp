#include "binaryio.hpp"

#include <fstream>
#include <iostream>
#include <string_view>

template <typename FileStream>
concept fileStreamType =
    std::same_as<FileStream, std::ifstream> || std::same_as<FileStream, std::ofstream>;

int open_file_behaviour(std::string_view const & file_name_to_open,
                        fileStreamType auto & file_stream, std::ios::openmode mode) {
  // Relate file stream with specific file (with the filename)
  file_stream.open(file_name_to_open.data(), mode);
  if (!file_stream.is_open()) {
    std::cout << "Unable to open file: " << file_name_to_open << "\n";
    return -1;
  }
  return 1;
}

void close_file_behaviour(std::string_view const & file_name_to_close,
                          fileStreamType auto & file_stream) {
  // Close files
  file_stream.close();
  if (!file_stream.is_open()) {
    std::cout << "File " << file_name_to_close << " closed correctly\n";
  } else {
    std::cout << "File " << file_name_to_close << " couldn't be closed correctly\n";
  }
}

int open_files(std::string_view const & input_filename_to_open, std::ifstream & input_file,
               std::string_view const & output_filename_to_open, std::ofstream & output_file) {
  std::cout << "Openning files...\n";

  // Open files and check if it could open
  if (open_file_behaviour(input_filename_to_open, input_file, std::ios::in) != 1) { return -1; }
  if (open_file_behaviour(output_filename_to_open, output_file, std::ios::out) != 1) { return -1; }

  std::cout << "Files opened successfully\n";

  return 1;
}

// Close functions are void because for the intent of this program its not that important if they
//  are closed correctly (same happens in terms of closing and checking if stream.failed)
void close_files(std::string_view const & input_filename_to_close, std::ifstream & input_file,
                 std::string_view const & output_filename_to_close, std::ofstream & output_file) {
  std::cout << "Closing files...\n";

  // Close files
  close_file_behaviour(input_filename_to_close, input_file);
  close_file_behaviour(output_filename_to_close, output_file);
}