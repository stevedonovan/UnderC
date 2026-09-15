cmake_minimum_required(VERSION 3.16)
project(UnderC_CLI VERSION 1.5.4 LANGUAGES CXX)
include(GNUInstallDirs)
option(UCC_SHARED "Link the CLI to a shared UnderC installation" OFF)
# The interpreter installs FindUnderc.cmake and UndercTargets.cmake under
# <prefix>/${CMAKE_INSTALL_LIBDIR}/cmake/Underc.  Search every prefix the caller
# might point us at: entries on CMAKE_PREFIX_PATH, and the install prefix itself.
# build-cmake-install.ps1 configures the CLI with only -DCMAKE_INSTALL_PREFIX
# pointing at the interpreter installation and no CMAKE_PREFIX_PATH, so without
# the install prefix here find_package cannot locate FindUnderc.cmake.
set(_UNDERC_SEARCH_PREFIXES ${CMAKE_PREFIX_PATH} "${CMAKE_INSTALL_PREFIX}")
foreach(UNDERC_PREFIX IN LISTS _UNDERC_SEARCH_PREFIXES)
    list(APPEND CMAKE_MODULE_PATH
        "${UNDERC_PREFIX}/${CMAKE_INSTALL_LIBDIR}/cmake/Underc"
        "${UNDERC_PREFIX}/lib/cmake/Underc"
        "${UNDERC_PREFIX}/lib64/cmake/Underc")
endforeach()
find_package(Underc REQUIRED MODULE)
add_executable(ucc main.cpp)
set_target_properties(ucc PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON CXX_EXTENSIONS OFF)
if(UNIX)
    set_property(TARGET ucc PROPERTY INSTALL_RPATH "$ORIGIN/../${CMAKE_INSTALL_LIBDIR}")
endif()
target_compile_definitions(ucc PRIVATE $<$<BOOL:${UCC_SHARED}>:UCC_SHARED=1>)
target_link_libraries(ucc PRIVATE Underc::underc)
install(TARGETS ucc RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
