if [ "$PREFIX" == "" ]; then
 PREFIX=/tmp/underc
fi
#when libraries are not installed in the system paths use
#-DCMAKE_PREFIX_PATH="$DEP_DIR/libffi" a : seperated list of directories with install directories
#call this within developer environment, to overwrite the prefix target directory
#PREFIX="/tmp/otherdir" .\build-static-install.sh
cmake -S src -B build-lib -DCMAKE_INSTALL_PREFIX=$PREFIX
cmake --build build-lib
cmake --build build-lib --target install
#then testbuild the cli interface
cmake -S cli -B build-cli -DCMAKE_PREFIX_PATH="$PREFIX" -DCMAKE_INSTALL_PREFIX=$PREFIX
cmake --build build-cli
cmake --build build-cli --target install
