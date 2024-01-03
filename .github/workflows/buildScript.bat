@echo off
for /d %%i in (*) do (
    if exist "%%i\CMakeLists.txt" (
	echo "CMakeLists.txt" found in "%%i". Starting building...
        cd "%%i"
        cmake -S . -B build && cmake --build build
        cd ..
    )
)
