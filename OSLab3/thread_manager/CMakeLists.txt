
add_library  (thread_manager "thread_manager.cpp" "thread_manager.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET thread_manager PROPERTY CXX_STANDARD 20)
endif()