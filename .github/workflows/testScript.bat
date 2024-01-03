@echo off
for /d %%i in (*) do (
    if exist "%%i\CMakeLists.txt" (
	echo "CMakeLists.txt" found in "%%i". Starting testing...
        cd "%%i"
        cd build && ctest
        cd ..
    )
)
