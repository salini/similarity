cmake_minimum_required(VERSION 2.8.7)
project (similarity  CXX)

if(${CMAKE_VERSION} VERSION_LESS "3.1")
    #message("CMAKE_VERSION less than 3.1")
    add_compile_options(-std=c++11)
else()
    #message("CMAKE_VERSION more than 3.1")
    set(CMAKE_CXX_STANDARD 11) # C++11...
    set(CMAKE_CXX_STANDARD_REQUIRED ON) #...is required...
    set(CMAKE_CXX_EXTENSIONS OFF) #...without compiler extensions like gnu++11
endif()

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" "${CMAKE_SOURCE_DIR}/cmake/macro")
include(macroUtils)
include(macroQt)

SET_VERSION(0 1 0)


#####################
#                   #
# FIND DEPENDENCIES #
#                   #
#####################
set(CMAKE_AUTOMOC ON) # Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOUIC ON) # Create code from a list of Qt designer ui files
set(CMAKE_INCLUDE_CURRENT_DIR ON)  # Find includes in corresponding build directories
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

find_package(OpenCV  REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

if(WIN32)
    find_package (Boost REQUIRED COMPONENTS system filesystem)
else()
    find_package (Boost REQUIRED COMPONENTS system  filesystem  program_options  iostreams)
endif()
include_directories (${Boost_INCLUDE_DIRS})
link_directories (${Boost_LIBRARY_DIRS})

##############################
#                            #
# CONFIGURE BUILD PROPERTIES #
#                            #
##############################
# Dynamic vs Static Linking
SET_BUILD_DYNAMIC_OPTION(DYNAMIC_LIB)
SET_CMAKE_RUNTIME_OUTPUT_DIRECTORIES()

## To get access to external configuration / data files during development
add_definitions(-DDEV_RESOURCES_DATA_PATH="${CMAKE_SOURCE_DIR}/resources")


#################
#               #
# PARSE SOURCES #
#               #
#################
include_directories(src)        #headers are in the same place as sources

add_subdirectory(examples)
#add_subdirectory(externalLibs)
add_subdirectory(resources)
add_subdirectory(src)

##### END of CMakeLists.txt

