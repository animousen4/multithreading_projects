﻿# CMakeList.txt : CMake project for OSLab2, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (main "main.cc" "main.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET main PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
