
add_library  (average "average.cpp" "average.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET average PROPERTY CXX_STANDARD 20)
endif()