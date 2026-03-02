cmake_minimum_required(VERSION 3.10)
project(BloodBankSystem)
set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES
    "managers/*.cpp"
    "models/*.cpp"
    "ui/*.cpp"
    "utils/*.cpp"
    "main.cpp"
)

add_executable(BloodBankSystem ${SOURCES})

target_include_directories(BloodBankSystem PRIVATE
    ${CMAKE_SOURCE_DIR}
    managers
    models
    ui
    utils
)