# CMakeList.txt : CMake project for OScolloquimNumberOperations, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (OScolloquimNumberOperations "OScolloquimNumberOperations.cpp" "OScolloquimNumberOperations.h" "entities/opercode.cpp" "entities/file/filemanager.h" "entities/file_data/file_data.h" "entities/path_maker/path_maker.h" "entities/thread_manager/thread_manager.h" "entities/action_processor/action_processor.h" "entities/data_processor/data_processor.h" "entities/consts/regexpr.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET OScolloquimNumberOperations PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
