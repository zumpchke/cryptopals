set(TARGET_NAME set1)

add_library(lib ex1.cpp ex2.cpp ex3.cpp ex4.cpp ex5.cpp ex6.cpp ex7.cpp ex8.cpp)
target_include_directories(lib PUBLIC "include")

add_executable(${TARGET_NAME} set1.cpp)
find_package(OpenSSL REQUIRED)
target_link_libraries(${TARGET_NAME} lib OpenSSL::SSL)

