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


add_library(
        igconnector SHARED
        src/broker.h
        src/igconnector.cpp
        src/utils.cpp
        src/lsclient/lsclient.cpp
)

add_executable(
        test_connect
        tests/test_connect.cpp
)

find_library (PTHREAD pthread) 
find_library (CURL curl)

target_link_libraries(
  igconnector
  curl
  pthread
)

target_link_libraries(
  test_connect
  igconnector
)




#install (TARGETS adam DESTINATION bin)
#install (TARGETS csv2influx DESTINATION tools)
#install (TARGETS nntrain DESTINATION tools)

#install (TARGETS igconnector DESTINATION lib)
#install (TARGETS influxdbbe DESTINATION lib)

#install (FILES "install/clanglibs/libc++.so" DESTINATION lib)
#install (FILES "install/clanglibs/librt.so" DESTINATION lib)
#install (FILES "install/tools/cbackup.sh" DESTINATION tools)
#install (FILES "install/tools/cleanall.sh" DESTINATION tools)


