cmake_minimum_required(VERSION 3.4)
set(CMAKE_CXX_COMPILER g++-8)
add_compile_options(-Wall -Werror -g)
project(CryptoPals VERSION 1.0
		   DESCRIPTION "CryptoPals Exercises"
		   LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(set1)
add_subdirectory(set2)
cmake_policy(SET CMP0079 NEW)
target_link_libraries(set2 lib)
