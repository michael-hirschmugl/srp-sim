cmake_minimum_required(VERSION 3.20)

# Projektname und C++-Standard
project(srp_project LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Alle Quell- und Header-Dateien
file(GLOB SOURCES CONFIGURE_DEPENDS
     "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB HEADERS CONFIGURE_DEPENDS
     "${CMAKE_SOURCE_DIR}/src/*.hpp")

add_executable(srp ${SOURCES} ${HEADERS})

# Falls Du später Bibliotheken brauchst, verlinkst Du sie hier, z. B.:
# target_link_libraries(srp PRIVATE <libname>)
