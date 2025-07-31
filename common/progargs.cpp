#include "progargs.hpp"

#include <array>
#include <iostream>
#include <string_view>
#include <vector>

// Minimum number of arguments need to be recieved by the program
static constexpr int MIN_ARGUMENTS_SIZE = 4;

using error_oscf = void (*)(std::vector<std::string_view> const &);

// Struct to manage operation arguments
struct operation_options {
    std::string_view operation_name;
    size_t args_size;
    error_oscf error_on_size_check_function;
};

void test(std::vector<std::string_view> const & example) {
  std::cout << example.size() << "\n";
}

// Array of all the operations with its arguments size
static constexpr std::array<operation_options, 5> OPERATION_OPTIONS = {
  {{"info", 4, test},
   {"maxlevel", 5, test},
   {"resize", 6, test},
   {"cutfreq", 5, test},
   {"compress", 4, test}}
};

// Check if arguments are valid for the program
int check_arguments(std::vector<std::string_view> const & argss) {
  // Check if number of arguments is correct
  if (argss.size() < MIN_ARGUMENTS_SIZE) {
    std::cout << "Error: Invalid number of arguments: " << argss.size() - 1 << "\n";
    return -1;
  }

  // Loop the array (check if its valid and its size is correct)
  bool third_arg_is_valid = false;
  for (auto const & opt : OPERATION_OPTIONS) {
    // Check if the operation name exists
    if (argss[3] == opt.operation_name) {
      third_arg_is_valid = true;

      // Check if size of operation exists
      if (argss.size() != opt.args_size) {
        // Info behaviour
        if (opt.operation_name == "info") {
          std::cout << "Error: Invalid extra arguments for " << opt.operation_name << ":";
          for (size_t i = MIN_ARGUMENTS_SIZE; i < argss.size(); i++) {
            std::cout << " " << argss[i];
          }
          std::cout << "\n";

          // Maxlevel behaviour
        } else if (opt.operation_name == "maxlevel") {
          std::cout << "Error: Invalid number of extra arguments for " << opt.operation_name << ": "
                    << argss.size() - MIN_ARGUMENTS_SIZE;
        }
      } else {
        break;
      }
    }
  }
  if (!third_arg_is_valid) {
    std::cout << "Error: Invalid option: " << argss[3] << "\n";
    return -1;
  }

  return 1;
}