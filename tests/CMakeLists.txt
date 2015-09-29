# Add tests in a semi-automated manner.

file(GLOB UnitTests ./ "*Test.cpp")
list(APPEND UnitTests "catchmain.cpp")
add_executable(unit ${UnitTests})
add_test(unit unit)
