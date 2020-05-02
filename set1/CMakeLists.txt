set(TARGET_NAME set1)

add_library(lib ex1.cpp ex2.cpp)
target_include_directories(lib PUBLIC "include")

add_executable(${TARGET_NAME} set1.cpp)
target_link_libraries(${TARGET_NAME} lib)

