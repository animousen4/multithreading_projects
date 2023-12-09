# CMakeList.txt : CMake project for OSLab5, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_subdirectory("client")
add_subdirectory("server")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  cmake_policy(SET CMP0141 NEW)
  set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# TODO: Add tests and install targets if needed.
