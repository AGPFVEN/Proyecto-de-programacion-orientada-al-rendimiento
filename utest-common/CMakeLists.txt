# Executable for all unit tests with list of sources
# For example, you may have one ∗_test.cpp for each ∗.cpp in common
add_executable(utest-common
    proargs_test.cpp
)

# Make sure proargs will be found in common and other headers
target_include_directories(utest-common PRIVATE ../common)

# Library dependencies
target_link_libraries (utest-common
    PRIVATE
    common
    GTest::gtest_main
    Microsoft.GSL::GSL
)

# Register test
add_test(NAME utest-common COMMAND utest-common)