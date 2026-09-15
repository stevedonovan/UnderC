rem call this from a msvc developer terminal
cmake -G "NMake Makefiles" -B out-build-cmake-vs2026-nmake-release -S ./src ^
 -DCMAKE_PREFIX_PATH="%DEP_DIR%\libffi-380-vc-x64r" ^
 -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=%DEP_DIR%\underc
cmake --build out-build-cmake-vs2026-nmake-release
cmake --build out-build-cmake-vs2026-nmake-release --target install
