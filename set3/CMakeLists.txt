set(TARGET_NAME set3)

add_library(lib_set3 ex1.cpp)
target_include_directories(lib_set3 PUBLIC "include")

add_executable(${TARGET_NAME} set3.cpp)
find_package(OpenSSL REQUIRED)
target_link_libraries(${TARGET_NAME} lib_set3 OpenSSL::SSL)
