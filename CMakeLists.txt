# MIT License
# 
# Copyright (c) 2025 @slack019
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

cmake_minimum_required(VERSION 3.23)
project(flux VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cmake/utils.cmake)
include(GNUInstallDirs) 

string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" PROJECT_IS_TOP_LEVEL)

option(BUILD_EXAMPLES "Build flux examples" OFF)
option(BUILD_TESTS "Build flux tests" OFF)
option(FLUX_INSTALL "Generate target for installing flux" OFF)
set_if_undefined(FLUX_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/flux" CACHE STRING
  "Install path for flux package-related CMake files")

if(DEFINED FLUX_SHARED_LIBS)
  set(BUILD_SHARED_LIBS ${FLUX_SHARED_LIBS})
endif() 

if(NOT DEFINED CMAKE_BUILD_TYPE) 
  set(CMAKE_BUILD_TYPE Release)
endif()

set_if_undefined(CMAKE_CXX_VISIBILITY_PRESET hidden)
set_if_undefined(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

# Initialized below
add_library(flux)
add_library(flux::flux ALIAS flux)

# Dependencies

include(GenerateExportHeader)
set(export_file_name "export-shared.hpp")

if(NOT BUILD_SHARED_LIBS)
  set(export_file_name "export-static.hpp")
endif() 

generate_export_header(flux EXPORT_FILE_NAME include/flux/${export_file_name})

set(SOURCES 
  include/flux/containers/string.hpp
  include/flux/export-flux.hpp
  include/flux/containers/vector.hpp
  source/containers/string.cpp
  source/containers/vector.cpp)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})

# Flux target

include(CMakePackageConfigHelpers)

target_sources(flux PRIVATE ${SOURCES})
target_compile_definitions(flux PUBLIC "$<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:FLUX_STATIC_DEFINE>")

target_include_directories(flux PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
  "$<INSTALL_INTERFACE:${FLUX_INSTALL_CMAKEDIR}>")

set_target_properties(flux PROPERTIES 
  SOVERSION ${PROJECT_VERSION_MAJOR}
  VERSION ${PROJECT_VERSION})

if(FLUX_INSTALL AND NOT CMAKE_SKIP_INSTALL_RULES)
  configure_package_config_file(cmake/flux-config.cmake.in flux-config.cmake
    INSTALL_DESTINATION "${FLUX_INSTALL_CMAKEDIR}")

  write_basic_package_version_file(flux-config-version.cmake 
    COMPATIBILITY SameMajorVersion)

  install(TARGETS flux EXPORT flux-export
    RUNTIME COMPONENT flux
    LIBRARY COMPONENT flux 
    ARCHIVE COMPONENT flux-dev 
    INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

  install(DIRECTORY include/ 
    TYPE INCLUDE 
    COMPONENT flux-dev)

  install(FILES "${CMAKE_CURRENT_BINARY_DIR}/include/flux/${export_file_name}"
    COMPONENT flux-dev 
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/flux") 

  set(targets_file "flux-shared-targets.cmake")

  if(NOT BUILD_SHARED_LIBS)
    set(targets_file "flux-static-targets.cmake")
  endif() 

  install(EXPORT flux-export
    COMPONENT flux-dev 
    FILE "${targets_file}"
    DESTINATION "${FLUX_INSTALL_CMAKEDIR}"
    NAMESPACE flux::)

  install(FILES 
    "${CMAKE_CURRENT_BINARY_DIR}/flux-config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/flux-config-version.cmake"
    COMPONENT flux-dev 
    DESTINATION "${FLUX_INSTALL_CMAKEDIR}")

endif() 

# Other 

if(BUILD_EXAMPLES)
  add_subdirectory(examples)
endif() 

if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
  add_subdirectory(third-party)
endif()


