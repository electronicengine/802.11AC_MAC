cmake_minimum_required(VERSION 3.17)
project(unix_Socket)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(unix_Sock main.cpp connection.cpp connection.h Threadpool.h Threadpool.cpp logging.cpp logging.h)