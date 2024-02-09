cmake_minimum_required(VERSION 3.7...3.28)

project(AVLTree)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(src/include)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0
)

FetchContent_MakeAvailable(Catch2)

add_executable(tests src/tests.cpp src/include/avl_node.hpp src/include/avl_tree.hpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

add_custom_target(run
    COMMAND tests
    DEPENDS tests
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
    COMMENT "Running tests"
)
