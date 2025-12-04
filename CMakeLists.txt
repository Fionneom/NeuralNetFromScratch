cmake_minimum_required(VERSION 3.10)
project(NeuralNetwork CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(NeuralNetwork 
    src/main.cpp
    src/neuron.cpp
    src/layer.cpp
    src/network.cpp
)

target_include_directories(NeuralNetwork PRIVATE 
    include
)