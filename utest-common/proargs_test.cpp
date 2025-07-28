#include "progargs.hpp"

#include <gtest/gtest.h>
#include <string_view>
#include <vector>

// Ejemplo
TEST(ProgArgsTest, ZeroArgsGiven) {
  std::vector<std::string_view> const supossed_args{};

  ASSERT_EQ(check_arguments(supossed_args), -1);
}

TEST(ProgArgsTest, OneArgsGiven) {
  std::vector<std::string_view> const supossed_args = {"test"};

  ASSERT_EQ(check_arguments(supossed_args), -1);
}

TEST(ProgArgsTest, TwoArgsGiven) {
  std::vector<std::string_view> const supossed_args = {"another", "test"};

  ASSERT_EQ(check_arguments(supossed_args), -1);
}

TEST(ProgArgsTest, ThreeArgsGiven) {
  std::vector<std::string_view> const supossed_args = {"yet", "another", "test"};

  ASSERT_EQ(check_arguments(supossed_args), -1);
}

TEST(ProgArgsTest, FourRandomArgsGiven) {
  std::vector<std::string_view> const supossed_args = {"yet", "another", "test", "again"};

  ASSERT_EQ(check_arguments(supossed_args), -1);
}
