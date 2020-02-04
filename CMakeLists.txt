cmake_minimum_required(VERSION 3.15)
project(Protocole_PolyLink)

set(CMAKE_C_STANDARD 11)

add_executable(Protocole_PolyLink src/main.c src/util/utils.h src/util/utils.c src/config/configIps.c src/config/configIps.h)
