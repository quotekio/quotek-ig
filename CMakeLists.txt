cmake_minimum_required(VERSION 2.6)

project(igconnector)

SET (CMAKE_CXX_COMPILER             "/usr/bin/g++")
SET (CMAKE_C_COMPILER		    "/usr/bin/gcc")
SET (CMAKE_CXX_FLAGS                "-O3 -std=c++11 -fPIC")

SET (CMAKE_LINKER_FLAGS    "-rdynamic")

add_library(
        igconnector3 SHARED
        src/broker.cpp
        src/igconnector.cpp
        src/utils.cpp
        src/lsclient.cpp
        src/lstable.cpp
        src/lssubscription.cpp
        src/http.cpp
)

find_library (PTHREAD pthread) 
find_library (CURL curl)

target_link_libraries(
  igconnector3
  curl
  pthread
)

install (TARGETS igconnector3 DESTINATION lib)
install (FILES "src/broker.hpp" DESTINATION include/igconnector/)
install (FILES "src/assoc.hpp" DESTINATION include/igconnector/)
install (FILES "src/utils.hpp" DESTINATION include/igconnector/)
install (FILES "src/brokerio.hpp" DESTINATION include/igconnector/)
install (FILES "src/igconnector.hpp" DESTINATION include/igconnector/)
install (FILES "src/lsclient.hpp" DESTINATION include/igconnector/)
install (FILES "src/lssubscription.hpp" DESTINATION include/igconnector/)
install (FILES "src/lstable.hpp" DESTINATION include/igconnector/)
install (DIRECTORY "src/rapidjson" DESTINATION include/igconnector/)

