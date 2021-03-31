cmake_minimum_required(VERSION 3.10)

# set the project name
project(Test)

# add the executable
add_executable(Test sdk_list.c sdk_api.c crud_api.c main.c)