
add_library  (min_max "min_max.cpp" "min_max.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET min_max PROPERTY CXX_STANDARD 20)
endif()