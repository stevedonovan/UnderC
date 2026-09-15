#run this script on a fully setup developer powershell
#. .\build-cmake-install.ps1
cmake -G "NMake Makefiles" -B out-build-cmake-install-release -S src -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=Off `
  -DCMAKE_PREFIX_PATH="$env:DEP_DIR\libffi-380-vc-x64r" `
  -DCMAKE_INSTALL_PREFIX="$env:DEP_DIR\underc-vc-x64r"
cmake --build out-build-cmake-install-release
cmake --build out-build-cmake-install-release --target install
cmake -S cli -B out-build-cmake-install-cli-release -DCMAKE_INSTALL_PREFIX="$env:DEP_DIR\underc-vc-x64r"
cmake --build out-build-cmake-install-cli-release
cmake --build out-build-cmake-install-cli-release --target install
cmake -S venv -B out-build-cmake-install-venv-release -DCMAKE_INSTALL_PREFIX="$env:DEP_DIR\underc-vc-x64r"
cmake --build out-build-cmake-install-venv-release
cmake --build out-build-cmake-install-venv-release --target install