# CMakeList.txt : CMake project for OSLab4, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (Sender "sender.h" "sender.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Sender PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
