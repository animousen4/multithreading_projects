
add_library  (marker "marker.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET marker PROPERTY CXX_STANDARD 20)
endif()