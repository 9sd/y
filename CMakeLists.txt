cmake_minimum_required(VERSION 3.10)
project(openssl_demo C)

find_package(OpenSSL REQUIRED)

add_executable(openssl_demo main.c)
target_link_libraries(openssl_demo OpenSSL::SSL OpenSSL::Crypto)
