cmake_minimum_required(VERSION 3.13)

project(n-puzzle)

set(CMAKE_CXX_STANDARD 17)

# find_package(fmt CONFIG REQUIRED)
# target_link_libraries(main PRIVATE fmt::fmt)

add_executable(8digit-bfs bfs.cpp NPuzzleStatus.hpp SearchMap.hpp)
add_executable(8digit-dfs dfs.cpp NPuzzleStatus.hpp SearchMap.hpp)

add_executable(x x.cpp NPuzzleStatus.hpp)
