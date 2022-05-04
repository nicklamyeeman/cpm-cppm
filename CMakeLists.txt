cmake_minimum_required(VERSION 3.10)

set(SRC_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/)
set(INC_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/)
set(DOC_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/doc/)
set(TST_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/)
set(BIN_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/)
set(LIB_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib/)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/)

##
## CPM
##

project(cpm VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CPM_SRC_DIRECTORY ${SRC_DIRECTORY}cpm-src/)
set(CPM_INC_DIRECTORY ${INC_DIRECTORY}cpm-include/)

set(CPM-SOURCES main.cpp
    ${CPM_SRC_DIRECTORY}CPM.cpp)

add_executable(cpm ${CPM-SOURCES})

target_compile_definitions(cpm PUBLIC _CPM_)

target_include_directories(cpm PUBLIC ${CPM_INC_DIRECTORY})

##
## CPPM
##

project(cppm VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CPPM_SRC_DIRECTORY ${SRC_DIRECTORY}cppm-src/)
set(CPPM_INC_DIRECTORY ${INC_DIRECTORY}cppm-include/)

set(CPPM-SOURCES main.cpp
    ${CPPM_SRC_DIRECTORY}CPPM.cpp)

add_executable(cppm ${CPPM-SOURCES})

target_compile_definitions(cppm PUBLIC _CPPM_)

target_include_directories(cppm PUBLIC ${CPPM_INC_DIRECTORY})
