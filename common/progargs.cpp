#include "progargs.hpp"

#include <array>
#include <iostream>
#include <string_view>
#include <vector>

constexpr int MIN_ARGUMENTS_SIZE                            = 4;
constexpr std::array<std::string_view, 5> OPERATION_OPTIONS = {"info", "maxlevel", "resize",
                                                               "cutfreq", "compress"};

// Check if arguments are valid for the program
int check_arguments(std::vector<std::string_view> const & argss) {
  // Check if number of arguments is correct
  if (argss.size() < MIN_ARGUMENTS_SIZE) {
    std::cout << "Error: Invalid number of arguments: " << argss.size() - 1 << "\n";
    return -1;
  }

  // Check if 3rd argument is valid
  bool third_arg_is_valid = false;
  for (auto const & opt : OPERATION_OPTIONS) {
    if (argss[3] == opt) {
      third_arg_is_valid = true;
      break;
    }
  }
  if (!third_arg_is_valid) {
    std::cout << "Error: Invalid option: " << argss[3] << "\n";
    return -1;
  }

  // Check if arguments are valid for selected option
  switch (argss[3]) {
    case "info":
      std::cout << "hh\n";
      break;

    default:
      break;
  }
  return 1;

  std::cout << argss[1] << "\n";

  return 0;
}