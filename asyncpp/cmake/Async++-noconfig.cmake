#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Async++" for configuration ""
set_property(TARGET Async++ APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(Async++ PROPERTIES
  IMPORTED_IMPLIB_NOCONFIG "${_IMPORT_PREFIX}/lib/libasync++.dll.a"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/bin/libasync++.dll"
  )

list(APPEND _cmake_import_check_targets Async++ )
list(APPEND _cmake_import_check_files_for_Async++ "${_IMPORT_PREFIX}/lib/libasync++.dll.a" "${_IMPORT_PREFIX}/bin/libasync++.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
