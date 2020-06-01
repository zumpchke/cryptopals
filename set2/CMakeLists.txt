set(TARGET_NAME set2)

add_library(lib_set2 ex1.cpp ex2.cpp ex3.cpp ex4.cpp ex5.cpp ex7.cpp)
target_include_directories(lib_set2 PUBLIC "include")

add_executable(${TARGET_NAME} set2.cpp)
find_package(OpenSSL REQUIRED)
target_link_libraries(${TARGET_NAME} lib_set2 OpenSSL::SSL)
