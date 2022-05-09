cmake_minimum_required(VERSION 3.20)

set(SRC_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/)
set(INC_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/)
set(DOC_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/doc/)
set(TST_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/)
set(BIN_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/)
set(LIB_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib/)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIRECTORY})

set(COMMON_SRC  ${SRC_DIRECTORY}Replace.cpp
                ${SRC_DIRECTORY}Regex.cpp
                ${SRC_DIRECTORY}Dir.cpp
                ${SRC_DIRECTORY}PM.cpp
                main.cpp
)

##
## CPM
##

project(cpm VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CPM_SRC_DIRECTORY ${SRC_DIRECTORY}cpm-src/)
set(CPM_INC_DIRECTORY ${INC_DIRECTORY}cpm-include/)

set(CPM-SOURCES     ${COMMON_SRC}
                    ${CPM_SRC_DIRECTORY}CPM.cpp
)

find_package(Threads REQUIRED)

add_executable(cpm ${CPM-SOURCES})

# target_compile_definitions(cpm PUBLIC _DEBUG_)
target_compile_definitions(cpm PUBLIC _CPM_)
target_compile_definitions(cpm PUBLIC _LIB_="${CMAKE_INSTALL_PREFIX}/lib/cpm")

target_include_directories(cpm PUBLIC ${CPM_INC_DIRECTORY} ${INC_DIRECTORY})
target_link_libraries (cpm Threads::Threads)

install(TARGETS cpm PUBLIC_HEADER DESTINATION bin)

##
## CPPM
##

project(cppm VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CPPM_SRC_DIRECTORY ${SRC_DIRECTORY}cppm-src/)
set(CPPM_INC_DIRECTORY ${INC_DIRECTORY}cppm-include/)

set(CPPM-SOURCES    ${COMMON_SRC}
                    ${CPPM_SRC_DIRECTORY}CPPM.cpp
)

find_package(Threads REQUIRED)

add_executable(cppm ${CPPM-SOURCES})

# target_compile_definitions(cppm PUBLIC _DEBUG_)
target_compile_definitions(cppm PUBLIC _CPPM_)
target_compile_definitions(cppm PUBLIC _LIB_="${CMAKE_INSTALL_PREFIX}/lib/cppm")

target_include_directories(cppm PUBLIC ${CPPM_INC_DIRECTORY} ${INC_DIRECTORY})
target_link_libraries (cppm Threads::Threads)

install(TARGETS cppm PUBLIC_HEADER DESTINATION bin)

install(DIRECTORY ${LIB_DIRECTORY}cpm DESTINATION lib)
install(DIRECTORY ${LIB_DIRECTORY}cppm DESTINATION lib)