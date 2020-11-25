# -----------------------------

cmake_minimum_required(VERSION 3.14)
project(CUI)

# -----------------------------

add_library(CUI INTERFACE)

target_include_directories(CUI
    INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/cui>)
target_include_directories(CUI
    INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
