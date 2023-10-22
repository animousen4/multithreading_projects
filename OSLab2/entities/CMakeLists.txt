
add_library  (entities "entities.cpp" "entities.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET entities PROPERTY CXX_STANDARD 20)
endif()