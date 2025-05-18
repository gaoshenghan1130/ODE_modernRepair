# Install script for directory: /Users/gaoshenghan/Desktop/ode

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/Library/Developer/CommandLineTools/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "runtime" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/Users/gaoshenghan/Desktop/ode/build/libode.8.0.0.dylib"
    "/Users/gaoshenghan/Desktop/ode/build/libode.8.dylib"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libode.8.0.0.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libode.8.dylib"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/strip" -x "${file}")
      endif()
    endif()
  endforeach()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "development" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/Users/gaoshenghan/Desktop/ode/build/libode.dylib")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "development" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ode" TYPE FILE FILES
    "/Users/gaoshenghan/Desktop/ode/include/ode/collision.h"
    "/Users/gaoshenghan/Desktop/ode/include/ode/collision_space.h"
    "/Users/gaoshenghan/Desktop/ode/include/ode/collision_trimesh.h"
    "/Users/gaoshenghan/Desktop/ode/include/ode/common.h"
    "/Users/gaoshenghan/Desktop/ode/include/ode/compatibility.h"
    "/Users/gaoshenghan/Desktop/ode/include/ode/contact.h"
    "/Users/gaoshenghan/Desktop/ode/include/ode/cooperative.h"
    "/Users/gaoshenghan/Desktop/ode/include/ode/error.h"
    "/Users/gaoshenghan/Desktop/ode/include/ode/export-dif.h"
    "/Users/gaoshenghan/Desktop/ode/include/ode/mass.h"
    "/Users/gaoshenghan/Desktop/ode/include/ode/matrix.h"
    "/Users/gaoshenghan/Desktop/ode/include/ode/matrix_coop.h"
    "/Users/gaoshenghan/Desktop/ode/include/ode/memory.h"
    "/Users/gaoshenghan/Desktop/ode/include/ode/misc.h"
    "/Users/gaoshenghan/Desktop/ode/include/ode/objects.h"
    "/Users/gaoshenghan/Desktop/ode/include/ode/ode.h"
    "/Users/gaoshenghan/Desktop/ode/include/ode/odeconfig.h"
    "/Users/gaoshenghan/Desktop/ode/include/ode/odecpp.h"
    "/Users/gaoshenghan/Desktop/ode/include/ode/odecpp_collision.h"
    "/Users/gaoshenghan/Desktop/ode/include/ode/odeinit.h"
    "/Users/gaoshenghan/Desktop/ode/include/ode/odemath.h"
    "/Users/gaoshenghan/Desktop/ode/include/ode/odemath_legacy.h"
    "/Users/gaoshenghan/Desktop/ode/include/ode/rotation.h"
    "/Users/gaoshenghan/Desktop/ode/include/ode/threading.h"
    "/Users/gaoshenghan/Desktop/ode/include/ode/threading_impl.h"
    "/Users/gaoshenghan/Desktop/ode/include/ode/timer.h"
    "/Users/gaoshenghan/Desktop/ode/build/include/ode/precision.h"
    "/Users/gaoshenghan/Desktop/ode/build/include/ode/version.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "development" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/Users/gaoshenghan/Desktop/ode/build/ode.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "development" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE PROGRAM FILES "/Users/gaoshenghan/Desktop/ode/build/ode-config")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "development" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/ode-0.16.0" TYPE FILE FILES "/Users/gaoshenghan/Desktop/ode/build/ode-config.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "development" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/ode-0.16.0" TYPE FILE FILES "/Users/gaoshenghan/Desktop/ode/build/ode-config-version.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "development" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/ode-0.16.0/ode-export.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/ode-0.16.0/ode-export.cmake"
         "/Users/gaoshenghan/Desktop/ode/build/CMakeFiles/Export/e84f0f784275ca0b5dcba7c8cb6ccd3e/ode-export.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/ode-0.16.0/ode-export-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/ode-0.16.0/ode-export.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/ode-0.16.0" TYPE FILE FILES "/Users/gaoshenghan/Desktop/ode/build/CMakeFiles/Export/e84f0f784275ca0b5dcba7c8cb6ccd3e/ode-export.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^()$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/ode-0.16.0" TYPE FILE FILES "/Users/gaoshenghan/Desktop/ode/build/CMakeFiles/Export/e84f0f784275ca0b5dcba7c8cb6ccd3e/ode-export-noconfig.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/Users/gaoshenghan/Desktop/ode/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
