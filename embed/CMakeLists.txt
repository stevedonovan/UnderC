cmake_minimum_required(VERSION 3.16)
project(UndercEmbedExample VERSION 1.5.4 LANGUAGES CXX)
include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Search every prefix the caller might point us at for the installed
# FindUnderc.cmake: entries on CMAKE_PREFIX_PATH, and the install prefix itself.
set(_UNDERC_SEARCH_PREFIXES ${CMAKE_PREFIX_PATH} "${CMAKE_INSTALL_PREFIX}")
foreach(UNDERC_PREFIX IN LISTS _UNDERC_SEARCH_PREFIXES)
    list(APPEND CMAKE_MODULE_PATH
        "${UNDERC_PREFIX}/${CMAKE_INSTALL_LIBDIR}/cmake/Underc"
        "${UNDERC_PREFIX}/lib/cmake/Underc"
        "${UNDERC_PREFIX}/lib64/cmake/Underc")
endforeach()
find_package(Underc REQUIRED MODULE)

add_executable(underc-embed main.cpp)
target_link_libraries(underc-embed PRIVATE Underc::underc)
