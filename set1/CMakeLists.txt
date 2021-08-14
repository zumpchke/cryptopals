set(TARGET_NAME set1)

add_library(lib STATIC ex1.cpp ex2.cpp ex3.cpp ex4.cpp ex5.cpp ex6.cpp ex7.cpp ex8.cpp)
find_package(OpenSSL REQUIRED)
if (${OpenSSL_FOUND})
	INCLUDE_DIRECTORIES(${OPENSSL_INCLUDE_DIR})
endif()
target_include_directories(lib PUBLIC "include" uu)

add_executable(${TARGET_NAME} set1.cpp)
target_link_libraries(${TARGET_NAME} lib OpenSSL::SSL)

