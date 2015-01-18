cmake_minimum_required(VERSION 2.6)

project(igconnector)

SET (CMAKE_CXX_COMPILER             "/usr/bin/clang++")
SET (CMAKE_C_COMPILER		    "/usr/bib/clang")
SET (CMAKE_CXX_FLAGS                "-g -O3 -std=c++11 -stdlib=libc++ -fPIC")

SET (CMAKE_LINKER_FLAGS    "-rdynamic")

SET (CMAKE_AR      "/usr/bin/llvm-ar")
SET (CMAKE_LINKER  "/usr/bin/llvm-ld")
SET (CMAKE_NM      "/usr/bin/llvm-nm")
SET (CMAKE_OBJDUMP "/usr/bin/llvm-objdump")
SET (CMAKE_RANLIB  "/usr/bin/llvm-ranlib")

add_executable(
        test_01_connect
        test_connect.cpp
        fixtures.cpp
)

add_executable(
        test_02_lsclient_connect
        test_lsclient_connect.cpp
        fixtures.cpp
)

add_executable(
        test_03_lsclient_subscribe
        test_lsclient_subscribe.cpp
        fixtures.cpp
)


add_executable(
        test_04_lsclient_getdata
        test_lsclient_getdata.cpp
        fixtures.cpp
)



target_link_libraries(
  test_01_connect
  igconnector3
)

target_link_libraries(
  test_02_lsclient_connect
  igconnector3
)

target_link_libraries(
  test_03_lsclient_subscribe
  igconnector3
)

target_link_libraries(
  test_04_lsclient_getdata
  igconnector3
)

