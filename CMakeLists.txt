cmake_minimum_required(VERSION 3.10)
project(
        SweepMine
        VERSION 1.0
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

set(SFML_INCLUDE_DIR "./build/_deps/sfml-src/include")


include_directories("include")
file(GLOB SOURCES "source/*.cpp")

add_executable(SweepMine ${SOURCES})
target_link_libraries(SweepMine PRIVATE sfml-graphics sfml-system sfml-window)
target_include_directories(SweepMine PRIVATE ${SFML_INCLUDE_DIR})