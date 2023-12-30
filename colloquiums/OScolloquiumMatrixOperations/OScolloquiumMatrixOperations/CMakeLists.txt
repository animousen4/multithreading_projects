# CMakeList.txt : CMake project for OScolloquiumMatrixOperations, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (
	OScolloquiumMatrixOperations
	"OScolloquiumMatrixOperations.cpp" "OScolloquiumMatrixOperations.h"
	 "matrix/matrix.cpp" "matrix/matrixCalculator.cpp" 
 "matrix/thread/calculateThread.cpp" "matrix/matrixTaskPool.cpp" "matrix/matrixTask.cpp" "matrix/matrixInputTask.cpp" "matrix/file/matrixFileReader.cpp" "matrix/validator/matrixValidator.cpp" "matrix/validator/matrixSizeValidator.cpp" "matrix/manager/matrixManager.cpp" "matrix/thread/threadConsts.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET OScolloquiumMatrixOperations PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
