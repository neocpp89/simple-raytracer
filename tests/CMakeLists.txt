# Add tests in a semi-automated manner.

file(GLOB UnitTests ./ "*Test.cpp")
list(APPEND UnitTests "catchmain.cpp")
add_executable(unit ${UnitTests})
target_include_directories(unit PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../src/libsrt/)
target_link_libraries(unit srt)
add_test(unit unit)
