# Locate an installed UnderC library. CMAKE_PREFIX_PATH and Underc_ROOT are
# honoured. Defines Underc_FOUND, Underc_INCLUDE_DIRS, Underc_LIBRARIES, and
# the imported target Underc::underc.
#
# The interpreter's install step writes UndercTargets.cmake beside this file.
# That export records the exact library, include directory, VM word width, and
# libffi the interpreter was actually built against, so it is used verbatim
# when present: a consumer then cannot pair a 64-bit interpreter with a 32-bit
# dependency, which surfaces only as unresolved externals at link time.
include(FindPackageHandleStandardArgs)

if(NOT TARGET Underc::underc AND EXISTS "${CMAKE_CURRENT_LIST_DIR}/UndercTargets.cmake")
    include("${CMAKE_CURRENT_LIST_DIR}/UndercTargets.cmake")
endif()

if(TARGET Underc::underc)
    get_target_property(_Underc_include_dirs Underc::underc INTERFACE_INCLUDE_DIRECTORIES)
    list(GET _Underc_include_dirs 0 Underc_INCLUDE_DIR)
    set(Underc_LIBRARY Underc::underc)
    find_package_handle_standard_args(Underc REQUIRED_VARS Underc_LIBRARY Underc_INCLUDE_DIR)
    set(Underc_INCLUDE_DIRS "${Underc_INCLUDE_DIR}")
    set(Underc_LIBRARIES Underc::underc)
    return()
endif()

# No export file: fall back to locating the pieces individually. The VM word
# width is derived by underc/vm_types.h from the consumer's own host, which is
# the same answer the interpreter reached when it was built for that host.
find_path(Underc_INCLUDE_DIR NAMES underc/ucdl.h PATH_SUFFIXES include)
find_library(Underc_LIBRARY NAMES underc PATH_SUFFIXES lib lib64)
find_package_handle_standard_args(Underc REQUIRED_VARS Underc_LIBRARY Underc_INCLUDE_DIR)
if(Underc_FOUND)
    set(Underc_INCLUDE_DIRS "${Underc_INCLUDE_DIR}")
    set(Underc_LIBRARIES "${Underc_LIBRARY}")
    if(NOT TARGET Underc::underc)
        add_library(Underc::underc UNKNOWN IMPORTED)
        set_target_properties(Underc::underc PROPERTIES
            IMPORTED_LOCATION "${Underc_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES "${Underc_INCLUDE_DIR}")
        if(UNIX AND NOT APPLE)
            set_property(TARGET Underc::underc PROPERTY
                INTERFACE_LINK_OPTIONS "-Wl,--export-dynamic")
        elseif(APPLE)
            set_property(TARGET Underc::underc PROPERTY
                INTERFACE_LINK_OPTIONS "-Wl,-export_dynamic")
        endif()
        find_library(Underc_READLINE_LIBRARY NAMES readline)
        find_library(Underc_FFI_LIBRARY NAMES ffi)
        find_package(Curses QUIET)
        set(_Underc_LINK_LIBRARIES "${CMAKE_DL_LIBS}")
        if(Underc_READLINE_LIBRARY)
            list(APPEND _Underc_LINK_LIBRARIES "${Underc_READLINE_LIBRARY}")
        endif()
        if(Underc_FFI_LIBRARY)
            list(APPEND _Underc_LINK_LIBRARIES "${Underc_FFI_LIBRARY}")
        endif()
        if(CURSES_LIBRARIES)
            list(APPEND _Underc_LINK_LIBRARIES ${CURSES_LIBRARIES})
        endif()
        set_property(TARGET Underc::underc PROPERTY INTERFACE_LINK_LIBRARIES "${_Underc_LINK_LIBRARIES}")
    endif()
endif()
mark_as_advanced(Underc_INCLUDE_DIR Underc_LIBRARY Underc_READLINE_LIBRARY Underc_FFI_LIBRARY)
