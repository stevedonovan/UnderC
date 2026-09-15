if [ "$PREFIX" == "" ]; then
 PREFIX=/tmp/underc
fi
#when libraries are not installed in the system paths use
#-DCMAKE_PREFIX_PATH="$DEP_DIR/libffi" a : seperated list of directories with install directories
#call this within developer environment, to overwrite the prefix target directory
#PREFIX="/tmp/otherdir" .\build-shared-install.sh
cmake -S src -B build-lib-shared -DUCL_USRDLL=On -DCMAKE_INSTALL_PREFIX=$PREFIX
cmake --build build-lib-shared
cmake --build build-lib-shared --target install
#then testbuild the cli interface
cmake -S cli -B build-cli-shared -DCMAKE_PREFIX_PATH="$PREFIX" -DCMAKE_INSTALL_PREFIX=$PREFIX
cmake --build build-cli-shared
cmake --build build-cli-shared --target install
