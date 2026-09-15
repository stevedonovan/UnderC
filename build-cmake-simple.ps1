#run this script on a fully setup developer powershell
#. .\build-cmake-simple.ps1
cmake -G "NMake Makefiles" -B out-build-cmake-simple-release -S ./src -DCMAKE_BUILD_TYPE=Release`
  -DCMAKE_PREFIX_PATH="$env:DEP_DIR\libffi-380-vc-x64r" `
  -DCMAKE_INSTALL_PREFIX="$env:DEP_DIR\underc-vc-x64r"
cmake --build out-build-cmake-simple-release
#Currently not supported. UnderC has to be installed in the target directory.
#cmake -S cli -B out-build-cmake-simple-cli-release -DUCC_INSOURCE_BUILD=On -DCMAKE_INSTALL_PREFIX="$env:DEP_DIR\underc-vc-x64r"
#cmake --build out-build-cmake-simple-cli-release