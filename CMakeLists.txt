#==============================================================================
# GMDS Project
#==============================================================================
cmake_minimum_required(VERSION 3.10.0)
#==============================================================================
# Operating System specificities (must be put at first)
#==============================================================================
if(APPLE)
    set(CMAKE_OSX_ARCHITECTURES x86_64)
endif()
#==============================================================================
project(concurrent_triangulation VERSION 0.1 LANGUAGES CXX)
#==============================================================================
# Compilation options mainly for testing purpose
#==============================================================================
option(WITH_TEST "Build test"                     OFF)
option(BUILD_SHARED_LIBS ""                       ON)
#==============================================================================
set(INC_FILES
        inc/ConcurrentTriangulation.h
        )
set(SRC_FILES
        src/ConcurrentTriangulation.cpp
        )
#==============================================================================
add_library(concurrent_triangulation ${INC_FILES} ${SRC_FILES})
#==============================================================================
# TARGET DEFINITION
#==============================================================================
include(GNUInstallDirs)

#LIBRARY TO INSTALL
target_link_libraries(concurrent_triangulation PUBLIC)

target_compile_features(concurrent_triangulation PUBLIC cxx_std_14)

# INCLUDE TO INSTALL
target_include_directories(concurrent_triangulation PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>
        )
set_target_properties(concurrent_triangulation PROPERTIES PUBLIC_HEADER "${INC_FILES}")

install(TARGETS concurrent_triangulation
        EXPORT CT
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})


#==============================================================================
if(WITH_TEST)
    add_subdirectory(tst)
endif(WITH_TEST)

#==============================================================================
# EXECUTABLE
#==============================================================================
add_executable(CT src/main.cpp)
target_link_libraries(CT PRIVATE concurrent_triangulation)
target_compile_features(CT PUBLIC cxx_std_14)
install(TARGETS CT)
