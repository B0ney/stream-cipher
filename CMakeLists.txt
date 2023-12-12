cmake_minimum_required(VERSION 3.0.0)
project(cipher VERSION 0.1.0 LANGUAGES C)

include(CTest)
enable_testing()

add_executable(cipher 
    src/main.c
    src/cipher.c 
    src/cipher_state.c
)

include_directories(include)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
