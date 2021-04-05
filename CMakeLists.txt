cmake_minimum_required(VERSION 3.10)

# set the project name
project(SDK)

# add the executable
add_executable(Main sdk_list.c sdk_api.c crud_api.c main.c)