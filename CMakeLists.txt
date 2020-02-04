cmake_minimum_required(VERSION 3.15)
project(Protocole_PolyLink)

set(CMAKE_C_STANDARD 11)

add_executable(Protocole_PolyLink src/main.c src/util/utils.h src/util/utils.c src/config/configIps.c src/config/configIps.h src/util/list/linked_list.h src/util/list/linked_list.c src/protocolesStructs/protocolesStructs.c src/protocolesStructs/protocolesStructs.h src/util/polylink_socket.c src/util/polylink_socket.h src/util/receive.c src/util/send.c src/util/receive.h src/util/send.h)
