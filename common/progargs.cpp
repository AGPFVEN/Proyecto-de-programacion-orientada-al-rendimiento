#include "progargs.hpp"

#include <array>
#include <charconv>
#include <iostream>
#include <string_view>
#include <vector>

// Minimum number of arguments need to be recieved by the program
static constexpr int MIN_ARGUMENTS_SIZE = 4;
static constexpr int MIN_MAXLEVEL_LIMIT = 0;
static constexpr int MAX_MAXLEVEL_LIMIT = 65535;

// Function to excecute when the command is info but the number of arguments is wrong
void eoscf_info_behaviour(std::string_view const operation_name_info,
                          std::vector<std::string_view> const & argsss) {
  std::cout << "Error: Invalid extra arguments for " << operation_name_info << ":";
  for (size_t i = MIN_ARGUMENTS_SIZE; i < argsss.size(); i++) { std::cout << " " << argsss[i]; }
  std::cout << "\n";
}

// Function to excecute when the command is maxlevel but the number of arguments is wrong
void eoscf_maxlevel_behaviour(std::string_view const operation_name_info,
                              std::vector<std::string_view> const & argsss) {
  std::cout << "Error: Invalid number of extra arguments for " << operation_name_info << ": "
            << argsss.size() - MIN_ARGUMENTS_SIZE << "\n";
}

// Function to execute when the command is maxlevel, the number of arguments is correct and there
//  are more aspects to check (it checks if 4th argument is a number between 0 and 65535)
int casc_maxlevel_behaviour(std::string_view const operation_name_info,
                            std::vector<std::string_view> const & argsss) {
  // Convert argument string into number
  int numeric_arg_to_eval             = 0;
  std::string_view const arg_to_check = argsss[4];
  auto [ptr, ec] = std::from_chars(arg_to_check.data(), arg_to_check.data() + arg_to_check.size(),
                                   numeric_arg_to_eval);
  if (ec != std::errc()) {
    std::cout << "Error: Invalid " << operation_name_info << ": " << arg_to_check << "\n";
    return -1;
  }

  // Make the validation
  if ((numeric_arg_to_eval < MIN_MAXLEVEL_LIMIT) || (numeric_arg_to_eval > MAX_MAXLEVEL_LIMIT)) {
    std::cout << "Error: Invalid " << operation_name_info << ": " << arg_to_check << "\n";
    return -1;
  }
  return 1;
}

int parse_positive_int(std::string_view arg) {
  int value   = 0;
  auto result = std::from_chars(arg.data(), arg.data() + arg.size(), value);

  if (result.ec != std::errc() || value < 0) { return -1; }

  return value;
}

// Function to execute when the command is resize, the number of arguments is correct and there are
//  more aspects to check (it checks if 4th and 5th arguments are positive numbers)
int casc_resize_behaviour(std::string_view const operation_name_info,
                          std::vector<std::string_view> const & argsss) {
  size_t const width_arg = 4;
  size_t const hight_arg = 5;

  // Make the validations
  if (parse_positive_int(argsss[width_arg]) == -1) {
    std::cout << "Error: Invalid " << operation_name_info << " width: " << argsss[width_arg]
              << "\n";
    return -1;
  }
  if (parse_positive_int(argsss[hight_arg]) == -1) {
    std::cout << "Error: Invalid " << operation_name_info << " hight: " << argsss[width_arg]
              << "\n";
    return -1;
  }

  return 1;
}

// Function to execute when the command is resize, the number of arguments is correct and there are
//  more aspects to check (it checks if 4th and 5th arguments are positive numbers)
int casc_cutfreq_behaviour(std::string_view const operation_name_info,
                           std::vector<std::string_view> const & argsss) {
  size_t const arg_to_analyze = 4;

  // Make the validations
  if (parse_positive_int(argsss[arg_to_analyze]) == -1) {
    std::cout << "Error: Invalid " << operation_name_info << ": " << argsss[arg_to_analyze] << "\n";
    return -1;
  }
  return 1;
}

// Function to execute after spotting that the number of arguments is not correcto for the operation
using error_oscf = void (*)(std::string_view const operation_name_info,
                            std::vector<std::string_view> const & argsss);

// Function (to make additional checks) to execute after knowing the number of arguments is correct
using check_asc = int (*)(std::string_view const operation_name_info,
                          std::vector<std::string_view> const & argsss);

// Struct to manage operation arguments
struct operation_options {
    std::string_view operation_name;
    size_t args_size;
    error_oscf error_on_size_check_function;
    check_asc check_after_size_check;
};

// Array of all the operations with its arguments size
static constexpr std::array<operation_options, 5> OPERATION_OPTIONS = {
  {{"info", 4, eoscf_info_behaviour, nullptr},
   {"maxlevel", 5, eoscf_maxlevel_behaviour, casc_maxlevel_behaviour},
   {"resize", 6, eoscf_maxlevel_behaviour, casc_resize_behaviour},
   {"cutfreq", 5, eoscf_maxlevel_behaviour, casc_cutfreq_behaviour},
   {"compress", 4, eoscf_info_behaviour, nullptr}}
};

// Check if arguments are valid for the program
int check_arguments(std::vector<std::string_view> const & argss) {
  // Check if number of arguments is correct
  if (argss.size() < MIN_ARGUMENTS_SIZE) {
    std::cout << "Error: Invalid number of arguments: " << argss.size() - 1 << "\n";
    return -1;
  }

  // Loop the args (check if its valid and its size is correct)
  bool third_arg_is_valid = false;
  for (auto const & opt : OPERATION_OPTIONS) {
    // Check if the operation name exists
    if (argss[3] == opt.operation_name) {
      third_arg_is_valid = true;
      // Check if size of operation exists
      if (argss.size() != opt.args_size) {
        // Command behaviour
        opt.error_on_size_check_function(opt.operation_name, argss);
      } else {
        if (opt.check_after_size_check != nullptr) {
          int const more_checks_result = opt.check_after_size_check(opt.operation_name, argss);
          if (more_checks_result != 1) { return more_checks_result; };
        }
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